#ifndef PHOEBE_GLOBAL_H
#define PHOEBE_GLOBAL_H 1

#include <gtk/gtk.h>

/* ************************************************************************** */
/*                       Global PHOEBE GTK+ widgets:                          */
/* ************************************************************************** */

GtkWidget *PHOEBE;
GtkWidget *PHOEBE_about;
GtkWidget *PHOEBE_assign_data_file;
GtkWidget *PHOEBE_assign_rv_data_file;
GtkWidget *PHOEBE_assign_lc_luminosity;
GtkWidget *PHOEBE_assign_el3;
GtkWidget *PHOEBE_assign_ld_monochromatic_lc;
GtkWidget *PHOEBE_assign_ld_monochromatic_rv;
GtkWidget *PHOEBE_assign_primary_spots;
GtkWidget *PHOEBE_assign_secondary_spots;
GtkWidget *PHOEBE_assign_weighting;
GtkWidget *PHOEBE_calculate_grid;
GtkWidget *PHOEBE_calculate_grid_edit_parameters;
GtkWidget *PHOEBE_calculate_pcsv;
GtkWidget *PHOEBE_calculate_phsv;
GtkWidget *PHOEBE_configuration;
GtkWidget *PHOEBE_configuration_browse;
GtkWidget *PHOEBE_data_sheet;
GtkWidget *PHOEBE_dc;
GtkWidget *PHOEBE_dc_correlation_matrix;
GtkWidget *PHOEBE_file_selector;
GtkWidget *PHOEBE_filter_menu;
GtkWidget *PHOEBE_fitting_quickbar;
GtkWidget *PHOEBE_import_from_fotel;
GtkWidget *PHOEBE_open_keyword_file;
GtkWidget *PHOEBE_open_data_file;
GtkWidget *PHOEBE_plot_lc;
GtkWidget *PHOEBE_plot_rv;
GtkWidget *PHOEBE_plot_to_file;
GtkWidget *PHOEBE_plot_to_file_selector;
GtkWidget *PHOEBE_ld_interpolation;
GtkWidget *PHOEBE_scripter;

/* ************************************************************************** */
/*                       Global PHOEBE keyword names:                         */
/* ************************************************************************** */

typedef enum PHOEBE_keyword
	{
	STARNAME,             /* Eclipsing binary name (convenience only)           */
	MODEL,                /* Eclipsing binary model                             */
	LCNO,                 /* Experimental LC data number                        */
	RVNO,                 /* Experimental RV data number                        */
	SPECNO,               /* Experimental spectra data number                   */
	HJD0,                 /* Ephemeris zero time in HJD                         */
	PERIOD,               /* Eclipsing binary orbital period                    */
	DPDT,                 /* Period time derivative                             */
	PSHIFT,               /* Phase shift                                        */
	SMA,                  /* Semi-major axis                                    */
	RM,                   /* Mass ratio                                         */
	INCL,                 /* Orbital inclination                                */
	VGA,                  /* Systemic (gamma) velocity                          */
	TAVH,                 /* Primary star surface temperature                   */
	TAVC,                 /* Secondary star surface temperature                 */
	PHSV,                 /* Modified Kopal primary star gravity potential      */
	PCSV,                 /* Modified Kopal secondary star gravity potential    */
	LOGG1,                /* Logarithm of a primary star gravity acceleration   */
	LOGG2,                /* Logarithm of a secondary star gravity acceleration */
	MET1,                 /* Primary star metallicity abundance [M/H]           */
	MET2,                 /* Secondary star metallicity abundance [M/H]         */
	E,                    /* Orbital eccentricity                               */
	PERR0,                /* Argument of periastron                             */
	DPERDT,               /* Argument of periastron's first time derivative     */
	F1,                   /* Primary star synchronicity parameter               */
	F2,                   /* Secondary star synchronicity parameter             */
	ALB1,                 /* Primary star surface albedo                        */
	ALB2,                 /* Secondary star surface albedo                      */
	GR1,                  /* Primary star gravity brightening                   */
	GR2,                  /* Secondary star gravity brightening                 */
	MNORM,                /* Flux-normalizing magnitude (flux = 1)              */
	LC_PLOT_SYNTHETIC,    /* Plot synthetic light curve when LC plot is run     */
	LC_PLOT_EXPERIMENTAL, /* Plot experimental light curve when LC plot is run  */
	LC_FILTER,            /* Data from which filter to plot when plotting LCs   */
	RV_PLOT_SYNTHETIC,    /* Plot synthetic light curve when RV plot is run     */
	RV_PLOT_EXPERIMENTAL, /* Plot experimental light curve when RV plot is run  */
	RV_FILTER             /* Data from which filter to plot when plotting RVs   */
	} PHOEBE_keyword;

