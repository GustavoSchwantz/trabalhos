#include "caminho.h"

Caminho::Caminho ()
    :Gtk::Box (Gtk::ORIENTATION_VERTICAL, 10),
    titulo ("Caminho:")
{
	set_border_width (5);

	caminho.set_policy (Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);

	caminho.add (entry);

	pack_start (titulo);
	pack_start (caminho);
	
}    

Caminho::~Caminho ()
{

}