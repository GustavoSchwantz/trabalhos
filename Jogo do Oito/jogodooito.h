#include <gtkmm/window.h>
//#include <gtkmm/radiobutton.h>
//#include <gtkmm/entry.h>
//#include <gtkmm/grid.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include "radiobuttonbox.h"
#include "entradas.h"
#include "informacoes.h"
#include "caminho.h"


class JogoDoOito : public Gtk::Window {
public:
	JogoDoOito ();
	~JogoDoOito ();

protected:
    Gtk::Box main_box;
    RadioButtonBox radiobuttons;
    Gtk::Frame opcao, estados;
    Entradas entradas;

    Algoritmo algoritmo;
    Informacoes info0, info1;
    Caminho caminho;
};