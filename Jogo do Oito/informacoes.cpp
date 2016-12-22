#include "informacoes.h"

Informacoes::Informacoes (const std::string& f)
    :frase (f)
{
	set_border_width (5);

	pack_start (frase, Gtk::PACK_SHRINK);
	pack_end (valor, Gtk::PACK_SHRINK);
}   

Informacoes::~Informacoes ()
{

} 