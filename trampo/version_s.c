#include "version_s.h"

int initfs (char *arquivo, int blocos)	
{
	/* retorna FALHA se o nome de arquivo ja existe ou se o numero de blocos nao e suficiente */ 
	if ( there_is_a_file_named (arquivo) ||  blocos < DIRECTORY_BLOCKS + 1 )	{				
	    return FALHA;
	}
       
        FILE *f = fopen (arquivo, "wb"); 
	uint32_t *b = (uint32_t*) calloc (1024, sizeof (uint32_t)); /* cria um bloco zerado */
        uint32_t i;
        
	/* grava os blocos onde ficarao os diretorios */
	for (i = 0; i < DIRECTORY_BLOCKS; ++i)
		fwrite (b, BLOCO, 1, f);
        
	uint32_t fb = ((blocos - DIRECTORY_BLOCKS -1)/1024) + 1; /* calcula o numero de blocos que a FAT ira ocupar */
        uint32_t db = blocos - DIRECTORY_BLOCKS - fb; /* calcula o numero de blocos de dados (tamanho FAT) */
        uint32_t fat [db]; /* fat que vai ser gravada no arquivo */

	/* inicializa a FAT */
        for (i = 0; i < db - 1; ++i) 
	        fat [i] = i + 1;	
        
        fat[i] = 0;

        /* o indicador de posicao do arquivo e posto apos o diretorio */
	fseek (f, -BLOCO/2, SEEK_CUR);         
	/* grava o tamanho da FAT no arquivo */ 
        fwrite (&db, sizeof (uint32_t), 1, f);
        /* grava o numero de blocos que a FAT ocupa no arquivo */	
        fwrite (&fb, sizeof (uint32_t), 1, f);
        /* grava o numero de blocos dados livres no arquivo */
        fwrite (&db, sizeof (uint32_t), 1, f);

        /* posiciona o indicador de posicao do arquivo no final do arquivo */
        fseek (f, 0, SEEK_END); 

         /* grava os blocos onde ficara a FAT */
	for (i = 0; i < fb; ++i)
		fwrite (b, BLOCO, 1, f);
        
	/* posiciona o indicador de posicao do arquivo no inicio do primeiro bloco onde esta FAT */
        fseek (f, DIRECTORY_BLOCKS*BLOCO, SEEK_SET); 	
	/* grava a FAT no arquivo */
        fwrite (fat, db*sizeof (uint32_t), 1, f); 	
        /* posiona o indicador de posicao do arquivo no final do arquivo */
        fseek (f, 0, SEEK_END);

        /* grava os blocos de dados */
        for (i = 0; i < db; ++i) {
		b[0] = i; /* grava o indice para o bloco de dados */
		fwrite (b, BLOCO, 1, f);
	}

        fclose (f);
	free (b);

        return SUCESSO;	
}

indice_fs_t vopenfs (char * arquivo)
{
	/* retorna FALHA se o nome de arquivo nao existe */
        if ( open_fs == MAX_OPEN_FS  || !there_is_a_file_named (arquivo) )   {
            return FALHA;
        }

	indice_arquivo_t fsh = search_for_fst_free_entry (); /* obtem o file handle do SAs */
        ++open_fs; /* mais um SAs aberto */	
        
        fst [fsh].occupied = YES; /* aquela entrada da tabela de SAs abertos esta agora ocupada */

	/* abre o arquivo p/ leitura e escrita */
        fst [fsh].file = fopen (arquivo, "rb+");

        /* carrega o diretorio */
        fread (fst [fsh].directory, 256*sizeof (fcb_t), 1, fst [fsh].file);

        /* obtem o tamanho da FAT */
	fread (&fst [fsh].fs, sizeof (uint32_t), 1, fst [fsh].file);

	/* obtem o numero de blocos da FAT */
	fread (&fst [fsh].fb, sizeof (uint32_t), 1, fst [fsh].file);

	/* obtem o numero de blocos de dados livres */
        fread (&fst [fsh].fblocks, sizeof (uint32_t), 1, fst [fsh].file);
        
	/* aloca memoria para a FAT */
        fst [fsh].fat = (uint32_t*) calloc (fst [fsh].fs, sizeof (uint32_t));

	/* posiciona o indicador de posicao do arquivo no inicio da FAT */
	fseek (fst [fsh].file, DIRECTORY_BLOCKS*BLOCO, SEEK_SET);

	/* carrega a FAT */
	fread (fst [fsh].fat, fst [fsh].fs*sizeof (uint32_t), 1, fst [fsh].file);

	/* posiciona o indicador de posicao do arquivo no inicio do primeiro bloco de dados */
	fseek (fst [fsh].file, (DIRECTORY_BLOCKS + fst [fsh].fb + 1)*BLOCO, SEEK_SET);

	return fsh;
}

