#include <gtkmm/box.h>
#include <gtkmm/radiobutton.h>
#include "enum.h"

class RadioButtonBox : public Gtk::Box {
public:
	RadioButtonBox ();
	~RadioButtonBox ();

	Algoritmo get_algoritmo ();

private:
    void on_button_selected ();

	Gtk::RadioButton busca_largura, busca_profundidade,
	    a_estrela, hill_clibing;
    Algoritmo algoritmo;
};