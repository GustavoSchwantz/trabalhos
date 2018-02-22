#include "version_c.h"

/* envia uma requisição para uma porta específica em um
 * hospedeiro específico. Retorna um socket de conexão
 * por onde os dados serão trocados 
 * */
int call_socket (char *hostname, unsigned short portnum);

int main ()
{
	puts ("Tentando se conectar com servidor...");

	if ((s = call_socket ("gustavo-Inspiron-5566", 50000)) < 0) {
		puts ("Erro ao tentar estabelecer conexão com o servidor.");
		exit (1);
	}

	puts ("Conexão com o servidor estabelecida!");
        
        int opcao;

        do {
		printf ("Entre com uma opção: ");
		scanf ("%d", &opcao);

		switch (opcao)
		{
			case FIM_CONEXAO:
				encerra_conexao ();
				break;

			case INIT_FS:
			{
				char n [20];
				int b;

				printf ("Nome do novo sistema de arquivos: ");
				scanf ("%s", n);
				printf ("Número de blocos para o novo sistema de arquivos: ");
				scanf ("%d", &b);

				if (initfs (n, b) == FALHA)
					puts ("Não foi possível criar o sistema de arquivos.");
				else
					puts ("Sistema de arquivos criado.");
			}
				break;

                        case VOPEN_FS:
			{
				char n [20];
				indice_fs_t fs;

				printf ("Nome do sistema de arquivos: ");
				scanf ("%s", n);
                                
				/* verifica se é possível abrir mais um sistema de arquivos
				 * e se vopenfs não retorna FALHA
				 * */
		      		if (sa_abertos >= 5 ||
					       	(fs = vopenfs (n)) == FALHA)
				       	puts ("Não foi possível abrir o sistema de arquivos.");
				else {
					fst [sa_abertos].occupied = YES;   // preenche entrada na TAs abertos
					strcpy (fst [sa_abertos].nome, n);
					fst [sa_abertos].indice = fs;
					fst [sa_abertos].arqs_abertos = 0;

					++sa_abertos; // mais um sistema de arquivos aberto

				        puts ("Sistema de arquivos aberto.");
				}
			}
				break;

			case VOPEN:
			{
				

                         

			}
		        	break;	

			default:
				puts ("Opção inválida!");
		}

	} while (opcao);	

	close (s);

	puts ("Conexão com o servidor encerrada.");

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
	
	memset (&sa, 0, sizeof (sa)); 
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