indice_arquivo_t vopen (indice_fs_t fs, char * nome,  int acesso, int version)
{
	/* verifica se fs e valido e se e possivel abrir mais um arquivo */
	if ( !( it_is_open (fs) && open_files < MAX_OPEN_FILES ) )
		return FALHA;

	fcb_t *fcb;
	indice_arquivo_t fh;
        
        /* procura pelo arquivo no diretorio */	
	if ( (fcb = search_file (fs, nome)) == NULL ) {

		//puts ("O FCB do arquivo não foi encontrado.");
                
                /* se o arquivo nao existe, ele so sera criado se o acesso */
                /* nao for apenas de leitura e se ha diretorio disponivel  */		
		if ( acesso == LEITURA || !(fcb = search_directory (fs)) )
                        return FALHA;

		//puts ("Há um diretório disponível para criar o arquivo.");
                
		strcpy (fcb->name, nome); /* preenche o campo dos diretorio */
		set_fcb (fcb, 0);
		fcb->nversions = 1;

		fh = get_a_file_handle (); /* obtem um indice para a tab. de arq. abertos */

                oft [fh].version = 0; /* primeira versao sendo aberta */
	}
	/* se o arquivo existe e o acesso for ESCRITA ou LEITURA/ESCRITA */
	else if ( acesso != LEITURA ) {
                /* primeiro e preciso verificar se o numero da versao e valido; */ 
		/* depois se o limite de versoes nao foi atingido; */
		/* se nao foi ainda, e feita a tentativa de criar outra versao               */
		if ( /* !(version >= 0 && version < fcb->nversions) || */ fcb->nversions == MAXVERSIONS
			       || !create_another_version (fs, fcb, fcb->nversions - 1) )
			return FALHA;

		fh = get_a_file_handle (); /* obtem um indice para a tab. de arq. abertos */

		oft [fh].version = fcb->nversions - 1; /* uma nova versao do arquivo foi criada */
               
		oft [fh].fcb->last_ace [oft [fh].version] = time (NULL); /* registra ultimo acesso */
	}
	/* se o acesso for de LEITURA */
	else {
		/* verifica se o numero de versao e valido */ 
		if ( !(version >= 0 && version < fcb->nversions) )
			return FALHA;

                fh = get_a_file_handle (); /* obtem um indice para a tab. de arq. abertos */

		oft [fh].version = version;

	        oft [fh].fcb->last_ace [oft [fh].version] = time (NULL); /* registra ultimo acesso */	
        }

	oft [fh].owner = fs;     /* preenche a entrada da tabela com os valores apropriados */
	oft [fh].occupied = YES;
	oft [fh].seek = 0; 
        oft [fh].acess = acesso;
        oft [fh].fcb = fcb;	
	
	++open_files; /* mais um arquivo aberto */

	//puts ("FCB do arquivo aberto:");
	//printf ("Nome: %s\n", oft [fh].fcb->name);
	//printf ("Primeiro Bloco: %d\n", oft [fh].fcb->first_block [version]);
	//printf ("Tamanho: %d\n", oft [fh].fcb->size [version]);
	//printf ("Versões: %d\n\n", oft [fh].fcb->nversions);

	// puts ("Entrada na TAA:");
        //printf ("Versão: %d\n", oft [fh].version);
        //printf ("Seek: %d\n\n", oft [fh].seek);

	return fh;
} 

uint32_t vread (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer)
{
	uint32_t i;
	uint32_t index = get_index ( 

			arquivo,

			(oft [arquivo].seek / BLOCO) + 1
		       	
			); /* indice do bloco onde esta o seek */

	fseek (fst [oft [arquivo].owner].file,
		       	( ( DIRECTORY_BLOCKS + fst [oft [arquivo].owner].fb + index)*BLOCO ) + oft [arquivo].seek,
		       	SEEK_SET); /* o indicador de posicao do arquivo e posto no ponto exato onde esta o seek */

	//printf ("Tamanho arquivo: %d\n", oft [arquivo].fcb->size [oft [arquivo].version]);

        /* enquanto houver bytes para ler */
	for (i = 0; (i < tamanho) && 
			(oft [arquivo].seek < oft [arquivo].fcb->size [oft [arquivo].version]);
		       	++i) {
                /* index sera atualizada quando eu tiver q continuar a ler em outro bloco */
		if ( oft [arquivo].seek != 0 && oft [arquivo].seek % BLOCO == 0 ) {
			index = fst [oft [arquivo].owner].fat [index];
                        fseek (fst [oft [arquivo].owner].file,
				       	(DIRECTORY_BLOCKS + fst [oft [arquivo].owner].fb + index)*BLOCO, 
					SEEK_SET); 
		}
                
		/* le um byte */
                fread (&buffer [i], 1, 1, fst [oft [arquivo].owner].file);
		/* incrementa o seek */
		++(oft [arquivo].seek);
	}
        
	oft [arquivo].fcb->last_ace [oft [arquivo].version] = time (NULL); /* registra ultimo acesso */
        //puts ("Chegay aki!!!"); 
	return i; /* retorna o numero de bytes lidos (= ao numero de iteracoes do laco for) */
}

