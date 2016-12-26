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
	std::array<int, 9> est_inicial = entradas.get_inicial ();
	std::array<int, 9> est_meta = entradas.get_meta ();

	if (!e_solucionavel (est_inicial, est_meta))
		return false;

    Node *nodo = new Node (est_inicial, nullptr);
    todos_os_nos.push_back (nodo);

	for (std::vector<Node*> nodos; !e_meta (nodo, est_meta); ) {
		nodos = insere_todos (expande (nodo), nodos);
		nodo = nodos.back ();
		nodos.pop_back ();
	}

	return true;
}

std::vector<Node*> JogoDoOito::expande (Node *n)
{
	std::vector<Node*> filhos;
    

    switch (cade_o_branco (n->get_estado ())) {
    	case 0: 
        
    	break;
        
        case 1:

    	break;

    	case 2:

    	break;

    	case 3:

    	break;

    	case 4:

    	break;

    	case 5:

    	break;

    	case 6:

    	break;

    	case 7:

    	break;

    	case 8:

    	break;
    }
}

std::array<int, 9> JogoDoOito::inverte_array (const std::array<int, 9>& arr)
{
	std::array<int, 9> novo_array;

	for (int i = 0; i < arr.size (); ++i) 
		novo_array[arr[i]] = i;

	return novo_array;
}

bool JogoDoOito::e_solucionavel (const std::array<int, 9>& e0,
		const std::array<int, 9>& e1)
{
	std::array<int, 9> array_aux = inverte_array (e1);

	int inversoes = 0;

	for (int i = 0; i < e0.size () - 1; ++i)
		for (int j = i + 1; i < e1.size (); ++j)
            if (e0[i] && e1[j] && array_aux[e0[i]] > array_aux[e0[j]])
            	++inversoes;

    if (inversoes % 2 == 0)
        return true;

    return false;            
}

bool JogoDoOito::e_meta (const std::array<int, 9>& e0,
	    const std::array<int, 9>& e1)
{
	for (int i = 0, j = 0; i != e0.size (); ++i, ++j)
		if (e0[i] != e1[j])
			return false;

	return true;	
}
