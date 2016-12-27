#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>

class Informacoes : public Gtk::Box {
public:
	Informacoes (const std::string& f);
	~Informacoes ();

private:
	Gtk::Label frase;
	Gtk::Entry valor;
};