int vwrite (indice_arquivo_t arquivo, uint32_t tamanho, char *buffer)
{
	//printf ("File Handle do arquivo: %d\n", arquivo);
	//printf ("Quanto eu quero escrever: %d\n", tamanho);
	//printf ("O que eu quero escrever: %s\n", buffer);
	//printf ("Versão: %d\n", oft [arquivo].version);
	//printf ("Seek: %d\n", oft [arquivo].seek);

	if (oft [arquivo].acess == LEITURA /* || strlen (buffer) != tamanho */)
		return FALHA;

	/* calcula a capacidade em bytes do arquivo */
        uint32_t c = ( BLOCO*( ( oft [arquivo].fcb->size [oft [arquivo].version] % BLOCO ) ?
			       	( oft [arquivo].fcb->size [oft [arquivo].version] / BLOCO) + 1
		: oft [arquivo].fcb->size [oft [arquivo].version] / BLOCO ) ) - oft [arquivo].seek;
        
	//printf ("Capacidade do arquivo: %d\n", c);

	/* se essa capacidade for menor do que a quantidade de bytes que eu */
	/* quero escrever, aloco mais blocos; se nao for possivel alocar ma */
	/* is blocos, a funcao retorna falha                                */
	if ( c < tamanho && !alloc_blocks (arquivo, tamanho - c) ) 
	        return FALHA;

	//printf ("Indíce do primeiro bloco: %d\n", oft [arquivo].fcb->first_block [oft [arquivo].version]);

       	uint32_t i;
	uint32_t index = get_index ( 

			arquivo,

		(oft [arquivo].seek / BLOCO) + 1   

			); /* indice do bloco onde esta o seek */

	//printf ("Indice do bloco onde esta o seek: %d\n", index);

	fseek (fst [oft [arquivo].owner].file,
		       	( ( DIRECTORY_BLOCKS + fst [oft [arquivo].owner].fb + index)*BLOCO ) + oft [arquivo].seek,
		       	SEEK_SET); /* o indicador de posicao do arquivo e posto no ponto exato onde esta o seek */
        /* enquanto houver bytes para escrever */
	for (i = 0; i < tamanho; ++i) {
                /* index sera atualizada quando eu tiver q continuar a escrever em outro bloco */
		if ( oft [arquivo].seek != 0 && oft [arquivo].seek % BLOCO == 0 ) {
			index = fst [oft [arquivo].owner].fat [index];
                        fseek (fst [oft [arquivo].owner].file,
				       	(DIRECTORY_BLOCKS + fst [oft [arquivo].owner].fb + index)*BLOCO, 
					SEEK_SET); 
		}
                
		/* escreve um byte */
                fwrite (&buffer [i], 1, 1, fst [oft [arquivo].owner].file);
		/* incrementa o seek */
		++(oft [arquivo].seek);
	}

	oft [arquivo].fcb->last_mod [oft [arquivo].version] = time (NULL); /* registra ultima mod. e acesso */
	oft [arquivo].fcb->last_ace [oft [arquivo].version] = time (NULL);

	oft [arquivo].fcb->size [oft [arquivo].version] =
	       	( oft [arquivo].seek > oft [arquivo].fcb->size [oft [arquivo].version]) ?
		oft [arquivo].seek :
	       	oft [arquivo].fcb->size [oft [arquivo].version]; /* atualiza o tamanho do arquivo */

        // puts ("Conteúdo gravado:");
	// puts (buffer);
        // printf ("Versão: %d\n", oft [arquivo].version);
        // printf ("Primeiro Bloco: %d\n", oft [fh].fcb->first_block [version]);
        // printf ("Tamanho: %d\n", oft [fh].fcb->size [version]);
        // printf ("Versões: %d\n\n", oft [fh].fcb->nversions);

	return SUCESSO;
}

