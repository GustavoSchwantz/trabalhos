#include "radiobuttonbox.h"
#include <iostream>

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

    busca_largura.signal_clicked ().connect (sigc::mem_fun (*this, &RadioButtonBox::on_button_selected));
    busca_profundidade.signal_clicked ().connect (sigc::mem_fun (*this, &RadioButtonBox::on_button_selected));
    a_estrela.signal_clicked ().connect (sigc::mem_fun (*this, &RadioButtonBox::on_button_selected));
    hill_clibing.signal_clicked ().connect (sigc::mem_fun (*this, &RadioButtonBox::on_button_selected));
    
    pack_start (busca_largura);
    pack_start (busca_profundidade);
    pack_start (a_estrela);
    pack_start (hill_clibing);
}    

RadioButtonBox::~RadioButtonBox ()
{
	
}

void RadioButtonBox::on_button_selected ()
{
    if (busca_largura.get_active ()) 
        algoritmo = Algoritmo::largura;
    else if (busca_profundidade.get_active ())
        algoritmo = Algoritmo::profundidade;
    else if (a_estrela.get_active ())
        algoritmo = Algoritmo::estrela;
    else
        algoritmo = Algoritmo::hill;
}

Algoritmo RadioButtonBox::get_algoritmo ()
{
    return algoritmo;
}