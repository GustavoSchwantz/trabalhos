#include <gtkmm/window.h>
//#include <gtkmm/radiobutton.h>
//#include <gtkmm/entry.h>
//#include <gtkmm/grid.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include "radiobuttonbox.h"
#include "entradas.h"

class JogoDoOito : public Gtk::Window {
public:
	JogoDoOito ();
	~JogoDoOito ();

protected:
    Gtk::Box main_box;
    RadioButtonBox radiobuttons;
    Gtk::Frame opcao, estados;
    Entradas entradas;
};