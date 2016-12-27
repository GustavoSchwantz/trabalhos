#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <vector>
#include <utility>
#include "radiobuttonbox.h"
#include "entradas.h"
#include "informacoes.h"
#include "caminho.h"


class JogoDoOito : public Gtk::Window {
public:
	JogoDoOito ();
	~JogoDoOito ();

private:
	/*bool busca_em_largura ();
	bool e_solucionavel (const std::array<int, 9>& e0,
		const std::array<int, 9>& e1);
	bool e_meta (const std::array<int, 9>& e0,
	    const std::array<int, 9>& e1);
	std::array<int, 9> inverte_array (const std::array<int, 9>& arr);
	std::vector<Node*> expande (Node *n);
	int cade_o_branco (const std::array<int, 9>& e);
	Node* cria_nodo (const std::array<int, 9>& e, int i, int j, Node *n);
	void insere_todos (const std::vector<Node*>& v0,
	    std::vector<Node*>& v1);
	void aperta_botao ();*/

    Gtk::Box main_box;
    RadioButtonBox radiobuttons;
    Gtk::Frame opcao, estados;
    Entradas entradas;
    Gtk::Button iniciar;

    Algoritmo algoritmo;
    Informacoes info0, info1;
    Caminho caminho;

    //std::vector<Node*> todos_os_nos;
    //int n_estados_testados;
    //int n_estados_solucao;
};