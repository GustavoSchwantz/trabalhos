#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/scrolledwindow.h>

class Caminho : public Gtk::Box {
public:
	Caminho ();
	~Caminho ();
private:
	Gtk::Label titulo;
	Gtk::ScrolledWindow caminho;
	Gtk::Entry entry;
};