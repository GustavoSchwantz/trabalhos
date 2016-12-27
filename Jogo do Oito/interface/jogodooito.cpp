#include "jogodooito.h"
#include <iostream>

JogoDoOito::JogoDoOito ()
    :main_box (Gtk::ORIENTATION_VERTICAL),
    opcao ("Selecione um algoritmo de busca"),
    estados ("Informe o estado inicial e o estado meta"),
    iniciar ("Iniciar Busca"),
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
	main_box.pack_start (iniciar);
	main_box.pack_start (info0);
	main_box.pack_start (info1);
	main_box.pack_start (caminho);

 	show_all_children ();
}   

JogoDoOito::~JogoDoOito ()
{
	
}

/*void JogoDoOito::aperta_botao ()
{
	if (!busca_em_largura ())
		std::cout << "Não é possível efetuar a busca" << std::endl;
	else
		for (auto it = todos_os_nos.begin (); it != todos_os_nos.end (); ++it) {
			std::cout << (*it)->get_estado()[0] << " "
			<< (*it)->get_estado()[1] << " "
			<< (*it)->get_estado()[2] << " "
		    << (*it)->get_estado()[3] << " "
			<< (*it)->get_estado()[4] << " "
			<< (*it)->get_estado()[5] << " "
			<< (*it)->get_estado()[6] << " "
			<< (*it)->get_estado()[7] << " "
			<< (*it)->get_estado()[8] << std::endl;

			delete (*it);
		}
}

bool JogoDoOito::busca_em_largura ()
{
	std::array<int, 9> est_inicial = entradas.get_inicial ();
	std::array<int, 9> est_meta = entradas.get_meta ();

	if (!e_solucionavel (est_inicial, est_meta))
		return false;

	//std::cout << "apos chamar e_solucionavel" << std::endl;

    Node *nodo = new Node (est_inicial, nullptr);
    todos_os_nos.push_back (nodo);

	for (std::vector<Node*> nodos; !e_meta (nodo->get_estado (), est_meta); ) {
		insere_todos (expande (nodo), nodos);
		nodo = nodos.back ();
		nodos.pop_back ();
	}

	return true;
}

void JogoDoOito::insere_todos (const std::vector<Node*>& v0,
	    std::vector<Node*>& v1)
{
	v1.insert (v1.begin (), v0.begin (), v0.end ());
}


int JogoDoOito::cade_o_branco (const std::array<int, 9>& e)
{
	for (int i = 0; i != e.size (); ++i)
		if (!e[i])
			return i;
}

Node* JogoDoOito::cria_nodo (const std::array<int, 9>& e, int i, int j, Node *n)
{
	std::array<int, 9> n_estado = e;

	std::swap (n_estado[i], n_estado[j]);

	Node *novo_nodo = new Node (n_estado, n);
	todos_os_nos.push_back (novo_nodo);

	return novo_nodo;
}

std::vector<Node*> JogoDoOito::expande (Node *n)
{
	std::vector<Node*> filhos;
	std::array<int, 9> estado;
	int indice;

    estado = n->get_estado ();
	indice = cade_o_branco (estado);
	Node *avo = n->get_pai ();
    

    switch (indice) {
    	case 0:
    	{
    		if (!avo) {
    			filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    		}
    		else {
    			if (cade_o_branco (avo->get_estado ()) == 1)
    				filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			else
    				filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    		}
        }   
        
    	return filhos;
        
        case 1:
        {
        	if (!avo) {
    			filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    		}
    		else {
    			if (cade_o_branco (avo->get_estado ()) == 0) {
    				filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			}
    			else if (cade_o_branco (avo->get_estado ()) == 2) {
    				filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			}
    			else {
    				filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			}
    		}
        } 
    	
    	return filhos;

    	case 2:
        {
        	if (!avo) {
    			filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    		}
    		else {
    			if (cade_o_branco (avo->get_estado ()) == 1)
    				filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			else
    				filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    		}
    	    
        }   
        
    	return filhos;

    	case 3:
    	{
    		if (!avo) {
    			filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    		}
    		else {
    			if (cade_o_branco (avo->get_estado ()) == 0) {
    				filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			}
    			else if (cade_o_branco (avo->get_estado ()) == 4) {
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			}
    			else {
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			}
    		}
    	}

    	return filhos;

    	case 4:
    	{
    		if (!avo) {
    			filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    		}
    		else {
    			if (cade_o_branco (avo->get_estado ()) == 1) {
    				filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    				filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			}
    			else if (cade_o_branco (avo->get_estado ()) == 3) {
    				filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			}
    			else if (cade_o_branco (avo->get_estado ()) == 5) {
    				filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			}
    			else {
    			    filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			}
    		}
    	}

    	return filhos;

    	case 5:
    	{
    		if (!avo) {
    			filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    		}
    		else {
    			if (cade_o_branco (avo->get_estado ()) == 3) {
    				filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			}
    			else if (cade_o_branco (avo->get_estado ()) == 8) {
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			}
    			else {
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 3, n));
    			}
    		}
    	}

    	return filhos;

    	case 6:
        {
        	if (!avo) {
    			filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    		}
    		else {
    			if (cade_o_branco (avo->get_estado ()) == 7)
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			else
    				filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    		}
        }   
        
    	return filhos;

    	case 7:
    	{
    		if (!avo) {
    			filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    		}
    		else {
    			if (cade_o_branco (avo->get_estado ()) == 4) {
    				filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			}
    			else if (cade_o_branco (avo->get_estado ()) == 8) {
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			}
    			else {
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			    filhos.push_back (cria_nodo (estado, indice, indice + 1, n));
    			}
    		}
    	}

    	return filhos;

    	case 8:
        {
        	if (!avo) {
    			filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    			filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    		}
    		else {
    			if (cade_o_branco (avo->get_estado ()) == 7)
    				filhos.push_back (cria_nodo (estado, indice, indice - 3, n));
    			else
    				filhos.push_back (cria_nodo (estado, indice, indice - 1, n));
    		}
        }   
        
    	return filhos;
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

	//std::cout << "apos inverte_array" << std::endl;

	int inversoes = 0;

	for (int i = 0; i < e0.size () - 1; ++i)
		for (int j = i + 1; j < e1.size (); ++j)
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
*/