#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/cfortran.h"
#include "phoebe_allocations.h"
#include "phoebe_global.h"
#include "phoebe_gui_support.h"
#include "phoebe_transformations.h"

/* C-Fortran callups declaration */
	#define OPENSTREAM(FN)                                          CCALLSFSUB1(OPENSTREAM,openstream,STRING,FN)
	#define CLOSESTREAM()                                           CCALLSFSUB0(CLOSESTREAM,closestream)

	#define CREATELCILINE1(a1,a2,a3,a4,a5,a6,a7,a8)                 CCALLSFSUB8(CREATELCILINE1,createlciline1,INT,INT,INT,INT,INT,INT,INT,INT,a1,a2,a3,a4,a5,a6,a7,a8)
	#define CREATELCILINE2(b1,b2,b3,b4,b5,b6,b7,b8)                 CCALLSFSUB8(CREATELCILINE2,createlciline2,INT,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,INT,DOUBLE,b1,b2,b3,b4,b5,b6,b7,b8)
	#define CREATELCILINE3(c1,c2,c3,c4,c5,c6,c7)                    CCALLSFSUB7(CREATELCILINE3,createlciline3,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,c1,c2,c3,c4,c5,c6,c7)
	#define CREATELCILINE4(d1,d2,d3,d4,d5,d6,d7,d8,d9,d10)          CCALLSFSUB10(CREATELCILINE4,createlciline4,INT,INT,INT,INT,INT,INT,DOUBLE,DOUBLE,DOUBLE,DOUBLE,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10)
	#define CREATELCILINE5(e1,e2,e3,e4,e5,e6,e7,e8,e9)              CCALLSFSUB9(CREATELCILINE5,createlciline5,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,e1,e2,e3,e4,e5,e6,e7,e8,e9)
	#define CREATELCILINE6(f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11)      CCALLSFSUB11(CREATELCILINE6,createlciline6,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11)
	#define CREATELCILINE7(g1,g2,g3,g4,g5,g6,g7,g8,g9,g10,g11,g12)  CCALLSFSUB12(CREATELCILINE7,createlciline7,INT,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,g1,g2,g3,g4,g5,g6,g7,g8,g9,g10,g11,g12)
	#define CREATELCILINE8(h1,h2,h3,h4)                             CCALLSFSUB4(CREATELCILINE8,createlciline8,DOUBLE,DOUBLE,DOUBLE,DOUBLE,h1,h2,h3,h4)
	#define CREATELCILINE10(j1,j2,j3,j4)                            CCALLSFSUB4(CREATELCILINE10,createlciline10,DOUBLE,DOUBLE,DOUBLE,DOUBLE,j1,j2,j3,j4)
	#define CREATELCILINE13(m1)                                     CCALLSFSUB1(CREATELCILINE13,createlciline13,INT,m1)

	#define CREATEDCILINE1(a1,a2,a3,a4,a5,a6,a7,a8)                 CCALLSFSUB8(CREATEDCILINE1,createdciline1,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,a1,a2,a3,a4,a5,a6,a7,a8)
	#define CREATEDCILINE2(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)          CCALLSFSUB10(CREATEDCILINE2,createdciline2,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)
	#define CREATEDCILINE3(a1,a2,a3,a4,a5,a6,a7,a8,a9)              CCALLSFSUB9(CREATEDCILINE3,createdciline3,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,a1,a2,a3,a4,a5,a6,a7,a8,a9)
	#define CREATEDCILINE4(a1,a2,a3,a4,a5)                          CCALLSFSUB5(CREATEDCILINE4,createdciline4,INTV,INT,INT,INT,DOUBLE,a1,a2,a3,a4,a5)
	#define CREATEDCILINE5(a1,a2,a3,a4)                             CCALLSFSUB4(CREATEDCILINE5,createdciline5,INT,INT,INT,INT,a1,a2,a3,a4)
	#define CREATEDCILINE6(a1,a2,a3,a4,a5,a6,a7)                    CCALLSFSUB7(CREATEDCILINE6,createdciline6,INT,INT,INT,INT,INT,INT,INT,a1,a2,a3,a4,a5,a6,a7)
	#define CREATEDCILINE7(a1,a2,a3,a4,a5,a6,a7)                    CCALLSFSUB7(CREATEDCILINE7,createdciline7,INT,INT,INT,INT,INT,INT,INT,a1,a2,a3,a4,a5,a6,a7)
	#define CREATEDCILINE8(a1,a2,a3,a4,a5)                          CCALLSFSUB5(CREATEDCILINE8,createdciline8,INT,DOUBLE,DOUBLE,DOUBLE,DOUBLE,a1,a2,a3,a4,a5)
	#define CREATEDCILINE9(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12)  CCALLSFSUB12(CREATEDCILINE9,createdciline9,INT,INT,INT,INT,INT,INT,INT,INT,DOUBLE,DOUBLE,DOUBLE,DOUBLE,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12)
	#define CREATEDCILINE10(a1,a2,a3,a4,a5,a6,a7,a8,a9)             CCALLSFSUB9(CREATEDCILINE10,createdciline10,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,a1,a2,a3,a4,a5,a6,a7,a8,a9)
	#define CREATEDCILINE11(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11)     CCALLSFSUB11(CREATEDCILINE11,createdciline11,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11)
	#define CREATEDCILINERV(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)         CCALLSFSUB10(CREATEDCILINERV,createdcilinerv,INT,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)
	#define CREATEDCILINELC(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12) CCALLSFSUB12(CREATEDCILINELC,createdcilinelc,INT,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,INT,DOUBLE,DOUBLE,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12)

	#define CREATESPOTSSTOPLINE() CCALLSFSUB0(CREATESPOTSSTOPLINE,createspotsstopline)
	#define CREATECLOUDSSTOPLINE() CCALLSFSUB0(CREATECLOUDSSTOPLINE,createcloudsstopline)
	#define CREATEDATASTOPLINE() CCALLSFSUB0(CREATEDATASTOPLINE,createdatastopline)

	#define CREATELCIENDLINE() CCALLSFSUB0(CREATELCIENDLINE,createlciendline)
	#define CREATEDCIENDLINE() CCALLSFSUB0(CREATEDCIENDLINE,createdciendline)

	#define CREATEDATALINE(a1,a2,a3) CCALLSFSUB3(CREATEDATALINE,createdataline,DOUBLE,DOUBLE,DOUBLE,a1,a2,a3)


