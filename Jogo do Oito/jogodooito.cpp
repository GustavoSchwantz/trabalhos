#include "jogodooito.h"
#include <iostream>

JogoDoOito::JogoDoOito ()
    :main_box (Gtk::ORIENTATION_VERTICAL),
    opcao ("Selecione um algoritmo de busca"),
    estados ("Informe o estado inicial e o estado meta")
{
	set_title ("Jogo do Oito");
	set_border_width (20);

 	add (main_box);

 	opcao.add (radiobuttons);
 	estados.add (entradas);

	main_box.pack_start (opcao);
	main_box.pack_start (estados);

 	show_all_children ();
}   

JogoDoOito::~JogoDoOito ()
{

}