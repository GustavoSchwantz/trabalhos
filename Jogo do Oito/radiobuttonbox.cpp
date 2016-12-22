#include "radiobuttonbox.h"

RadioButtonBox::RadioButtonBox ()
    :busca_largura ("Busca em Largura"),
    busca_profundidade ("Busca em Profundidade"),
    a_estrela ("A*"),
    hill_clibing ("Hill Clibing")
{
	set_border_width (10);
	
	busca_profundidade.join_group (busca_largura);
	a_estrela.join_group (busca_largura);
	hill_clibing.join_group (busca_largura);
    
    pack_start (busca_largura);
    pack_start (busca_profundidade);
    pack_start (a_estrela);
    pack_start (hill_clibing);
}    

RadioButtonBox::~RadioButtonBox ()
{
	
}