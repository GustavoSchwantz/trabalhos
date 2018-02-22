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

	char sa [20];               // parâmetros para a operação
        int blocos;
	indice_fs_t fs;
	char nome [20];
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
        
	puts ("Criando porta de escuta...");

	if ((s = establish (PORT)) < 0) { 
	       	puts ("Erro ao criar porta de escuta no servidor."); 
		exit (1); 
	}

	puts ("Porta de escuta criada!");
	puts ("Servidor esperando por conexão...");

        int t;
        
        if ((t = get_connection (s)) < 0) {
		puts ("Erro ao tentar estabelecer uma conexão.");
		close (s);
                exit (1);
	}

	puts ("Conexão estabelecida!");

	requisicao_t req;
	resposta_t res;

        do {
                
		puts ("Esperando por requisição do cliente.");

		if (read_data (t, (void*) &req, sizeof (struct requisicao)) < 0) {
			puts ("Falha ao receber dados do cliente.");
                        exit (1);
		}

		puts ("Requisição recebida!");

		switch (req.op)
		{
			case 0:
				puts ("Encerrando conexão com o cliente...");
				break;
			case 1:
			{
				puts ("Função \"initfs\" selecionada.");

				if ((res.res_1 = initfs (req.sa, req.blocos)) == FALHA) 
					puts ("Falha ao criar novo sistema de arquivos.");
				
				puts ("Novo sistema de arquivos criado!");
				if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
					close (t);
					close (s);
                                        exit (1);
				}
				
			}
				break;
			case 2:
			{
				puts ("Função \"vopenfs\" selecionada.");

				if ( (res.res_2 = vopenfs (req.sa)) == FALHA)
					puts ("Falha ao abrir o sistema de arquivos.");
				
				puts ("Sistema de arquivos aberto!");
                                if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
			        	puts ("Falha ao enviar dados ao cliente");
	                                close (t);
					close (s);
					exit (1);
				}	
			}
		        	break;	
			case 3:
			{
				puts ("Função \"vopen\" selecionada.");

				if ( (res.res_3 = vopen (req.fs, req.nome, req.acesso, req.versao)) == FALHA)
					 puts ("Falha ao abrir arquivo.");
				
			        puts ("Arquivo aberto!");
                                if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
				        close (t);
				        close (s);
				         exit (1);
				}
			}
		        	break;	
			case 4:
			{
                        	puts ("Função \"vclose\" selecionada.");

				if ( (res.res_1 = vclose (req.arquivo)) == FALHA)
					puts ("Falha ao fechar arquivo.");
				
				puts ("Arquivo fechado!");
				if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
					close (t);
					close (s);
					exit (1);
				}
			}
		        	break;	
			case 5:
			{
                        	puts ("Função \"vread\" selecionada.");

				res.res_4 = vread (req.arquivo, req.tam, req.buffer);

                                puts ("Arquivo lido!");
                                if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
					close (t);
					close (s);
					exit (1);
				}
			}
		        	break;
			case 6:
			{
				puts ("Função \"vwrite\" selecionada.");

                                if ( (res.res_1 = vwrite (req.arquivo, req.tam, req.buffer)) == FALHA)
				       	puts ("Falha ao escrever arquivo.");
                              
				puts ("Arquivo escrito!");
                                if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
					close (t);
					close (s);
					exit (1);
				}
			}
		        	break;	
                        case 7:
			{
				puts ("Função \"vdelete\" selecionada.");
                                
				if ( (res.res_1 = vdelete (req.arquivo)) == FALHA)
					puts ("Falha ao deletar arquivo.");

				puts ("Arquivo deletado!");
				if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
					close (t);
					close (s);
					exit (1);
				}
			}
				break;
			case 8:
			{
                        	puts ("Função \"vseek\" selecionada.");

				if ( (res.res_1 = vseek (req.arquivo, req.seek)) == FALHA)
					puts ("Falha ao deletar arquivo.");
				
				puts ("Seek do arquivo atualizado!");
				if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
					close (t);
					close (s);
					exit (1);
				}
			}
		        	break;	
			case 9:
			{
				puts ("Função \"vcreation\" selecionada.");

				res.res_5 = vcreation (req.arquivo, req.versao);

				puts ("Tempo de criação do arquivo obtido!");

			        if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
				        close (t);
				        close (s);
				        exit (1);
				}	
			}
		        	break;	
			case 10:
			{
                        	puts ("Função \"vaccessed\" selecionada.");

				res.res_5 = vaccessed (req.arquivo, req.versao);

				puts ("Tempo de acesso obtido!");

				if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
					close (t);
					close (s);
					exit (1);
				}
			}
		        	break;
			case 11:
			{
				puts ("Função \"vlast_modified\" selecionada.");

				res.res_5 = vlast_modified (req.arquivo, req.versao);

				puts ("Tempo de última modificação obtido!");

				if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
					close (t);
					close (s);
					exit (1);
				}
			}
		        	break;
			case 12:
			{
                        	puts ("Função \"vclosefs\" selecionada.");

				res.res_1 = vclosefs (req.fs);

				puts ("Sistema de arquivos fechado!");

				if (write_data (t, (void*) &res, sizeof (struct resposta)) < 0) {
					puts ("Falha ao enviar dados ao cliente");
					close (t);
					close (s);
					exit (1);
				}
			}
		        	break;	
		}
	} while (req.op);	

	close (t);
	close (s);

	puts ("Conexão com o cliente encerrada.");
	puts ("Socket de escuta fechado!");
	puts ("Fim da execução do servidor");

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

