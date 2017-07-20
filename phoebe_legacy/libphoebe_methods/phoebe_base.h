#ifndef PHOEBE_BASE_H
	#define PHOEBE_BASE_H 1

int    intern_get_atmcof_filenames (char **atmcofplanck, char **atmcof);

int    phoebe_init      ();
int    phoebe_configure ();
int    phoebe_quit      ();
void   phoebe_load_ld_tables();

#endif
