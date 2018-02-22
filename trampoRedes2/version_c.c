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
	requisicao_t req;

	req.op = VOPEN_FS;          // indica a operação que será realizada no servidor
        strcpy (req.sa, arquivo);

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

        return res.res_2; // retorna resultado 
}

indice_arquivo_t vopen (indice_fs_t fs, char * nome,  int acesso, int version)
{
	requisicao_t req;

	req.op = VOPEN;            // indica a operação que será realizada no servidor

        req.fs = fs;               // parâmetros que serão enviados na mensagem
	strcpy (req.nome, nome);
	req.acesso = acesso;
	req.versao = version;

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

        return res.res_3; // retorna resultado
}

int vclose (indice_arquivo_t arquivo)
{
	requisicao_t req;

	req.op = VCLOSE;            // indica a operação que será realizada no servidor
	req.arquivo = arquivo;

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

uint32_t vread (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer)
{
	requisicao_t req;

	req.op = VREAD;                      // indica a operação que será realizada no servidor

        req.arquivo = arquivo;               // parâmetros que serão enviados na mensagem
	req.tam = tamanho;
	strcpy (buffer, req.buffer);
        
	/* envia a mensagem para o servidor */
	if (write_data (s, (void*) &req, sizeof (struct requisicao)) < 0) {
		puts ("Falha ao tentar enviar requisição ao servidor.");
		return (-1);
	}

	resposta_t res;

	/* recebe o resultado da operação realizada no servidor */
	if (read_data (s, (void*) &res, sizeof (struct resposta)) < 0) {
		puts ("Falha ao receber resposta do servidor.");
		return (-1);
	}

	return res.res_4; // retorna resultado
}

int vwrite (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer)
{
	requisicao_t req;

        req.op = VWRITE;                     // indica a operação que será realizada no servidor

        req.arquivo = arquivo;               // parâmetros que serão enviados na mensagem
	req.tam = tamanho;
	strcpy (req.buffer, buffer);

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

int vdelete (indice_arquivo_t arquivo)
{
	requisicao_t req;

	req.op = VDELETE;                     // indica a operação que será realizada no servidor
	req.arquivo = arquivo;

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

int vseek (indice_arquivo_t arquivo, uint32_t seek)
{
	 requisicao_t req;

	 req.op = VSEEK;                     // indica a operação que será realizada no servidor
	 req.arquivo = arquivo;
	 req.seek = seek;

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

time_t vcreation (indice_arquivo_t arquivo, int versao)
{
	requisicao_t req;

        req.op = VCREATION;                     // indica a operação que será realizada no servidor
        req.arquivo = arquivo;
        req.versao = versao;

	/* envia a mensagem para o servidor */
        if (write_data (s, (void*) &req, sizeof (struct requisicao)) < 0) { 
	       	puts ("Falha ao tentar enviar requisição ao servidor.");
	        return (-1); 
        }

        resposta_t res;

        /* recebe o resultado da operação realizada no servidor */
        if (read_data (s, (void*) &res, sizeof (struct resposta)) < 0) {   
	       	puts ("Falha ao receber resposta do servidor.");
                return (-1);  
        }

        return res.res_5; // retorna resultado
}

time_t vaccessed (indice_arquivo_t arquivo, int versao)
{
	requisicao_t req;

        req.op = VACCESSED;                     // indica a operação que será realizada no servidor
        req.arquivo = arquivo;
        req.versao = versao;

        /* envia a mensagem para o servidor */
        if (write_data (s, (void*) &req, sizeof (struct requisicao)) < 0) {  
	       	puts ("Falha ao tentar enviar requisição ao servidor.");
	       	return (-1);
       	}

        resposta_t res;

        /* recebe o resultado da operação realizada no servidor */
        if (read_data (s, (void*) &res, sizeof (struct resposta)) < 0) {    
	       	puts ("Falha ao receber resposta do servidor.");
	        return (-1);
       	}
       
       	return res.res_5; // retorna resultado
}

time_t vlast_modified (indice_arquivo_t arquivo, int versao)
{
	requisicao_t req;

	req.op = VLMOD;                     // indica a operação que será realizada no servidor
        req.arquivo = arquivo;
	req.versao = versao;

	/* envia a mensagem para o servidor */
	if (write_data (s, (void*) &req, sizeof (struct requisicao)) < 0) {  
	       	puts ("Falha ao tentar enviar requisição ao servidor.");
	       	return (-1);
       	}

	resposta_t res;

        /* recebe o resultado da operação realizada no servidor */
	if (read_data (s, (void*) &res, sizeof (struct resposta)) < 0) {    
		puts ("Falha ao receber resposta do servidor.");
	        return (-1);
        }

        return res.res_5; // retorna resultado
}

int vclosefs (indice_fs_t fs)
{
	requisicao_t req;

	req.op = VCLOSE_FS;                     // indica a operação que será realizada no servidor
        req.fs = fs;

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

void encerra_conexao ()
{
	requisicao_t req;

        req.op = FIM_CONEXAO;

	/* envia a mensagem para o servidor */
	if (write_data (s, (void*) &req, sizeof (struct requisicao)) < 0)
        	puts ("Falha ao tentar enviar requisição ao servidor.");
}
