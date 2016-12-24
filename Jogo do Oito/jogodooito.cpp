#include "jogodooito.h"
#include <iostream>

JogoDoOito::JogoDoOito ()
    :main_box (Gtk::ORIENTATION_VERTICAL),
    opcao ("Selecione um algoritmo de busca"),
    estados ("Informe o estado inicial e o estado meta"),
    info0 ("Número de Estados Testados: "),
    info1 ("Número de Estados para Solução: ")
{
	set_title ("Quebra-Cabeça do Oito");
	set_border_width (15);

 	add (main_box);

 	opcao.add (radiobuttons);
 	estados.add (entradas);

 	opcao.set_border_width (5);
 	estados.set_border_width (5);

	main_box.pack_start (opcao);
	main_box.pack_start (estados);
	main_box.pack_start (info0);
	main_box.pack_start (info1);
	main_box.pack_start (caminho);

 	show_all_children ();
}   

JogoDoOito::~JogoDoOito ()
{

}

bool JogoDoOito::busca_em_largura ()
{
	std::vector<Node*> nodes;
	std::array<int, 9> meta;

	nodes.push_back (new Node (entradas.get_inicial (), nullptr));
	meta = entradas.get_meta ();

	for ( ; ; ) {
		if (!nodes.size ()) { return false; }
		Node *node = nodes.back (); nodes.pop_back ();
        if (e_meta (node->get_estado (), meta))
        	return true;
        //nodes = insere_todos (expandir (node), nodes);
	}

}

bool e_meta (const std::array<int, 9>& e0,
	    const std::array<int, 9> e1)
{
	for (int i = 0, j = 0; i != e0.size (); ++i, ++j)
		if (e0[i] != e1[j])
			return false;

	return true;	
}
