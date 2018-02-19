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
#include "version_c.h"

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
       	int op;                  // tipo de resultado

        int res_1;               // resultados
        indice_fs_t res_2;
        indice_arquivo_t res_3;
        uint32_t res_4;
        time_t res_5;
} resposta_t;

/* envia uma requisição para uma porta específica em um
 * hospedeiro específico. Retorna um socket de conexão
 * por onde os dados serão trocados */
int call_socket (char *hostname, unsigned short portnum);
/* escreve n bytes de buff no socket s.
 * Retorna o número de bytes escritos no socket*/
int write_data (int s, void *buf, int n);

int main ()
{
	int s;

	puts ("Tentando se conectar com servidor...");

	if ((s = call_socket ("gustavo-Inspiron-5566", 50000)) < 0) {
		puts ("Erro ao tentar estabelecer conexão com o servidor.");
		exit (1);
	}

	puts ("Conexão com o servidor estabelecida!");
	puts ("Enviando requisição...");
        
	requisicao_t req;

	req.op = 0;
	strcpy (req.sa, "small_fs");
	req.blocos = 500;

        write_data (s, (void *) &req, sizeof (struct requisicao));

	puts ("Requisição enviada!");

	close (s);

	return 0;
}

int call_socket (char *hostname, unsigned short portnum) 
{ 
	struct sockaddr_in sa; 
	struct hostent *hp; 
	int a, s; 
	
	if ((hp = gethostbyname (hostname)) == NULL) {             // existe esse hospedeiro ? 
		errno = ECONNREFUSED;                              
		return (-1);                                       
	} 
	
	memset (&sa, 0, sizeof(sa)); 
	memcpy ((char *) &sa.sin_addr, hp->h_addr, hp->h_length); // seta o endereço  
	
	sa.sin_family = hp->h_addrtype; 
	sa.sin_port = htons((u_short)portnum); 

	if ((s = socket (hp->h_addrtype, SOCK_STREAM, 0)) < 0)    // obtém socket  
		return(-1); 
	
	if (connect (s, &sa, sizeof sa) < 0) {                    // se conecta ao servidor 
		close(s); 
		return(-1); 
	} 
	
	return (s); 
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
		       	return(-1);
       	}

        return (bcount);
}

