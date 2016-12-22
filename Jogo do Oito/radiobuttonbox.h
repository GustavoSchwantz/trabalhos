#include <gtkmm/box.h>
#include <gtkmm/radiobutton.h>

class RadioButtonBox : public Gtk::Box {
public:
	RadioButtonBox ();
	~RadioButtonBox ();

private:
	Gtk::RadioButton busca_largura, busca_profundidade,
	    a_estrela, hill_clibing;
};