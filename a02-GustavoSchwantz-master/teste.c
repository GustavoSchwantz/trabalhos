#include "memvirt.h"
#include "simpletest.h"

#define WS(a, b, c) \
if (a){ \
	isEqual(a->avg_ws, b, c); \
} \
else isNotNull(a, c);

#define PFRATE(a, b, c) \
if (a){ \
	isNear(a->total_pf_rate, b, c); \
} \
else isNotNull(a, c);

void tzero1 ()
{
	WHEN("eu tenho apenas um processo, 4 frames e um intervalo igual a 20");
	
	struct result *r = memvirt (1, 4, "t01.txt", 20);

	THEN("esse único processo vai ter 10 referências");
	isEqual(r->refs[0], 10, 1); 
	
	THEN("seu número de PF vai ser 4");
	isEqual(r->pfs[0], 4, 1);
	
	THEN("sua taxa de PF vai ser 40%");
	isEqual(r->pf_rate[0], 0, 1);
	
	THEN("o ws vai ser zero");
	isEqual(r->avg_ws, 0, 1);
	
	THEN("a taxa de PF média vai ser 40%");
	isEqual(r->total_pf_rate, 0, 1);
	
	free (r);    
}

void tzero2 ()
{
	WHEN("eu tenho apenas 3 processos, 7 frames e um intervalo igual a 4");
	
	struct result *r = memvirt (3, 7, "t02.txt", 4);

	THEN("o primeiro processo irá ter 3 referências");
	isEqual(r->refs[0], 3, 1); 
	
	THEN("o segundo processo irá ter 2 referências");
	isEqual(r->pfs[1], 2, 1);
	
	THEN("o terçeiro processo irá ter 2 referências");
	isEqual(r->pfs[2], 2, 1);
	
	THEN("o número de PF do primeiro irá ser");
	isEqual(r->pfs[0], 2, 1);
	
	free (r);    
}

void tzero3 ()
{
	struct result * r;

	WHEN ("dois processos, cinco frames e um intervalo igual de quatro");
	
	r = memvirt (2, 5,"t03.txt", 4);
	
	THEN ("o primero processo irá ter 10 referências");
	isEqual(r->refs[0], 10, 1);
	
	THEN ("o segundo processo irá ter 2 referências");
	isEqual(r->refs[1], 2, 1);

	WS(r, 2, 1);
	PFRATE(r, .9, 1);
	if(r)
		free(r);
}

int main (int argc, char const *argv[])
{
    DESCRIBE("Testes do simulador de memória virtual");

	 tzero1 ();
	 tzero2 ();
	 tzero3 ();
	 GRADEME(); 

	 if (grade==maxgrade)	
	     return 0;
	 else return grade;

	 return 0;     
}