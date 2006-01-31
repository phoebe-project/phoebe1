#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/cfortran.h"
#include "phoebe_allocations.h"
#include "phoebe_error_handling.h"
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

	#define READDCILINE1(a1,a2,a3,a4,a5,a6,a7,a8)                 CCALLSFSUB8(READDCILINE1,readdciline1,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,a1,a2,a3,a4,a5,a6,a7,a8)
	#define READDCILINE2(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)          CCALLSFSUB10(READDCILINE2,readdciline2,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)
	#define READDCILINE3(a1,a2,a3,a4,a5,a6,a7,a8,a9)              CCALLSFSUB9(READDCILINE3,readdciline3,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,a1,a2,a3,a4,a5,a6,a7,a8,a9)
	#define READDCILINE4(a1,a2,a3,a4,a5)                          CCALLSFSUB5(READDCILINE4,readdciline4,INTVV,INTV,INTV,INTV,DOUBLEV,a1,a2,a3,a4,a5)
	#define READDCILINE5(a1,a2,a3,a4)                             CCALLSFSUB4(READDCILINE5,readdciline5,INTV,INTV,INTV,INTV,a1,a2,a3,a4)
	#define READDCILINE6(a1,a2,a3,a4,a5,a6,a7)                    CCALLSFSUB7(READDCILINE6,readdciline6,INTV,INTV,INTV,INTV,INTV,INTV,INTV,a1,a2,a3,a4,a5,a6,a7)
	#define READDCILINE7(a1,a2,a3,a4,a5,a6,a7)                    CCALLSFSUB7(READDCILINE7,readdciline7,INTV,INTV,INTV,INTV,INTV,INTV,INTV,a1,a2,a3,a4,a5,a6,a7)
	#define READDCILINE8(a1,a2,a3,a4,a5)                          CCALLSFSUB5(READDCILINE8,readdciline8,INTV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,a1,a2,a3,a4,a5)
	#define READDCILINE9(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12)  CCALLSFSUB12(READDCILINE9,readdciline9,INTV,INTV,INTV,INTV,INTV,INTV,INTV,INTV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12)
	#define READDCILINE10(a1,a2,a3,a4,a5,a6,a7,a8,a9)             CCALLSFSUB9(READDCILINE10,readdciline10,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,a1,a2,a3,a4,a5,a6,a7,a8,a9)
	#define READDCILINE11(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11)     CCALLSFSUB11(READDCILINE11,readdciline11,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11)
	#define READDCILINERV(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)         CCALLSFSUB10(READDCILINERV,readdcilinerv,INTV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)
	#define READDCILINELC(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12) CCALLSFSUB12(READDCILINELC,readdcilinelc,INTV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,INTV,DOUBLEV,DOUBLEV,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12)
	#define READDCILINESPOTS(h1,h2,h3,h4)                         CCALLSFSUB4(READDCILINESPOTS,readdcilinespots,DOUBLEV,DOUBLEV,DOUBLEV,DOUBLEV,h1,h2,h3,h4)