int vdelete (indice_arquivo_t arquivo) 
{
	/* verifica se o arquivo esta aberto */
	if ( oft [arquivo].occupied == NO )
		return FALHA;
        
        indice_fs_t fs;
	char name [256];

	fs = oft [arquivo].owner;               /* pega o SAs a q o arq. pertence e seu nome */
	strcpy (name, oft [arquivo].fcb->name);
        
	oft [arquivo].occupied = NO; /* fecha o arquivo desocupando sua entrada na TAA */  
	--open_files;

	int i;
        
	/* as entradas na TAA das outras versoes tbm sao desocupadas */
	for (i = 0; i < MAX_OPEN_FILES; ++i)
		if ( oft [i].owner == fs &&
			       	!strcmp (oft [i].fcb->name, name) ) {
			oft [i].occupied = NO;
			--open_files;
		}


        /* fechado o arq. e todas as suas versoes, hora de elmina-lo do SAs */
	fcb_t *fcb = search_file (fs, name);
        
	/* devolve os blocos de cada versao para o SAs */
        for (i = 0; i < fcb->nversions; ++i) 
		free_blocks (fs, fcb->first_block [i]);
        
	/* apaga a entrada do arq. no dir. apagando o seu nome (colocando tudo pra zero) */
	memset (fcb->name, '\0', 256);
        
	return SUCESSO;
}

int vclose (indice_arquivo_t arquivo)
{
	/* verifica se o arquivo esta aberto */
	if ( oft [arquivo].occupied == NO )
		return FALHA;
        
	oft [arquivo].occupied = NO; /* fecha o arquivo desocupando sua entrada na TAA */  
	--open_files;
        
	return SUCESSO;
}

int vseek (indice_arquivo_t arquivo, uint32_t seek)
{
	/* verifica se o arquivo esta aberto */
	/* ou se o seek passado e valido     */
        if ( oft [arquivo].occupied == NO ||
	  seek > oft [arquivo].fcb->size [oft [arquivo].version] )
                return FALHA;
        
	oft [arquivo].seek = seek;

	//puts ("Aki tbm!!!");

	return SUCESSO;
}

time_t vcreation (indice_arquivo_t arquivo, int versao)
{
	return oft [arquivo].fcb->tcreation [versao];
}

time_t vaccessed (indice_arquivo_t arquivo, int versao)
{
	return oft [arquivo].fcb->last_ace [versao];
}

time_t vlast_modified (indice_arquivo_t arquivo, int versao)
{
	return oft [arquivo].fcb->last_mod [versao];
}

int vclosefs (indice_fs_t fs)
{
	/* verifica se o SAs esta aberto */
        if ( fst [fs].occupied == NO )
                return FALHA;

	/* grava o diretorio */
        fwrite (fst [fs].directory, 256*sizeof (fcb_t), 1, fst [fs].file);

	/* grava o tamanho da FAT */
        fwrite (&fst [fs].fs, sizeof (uint32_t), 1, fst [fs].file);

        /* grava o numero de blocos da FAT */
        fwrite (&fst [fs].fb, sizeof (uint32_t), 1, fst [fs].file);

        /* grava o numero de blocos de dados livres */
        fwrite (&fst [fs].fblocks, sizeof (uint32_t), 1, fst [fs].file);

	/* posiciona o indicador de posicao do arquivo no inicio da FAT */
        fseek (fst [fs].file, DIRECTORY_BLOCKS*BLOCO, SEEK_SET);

        /* grava a FAT */
        fwrite (fst [fs].fat, fst [fs].fs*sizeof (uint32_t), 1, fst [fs].file);

	fst [fs].occupied = NO; /* aquela entrada da TSAA nao esta mais sendo usada */

	--open_fs;
        
	return SUCESSO;
}

int there_is_a_file_named (char *arquivo)
{
        FILE *f;

        if ( (f = fopen (arquivo, "r")) == NULL ) 
		return FALHA;
        
	fclose (f);

	return SUCESSO;
}

indice_fs_t search_for_fst_free_entry ()
{
	indice_fs_t i;

	for (i = 1; i < MAX_OPEN_FS; ++i)
		if ( fst [i].occupied == NO )
			return i;

	return FALHA;
}

int it_is_open (indice_fs_t fs)
{
	return (fst [fs].occupied == YES) ? SUCESSO : FALHA;
}

fcb_t * search_file (indice_fs_t fs, char *n)
{
        int i;

        for (i = 0; i < 256; ++i)
                if ( !strcmp (fst [fs].directory [i].name, n) )
                        return &fst [fs].directory [i];

        return NULL;
}

