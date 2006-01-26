#include <gtk/gtk.h>

#include "phoebe_gui_accessories.h"

int main (int argc, char *argv[])
{
	gtk_set_locale ();
	gtk_init (&argc, &argv);
	parse_startup_line (argc, argv);
	phoebe_init ();
	gtk_main ();

	return 0;
}
