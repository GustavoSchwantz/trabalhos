#ifndef _VERSION_C_H_
#define _VERSION_C_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SUCESSO            1
#define FALHA              0
#define LEITURA            0
#define ESCRITA            1
#define LEITURAESCRITA     2

typedef int indice_arquivo_t;
typedef int indice_fs_t;

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

#endif