/* ************************************************************************** */
/*                       Global PHOEBE script keywords:                       */
/* ************************************************************************** */

typedef struct PHOEBE_script_command
	{
	char name[255];
	char description[255];
	int parno;
	char label[4][255];
	GtkWidget *widget[4];
	} PHOEBE_script_command;

typedef struct PHOEBE_script_command_list
	{
	int command_no;
	PHOEBE_script_command *command;
	} PHOEBE_script_command_list;

PHOEBE_script_command_list PHOEBE_command_list;

/* ************************************************************************** */
/*                     Global PHOEBE information strings:                     */
/* ************************************************************************** */

char PHOEBE_VERSION_NUMBER[20];
char PHOEBE_VERSION_DATE[20];

char USER_HOME_DIR[255];

char PHOEBE_STARTUP_DIR[255];

char PHOEBE_HOME_DIR[255];
char PHOEBE_BASE_DIR[255];
char PHOEBE_CONFIG[255];
char PHOEBE_SOURCE_DIR[255];
char PHOEBE_DEFAULTS_DIR[255];
char PHOEBE_TEMP_DIR[255];
char PHOEBE_DATA_DIR[255];
char PHOEBE_LC_DIR[255];
char PHOEBE_DC_DIR[255];
char PHOEBE_FF_DIR[255];
char PHOEBE_PLOTTING_PACKAGE[255];
int  PHOEBE_LD_SWITCH;
char PHOEBE_LD_DIR[255];

char PHOEBE_KEYWORD_FILENAME[255];
char PHOEBE_DEFAULTS[255];

char *PHOEBE_LOCALE;

/* ************************************************************************** */
/*                    Global PHOEBE configuration options:                    */
/* ************************************************************************** */

int PHOEBE_3D_PLOT_CALLBACK_OPTION;

int PHOEBE_CONFIRM_ON_SAVE;
int PHOEBE_CONFIRM_ON_QUIT;

int PHOEBE_WARN_ON_SYNTHETIC_SCATTER;

int PHOEBE_EXECUTE_SCRIPT;
char PHOEBE_EXECUTE_SCRIPT_NAME[255];

/* ************************************************************************** */
/*                    Global PHOEBE command line arguments:                   */
/* ************************************************************************** */

typedef struct PHOEBE_COMMAND_LINE_ARGS
	{
	int KEYWORD_SWITCH;
	char KEYWORD[255];
	} PHOEBE_COMMAND_LINE_ARGS;

/* ************************************************************************** */
/*                     Global PHOEBE plotting constants:                      */
/* ************************************************************************** */

double LC_ZOOM_FACTOR;
double LC_X_OFFSET;
double LC_Y_OFFSET;

double RV_ZOOM_FACTOR;
double RV_X_OFFSET;
double RV_Y_OFFSET;


/* ************************************************************************** */
/*                       PHOEBE typedefs and structs:                         */
/* ************************************************************************** */

typedef struct PHOEBE_main_parameters
	{
	double SMA;       /* Semi-major axis                                        */
	double RM;        /* Mass ratio                                             */
	double PERIOD;    /* Period                                                 */
	double HJD0;      /* Heliocentric julian date at phase 0                    */
	double TAVH;      /* Primary star surface temperature                       */
	double TAVC;      /* Secondary star surface temperature                     */
	double XINCL;     /* Inclination                                            */
	double VGA;       /* System radial velocity                                 */
	double PHSV;      /* Primary star surface potential                         */
	double PCSV;      /* Secondary star surface potential                       */
	double GR1;       /* Primary star gravity brightening                       */
	double GR2;       /* Secondary star gravity brightening                     */
	double ALB1;      /* Primary star albedo                                    */
	double ALB2;      /* Secondary star albedo                                  */
	double F1;        /* Primary star synchronicity parameter                   */
	double F2;        /* Secondary star synchronicity parameter                 */
	double E;         /* Orbital eccentricity                                   */
	double PERR0;     /* Argument of periastron at phase 0                      */
	double DPERDT;    /* First time derivative of the argument of periastron    */
	double DPDT;      /* First time derivative of period                        */
	double PSHIFT;    /* Phase shift                                            */
	double MNORM;     /* Normalizing magnitude for input data files             */
	double LOGG1;     /* Primary star surface gravity (log g)                   */
	double LOGG2;     /* Secondary star surface gravity (log g)                 */
	double M1;        /* Primary star metallicity ([M/H])                       */
	double M2;        /* Secondary star metallicity ([M/H])                     */
	double ABUNIN;    /* Chemical composition (since WD2003)                    */
	} PHOEBE_main_parameters;

