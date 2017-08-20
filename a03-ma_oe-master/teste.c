#include "string.h"
#include "simplegrade.h"
#include "version.h" /* Nao esquece que o simplegrade.h do version.h ta comentado */
                         /* e a isNear tambem */

#define MAX_OPEN_FS 251      /* numero maximo de sistemas de arquivos abertos */
#define MAX_OPEN_FILES 2049  /* numero maximo de arquivos abertos */
#define DIRECTORY_BLOCKS 33  /* numero de blocos usado pelo diretorio */

#define YES 1
#define NO  0

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
       indice_fs_t fsHandle; /*Handle indicando a qual sistema de arquivo pertence o arquivo*/
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

extern file_system_t fst [MAX_OPEN_FS];  /* vetor de sistemas de arquivos */
extern entry_oft_t oft [MAX_OPEN_FILES]; /* tabela de arquivos abertos */

extern int open_fs;    /* numero de sistemas de arquivos abertos */
extern int open_files; /* numero de arquivos abertos */

void medium_test ()
{
	remove("versioning");
        initfs("versioning",500);
        indice_fs_t vfs = vopenfs ("versioning");

        WHEN ("Tento abrir um arquivo que não existe no modo ESCRITA");

	IF ("Esse é o primeiro arquivo do SAs");
        THEN("vopen deve retornar 1 como fh");

	indice_arquivo_t f;
       
	isEqual ( f = vopen (vfs, "a.txt", ESCRITA, 0), 1, 1);

	THEN("o número de arquivos abertos deve ser um");
        isEqual (open_files, 1, 1);

	IF ("Eu tentar escrever um bloco");
	THEN ("vwrite de retornar SUCESSO");
	
	char *block = (char*) calloc (BLOCO, sizeof (char));

        int i;

	for(i = 0; i < BLOCO; i++){
                block [i] = 'a';
        }

	isEqual (vwrite (f, BLOCO, block), SUCESSO, 1);

	IF ("Eu tentar fechar o arquivo");
        THEN ("vclose deve retornar SUCESSO");

	isEqual (vclose (f), SUCESSO, 1);

	IF ("O número de arquivos abertos era um");
        THEN ("Agora deve ser zero");

        isEqual (open_files, 0, 1);

	IF ("Se eu tentar abrir o mesmo arquivo no modo ESCRITA");
        THEN("vopen deve retornar 1 como fh novamente");

        isEqual ( f = vopen (vfs, "a.txt", ESCRITA, 1), 1, 1);

        THEN("o número de arquivos abertos deve ser um");
        isEqual (open_files, 1, 1);

        IF ("Eu tentar escrever um bloco");
        THEN ("vwrite de retornar SUCESSO");

        for(i = 0; i < BLOCO; i++){
                block [i] = 'b';
        }

        isEqual (vwrite (f, BLOCO, block), SUCESSO, 1);

        IF ("Eu tentar fechar o arquivo");
        THEN ("vclose deve retornar SUCESSO");

        isEqual (vclose (f), SUCESSO, 1);

        IF ("O número de arquivos abertos era um");
        THEN ("Agora deve ser zero");

	isEqual (open_files, 0, 1);

	IF ("Agora eu tentar abrir a primeira versão do arquivo em LEITURA");
        THEN ("vopen deve retornar 1 como fh");

        isEqual (f = vopen (vfs, "a.txt", LEITURA, 0), 1, 1);

	indice_arquivo_t f1;

	IF ("Agora eu tentar abrir a segunda versão do arquivo em LEITURA");
        THEN ("vopen deve retornar 2 como fh");

        isEqual (f1 = vopen (vfs, "a.txt", LEITURA, 1), 2, 1);
        
	THEN ("o número de arquivos abertos deve ser 2");

        isEqual (open_files, 2, 1);

	IF ("Eu tentar ler um bloco da primeira versão");
        THEN ("vread de retornar 4096");

        isEqual (vread (f, BLOCO, block), BLOCO, 1);

	free (block);
        free (fst [vfs].fat);
	fclose (fst [vfs].file);
}

void small_test ()
{
	remove ("versioning");

	WHEN ("Quando eu tento criar um SAs com 42 blocos");
        THEN ("a funcao initfs deve retornar SUCESSO");
        isEqual (initfs ("versioning", 42), SUCESSO, 1);

	indice_fs_t fsh;
        
	WHEN ("Quando eu tento abrir o SAs versioning");
        THEN ("a funcao vopenfs deve retornar 1 como fs handle");
        isEqual (( fsh = vopenfs ("versioning") ), 1, 1);

        indice_arquivo_t fh;

        // WHEN ("Quando eu tento abrir um arquivo passando um SAs que nao existe");
        // THEN ("a funcao deve retornar FALHA");
        // isEqual (( fh = vopen (fsh + 1, "lol.txt", LEITURA, 0) ), FALHA, 1);

        WHEN ("Quando eu tento abrir um arquivo que nao existe no modo ESCRITA");
        THEN ("a funcao deve retornar 1 como file handle");
        isEqual (( fh = vopen (fsh, "first_file.txt", ESCRITA, 0) ), 1, 1);

        // WHEN ("Quando eu tento abrir um arquivo que existe no modo LEITURA");

        // THEN ("a funcao deve retornar 2 como file handle");
        // isEqual (( fh = vopen (fsh, "lol.txt", ESCRITA, 0) ), 2, 1);

        THEN ("eu espero ter 1 arquivos abertos");
        isEqual (open_files, 1, 1);

	WHEN ("Quando eu tento escrever em um arquivo com permissão para escrita");
        THEN ("a funcao vwrite deve retornar SUCCESSO");
        
	char *str0 = "Gustavo Adolfo Schwantz Oliveira";
	
	isEqual ( vwrite (fh, strlen (str0), str0), SUCESSO, 1);

	WHEN ("Quando eu tento verificar o tamanho do arquivo");
        THEN ("ele deve ser igual ao numero de bytes escritos");
	isEqual ( oft [fh].seek, strlen (str0), 1);

        fclose (fst [fsh].file);
        free (fst [fsh].fat);
}

