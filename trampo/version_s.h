#ifndef _VERSION_S_H_
#define _VERSION_S_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SUCESSO 1
#define FALHA 0
#define LEITURA 0
#define ESCRITA 1
#define LEITURAESCRITA 2
#define MAXVERSIONS 8            // máximo de versões que um arquivo pode ter 
#define MAXBLOCKSVERSION 256     // máximo de blocos que uma versão pode mudar
#define BLOCO 4096
#define MAX_OPEN_FS 251          // numero maximo de sistemas de arquivos abertos 
#define MAX_OPEN_FILES 2049      // numero maximo de arquivos abertos 
#define DIRECTORY_BLOCKS 33      // numero de blocos usado pelo diretorio  
#define YES 1                    // algumas macros  
#define NO  0

typedef int indice_arquivo_t;
typedef int indice_fs_t;

/* estrutura para representar o descritor do arquivo */
typedef struct fcb {
	char name[256];                     /* nome do arquivo  */
	time_t tcreation [MAXVERSIONS];     /* tempo de criacao do arquivo */
        time_t last_mod [MAXVERSIONS];      /* tempo da ultima modificacao */
	time_t last_ace [MAXVERSIONS];      /* tempo de ultimo acesso */
	uint32_t first_block [MAXVERSIONS]; /* indice do primeiro bloco */ 
	uint32_t size [MAXVERSIONS];        /* tamanho do arquivo em bytes */
	int nversions;                      /* numero de versoes que o arquivo possui */
} fcb_t;

/* estrutura que representa uma entrada na tabela de arquivos abertos */
typedef struct entry_oft {
	indice_fs_t owner;      /* indica a qual sistema de arquivo pertence o arquivo */
	int occupied;           /* flag que indica se a entrada esta sendo usada */
        uint32_t seek;          /* seek atual do arquivo */
	int version;            /* versão do arquivo */
	int acess;              /* permissao para o acesso do arquivo */
        fcb_t *fcb;             /* ponteiro para um descritor do arquivo */
} entry_oft_t;

/* estrutura que representa um sistema de arquivos */
typedef struct file_system {
	int occupied;          /* flag que indica se a entrada esta sendo usada */
        FILE *file;            /* ponteiro para o arquivao */
	fcb_t directory [256]; /* vetor para o diretorio */
	uint32_t *fat;         /* ponteiro para a FAT */ 
	uint32_t fs;           /* tamanho da FAT */
	uint32_t fb;           /* numero de blocos que a FAT ocupa */
	uint32_t fblocks;      /* numero de blocos livres no SAs */
} file_system_t;

file_system_t fst [MAX_OPEN_FS];  /* tabela de sistemas de arquivos abertos */
entry_oft_t oft [MAX_OPEN_FILES]; /* tabela de arquivos abertos */

int open_fs;    /* numero de sistemas de arquivos abertos */
int open_files; /* numero de arquivos abertos */

int there_is_a_file_named (char *arquivo);
indice_fs_t search_for_fst_free_entry ();
int it_is_open (indice_fs_t fs);
fcb_t * search_file (indice_fs_t fs, char *n);
fcb_t * search_directory (indice_fs_t fs);
void set_fcb (fcb_t *fcb, int v);
indice_arquivo_t get_a_file_handle ();
fcb_t * create_another_version (indice_fs_t fs, fcb_t *fcb, int v);
int get_a_free_block (indice_fs_t fs);
void give_a_block_back (indice_fs_t fs, uint32_t index);
void give_a_free_block (indice_fs_t fs, uint32_t index, fcb_t *fcb, int v);
void read_a_block (indice_fs_t fs, uint32_t *b, uint32_t index);
void write_a_block (indice_fs_t fs, uint32_t *b, uint32_t index);
int alloc_blocks (indice_arquivo_t fh, uint32_t n);
uint32_t get_index (indice_arquivo_t fh, uint32_t x);
void free_blocks (indice_fs_t fs, uint32_t fb);

/** Inicializa o arquivo no sistema de arquivos hospedeiro.
 *
 *  Deve ser chamada apenas uma vez para um determinado sistema de arquivos.
 *  Caso o nome de arquivo já exista, deve retornar erro.
 *  Também deve retornar erro caso o número de blocos não seja o suficiente
 *  para armazenar os metadados pelo menos.
 *
 *  @param arquivo nome do arquivo no sistema de arquivos hospedeiro
 *  @param blocos número de blocos do arquivo
 *  @return SUCCESSO ou FALHA
 */
int initfs (char * arquivo, int blocos);


/** Abre um sistema de arquivos.
 *
 *  @param nome do arquivo no sistema de arquivos hospedeiro
 *  @return file handle do descritor de sistema de arquivos ou FALHA
 */

indice_fs_t vopenfs(char * arquivo);


/** Abre um arquivo versionado.
 *
 *
 * @param fs o file handle do sistema de arquivos
 * @param nome o arquivo a ser aberto
 * @param acesso LEITURA, ESCRITA ou LEITURAESCRITA
 * @param versao versão a ser aberta
 * @return índice do arquivo aberto, FALHA se não abrir
 */
indice_arquivo_t vopen(indice_fs_t fs, char * nome,  int acesso, int version);

/** Fecha um arquivo versionado.
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @return SUCESSO OU FALHA
 */
int vclose(indice_arquivo_t arquivo);

/** Lê bytes de um arquivo versionado aberto.
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @param tamanho número de bytes a serem lidos
 * @param buffer ponteiro para buffer onde serão armazenados os bytes lidos
 * @return número de bytes lidos
 */
uint32_t vread(indice_arquivo_t arquivo, uint32_t tamanho, char *buffer);

/** Escreve bytes em um arquivo versionado aberto.
 *
 * A escrita é sempre realizada no modo append, ou seja, no fim do arquivo.
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @param tamanho número de bytes a serem escritos
 * @param buffer ponteiro para conteúdo a ser escrito
 * @return SUCESSO ou FALHA
 */
int vwrite(indice_arquivo_t arquivo, uint32_t tamanho, char *buffer);

/** Apaga um arquivo e o fecha.
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @return SUCESSO ou FALHA
 */

int vdelete(indice_arquivo_t arquivo);

/** Modifica a posição atual de leitura ou escrita do arquivo
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @param seek deslocamento em relação ao início do arquivo
 * @return SUCESSO ou FALHA
 */
int vseek(indice_arquivo_t arquivo, uint32_t seek);

/** Retorna o tempo em que uma versão do arquivo foi criado
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @param versao versão a ser retornada
 * @return tempo
 */
time_t vcreation(indice_arquivo_t arquivo, int versao);

/** Retorna o tempo em que a versão do arquivo foi acessado
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @return tempo
 */
time_t vaccessed(indice_arquivo_t arquivo, int versao);

/** Retorna o tempo em que o arquivo foi modificado
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @param versao versão a ser retornada
 * @return tempo
 */
time_t vlast_modified(indice_arquivo_t arquivo, int versao);

int vclosefs (indice_fs_t fs);

#endif
