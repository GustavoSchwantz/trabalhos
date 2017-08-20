#include <stdio.h>
#include <stdlib.h>
#include "memvirt.h"

#define ON  1  /* valores possiveis p/ o bit de referencia */
#define OFF 0
#define TRUE  1 /* valores booleanos */
#define FALSE 0

/* estrutura p/ representar uma pagina */
struct reg {
    int content;      /* numero da pagina */
    int ref_bit;      /* bit de referencia */
    struct reg *next; /* proxima pagina */
    struct reg *last; /* pagina anterior */
};

/* estrutura p/ representar uma lista de paginas */
struct list {
	struct reg *nil;    /* sentinela da lista */
};

typedef struct reg cel;   /* definindo o tipo cel */
typedef struct list LIST; /* definindo o tipo LIST */

/* interface da lista encadeada */
void list_init (LIST *l);
cel *cell_factory (int c);
cel *list_search (LIST *l, int c);
void list_insert (LIST *l, cel *x);
void list_delete (cel *x);
void print_list (LIST *l);
void destroy_list (LIST *l);

/* estrutura p/ representar um processo */
struct process {
    LIST list;             /* lista de paginas q estao em memoria */
    LIST list2;            /* lista de paginas q foram acessadas no ultimo intervalo */
    uint32_t n_pages;      /* numero de paginas q estao em memoria */
    uint32_t n_frames;     /* numero de frames do processo */
    uint32_t n_frames_max; /* numero de frames maximo do processo */
    uint32_t wss;          /* tamanho do ws do processo */  
    uint32_t s_wss;        /* somatorio dos ws do processo */
    uint32_t n_wss;        /* numero de ws do processo */      
};

/* aloca a estrutura p/ os resultados */
struct result *result_create (int np); 
/* cria o vetor p/ representar os processos */
struct process *procs_create (int np, uint32_t nf, uint32_t *af);
/* retorna TRUE se o proc p estiver em l e FALSE caso o contrario */
int it_is_on_the_memory (LIST *l, int p);
/* ve se da p/ pegar o frame de outro processo. Se sim, ret TRUE e retira o frame do proc. Senao ret FALSE */
int get_from_other_process (struct process *p, int np, int pid);
/* escolhe uma pag vitima e libera um frame de um proc */
void clock_algorithm (struct process *p);
/* carrega uma pagina p/ a mem do processo p */
void load_page (struct process *p, int page);
/* ativa o bit de ref de uma pagina */
void turn_on_ref_bit (LIST *l, int page);
/* calcula o ws p/ todos os processos */
void calculates_ws (struct process *p, int np);
/* redistribui os frames entre os procs de acordo c/ o ws de c/ um */
void distribute_frames (struct process *p, int np, uint32_t nf, uint32_t *af);
/* calcula a taxa de PF p/ proc, ws medio e a taxa de PF p/ toda a simulação */
void latest_calculations (struct result *r, struct process *p, int np);
/* desaloca as listas de paginas de cada processo */
void release_procs (struct process *p, int np);

struct result * memvirt (int num_procs, uint32_t num_frames, char * filename, uint32_t interval)
{
   FILE *file = fopen (filename, "r");	
	int pid, page;
	uint32_t count = 0, available_frames = num_frames; /* variaveis p/ verificar o intervalo e frames disponiveis, respc. */
	struct result *r = result_create (num_procs);   
	struct process *p = procs_create (num_procs, num_frames, &available_frames);
	