void initfs_test ()
{
	DESCRIBE ("Testes com a initfs");

	WHEN ("Quando o numero de blocos for insuficiente");
	THEN ("a funcao deve retornar FALHA");
	isEqual (initfs ("very_small_fs", 10), 0, 1);

	WHEN ("Quando eu tento criar um SAs com 500 blocos");
        THEN ("a funcao deve retornar SUCESSO");
        isEqual (initfs ("some_fs", 500), 1, 1);

	WHEN ("Quando eu tento criar um SAs que ja existe");
        THEN ("a funcao deve retornar FALHA");

	initfs ("unique_fs", 200);

        isEqual (initfs ("unique_fs", 200), 0, 1);

        WHEN ("Quando eu tentar criar um SAs de 40 blocos");
	THEN ("a funcao deve retornar SUCESSO");
        isEqual (initfs ("small_fs", 40), 1, 1);

	FILE *f = fopen ("small_fs", "rb");
        uint32_t fs;
        
	fseek (f, (33 - 1)*BLOCO + (BLOCO/2), SEEK_SET); 
        fread (&fs, sizeof (uint32_t), 1, f);
        	
	THEN ("o tamanho da FAT deve ser 6");
        isEqual (fs, 6, 1);

	THEN ("os valores da FAT devem ser [1, 2, 3, 4, 5, 0]");
        

	uint32_t fat [fs];

	fseek (f, 33*BLOCO, SEEK_SET);
        fread (fat, fs*sizeof (uint32_t), 1, f);

        isEqual (fat [0], 1, 1);
        isEqual (fat [1], 2, 1);
        isEqual (fat [2], 3, 1);
        isEqual (fat [3], 4, 1);
        isEqual (fat [4], 5, 1);
        isEqual (fat [5], 0, 1);

        THEN ("o terceiro bloco de dados deve ter indice 2");

	uint32_t x;

	fseek (f, 36*BLOCO, SEEK_SET);
        fread (&x, sizeof (uint32_t), 1, f);

        isEqual (x, 2, 1);	

	free (f);
}

void vopenfs_test ()
{
	initfs ("small_fs", 40);
	
	indice_fs_t fsh;
	uint32_t index;

        DESCRIBE ("Testes com a vopenfs");

        WHEN ("Quando eu tento abrir meu primeiro SAs");
        THEN ("a funcao deve retornar 1 como file handle");
        isEqual (( fsh = vopenfs ("small_fs") ), 1, 1);

	THEN ("eu devo ter um SAs aberto");
        isEqual (open_fs, 1, 1);

        THEN ("a entrada um deve estar ocupada");
        isEqual (fst [fsh].occupied, YES, 1);

	THEN ("o ponteiro do arquivao deve apontar para o primeiro bloco de dados");
	fread (&index, sizeof (uint32_t), 1, fst [fsh].file);
        isEqual (index, 1, 1);

        THEN ("o tamanho da FAT deve ser 6");
        isEqual (fst [fsh].fs, 6, 1);

	THEN ("a FAT deve ocupar um bloco");
        isEqual (fst [fsh].fb, 1, 1);


        THEN ("os valores da FAT devem ser [1, 2, 3, 4, 5, 0]");

        isEqual (fst [fsh].fat [0], 1, 1);
        isEqual (fst [fsh].fat [1], 2, 1);
        isEqual (fst [fsh].fat [2], 3, 1);
        isEqual (fst [fsh].fat [3], 4, 1);
        isEqual (fst [fsh].fat [4], 5, 1);
        isEqual (fst [fsh].fat [5], 0, 1);

        fclose (fst [fsh].file);
	free (fst [fsh].fat);
}

void vopen_test ()
{
	initfs ("small_fs", 42);
	indice_fs_t fsh = vopenfs ("small_fs");

        indice_arquivo_t fh;

        DESCRIBE ("Testes com a vopen");

        WHEN ("Quando eu tento abrir um arquivo passando um SAs que nao existe");
        THEN ("a funcao deve retornar FALHA");
        isEqual (( fh = vopen (fsh + 1, "lol.txt", LEITURA, 0) ), FALHA, 1);

	WHEN ("Quando eu tento abrir um arquivo que nao existe no modo ESCRITA");
        THEN ("a funcao deve retornar 1 como file handle");
        isEqual (( fh = vopen (fsh, "lol.txt", ESCRITA, 0) ), 1, 1);

	WHEN ("Quando eu tento abrir um arquivo que existe no modo LEITURA");

        THEN ("a funcao deve retornar 2 como file handle");
        isEqual (( fh = vopen (fsh, "lol.txt", ESCRITA, 0) ), 2, 1);

	THEN ("eu espero ter 2 arquivos abertos");
        isEqual (open_files, 2, 1);

        fclose (fst [fsh].file);
        free (fst [fsh].fat);
}

int main ()
{
        DESCRIBE ("Testes do Sistema de Arquivos Versionado");
        
	small_test ();
        // initfs_test ();
        // vopenfs_test ();
	// vopen_test ();
	// medium_test ();
	//GRADEME ();

	return 0;
}




