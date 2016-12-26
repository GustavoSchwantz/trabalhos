#include "entradas.h"

Entradas::Entradas ()
    //:buscar ("Iniciar Busca")
{
	set_border_width (10);

	inicial[0].set_width_chars (1);
	inicial[1].set_width_chars (1);
	inicial[2].set_width_chars (1);
	inicial[3].set_width_chars (1);
	inicial[4].set_width_chars (1);
	inicial[5].set_width_chars (1);
	inicial[6].set_width_chars (1);
	inicial[7].set_width_chars (1);
	inicial[8].set_width_chars (1);

	inicial[0].set_max_length (1);
	inicial[1].set_max_length (1);
	inicial[2].set_max_length (1);
	inicial[3].set_max_length (1);
	inicial[4].set_max_length (1);
	inicial[5].set_max_length (1);
	inicial[6].set_max_length (1);
	inicial[7].set_max_length (1);
	inicial[8].set_max_length (1);

	grid0.add (inicial[0]);
	grid0.add (inicial[1]);
	grid0.add (inicial[2]);
	grid0.attach (inicial[3], 0, 1, 1, 1);
	grid0.attach (inicial[4], 1, 1, 1, 1);
	grid0.attach (inicial[5], 2, 1, 1, 1);
	grid0.attach (inicial[6], 0, 2, 1, 1);
	grid0.attach (inicial[7], 1, 2, 1, 1);
	grid0.attach (inicial[8], 2, 2, 1, 1);

	pack_start (grid0, Gtk::PACK_EXPAND_PADDING);

	meta[0].set_width_chars (1);
	meta[1].set_width_chars (1);
	meta[2].set_width_chars (1);
	meta[3].set_width_chars (1);
	meta[4].set_width_chars (1);
	meta[5].set_width_chars (1);
	meta[6].set_width_chars (1);
	meta[7].set_width_chars (1);
	meta[8].set_width_chars (1);

	meta[0].set_max_length (1);
	meta[1].set_max_length (1);
	meta[2].set_max_length (1);
	meta[3].set_max_length (1);
	meta[4].set_max_length (1);
	meta[5].set_max_length (1);
	meta[6].set_max_length (1);
	meta[7].set_max_length (1);
	meta[8].set_max_length (1);

	grid1.add (meta[0]);
	grid1.add (meta[1]);
	grid1.add (meta[2]);
	grid1.attach (meta[3], 0, 1, 1, 1);
	grid1.attach (meta[4], 1, 1, 1, 1);
	grid1.attach (meta[5], 2, 1, 1, 1);
	grid1.attach (meta[6], 0, 2, 1, 1);
	grid1.attach (meta[7], 1, 2, 1, 1);
	grid1.attach (meta[8], 2, 2, 1, 1);

	pack_start (grid1, Gtk::PACK_EXPAND_PADDING);
	//pack_start (buscar, Gtk::PACK_EXPAND_PADDING);
}

Entradas::~Entradas ()
{

}

std::array<int, 9> Entradas::get_inicial ()
{
	std::array<int, 9> i;

	i[0] = std::stoi (inicial[0].get_text ());
	i[1] = std::stoi (inicial[1].get_text ());
	i[2] = std::stoi (inicial[2].get_text ());
	i[3] = std::stoi (inicial[3].get_text ());
	i[4] = std::stoi (inicial[4].get_text ());
	i[5] = std::stoi (inicial[5].get_text ());
	i[6] = std::stoi (inicial[6].get_text ());
	i[7] = std::stoi (inicial[7].get_text ());
	i[8] = std::stoi (inicial[8].get_text ());

	return i;
}

std::array<int, 9> Entradas::get_meta ()
{
	std::array<int, 9> m;

	m[0] = std::stoi (meta[0].get_text ());
	m[1] = std::stoi (meta[1].get_text ());
	m[2] = std::stoi (meta[2].get_text ());
	m[3] = std::stoi (meta[3].get_text ());
	m[4] = std::stoi (meta[4].get_text ());
	m[5] = std::stoi (meta[5].get_text ());
	m[6] = std::stoi (meta[6].get_text ());
	m[7] = std::stoi (meta[7].get_text ());
	m[8] = std::stoi (meta[8].get_text ());

	return m;
}