   /* enquanto houver pids e paginas no arquivo */	
	while ( EOF != fscanf (file, "%d %d", &pid, &page) ) { 
	    list_insert ( &(p[pid].list2), cell_factory (page) );
	    /* verifica se a pagina esta em memoria */   	
	    if ( !it_is_on_the_memory (&(p[pid].list), page) ) {
	    	  ++(r->pfs[pid]); /* registra PF */
	    	  /* o processo tem frames disponiveis ? */
	    	  if ( p[pid].n_frames > 0 );   
	    	  /* o processo tem menos frames q o determinado pelo seu max ? */   
           else if ( p[pid].n_frames < p[pid].n_frames_max ) {   
               /* o sistema tem frames disponiveis ? */
               if ( available_frames > 0 ) {
                   --available_frames;
                   ++(p[pid].n_frames);            
               }
               /* da p/ pegar de outra processo ? */
               else if ( get_from_other_process (p, num_procs, pid) ) { 	
                   ++(p[pid].n_frames);                   
               } 
               /* senao pego um meu msm */                     	
               else {
                   clock_algorithm (&p[pid]); 
                   ++(p[pid].n_frames);      		
               }  
           }  
           /* senao pego um meu msm */
           else { 
               clock_algorithm (&p[pid]);
               ++(p[pid].n_frames);
           }               
           load_page (&p[pid], page);   	    
	    }
	    ++(r->refs[pid]); /* registra a referencia a pagina */
       turn_on_ref_bit (&(p[pid].list), page); /* indica q a pag foi acessada recentemente */    
	    ++count; 
	    /* ja chegou a hora de recalcular o ws de c/ processo? */
	    if ( count == interval ) {
           calculates_ws (p, num_procs);
           distribute_frames (p, num_procs, num_frames, &available_frames);
           count = 0;	    
	    }
	}
	
	latest_calculations (r, p, num_procs);
	fclose (file);
	release_procs (p, num_procs);
	free (p);
	
	return r;
}

void list_init (LIST *l)
{
	l->nil = cell_factory (-1);
	l->nil->next = l->nil;
	l->nil->last = l->nil;
}

cel *cell_factory (int c)
{
	cel *x;
	x = malloc (sizeof (cel));
	x->content = c;

	return x;
}

cel *list_search (LIST *l, int c) 
{
	cel *x = l->nil->next;

	while (x != l->nil && x->content != c) 
        x = x->next;

	return x;
}

void list_insert (LIST *l, cel *x)
{
	x->last = l->nil->last;
   l->nil->last->next = x;
   l->nil->last = x;
   x->next = l->nil;
}

void list_delete (cel *x)
{
	x->last->next = x->next;
	x->next->last = x->last;
   free (x);
}

void print_list (LIST *l)
{
	cel *x;

	for (x = l->nil->next; x != l->nil; x = x->next)
		printf("%d\n", x->content);
}

void destroy_list (LIST *l)
{
	cel *x;

	for (x = l->nil->next; x != l->nil; x = x->next)
		free (x);

	l->nil->next = l->nil;
	l->nil->last = l->nil;
}

struct result *result_create (int np)
{
	struct result *r;
	
	if ( (r = (struct result*) calloc (1, sizeof (struct result) )) == NULL ) {
	    printf ("NÃO FOI POSSÍVEL ALOCAR MEMÓRIA!\n");
	    exit (EXIT_FAILURE);
	}
	
	if ( (r->refs = (uint32_t*) calloc ( np, sizeof (uint32_t) )) == NULL ) {
	    printf ("NÃO FOI POSSÍVEL ALOCAR MEMÓRIA!\n");
	    exit (EXIT_FAILURE);
	}
	
	if ( (r->pfs = (uint32_t*) calloc ( np, sizeof (uint32_t) )) == NULL ) {
	    printf ("NÃO FOI POSSÍVEL ALOCAR MEMÓRIA!\n");
	    exit (EXIT_FAILURE);
	}
	
	if ( (r->pf_rate = (float*) calloc ( np, sizeof (float) )) == NULL ) {
	    printf ("NÃO FOI POSSÍVEL ALOCAR MEMÓRIA!\n");
	    exit (EXIT_FAILURE);
	}
	
	return r;
}

struct process *procs_create (int np, uint32_t nf, uint32_t *af)
{
   struct process *p;
	
