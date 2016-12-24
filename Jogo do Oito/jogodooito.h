#include <gtkmm/window.h>
//#include <gtkmm/radiobutton.h>
//#include <gtkmm/entry.h>
//#include <gtkmm/grid.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <vector>
#include "radiobuttonbox.h"
#include "entradas.h"
#include "informacoes.h"
#include "caminho.h"
#include "node.h"


class JogoDoOito : public Gtk::Window {
public:
	JogoDoOito ();
	~JogoDoOito ();

protected:
	bool busca_em_largura ();
	bool e_meta (const std::array<int, 9>& e0,
	    const std::array<int, 9> e1);

    Gtk::Box main_box;
    RadioButtonBox radiobuttons;
    Gtk::Frame opcao, estados;
    Entradas entradas;

    Algoritmo algoritmo;
    Informacoes info0, info1;
    Caminho caminho;
};