typedef struct PHOEBE_switches
	{
	int    MPAGE;     /* What operation we want from WD                         */
	int    MODE;      /* What kind of binaries do we simulate                   */
	int    NLC;       /* Number of light curves                                 */
	int    IFVC1;     /* Is there a primary star RV curve available             */
	int    IFVC2;     /* Is there a secondary star RV curve available           */
	int    BINNING;   /* Should data be binned (useful for large databases)     */
	int    BINNO;     /* In case BINNING is on, this is the number of bins      */
	int    NPPL;      /* Number of points per line in a DCI file                */
	int    MREF;      /* Reflection effect switch                               */
	int    NREF;      /* Number of reflections                                  */
	int    ICOR1;     /* Proximity and eclipse effects on primary star rv       */
	int    ICOR2;     /* Proximity and eclipse effects on secondary star rv     */
	int    JDPHS;     /* Independent variable: time or phase                    */
	int    IPB;       /* Decouple temperature and luminosity for secondary star */
	int    IFAT1;     /* Atmosphere model for primary star                      */
	int    IFAT2;     /* Atmosphere model for secondary star                    */
	int    MODELLGG;  /* Switch to decouple model log g from atmospheric log g  */
	int    N1;        /* Grid size for primary star                             */
	int    N2;        /* Grid size for secondary star                           */
	int    N1L;       /* Coarse grid size for primary star                      */
	int    N2L;       /* Coarse grid size for secondary star                    */
	int    ISYM;      /* Use symetrical derivatives                             */
	int    K0;        /* Scratch file option                                    */
	int    KDISK;     /* Scratch file switch                                    */
	double THE;       /* The semi-duration of primary eclipse in phase units    */
	double XLAMDA;    /* Levenberg-Marquardt Step Coefficient Lambda            */
	int    REDDENING; /* Is the reddening effect to be removed from data        */
	double REDDENING_R; /* The reddening correlation coefficient                */
	double REDDENING_E; /* The reddening color excess coefficient               */
	int    NOISE;     /* Synthetic scatter level-weighting dependence           */
	double SIGMA;     /* Synthetic scatter standard deviation                   */
	double SEED;      /* Synthetic scatter random numbers generator seed        */
	} PHOEBE_switches;

typedef struct PHOEBE_curve_parameters
	{
	double PHNORM;   /* Phase where flux is normalized to FACTOR (usually 1)    */
	double FACTOR;   /* Multiplication factor: flux -> FACTOR * flux            */
	double HJDST;    /* HJD of the starting point of the graph                  */
	double HJDSP;    /* HJD of the ending point of the graph                    */
	double HJDIN;    /* HJD increment between nodes                             */
	double PHSTRT;   /* Phase of the starting point of the graph                */
	double PHSTOP;   /* Phase of the ending point of the graph                  */
	double PHIN;     /* Phase increment between nodes                           */
	} PHOEBE_curve_parameters;


typedef struct PHOEBE_limb_darkening
	{
	int LD;          /* Which limb-darkening law to use                         */
	double XBOL1;    /* Primary star linear coefficient                         */
	double XBOL2;    /* Secondary star linear coefficient                       */
	double YBOL1;    /* Primary star non-linear coefficient                     */
	double YBOL2;    /* Secondary star non-linear coefficient                   */
	} PHOEBE_limb_darkening;

typedef struct PHOEBE_spots
	{
	int    SPRIM;    /* Number of spots on the primary star                   */
	int    SSEC;     /* Number of spots on the secondary star                 */
	int    IFSMV1;   /* Do spots move longitudinally on primary star          */
	int    IFSMV2;   /* Do spots move longitudinally on secondary star        */
	int    KSPA;     /* Is the adjustable spot on a primary star?   [1,2]     */
	int    NSPA;     /* Which spot do we want to adjust?                      */
	int    KSPB;     /* Is the adjustable spot on a secondary star? [1,2]     */
	int    NSPB;     /* Which spot do we want to adjust?                      */
	double *XLAT1;   /* Primary star spots latitude                           */
	double *XLONG1;  /* Primary star spots longitude                          */
	double *RADSP1;  /* Primary star spots angular radius                     */
	double *TEMSP1;  /* Primary star spots temperature                        */
	double *XLAT2;   /* Secondary star spots latitude                         */
	double *XLONG2;  /* Secondary star spots longitude                        */
	double *RADSP2;  /* Secondary star spots angular radius                   */
	double *TEMSP2;  /* Secondary star spots temperature                      */
	} PHOEBE_spots;

