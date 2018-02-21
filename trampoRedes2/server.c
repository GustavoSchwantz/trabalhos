#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <signal.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
#include <netinet/in.h> 
#include <netdb.h>
#include "version_s.h"

#define PORT           50000
#define MAXHOSTNAME    50

typedef struct requisicao {
        int op;                     // operação a ser realizada no servidor

	char sa [10];               // parâmetros para a operação
        int blocos;
	indice_fs_t fs;
	char nome [10];
	int acesso;
	int versao;
	indice_arquivo_t arquivo;
        uint32_t tam;
        char buffer [256];
        uint32_t seek;	
} requisicao_t;

typedef struct resposta {
	int res_1;               // resultados
	indice_fs_t res_2;
	indice_arquivo_t res_3;
	uint32_t res_4;
        time_t res_5;
} resposta_t;

/* recebe um número de porta como parâmetro e 
 * devolve um socket TCP associado a  aquela 
 * porta
 *  */
int establish (unsigned short pn);

/* recebe um socket como parâmetro e espera por
 * uma requisão neste socket. Caso receba, devolve
 * um novo socket para a conexão
 * */
int get_connection (int s);

/* preenche buf com n bytes lidos do socket s.
 * Retorna o número de bytes lidos do socket 
 * */
int read_data (int s, void *buf, int n);

/* escreve n bytes de buf no socket s.
 *  * Retorna o número de bytes escritos no socket*/
int write_data (int s, void *buf, int n);

int main ()
{
	int s;

	if ((s = establish (PORT)) < 0) { 
	       	puts ("Erro ao criar porta de escuta no servidor."); 
		exit (1); 
	}

	puts ("Servidor esperando por requisição...");

        int t;
        
        if ((t = get_connection (s)) < 0) {
		puts ("Erro ao tentar estabelecer uma conexão.");
		close (s);
                exit (1);
	}

	requisicao_t req;
	resposta_t res;

        for ( ; ; ) {

		if (read_data (t, (void*) &req, sizeof (struct requisicao)) < 0) {
			puts ("Falha ao receber dados do cliente.");
                        exit (1);
		}

		switch (req.op)
		{
			case 0:
			{
				res.res_1 = initfs (req.sa, req.blocos);
                                
				if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
                                        exit (1);
				}
			}

			break;
		}
	}	

	close (t);
	close (s);

	return 0;
}

int establish (unsigned short pn) 
{ 
	char myname [MAXHOSTNAME + 1]; 
	int s; 
	struct sockaddr_in sa; 
	struct hostent *hp; 
	
	memset (&sa, 0, sizeof (struct sockaddr_in));          // limpa a estrutura

	if ( gethostname (myname, MAXHOSTNAME) < 0 )  	       // pega o nome do hospedeiro
	        return (-1);

	hp = gethostbyname (myname);                           // usa o nome para pegar informações
							       // sobre o endereço	  
	
	if (hp == NULL)                                        // o hospedeiro existe?  
		return (-1); 
	
	sa.sin_family = hp->h_addrtype;                        // tipo do endereço do hospedeiro  
	sa.sin_port = htons (pn);                              // o número de porta do hospedeiro  
	
	if ((s = socket (AF_INET, SOCK_STREAM, 0)) < 0)        // cria o socket  
		return (-1); 
	
	if (bind (s, &sa, sizeof (struct sockaddr_in)) < 0) { 
		close(s); 
		return(-1);                                    // associa o  end. do hosp. ao socket  
	}

        listen (s, 3);	
	
	return (s); 
}
 
int get_connection (int s) 
{ 
	int t;                                   

	if ( (t = accept (s, NULL, NULL) ) < 0) // aceita a conexão se receber uma requisição 
		return (-1); 

	return (t);                             // retorna socket para a conexão 
}

int read_data (int s, void *buf, int n) 
{ 
	int bcount;                                   // conta o número de bytes lido  
	int br;                                       // bytes lidos em uma chamada a read

	bcount = 0; 
	br = 0; 
	
	/* enquanto não houver lido n bytes */
	while (bcount < n) {
                /* lê br bytes do socket */		
		if ( ( br = read (s, buf, n-bcount) ) > 0 ) { 
			bcount += br;                  // incrementa o contador de bytes */ 
			buf += br;                     // atualiza ptr do buffer 
		} 
		else if (br < 0)                       // deu ruim 
			return(-1); 
	} 
	
	return (bcount); 
}

int write_data (int s, void *buf, int n)
{
       	int bcount;                                              // conta o número de bytes escrito  
        int br;                                                  // bytes escritos em uma chamada a write

        bcount = 0;
        br = 0;

        /* enquanto não houver escrito n bytes */
        while (bcount < n) {
	       	/* escreve br bytes no socket */
	        if ( ( br = write (s, buf, n-bcount) ) > 0 ) {
		       	bcount += br;                           // incrementa o contador de bytes                     
			buf += br;                              // atualiza ptr do buffer
	       	}
	       	else if (br < 0)                                // deu ruim 
			return (-1);
	}

	return (bcount);
}