	if ( (p = (struct process*) calloc ( np, sizeof (struct process) )) == NULL ) {
	    printf ("NÃO FOI POSSÍVEL ALOCAR MEMÓRIA!\n");
	    exit (EXIT_FAILURE);
	}
	
	int i;
	
	for (i = 0; i < np; ++i) {
       list_init (&(p[i].list));
       list_init (&(p[i].list2));
       p[i].n_pages = 0;
       p[i].n_frames = nf/np;
       p[i].n_frames_max = nf/np;
       p[i].s_wss = 0;        
       p[i].n_wss = 0;     
       
       (*af) = (*af) - (nf/np);     	
	}
	
	return p;
}

int it_is_on_the_memory (LIST *l, int p)
{
    if ( list_search (l, p) == l->nil )
        return FALSE;
        
    return TRUE;    
}

int get_from_other_process (struct process *p, int np, int pid)
{
    int i;
    
    for (i = 0; i < np; ++i)
        if ( i != pid && p[i].n_frames >= p[i].wss ) {
            if ( p[i].n_pages == p[i].n_frames ) 
                clock_algorithm (&p[i]);
            else 
            	 --(p[i].n_frames); 
            return TRUE;             
        }
            
    return FALSE;        
}

void clock_algorithm (struct process *p)
{
	cel *c;

	for (c = (p->list).nil->next; ; c = c->next) {
		//printf ("o problema é aqui!\n");
		if ( c != (p->list).nil && c->ref_bit == OFF ) {
		    cel *oh = (p->list).nil;
		    c->content = -1;
		    (p->list).nil = c;
		    list_delete (oh);
		    --(p->n_pages);
		    return;
		}
	   else if ( c != (p->list).nil ) 
          c->ref_bit = OFF;	
   }
}

void load_page (struct process *p, int page)
{
	list_insert ( &(p->list), cell_factory (page) );
	++(p->n_pages);
	--(p->n_frames);
}

void turn_on_ref_bit (LIST *l, int page)
{
    (list_search (l, page))->ref_bit = ON;
}

void calculates_ws (struct process *p, int np) 
{
	int i;
	cel *c;
	
	for (i = 0; i < np; ++i) {
		 int wss = 1;
		 int aux = ((p[i].list2).nil->next)->content; 
	    for (c = (p[i].list2).nil->next; c != (p[i].list2).nil; c = c->next) 
           if ( c->content != aux ) {
               ++wss;
               aux = c->content;           
           }    	    
	    p[i].wss = wss;
	    p[i].s_wss += wss;
	    ++(p[i].n_wss);
	    
	    destroy_list (&(p[i].list2));
	    list_init (&(p[i].list2));
   }
 }

void distribute_frames (struct process *p, int np, uint32_t nf, uint32_t *af)
{
    int i;
    
    for (i = 0; i < np; ++i) {
    	  (*af) += p[i].n_frames;
	     p[i].n_frames = 0;
	 }
	
	 for (i = 0; i < np; ++i) {
	     p[i].n_frames_max = (uint32_t) ((float) p[i].wss/nf) * (nf);
	     uint32_t count = 0;
	     while ( (*af) > 0 && count < p[i].n_frames_max ) {
            ++(p[i].n_frames);
            --(*af);
            ++count;	     
	     }	
	 }
}

void latest_calculations (struct result *r, struct process *p, int np)
{
    int i;
    uint32_t s_avg_ws = 0;
    float spf = 0.0;
    
    for (i = 0; i < np; ++i) {
        r->pf_rate[i] = ((float) r->pfs[i]/r->refs[i]);
        s_avg_ws += (!(p[i].n_wss)) ? 0 : (p[i].s_wss)/(p[i].n_wss); 
        spf += r->pf_rate[i];
    }
    
    r->avg_ws = s_avg_ws/np;
    r->total_pf_rate = spf/np;
}

void release_procs (struct process *p, int np)
{
	int i;
	
	for (i = 0; i < np; ++i) {
	    destroy_list (&(p[i].list));
	    destroy_list (&(p[i].list2));
	 }
}