fcb_t * search_directory (indice_fs_t fs)
{
        int i;

        for (i = 0; i < 256; ++i)
                if ( !strlen (fst [fs].directory [i].name) )
                        return &fst [fs].directory [i];

        return NULL;
}

void set_fcb (fcb_t *fcb, int v)
{
        fcb->tcreation [v] = time (NULL);
        fcb->last_mod [v] = time (NULL);
        fcb->last_ace [v] = time (NULL);
        fcb->first_block [v] = 0;
        fcb->size [v] = 0;
}

indice_arquivo_t get_a_file_handle ()
{
	indice_arquivo_t i;

        for (i = 1; i < MAX_OPEN_FILES; ++i)
                if ( oft [i].occupied == NO )
                        return i;

        return FALHA;
}	

fcb_t * create_another_version (indice_fs_t fs, fcb_t *fcb, int v)
{
	uint32_t ovb = (fcb->size [v] % BLOCO) ? (fcb->size [v] / BLOCO) + 1
		: (fcb->size [v] / BLOCO);

	if (ovb > fst [fs].fblocks)
		return NULL;

        set_fcb (fcb, fcb->nversions);

        uint32_t i;
        uint32_t b [1024];

        for (i = 0; i < ovb; ++i)
		give_a_free_block (fs, get_a_free_block (fs), fcb, fcb->nversions);
        
	uint32_t ovi = fcb->first_block [v];
	uint32_t nvi = fcb->first_block [fcb->nversions];

        for (i = 0; i < ovb; ++i) {
		read_a_block (fs, b, ovi);
		write_a_block (fs, b, nvi);
                
		ovi = fst [fs].fat [ovi];
		nvi = fst [fs].fat [nvi];
	}

	fcb->last_ace [v] = time (NULL); /* registra ultimo acesso */
        
	fcb->size [fcb->nversions] = fcb->size [v];
	++(fcb->nversions);

	return fcb;
}

int get_a_free_block (indice_fs_t fs)
{
	uint32_t fblock = fst [fs].fat [0];
	fst [fs].fat [0] = fst [fs].fat [fblock];
	fst [fs].fat [fblock] = 0;
        
	--(fst [fs].fblocks);

	return fblock;
}

void give_a_block_back (indice_fs_t fs, uint32_t index)
{
	fst [fs].fat [index] = fst [fs].fat [0];
	fst [fs].fat [0] = index;

	++(fst [fs].fblocks);
}

void give_a_free_block (indice_fs_t fs, uint32_t index, fcb_t *fcb, int v)
{
	if (fcb->first_block [v] == 0)
		fcb->first_block [v] = index;
	else {
		uint32_t obi = fcb->first_block [v];
		uint32_t cbi;

		while ( (cbi = fst [fs].fat [obi] ) != 0 ) obi = cbi;

                fst [fs].fat [obi] = index;
	}
}

void read_a_block (indice_fs_t fs, uint32_t *b, uint32_t index)
{
	fseek (fst [fs].file, (DIRECTORY_BLOCKS + fst [fs].fb + index)*BLOCO, SEEK_SET);
	fread (b, BLOCO, 1, fst [fs].file);
}

void write_a_block (indice_fs_t fs, uint32_t *b, uint32_t index) 
{
	fseek (fst [fs].file, (DIRECTORY_BLOCKS + fst [fs].fb + index)*BLOCO, SEEK_SET);
        fwrite (b, BLOCO, 1, fst [fs].file);
}

int alloc_blocks (indice_arquivo_t fh, uint32_t n)
{
	uint32_t nb = ( n % BLOCO ) ? ( n / BLOCO ) + 1
		: ( n / BLOCO);

	if (nb > fst [oft [fh].owner].fblocks)
		return FALHA;

        uint32_t i;

        for (i = 0; i < nb; ++i)
		give_a_free_block (oft [fh].owner, get_a_free_block (oft [fh].owner),
			       	oft [fh].fcb, oft [fh].version);

	return SUCESSO;
}

uint32_t get_index (indice_arquivo_t fh, uint32_t x)
{
	uint32_t i;
        uint32_t index = oft [fh].fcb->first_block [oft [fh].version];

	for (i = 1; i != x; index = fst [oft [fh].owner].fat [index], ++i);
        
	return index;
}

void free_blocks (indice_fs_t fs, uint32_t fb)
{
	uint32_t ai = fb;
        uint32_t ni = fst [fs].fat [fb];

	while ( ai != 0 ) {
		give_a_block_back (fs, ai);
		ai = ni;
		ni = fst [fs].fat [ni];
	}
}