int create_lci_file (char filename[], PHOEBE_main_parameters main, PHOEBE_switches switches,
    PHOEBE_limb_darkening ld, PHOEBE_spots spots, PHOEBE_curve_parameters curve,
    PHOEBE_wl_dependent_parameters mono)
	{
	int i;
printf ("->%g<-\n", main.DPDT);

	OPENSTREAM (filename);
	CREATELCILINE1  (switches.MPAGE, switches.NREF, switches.MREF, spots.IFSMV1, spots.IFSMV2, switches.ICOR1, switches.ICOR2, ld.LD);
	CREATELCILINE2  (switches.JDPHS, main.HJD0, main.PERIOD, main.DPDT, main.PSHIFT, switches.SIGMA, switches.NOISE, switches.SEED);
	CREATELCILINE3  (curve.HJDST, curve.HJDSP, curve.HJDIN, curve.PHSTRT, curve.PHSTOP, curve.PHIN, curve.PHNORM);
	CREATELCILINE4  (switches.MODE, switches.IPB, switches.IFAT1, switches.IFAT2, switches.N1, switches.N2, main.PERR0, main.DPERDT, switches.THE, 100.0);
	CREATELCILINE5  (main.E, main.SMA, main.F1, main.F2, main.VGA/100., main.XINCL, main.GR1, main.GR2, main.ABUNIN);
	CREATELCILINE6  (main.TAVH/10000., main.TAVC/10000., main.ALB1, main.ALB2, main.PHSV, main.PCSV, main.RM, ld.XBOL1, ld.XBOL2, ld.YBOL1, ld.YBOL2);
	CREATELCILINE7  (mono.IBAND, mono.HLA, mono.CLA, mono.X1A, mono.X2A, mono.Y1A, mono.Y2A, mono.EL3, mono.OPSF, 0.0, curve.FACTOR, mono.WLA/1000.);
	if (spots.SPRIM != 0)
		for (i = 0; i < spots.SPRIM; i++)
			CREATELCILINE8  (spots.XLAT1[i], spots.XLONG1[i], spots.RADSP1[i], spots.TEMSP1[i]);
	CREATESPOTSSTOPLINE ();
	if (spots.SSEC != 0)
		for (i = 0; i < spots.SSEC; i++)
			CREATELCILINE10 (spots.XLAT2[i], spots.XLONG2[i], spots.RADSP2[i], spots.TEMSP2[i]);
	CREATESPOTSSTOPLINE ();
	CREATECLOUDSSTOPLINE ();
	CREATELCIENDLINE ();
	CLOSESTREAM ();

	return 0;
	}

