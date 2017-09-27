#ifndef PHOEBE_BASE_H
	#define PHOEBE_BASE_H 1

int  intern_get_atmcof_filenames(char **atmcofplanck, char **atmcof);

int  phoebe_init(void);
int  phoebe_configure(void);
int  phoebe_custom_configure(char *startup, char *home, char *basedir, char *tmpdir, char *datadir, char *ptfdir, int ldswitch, int ldintern, char *lddir, char *vhdir, int loadatm, int dumplco, int verbose_warnings, int verbose_errors);
int  phoebe_quit(void);
void phoebe_load_ld_tables(void);

#endif
