#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "roteador.h"

#define NUM_CONSUMER 4 /* numero de threads que retiram pacotes da fila */

/* estrutura p/ os parametros da thread produtora */
struct p_args {
    uint32_t *pacotes;
    int num_pacotes;
    uint32_t *queue;
    int num_enlaces;
};

/* estrutura p/ os parametros das quatro threads consumidoras */
struct c_args {
    entrada *rotas;
    int num_rotas;
    uint32_t *queue;
    uint32_t *list;
    int num_enlaces;
    int num_pacotes;
};

struct p_args pa;
struct c_args ca;

int queue_size; /* numero de pacotes que estao na fila */
int consumed;   /* numero de total de pacotes processados pelas consumidoras */
int in;         /* ptr logico para o inserir na fila */
int out;        /* ptr logico para o remover da fila */

/* mutexes p/ garantirem a sicronizacao das threads */
pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER; /* lock p/ exclusao mutua no acesso a fila */
pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER; /* lock p/ acesso a lista. Apenas as 4 threads consumidoras usam */

/* cria um vetor de tamanho n */
uint32_t* queue_create (int n);
/* thread coordenadora que insere pacotes na fila */
void* producer_thread (void *x);
/* serao as quatro threads que pegarao os pacotes da fila e farao o devido processamento */
void* consumer_thread (void *x);
/* insere um pacote na fila */
void enqueue (uint32_t *q, int n, uint32_t p);
/* remove um pacote da fila */
uint32_t dequeue (uint32_t *q, int n);

/* recebe um pacote, a tabela de roteamento, o tamanho da 
 * tabela roteamento e devolve o numero do enlace correspondente 
 * a aquele pacote
 */
int get_route (uint32_t p, entrada *r, int nr);

/* recebe o numero de bits da parte de rede e devolve a mascara
 * correspondente
 */
uint32_t get_mask (int n);


uint32_t* roteamento (entrada * rotas, int num_rotas, uint32_t * pacotes, 
	int num_pacotes, int num_enlaces) 
{
    queue_size = 0; /* inicialmente a fila esta vazia */
    consumed = 0;   /* inicialmente nenhum item foi consumido ainda */

    in = 0;         /* como a fila esta vazia */
    out = 0;

	uint32_t *queue, *list; /* a fila e lista de pacotes p/ cada enlace */
    
    /* cria a fila e a lista */
    queue = queue_create (num_enlaces);
    list = queue_create (num_enlaces + 1);

    pthread_t producer; /* thread coordenadora */
    int rp;

    /* parametros que serao passados p/ a thread coordenadora */
    pa.pacotes = pacotes;
    pa.num_pacotes = num_pacotes;
    pa.queue = queue;
    pa.num_enlaces = num_enlaces;
    
    /* cria a thread coordenadora */
    rp = pthread_create (&producer, NULL, producer_thread, (void *) &pa);

    if (rp) {
        printf ("Falha ao criar a thread produtora. O código retornado foi %d\n", rp);
        exit(-1);
    }

    pthread_t consumers[NUM_CONSUMER]; /* threads que retiram da fila */
    int rc;

    int i;

    /* parametros que serao passados p/ as quatro threads */
    ca.rotas = rotas;
    ca.num_rotas = num_rotas;
    ca.queue = queue;
    ca.list = list;
    ca.num_enlaces = num_enlaces;
    ca.num_pacotes = num_pacotes;
    
    /* cria as threads */
    for(i = 0; i < NUM_CONSUMER; ++i) {
        rc = pthread_create (&consumers[i], NULL, consumer_thread, (void *) &ca);  
        if (rc) {
            printf ("Falha ao criar uma thread consumidora. O código retornado" 
          	    "pela thread %d foi %d\n", i, rc);
            exit(-1);
        }
    }

    /* a thread principal espera pelo encerramento das threads que fazem o processamento */
    for(i = 0; i < NUM_CONSUMER; ++i) {
        rc = pthread_join (consumers[i], NULL);  
        if (rc) {
            printf ("Falha! O código retornado pelo join é %d\n", rc);
            exit(-1);
        }
    }

     /* da free so na fila, pois a lista deve ser retornada */
    free (queue);

    return list;
}