int create_dci_file (char filename[], double DEL[35], int KEP[35],
    PHOEBE_main_parameters main, PHOEBE_limb_darkening ld, PHOEBE_spots spots,
		PHOEBE_switches switches, PHOEBE_mms mms)
	{
	/* 0->33 index in DEL array isn't OB1, it is supposed to be like that.      */

	int i, j;

	PHOEBE_data lc;
	PHOEBE_data rv;

	PHOEBE_wl_dependent_parameters mono;

	OPENSTREAM (filename);
	CREATEDCILINE1  (DEL[0], DEL[1], DEL[2], DEL[3], DEL[4], DEL[5], DEL[6], DEL[7]);
	CREATEDCILINE2  (DEL[9], DEL[10], DEL[11], DEL[12], DEL[13], DEL[15], DEL[16], DEL[17], DEL[18], DEL[19]);
	CREATEDCILINE3  (DEL[20], DEL[21], DEL[22], DEL[23], DEL[24], DEL[30], DEL[31], DEL[32], DEL[33]);
	CREATEDCILINE4  (KEP, 1, 1, 1, switches.XLAMDA);
	CREATEDCILINE5  (spots.KSPA, spots.NSPA, spots.KSPB, spots.NSPB);
	CREATEDCILINE6  (switches.IFVC1, switches.IFVC2, switches.NLC, switches.K0, switches.KDISK, switches.ISYM, switches.NPPL);
	CREATEDCILINE7  (switches.NREF, switches.MREF, spots.IFSMV1, spots.IFSMV2, switches.ICOR1, switches.ICOR2, ld.LD);
	CREATEDCILINE8  (switches.JDPHS, main.HJD0, main.PERIOD, main.DPDT, main.PSHIFT);
	CREATEDCILINE9  (switches.MODE, switches.IPB, switches.IFAT1, switches.IFAT2, switches.N1, switches.N2, switches.N1L, switches.N2L, main.PERR0, main.DPERDT, switches.THE, 100.0);
	CREATEDCILINE10 (main.E, main.SMA, main.F1, main.F2, main.VGA/100., main.XINCL, main.GR1, main.GR2, main.ABUNIN);
	CREATEDCILINE11 (main.TAVH/10000., main.TAVC/10000., main.ALB1, main.ALB2, main.PHSV, main.PCSV, main.RM, ld.XBOL1, ld.XBOL2, ld.YBOL1, ld.YBOL2);

	if (switches.IFVC1 == 1)
		{
		mono = read_in_wl_dependent_parameters (PHOEBE_rv_data[0].filter);
		CREATEDCILINERV (mono.IBAND, mono.HLA, mono.CLA, mono.X1A, mono.X2A, mono.Y1A, mono.Y2A, mono.OPSF, mono.SIGMA, mono.WLA/1000.);
		}

	if (switches.IFVC2 == 1)
		{
		mono = read_in_wl_dependent_parameters (PHOEBE_rv_data[1].filter);
		CREATEDCILINERV (mono.IBAND, mono.HLA, mono.CLA, mono.X1A, mono.X2A, mono.Y1A, mono.Y2A, mono.OPSF, mono.SIGMA, mono.WLA/1000.);
		}

	for (i = 0; i < switches.NLC; i++)
		{
		mono = read_in_wl_dependent_parameters (PHOEBE_lc_data[i].filter);
		CREATEDCILINELC (mono.IBAND, mono.HLA, mono.CLA, mono.X1A, mono.X2A, mono.Y1A, mono.Y2A, mono.EL3, mono.OPSF, mono.NOISE, mono.SIGMA, mono.WLA/1000.);
		}

	if (spots.SPRIM != 0)
		for (i = 0; i < spots.SPRIM; i++)
			CREATELCILINE8  (spots.XLAT1[i], spots.XLONG1[i], spots.RADSP1[i], spots.TEMSP1[i]);
	CREATESPOTSSTOPLINE ();
	if (spots.SSEC != 0)
		for (i = 0; i < spots.SSEC; i++)
			CREATELCILINE10 (spots.XLAT2[i], spots.XLONG2[i], spots.RADSP2[i], spots.TEMSP2[i]);
	CREATESPOTSSTOPLINE ();

	CREATECLOUDSSTOPLINE ();

	if (switches.IFVC1 == 1)
		{
		read_in_experimental_rv_data (0, &rv, switches.JDPHS, 7, 100.0);
		for (i = 0; i < rv.ptsno; i++) CREATEDATALINE (rv.indep[i], rv.dep[i], rv.weight[i]);
		CREATEDATASTOPLINE ();
		}

	if (switches.IFVC2 == 1)
		{
		read_in_experimental_rv_data (1, &rv, switches.JDPHS, 8, 100.0);
		for (i = 0; i < rv.ptsno; i++) CREATEDATALINE (rv.indep[i], rv.dep[i], rv.weight[i]);
		CREATEDATASTOPLINE ();
		}

	for (i = 0; i < switches.NLC; i++)
		{
		read_in_experimental_lc_data (i, &lc, switches.JDPHS, 5);
		for (j = 0; j < lc.ptsno; j++) CREATEDATALINE (lc.indep[j], lc.dep[j], lc.weight[j]);
		CREATEDATASTOPLINE ();
		}

	/* Free dynamical memory arrays, since we don't need them anymore, but only */
	/* if they were phoebe_malloc()ed:                                          */
	if ( (switches.IFVC1 == 1) || (switches.IFVC2 == 1) )
		{
		free (rv.indep); free (rv.dep); free (rv.weight);
		}
	if (switches.NLC != 0)
		{
		free (lc.indep); free (lc.dep); free (lc.weight);
		}

	/* Create multiple subsets, if any: */
	if (mms.on == 1)
		{
		if (mms.no >= 1) CREATEDCILINE4  (mms.s1, 1, 1, 1, switches.XLAMDA);
		if (mms.no >= 2) CREATEDCILINE4  (mms.s2, 1, 1, 1, switches.XLAMDA);
		if (mms.no >= 3) CREATEDCILINE4  (mms.s3, 1, 1, 1, switches.XLAMDA);
		if (mms.no >= 4) CREATEDCILINE4  (mms.s4, 1, 1, 1, switches.XLAMDA);
		if (mms.no == 5) CREATEDCILINE4  (mms.s5, 1, 1, 1, switches.XLAMDA);
		}

	CREATEDCIENDLINE ();

	CLOSESTREAM ();

	return 0;
	}
