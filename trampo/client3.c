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
	puts ("Tentando abrir sistema de arquivos no servidor...");

        indice_fs_t ifs;

	if ( (ifs = vopenfs ("file_system.bin")) == FALHA ) {
        	puts ("Falha ao abrir o sistema de arquivos no servidor.");
		exit (1);
	}

        puts ("Sistema de arquivos aberto!");

	char nome [20];

        printf ("Entre com o nome de um arquivo: ");
	scanf ("%s", nome);

	indice_arquivo_t ia;

	if ( (ia = vopen (ifs, nome, LEITURA, 0)) == FALHA ) {
        	puts ("Falha ao abrir o arquivo no servidor.");
		exit (1);
	}

	puts ("Arquivo aberto!");

	char conteudo [256];

	puts ("Lendo do arquivo...");

        if ( vread (ia, 256, conteudo) < 0 ) {
		puts ("Falha ao ler do arquivo.");
		exit (1);
	}
	
        printf ("Conteúdo: %s\n", conteudo);

        puts ("Fechando arquivo...");

	if ( vclose (ia) == FALHA ) {
        	puts ("Falha ao fechar o arquivo.");
		exit (1);
	}

	puts ("Arquivo fechado!");
	puts ("Fechando sistema de arquivos...");
        
	if ( vclosefs (ia) == FALHA ) {
        	puts ("Falha ao fechar o sistema arquivos.");
		exit (1);
	}
        
	puts ("Fechando conexão...");

	encerra_conexao ();
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

