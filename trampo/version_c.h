#ifndef _VERSION_C_H_
#define _VERSION_C_H_

#include <string.h>
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
#define FIM_CONEXAO        0
#define INIT_FS            1
#define VOPEN_FS           2
#define VOPEN              3
#define VCLOSE             4
#define VREAD              5
#define VWRITE             6
#define VDELETE            7
#define VSEEK              8
#define VCREATION          9
#define VACCESSED         10
#define VLMOD             11
#define VCLOSE_FS         12

typedef int indice_arquivo_t;
typedef int indice_fs_t;

/* estrutura que representa uma requisição do 
 * cliente para o servidor 
 * */
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

/* estrutura que representa uma resposta do
 * servidor para o cliente
 * */
typedef struct resposta {
        int res_1;               // resultados
        indice_fs_t res_2;
        indice_arquivo_t res_3;
        uint32_t res_4;
        time_t res_5;
	char buffer [256];
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

void encerra_conexao ();

#endif

