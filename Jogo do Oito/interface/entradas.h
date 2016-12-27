#include <gtkmm/grid.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <array>

class Entradas : public Gtk::Box {
public:
	Entradas ();
	~Entradas ();

    std::array<int, 9> get_inicial (); 
    std::array<int, 9> get_meta ();

private:
    std::array<Gtk::Entry, 9> inicial, meta;
    Gtk::Grid grid0, grid1;
    //Gtk::Button buscar;
};