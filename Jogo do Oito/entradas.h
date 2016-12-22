#include <gtkmm/grid.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <array>

class Entradas : public Gtk::Box {
public:
	Entradas ();
	~Entradas ();

private:
    std::array<Gtk::Entry, 9> inicial, meta;
    Gtk::Grid grid0, grid1;
};