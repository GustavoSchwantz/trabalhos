#ifndef _VERSION_C_H_
#define _VERSION_C_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>


#define SUCESSO            1
#define FALHA              0
#define LEITURA            0
#define ESCRITA            1
#define LEITURAESCRITA     2
#define INIT_FS            0

typedef int indice_arquivo_t;
typedef int indice_fs_t;

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

int s; // socket por onde os dados serão trocados com o servidor

int initfs (char * arquivo, int blocos);

indice_fs_t vopenfs (char * arquivo);

indice_arquivo_t vopen (indice_fs_t fs, char * nome,  int acesso, int version);

int vclose (indice_arquivo_t arquivo);

uint32_t vread (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer);

int vwrite (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer);

int vdelete (indice_arquivo_t arquivo);

int vseek (indice_arquivo_t arquivo, uint32_t seek);

time_t vcreation (indice_arquivo_t arquivo, int versao);

time_t vaccessed (indice_arquivo_t arquivo, int versao);

time_t vlast_modified (indice_arquivo_t arquivo, int versao);

int vclosefs (indice_fs_t fs);

int read_data (int s, void *buf, int n);

int write_data (int s, void *buf, int n);

#endif

