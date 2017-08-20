#include <stdio.h>
#include <stdlib.h>
#include "roteador.h"

/* recebe um pacote, a tabela de roteamento, o tamanho da 
 * tabela roteamento e devolve o numero do enlace correspondente 
 * a aquele pacote
 */
int get_route (uint32_t p, entrada *r, int nr);
/* recebe o numero de bits da parte de rede e devolve a mascara
 * correspondente
 */
uint32_t get_mask (int n);

uint32_t* roteamento (entrada * rotas, int num_rotas, uint32_t * pacotes, 
	int num_pacotes, int num_enlaces) 
{
	uint32_t *list; /* lista de enlaces de saida */

	if ( (list = (uint32_t*) calloc (num_enlaces + 1, sizeof (uint32_t))) == NULL ) {
		printf("Enable to allocate memory.\n");
		exit (1);
	}

	int i;
    
    /* para cada pacote, pega o enlace para onde ele deve ir */
	for (i = 0; i < num_pacotes; ++i) {

		int e = get_route (pacotes[i], rotas, num_rotas);
        
        /* contabiliza o enlace */ 
		list[e]++;
	}

	return list;
}	

int get_route (uint32_t p, entrada *r, int nr)
{
	int e = 0; /* enlace da entrada de maior prefixo */
    int s = 0; /* bits da parte de rede da entrada de maior prefixo */
    int i;
    
    /* compara um pacote com cada entrada da tabela */
    for (i = 0; i < nr; ++i) {
        
        /* pega uma mascara */
    	uint32_t m = get_mask (r[i].mascara);
        
        /* se o resultado da AND bit a bit do endereco do pacote
         * com a mascara de rede for igual ao resultado da AND bit
         * a bit do endereco com a mascara e essa mascara for maior 
         * do q a ultima, salva o tamanho da mascara e o enlace
         */ 
    	if ( (p & m) == (r[i].endereco & m) && r[i].mascara > s) {
    		s = r[i].mascara;
    		e = r[i].enlace;
    	}
    }

    return e;
}

uint32_t get_mask (int n)
{
	uint32_t m = 0;

	m = ~m;

	m = m << (32 - n);

	return m;
}

