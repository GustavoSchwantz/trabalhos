#include "version_c.h"

int initfs (char * arquivo, int blocos)
{
	requisicao_t req;

	req.op = INIT_FS;          // indica a operação que será realizada no servidor

        strcpy (req.sa, arquivo);  // parâmetros que serão enviados na mensagem 
        req.blocos = blocos;
        
	/* envia a mensagem para o servidor */
	if (write_data (s, (void*) &req, sizeof (struct requisicao)) < 0) {
		puts ("Falha ao tentar enviar requisição ao servidor.");
                return FALHA;
	}

	resposta_t res;
        
	/* recebe o resultado da operação realizada no servidor */
	if (read_data (s, (void*) &res, sizeof (struct resposta)) < 0) {
		puts ("Falha ao receber resposta do servidor.");
		return FALHA;
	}

        return res.res_1; // retorna resultado 
}

indice_fs_t vopenfs (char * arquivo) 
{

}

indice_arquivo_t vopen (indice_fs_t fs, char * nome,  int acesso, int version)
{

}

int vclose (indice_arquivo_t arquivo)
{

}

uint32_t vread (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer)
{

}

int vwrite (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer)
{

}

int vdelete (indice_arquivo_t arquivo)
{

}

int vseek (indice_arquivo_t arquivo, uint32_t seek)
{

}

time_t vcreation (indice_arquivo_t arquivo, int versao)
{

}

time_t vaccessed (indice_arquivo_t arquivo, int versao)
{

}

time_t vlast_modified (indice_arquivo_t arquivo, int versao)
{

}

int vclosefs (indice_fs_t fs)
{

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
		       	return (-1);
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