uint32_t* queue_create (int n)
{
	uint32_t *q;

	if ( (q = (uint32_t*) calloc (n, sizeof (uint32_t))) == NULL ) {
		printf ("Não foi possível alocar memória.\n");
		exit (1);
	}

	return q;
}

void* producer_thread (void *x)
{
	struct p_args *args; /* para receber os parametros */
	int produced;        /* numero de pacotes retirados da lista de pacotes */

	args = (struct p_args *) x; /* pega os parametros */
	produced = 0;               /* nenhum pacote retirado ainda */
    
    /* enquanto houver pacotes p/ serem retirados da lista de pacotes... */ 
	for ( ; produced < args->num_pacotes; ) {
        
        /* ... pega um pacote... */
        uint32_t p = args->pacotes[produced];
        
        pthread_mutex_lock (&mutex_a);

        /* ... se a fila nao tiver cheia, coloca o pacote nela. */
        if (queue_size < args->num_enlaces) {

        	enqueue (args->queue, args->num_enlaces, p); 
            queue_size++;
            produced++;
        }

		pthread_mutex_unlock (&mutex_a);
	}
}

void* consumer_thread (void *x)
{
	struct c_args *args; /* para receber os parametros */

	args = (struct c_args *) x; /* pega os parametros */
    
    /* para sempre (so que nao) */
	for ( ; ; ) {

		uint32_t p;
    
        pthread_mutex_lock (&mutex_a);
        
        /* se a fila nao estiver vazia... */
        if (queue_size > 0) {
            
            /* ... pega uma pacote. Senao... */
            p = dequeue (args->queue, args->num_enlaces);
            queue_size--;
            consumed++;
        }
        else {
            
            /* todos os pacotes ja foram processados ? */
        	if (consumed == args->num_pacotes) {
                
                /* se sim, sai do loop */
        		pthread_mutex_unlock (&mutex_a);
        		break;
        	}
            
            /* senao, tenta outra vez */
            pthread_mutex_unlock (&mutex_a);
            continue; 
        }

        pthread_mutex_unlock (&mutex_a);

        /* com o pacote e tabela, procura o enlace de destino */
        int e = get_route (p, args->rotas, args->num_rotas);

        pthread_mutex_lock (&mutex_b);

        /* contabiliza p/ qual enlace foi o pacote */
        args->list[e]++;

        pthread_mutex_unlock (&mutex_b);
	}
}

void enqueue (uint32_t *q, int n, uint32_t p)
{
    q[in] = p;
    in = (in + 1) % n;
}

uint32_t dequeue (uint32_t *q, int n)
{
	uint32_t p = q[out];
	out = (out + 1) % n;
    return p;
}

int get_route (uint32_t p, entrada *r, int nr)
{
	int e = 0; /* enlace da entrada de maior prefixo */
    int s = 0; /* bits da parte de rede da entrada de maior prefixo */
    int i;
    
    /* compara um pacote com cada entrada da tabela */
    for (i = 0; i < nr; ++i) {
        
        /* pega uma mascara */
    	uint32_t m = get_mask (r[i].mascara);
        
        /* se o resultado da AND bit a bit do endereco do pacote
         * com a mascara de rede for igual ao resultado da AND bit
         * a bit do endereco com a mascara e essa mascara for maior 
         * do q a ultima, salva o tamanho da mascara e o enlace
         */ 
    	if ( (p & m) == (r[i].endereco & m) && r[i].mascara > s) {
    		s = r[i].mascara;
    		e = r[i].enlace;
    	}
    }

    return e;
}

uint32_t get_mask (int n)
{
	uint32_t m = 0;

	m = ~m;

	m = m << (32 - n);

	return m;
}