int create_lci_file (char filename[], PHOEBE_main_parameters main, PHOEBE_switches switches,
    PHOEBE_limb_darkening ld, PHOEBE_spots spots, PHOEBE_curve_parameters curve,
    PHOEBE_wl_dependent_parameters mono)
	{
	int i;

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

int read_out_dci_file (char *filename)
{
	int i, curves;
	double *s = phoebe_malloc (35 * sizeof (*s));
	int    *k = phoebe_malloc (35 * sizeof (*k));
	int    dummyint;
	int    kspa, kspb, nspa, nspb, ifvc1, ifvc2, nlc, isym, nppl;
	int    nref, mref, ifsmv1, ifsmv2, icor1, icor2, ld, jdphs;
	int    mode, ipb, ifat1, ifat2, n1, n2, n1l, n2l;
	double lambda, hjd0, period, dpdt, pshift, perr0, dperdt, the, vunit;
	double e, a, f1, f2, vga, incl, gr1, gr2, abun, tavh, tavc, alb1, alb2;
	double phsv, pcsv, rm, xbol1, xbol2, ybol1, ybol2;

	int *iband, *noise;
	double *hla, *cla, *x1a, *x2a, *y1a, *y2a, *el3, *opsf, *sigma, *wla;
	double *xlat1, *xlat2, *xlong1, *xlong2, *radsp1, *radsp2, *temsp1, *temsp2;
	
	OPENSTREAM (filename);
	READDCILINE1  (&s[0], &s[1], &s[2], &s[3], &s[4], &s[5], &s[6], &s[7]);
	READDCILINE2  (&s[8], &s[9], &s[10], &s[11], &s[12], &s[13], &s[14], &s[15], &s[16], &s[17]);
	READDCILINE3  (&s[18], &s[19], &s[20], &s[21], &s[22], &s[23], &s[24], &s[25], &s[26]);
	READDCILINE4  (&k, &dummyint, &dummyint, &dummyint, &lambda);
	READDCILINE5  (&kspa, &nspa, &kspb, &nspb);
	READDCILINE6  (&ifvc1, &ifvc2, &nlc, &dummyint, &dummyint, &isym, &nppl);
	READDCILINE7  (&nref, &mref, &ifsmv1, &ifsmv2, &icor1, &icor2, &ld);
	READDCILINE8  (&jdphs, &hjd0, &period, &dpdt, &pshift);
	READDCILINE9  (&mode, &ipb, &ifat1, &ifat2, &n1, &n2, &n1l, &n2l, &perr0, &dperdt, &the, &vunit);
	READDCILINE10 (&e, &a, &f1, &f2, &vga, &incl, &gr1, &gr2, &abun);
	READDCILINE11 (&tavh, &tavc, &alb1, &alb2, &phsv, &pcsv, &rm, &xbol1, &xbol2, &ybol1, &ybol2);

	/* Now we must do the readout of passband-dependent parameters: */
	curves = ifvc1 + ifvc2 + nlc;
	iband = phoebe_malloc (curves * sizeof (*iband));
	hla   = phoebe_malloc (curves * sizeof (*hla));
	cla   = phoebe_malloc (curves * sizeof (*cla));
	x1a   = phoebe_malloc (curves * sizeof (*x1a));
	x2a   = phoebe_malloc (curves * sizeof (*x2a));
	y1a   = phoebe_malloc (curves * sizeof (*y1a));
	y2a   = phoebe_malloc (curves * sizeof (*y2a));
	el3   = phoebe_malloc (curves * sizeof (*el3));
	opsf  = phoebe_malloc (curves * sizeof (*opsf));
	sigma = phoebe_malloc (curves * sizeof (*sigma));
	wla   = phoebe_malloc (curves * sizeof (*wla));
	noise = phoebe_malloc (curves * sizeof (*noise));

	for (i = 0; i < ifvc1 + ifvc2; i++) {
		READDCILINERV (&iband[i], &hla[i], &cla[i], &x1a[i], &x2a[i], &y1a[i], &y2a[i], &opsf[i], &sigma[i], &wla[i]);
		el3[i] = -1.0; noise[i] = -1;
	}
	for (i = ifvc1 + ifvc2; i < ifvc1 + ifvc2 + nlc; i++) {
		READDCILINELC (&iband[i], &hla[i], &cla[i], &x1a[i], &x2a[i], &y1a[i], &y2a[i], &el3[i], &opsf[i], &noise[i], &sigma[i], &wla[i]);
	}

	/* Next come the spots: */
	if (nspa != 0) {
		xlat1  = phoebe_malloc (nspa * sizeof (*xlat1));
		xlong1 = phoebe_malloc (nspa * sizeof (*xlong1));
		radsp1 = phoebe_malloc (nspa * sizeof (*radsp1));
		temsp1 = phoebe_malloc (nspa * sizeof (*temsp1));

		for (i = 0; i < nspa; i++) {
			READDCILINESPOTS (&xlat1[i], &xlong1[i], &radsp1[i], &temsp1[i]);
		}
	}
	if (nspb != 0) {
		xlat2  = phoebe_malloc (nspa * sizeof (*xlat2));
		xlong2 = phoebe_malloc (nspa * sizeof (*xlong2));
		radsp2 = phoebe_malloc (nspa * sizeof (*radsp2));
		temsp2 = phoebe_malloc (nspa * sizeof (*temsp2));

		for (i = 0; i < nspb; i++) {
			READDCILINESPOTS (&xlat2[i], &xlong2[i], &radsp2[i], &temsp2[i]);
		}
	}

	CLOSESTREAM ();

	printf ("dels:   "); for (i = 0; i < 26; i++) { printf ("%3.3lf, ", s[i]); } printf ("%lf\n", s[i]);
	printf ("keps:   "); for (i = 0; i < 35; i++) { printf ("%d", k[i]); } printf ("\n");
	printf ("lambda: %lf\n", lambda);
	printf ("kspa:   %d\n", kspa);
	printf ("nspa:   %d\n", nspa);
	printf ("kspb:   %d\n", kspb);
	printf ("nspb:   %d\n", nspb);
	printf ("ifvc1:  %d\n", ifvc1);
	printf ("ifvc2:  %d\n", ifvc2);
	printf ("nlc:    %d\n", nlc);
	printf ("isym:   %d\n", isym);
	printf ("nppl:   %d\n", nppl);
	printf ("nref:   %d\n", nref);
	printf ("mref:   %d\n", mref);
	printf ("ifsmv1: %d\n", ifsmv1);
	printf ("ifsmv2: %d\n", ifsmv2);
	printf ("icor1:  %d\n", icor1);
	printf ("icor2:  %d\n", icor2);
	printf ("ld:     %d\n", ld);
	printf ("jdphs:  %d\n", jdphs);
	printf ("hjd0:   %lf\n", hjd0);
	printf ("period: %lf\n", period);
	printf ("dpdt:   %lf\n", dpdt);
	printf ("pshift: %lf\n", pshift);
	printf ("mode:   %d\n", mode);
	printf ("ipb:    %d\n", ipb);
	printf ("ifat1:  %d\n", ifat1);
	printf ("ifat2:  %d\n", ifat2);
	printf ("n1:     %d\n", n1);
	printf ("n2:     %d\n", n2);
	printf ("n1l:    %d\n", n1l);
	printf ("n2l:    %d\n", n2l);
	printf ("perr0:  %lf\n", perr0);
	printf ("dperdt: %lf\n", dperdt);
	printf ("the:    %lf\n", the);
	printf ("vunit:  %lf\n", vunit);
	printf ("e:      %lf\n", e);
	printf ("a:      %lf\n", a);
	printf ("f1:     %lf\n", f1);
	printf ("f2:     %lf\n", f2);
	printf ("vga:    %lf\n", vga);
	printf ("incl:   %lf\n", incl);
	printf ("gr1:    %lf\n", gr1);
	printf ("gr2:    %lf\n", gr2);
	printf ("abun:   %lf\n", abun);
	printf ("tavh:   %lf\n", tavh);
	printf ("tavc:   %lf\n", tavc);
	printf ("alb1:   %lf\n", alb1);
	printf ("alb2:   %lf\n", alb2);
	printf ("phsv:   %lf\n", phsv);
	printf ("pcsv:   %lf\n", pcsv);
	printf ("rm:     %lf\n", rm);
	printf ("xbol1:  %lf\n", xbol1);
	printf ("xbol2:  %lf\n", xbol2);
	printf ("ybol1:  %lf\n", ybol1);
	printf ("ybol2:  %lf\n", ybol2);
	printf ("iband:  "); for (i = 0; i < curves-1; i++) { printf ("%d, ", iband[i]); } printf ("%d\n", iband[i]);
	printf ("hla:    "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", hla[i]); } printf ("%lf\n", hla[i]);
	printf ("cla:    "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", cla[i]); } printf ("%lf\n", cla[i]);
	printf ("x1a:    "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", x1a[i]); } printf ("%lf\n", x1a[i]);
	printf ("x2a:    "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", x2a[i]); } printf ("%lf\n", x2a[i]);
	printf ("y1a:    "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", y1a[i]); } printf ("%lf\n", y1a[i]);
	printf ("y2a:    "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", y2a[i]); } printf ("%lf\n", y2a[i]);
	printf ("el3:    "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", el3[i]); } printf ("%lf\n", el3[i]);
	printf ("opsf:   "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", opsf[i]); } printf ("%lf\n", opsf[i]);
	printf ("noise:  "); for (i = 0; i < curves-1; i++) { printf ("%d, ", noise[i]); } printf ("%d\n", noise[i]);
	printf ("sigma:  "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", sigma[i]); } printf ("%lf\n", sigma[i]);
	printf ("wla:    "); for (i = 0; i < curves-1; i++) { printf ("%lf, ", wla[i]); } printf ("%lf\n", wla[i]);
	printf ("xlat1:  "); for (i = 0; i < nspa-1; i++) { printf ("%lf, ", xlat1[i]); } if (nspa != 0) printf ("%lf\n", xlat1[i]); else printf ("none\n");
	printf ("xlong1: "); for (i = 0; i < nspa-1; i++) { printf ("%lf, ", xlong1[i]); } if (nspa != 0) printf ("%lf\n", xlong1[i]); else printf ("none\n");
	printf ("radsp1: "); for (i = 0; i < nspa-1; i++) { printf ("%lf, ", radsp1[i]); } if (nspa != 0) printf ("%lf\n", radsp1[i]); else printf ("none\n");
	printf ("temsp1: "); for (i = 0; i < nspa-1; i++) { printf ("%lf, ", temsp1[i]); } if (nspa != 0) printf ("%lf\n", temsp1[i]); else printf ("none\n");
	printf ("xlat2:  "); for (i = 0; i < nspb-1; i++) { printf ("%lf, ", xlat2[i]); } if (nspb != 0) printf ("%lf\n", xlat2[i]); else printf ("none\n");
	printf ("xlong2: "); for (i = 0; i < nspb-1; i++) { printf ("%lf, ", xlong2[i]); } if (nspb != 0) printf ("%lf\n", xlong2[i]); else printf ("none\n");
	printf ("radsp2: "); for (i = 0; i < nspb-1; i++) { printf ("%lf, ", radsp2[i]); } if (nspb != 0) printf ("%lf\n", radsp2[i]); else printf ("none\n");
	printf ("temsp2: "); for (i = 0; i < nspb-1; i++) { printf ("%lf, ", temsp2[i]); } if (nspb != 0) printf ("%lf\n", temsp2[i]); else printf ("none\n");

	free (iband);
	free (hla);
	free (cla);
	free (x1a);
	free (x2a);
	free (y1a);
	free (y2a);
	free (el3);
	free (opsf);
	free (noise);
	free (sigma);
	free (wla);

	if (nspa != 0) { free (xlat1); free (xlong1); free (radsp1); free (temsp1); }
	if (nspb != 0) { free (xlat2); free (xlong2); free (radsp2); free (temsp2); }

	free (s);
	free (k);
	return 0;
}
