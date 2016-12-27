#include "jogodooito.h"
#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create (argc, argv, "org.gtkmm.example");

	JogoDoOito jogo;

	return app->run (jogo);
}