typedef struct PHOEBE_wl_dependent_parameters
	{
	double WLA;      /* Central wavelength of a given filter                    */
	double HLA;      /* Primary star luminosity                                 */
	double CLA;      /* Secondary star luminosity                               */
	double X1A;      /* Primary star linear limb darkening coefficient          */
	double Y1A;      /* Secondary star linear limb darkening coefficient        */
	double X2A;      /* Primary star non-linear limb darkening coefficient      */
	double Y2A;      /* Secondary star non-linear limb darkening coefficient    */
	double EL3;      /* Third light                                             */
	double OPSF;     /* Opacity function                                        */
	int    NOISE;    /* How level-dependent weights are to be applied           */
	double SIGMA;    /* Standard deviation of experimental data                 */
	double VGA;      /* Systemic radial velocity                                */
	int    IBAND;    /* Filter identification number (since WD2003)             */
	} PHOEBE_wl_dependent_parameters;

typedef struct PHOEBE_data
	{
	int     ptsno;   /* The number of points that PHOEBE_data currently holds   */
	double *indep;   /* An array of independent data points                     */
	double *dep;     /* An array of dependent data points                       */
	double *weight;  /* An array of weights for data points                     */
	} PHOEBE_data;

typedef struct PHOEBE_vector
	{
	double x;
	double y;
	double z;
	} PHOEBE_vector;

typedef struct PHOEBE_3D_data
	{
	double *x;       /* An array of x-axis values                               */
	double *y;       /* An array of y-axis values                               */
	double *z;       /* An array of z-axis values                               */
	int ptsx;        /* Number of points in x-axis array                        */
	int ptsy;        /* Number of points in y-axis array                        */
	int ptsz;        /* Number of points in z-axis array                        */
	} PHOEBE_3D_data;

typedef struct PHOEBE_data_record
	{
	char column1[20];
	char column2[20];
	char column3[20];
	char filename[255];
	char sigma[20];
	char filter[20];
	} PHOEBE_data_record;

typedef struct PHOEBE_synthetic_rv_record
	{
	double hjd;
	double phase;
	double primary_norm_rv;
	double secondary_norm_rv;
	double primary_eclipse_corr;
	double secondary_eclipse_corr;
	double primary_rv;
	double secondary_rv;
	} PHOEBE_synthetic_rv_record;

typedef struct PHOEBE_dco_record
	{
	int    *points_no;      /* Array of data point numbers for all data curves  */
	double *chi2;           /* Array of chi2 values based on individual weights */
	int    *param_no;       /* The number of adjusted parameter (1--35)         */
	int    *curve_no;       /* The curve for which a given parameter applies    */
	double *original_value; /* Original value of a given parameter              */
	double *correction;     /* The correction to a given parameter              */
	double *modified_value; /* Modified value of a given parameter              */
	double *sigma;          /* Standard deviation of the parameter fit          */
	} PHOEBE_dco_record;

typedef struct PHOEBE_calculated_parameters
	{
	double mass_p;
	double mass_s;
	double radius_p;
	double radius_s;
	double mbol_p;
	double mbol_s;
	double logg_p;
	double logg_s;
	double psb_p;
	double psb_s;
	double surface_p;
	double surface_s;
	double rpole_p;
	double rpole_s;
	double rpoint_p;
	double rpoint_s;
	double rside_p;
	double rside_s;
	double rback_p;
	double rback_s;
	} PHOEBE_calculated_parameters;

typedef struct PHOEBE_mms
	{
	int on;          /* A switch to tell the program whether to use MMS or not  */
	int no;          /* A number of multiple subsets                            */
	int s1[35];      /* Multiple subset 1                                       */
	int s2[35];      /* Multiple subset 2                                       */
	int s3[35];      /* Multiple subset 3                                       */
	int s4[35];      /* Multiple subset 4                                       */
	int s5[35];      /* Multiple subset 5                                       */
	} PHOEBE_mms;

typedef enum PHOEBE_plot_device
	{
	x11,
	eps,
	ascii,
	xpm,
	gif,
	tinygif,
	ppm,
	tinyxpm,
	png
	} PHOEBE_plot_device;

/* ************************************************************************** */
/*                         Static struct declarations:                        */
/* ************************************************************************** */

PHOEBE_COMMAND_LINE_ARGS PHOEBE_args;

PHOEBE_data_record *PHOEBE_lc_data;
PHOEBE_data_record *PHOEBE_rv_data;

#endif
