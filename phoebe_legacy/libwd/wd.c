/* wd.F -- translated by f2c (version 20200916).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    doublereal abun[19], glog[11];
} abung_;

#define abung_1 abung_

union {
    struct {
	doublereal grand[581856];
	integer istart;
    } _1;
    struct {
	doublereal grand[481536];
	integer istart;
    } _2;
} arrayleg_;

#define arrayleg_1 (arrayleg_._1)
#define arrayleg_2 (arrayleg_._2)

struct {
    doublereal tlowtol, thightol, glowtol, ghightol;
} ramprange_;

#define ramprange_1 ramprange_

union {
    struct {
	integer message[8]	/* was [2][4] */, komp;
    } _1;
    struct {
	integer message[8]	/* was [2][4] */, kompcom;
    } _2;
} atmmessages_;

#define atmmessages_1 (atmmessages_._1)
#define atmmessages_2 (atmmessages_._2)

union {
    struct {
	integer kh, ipbdum, irte, nref, irvol1, irvol2, mref, ifsmv1, ifsmv2, 
		icor1, icor2, ld, ncl, jdphs, ipc;
    } _1;
    struct {
	integer kh, ipb, irte, nref, irvol1, irvol2, mref, ifsmv1, ifsmv2, 
		icor1, icor2, ld, ncl, jdphs, ipc;
    } _2;
    struct {
	integer khdum, ipb, irte, nref, irvol1, irvol2, mref, ifsmv1, ifsmv2, 
		icor1, icor2, ld, ncl, jdphs, ipc;
    } _3;
    struct {
	integer khdum, ipbdum, irtedm, nrefdm, irv1dm, irv2dm, mrefdm, ifs1dm,
		 ifs2dm, icr1dm, icr2dm, ld, ncl, jdphs, ipc;
    } _4;
    struct {
	integer khdum, ipbdum, irtedm, nrefdm, irv1dm, irv2dm, mrefdm, is1dm, 
		is2dm, ic1dm, ic2dm, ld, ncl, jdphs, ipc;
    } _5;
    struct {
	integer id1, id2, id3, id4, id5, id6, id7, id8, id9, id10, id11, ld, 
		id13, id14, id15;
    } _6;
} invar_;

#define invar_1 (invar_._1)
#define invar_2 (invar_._2)
#define invar_3 (invar_._3)
#define invar_4 (invar_._4)
#define invar_5 (invar_._5)
#define invar_6 (invar_._6)

union {
    struct {
	doublereal pshift, dp, ef, efc, ecos, perr0, phper, pconsc, pconic, 
		phperi, vsum1, vsum2, vra1, vra2, vkm1, vkm2, vunit, vfvu, 
		trc, qfacd;
    } _1;
    struct {
	doublereal psh, dp, ef, efc, ecos, pert, phper, pconsc, pconic, 
		phperi, vsum1, vsum2, vra1, vra2, vkm1, vkm2, vunit, vfvu, 
		trc, qfacd;
    } _2;
    struct {
	doublereal du2, du3, du4, du5, du6, du7, du8, du9, du10, du11, du12, 
		du13, du14, du15, du16, du17, vunit, vfvu, du20, qfacd;
    } _3;
} flvar_;

#define flvar_1 (flvar_._1)
#define flvar_2 (flvar_._2)
#define flvar_3 (flvar_._3)

struct {
    integer nsp1, nsp2;
} nspt_;

#define nspt_1 nspt_

union {
    struct {
	doublereal dperdt, hjd, hjd0, perr;
    } _1;
    struct {
	doublereal dperdt, hjd, hjd0, perdum;
    } _2;
} ardot_;

#define ardot_1 (ardot_._1)
#define ardot_2 (ardot_._2)

union {
    struct {
	doublereal snlat[200]	/* was [2][100] */, cslat[200]	/* was [2][
		100] */, snlng[200]	/* was [2][100] */, cslng[200]	/* 
		was [2][100] */, rdsp[200]	/* was [2][100] */, tmsp[200]	
		/* was [2][100] */, xlng[200]	/* was [2][100] */;
	integer kks[200]	/* was [2][100] */, lspot[200]	/* was [2][
		100] */;
    } _1;
    struct {
	doublereal sinlat[200]	/* was [2][100] */, coslat[200]	/* was [2][
		100] */, sinlng[200]	/* was [2][100] */, coslng[200]	/* 
		was [2][100] */, radsp[200]	/* was [2][100] */, temsp[200]
			/* was [2][100] */, xlng[200]	/* was [2][100] */;
	integer kks[200]	/* was [2][100] */, lspot[200]	/* was [2][
		100] */;
    } _2;
    struct {
	doublereal sinlat[200]	/* was [2][100] */, coslat[200]	/* was [2][
		100] */, sinlng[200]	/* was [2][100] */, coslng[200]	/* 
		was [2][100] */, rad[200]	/* was [2][100] */, temsp[200]
			/* was [2][100] */, xlng[200]	/* was [2][100] */;
	integer kks[200]	/* was [2][100] */, lspot[200]	/* was [2][
		100] */;
    } _3;
} spots_;

#define spots_1 (spots_._1)
#define spots_2 (spots_._2)
#define spots_3 (spots_._3)

union {
    struct {
	doublereal e, a, period, vga, sini, vf, vfac, vgam, vol1, vol2;
	integer ifc;
    } _1;
    struct {
	doublereal ec, a, period, vga, sini, vf, vfac, vgam, vol1, vol2;
	integer ifc;
    } _2;
    struct {
	doublereal ecc, smaxis, period, vgadum, sindum, vfdum, vfadum, vgmdum,
		 v1dum, v2dum;
	integer ifcdum;
    } _3;
    struct {
	doublereal e, dum1, dum2, dum3, dum4, dum5, dum6, dum7, dum8, dum9;
	integer ifc;
    } _4;
    struct {
	doublereal e, smaxis, period, vgadum, sindum, vfdum, vfadum, vgmdum, 
		v1dum, v2dum;
	integer ifcdum;
    } _5;
} eccen_;

#define eccen_1 (eccen_._1)
#define eccen_2 (eccen_._2)
#define eccen_3 (eccen_._3)
#define eccen_4 (eccen_._4)
#define eccen_5 (eccen_._5)

union {
    struct {
	doublereal vo1, vo2, ff1, ff2, du1, du2, du3, du4, du5, du6, du7;
    } _1;
    struct {
	doublereal duma, dumb, dumc, dumd, du1, du2, du3, du4, du5, du6, du7;
    } _2;
    struct {
	doublereal du1, du2, du3, du4, binw1, binw2, sc1, sc2, sl1, sl2, 
		clight;
    } _3;
    struct {
	doublereal vo1, vo2, ff1, ff2, binw1, binw2, sc1, sc2, sl1, sl2, 
		clight;
    } _4;
} prof2_;

#define prof2_1 (prof2_._1)
#define prof2_2 (prof2_._2)
#define prof2_3 (prof2_._3)
#define prof2_4 (prof2_._4)

union {
    struct {
	doublereal plcof[2400];
    } _1;
    struct {
	doublereal plcof[2900];
    } _2;
    struct {
	doublereal plcof[1750];
    } _3;
} planckleg_;

#define planckleg_1 (planckleg_._1)
#define planckleg_2 (planckleg_._2)
#define planckleg_3 (planckleg_._3)

union {
    struct {
	doublereal dpdx1, dpdx2, pot1, pot2;
    } _1;
    struct {
	doublereal dpdx1, dpdx2, phsv, pcsv;
    } _2;
} dpdx_;

#define dpdx_1 (dpdx_._1)
#define dpdx_2 (dpdx_._2)

struct {
    doublereal summ1, summ2;
} summ_;

#define summ_1 summ_

struct {
    doublereal acm, opsf;
} cld_;

#define cld_1 cld_

union {
    struct {
	integer nbins, nl, inmax, inmin, nf1, nf2;
    } _1;
    struct {
	integer nbins, nl, inmax, inmin, idum1, idum2;
    } _2;
} ipro_;

#define ipro_1 (ipro_._1)
#define ipro_2 (ipro_._2)

struct {
    integer in1min, in1max, in2min, in2max, mpage, nl1, nl2;
} inprof_;

#define inprof_1 inprof_

union {
    struct {
	doublereal xld, yld;
    } _1;
    struct {
	doublereal x, y;
    } _2;
} coflimbdark_;

#define coflimbdark_1 (coflimbdark_._1)
#define coflimbdark_2 (coflimbdark_._2)

struct {
    doublereal gplog1, gplog2;
} gpoles_;

#define gpoles_1 gpoles_

struct {
    integer kff1, kff2, kfo1, kfo2;
} kfac_;

#define kfac_1 kfac_

struct {
    doublereal x1;
} misc_;

#define misc_1 misc_

struct {
    doublereal sefac;
} setest_;

#define setest_1 setest_

union {
    struct {
	doublereal vksf, binc, binw, difp, deldel, renfsq;
    } _1;
    struct {
	doublereal vks, binc, binw, difp, dum1, dum2;
    } _2;
} flpro_;

#define flpro_1 (flpro_._1)
#define flpro_2 (flpro_._2)

struct {
    doublereal r1h, rlh, r1c, rlc;
} radi_;

#define radi_1 radi_

/* Table of constant values */

static integer c__11 = 11;
static doublereal c_b15 = 0.;
static doublereal c_b18 = 10.;
static integer c__5 = 5;
static integer c_b311 = 481536;
static integer c__2400 = 2400;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__19 = 19;
static integer c__9 = 9;
static doublereal c_b886 = .33333333333333331;
static integer c_b900 = 581856;
static integer c__2900 = 2900;
static integer c__100 = 100;
static integer c__0 = 0;
static integer c__10 = 10;
static doublereal c_b1275 = 1.;
static integer c__7 = 7;
static doublereal c_b1630 = 300.;
static doublereal c_b1639 = 150.;
static doublereal c_b1646 = -10001.;

/* Subroutine */ int atmx_(doublereal *t, doublereal *g, integer *ifil, 
	doublereal *xintlog, doublereal *xint)
{
    /* Initialized data */

    static doublereal effwvl[58] = { 350.,412.,430.,546.,365.,440.,550.,680.,
	    870.,1220.,2145.,3380.,4900.,9210.,650.,790.,230.,250.,270.,290.,
	    310.,330.,430.,520.,500.,640.,640.,1620.,345.6,424.5,402.4,448.,
	    550.,540.5,580.5,592.,355.7,482.5,626.1,767.2,909.7,367.,485.,
	    624.,752.,867.,963.,963.,326.,362.,382.,431.,540.,547.,550.,550.,
	    427.,623. };

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    double d_lg10(doublereal *), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    extern /* Subroutine */ int legendre_(doublereal *, doublereal *, integer 
	    *);
    static doublereal thighrec, thighlog;
    static integer ifreturn, j, k, m;
    extern /* Subroutine */ int planckint_(doublereal *, integer *, 
	    doublereal *, doublereal *);
    static integer ib;
    static doublereal gg;
    static integer ma, ii, jj, kj;
    static doublereal tb;
    static integer kk, nj;
    static doublereal te, pl[10];
    static integer it;
    static doublereal tt, yy[4];
    static integer it1;
    static doublereal tlowmidlog;
    static integer ibb;
    static doublereal pha[4];
    static integer iij, kik, njj;
    static doublereal dum, tte[2], thighmidlog;
    static integer ibin;
    static doublereal trec, tlog, glow, tlow, xnum;
    static integer icase;
    static doublereal ghigh, tbrec, denom, thigh, terec, tblog, telog, slope, 
	    yylow;
    extern /* Subroutine */ int binnum_(doublereal *, integer *, doublereal *,
	     integer *);
    static doublereal yyhigh, wvlmax, fractol;
    static integer ibinsav;
    static doublereal tlowrec, tlowlog;

/* Version of January 23, 2004 */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     Model atmosphere grid properties: */

/*       itemppts  ..   number of temperature coefficients per spectrum */
/*                        default: itemppts=48 (4x12) */
/*       iloggpts  ..   number of log(g) nodes */
/*                        default: iloggpts=11 (atmosphere grid) */
/*       imetpts   ..   number of metallicity nodes */
/*                        default: imetpts=19  (atmosphere grid) */
/*       iatmpts   ..   size of the atmosphere grid per passband per */
/*                      metallicity */
/*                        default: iatmpts = 11*48 = 528 */
/*                        11 log(g) values and */
/*                        48=4x12 temperature coefficients */
/*       iatmchunk ..   size of the atmosphere grid per metallicity */
/*                        default: iatmchunk = 528*25 = 13200 */
/*       iatmsize  ..   size of the atmosphere grid */
/*                        default: iatmsize = 13200*19 = 250800 */


/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    tlog = d_lg10(t);
    trec = 1. / *t;
    tlow = 3500. - ramprange_1.tlowtol;
    if (*t <= tlow) {
	goto L66;
    }
    thigh = ramprange_1.thightol + 5e4;
    fractol = ramprange_1.thightol / 5e4;
    glow = 0. - ramprange_1.glowtol;
    if (*g <= glow) {
	goto L77;
    }
    ghigh = ramprange_1.ghightol + 5.;
    if (*g >= ghigh) {
	goto L78;
    }
    tt = *t;
    gg = *g;
    if (*g >= 0.) {
	goto L11;
    }
    gg = 0.;
    goto L12;
L11:
    if (*g <= 5.) {
	goto L12;
    }
    gg = 5.;
L12:
/* cccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* The following is for 4-point interpolation in log g. */
/* cccccccccccccccccccccccccccccccccccccccccccccccccccc */
    m = 4;
    ifreturn = 0;
    icase = arrayleg_1.istart + (*ifil - 1) * 528;
    binnum_(abung_1.glog, &c__11, g, &j);
/* Computing MIN */
/* Computing MAX */
    i__3 = j - (m - 1) / 2;
    i__1 = max(i__3,1), i__2 = 12 - m;
    k = min(i__1,i__2);
    if (*g <= 0.) {
	j = 1;
    }
L10:
    ib = icase + (k - 1) * 48;
    ib += -48;
/* cccccccccccccccccccccccccccccccccccccccccccccccccccc */
    i__1 = m;
    for (ii = 1; ii <= i__1; ++ii) {
	ib += 48;
	for (ibin = 1; ibin <= 4; ++ibin) {
	    it = ib + (ibin - 1) * 12;
	    it1 = it + 1;
	    if (tt <= arrayleg_1.grand[it1 - 1]) {
		goto L720;
	    }
/* L719: */
	}
	--ibin;
L720:
	tb = arrayleg_1.grand[it - 1];
	if (tb != 0.) {
	    goto L55;
	}
	if (ibin == 4) {
	    --ibin;
	}
	if (ibin == 1) {
	    ++ibin;
	}
	it = ib + (ibin - 1) * 12;
	it1 = it + 1;
	tb = arrayleg_1.grand[it - 1];
L55:
	te = arrayleg_1.grand[it1 - 1];
	ibinsav = ibin;
	thigh = te + fractol * te;
	ibb = ib + 1 + (ibin - 1) * 12;
	for (jj = 1; jj <= 10; ++jj) {
	    if (arrayleg_1.grand[ibb + jj - 1] != 0.) {
		goto L1;
	    }
	    goto L2;
L1:
	    ;
	}
L2:
	ma = jj - 1;
	pha[ii - 1] = (tt - tb) / (te - tb);
	yy[ii - 1] = 0.;
	legendre_(&pha[ii - 1], pl, &ma);
	if (pha[ii - 1] < 0.) {
	    legendre_(&c_b15, pl, &ma);
	}
	i__2 = ma;
	for (kk = 1; kk <= i__2; ++kk) {
	    kj = ibb + kk;
/* L3: */
	    yy[ii - 1] += pl[kk - 1] * arrayleg_1.grand[kj - 1];
	}
	if (pha[ii - 1] >= 0.) {
	    goto L4;
	}
	tlow = tb - ramprange_1.tlowtol;
	planckint_(&tlow, ifil, &yylow, &dum);
	if (*t >= tlow) {
	    goto L424;
	}
	planckint_(t, ifil, &yy[ii - 1], &dum);
	goto L4;
L424:
	d__1 = tb * tlow;
	tlowmidlog = d_lg10(&d__1) * .5;
	d__1 = 6.4624 - tlowmidlog;
	wvlmax = pow_dd(&c_b18, &d__1);
	if (effwvl[*ifil - 1] < wvlmax) {
	    goto L425;
	}
	tblog = d_lg10(&tb);
	tlowlog = d_lg10(&tlow);
	slope = (yy[ii - 1] - yylow) / (tblog - tlowlog);
	yy[ii - 1] = yylow + slope * (tlog - tlowlog);
	goto L4;
L425:
	tbrec = 1. / tb;
	tlowrec = 1. / tlow;
	slope = (yy[ii - 1] - yylow) / (tbrec - tlowrec);
	yy[ii - 1] = yylow + slope * (trec - tlowrec);
L4:
	ibin = ibinsav;
    }
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* Next, do a m-point Lagrange interpolation. */
    *xintlog = 0.;
    i__1 = m;
    for (ii = 1; ii <= i__1; ++ii) {
	xnum = 1.;
	denom = 1.;
	nj = k + ii - 1;
	i__2 = m;
	for (iij = 1; iij <= i__2; ++iij) {
	    njj = k + iij - 1;
	    if (ii == iij) {
		goto L500;
	    }
	    xnum *= gg - abung_1.glog[njj - 1];
	    denom *= abung_1.glog[nj - 1] - abung_1.glog[njj - 1];
L500:
	    ;
	}
	*xintlog += yy[ii - 1] * xnum / denom;
/* L501: */
    }
/* ccccccccccccccccccccccccccccccccccccccccccccccc */
/*  Check if a ramp function will be needed, or if we are */
/*  close to the border and need to interpolate between less */
/*  than 4 points. */
/* cccccccccccccccccccccccccccccccccccccccccccccccc */
    if (*g < 0.) {
	goto L7;
    }
    if (*g > 5.) {
	goto L9;
    }
    if (*t < 3500.) {
	goto L99;
    }
    if (pha[0] <= 1.) {
	goto L99;
    }
    if (ifreturn == 1) {
	goto L99;
    }
    if (j == 1) {
	goto L5;
    }
    if (pha[2] > 1.) {
	goto L5;
    }
    ++k;
    if (pha[1] > 1.) {
	goto L41;
    }
L42:
    if (k > 8) {
	m = 12 - k;
    }
    ifreturn = 1;
    goto L10;
L41:
    if (j < 10) {
	goto L5;
    }
    ++k;
    goto L42;
/* cccccccccccccccccccccccccccccccccccccccccccccccc */
L5:
    ib = icase + (j - 1) * 48;
    ib += -48;
    for (kik = 1; kik <= 2; ++kik) {
	ib += 48;
	for (ibin = 1; ibin <= 4; ++ibin) {
	    it = ib + (ibin - 1) * 12;
	    it1 = it + 1;
	    if (tt <= arrayleg_1.grand[it1 - 1]) {
		goto L620;
	    }
/* L619: */
	}
	--ibin;
L620:
	tb = arrayleg_1.grand[it - 1];
	if (tb != 0.) {
	    goto L67;
	}
	if (ibin == 1) {
	    ++ibin;
	}
	if (ibin == 4) {
	    --ibin;
	}
	it = ib + (ibin - 1) * 12;
	it1 = it + 1;
	tb = arrayleg_1.grand[it - 1];
L67:
	te = arrayleg_1.grand[it1 - 1];
	tte[kik - 1] = *t;
	if (*t > te) {
	    tte[kik - 1] = te;
	}
	ibb = ib + 1 + (ibin - 1) * 12;
	for (jj = 1; jj <= 10; ++jj) {
	    if (arrayleg_1.grand[ibb + jj - 1] != 0.) {
		goto L111;
	    }
	    goto L22;
L111:
	    ;
	}
L22:
	ma = jj - 1;
	pha[kik - 1] = (tte[kik - 1] - tb) / (te - tb);
	legendre_(&pha[kik - 1], pl, &ma);
	yy[kik - 1] = 0.;
	i__1 = ma;
	for (kk = 1; kk <= i__1; ++kk) {
	    kj = ibb + kk;
/* L33: */
	    yy[kik - 1] += pl[kk - 1] * arrayleg_1.grand[kj - 1];
	}
	ibin = ibinsav;
/* L61: */
    }
    if (*g > 5.) {
	goto L43;
    }
    if (*g < 0.) {
	goto L47;
    }
    slope = (yy[1] - yy[0]) * 2.;
    yy[0] = yy[1] + slope * (*g - abung_1.glog[j]);
    slope = (tte[1] - tte[0]) * 2.;
    te = tte[0] + slope * (*g - abung_1.glog[j - 1]);
    thigh = te * (fractol + 1.);
    if (*t > thigh) {
	goto L79;
    }
    planckint_(&thigh, ifil, &yyhigh, &dum);
    d__1 = te * thigh;
    thighmidlog = d_lg10(&d__1) * .5;
    d__1 = 6.4624 - thighmidlog;
    wvlmax = pow_dd(&c_b18, &d__1);
    if (effwvl[*ifil - 1] < wvlmax) {
	goto L426;
    }
    thighlog = d_lg10(&thigh);
    telog = d_lg10(&te);
    slope = (yyhigh - yy[0]) / (thighlog - telog);
    *xintlog = yyhigh + slope * (tlog - thighlog);
    goto L99;
L426:
    thighrec = 1. / thigh;
    terec = 1. / te;
    slope = (yyhigh - yy[0]) / (thighrec - terec);
    *xintlog = yyhigh + slope * (trec - thighrec);
    goto L99;
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
L43:
    yy[0] = yy[1];
    te = tte[1];
    planckint_(&thigh, ifil, &yyhigh, &dum);
    d__1 = te * thigh;
    thighmidlog = d_lg10(&d__1) * .5;
    d__1 = 6.4624 - thighmidlog;
    wvlmax = pow_dd(&c_b18, &d__1);
    if (effwvl[*ifil - 1] < wvlmax) {
	goto L427;
    }
    thighlog = d_lg10(&thigh);
    telog = d_lg10(&te);
    slope = (yyhigh - yy[0]) / (thighlog - telog);
    *xintlog = yyhigh + slope * (tlog - thighlog);
    goto L44;
L427:
    thighrec = 1. / thigh;
    terec = 1. / te;
    slope = (yyhigh - yy[0]) / (thighrec - terec);
    *xintlog = yyhigh + slope * (trec - thighrec);
    goto L44;
L47:
    te = tte[0];
    planckint_(&thigh, ifil, &yyhigh, &dum);
    d__1 = te * thigh;
    thighmidlog = d_lg10(&d__1) * .5;
    d__1 = 6.4624 - thighmidlog;
    wvlmax = pow_dd(&c_b18, &d__1);
    if (effwvl[*ifil - 1] < wvlmax) {
	goto L428;
    }
    thighlog = d_lg10(&thigh);
    telog = d_lg10(&te);
    slope = (yyhigh - yy[0]) / (thighlog - telog);
    *xintlog = yyhigh + slope * (tlog - thighlog);
    goto L63;
L428:
    thighrec = 1. / thigh;
    terec = 1. / te;
    slope = (yyhigh - yy[0]) / (thighrec - terec);
    *xintlog = yyhigh + slope * (trec - thighrec);
    goto L63;
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
L7:
    thigh = (fractol + 1.) * 6e3;
    if (*t > thigh) {
	goto L79;
    }
    if (pha[0] <= 1.) {
	goto L63;
    }
    goto L5;
L63:
    planckint_(t, ifil, &yylow, &dum);
    slope = (yylow - *xintlog) / glow;
    *xintlog = yylow + slope * (*g - glow);
    goto L99;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
L9:
    thigh = (fractol + 1.) * 5e4;
    if (*t > thigh) {
	goto L79;
    }
    if (*t > 5e4) {
	goto L52;
    }
L44:
    planckint_(t, ifil, &yyhigh, &dum);
    slope = (yyhigh - *xintlog) / (ghigh - 5.);
    *xintlog = yyhigh + slope * (*g - ghigh);
    goto L99;
L52:
    j = 10;
    goto L5;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
L66:
    atmmessages_1.message[atmmessages_1.komp + 5] = 1;
    planckint_(t, ifil, xintlog, xint);
    return 0;
L77:
    atmmessages_1.message[atmmessages_1.komp - 1] = 1;
    planckint_(t, ifil, xintlog, xint);
    return 0;
L78:
    atmmessages_1.message[atmmessages_1.komp + 1] = 1;
    planckint_(t, ifil, xintlog, xint);
    return 0;
L79:
    atmmessages_1.message[atmmessages_1.komp + 3] = 1;
    planckint_(t, ifil, xintlog, xint);
    return 0;
L99:
    *xint = pow_dd(&c_b18, xintlog);
    return 0;
} /* atmx_ */

/* Subroutine */ int bbl_(doublereal *rv, doublereal *grx, doublereal *gry, 
	doublereal *grz, doublereal *rvq, doublereal *grxq, doublereal *gryq, 
	doublereal *grzq, integer *mmsave, doublereal *fr1, doublereal *fr2, 
	doublereal *hld, doublereal *slump1, doublereal *slump2, doublereal *
	theta, doublereal *rho, doublereal *aa, doublereal *bb, doublereal *
	phsv, doublereal *pcsv, integer *n1, integer *n2, doublereal *f1, 
	doublereal *f2, doublereal *d__, doublereal *hlum, doublereal *clum, 
	doublereal *xh, doublereal *xc, doublereal *yh, doublereal *yc, 
	doublereal *gr1, doublereal *gr2, doublereal *wl, doublereal *sm1, 
	doublereal *sm2, doublereal *tpolh, doublereal *tpolc, doublereal *
	sbrh, doublereal *sbrc, doublereal *tavh, doublereal *tavc, 
	doublereal *alb1, doublereal *alb2, doublereal *xbol1, doublereal *
	xbol2, doublereal *ybol1, doublereal *ybol2, doublereal *phas, 
	doublereal *rm, doublereal *xincl, doublereal *hot, doublereal *cool, 
	doublereal *snth, doublereal *csth, doublereal *snfi, doublereal *
	csfi, doublereal *tld, doublereal *glump1, doublereal *glump2, 
	doublereal *xx1, doublereal *xx2, doublereal *yy1, doublereal *yy2, 
	doublereal *zz1, doublereal *zz2, doublereal *dint1, doublereal *
	dint2, doublereal *grv1, doublereal *grv2, doublereal *rftemp, 
	doublereal *rf1, doublereal *rf2, doublereal *csbt1, doublereal *
	csbt2, doublereal *gmag1, doublereal *gmag2, doublereal *glog1, 
	doublereal *glog2, doublereal *fbin1, doublereal *fbin2, doublereal *
	delv1, doublereal *delv2, doublereal *count1, doublereal *count2, 
	doublereal *delwl1, doublereal *delwl2, doublereal *resf1, doublereal 
	*resf2, doublereal *wl1, doublereal *wl2, doublereal *dvks1, 
	doublereal *dvks2, doublereal *tau1, doublereal *tau2, doublereal *
	emm1, doublereal *emm2, doublereal *hbarw1, doublereal *hbarw2, 
	doublereal *xcl, doublereal *ycl, doublereal *zcl, doublereal *rcl, 
	doublereal *op1, doublereal *fcl, doublereal *dens, doublereal *encl, 
	doublereal *edens, doublereal *taug, doublereal *emmg, doublereal *
	yskp, doublereal *zskp, integer *mode, integer *iband, integer *ifat1,
	 integer *ifat2, integer *ifphn, doublereal *tloc1, doublereal *tloc2,
	 doublereal *xinorm1, doublereal *xinorm2)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal u, ff, pi;
    static integer kp;
    static doublereal tr;
    extern /* Subroutine */ int lcr_(doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    );
    static doublereal dum, xlg;
    static integer nsp;
    static doublereal qfac, gpha, vfcc, psft, cosu, qfac1, xmean;
    extern /* Subroutine */ int light_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, integer *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *);
    static integer ifsmv;
    static doublereal twopi;
    extern /* Subroutine */ int kepler_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal somhot, somkul;

/*  Version of December 18, 2003 */
    /* Parameter adjustments */
    --xinorm2;
    --xinorm1;
    --tloc2;
    --tloc1;
    --zskp;
    --yskp;
    --emmg;
    --taug;
    --edens;
    --encl;
    --dens;
    --fcl;
    --op1;
    --rcl;
    --zcl;
    --ycl;
    --xcl;
    --hbarw2;
    --hbarw1;
    --emm2;
    --emm1;
    --tau2;
    --tau1;
    --dvks2;
    --dvks1;
    --wl2;
    --wl1;
    --resf2;
    --resf1;
    --delwl2;
    --delwl1;
    --count2;
    --count1;
    --delv2;
    --delv1;
    --fbin2;
    --fbin1;
    --glog2;
    --glog1;
    --gmag2;
    --gmag1;
    --csbt2;
    --csbt1;
    --rf2;
    --rf1;
    --rftemp;
    --grv2;
    --grv1;
    --zz2;
    --zz1;
    --yy2;
    --yy1;
    --xx2;
    --xx1;
    --glump2;
    --glump1;
    --tld;
    --csfi;
    --snfi;
    --csth;
    --snth;
    --bb;
    --aa;
    --rho;
    --theta;
    --slump2;
    --slump1;
    --hld;
    --fr2;
    --fr1;
    --mmsave;
    --grzq;
    --gryq;
    --grxq;
    --rvq;
    --grz;
    --gry;
    --grx;
    --rv;

    /* Function Body */
    pi = 3.141592653589793;
    twopi = pi + pi;
    prof2_1.ff1 = *f1;
    prof2_1.ff2 = *f2;
    qfac1 = 1. / (*rm + 1.);
    qfac = *rm * qfac1;
    if (*mode == 1) {
	*xc = *xh;
    }
    if (*mode == 1) {
	*yc = *yh;
    }
    psft = *phas - flvar_1.phperi;
L29:
    if (psft > 1.) {
	psft += -1.;
    }
    if (psft > 1.) {
	goto L29;
    }
L30:
    if (psft < 0.) {
	psft += 1.;
    }
    if (psft < 0.) {
	goto L30;
    }
    xmean = psft * twopi;
    tr = xmean;
    for (kp = 1; kp <= 2; ++kp) {
	nsp = nspt_1.nsp1 * (2 - kp) + nspt_1.nsp2 * (kp - 1);
	ff = *f1 * (doublereal) (2 - kp) + *f2 * (doublereal) (kp - 1);
	ifsmv = invar_1.ifsmv1 * (2 - kp) + invar_1.ifsmv2 * (kp - 1);
	if (ifsmv == 0) {
	    goto L60;
	}
	i__1 = nsp;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    xlg = spots_1.xlng[kp + (i__ << 1) - 3] + twopi * ff * (*phas - 
		    flvar_1.pconsc) - (tr - flvar_1.trc);
	    spots_1.snlng[kp + (i__ << 1) - 3] = sin(xlg);
	    spots_1.cslng[kp + (i__ << 1) - 3] = cos(xlg);
/* L61: */
	}
L60:
	;
    }
    if (eccen_1.e != 0.) {
	kepler_(&xmean, &eccen_1.e, &dum, &tr);
    }
    u = tr + ardot_1.perr;
    cosu = cos(u);
    gpha = u / twopi - .25;
L40:
    if (gpha < 0.) {
	gpha += 1.;
    }
    if (gpha < 0.) {
	goto L40;
    }
L50:
    if (gpha >= 1.) {
	gpha += -1.;
    }
    if (gpha >= 1.) {
	goto L50;
    }
    *d__ = flvar_1.ef / (eccen_1.e * cos(tr) + 1.);
    flvar_1.qfacd = qfac * *d__;
    if (invar_1.irte == 1) {
	goto L19;
    }
    lcr_(&rv[1], &grx[1], &gry[1], &grz[1], &rvq[1], &grxq[1], &gryq[1], &
	    grzq[1], &mmsave[1], &fr1[1], &fr2[1], &hld[1], &slump1[1], &
	    slump2[1], rm, phsv, pcsv, n1, n2, f1, f2, d__, hlum, clum, xh, 
	    xc, yh, yc, gr1, gr2, sm1, sm2, tpolh, tpolc, sbrh, sbrc, ifat1, 
	    ifat2, tavh, tavc, alb1, alb2, xbol1, xbol2, ybol1, ybol2, &
	    eccen_1.vol1, &eccen_1.vol2, &snth[1], &csth[1], &snfi[1], &csfi[
	    1], &tld[1], &glump1[1], &glump2[1], &xx1[1], &xx2[1], &yy1[1], &
	    yy2[1], &zz1[1], &zz2[1], dint1, dint2, &grv1[1], &grv2[1], &
	    csbt1[1], &csbt2[1], &rftemp[1], &rf1[1], &rf2[1], &gmag1[1], &
	    gmag2[1], &glog1[1], &glog2[1], mode, iband, &tloc1[1], &tloc2[1],
	     &xinorm1[1], &xinorm2[1]);
L19:
    prof2_1.vo1 = qfac * eccen_1.sini * (flvar_1.ecos + cosu) / flvar_1.efc + 
	    eccen_1.vgam;
    prof2_1.vo2 = -qfac1 * eccen_1.sini * (flvar_1.ecos + cosu) / flvar_1.efc 
	    + eccen_1.vgam;
    light_(&gpha, xincl, xh, xc, yh, yc, n1, n2, hot, cool, &rv[1], &grx[1], &
	    gry[1], &grz[1], &rvq[1], &grxq[1], &gryq[1], &grzq[1], &mmsave[1]
	    , &theta[1], &rho[1], &aa[1], &bb[1], &slump1[1], &slump2[1], &
	    somhot, &somkul, d__, wl, &snth[1], &csth[1], &snfi[1], &csfi[1], 
	    &tld[1], &gmag1[1], &gmag2[1], &glog1[1], &glog2[1], &fbin1[1], &
	    fbin2[1], &delv1[1], &delv2[1], &count1[1], &count2[1], &delwl1[1]
	    , &delwl2[1], &resf1[1], &resf2[1], &wl1[1], &wl2[1], &dvks1[1], &
	    dvks2[1], &tau1[1], &tau2[1], &emm1[1], &emm2[1], &hbarw1[1], &
	    hbarw2[1], &xcl[1], &ycl[1], &zcl[1], &rcl[1], &op1[1], &fcl[1], &
	    edens[1], &encl[1], &dens[1], &taug[1], &emmg[1], &yskp[1], &zskp[
	    1], iband, ifat1, ifat2, ifphn);
    flvar_1.vra1 = 0.;
    flvar_1.vra2 = 0.;
    if (*hot > 0.) {
	flvar_1.vra1 = *f1 * somhot / *hot;
    }
    if (*cool > 0.) {
	flvar_1.vra2 = *f2 * somkul / *cool;
    }
    flvar_1.vsum1 = prof2_1.vo1;
    flvar_1.vsum2 = prof2_1.vo2;
    if (invar_1.icor1 == 1) {
	flvar_1.vsum1 = prof2_1.vo1 + flvar_1.vra1;
    }
    if (invar_1.icor2 == 1) {
	flvar_1.vsum2 = prof2_1.vo2 + flvar_1.vra2;
    }
    vfcc = eccen_1.vfac / flvar_1.vunit;
    flvar_1.vkm1 = flvar_1.vsum1 * vfcc;
    flvar_1.vkm2 = flvar_1.vsum2 * vfcc;
    return 0;
} /* bbl_ */

/* Subroutine */ int binnum_(doublereal *x, integer *n, doublereal *y, 
	integer *j)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, mon;

/*  Version of January 7, 2002 */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    mon = 1;
    if (x[1] > x[2]) {
	mon = -1;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (mon == -1) {
	    goto L3;
	}
	if (*y <= x[i__]) {
	    goto L2;
	}
	goto L1;
L3:
	if (*y > x[i__]) {
	    goto L2;
	}
L1:
	;
    }
L2:
    *j = i__ - 1;
    return 0;
} /* binnum_ */

/* Subroutine */ int cloud_(doublereal *cosa, doublereal *cosb, doublereal *
	cosg, doublereal *x1, doublereal *y1, doublereal *z1, doublereal *xc, 
	doublereal *yc, doublereal *zc, doublereal *rr, doublereal *wl, 
	doublereal *op1, doublereal *opsf, doublereal *edens, doublereal *acm,
	 doublereal *en, doublereal *cmpd, doublereal *ri, doublereal *dx, 
	doublereal *dens, doublereal *tau)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *), exp(
	    doublereal);

    /* Local variables */
    static doublereal t, u, v, w, aa, bb, cc, xs1, xs2, xx1, xx2, yy1, yy2, 
	    zz1, zz2, dis, sqd, xss, sige, dubaa, xsfar, xxfar, yyfar, zzfar, 
	    dabcoa, dabcob, dtaudx, dtdxes, xsnear, xxnear, yynear, zznear;

/*  Version of January 9, 2002 */
    *dx = 0.;
    *tau = 0.;
    *ri = 1.;
    sige = 6.653e-25;
    dtdxes = sige * *edens;
/*  cosa can be zero, so an alternate path to the solution is needed */
    dabcoa = abs(*cosa);
    dabcob = abs(*cosb);
    if (dabcoa < dabcob) {
	goto L32;
    }
    w = *cosb / *cosa;
    v = *cosg / *cosa;
    u = *y1 - *yc - w * *x1;
    t = *z1 - *zc - v * *x1;
    aa = w * w + 1. + v * v;
    bb = (w * u + v * t - *xc) * 2.;
    cc = *xc * *xc + u * u + t * t - *rr * *rr;
    dubaa = aa + aa;
    dis = bb * bb - aa * 4. * cc;
    if (dis <= 0.) {
	return 0;
    }
    sqd = sqrt(dis);
    xx1 = (-bb + sqd) / dubaa;
    xx2 = (-bb - sqd) / dubaa;
    yy1 = w * (xx1 - *x1) + *y1;
    yy2 = w * (xx2 - *x1) + *y1;
    zz1 = v * (xx1 - *x1) + *z1;
    zz2 = v * (xx2 - *x1) + *z1;
    goto L39;
L32:
    w = *cosa / *cosb;
    v = *cosg / *cosb;
    u = *x1 - *xc - w * *y1;
    t = *z1 - *zc - v * *y1;
    aa = w * w + 1. + v * v;
    bb = (w * u + v * t - *yc) * 2.;
    cc = *yc * *yc + u * u + t * t - *rr * *rr;
    dubaa = aa + aa;
    dis = bb * bb - aa * 4. * cc;
    if (dis <= 0.) {
	return 0;
    }
    sqd = sqrt(dis);
    yy1 = (-bb + sqd) / dubaa;
    yy2 = (-bb - sqd) / dubaa;
    xx1 = w * (yy1 - *y1) + *x1;
    xx2 = w * (yy2 - *y1) + *x1;
    zz1 = v * (yy1 - *y1) + *z1;
    zz2 = v * (yy2 - *y1) + *z1;
L39:
    dis = bb * bb - aa * 4. * cc;
    if (dis <= 0.) {
	return 0;
    }
    sqd = sqrt(dis);
    xs1 = (xx1 - *cmpd) * *cosa + yy1 * *cosb + zz1 * *cosg;
    xs2 = (xx2 - *cmpd) * *cosa + yy2 * *cosb + zz2 * *cosg;
    xxnear = xx1;
    yynear = yy1;
    zznear = zz1;
    xxfar = xx2;
    yyfar = yy2;
    zzfar = zz2;
    xsnear = xs1;
    xsfar = xs2;
    if (xs1 > xs2) {
	goto L38;
    }
    xxnear = xx2;
    yynear = yy2;
    zznear = zz2;
    xxfar = xx1;
    yyfar = yy1;
    zzfar = zz1;
    xsnear = xs2;
    xsfar = xs1;
L38:
    xss = (*x1 - *cmpd) * *cosa + *y1 * *cosb + *z1 * *cosg;
    if (xss >= xsnear) {
	return 0;
    }
    if (xss <= xsfar) {
	goto L20;
    }
    xxfar = *x1;
    yyfar = *y1;
    zzfar = *z1;
L20:
    dtaudx = dtdxes + (*op1 * pow_dd(wl, en) + *opsf) * *dens;
/* Computing 2nd power */
    d__1 = xxnear - xxfar;
/* Computing 2nd power */
    d__2 = yynear - yyfar;
/* Computing 2nd power */
    d__3 = zznear - zzfar;
    *dx = sqrt(d__1 * d__1 + d__2 * d__2 + d__3 * d__3);
    *tau = *dx * dtaudx * *acm;
    *ri = exp(-(*tau));
    return 0;
} /* cloud_ */

/* Subroutine */ int conjph_(doublereal *ecc, doublereal *argper, doublereal *
	phzero, doublereal *trsc, doublereal *tric, doublereal *econsc, 
	doublereal *econic, doublereal *xmsc, doublereal *xmic, doublereal *
	pconsc, doublereal *pconic)
{
    /* Builtin functions */
    double acos(doublereal), sqrt(doublereal), tan(doublereal), atan(
	    doublereal), sin(doublereal);

    /* Local variables */
    static doublereal pi, pi32, pih, ecfac, twopi;

/*  Version of December 15, 2003 */

/*  Subroutine conjph computes the phases of superior and inferior conjunction */
/*    (pconsc and pconic) of star 1 */

    pi = acos(-1.);
    pih = pi * .5;
    pi32 = pi * 1.5;
    twopi = pi + pi;
    ecfac = sqrt((1. - *ecc) / (*ecc + 1.));

/*  sc in variable names (like trsc) means superior conjunction, and */
/*  ic means inferior conjunction (always for star 1). */

    *trsc = pih - *argper;
    *tric = pi32 - *argper;
    *econsc = atan(ecfac * tan(*trsc * .5)) * 2.;
    *econic = atan(ecfac * tan(*tric * .5)) * 2.;
    *xmsc = *econsc - *ecc * sin(*econsc);
    *xmic = *econic - *ecc * sin(*econic);
    *pconsc = (*xmsc + *argper) / twopi - .25 + *phzero;
    *pconic = (*xmic + *argper) / twopi - .25 + *phzero;
    return 0;
} /* conjph_ */

/* Subroutine */ int dc_(char *atmtab, char *pltab, integer *l3perc, integer *
	knobs, doublereal *indeps, doublereal *fluxes, doublereal *weights, 
	integer *nph, doublereal *delph, doublereal *corrs, doublereal *
	stdevs, doublereal *chi2s, doublereal *cormat, doublereal *ccla, 
	doublereal *cfval, doublereal *args, ftnlen atmtab_len, ftnlen 
	pltab_len)
{
    /* Initialized data */

    static char arad[10*4] = "POLE      " "POINT     " "SIDE      " "BACK   "
	    "   ";

    /* Format strings */
    static char fmt_15[] = "(1x,16(f11.5))";
    static char fmt_16[] = "(1x,18(f7.4))";
    static char fmt_67[] = "(20a4)";
    static char fmt_17[] = "(1x,22(f6.3))";
    static char fmt_19[] = "(1x,26(f5.2))";
    static char fmt_21[] = "(f27.16,f36.16,d22.6)";
    static char fmt_55[] = "(10(3x,d8.1))";
    static char fmt_56[] = "(10(1x,d7.1))";
    static char fmt_20[] = "(1x,2(4i1,1x),7i1,1x,4(5i1,1x),i1,1x,i1,1x,i1,d1"
	    "0.3)";
    static char fmt_101[] = "(\002 \002)";
    static char fmt_1[] = "(i3,i6,i6,i7,i7,i5,i5,i5,f15.6,d13.5,f10.5,f16.3,"
	    "f14.4)";
    static char fmt_701[] = "(4i2,4i4,f13.6,d12.5,f8.5,f9.3)";
    static char fmt_2[] = "(5(f14.5,f8.4,f12.2))";
    static char fmt_85[] = "(i3,2f10.5,4(1x,f6.3),f8.4,d10.3,i6,d14.5,f10.6)";
    static char fmt_18[] = "(i3,2f10.5,4f7.3,f8.4,d10.3,i2,d12.5,f10.6)";
    static char fmt_218[] = "(i3,2f10.5,4f7.3,d10.3,d12.5,f10.6)";
    static char fmt_37[] = "(1x,11f12.7)";
    static char fmt_137[] = "(1x,f11.7)";
    static char fmt_715[] = "(22x,\002Input-Output in F Format\002)";
    static char fmt_716[] = "(22x,\002Input-Output in D Format\002)";
    static char fmt_43[] = "(\002No.\002,2x,\002Curve\002,4x,\002Input Par"
	    "am.\002,8x,\002Correction\002,5x,\002Output Param.\002,4x,\002St"
	    "andard Deviation\002)";
    static char fmt_615[] = "(i2,i7,4f18.10)";
    static char fmt_616[] = "(i2,i7,4d18.10)";
    static char fmt_138[] = "(1x,\002SUM OF ABSOLUTE VALUES OF CHECKS IS\002"
	    ",1x,d12.6)";
    static char fmt_181[] = "(7x,\002NORMAL EQUATIONS\002)";
    static char fmt_183[] = "(7x,\002CORRELATION COEFFICIENTS\002)";
    static char fmt_184[] = "(7x,\002NORMAL EQUATIONS TIMES INVERSE\002)";
    static char fmt_185[] = "(1x,\002CHECK OF COMPUTED DEPENDENT VARIABLES F"
	    "ROM NORMAL EQUATIONS\002)";
    static char fmt_82[] = "(7x,\002UNWEIGHTED OBSERVATIONAL EQUATIONS\002)";
    static char fmt_83[] = "(7x,\002WEIGHTED OBSERVATIONAL EQUATIONS\002)";
    static char fmt_9[] = "(33x,\002OBSERVATIONS\002)";
    static char fmt_955[] = "(3(9x,\002phase   V rad   wt\002))";
    static char fmt_10[] = "(3(9x,\002phase   light   wt\002))";
    static char fmt_755[] = "(3(9x,\002JD      V rad   wt\002))";
    static char fmt_756[] = "(3(9x,\002JD      light   wt\002))";
    static char fmt_40[] = "(\002   Sum(W*Res**2) for input values       Sum"
	    "(W*Res**2) predicted          determinant\002)";
    static char fmt_11[] = "(1x,\002band\002,5x,\002L1\002,8x,\002L2     x1 "
	    "    x2     y1     y2   3rd lt\002,4x,\002opsf     NOISE    Sigm"
	    "a\002,6x,\002Wave L\002)";
    static char fmt_111[] = "(1x,\002band\002,5x,\002L1\002,8x,\002L2     x1"
	    "    x2    y1    y2     ops  f\002,7x,\002Sigma\002,6x,\002Wave "
	    "L\002)";
    static char fmt_12[] = "(\002MODE   IPB  IFAT1  IFAT2   N1   N2  N1L  "
	    "N2L\002,7x,\002Arg Per\002,5x,\002dperdt\002,7x,\002TH e\002,8x"
	    ",\002V unit(km/s)     V FAC\002)";
    static char fmt_206[] = "(f6.5,d13.6,2f11.4,f11.4,f10.3,2f8.3,i6,i9,f9.2"
	    ",i3)";
    static char fmt_205[] = "(\002  ecc\002,4x,\002S-M axis\002,7x,\002F1"
	    "\002,9x,\002F2\002,8x,\002V Gam\002,7x,\002INCL      G1      G"
	    "2\002,2x,\002Nspot 1\002,2x,\002Nspot 2\002,\002  [M/H] iab\002)";
    static char fmt_402[] = "(\002    DEL EC     DEL PER    DEL F1     DEL F"
	    "2     DEL PHS    DEL INCL    DEL G1     DEL G2     DEL T1     DE"
	    "L T2\002)";
    static char fmt_403[] = "(\002    DEL ALB1   DEL ALB2   DEL POT1   DEL P"
	    "OT2   DEL Q      DEL L1     DEL L2     DEL X1     DEL X2\002)";
    static char fmt_406[] = "(\002 ADJUSTMENT CONTROL INTEGERS; 1 SUPPRESSES"
	    " ADJUSTMENT, 0 ALLOWS ADJUSTMENT.\002)";
    static char fmt_702[] = "(f6.5,d13.6,2f10.4,f10.4,f9.3,2f7.3,f7.2)";
    static char fmt_706[] = "(f7.4,f8.4,2f7.3,3d13.6,4f7.3)";
    static char fmt_408[] = "(2f8.4,2f9.3,2d15.6,d13.6,4f9.3)";
    static char fmt_705[] = "(i1,1x,i1,1x,5i2)";
    static char fmt_54[] = "(\002     T1      T2\002,5x,\002Alb 1\002,4x,"
	    "\002Alb 2\002,9x,\002Pot 1\002,10x,\002Pot 2\002,8x,\002M2/M1  x"
	    "1(bolo) x2(bolo) y1(bolo) y2(bolo)\002)";
    static char fmt_707[] = "(\002    IFVC1   IFVC2   NLC   KO   KDISK   ISY"
	    "M   nppl\002)";
    static char fmt_917[] = "(\002nref\002,3x,\002mref\002,3x,\002ifsmv1\002"
	    ",3x,\002ifsmv2\002,3x,\002icor1\002,3x,\002icor2\002,3x,\002l"
	    "d\002)";
    static char fmt_708[] = "(8(4x,i3))";
    static char fmt_912[] = "(i3,i7,i8,i9,i8,i8,i7)";
    static char fmt_650[] = "(20x,\002RADII AND RELATED QUANTITIES (FROM INP"
	    "UT)\002)";
    static char fmt_651[] = "(5x,\002DOM1/DQ\002,5x,\002DOM2/DQ\002,5x,\002O"
	    "M1-Q CORR.\002,5x,\002OM2-Q CORR.\002,5x,\002OM1 S.D.\002,4x,"
	    "\002OM2 S.D.\002,4x,\002Q  S.D.\002)";
    static char fmt_652[] = "(1x,3f12.6,4x,f12.6,4x,3f12.6)";
    static char fmt_653[] = "(\002 COMPONENT\002,11x,\002R\002,9x,\002DR/DO"
	    "M\002,8x,\002DR/DQ\002,11x,\002S.D.\002)";
    static char fmt_654[] = "(2x,i1,1x,a6,4f14.6)";
    static char fmt_684[] = "(i2,4f13.5)";
    static char fmt_985[] = "(4f9.5)";
    static char fmt_983[] = "(1x,\002STAR  CO-LATITUDE  LONGITUDE  SPOT RADI"
	    "US  TEMP.FACTOR \002)";
    static char fmt_399[] = "(\002    DEL LAT    DEL LONG   DEL RAD    DEL T"
	    "EMPF  DEL LAT    del LONG   del RAD    del TEMPF\002)";
    static char fmt_60[] = "(4i3)";
    static char fmt_61[] = "(1x,4i6)";
    static char fmt_66[] = "(\002   STAR  SPOT   STAR  SPOT\002)";
    static char fmt_166[] = "(\002 SPOTS TO BE ADJUSTED\002)";
    static char fmt_440[] = "(\002 AS1=FIRST ADJUSTED SPOT\002)";
    static char fmt_441[] = "(\002 AS2=SECOND ADJUSTED SPOT\002)";
    static char fmt_405[] = "(\002 ORDER OF PARAMETERS IS AS FOLLOWS:\002)";
    static char fmt_1440[] = "(\002  (1) - AS1 LATITUDE\002)";
    static char fmt_1441[] = "(\002  (2) - AS1 LONGITUDE\002)";
    static char fmt_1442[] = "(\002  (3) - AS1 ANGULAR RADIUS\002)";
    static char fmt_1443[] = "(\002  (4) - AS1 TEMPERATURE FACTOR\002)";
    static char fmt_1444[] = "(\002  (5) - AS2 LATITUDE\002)";
    static char fmt_1445[] = "(\002  (6) - AS2 LONGITUDE\002)";
    static char fmt_1446[] = "(\002  (7) - AS2 ANGULAR RADIUS\002)";
    static char fmt_1447[] = "(\002  (8) - AS2 TEMPERATURE FACTOR\002)";
    static char fmt_1448[] = "(\002  (9) - A=ORBITAL SEMI-MAJOR AXIS\002)";
    static char fmt_1449[] = "(\002 (10) - E=ORBITAL ECCENTRICITY\002)";
    static char fmt_1450[] = "(\002 (11) - PERR0=ARGUMENT of PERIASTRON at t"
	    "ime HJD0\002)";
    static char fmt_1451[] = "(\002 (12) - F1=STAR 1 ROTATION PARAMETER\002)";
    static char fmt_1452[] = "(\002 (13) - F2=STAR 2 ROTATION PARAMETER\002)";
    static char fmt_1453[] = "(\002 (14) - PHASE SHIFT= PHASE OF PRIMARY CON"
	    "JUNCTION\002)";
    static char fmt_1454[] = "(\002 (15) - VGAM=SYSTEMIC RADIAL VELOCITY\002)"
	    ;
    static char fmt_1455[] = "(\002 (16) - INCL=ORBITAL INCLINATION\002)";
    static char fmt_1456[] = "(\002 (17) - g1=STAR 1 GRAVITY DARKENING EXPON"
	    "ENT\002)";
    static char fmt_1457[] = "(\002 (18) - g2=STAR 2 GRAVITY DARKENING EXPON"
	    "ENT\002)";
    static char fmt_1458[] = "(\002 (19) - T1=STAR 1 AVERAGE SURFACE TEMPERA"
	    "TURE\002)";
    static char fmt_1459[] = "(\002 (20) - T2=STAR 2 AVERAGE SURFACE TEMPERA"
	    "TURE\002)";
    static char fmt_1460[] = "(\002 (21) - ALB1=STAR 1 BOLOMETRIC ALBEDO\002)"
	    ;
    static char fmt_1461[] = "(\002 (22) - ALB2=STAR 2 BOLOMETRIC ALBEDO\002)"
	    ;
    static char fmt_1462[] = "(\002 (23) - POT1=STAR 1 SURFACE POTENTIAL\002)"
	    ;
    static char fmt_1463[] = "(\002 (24) - POT2=STAR 2 SURFACE POTENTIAL\002)"
	    ;
    static char fmt_1464[] = "(\002 (25) - Q=MASS RATIO (STAR 2/STAR 1)\002)";
    static char fmt_1470[] = "(\002 (26) - HJD0= Hel. JD reference time\002)";
    static char fmt_1471[] = "(\002 (27) - PERIOD= orbital period\002)";
    static char fmt_1472[] = "(\002 (28) - DPDT= time derivative of orbital "
	    "period\002)";
    static char fmt_1473[] = "(\002 (29) - DPERDT= time derivative of argume"
	    "nt of periastron\002)";
    static char fmt_1474[] = "(\002 (30) - unused channel reserved for futur"
	    "e expansion\002)";
    static char fmt_1465[] = "(\002 (31) - L1=STAR 1 RELATIVE MONOCHROMATIC "
	    "LUMINOSITY\002)";
    static char fmt_1466[] = "(\002 (32) - L2=STAR 2 RELATIVE MONOCHROMATIC "
	    "LUMINOSITY\002)";
    static char fmt_1467[] = "(\002 (33) - X1=STAR 1 LIMB DARKENING COEFFICI"
	    "ENT\002)";
    static char fmt_1468[] = "(\002 (34) - X2=STAR 2 LIMB DARKENING COEFFICI"
	    "ENT\002)";
    static char fmt_1469[] = "(\002 (35) - el3=third light\002)";
    static char fmt_119[] = "(1x,i6,i13,f18.8)";
    static char fmt_159[] = "(\002 Sums of squares of residuals for separate"
	    " curves, including only individual weights\002)";
    static char fmt_169[] = "(\002    Curve     No. of obs.   Sum of square"
	    "s\002)";
    static char fmt_1063[] = "(3f9.4,f7.4,d11.4,f9.4,d11.3,f9.4,f7.3)";
    static char fmt_64[] = "(3f10.4,f9.4,d12.4,f10.4,d12.4,f9.4,f9.3,d12.4)";
    static char fmt_69[] = "(\002      xcl       ycl       zcl      rcl     "
	    "  op1         fcl        ne       mu e      encl     dens\002)";
    static char fmt_170[] = "(i3,f17.6,d18.10,d14.6,f10.4,f11.5,i5)";
    static char fmt_649[] = "(i1,f15.6,d17.10,d14.6,f10.4)";
    static char fmt_171[] = "(\002JDPHS\002,5x,\002J.D. zero\002,7x,\002Peri"
	    "od\002,11x,\002dPdt\002,6x,\002Ph. shift\002)";
    static char fmt_911[] = "(7(i1,1x))";
    static char fmt_840[] = "(\002Do not try to adjust the ephemeris or any "
	    "time derivative parameters\002,\002when JDPHS = 2\002)";
    static char fmt_839[] = "(\002Ordinarily one should not try to adjust bo"
	    "th PSHIFT and\002,\002 HJD0. They are perfectly correlated if th"
	    "e period is constant\002,\002 and extremely highly correlated if"
	    " the period is not constant\002)";
    static char fmt_283[] = "(\002log g below ramp range for at least one po"
	    "int\002,\002 on star\002,i2,\002, black body applied locally."
	    "\002)";
    static char fmt_284[] = "(\002log g above ramp range for at least one po"
	    "int\002,\002 on star\002,i2,\002, black body applied locally."
	    "\002)";
    static char fmt_285[] = "(\002T above ramp range for at least one\002"
	    ",\002 point on star\002,i2,\002, black body applied locally.\002)"
	    ;
    static char fmt_286[] = "(\002T below ramp range for at least one poin"
	    "t\002,\002 on star\002,i2,\002, black body applied locally.\002)";
    static char fmt_287[] = "(\002Input [M/H] = \002,f6.3,\002 is not a valu"
	    "e recognized by \002,\002the program. Replaced by \002,f5.2)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5, i__6;
    doublereal d__1, d__2, d__3, d__4;
    olist o__1;
    cllist cl__1;
    alist al__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsle(cilist *), do_lio(integer *, integer *, 
	    char *, ftnlen), e_rsle(void), f_clos(cllist *);
    double acos(doublereal);
    integer s_wsfe(cilist *), e_wsfe(void), s_rsfe(cilist *), do_fio(integer *
	    , char *, ftnlen), e_rsfe(void);
    double sin(doublereal), cos(doublereal);
    integer s_wsle(cilist *), e_wsle(void);
    double log(doublereal);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer f_rew(alist *);
    double sqrt(doublereal), pow_di(doublereal *, integer *);

    /* Local variables */
    static doublereal brac2, dphpd;
    static integer icv, icvp, nbs, jstart, jstop;
    static doublereal resq;
    static integer iww, jres, nobbs, nois;
    static doublereal rootwt;
    static integer lob;
    extern /* Subroutine */ int square_(doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *);
    static doublereal deter;
    static integer msq, no1, no2, nrm, irm;
    static doublereal coro1, coro2, corq;
    static integer ijm, ijq;
    static doublereal co1q, co2q;
    extern /* Subroutine */ int dgmprd_(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *);
    static doublereal ansch;
    static integer int__, idi;
    static doublereal err;
    static integer iout, kpar, imax, kurv, kcurv, ipar;
    static doublereal parout, hlum, clum;
    static integer icla;
    static doublereal ressq;
    static integer jst;
    static doublereal do1, do2, coq, ome, dom;
    extern /* Subroutine */ int romq_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *);
    static doublereal drdo, drdq, dodq, dr, do2dq, do1dq, d__, e, f;
    static integer i__, j;
    static doublereal r__, s, v[50], a1, a2, f1, f2, g1, g2;
    static integer j4, n1, n2, j7, j8, j5;
    static doublereal t1, t2;
    static integer j6, i9;
    static doublereal x1, x2, y1, y2, aa[20], bb[20];
    static integer ib;
    static doublereal bl[50000], cl, cn[2500], em, br[50000];
    static integer ii;
    static doublereal sd[50];
    static integer ll[50];
    static doublereal pi;
    static integer mm[50], ni, ko;
    static doublereal po[2], rm;
    static integer ns, is, kp, in, ix, ks, ny;
    static doublereal rv[33202], tt, dl, wt[50000];
    static integer ih, il;
    static doublereal hl, xr;
    static integer iw, jf, kc, ke, kx, jr, jx, jm, jq, jt, im;
    static doublereal dq;
    static integer ib1;
    static doublereal ff1, ff2;
    static integer kd, lc1;
    static doublereal th, fi, en0, el3;
    static integer m1h, m2h;
    static doublereal fr1[33202], fr2[33202], rf1[33202], rf2[33202], x1a[50],
	     x2a[50], y1a[50], op1[100], y2a[50], wl1[1], wl2[1];
    static integer n1l, n2l;
    static doublereal gr1, gr2, xx1[33202], xx2[33202], yy1[33202], yy2[33202]
	    , zz1[33202], zz2[33202];
    static integer nn1, mm1, mm2, mm3, mm4, m1l, m2l, iab;
    static doublereal cla[50], clc[50], ccl[50], cnc[2500], fcl[100], hla[50],
	     del[35], hld[33202], cnn[2500];
    static integer kep[35];
    static doublereal rcl[100];
    static integer ifm, ifr;
    static doublereal obs[2500000], wla[50], xcl[100], ycl[100], zcl[100], 
	    rho[800], erv[33202];
    static integer nlc;
    static doublereal the, grx[33202], gry[33202], grz[33202];
    static integer low[35], nvc, irx;
    static doublereal dif, out[50], rvq[33202];
    static integer mod;
    static doublereal srv[33202], xld, omd, rmr, smd, alb1, alb2, dap, vl1, 
	    dif1, el3a[50], dif2, vl2, php;
    extern /* Subroutine */ int bbl_(doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal sm1, sm2, hot, erf1[33202], erf2[33202], efr1[33202], 
	    efr2[33202], emm1[1], emm2[1], p1ap, p2ap;
    static integer lcv, ijp, ima, mat;
    static doublereal tau1[1], srf1[33202], srf2[33202], sfr1[33202], sfr2[
	    33202], grv1[33202], grv2[33202], tau2[1], exx1[33202], exx2[
	    33202], eyy1[33202], eyy2[33202], ezz1[33202], ezz2[33202];
    static integer ktr;
    static doublereal sxx1[33202], sxx2[33202], syy1[33202], syy2[33202], 
	    szz1[33202], szz2[33202];
    static integer ibef, kss;
    static doublereal vc1, vc2, dlif[35];
    static integer ifap;
    static doublereal encl[100];
    static integer ist;
    static doublereal para[280];
    static integer keep[36];
    static doublereal phjd[50000], hold[2500000], xfia[4], dens[100], phas[
	    50000], tldh[66404], emmg[1], tldl[66404], omcr[2], taug[1], xtha[
	    4], egrx[33202], egry[33202], egrz[33202], ervl[33202], xlat[200]	
	    /* was [2][100] */, ervq[33202], xmue[100], flux[50000], grxq[
	    33202], gryq[33202], grzq[33202], sgrx[33202], sgry[33202], sgrz[
	    33202], srvl[33202], yskp[1], zskp[1], srvq[33202], gmag1[33202], 
	    gmag2[33202], ecsb1[33202], ecsb2[33202], egmg1[33202], egmg2[
	    33202], fbin1[1], fbin2[1], eglm1[33202], eglm2[33202], glog1[
	    33202], glog2[33202], scsb1[33202], csbt1[33202], csbt2[33202], 
	    sgmg1[33202], sgmg2[33202], scsb2[33202], elmp1[33202], tloc1[
	    33202], tloc2[33202], sglm1[33202], sglm2[33202], egrv1[33202], 
	    srf1l[33202], srf2l[33202], elmp2[33202], egrv2[33202], erf1l[
	    33202], slmp1[33202], slmp2[33202], erf2l[33202], sfr1l[33202], 
	    efr1l[33202], exx1l[33202], sgrv1[33202], sgrv2[33202], eyy1l[
	    33202], ezz1l[33202], exx2l[33202], eyy2l[33202], ezz2l[33202], 
	    sfr2l[33202], efr2l[33202], delv1[1], delv2[1];
    static integer iband[50];
    static doublereal dfdap[50000], sxx1l[33202], sxx2l[33202], syy1l[33202], 
	    syy2l[33202], szz1l[33202], szz2l[33202], dfdph[50000], resf1[1], 
	    resf2[1], dvks1[1], dvks2[1], csfih[66404], edens[100], etldh[
	    66404], sigma[50], etldl[66404], csfil[66404], snfih[66404], 
	    opsfa[50], radsp[200]	/* was [2][100] */, csthh[400], snfil[
	    66404];
    static integer noise[50];
    static doublereal stldh[66404], egrxl[33202], egryl[33202], egrzl[33202], 
	    stldl[66404], snthh[400], egrxq[33202], egryq[33202], egrzq[33202]
	    , ervql[33202], xlong[200]	/* was [2][100] */, temsp[200]	/* 
	    was [2][100] */, snthl[400], csthl[400], sgrxl[33202], sgryl[
	    33202], sgrzl[33202], theta[800], cnout[2500], sgrxq[33202], 
	    sgryq[33202], sgrzq[33202], srvql[33202], ecsb1l[33202], ecsb2l[
	    33202], egmg1l[33202], egmg2l[33202], eglm1l[33202], eglm2l[33202]
	    , hbarw1[1], hbarw2[1], scsb1l[33202], scsb2l[33202], sgmg1l[
	    33202], sgmg2l[33202], elmp1l[33202], elmp2l[33202], delwl1[1], 
	    sglm1l[33202], sglm2l[33202], egrv1l[33202], egrv2l[33202], 
	    delwl2[1], glump1[33202], glump2[33202], slmp1l[33202], slmp2l[
	    33202], count1[1], count2[1], sgrv1l[33202], sgrv2l[33202], 
	    slump1[33202], slump2[33202];
    static integer mmsavh[404], nshift[36];
    static doublereal rftemp[33202];
    static integer mmsavl[404];
    static doublereal toldis, egrxql[33202], egryql[33202], egrzql[33202];
    static integer ikks, jkks, immsav, ifder;
    static doublereal xlamda;
    static integer kspa;
    static doublereal sgrxql[33202], sgryql[33202], sgrzql[33202];
    static integer nspa, kspb, nspb, ifvc1, ifvc2, kdisk, isym, nppl;
    static doublereal dpdt, pshift;
    static integer mode, ifat1, ifat2;
    static doublereal perr0, xincl, abunin, tavh, tavc, phsv, pcsv, xbol1, 
	    xbol2, ybol1, ybol2;
    extern /* Subroutine */ int sincos_(integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    ;
    static doublereal dint1, dint2;
    static integer mtlh, mtll, nlvc, nvcp, ifphi, kosq, nstot, ipara;
    extern /* Subroutine */ int binnum_(doublereal *, integer *, doublereal *,
	     integer *), modlog_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), ellone_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal xldd;
    extern /* Subroutine */ int volume_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *);
    static doublereal xinorm1[33202], xinorm2[33202], summd, poth, potc, 
	    tpolh, tpolc, sbrh, sbrc, cool;
    static integer nspot, ifirst, last, nobs;
    extern /* Subroutine */ int jdph_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal xjddum;
    static integer matrix, ncoeff, nmat, ncof, iobs, ksmax, kssmax;
    static doublereal elit;
    static integer isp;
    static doublereal dtime;
    static integer ksr, lcf, kpct1, kpct2, ksp, ict;
    static doublereal sign;
    static integer iss;
    static doublereal svol1, svol2, ssum1, ssum2, ssm1, ssm2;
    static integer ire;
    static doublereal evol1, evol2, esum1, esum2, esm1, esm2, evol1l, evol2l, 
	    esum1l, esum2l, esm1l, esm2l, svol1l, svol2l, ssum1l, ssum2l, 
	    ssm1l, ssm2l, dels, xlt, xinc, rmass;
    static integer iph;
    static doublereal phasin, tph, tpc, hotr, coolr;
    static integer ihl, ihh;
    static doublereal htt, xlr, xnr;
    static integer khkeep;
    static doublereal brac, dis;

    /* Fortran I/O blocks */
    static cilist io___114 = { 0, 22, 0, 0, 0 };
    static cilist io___115 = { 0, 23, 0, 0, 0 };
    static cilist io___131 = { 0, 16, 0, fmt_405, 0 };
    static cilist io___132 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___133 = { 0, 16, 0, fmt_440, 0 };
    static cilist io___134 = { 0, 16, 0, fmt_441, 0 };
    static cilist io___135 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___136 = { 0, 16, 0, fmt_1440, 0 };
    static cilist io___137 = { 0, 16, 0, fmt_1441, 0 };
    static cilist io___138 = { 0, 16, 0, fmt_1442, 0 };
    static cilist io___139 = { 0, 16, 0, fmt_1443, 0 };
    static cilist io___140 = { 0, 16, 0, fmt_1444, 0 };
    static cilist io___141 = { 0, 16, 0, fmt_1445, 0 };
    static cilist io___142 = { 0, 16, 0, fmt_1446, 0 };
    static cilist io___143 = { 0, 16, 0, fmt_1447, 0 };
    static cilist io___144 = { 0, 16, 0, fmt_1448, 0 };
    static cilist io___145 = { 0, 16, 0, fmt_1449, 0 };
    static cilist io___146 = { 0, 16, 0, fmt_1450, 0 };
    static cilist io___147 = { 0, 16, 0, fmt_1451, 0 };
    static cilist io___148 = { 0, 16, 0, fmt_1452, 0 };
    static cilist io___149 = { 0, 16, 0, fmt_1453, 0 };
    static cilist io___150 = { 0, 16, 0, fmt_1454, 0 };
    static cilist io___151 = { 0, 16, 0, fmt_1455, 0 };
    static cilist io___152 = { 0, 16, 0, fmt_1456, 0 };
    static cilist io___153 = { 0, 16, 0, fmt_1457, 0 };
    static cilist io___154 = { 0, 16, 0, fmt_1458, 0 };
    static cilist io___155 = { 0, 16, 0, fmt_1459, 0 };
    static cilist io___156 = { 0, 16, 0, fmt_1460, 0 };
    static cilist io___157 = { 0, 16, 0, fmt_1461, 0 };
    static cilist io___158 = { 0, 16, 0, fmt_1462, 0 };
    static cilist io___159 = { 0, 16, 0, fmt_1463, 0 };
    static cilist io___160 = { 0, 16, 0, fmt_1464, 0 };
    static cilist io___161 = { 0, 16, 0, fmt_1470, 0 };
    static cilist io___162 = { 0, 16, 0, fmt_1471, 0 };
    static cilist io___163 = { 0, 16, 0, fmt_1472, 0 };
    static cilist io___164 = { 0, 16, 0, fmt_1473, 0 };
    static cilist io___165 = { 0, 16, 0, fmt_1474, 0 };
    static cilist io___166 = { 0, 16, 0, fmt_1465, 0 };
    static cilist io___167 = { 0, 16, 0, fmt_1466, 0 };
    static cilist io___168 = { 0, 16, 0, fmt_1467, 0 };
    static cilist io___169 = { 0, 16, 0, fmt_1468, 0 };
    static cilist io___170 = { 0, 16, 0, fmt_1469, 0 };
    static cilist io___171 = { 0, 15, 0, fmt_56, 0 };
    static cilist io___174 = { 0, 15, 0, fmt_56, 0 };
    static cilist io___175 = { 0, 15, 0, fmt_56, 0 };
    static cilist io___176 = { 0, 15, 0, fmt_20, 0 };
    static cilist io___182 = { 0, 15, 0, fmt_60, 0 };
    static cilist io___187 = { 0, 15, 0, fmt_705, 0 };
    static cilist io___195 = { 0, 15, 0, fmt_911, 0 };
    static cilist io___196 = { 0, 15, 0, fmt_649, 0 };
    static cilist io___199 = { 0, 16, 0, fmt_840, 0 };
    static cilist io___200 = { 0, 16, 0, fmt_840, 0 };
    static cilist io___201 = { 0, 16, 0, fmt_840, 0 };
    static cilist io___202 = { 0, 16, 0, fmt_839, 0 };
    static cilist io___203 = { 0, 15, 0, fmt_701, 0 };
    static cilist io___213 = { 0, 15, 0, fmt_702, 0 };
    static cilist io___221 = { 0, 15, 0, fmt_706, 0 };
    static cilist io___264 = { 0, 15, 0, fmt_218, 0 };
    static cilist io___275 = { 0, 15, 0, fmt_18, 0 };
    static cilist io___278 = { 0, 15, 0, fmt_985, 0 };
    static cilist io___284 = { 0, 15, 0, fmt_1063, 0 };
    static cilist io___303 = { 0, 16, 0, fmt_287, 0 };
    static cilist io___395 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___396 = { 0, 16, 0, fmt_399, 0 };
    static cilist io___397 = { 0, 16, 0, fmt_55, 0 };
    static cilist io___398 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___399 = { 0, 16, 0, fmt_402, 0 };
    static cilist io___400 = { 0, 16, 0, fmt_55, 0 };
    static cilist io___401 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___402 = { 0, 16, 0, fmt_403, 0 };
    static cilist io___403 = { 0, 16, 0, fmt_55, 0 };
    static cilist io___404 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___405 = { 0, 16, 0, fmt_406, 0 };
    static cilist io___406 = { 0, 16, 0, fmt_20, 0 };
    static cilist io___407 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___408 = { 0, 16, 0, fmt_166, 0 };
    static cilist io___409 = { 0, 16, 0, fmt_66, 0 };
    static cilist io___410 = { 0, 16, 0, fmt_61, 0 };
    static cilist io___411 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___412 = { 0, 16, 0, fmt_707, 0 };
    static cilist io___413 = { 0, 16, 0, fmt_708, 0 };
    static cilist io___414 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___415 = { 0, 16, 0, fmt_917, 0 };
    static cilist io___416 = { 0, 16, 0, fmt_912, 0 };
    static cilist io___417 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___418 = { 0, 16, 0, fmt_171, 0 };
    static cilist io___419 = { 0, 16, 0, fmt_170, 0 };
    static cilist io___420 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___421 = { 0, 16, 0, fmt_12, 0 };
    static cilist io___422 = { 0, 16, 0, fmt_1, 0 };
    static cilist io___423 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___424 = { 0, 16, 0, fmt_205, 0 };
    static cilist io___425 = { 0, 16, 0, fmt_206, 0 };
    static cilist io___426 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___427 = { 0, 16, 0, fmt_54, 0 };
    static cilist io___428 = { 0, 16, 0, fmt_408, 0 };
    static cilist io___429 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___430 = { 0, 16, 0, fmt_111, 0 };
    static cilist io___431 = { 0, 16, 0, fmt_218, 0 };
    static cilist io___432 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___433 = { 0, 16, 0, fmt_11, 0 };
    static cilist io___435 = { 0, 16, 0, fmt_85, 0 };
    static cilist io___436 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___437 = { 0, 16, 0, fmt_983, 0 };
    static cilist io___439 = { 0, 16, 0, fmt_684, 0 };
    static cilist io___440 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___441 = { 0, 16, 0, fmt_69, 0 };
    static cilist io___442 = { 0, 16, 0, fmt_64, 0 };
    static cilist io___443 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___444 = { 0, 16, 0, 0, 0 };
    static cilist io___445 = { 0, 16, 0, 0, 0 };
    static cilist io___446 = { 0, 16, 0, 0, 0 };
    static cilist io___447 = { 0, 16, 0, 0, 0 };
    static cilist io___448 = { 0, 16, 0, 0, 0 };
    static cilist io___449 = { 0, 16, 0, 0, 0 };
    static cilist io___450 = { 0, 16, 0, 0, 0 };
    static cilist io___451 = { 0, 16, 0, 0, 0 };
    static cilist io___452 = { 0, 16, 0, 0, 0 };
    static cilist io___453 = { 0, 16, 0, 0, 0 };
    static cilist io___454 = { 0, 16, 0, 0, 0 };
    static cilist io___455 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___456 = { 0, 16, 0, fmt_9, 0 };
    static cilist io___458 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___459 = { 0, 16, 0, fmt_955, 0 };
    static cilist io___460 = { 0, 16, 0, fmt_10, 0 };
    static cilist io___461 = { 0, 16, 0, fmt_755, 0 };
    static cilist io___462 = { 0, 16, 0, fmt_756, 0 };
    static cilist io___465 = { 0, 15, 0, fmt_2, 0 };
    static cilist io___470 = { 0, 16, 0, fmt_2, 0 };
    static cilist io___694 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___695 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___696 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___697 = { 0, 16, 0, fmt_159, 0 };
    static cilist io___698 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___699 = { 0, 16, 0, fmt_169, 0 };
    static cilist io___709 = { 0, 16, 0, fmt_119, 0 };
    static cilist io___710 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___711 = { 0, 16, 0, fmt_283, 0 };
    static cilist io___712 = { 0, 16, 0, fmt_284, 0 };
    static cilist io___713 = { 0, 16, 0, fmt_285, 0 };
    static cilist io___714 = { 0, 16, 0, fmt_286, 0 };
    static cilist io___715 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___717 = { 0, 9, 0, fmt_67, 0 };
    static cilist io___718 = { 0, 15, 0, fmt_20, 0 };
    static cilist io___724 = { 0, 16, 0, fmt_20, 0 };
    static cilist io___725 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___726 = { 0, 16, 0, fmt_82, 0 };
    static cilist io___727 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___728 = { 0, 16, 0, fmt_15, 0 };
    static cilist io___729 = { 0, 16, 0, fmt_16, 0 };
    static cilist io___730 = { 0, 16, 0, fmt_17, 0 };
    static cilist io___731 = { 0, 16, 0, fmt_19, 0 };
    static cilist io___732 = { 0, 9, 0, fmt_67, 0 };
    static cilist io___733 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___737 = { 0, 16, 0, fmt_83, 0 };
    static cilist io___738 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___739 = { 0, 16, 0, fmt_15, 0 };
    static cilist io___740 = { 0, 16, 0, fmt_16, 0 };
    static cilist io___741 = { 0, 16, 0, fmt_17, 0 };
    static cilist io___742 = { 0, 16, 0, fmt_19, 0 };
    static cilist io___755 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___756 = { 0, 16, 0, fmt_181, 0 };
    static cilist io___757 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___759 = { 0, 16, 0, fmt_37, 0 };
    static cilist io___761 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___762 = { 0, 16, 0, fmt_183, 0 };
    static cilist io___763 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___779 = { 0, 16, 0, fmt_37, 0 };
    static cilist io___781 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___782 = { 0, 16, 0, fmt_184, 0 };
    static cilist io___783 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___786 = { 0, 16, 0, fmt_37, 0 };
    static cilist io___788 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___789 = { 0, 16, 0, fmt_185, 0 };
    static cilist io___790 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___798 = { 0, 16, 0, fmt_137, 0 };
    static cilist io___800 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___801 = { 0, 16, 0, fmt_138, 0 };
    static cilist io___802 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___803 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___804 = { 0, 16, 0, fmt_715, 0 };
    static cilist io___805 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___806 = { 0, 16, 0, fmt_43, 0 };
    static cilist io___814 = { 0, 16, 0, fmt_615, 0 };
    static cilist io___815 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___816 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___817 = { 0, 16, 0, fmt_716, 0 };
    static cilist io___818 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___819 = { 0, 16, 0, fmt_43, 0 };
    static cilist io___822 = { 0, 16, 0, fmt_616, 0 };
    static cilist io___824 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___827 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___828 = { 0, 16, 0, fmt_40, 0 };
    static cilist io___829 = { 0, 16, 0, fmt_21, 0 };
    static cilist io___830 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___831 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___832 = { 0, 16, 0, fmt_650, 0 };
    static cilist io___833 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___834 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___835 = { 0, 16, 0, fmt_653, 0 };
    static cilist io___836 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___852 = { 0, 16, 0, fmt_654, 0 };
    static cilist io___855 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___856 = { 0, 16, 0, fmt_101, 0 };
    static cilist io___857 = { 0, 16, 0, fmt_651, 0 };
    static cilist io___858 = { 0, 16, 0, fmt_652, 0 };


/*  This is the Differential Corrections Main Program. */

/*  Version of May 24, 2007 */

/*     PARAMETER NUMBER 9 IS A, THE RELATIVE ORBITAL SEMI-MAJOR AXIS, IF */
/*     SIMULTANEOUS LIGHT AND VELOCITY SOLUTIONS ARE BEING DONE. HOWEVER, */
/*     IF ONLY VELOCITY CURVES ARE BEING SOLVED, PARAMETER 9 WILL */
/*     EFFECTIVELY BE A*SIN(I), PROVIDED AN INCLINATION OF 90 DEG. IS */
/*     ENTERED. IN SOME RARE SITUATIONS IT MAY BE POSSIBLE TO */
/*     FIND A AND I SEPARATELY from velocities only. THIS COULD BE */
/*     THE CASE IF THE VELOCITY PROXIMITY EFFECTS ARE IMPORTANT. */

/*     OTHER PROGRAM UNITS: ORBITAL S-M AXIS IN SOLAR RADII (6.957d5 KM), */
/*     PERIOD IN DAYS, PHASE IN 2 PI RADIANS, SYSTEMIC VELOCITY AND */
/*     THIRD LIGHT IN SAME UNITS AS VELOCITY AND LIGHT OBSERVATIONS, */
/*     INCLINATION IN DEGREES, TEMPERATURES IN 10000K., SPOT LATITUDES */
/*     IN RADIANS (0=NORTH POLE, Pi=SOUTH POLE), SPOT LONGITUDES */
/*     IN RADIANS (0=LINE OF CENTERS MERIDIAN, INCREASING COUNTER- */
/*     CLOCKWISE AS SEEN FROM NORTH POLE TO 2 Pi), */
/*     SPOT ANGULAR RADII IN RADIANS. SPOT TEMPERATURE FACTOR IS */
/*     DIMENSIONLESS. */


/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*                      ARRAY DIMENSIONING WRAPPER */
/*                            March 6, 2007 */

/*     The following parameters are maximum array sizes. */
/*     There is no need to change any dimension numbers except these */
/*     in order to accomodate finer grids. */

/*        Nmax    ..    maximum grid fineness parameters N1 and N2 */
/*                        default:   Nmax =    100 */
/*      igsmax    ..    maximum number of surface elements (depends on N1 and N2) */
/*                        e.g. igsmax=762 for N=30, 3011 for N=60, etc. */
/*                        default: igsmax =   8331 */
/*      ispmax    ..    maximum number of spots */
/*                        default: ispmax =    100 */
/*      iclmax    ..    maximum number of clouds */
/*                        default: iclmax =    100 */
/*      iptmax    ..    maximum number of observed data points, including */
/*                        blank points on last lines of the velocity and light curve */
/*                        data sets and on stop lines */
/*                        default: iptmax =  10000 */
/*       ncmax    ..    maximum number of input data curves (velocity +light) */
/*                        default: 50 */
/*      iplmax    ..    maximum number of passbands */
/*                        default: iplmax =     26 */
/*       ipmax    ..    maximum number of parameters that are actually */
/*            adjusted, with band-independent parameters counted once each and */
/*            band-dependent parameters counted N_band times each. */
/*                        default: ipmax= 50 */


/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     Model atmosphere grid properties: */

/*       itemppts  ..   number of temperature coefficients per spectrum */
/*                        default: itemppts=48 (4x12) */
/*       iloggpts  ..   number of log(g) nodes */
/*                        default: iloggpts=11 (atmosphere grid) */
/*       imetpts   ..   number of metallicity nodes */
/*                        default: imetpts=19  (atmosphere grid) */
/*       iatmpts   ..   size of the atmosphere grid per passband per */
/*                      metallicity */
/*                        default: iatmpts = 11*48 = 528 */
/*                        11 log(g) values and */
/*                        48=4x12 temperature coefficients */
/*       iatmchunk ..   size of the atmosphere grid per metallicity */
/*                        default: iatmchunk = 528*25 = 13200 */
/*       iatmsize  ..   size of the atmosphere grid */
/*                        default: iatmsize = 13200*19 = 250800 */


/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     Locations of the auxiliary files atmcof.dat and atmcofplanck.dat: */


/*     parameter (atmtab='atmcof.dat') */
/*     parameter ( pltab='atmcofplanck.dat') */

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     Other array dimensions that are set automatically are listed */
/*     below and should not be changed, as the above parameter statements */
/*     determine their values. */

/*        MMmax    ..    maximum dimension of the MMSAVE array */
/*       ifrmax    ..    maximum dimension of the horizon polar */
/*                       coordinate arrays */
/*       istmax    ..    maximum dimension of storage arrays OBS and HOLD */
/*                         (iptmax * (no. of adjusted parameters + 1). */
/*       iplcof    ..    dimension of the atmcofplanck matrix, 50 per */
/*                       passband */


/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     Finally, the following dimensions are considered static and */
/*     their size does not depend on parameters. */

/*       ichno    ..    number of parameter channels (currently 35) */


/*     Nothing needs to be changed beyond this point to accomodate finer grids. */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extensions: */

/*       L3perc   ..   switch whether third light is given in percent */
/*        knobs   ..   cummulative number of observations */
/*       indeps   ..   array of data HJDs or phases */
/*       fluxes   ..   array of data fluxes */
/*      weights   ..   array of data weights */
/*        corrs   ..   an array of computed corrections */
/*       stdevs   ..   standard deviations of fitted parameters */
/*        chi2s   ..   chi2 values of individual curves after the fit */
/*       cormat   ..   correlation matrix (a wrapped 1D array) */
/*         ccla   ..   computed CLA values */
/*        cfval   ..   cost function value (global goodness-of-fit value) */
/*          nph   ..   finite time integration oversampling rate */
/*        delph   ..   finite time integration cadence */
/*         args   ..   an array of passed parameters (arguments): */

/*                     args( 1) = phase shift */
/*                     args( 2) = inclination */

/*                     Incorporating args was necessary to circumvent */
/*                     rounding problems in WD when using I/O. */

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE modification: */

/*     Removed: knobs(ncmax+2) */

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/* The following dimensioned variables are not used by DC. They are */
/*    dimensioned only for compatibility with usage of subroutine */
/*    LIGHT by program LC. */

    /* Parameter adjustments */
    --args;
    --ccla;
    --cormat;
    --chi2s;
    --stdevs;
    --corrs;
    --weights;
    --fluxes;
    --indeps;
    --knobs;

    /* Function Body */

/*           Bandpass Label Assignments for Stellar Atmospheres */

/*    Label   Bandpass   Reference for Response Function */
/*    -----   --------   ------------------------------- */
/*       1        u      Crawford, D.L. and Barnes, J.V. 1974, AJ, 75, 978 */
/*       2        v          "                "           " */
/*       3        b          "                "           " */
/*       4        y          "                "           " */
/*       5        U      Buser, R. 1978, Ang, 62, 411 */
/*       6        B      Azusienis and Straizys 1969, Sov. Astron., 13, 316 */
/*       7        V          "             "                " */
/*       8        R      Johnson, H.L. 1965, ApJ, 141, 923 */
/*       9        I         "            "    " */
/*      10        J         "            "    " */
/*      11        K         "            "    " */
/*      12        L         "            "    " */
/*      13        M         "            "    " */
/*      14        N         "            "    " */
/*      15        R_c    Bessell, M.S. 1983, PASP, 95, 480 */
/*      16        I_c       "            "    " */
/*      17      230      Kallrath, J., Milone, E.F., Terrell, D., Young, A.T. */
/*                          1998, ApJ, 508, 308 */
/*      18      250         "             "             "           " */
/*      19      270         "             "             "           " */
/*      20      290         "             "             "           " */
/*      21      310         "             "             "           " */
/*      22      330         "             "             "           " */
/*      23     'TyB'    Tycho catalog B */
/*      24     'TyV'    Tycho catalog V */
/*      25     'HIP'    Hipparcos catalog */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*      PHOEBE extensions: */

/*      26   CoRoT-exo  Carla Maceroni, private communication */
/*      27   CoRoT-sis  Carla Maceroni, private communication */
/*      28       H      Johnson, H.L. 1965, ApJ, 141, 923 */
/*      29   Geneva U   Golay, M. 1962, Pub. Obs. Geneve No. 15 (serie A), 29 */
/*      30   Geneva B       "             "             "           " */
/*      31   Geneva B1      "             "             "           " */
/*      32   Geneva B2      "             "             "           " */
/*      33   Geneva V       "             "             "           " */
/*      34   Geneva V1      "             "             "           " */
/*      35   Geneva G       "             "             "           " */
/*      36   Kepler     Kepler Science Book */
/*      37   SDSS u     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      38   SDSS g     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      39   SDSS r     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      40   SDSS i     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      41   SDSS z     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      42   LSST u     LSST science book */
/*      43   LSST g     LSST science book */
/*      44   LSST r     LSST science book */
/*      45   LSST i     LSST science book */
/*      46   LSST z     LSST science book */
/*      47   LSST y3    LSST science book */
/*      48   LSST y4    LSST science book */

/* L15: */
/* L16: */
/* L67: */
/* L17: */
/* L19: */
/* L21: */
/* L55: */
/* L56: */
/* L20: */
/* L101: */
/* L1: */
/* L701: */
/*   2 FORMAT(5(F14.5,F8.4,F6.2)) */
/* L2: */
/* L85: */
/* L18: */
/* L218: */
/* L37: */
/* L137: */
/* L715: */
/* L716: */
/* L43: */
/* L615: */
/* L616: */
/* L138: */
/* L181: */
/* L183: */
/* L184: */
/* L185: */
/* L82: */
/* L83: */
/* L9: */
/* L955: */
/* L10: */
/* L755: */
/* L756: */
/* L40: */
/* L11: */
/* L111: */
/* L12: */
/* L206: */
/* L205: */
/* L402: */
/* L403: */
/* L406: */
/* L702: */
/* L706: */
/* L408: */
/* L705: */
/* L54: */
/* L707: */
/* L917: */
/* L708: */
/* L912: */
/* L650: */
/* L651: */
/* L652: */
/* L653: */
/* L654: */
/* L684: */
/* L985: */
/* L983: */
/* L399: */
/* L60: */
/* L61: */
/* L66: */
/* L166: */
/* L440: */
/* L441: */
/* L405: */
/* L1440: */
/* L1441: */
/* L1442: */
/* L1443: */
/* L1444: */
/* L1445: */
/* L1446: */
/* L1447: */
/* L1448: */
/* L1449: */
/* L1450: */
/* L1451: */
/* L1452: */
/* L1453: */
/* L1454: */
/* L1455: */
/* L1456: */
/* L1457: */
/* L1458: */
/* L1459: */
/* L1460: */
/* L1461: */
/* L1462: */
/* L1463: */
/* L1464: */
/* L1470: */
/* L1471: */
/* L1472: */
/* L1473: */
/* L1474: */
/* L1465: */
/* L1466: */
/* L1467: */
/* L1468: */
/* L1469: */
/* L119: */
/* L159: */
/* L169: */
/* L1063: */
/* L64: */
/* L69: */
/* L170: */
/* L649: */
/* L171: */
/* L911: */
/* L840: */
/* L839: */
/* L283: */
/* L284: */
/* L285: */
/* L286: */
/* L287: */
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*  Ramp ranges are set here. The values below seem to work well, however, */
/*  they can be changed. */
    ramprange_1.tlowtol = 1500.;
    ramprange_1.thightol = 5e4;
    ramprange_1.glowtol = 4.;
    ramprange_1.ghightol = 4.;
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    abung_1.abun[0] = 1.;
    abung_1.abun[1] = .5;
    abung_1.abun[2] = .3;
    abung_1.abun[3] = .2;
    abung_1.abun[4] = .1;
    abung_1.abun[5] = 0.;
    abung_1.abun[6] = -.1;
    abung_1.abun[7] = -.2;
    abung_1.abun[8] = -.3;
    abung_1.abun[9] = -.5;
    abung_1.abun[10] = -1.;
    abung_1.abun[11] = -1.5;
    abung_1.abun[12] = -2.;
    abung_1.abun[13] = -2.5;
    abung_1.abun[14] = -3.;
    abung_1.abun[15] = -3.5;
    abung_1.abun[16] = -4.;
    abung_1.abun[17] = -4.5;
    abung_1.abun[18] = -5.;
    abung_1.glog[0] = 0.;
    abung_1.glog[1] = .5;
    abung_1.glog[2] = 1.;
    abung_1.glog[3] = 1.5;
    abung_1.glog[4] = 2.;
    abung_1.glog[5] = 2.5;
    abung_1.glog[6] = 3.;
    abung_1.glog[7] = 3.5;
    abung_1.glog[8] = 4.;
    abung_1.glog[9] = 4.5;
    abung_1.glog[10] = 5.;
    atmmessages_1.message[0] = 0;
    atmmessages_1.message[2] = 0;
    atmmessages_1.message[1] = 0;
    atmmessages_1.message[3] = 0;
    atmmessages_1.message[4] = 0;
    atmmessages_1.message[6] = 0;
    atmmessages_1.message[5] = 0;
    atmmessages_1.message[7] = 0;
    o__1.oerr = 0;
    o__1.ounit = 22;
    o__1.ofnmlen = atmtab_len;
    o__1.ofnm = atmtab;
    o__1.orl = 0;
    o__1.osta = "old";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_rsle(&io___114);
    do_lio(&c__5, &c_b311, (char *)&arrayleg_2.grand[0], (ftnlen)sizeof(
	    doublereal));
    e_rsle();
    cl__1.cerr = 0;
    cl__1.cunit = 22;
    cl__1.csta = 0;
    f_clos(&cl__1);
    o__1.oerr = 0;
    o__1.ounit = 23;
    o__1.ofnmlen = pltab_len;
    o__1.ofnm = pltab;
    o__1.orl = 0;
    o__1.osta = "old";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_rsle(&io___115);
    do_lio(&c__5, &c__2400, (char *)&planckleg_1.plcof[0], (ftnlen)sizeof(
	    doublereal));
    e_rsle();
    cl__1.cerr = 0;
    cl__1.cunit = 23;
    cl__1.csta = 0;
    f_clos(&cl__1);
    o__1.oerr = 0;
    o__1.ounit = 15;
    o__1.ofnmlen = 11;
    o__1.ofnm = "dcin.active";
    o__1.orl = 0;
    o__1.osta = "old";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = 16;
    o__1.ofnmlen = 12;
    o__1.ofnm = "dcout.active";
    o__1.orl = 0;
    o__1.osta = 0;
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    tt = .66666666666666663;
    ipro_1.nbins = 1;
    ipro_1.nl = 1;
    ipro_1.inmax = 1;
    ipro_1.inmin = 1;
    ipro_1.nf1 = 1;
    ipro_1.nf2 = 1;
    toldis = 1e-5;
    pi = acos(-1.);
    en0 = 6.0221409e23;
    xtha[0] = 0.;
    xtha[1] = pi * .5;
    xtha[2] = pi * .5;
    xtha[3] = pi * .5;
    xfia[0] = 0.;
    xfia[1] = 0.;
    xfia[2] = pi * .5;
    xfia[3] = pi;

/*  The initializations in th 886 and 887 loops are just to avoid */
/*    triggering error messages from some compilers. The quantities do */
/*    not otherwise need initialization. Same for du1, ...., du7. */
/*    Same for mpage, nl1, nl2. */

    for (ikks = 1; ikks <= 2; ++ikks) {
	for (jkks = 1; jkks <= 100; ++jkks) {
/* L886: */
	    spots_1.kks[ikks + (jkks << 1) - 3] = 0;
	}
    }
    for (immsav = 1; immsav <= 404; ++immsav) {
	mmsavh[immsav - 1] = 0;
/* L887: */
	mmsavl[immsav - 1] = 0;
    }
    prof2_2.du1 = 0.;
    prof2_2.du2 = 0.;
    prof2_2.du3 = 0.;
    prof2_2.du4 = 0.;
    prof2_2.du5 = 0.;
    prof2_2.du6 = 0.;
    prof2_2.du7 = 0.;
    inprof_1.mpage = 0;
    inprof_1.nl1 = 0;
    inprof_1.nl2 = 0;
    ibef = 0;
    invar_2.kh = 25;
    ns = 1;
    ni = 0;
    ny = 0;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE modification: */

/*     Commented out: KNOBS(1)=0 */

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    s_wsfe(&io___131);
    e_wsfe();
    s_wsfe(&io___132);
    e_wsfe();
    s_wsfe(&io___133);
    e_wsfe();
    s_wsfe(&io___134);
    e_wsfe();
    s_wsfe(&io___135);
    e_wsfe();
    s_wsfe(&io___136);
    e_wsfe();
    s_wsfe(&io___137);
    e_wsfe();
    s_wsfe(&io___138);
    e_wsfe();
    s_wsfe(&io___139);
    e_wsfe();
    s_wsfe(&io___140);
    e_wsfe();
    s_wsfe(&io___141);
    e_wsfe();
    s_wsfe(&io___142);
    e_wsfe();
    s_wsfe(&io___143);
    e_wsfe();
    s_wsfe(&io___144);
    e_wsfe();
    s_wsfe(&io___145);
    e_wsfe();
    s_wsfe(&io___146);
    e_wsfe();
    s_wsfe(&io___147);
    e_wsfe();
    s_wsfe(&io___148);
    e_wsfe();
    s_wsfe(&io___149);
    e_wsfe();
    s_wsfe(&io___150);
    e_wsfe();
    s_wsfe(&io___151);
    e_wsfe();
    s_wsfe(&io___152);
    e_wsfe();
    s_wsfe(&io___153);
    e_wsfe();
    s_wsfe(&io___154);
    e_wsfe();
    s_wsfe(&io___155);
    e_wsfe();
    s_wsfe(&io___156);
    e_wsfe();
    s_wsfe(&io___157);
    e_wsfe();
    s_wsfe(&io___158);
    e_wsfe();
    s_wsfe(&io___159);
    e_wsfe();
    s_wsfe(&io___160);
    e_wsfe();
    s_wsfe(&io___161);
    e_wsfe();
    s_wsfe(&io___162);
    e_wsfe();
    s_wsfe(&io___163);
    e_wsfe();
    s_wsfe(&io___164);
    e_wsfe();
    s_wsfe(&io___165);
    e_wsfe();
    s_wsfe(&io___166);
    e_wsfe();
    s_wsfe(&io___167);
    e_wsfe();
    s_wsfe(&io___168);
    e_wsfe();
    s_wsfe(&io___169);
    e_wsfe();
    s_wsfe(&io___170);
    e_wsfe();
    s_rsfe(&io___171);
    for (i__ = 1; i__ <= 8; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    e_rsfe();
    s_rsfe(&io___174);
    for (i__ = 10; i__ <= 14; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    for (i__ = 16; i__ <= 20; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    e_rsfe();
    s_rsfe(&io___175);
    for (i__ = 21; i__ <= 25; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    for (i__ = 31; i__ <= 34; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    e_rsfe();
    s_rsfe(&io___176);
    for (i__ = 1; i__ <= 35; ++i__) {
	do_fio(&c__1, (char *)&kep[i__ - 1], (ftnlen)sizeof(integer));
    }
    do_fio(&c__1, (char *)&ifder, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifm, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifr, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&xlamda, (ftnlen)sizeof(doublereal));
    e_rsfe();
    s_rsfe(&io___182);
    do_fio(&c__1, (char *)&kspa, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nspa, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&kspb, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nspb, (ftnlen)sizeof(integer));
    e_rsfe();
    s_rsfe(&io___187);
    do_fio(&c__1, (char *)&ifvc1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifvc2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nlc, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ko, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&kdisk, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&isym, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nppl, (ftnlen)sizeof(integer));
    e_rsfe();
    s_rsfe(&io___195);
    do_fio(&c__1, (char *)&invar_2.nref, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.mref, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.ifsmv1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.ifsmv2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.icor1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.icor2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.ld, (ftnlen)sizeof(integer));
    e_rsfe();
    s_rsfe(&io___196);
    do_fio(&c__1, (char *)&invar_2.jdphs, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ardot_2.hjd0, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&eccen_2.period, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&dpdt, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&pshift, (ftnlen)sizeof(doublereal));
    e_rsfe();
    if (invar_2.jdphs == 2 && kep[25] == 0) {
	s_wsfe(&io___199);
	e_wsfe();
    }
    if (invar_2.jdphs == 2 && kep[26] == 0) {
	s_wsfe(&io___200);
	e_wsfe();
    }
    if (invar_2.jdphs == 2 && kep[27] == 0) {
	s_wsfe(&io___201);
	e_wsfe();
    }
    if (kep[13] == 0 && kep[25] == 0) {
	s_wsfe(&io___202);
	e_wsfe();
    }
    s_rsfe(&io___203);
    do_fio(&c__1, (char *)&mode, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.ipb, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifat1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifat2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&n1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&n2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&n1l, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&n2l, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&perr0, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ardot_2.dperdt, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&the, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&flvar_2.vunit, (ftnlen)sizeof(doublereal));
    e_rsfe();
    s_rsfe(&io___213);
    do_fio(&c__1, (char *)&e, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&eccen_2.a, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&f1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&f2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&eccen_2.vga, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&xincl, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&gr1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&gr2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&abunin, (ftnlen)sizeof(doublereal));
    e_rsfe();
    s_rsfe(&io___221);
    do_fio(&c__1, (char *)&tavh, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tavc, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&alb1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&alb2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&phsv, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&pcsv, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&rm, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&xbol1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&xbol2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ybol1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ybol2, (ftnlen)sizeof(doublereal));
    e_rsfe();
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*     Override the read-in values with passed values: */
    pshift = args[1];
    xincl = args[2];
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    cld_1.acm = eccen_2.a * 6.957e10;
    nn1 = n1;
    sincos_(&c__1, &n1, &n1, snthh, csthh, snfih, csfih, mmsavh);
    sincos_(&c__2, &n2, &n1, snthh, csthh, snfih, csfih, mmsavh);
    sincos_(&c__1, &n1l, &n1l, snthl, csthl, snfil, csfil, mmsavl);
    sincos_(&c__2, &n2l, &n1l, snthl, csthl, snfil, csfil, mmsavl);
    dint1 = pi * (1. - xbol1 / 3.);
    if (invar_2.ld == 2) {
	dint1 += pi * ybol1 * 2. / 9.;
    }
    if (invar_2.ld == 3) {
	dint1 -= pi * ybol1 * .2;
    }
    dint2 = pi * (1. - xbol2 / 3.);
    if (invar_2.ld == 2) {
	dint2 += pi * ybol2 * 2. / 9.;
    }
    if (invar_2.ld == 3) {
	dint2 -= pi * ybol2 * .2;
    }
    is = isym + 1;
    keep[35] = 0;
    mm1 = n1 + 1;
    mm2 = n1 + n2 + 2;
    mm3 = n1l + 1;
    mm4 = n1l + n2l + 2;
    m1h = mmsavh[mm1 - 1];
    m2h = mmsavh[mm2 - 1];
    m1l = mmsavl[mm3 - 1];
    m2l = mmsavl[mm4 - 1];
    mtlh = m1h + m2h;
    mtll = m1l + m2l;
    nvc = ifvc1 + ifvc2;
    nlvc = nlc + nvc;
    nvcp = nvc + 1;
    if (nvc != 0) {
	goto L288;
    }
    kep[8] = 1;
    kep[14] = 1;
L288:
    for (i__ = 1; i__ <= 35; ++i__) {
	keep[i__ - 1] = kep[i__ - 1];
/* L84: */
	low[i__ - 1] = 1;
    }
    low[0] = 0;
    low[1] = 0;
    low[2] = 0;
    low[4] = 0;
    low[5] = 0;
    low[6] = 0;
    low[9] = 0;
    low[10] = 0;
    low[11] = 0;
    low[12] = 0;
    low[13] = 0;
    low[15] = 0;
    low[22] = 0;
    low[23] = 0;
    low[24] = 0;
    ifap = 1 - keep[28];
    ifphi = 1 - keep[25] * keep[26] * keep[27];
    kosq = (ko - 2) * (ko - 2);
    if (nvc == 0) {
	goto L195;
    }
    i__1 = nvc;
    for (i__ = 1; i__ <= i__1; ++i__) {
	el3a[i__ - 1] = 0.;
/* L90: */
	s_rsfe(&io___264);
	do_fio(&c__1, (char *)&iband[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hla[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cla[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x1a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x2a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y1a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y2a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&opsfa[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sigma[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&wla[i__ - 1], (ftnlen)sizeof(doublereal));
	e_rsfe();
    }
L195:
    if (nlvc == nvc) {
	goto L194;
    }
    i__1 = nlvc;
    for (i__ = nvcp; i__ <= i__1; ++i__) {
/* L190: */
	s_rsfe(&io___275);
	do_fio(&c__1, (char *)&iband[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hla[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cla[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x1a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x2a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y1a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y2a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&el3a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&opsfa[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&noise[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&sigma[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&wla[i__ - 1], (ftnlen)sizeof(doublereal));
	e_rsfe();
    }
L194:
    nspt_1.nsp1 = 0;
    nspt_1.nsp2 = 0;
    for (kp = 1; kp <= 2; ++kp) {
	for (i__ = 1; i__ <= 100; ++i__) {
	    s_rsfe(&io___278);
	    do_fio(&c__1, (char *)&xlat[kp + (i__ << 1) - 3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&xlong[kp + (i__ << 1) - 3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&radsp[kp + (i__ << 1) - 3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temsp[kp + (i__ << 1) - 3], (ftnlen)sizeof(
		    doublereal));
	    e_rsfe();
	    spots_1.xlng[kp + (i__ << 1) - 3] = xlong[kp + (i__ << 1) - 3];
	    if (xlat[kp + (i__ << 1) - 3] >= 200.) {
		goto L988;
	    }
	    spots_1.snlat[kp + (i__ << 1) - 3] = sin(xlat[kp + (i__ << 1) - 3]
		    );
	    spots_1.cslat[kp + (i__ << 1) - 3] = cos(xlat[kp + (i__ << 1) - 3]
		    );
	    spots_1.snlng[kp + (i__ << 1) - 3] = sin(xlong[kp + (i__ << 1) - 
		    3]);
	    spots_1.cslng[kp + (i__ << 1) - 3] = cos(xlong[kp + (i__ << 1) - 
		    3]);
	    spots_1.rdsp[kp + (i__ << 1) - 3] = radsp[kp + (i__ << 1) - 3];
	    spots_1.tmsp[kp + (i__ << 1) - 3] = temsp[kp + (i__ << 1) - 3];
	    if (kp == 1) {
		++nspt_1.nsp1;
	    }
/* L987: */
	    if (kp == 2) {
		++nspt_1.nsp2;
	    }
	}
L988:
	;
    }
    nstot = nspt_1.nsp1 + nspt_1.nsp2;
    invar_2.ncl = 0;
    for (i__ = 1; i__ <= 100; ++i__) {
	s_rsfe(&io___284);
	do_fio(&c__1, (char *)&xcl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ycl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&zcl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rcl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&op1[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&fcl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&edens[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&xmue[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&encl[i__ - 1], (ftnlen)sizeof(doublereal));
	e_rsfe();
	if (xcl[i__ - 1] > 100.) {
	    goto L1066;
	}
	++invar_2.ncl;
	dens[i__ - 1] = edens[i__ - 1] * xmue[i__ - 1] / en0;
/* L1062: */
    }
L1066:
    for (ipara = 1; ipara <= 8; ++ipara) {
/* L153: */
	para[ipara - 1] = 0.;
    }
    if (nspa == 0) {
	goto L154;
    }
    para[0] = xlat[kspa + (nspa << 1) - 3];
    para[1] = xlong[kspa + (nspa << 1) - 3];
    para[2] = radsp[kspa + (nspa << 1) - 3];
    para[3] = temsp[kspa + (nspa << 1) - 3];
L154:
    if (nspb == 0) {
	goto L155;
    }
    para[4] = xlat[kspb + (nspb << 1) - 3];
    para[5] = xlong[kspb + (nspb << 1) - 3];
    para[6] = radsp[kspb + (nspb << 1) - 3];
    para[7] = temsp[kspb + (nspb << 1) - 3];
L155:
    para[8] = eccen_2.a;
    para[9] = e;
    para[10] = perr0;
    para[11] = f1;
    para[12] = f2;
    para[13] = pshift;
    para[14] = eccen_2.vga;
    para[15] = xincl;
    para[16] = gr1;
    para[17] = gr2;
    para[18] = tavh;
    para[19] = tavc;
    para[20] = alb1;
    para[21] = alb2;
    para[22] = phsv;
    para[23] = pcsv;
    para[24] = rm;
    para[25] = ardot_2.hjd0;
    para[26] = eccen_2.period;
    para[27] = dpdt;
    para[28] = ardot_2.dperdt;
    para[29] = 0.;
    ib = nvc;
    i__1 = nlc + 30;
    for (irx = 31; irx <= i__1; ++irx) {
	++ib;
/* L191: */
	para[irx - 1] = hla[ib - 1];
    }
    ib = nvc;
    i__1 = (nlc << 1) + 30;
    for (irx = nlc + 31; irx <= i__1; ++irx) {
	++ib;
/* L186: */
	para[irx - 1] = cla[ib - 1];
    }
    ib = nvc;
    i__1 = nlc * 3 + 30;
    for (irx = (nlc << 1) + 31; irx <= i__1; ++irx) {
	++ib;
/* L187: */
	para[irx - 1] = x1a[ib - 1];
    }
    ib = nvc;
    i__1 = (nlc << 2) + 30;
    for (irx = nlc * 3 + 31; irx <= i__1; ++irx) {
	++ib;
/* L188: */
	para[irx - 1] = x2a[ib - 1];
    }
    ib = nvc;
    i__1 = nlc * 5 + 30;
    for (irx = (nlc << 2) + 31; irx <= i__1; ++irx) {
	++ib;
/* L189: */
	para[irx - 1] = el3a[ib - 1];
    }
    flvar_2.pert = perr0;
    eccen_2.ec = e;
    ardot_2.hjd = ardot_2.hjd0;
    flvar_2.psh = pshift;
    invar_2.irte = 0;
    invar_2.irvol1 = 0;
    invar_2.irvol2 = 0;
/* *************************************************************** */
/*  The following lines take care of abundances that may not be among */
/*  the 19 Kurucz values (see abun array). abunin is reset at the */
/*  allowed value nearest the input value. */
    binnum_(abung_1.abun, &c__19, &abunin, &iab);
    dif1 = abunin - abung_1.abun[iab - 1];
    if (iab == 19) {
	goto L7702;
    }
    dif2 = abung_1.abun[iab] - abung_1.abun[iab - 1];
    dif = dif1 / dif2;
    if (dif >= 0. && dif <= .5) {
	goto L7702;
    }
    ++iab;
L7702:
    if (dif1 != 0.) {
	s_wsfe(&io___303);
	do_fio(&c__1, (char *)&abunin, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&abung_1.abun[iab - 1], (ftnlen)sizeof(
		doublereal));
	e_wsfe();
    }
    abunin = abung_1.abun[iab - 1];
    arrayleg_2.istart = (iab - 1) * 25344 + 1;
/* *************************************************************** */
    modlog_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, mmsavh, fr1, fr2, hld, &
	    rm, &phsv, &pcsv, &gr1, &gr2, &alb1, &alb2, &n1, &n2, &f1, &f2, &
	    mod, &xincl, &the, &mode, snthh, csthh, snfih, csfih, grv1, grv2, 
	    xx1, yy1, zz1, xx2, yy2, zz2, glump1, glump2, csbt1, csbt2, gmag1,
	     gmag2, glog1, glog2, tloc1, tloc2, xinorm1, xinorm2);
    ellone_(&f1, &flvar_2.dp, &rm, &xld, omcr, &xldd, &omd);
    rmr = 1. / rm;
    ellone_(&f2, &flvar_2.dp, &rmr, &xld, &omcr[1], &xldd, &omd);
    omcr[1] = rm * omcr[1] + (1. - rm) * .5;
    po[0] = phsv;
    po[1] = pcsv;
    volume_(&eccen_2.vol1, &rm, &phsv, &flvar_2.dp, &f1, &nn1, &n1, &c__1, rv,
	     grx, gry, grz, rvq, grxq, gryq, grzq, mmsavh, fr1, fr2, hld, 
	    snthh, csthh, snfih, csfih, &summd, &smd, grv1, grv2, xx1, yy1, 
	    zz1, xx2, yy2, zz2, csbt1, csbt2, glump1, glump2, gmag1, gmag2, 
	    glog1, glog2, &gr1, &c__1, tloc1, tloc2, xinorm1, xinorm2);
    volume_(&eccen_2.vol2, &rm, &pcsv, &flvar_2.dp, &f2, &n2, &n1, &c__2, rv, 
	    grx, gry, grz, rvq, grxq, gryq, grzq, mmsavh, fr1, fr2, hld, 
	    snthh, csthh, snfih, csfih, &summd, &smd, grv1, grv2, xx1, yy1, 
	    zz1, xx2, yy2, zz2, csbt1, csbt2, glump1, glump2, gmag1, gmag2, 
	    glog1, glog2, &gr2, &c__1, tloc1, tloc2, xinorm1, xinorm2);
    if (e == 0.) {
	goto L134;
    }
    dap = e + 1.;
    p1ap = phsv - e * 2. * rm / (1. - e * e);
    vl1 = eccen_2.vol1;
    volume_(&vl1, &rm, &p1ap, &dap, &f1, &nn1, &n1, &c__1, rv, grx, gry, grz, 
	    rvq, grxq, gryq, grzq, mmsavh, fr1, fr2, hld, snthh, csthh, snfih,
	     csfih, &summd, &smd, grv1, grv2, xx1, yy1, zz1, xx2, yy2, zz2, 
	    csbt1, csbt2, glump1, glump2, gmag1, gmag2, glog1, glog2, &gr1, &
	    c__2, tloc1, tloc2, xinorm1, xinorm2);
    dpdx_1.dpdx1 = (phsv - p1ap) * (1. - e * e) * .5 / e;
    p2ap = pcsv - e * 2. / (1. - e * e);
    vl2 = eccen_2.vol2;
    volume_(&vl2, &rm, &p2ap, &dap, &f2, &n2, &n1, &c__2, rv, grx, gry, grz, 
	    rvq, grxq, gryq, grzq, mmsavh, fr1, fr2, hld, snthh, csthh, snfih,
	     csfih, &summd, &smd, grv1, grv2, xx1, yy1, zz1, xx2, yy2, zz2, 
	    csbt1, csbt2, glump1, glump2, gmag1, gmag2, glog1, glog2, &gr2, &
	    c__2, tloc1, tloc2, xinorm1, xinorm2);
    dpdx_1.dpdx2 = (pcsv - p2ap) * (1. - e * e) * .5 / e;
L134:
    php = flvar_2.phper;
    poth = phsv;
    potc = pcsv;
    dpdx_1.pot1 = phsv;
    dpdx_1.pot2 = pcsv;
    i__1 = nlvc;
    for (i__ = 1; i__ <= i__1; ++i__) {
	cld_1.opsf = opsfa[i__ - 1];
/* L24: */
	bbl_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, mmsavh, fr1, fr2, hld, 
		slump1, slump2, theta, rho, aa, bb, &poth, &potc, &n1, &n2, &
		f1, &f2, &d__, &hla[i__ - 1], &cla[i__ - 1], &x1a[i__ - 1], &
		x2a[i__ - 1], &y1a[i__ - 1], &y2a[i__ - 1], &gr1, &gr2, &wla[
		i__ - 1], &sm1, &sm2, &tpolh, &tpolc, &sbrh, &sbrc, &tavh, &
		tavc, &alb1, &alb2, &xbol1, &xbol2, &ybol1, &ybol2, &php, &rm,
		 &xincl, &hot, &cool, snthh, csthh, snfih, csfih, tldh, 
		glump1, glump2, xx1, xx2, yy1, yy2, zz1, zz2, &dint1, &dint2, 
		grv1, grv2, rftemp, rf1, rf2, csbt1, csbt2, gmag1, gmag2, 
		glog1, glog2, fbin1, fbin2, delv1, delv2, count1, count2, 
		delwl1, delwl2, resf1, resf2, wl1, wl2, dvks1, dvks2, tau1, 
		tau2, emm1, emm2, hbarw1, hbarw2, xcl, ycl, zcl, rcl, op1, 
		fcl, dens, encl, edens, taug, emmg, yskp, zskp, &mode, &iband[
		i__ - 1], &ifat1, &ifat2, &c__1, tloc1, tloc2, xinorm1, 
		xinorm2);
    }
    del[8] = 0.;
    del[14] = 0.;
    del[25] = 0.;
    del[26] = 0.;
    del[27] = 0.;
    del[28] = 0.;
    del[34] = 0.;
    s_wsfe(&io___395);
    e_wsfe();
    s_wsfe(&io___396);
    e_wsfe();
    s_wsfe(&io___397);
    for (i__ = 1; i__ <= 8; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    e_wsfe();
    s_wsfe(&io___398);
    e_wsfe();
    s_wsfe(&io___399);
    e_wsfe();
    s_wsfe(&io___400);
    for (i__ = 10; i__ <= 14; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    for (i__ = 16; i__ <= 20; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    e_wsfe();
    s_wsfe(&io___401);
    e_wsfe();
    s_wsfe(&io___402);
    e_wsfe();
    s_wsfe(&io___403);
    for (i__ = 21; i__ <= 25; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    for (i__ = 31; i__ <= 34; ++i__) {
	do_fio(&c__1, (char *)&del[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    e_wsfe();
    s_wsfe(&io___404);
    e_wsfe();
    s_wsfe(&io___405);
    e_wsfe();
    s_wsfe(&io___406);
    for (i__ = 1; i__ <= 35; ++i__) {
	do_fio(&c__1, (char *)&kep[i__ - 1], (ftnlen)sizeof(integer));
    }
    do_fio(&c__1, (char *)&ifder, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifm, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifr, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&xlamda, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___407);
    e_wsfe();
    s_wsfe(&io___408);
    e_wsfe();
    s_wsfe(&io___409);
    e_wsfe();
    s_wsfe(&io___410);
    do_fio(&c__1, (char *)&kspa, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nspa, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&kspb, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nspb, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___411);
    e_wsfe();
    s_wsfe(&io___412);
    e_wsfe();
    s_wsfe(&io___413);
    do_fio(&c__1, (char *)&ifvc1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifvc2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nlc, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ko, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&kdisk, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&isym, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nppl, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___414);
    e_wsfe();
    s_wsfe(&io___415);
    e_wsfe();
    s_wsfe(&io___416);
    do_fio(&c__1, (char *)&invar_2.nref, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.mref, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.ifsmv1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.ifsmv2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.icor1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.icor2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.ld, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___417);
    e_wsfe();
    s_wsfe(&io___418);
    e_wsfe();
    s_wsfe(&io___419);
    do_fio(&c__1, (char *)&invar_2.jdphs, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ardot_2.hjd0, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&eccen_2.period, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&dpdt, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&pshift, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*delph), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*nph), (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___420);
    e_wsfe();
    s_wsfe(&io___421);
    e_wsfe();
    s_wsfe(&io___422);
    do_fio(&c__1, (char *)&mode, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&invar_2.ipb, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifat1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifat2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&n1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&n2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&n1l, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&n2l, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&perr0, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ardot_2.dperdt, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&the, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&flvar_2.vunit, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&eccen_2.vfac, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___423);
    e_wsfe();
    s_wsfe(&io___424);
    e_wsfe();
    s_wsfe(&io___425);
    do_fio(&c__1, (char *)&e, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&eccen_2.a, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&f1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&f2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&eccen_2.vga, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&xincl, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&gr1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&gr2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&nspt_1.nsp1, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nspt_1.nsp2, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&abunin, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&iab, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___426);
    e_wsfe();
    s_wsfe(&io___427);
    e_wsfe();
    s_wsfe(&io___428);
    do_fio(&c__1, (char *)&tavh, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tavc, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&alb1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&alb2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&phsv, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&pcsv, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&rm, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&xbol1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&xbol2, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ybol1, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ybol2, (ftnlen)sizeof(doublereal));
    e_wsfe();
    if (nvc == 0) {
	goto L196;
    }
    s_wsfe(&io___429);
    e_wsfe();
    s_wsfe(&io___430);
    e_wsfe();
    i__1 = nvc;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L91: */
	s_wsfe(&io___431);
	do_fio(&c__1, (char *)&iband[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hla[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cla[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x1a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x2a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y1a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y2a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&opsfa[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sigma[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&wla[i__ - 1], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
L196:
    if (nlvc == nvc) {
	goto L197;
    }
    s_wsfe(&io___432);
    e_wsfe();
    s_wsfe(&io___433);
    e_wsfe();
    i__1 = nlvc;
    for (i__ = nvcp; i__ <= i__1; ++i__) {
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

/*     The following block supports third light to be printed from the */
/*     passed percentage of third luminosity. */

	if (*l3perc == 1) {
	    el3 = (hla[i__ - 1] + cla[i__ - 1]) * el3a[i__ - 1] / ((1. - el3a[
		    i__ - 1]) * 12.566371999999999);
	} else {
	    el3 = el3a[i__ - 1];
	}
/* L92: */
	s_wsfe(&io___435);
	do_fio(&c__1, (char *)&iband[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hla[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cla[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x1a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x2a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y1a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y2a[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&el3, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&opsfa[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&noise[i__ - 1], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&sigma[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&wla[i__ - 1], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
/*  92 write(16,85)iband(i),hla(i),cla(i),x1a(i),x2a(i),y1a(i),y2a(i), */
/*    $el3a(i),opsfa(i),noise(i),sigma(i),wla(i) */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
L197:
    s_wsfe(&io___436);
    e_wsfe();
    if (nstot > 0) {
	s_wsfe(&io___437);
	e_wsfe();
    }
    for (kp = 1; kp <= 2; ++kp) {
	if (nspt_1.nsp1 + kp - 1 == 0) {
	    goto L688;
	}
/* Computing 2nd power */
	i__1 = kp - 2;
	if (nspt_1.nsp2 + i__1 * i__1 == 0) {
	    goto L688;
	}
	nspot = nspt_1.nsp1;
	if (kp == 2) {
	    nspot = nspt_1.nsp2;
	}
	i__1 = nspot;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L687: */
	    s_wsfe(&io___439);
	    do_fio(&c__1, (char *)&kp, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&xlat[kp + (i__ << 1) - 3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&xlong[kp + (i__ << 1) - 3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&radsp[kp + (i__ << 1) - 3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temsp[kp + (i__ << 1) - 3], (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
	}
L688:
	s_wsfe(&io___440);
	e_wsfe();
    }
    if (invar_2.ncl == 0) {
	goto L1067;
    }
    s_wsfe(&io___441);
    e_wsfe();
    i__1 = invar_2.ncl;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L68: */
	s_wsfe(&io___442);
	do_fio(&c__1, (char *)&xcl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ycl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&zcl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rcl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&op1[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&fcl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&edens[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&xmue[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&encl[i__ - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&dens[i__ - 1], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    s_wsfe(&io___443);
    e_wsfe();
L1067:
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE addition: */

    s_wsle(&io___444);
    do_lio(&c__9, &c__1, "            *** IMPORTANT NOTICE ***", (ftnlen)36);
    e_wsle();
    s_wsle(&io___445);
    do_lio(&c__9, &c__1, "", (ftnlen)0);
    e_wsle();
    s_wsle(&io___446);
    do_lio(&c__9, &c__1, "THE FOLLOWING BLOCK OF OBSERVATIONS WAS *NOT* USED",
	     (ftnlen)50);
    e_wsle();
    s_wsle(&io___447);
    do_lio(&c__9, &c__1, "IN DC, IT HAS BEEN READ FROM THE DCI FILE AND COPI"
	    "ED", (ftnlen)52);
    e_wsle();
    s_wsle(&io___448);
    do_lio(&c__9, &c__1, "HERE. PHOEBE PASSES DATA ARRAYS TO DC DIRECTLY, NOT"
	    , (ftnlen)51);
    e_wsle();
    s_wsle(&io___449);
    do_lio(&c__9, &c__1, "THROUGH A DCI FILE. IF YOUR WEIGHTS SHOW -1.0, THAT"
	    , (ftnlen)51);
    e_wsle();
    s_wsle(&io___450);
    do_lio(&c__9, &c__1, "MEANS THAT FORMATTING RESTRICTIONS OF WD WOULD HAVE"
	    , (ftnlen)51);
    e_wsle();
    s_wsle(&io___451);
    do_lio(&c__9, &c__1, "PREVENTED THEIR PROPER OUTPUT. HOWEVER, SINCE THE", 
	    (ftnlen)49);
    e_wsle();
    s_wsle(&io___452);
    do_lio(&c__9, &c__1, "DATA ARE PASSED TO DC DIRECTLY, THESE VALUES DO NOT"
	    , (ftnlen)51);
    e_wsle();
    s_wsle(&io___453);
    do_lio(&c__9, &c__1, "PLAY ANY ROLE.", (ftnlen)14);
    e_wsle();
    s_wsle(&io___454);
    do_lio(&c__9, &c__1, "", (ftnlen)0);
    e_wsle();
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    s_wsfe(&io___455);
    e_wsfe();
    s_wsfe(&io___456);
    e_wsfe();
    i__1 = nlvc;
    for (lcv = 1; lcv <= i__1; ++lcv) {
	s_wsfe(&io___458);
	e_wsfe();
	if (lcv <= nvc && invar_2.jdphs == 2) {
	    s_wsfe(&io___459);
	    e_wsfe();
	}
	if (lcv > nvc && invar_2.jdphs == 2) {
	    s_wsfe(&io___460);
	    e_wsfe();
	}
	if (lcv <= nvc && invar_2.jdphs == 1) {
	    s_wsfe(&io___461);
	    e_wsfe();
	}
	if (lcv > nvc && invar_2.jdphs == 1) {
	    s_wsfe(&io___462);
	    e_wsfe();
	}
	for (i__ = ns; i__ <= 50000; ++i__) {
	    ifirst = nppl * (i__ - 1) + ny + 1;
	    last = ifirst + nppl - 1;
	    s_rsfe(&io___465);
	    i__2 = last;
	    for (in = ifirst; in <= i__2; ++in) {
		do_fio(&c__1, (char *)&phjd[in - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&flux[in - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&wt[in - 1], (ftnlen)sizeof(doublereal))
			;
	    }
	    e_rsfe();
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*     WRITE(16,2) (phjd(in),flux(in),wt(in),in=ifirst,last) */
	    if (phjd[ifirst - 1] > -1e4) {
		s_wsfe(&io___470);
		i__2 = last;
		for (in = ifirst; in <= i__2; ++in) {
		    do_fio(&c__1, (char *)&indeps[in], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&fluxes[in], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&weights[in], (ftnlen)sizeof(
			    doublereal));
		}
		e_wsfe();
		goto L74;
	    }
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	    ni = (integer) (-(phjd[ifirst - 1] + 1e4));
	    ny += ni;
	    nobs = nppl * (i__ - ns - 1) + ni;
	    goto L150;
L74:
	    ;
	}
L150:
	ns = i__ - 1;
	lc1 = lcv + 1;
/*  75 KNOBS(LC1)=NOBS+KNOBS(LCV) */
/* L75: */
    }
    i__1 = knobs[lc1];
    for (ijp = 1; ijp <= i__1; ++ijp) {
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE modification: */

/*     phas(ijp)=phjd(ijp) */
/*     if(jdphs.eq.1) call jdph(phjd(ijp),0.d0,hjd0,period,dpdt,xjddum, */
/*    $phas(ijp)) */

	phas[ijp - 1] = indeps[ijp];
	if (invar_2.jdphs == 1) {
	    jdph_(&indeps[ijp], &c_b15, &ardot_2.hjd0, &eccen_2.period, &dpdt,
		     &xjddum, &phas[ijp - 1]);
	}

/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* L275: */
    }
    matrix = 31;
    for (ima = 1; ima <= 30; ++ima) {
/* L427: */
	matrix -= keep[ima - 1];
    }
    matrix += nlc * (5 - keep[30] - keep[31] - keep[32] - keep[33] - keep[34])
	    ;
    mat = matrix - 1;
    em = (doublereal) (matrix - 15);
    ktr = (integer) (em * .24 + 2.2);
    if (em <= 1.5) {
	ktr = 1;
    }
    if (em > 12.) {
	ktr = 5;
    }
    ncoeff = matrix * knobs[lc1];
    nmat = mat * knobs[lc1];
    ncof = ncoeff;
    i__1 = ncof;
    for (j = 1; j <= i__1; ++j) {
/* L63: */
	hold[j - 1] = 0.;
    }
    if (kosq == 1) {
	goto L71;
    }
    i__1 = ncoeff;
    for (iobs = 1; iobs <= i__1; ++iobs) {
/* L416: */
	obs[iobs - 1] = 0.;
    }
    ksmax = 37;
    kssmax = 37;
    if (e == 0.) {
	ksmax = 1;
    }
    if (e != 0.) {
	kssmax = 1;
    }
    i__1 = kssmax;
    for (kss = 1; kss <= i__1; ++kss) {
	i__2 = nlvc;
	for (ib = 1; ib <= i__2; ++ib) {
	    vc1 = 0.;
	    vc2 = 0.;
	    elit = 0.;
	    if (ib > nvc) {
		elit = 1.;
	    }
	    if (ib == ifvc1) {
		vc1 = 1.;
	    }
	    if (ib == ifvc2 * (ifvc1 + 1)) {
		vc2 = 1.;
	    }
	    ist = knobs[ib] + 1;
	    ib1 = ib + 1;
	    isp = knobs[ib1];
	    i__3 = isp;
	    for (ix = ist; ix <= i__3; ++ix) {
		i__4 = ksmax;
		for (ks = 1; ks <= i__4; ++ks) {
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE modification: */

/*     hjd=phjd(ix) */

		    ardot_2.hjd = indeps[ix];

/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
		    dtime = ardot_2.hjd - ardot_2.hjd0;
		    invar_2.irte = 0;
		    invar_2.irvol1 = 0;
		    invar_2.irvol2 = 0;
		    if (e != 0.) {
			goto L297;
		    }
		    if (ix != ist) {
			invar_2.irte = 1;
		    }
		    if (ix == ist) {
			goto L297;
		    }
		    invar_2.irvol1 = 1;
		    invar_2.irvol2 = 1;
L297:
		    ksr = ks;
		    if (e == 0.) {
			ksr = kss;
		    }
		    if (e != 0.) {
			goto L1110;
		    }
		    if (isym != 1) {
			goto L1110;
		    }
		    if (ksr == 1) {
			goto L420;
		    }
L1110:
		    invar_2.kh = ksr - 2;
		    if (invar_2.kh > 0) {
			goto L740;
		    }
		    invar_2.kh = 1;
		    goto L941;
L740:
		    if (ifap * invar_2.kh == 11) {
			goto L842;
		    }
		    if (ifphi * invar_2.kh == 14) {
			goto L842;
		    }
		    if (keep[invar_2.kh - 1] == 1) {
			goto L420;
		    }
L842:
/* 842 IF(E.EQ.0.d0) GOTO 889 */
/*     IF(KSR.LE.2) GOTO 889 */
/*     IF(KH.LE.9) IRTE=1 */
/*     IF(KH.LE.9) IRVOL1=1 */
/*     IF(KH.LE.9) IRVOL2=1 */
/*     IF(KH.EQ.12) IRVOL2=1 */
/*     IF(KH.EQ.13) IRVOL1=1 */
/*     IF(KH.EQ.15) IRTE=1 */
/*     IF(KH.EQ.15) IRVOL1=1 */
/*     IF(KH.EQ.15) IRVOL2=1 */
/*     IF(KH.EQ.16) IRTE=1 */
/*     IF(KH.EQ.16) IRVOL1=1 */
/*     IF(KH.EQ.16) IRVOL2=1 */
/*     IF(KH.EQ.17) IRVOL2=1 */
/*     IF(KH.EQ.18) IRVOL1=1 */
/*     IF(KH.EQ.19) IRVOL1=1 */
/*     IF(KH.EQ.19) IRVOL2=1 */
/*     IF(KH.EQ.20) IRVOL1=1 */
/*     IF(KH.EQ.20) IRVOL2=1 */
/*     IF(KH.EQ.21) IRVOL1=1 */
/*     IF(KH.EQ.21) IRVOL2=1 */
/*     IF(KH.EQ.22) IRVOL1=1 */
/*     IF(KH.EQ.22) IRVOL2=1 */
/*     IF(KH.EQ.23) IRVOL2=1 */
/*     IF(KH.EQ.24) IRVOL1=1 */
/*     IF(KH.GE.31) IRVOL1=1 */
/*     IF(KH.GE.31) IRVOL2=1 */
/* 889 CONTINUE */
		    lcf = 0;
		    if (invar_2.kh > 30) {
			lcf = ib - nvc;
		    }
		    kpct1 = 0;
		    kpct2 = 0;
		    ksp = invar_2.kh;
		    if (invar_2.kh > 30) {
			ksp = 30;
		    }
		    if (invar_2.kh < 2) {
			goto L808;
		    }
		    i__5 = ksp;
		    for (ict = 1; ict <= i__5; ++ict) {
/* L804: */
			kpct1 = kpct1 + 1 - keep[ict - 1];
		    }
		    goto L809;
L808:
		    kpct1 = 1;
L809:
		    if (invar_2.kh < 31) {
			goto L806;
		    }
		    i__5 = invar_2.kh;
		    for (ict = 31; ict <= i__5; ++ict) {
/* L805: */
			kpct2 = kpct2 + 1 - keep[ict - 1];
		    }
		    goto L807;
L806:
		    kpct2 = 1;
L807:
		    ii = (kpct1 + nlc * (kpct2 - 1) + lcf - 1) * knobs[lc1] + 
			    ix;
		    if (invar_2.kh == 9) {
			goto L300;
		    }
		    if (invar_2.kh == 15) {
			goto L308;
		    }
		    if (invar_2.kh == 26) {
			goto L844;
		    }
		    if (invar_2.kh == 27) {
			goto L845;
		    }
		    if (invar_2.kh == 28) {
			goto L846;
		    }
		    if (invar_2.kh == 29) {
			goto L847;
		    }
		    if (invar_2.kh == 35) {
			goto L301;
		    }
		    if (invar_2.kh != 31) {
			goto L941;
		    }
		    if (mode <= 0) {
			goto L941;
		    }
		    if (invar_2.ipb == 1) {
			goto L941;
		    }
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

/*     The following block supports third light to be computed from the */
/*     passed percentage of third luminosity. */

/*     IF(IB.GT.NVC) OBS(II)=(BR(IX)-EL3A(IB))/HLA(IB) */

		    if (ib > nvc) {
			if (*l3perc == 1) {
			    el3 = (hla[ib - 1] + cla[ib - 1]) * el3a[ib - 1] /
				     ((1. - el3a[ib - 1]) * 
				    12.566371999999999);
			} else {
			    el3 = el3a[ib - 1];
			}
			obs[ii - 1] = (br[ix - 1] - el3) / hla[ib - 1];
		    }

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
		    goto L420;
L941:
		    dl = del[invar_2.kh - 1];
		    if (isym == 1) {
			dl = del[invar_2.kh - 1] * .5;
		    }
		    sign = 1.;
		    iss = 1;
		    for (ih = 1; ih <= 35; ++ih) {
/* L421: */
			dlif[ih - 1] = 0.;
		    }
		    if (ksr <= 2) {
			goto L777;
		    }
		    iss = is;
		    dlif[invar_2.kh - 1] = 1.;
L777:
		    i__5 = iss;
		    for (il = 1; il <= i__5; ++il) {
			if (e != 0.) {
			    goto L4011;
			}
			if (isym == 1 && ix != ist) {
			    goto L4012;
			}
			goto L940;
L4011:
			if (ksr <= 2) {
			    goto L940;
			}
			goto L4014;
L4012:
			if (il == 2) {
			    goto L4016;
			}
L4014:
			if (low[invar_2.kh - 1] == 1) {
			    goto L314;
			}
			eccen_2.vol1 = svol1;
			eccen_2.vol2 = svol2;
			summ_1.summ1 = ssum1;
			summ_1.summ2 = ssum2;
			sm1 = ssm1;
			sm2 = ssm2;
			i__6 = mtlh;
			for (ire = 1; ire <= i__6; ++ire) {
/* L851: */
			    tldh[ire - 1] = stldh[ire - 1];
			}
			i__6 = m1h;
			for (ire = 1; ire <= i__6; ++ire) {
			    rv[ire - 1] = srv[ire - 1];
			    grx[ire - 1] = sgrx[ire - 1];
			    gry[ire - 1] = sgry[ire - 1];
			    grz[ire - 1] = sgrz[ire - 1];
			    glump1[ire - 1] = sglm1[ire - 1];
			    grv1[ire - 1] = sgrv1[ire - 1];
			    xx1[ire - 1] = sxx1[ire - 1];
			    yy1[ire - 1] = syy1[ire - 1];
			    zz1[ire - 1] = szz1[ire - 1];
			    gmag1[ire - 1] = sgmg1[ire - 1];
			    csbt1[ire - 1] = scsb1[ire - 1];
			    rf1[ire - 1] = srf1[ire - 1];
			    fr1[ire - 1] = sfr1[ire - 1];
/* L508: */
			    slump1[ire - 1] = slmp1[ire - 1];
			}
			i__6 = m2h;
			for (ire = 1; ire <= i__6; ++ire) {
			    rvq[ire - 1] = srvq[ire - 1];
			    grxq[ire - 1] = sgrxq[ire - 1];
			    gryq[ire - 1] = sgryq[ire - 1];
			    grzq[ire - 1] = sgrzq[ire - 1];
			    glump2[ire - 1] = sglm2[ire - 1];
			    grv2[ire - 1] = sgrv2[ire - 1];
			    xx2[ire - 1] = sxx2[ire - 1];
			    yy2[ire - 1] = syy2[ire - 1];
			    zz2[ire - 1] = szz2[ire - 1];
			    gmag2[ire - 1] = sgmg2[ire - 1];
			    csbt2[ire - 1] = scsb2[ire - 1];
			    rf2[ire - 1] = srf2[ire - 1];
			    fr2[ire - 1] = sfr2[ire - 1];
/* L309: */
			    slump2[ire - 1] = slmp2[ire - 1];
			}
			goto L940;
L4016:
			if (low[invar_2.kh - 1] == 1) {
			    goto L4018;
			}
			eccen_2.vol1 = evol1;
			eccen_2.vol2 = evol2;
			summ_1.summ1 = esum1;
			summ_1.summ2 = esum2;
			sm1 = esm1;
			sm2 = esm2;
			i__6 = mtlh;
			for (ire = 1; ire <= i__6; ++ire) {
/* L852: */
			    tldh[ire - 1] = etldh[ire - 1];
			}
			i__6 = m1h;
			for (ire = 1; ire <= i__6; ++ire) {
			    rv[ire - 1] = erv[ire - 1];
			    grx[ire - 1] = egrx[ire - 1];
			    gry[ire - 1] = egry[ire - 1];
			    grz[ire - 1] = egrz[ire - 1];
			    glump1[ire - 1] = eglm1[ire - 1];
			    grv1[ire - 1] = egrv1[ire - 1];
			    xx1[ire - 1] = exx1[ire - 1];
			    yy1[ire - 1] = eyy1[ire - 1];
			    zz1[ire - 1] = ezz1[ire - 1];
			    gmag1[ire - 1] = egmg1[ire - 1];
			    csbt1[ire - 1] = ecsb1[ire - 1];
			    rf1[ire - 1] = erf1[ire - 1];
			    fr1[ire - 1] = efr1[ire - 1];
/* L1508: */
			    slump1[ire - 1] = elmp1[ire - 1];
			}
			i__6 = m2h;
			for (ire = 1; ire <= i__6; ++ire) {
			    rvq[ire - 1] = ervq[ire - 1];
			    grxq[ire - 1] = egrxq[ire - 1];
			    gryq[ire - 1] = egryq[ire - 1];
			    grzq[ire - 1] = egrzq[ire - 1];
			    glump2[ire - 1] = eglm2[ire - 1];
			    grv2[ire - 1] = egrv2[ire - 1];
			    xx2[ire - 1] = exx2[ire - 1];
			    yy2[ire - 1] = eyy2[ire - 1];
			    zz2[ire - 1] = ezz2[ire - 1];
			    gmag2[ire - 1] = egmg2[ire - 1];
			    csbt2[ire - 1] = ecsb2[ire - 1];
			    rf2[ire - 1] = erf2[ire - 1];
			    fr2[ire - 1] = efr2[ire - 1];
/* L1309: */
			    slump2[ire - 1] = elmp2[ire - 1];
			}
			goto L940;
L4018:
			eccen_2.vol1 = evol1l;
			eccen_2.vol2 = evol2l;
			summ_1.summ1 = esum1l;
			summ_1.summ2 = esum2l;
			sm1 = esm1l;
			sm2 = esm2l;
			i__6 = mtll;
			for (ire = 1; ire <= i__6; ++ire) {
/* L853: */
			    tldl[ire - 1] = etldl[ire - 1];
			}
			i__6 = m1l;
			for (ire = 1; ire <= i__6; ++ire) {
			    rv[ire - 1] = ervl[ire - 1];
			    grx[ire - 1] = egrxl[ire - 1];
			    gry[ire - 1] = egryl[ire - 1];
			    grz[ire - 1] = egrzl[ire - 1];
			    glump1[ire - 1] = eglm1l[ire - 1];
			    grv1[ire - 1] = egrv1l[ire - 1];
			    xx1[ire - 1] = exx1l[ire - 1];
			    yy1[ire - 1] = eyy1l[ire - 1];
			    zz1[ire - 1] = ezz1l[ire - 1];
			    gmag1[ire - 1] = egmg1l[ire - 1];
			    csbt1[ire - 1] = ecsb1l[ire - 1];
			    rf1[ire - 1] = erf1l[ire - 1];
			    fr1[ire - 1] = efr1l[ire - 1];
/* L310: */
			    slump1[ire - 1] = elmp1l[ire - 1];
			}
			i__6 = m2l;
			for (ire = 1; ire <= i__6; ++ire) {
			    rvq[ire - 1] = ervql[ire - 1];
			    grxq[ire - 1] = egrxql[ire - 1];
			    gryq[ire - 1] = egryql[ire - 1];
			    grzq[ire - 1] = egrzql[ire - 1];
			    glump2[ire - 1] = eglm2l[ire - 1];
			    grv2[ire - 1] = egrv2l[ire - 1];
			    xx2[ire - 1] = exx2l[ire - 1];
			    yy2[ire - 1] = eyy2l[ire - 1];
			    zz2[ire - 1] = ezz2l[ire - 1];
			    gmag2[ire - 1] = egmg2l[ire - 1];
			    csbt2[ire - 1] = ecsb2l[ire - 1];
			    rf2[ire - 1] = erf2l[ire - 1];
			    fr2[ire - 1] = efr2l[ire - 1];
/* L311: */
			    slump2[ire - 1] = elmp2l[ire - 1];
			}
			goto L940;
L314:
			eccen_2.vol1 = svol1l;
			eccen_2.vol2 = svol2l;
			summ_1.summ1 = ssum1l;
			summ_1.summ2 = ssum2l;
			sm1 = ssm1l;
			sm2 = ssm2l;
			i__6 = mtll;
			for (ire = 1; ire <= i__6; ++ire) {
/* L854: */
			    tldl[ire - 1] = stldl[ire - 1];
			}
			i__6 = m1l;
			for (ire = 1; ire <= i__6; ++ire) {
			    rv[ire - 1] = srvl[ire - 1];
			    grx[ire - 1] = sgrxl[ire - 1];
			    gry[ire - 1] = sgryl[ire - 1];
			    grz[ire - 1] = sgrzl[ire - 1];
			    glump1[ire - 1] = sglm1l[ire - 1];
			    grv1[ire - 1] = sgrv1l[ire - 1];
			    xx1[ire - 1] = sxx1l[ire - 1];
			    yy1[ire - 1] = syy1l[ire - 1];
			    zz1[ire - 1] = szz1l[ire - 1];
			    gmag1[ire - 1] = sgmg1l[ire - 1];
			    csbt1[ire - 1] = scsb1l[ire - 1];
			    rf1[ire - 1] = srf1l[ire - 1];
			    fr1[ire - 1] = sfr1l[ire - 1];
/* L1310: */
			    slump1[ire - 1] = slmp1l[ire - 1];
			}
			i__6 = m2l;
			for (ire = 1; ire <= i__6; ++ire) {
			    rvq[ire - 1] = srvql[ire - 1];
			    grxq[ire - 1] = sgrxql[ire - 1];
			    gryq[ire - 1] = sgryql[ire - 1];
			    grzq[ire - 1] = sgrzql[ire - 1];
			    glump2[ire - 1] = sglm2l[ire - 1];
			    grv2[ire - 1] = sgrv2l[ire - 1];
			    xx2[ire - 1] = sxx2l[ire - 1];
			    yy2[ire - 1] = syy2l[ire - 1];
			    zz2[ire - 1] = szz2l[ire - 1];
			    gmag2[ire - 1] = sgmg2l[ire - 1];
			    csbt2[ire - 1] = scsb2l[ire - 1];
			    rf2[ire - 1] = srf2l[ire - 1];
			    fr2[ire - 1] = sfr2l[ire - 1];
/* L1311: */
			    slump2[ire - 1] = slmp2l[ire - 1];
			}
L940:
			dels = dl * sign;
			sign = -1.;
			if (nspa == 0) {
			    goto L470;
			}
			xlt = xlat[kspa + (nspa << 1) - 3] + dels * dlif[0];
			spots_1.xlng[kspa + (nspa << 1) - 3] = xlong[kspa + (
				nspa << 1) - 3] + dels * dlif[1];
			spots_1.snlat[kspa + (nspa << 1) - 3] = sin(xlt);
			spots_1.cslat[kspa + (nspa << 1) - 3] = cos(xlt);
			spots_1.snlng[kspa + (nspa << 1) - 3] = sin(
				spots_1.xlng[kspa + (nspa << 1) - 3]);
			spots_1.cslng[kspa + (nspa << 1) - 3] = cos(
				spots_1.xlng[kspa + (nspa << 1) - 3]);
			spots_1.rdsp[kspa + (nspa << 1) - 3] = radsp[kspa + (
				nspa << 1) - 3] + dels * dlif[2];
			spots_1.tmsp[kspa + (nspa << 1) - 3] = temsp[kspa + (
				nspa << 1) - 3] + dels * dlif[3];
L470:
			if (nspb == 0) {
			    goto L471;
			}
			xlt = xlat[kspb + (nspb << 1) - 3] + dels * dlif[4];
			spots_1.xlng[kspb + (nspb << 1) - 3] = xlong[kspb + (
				nspb << 1) - 3] + dels * dlif[5];
			spots_1.snlat[kspb + (nspb << 1) - 3] = sin(xlt);
			spots_1.cslat[kspb + (nspb << 1) - 3] = cos(xlt);
			spots_1.snlng[kspb + (nspb << 1) - 3] = sin(
				spots_1.xlng[kspb + (nspb << 1) - 3]);
			spots_1.cslng[kspb + (nspb << 1) - 3] = cos(
				spots_1.xlng[kspb + (nspb << 1) - 3]);
			spots_1.rdsp[kspb + (nspb << 1) - 3] = radsp[kspb + (
				nspb << 1) - 3] + dels * dlif[6];
			spots_1.tmsp[kspb + (nspb << 1) - 3] = temsp[kspb + (
				nspb << 1) - 3] + dels * dlif[7];
L471:
			eccen_2.ec = e + dels * dlif[9];
			flvar_2.pert = perr0 + dels * dlif[10];
			ff1 = f1 + dels * dlif[11];
			ff2 = f2 + dels * dlif[12];
			flvar_2.psh = pshift + dels * dlif[13];
			xinc = xincl + dels * dlif[15];
			g1 = gr1 + dels * dlif[16];
			g2 = gr2 + dels * dlif[17];
			t1 = tavh + dels * dlif[18];
			t2 = tavc + dels * dlif[19];
			a1 = alb1 + dels * dlif[20];
			a2 = alb2 + dels * dlif[21];
			dpdx_1.pot1 = phsv + dels * dlif[22];
			dpdx_1.pot2 = pcsv + dels * dlif[23];
			rmass = rm + dels * dlif[24];
			hl = hla[ib - 1] + dels * dlif[30];
			cl = cla[ib - 1] + dels * dlif[31];
			x1 = x1a[ib - 1] + dels * dlif[32];
			x2 = x2a[ib - 1] + dels * dlif[33];
			y1 = y1a[ib - 1];
			y2 = y2a[ib - 1];
			cld_1.opsf = opsfa[ib - 1];
			if (ksr == 1) {
			    goto L802;
			}
			if (ksr == 2) {
			    goto L872;
			}
			if (low[invar_2.kh - 1] == 1) {
			    goto L802;
			}
L872:
			modlog_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, 
				mmsavh, fr1, fr2, hld, &rmass, &dpdx_1.pot1, &
				dpdx_1.pot2, &g1, &g2, &a1, &a2, &n1, &n2, &
				ff1, &ff2, &mod, &xinc, &the, &mode, snthh, 
				csthh, snfih, csfih, grv1, grv2, xx1, yy1, 
				zz1, xx2, yy2, zz2, glump1, glump2, csbt1, 
				csbt2, gmag1, gmag2, glog1, glog2, tloc1, 
				tloc2, xinorm1, xinorm2);
			hot = 0.;
			cool = 0.;
			i__6 = *nph;
			for (iph = 1; iph <= i__6; ++iph) {
			    phasin = phas[ix - 1];
			    if (*nph > 1 && ib > nvc) {
				phasin = phas[ix - 1] + *delph * ((doublereal)
					 (iph - 1) / (doublereal) (*nph - 1) 
					- .5);
			    }
			    bbl_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, 
				    mmsavh, fr1, fr2, hld, slump1, slump2, 
				    theta, rho, aa, bb, &dpdx_1.pot1, &
				    dpdx_1.pot2, &n1, &n2, &ff1, &ff2, &d__, &
				    hl, &cl, &x1, &x2, &y1, &y2, &g1, &g2, &
				    wla[ib - 1], &sm1, &sm2, &tph, &tpc, &
				    sbrh, &sbrc, &t1, &t2, &a1, &a2, &xbol1, &
				    xbol2, &ybol1, &ybol2, &phasin, &rmass, &
				    xinc, &hotr, &coolr, snthh, csthh, snfih, 
				    csfih, tldh, glump1, glump2, xx1, xx2, 
				    yy1, yy2, zz1, zz2, &dint1, &dint2, grv1, 
				    grv2, rftemp, rf1, rf2, csbt1, csbt2, 
				    gmag1, gmag2, glog1, glog2, fbin1, fbin2, 
				    delv1, delv2, count1, count2, delwl1, 
				    delwl2, resf1, resf2, wl1, wl2, dvks1, 
				    dvks2, tau1, tau2, emm1, emm2, hbarw1, 
				    hbarw2, xcl, ycl, zcl, rcl, op1, fcl, 
				    dens, encl, edens, taug, emmg, yskp, zskp,
				     &mode, &iband[ib - 1], &ifat1, &ifat2, &
				    c__1, tloc1, tloc2, xinorm1, xinorm2);
			    hot += hotr / (doublereal) (*nph);
			    cool += coolr / (doublereal) (*nph);
/* L551: */
			}
			goto L801;
L802:
			modlog_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, 
				mmsavl, fr1, fr2, hld, &rmass, &dpdx_1.pot1, &
				dpdx_1.pot2, &g1, &g2, &a1, &a2, &n1l, &n2l, &
				ff1, &ff2, &mod, &xinc, &the, &mode, snthl, 
				csthl, snfil, csfil, grv1, grv2, xx1, yy1, 
				zz1, xx2, yy2, zz2, glump1, glump2, csbt1, 
				csbt2, gmag1, gmag2, glog1, glog2, tloc1, 
				tloc2, xinorm1, xinorm2);
			hot = 0.;
			cool = 0.;
			i__6 = *nph;
			for (iph = 1; iph <= i__6; ++iph) {
			    phasin = phas[ix - 1];
			    if (*nph > 1 && ib > nvc) {
				phasin = phas[ix - 1] + *delph * ((doublereal)
					 (iph - 1) / (doublereal) (*nph - 1) 
					- .5);
			    }
			    bbl_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, 
				    mmsavl, fr1, fr2, hld, slump1, slump2, 
				    theta, rho, aa, bb, &dpdx_1.pot1, &
				    dpdx_1.pot2, &n1l, &n2l, &ff1, &ff2, &d__,
				     &hl, &cl, &x1, &x2, &y1, &y2, &g1, &g2, &
				    wla[ib - 1], &sm1, &sm2, &tph, &tpc, &
				    sbrh, &sbrc, &t1, &t2, &a1, &a2, &xbol1, &
				    xbol2, &ybol1, &ybol2, &phasin, &rmass, &
				    xinc, &hotr, &coolr, snthl, csthl, snfil, 
				    csfil, tldl, glump1, glump2, xx1, xx2, 
				    yy1, yy2, zz1, zz2, &dint1, &dint2, grv1, 
				    grv2, rftemp, rf1, rf2, csbt1, csbt2, 
				    gmag1, gmag2, glog1, glog2, fbin1, fbin2, 
				    delv1, delv2, count1, count2, delwl1, 
				    delwl2, resf1, resf2, wl1, wl2, dvks1, 
				    dvks2, tau1, tau2, emm1, emm2, hbarw1, 
				    hbarw2, xcl, ycl, zcl, rcl, op1, fcl, 
				    dens, encl, edens, taug, emmg, yskp, zskp,
				     &mode, &iband[ib - 1], &ifat1, &ifat2, &
				    c__1, tloc1, tloc2, xinorm1, xinorm2);
			    hot += hotr / (doublereal) (*nph);
			    cool += coolr / (doublereal) (*nph);
/* L550: */
			}
L801:
			if (e != 0.) {
			    goto L4111;
			}
			if (isym == 0) {
			    goto L602;
			}
			if (ix != ist) {
			    goto L602;
			}
			if (ksr == 1) {
			    goto L602;
			}
			if (ksr == 2) {
			    goto L4119;
			}
			if (low[invar_2.kh - 1] == 1) {
			    goto L4112;
			}
			goto L4119;
L4111:
			if (invar_2.irte == 1) {
			    goto L602;
			}
			if (ksr >= 3) {
			    goto L602;
			}
			if (ksr == 2) {
			    goto L4119;
			}
L4112:
			if (il == 2) {
			    goto L4116;
			}
			svol1l = eccen_2.vol1;
			svol2l = eccen_2.vol2;
			ssum1l = summ_1.summ1;
			ssum2l = summ_1.summ2;
			ssm1l = sm1;
			ssm2l = sm2;
			i__6 = mtll;
			for (ihl = 1; ihl <= i__6; ++ihl) {
/* L855: */
			    stldl[ihl - 1] = tldl[ihl - 1];
			}
			i__6 = m1l;
			for (ihl = 1; ihl <= i__6; ++ihl) {
			    srvl[ihl - 1] = rv[ihl - 1];
			    sgrxl[ihl - 1] = grx[ihl - 1];
			    sgryl[ihl - 1] = gry[ihl - 1];
			    sgrzl[ihl - 1] = grz[ihl - 1];
			    slmp1l[ihl - 1] = slump1[ihl - 1];
			    sglm1l[ihl - 1] = glump1[ihl - 1];
			    sgrv1l[ihl - 1] = grv1[ihl - 1];
			    sxx1l[ihl - 1] = xx1[ihl - 1];
			    syy1l[ihl - 1] = yy1[ihl - 1];
			    szz1l[ihl - 1] = zz1[ihl - 1];
			    sgmg1l[ihl - 1] = gmag1[ihl - 1];
			    scsb1l[ihl - 1] = csbt1[ihl - 1];
			    srf1l[ihl - 1] = rf1[ihl - 1];
			    sfr1l[ihl - 1] = fr1[ihl - 1];
/* L603: */
			}
			i__6 = m2l;
			for (ihl = 1; ihl <= i__6; ++ihl) {
			    srvql[ihl - 1] = rvq[ihl - 1];
			    sgrxql[ihl - 1] = grxq[ihl - 1];
			    sgryql[ihl - 1] = gryq[ihl - 1];
			    sgrzql[ihl - 1] = grzq[ihl - 1];
			    slmp2l[ihl - 1] = slump2[ihl - 1];
			    sglm2l[ihl - 1] = glump2[ihl - 1];
			    sgrv2l[ihl - 1] = grv2[ihl - 1];
			    sxx2l[ihl - 1] = xx2[ihl - 1];
			    syy2l[ihl - 1] = yy2[ihl - 1];
			    szz2l[ihl - 1] = zz2[ihl - 1];
			    sgmg2l[ihl - 1] = gmag2[ihl - 1];
			    scsb2l[ihl - 1] = csbt2[ihl - 1];
			    srf2l[ihl - 1] = rf2[ihl - 1];
			    sfr2l[ihl - 1] = fr2[ihl - 1];
/* L606: */
			}
			goto L602;
L4116:
			evol1l = eccen_2.vol1;
			evol2l = eccen_2.vol2;
			esum1l = summ_1.summ1;
			esum2l = summ_1.summ2;
			esm1l = sm1;
			esm2l = sm2;
			i__6 = mtll;
			for (ihl = 1; ihl <= i__6; ++ihl) {
/* L856: */
			    etldl[ihl - 1] = tldl[ihl - 1];
			}
			i__6 = m1l;
			for (ihl = 1; ihl <= i__6; ++ihl) {
			    ervl[ihl - 1] = rv[ihl - 1];
			    egrxl[ihl - 1] = grx[ihl - 1];
			    egryl[ihl - 1] = gry[ihl - 1];
			    egrzl[ihl - 1] = grz[ihl - 1];
			    elmp1l[ihl - 1] = slump1[ihl - 1];
			    eglm1l[ihl - 1] = glump1[ihl - 1];
			    egrv1l[ihl - 1] = grv1[ihl - 1];
			    exx1l[ihl - 1] = xx1[ihl - 1];
			    eyy1l[ihl - 1] = yy1[ihl - 1];
			    ezz1l[ihl - 1] = zz1[ihl - 1];
			    egmg1l[ihl - 1] = gmag1[ihl - 1];
			    ecsb1l[ihl - 1] = csbt1[ihl - 1];
			    erf1l[ihl - 1] = rf1[ihl - 1];
			    efr1l[ihl - 1] = fr1[ihl - 1];
/* L1603: */
			}
			i__6 = m2l;
			for (ihl = 1; ihl <= i__6; ++ihl) {
			    ervql[ihl - 1] = rvq[ihl - 1];
			    egrxql[ihl - 1] = grxq[ihl - 1];
			    egryql[ihl - 1] = gryq[ihl - 1];
			    egrzql[ihl - 1] = grzq[ihl - 1];
			    elmp2l[ihl - 1] = slump2[ihl - 1];
			    eglm2l[ihl - 1] = glump2[ihl - 1];
			    egrv2l[ihl - 1] = grv2[ihl - 1];
			    exx2l[ihl - 1] = xx2[ihl - 1];
			    eyy2l[ihl - 1] = yy2[ihl - 1];
			    ezz2l[ihl - 1] = zz2[ihl - 1];
			    egmg2l[ihl - 1] = gmag2[ihl - 1];
			    ecsb2l[ihl - 1] = csbt2[ihl - 1];
			    erf2l[ihl - 1] = rf2[ihl - 1];
			    efr2l[ihl - 1] = fr2[ihl - 1];
/* L1606: */
			}
			goto L602;
L4119:
			if (il == 2) {
			    goto L4120;
			}
			svol1 = eccen_2.vol1;
			svol2 = eccen_2.vol2;
			ssum1 = summ_1.summ1;
			ssum2 = summ_1.summ2;
			ssm1 = sm1;
			ssm2 = sm2;
			i__6 = mtlh;
			for (ihh = 1; ihh <= i__6; ++ihh) {
/* L857: */
			    stldh[ihh - 1] = tldh[ihh - 1];
			}
			i__6 = m1h;
			for (ihh = 1; ihh <= i__6; ++ihh) {
			    srv[ihh - 1] = rv[ihh - 1];
			    sgrx[ihh - 1] = grx[ihh - 1];
			    sgry[ihh - 1] = gry[ihh - 1];
			    sgrz[ihh - 1] = grz[ihh - 1];
			    slmp1[ihh - 1] = slump1[ihh - 1];
			    sglm1[ihh - 1] = glump1[ihh - 1];
			    sgrv1[ihh - 1] = grv1[ihh - 1];
			    sxx1[ihh - 1] = xx1[ihh - 1];
			    syy1[ihh - 1] = yy1[ihh - 1];
			    szz1[ihh - 1] = zz1[ihh - 1];
			    sgmg1[ihh - 1] = gmag1[ihh - 1];
			    scsb1[ihh - 1] = csbt1[ihh - 1];
			    srf1[ihh - 1] = rf1[ihh - 1];
			    sfr1[ihh - 1] = fr1[ihh - 1];
/* L601: */
			}
			i__6 = m2h;
			for (ihh = 1; ihh <= i__6; ++ihh) {
			    srvq[ihh - 1] = rvq[ihh - 1];
			    sgrxq[ihh - 1] = grxq[ihh - 1];
			    sgryq[ihh - 1] = gryq[ihh - 1];
			    sgrzq[ihh - 1] = grzq[ihh - 1];
			    slmp2[ihh - 1] = slump2[ihh - 1];
			    sglm2[ihh - 1] = glump2[ihh - 1];
			    sgrv2[ihh - 1] = grv2[ihh - 1];
			    sxx2[ihh - 1] = xx2[ihh - 1];
			    syy2[ihh - 1] = yy2[ihh - 1];
			    szz2[ihh - 1] = zz2[ihh - 1];
			    sgmg2[ihh - 1] = gmag2[ihh - 1];
			    scsb2[ihh - 1] = csbt2[ihh - 1];
			    srf2[ihh - 1] = rf2[ihh - 1];
			    sfr2[ihh - 1] = fr2[ihh - 1];
/* L605: */
			}
			goto L602;
L4120:
			evol1 = eccen_2.vol1;
			evol2 = eccen_2.vol2;
			esum1 = summ_1.summ1;
			esum2 = summ_1.summ2;
			esm1 = sm1;
			esm2 = sm2;
			i__6 = mtlh;
			for (ihh = 1; ihh <= i__6; ++ihh) {
/* L858: */
			    etldh[ihh - 1] = tldh[ihh - 1];
			}
			i__6 = m1h;
			for (ihh = 1; ihh <= i__6; ++ihh) {
			    erv[ihh - 1] = rv[ihh - 1];
			    egrx[ihh - 1] = grx[ihh - 1];
			    egry[ihh - 1] = gry[ihh - 1];
			    egrz[ihh - 1] = grz[ihh - 1];
			    elmp1[ihh - 1] = slump1[ihh - 1];
			    eglm1[ihh - 1] = glump1[ihh - 1];
			    egrv1[ihh - 1] = grv1[ihh - 1];
			    exx1[ihh - 1] = xx1[ihh - 1];
			    eyy1[ihh - 1] = yy1[ihh - 1];
			    ezz1[ihh - 1] = zz1[ihh - 1];
			    egmg1[ihh - 1] = gmag1[ihh - 1];
			    ecsb1[ihh - 1] = csbt1[ihh - 1];
			    erf1[ihh - 1] = rf1[ihh - 1];
			    efr1[ihh - 1] = fr1[ihh - 1];
/* L1601: */
			}
			i__6 = m2h;
			for (ihh = 1; ihh <= i__6; ++ihh) {
			    ervq[ihh - 1] = rvq[ihh - 1];
			    egrxq[ihh - 1] = grxq[ihh - 1];
			    egryq[ihh - 1] = gryq[ihh - 1];
			    egrzq[ihh - 1] = grzq[ihh - 1];
			    elmp2[ihh - 1] = slump2[ihh - 1];
			    eglm2[ihh - 1] = glump2[ihh - 1];
			    egrv2[ihh - 1] = grv2[ihh - 1];
			    exx2[ihh - 1] = xx2[ihh - 1];
			    eyy2[ihh - 1] = yy2[ihh - 1];
			    ezz2[ihh - 1] = zz2[ihh - 1];
			    egmg2[ihh - 1] = gmag2[ihh - 1];
			    ecsb2[ihh - 1] = csbt2[ihh - 1];
			    erf2[ihh - 1] = rf2[ihh - 1];
			    efr2[ihh - 1] = fr2[ihh - 1];
/* L1605: */
			}
L602:
			htt = hot;
			if (mode == -1) {
			    htt = 0.;
			}
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

/*     The following block supports third light to be computed from the */
/*     passed percentage of third luminosity. */

			if (*l3perc == 1) {
			    el3 = (hla[ib - 1] + cla[ib - 1]) * el3a[ib - 1] /
				     ((1. - el3a[ib - 1]) * 
				    12.566371999999999);
			} else {
			    el3 = el3a[ib - 1];
			}

/*     XR=(HTT+COOL+EL3A(IB))*ELIT+VKM1*VC1+VKM2*VC2 */

			xr = (htt + cool + el3) * elit + flvar_2.vkm1 * vc1 + 
				flvar_2.vkm2 * vc2;

/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
			if (ksr != 1) {
			    goto L710;
			}
			bl[ix - 1] = xr;
			goto L420;
L710:
			if (ksr != 2) {
			    goto L711;
			}
			br[ix - 1] = xr;
			ii = nmat + ix;
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE modification: */

/*     OBS(II)=FLUX(IX)-XR */

			obs[ii - 1] = fluxes[ix] - xr;

/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
			if (iss == 2) {
			    goto L319;
			}
			goto L420;
L711:
			xlr = br[ix - 1];
			if (low[invar_2.kh - 1] == 1) {
			    xlr = bl[ix - 1];
			}
			if (il != 2) {
			    goto L388;
			}
			xlr = xr;
			goto L87;
L388:
			xnr = xr;
L87:
			khkeep = invar_2.kh * keep[invar_2.kh - 1];
			if (khkeep != 11 && khkeep != 14) {
			    obs[ii - 1] = (xnr - xlr) / del[invar_2.kh - 1];
			}
			if (invar_2.kh == 11) {
			    dfdap[ix - 1] = (xnr - xlr) / del[invar_2.kh - 1];
			}
			if (invar_2.kh == 14) {
			    dfdph[ix - 1] = (xnr - xlr) / del[invar_2.kh - 1];
			}
L319:
			;
		    }
		    goto L420;
L300:
		    if (ib <= nvc) {
			obs[ii - 1] = (br[ix - 1] - eccen_2.vga) / eccen_2.a;
		    }
		    goto L420;
L308:
		    if (ib <= nvc) {
			obs[ii - 1] = 1.;
		    }
		    goto L420;
L844:
		    obs[ii - 1] = dfdph[ix - 1] / (eccen_2.period + dtime * 
			    dpdt);
		    goto L420;
L845:
		    brac = eccen_2.period + dtime * dpdt;
		    obs[ii - 1] = dfdph[ix - 1] * dtime / (brac * 
			    eccen_2.period);
		    goto L420;
L846:
		    dis = (d__1 = dtime * dpdt / eccen_2.period, abs(d__1));
		    if (dis > toldis) {
			goto L848;
		    }
		    brac2 = eccen_2.period * 2. + dtime * dpdt;
/* Computing 2nd power */
		    d__1 = dtime / brac2;
/* Computing 3rd power */
		    d__2 = dtime;
/* Computing 2nd power */
		    d__3 = dpdt;
/* Computing 4th power */
		    d__4 = brac2, d__4 *= d__4;
		    dphpd = d__1 * d__1 * -2. + tt * (d__2 * (d__2 * d__2)) * 
			    (brac2 * 2. * dpdt - d__3 * d__3 * 3. * dtime) / (
			    d__4 * d__4);
		    goto L849;
L848:
		    brac = eccen_2.period + dtime * dpdt;
/* Computing 2nd power */
		    d__1 = dpdt;
		    dphpd = dtime / (brac * dpdt) - (log(brac) - log(
			    eccen_2.period)) / (d__1 * d__1);
L849:
		    obs[ii - 1] = -dfdph[ix - 1] * dphpd;
		    goto L420;
L847:
		    obs[ii - 1] = dtime * dfdap[ix - 1];
		    goto L420;
L301:
		    if (ib > nvc) {
			obs[ii - 1] = 1.;
		    }
L420:
		    ;
		}
/* L418: */
	    }
/* L417: */
	}
/* L419: */
    }
    s_wsfe(&io___694);
    e_wsfe();
    s_wsfe(&io___695);
    e_wsfe();
    s_wsfe(&io___696);
    e_wsfe();
    s_wsfe(&io___697);
    e_wsfe();
    s_wsfe(&io___698);
    e_wsfe();
    s_wsfe(&io___699);
    e_wsfe();
    i__1 = nlvc;
    for (icv = 1; icv <= i__1; ++icv) {
	icvp = icv + 1;
	nbs = knobs[icvp] - knobs[icv];
	iw = knobs[icv] + 1;
	jstart = nmat + iw;
	jstop = jstart + nbs - 1;
	resq = 0.;
	iww = iw - 1;
	i__2 = jstop;
	for (jres = jstart; jres <= i__2; ++jres) {
	    ++iww;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE modification: */

/* 299 resq=resq+wt(iww)*obs(jres)**2 */

/* L299: */
/* Computing 2nd power */
	    d__1 = obs[jres - 1];
	    resq += weights[iww] * (d__1 * d__1);
	}

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	s_wsfe(&io___709);
	do_fio(&c__1, (char *)&icv, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nbs, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&resq, (ftnlen)sizeof(doublereal));
	e_wsfe();
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

	chi2s[icv] = resq;

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* L298: */
    }
    s_wsfe(&io___710);
    e_wsfe();
    for (atmmessages_1.komp = 1; atmmessages_1.komp <= 2; 
	    ++atmmessages_1.komp) {
	if (atmmessages_1.message[atmmessages_1.komp - 1] == 1) {
	    s_wsfe(&io___711);
	    do_fio(&c__1, (char *)&atmmessages_1.komp, (ftnlen)sizeof(integer)
		    );
	    e_wsfe();
	}
	if (atmmessages_1.message[atmmessages_1.komp + 1] == 1) {
	    s_wsfe(&io___712);
	    do_fio(&c__1, (char *)&atmmessages_1.komp, (ftnlen)sizeof(integer)
		    );
	    e_wsfe();
	}
	if (atmmessages_1.message[atmmessages_1.komp + 3] == 1) {
	    s_wsfe(&io___713);
	    do_fio(&c__1, (char *)&atmmessages_1.komp, (ftnlen)sizeof(integer)
		    );
	    e_wsfe();
	}
	if (atmmessages_1.message[atmmessages_1.komp + 5] == 1) {
	    s_wsfe(&io___714);
	    do_fio(&c__1, (char *)&atmmessages_1.komp, (ftnlen)sizeof(integer)
		    );
	    e_wsfe();
	}
/* L909: */
    }
    s_wsfe(&io___715);
    e_wsfe();
    goto L65;
L71:
    jf = 0;
    if (ko == 0) {
	s_stop("", (ftnlen)0);
    }
    i__1 = ncof;
    for (j = 1; j <= i__1; ++j) {
/* L261: */
	obs[j - 1] = hold[j - 1];
    }
    if (kdisk == 0) {
	goto L72;
    }
    al__1.aerr = 0;
    al__1.aunit = 9;
    f_rew(&al__1);
    s_rsfe(&io___717);
    i__1 = ncof;
    for (j = 1; j <= i__1; ++j) {
	do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal));
    }
    e_rsfe();
L72:
    s_rsfe(&io___718);
    for (i__ = 1; i__ <= 35; ++i__) {
	do_fio(&c__1, (char *)&keep[i__ - 1], (ftnlen)sizeof(integer));
    }
    do_fio(&c__1, (char *)&ifder, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifm, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifr, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&xlamda, (ftnlen)sizeof(doublereal));
    e_rsfe();
    if (keep[0] != 2) {
	goto L866;
    }
    cl__1.cerr = 0;
    cl__1.cunit = 15;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = 16;
    cl__1.csta = 0;
    f_clos(&cl__1);
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: stop changed to return */

    return 0;

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
L866:
    for (i__ = 1; i__ <= 35; ++i__) {
/* L232: */
	if (kep[i__ - 1] == 1) {
	    keep[i__ - 1] = 1;
	}
    }
    nobs = knobs[lc1];
    matrix = 31;
    for (ima = 1; ima <= 30; ++ima) {
/* L428: */
	matrix -= keep[ima - 1];
    }
    matrix += nlc * (5 - keep[30] - keep[31] - keep[32] - keep[33] - keep[34])
	    ;
    mat = matrix - 1;
    em = (doublereal) (matrix - 15);
    ktr = (integer) (em * .24 + 2.2);
    if (em <= 1.5) {
	ktr = 1;
    }
    if (em > 12.) {
	ktr = 5;
    }
    ncoeff = matrix * nobs;
    kc = 1;
    nshift[0] = 0;
    for (i__ = 2; i__ <= 36; ++i__) {
	if (i__ > 31) {
	    kc = nlc;
	}
	ke = 0;
	j = i__ - 1;
	if (keep[j - 1] > kep[j - 1]) {
	    ke = 1;
	}
/* L59: */
	nshift[i__ - 1] = nobs * ke * kc + nshift[j - 1];
    }
    nobbs = nobs;
    for (i__ = 1; i__ <= 36; ++i__) {
	if (keep[i__ - 1] == 1) {
	    goto L30;
	}
	if (i__ > 30) {
	    nobbs = nobs * nlc;
	}
	if (i__ == 36) {
	    nobbs = nobs;
	}
	i__1 = nobbs;
	for (j = 1; j <= i__1; ++j) {
	    ++jf;
	    kx = jf + nshift[i__ - 1];
/* L32: */
	    obs[jf - 1] = obs[kx - 1];
	}
L30:
	;
    }
L65:
    s_wsfe(&io___724);
    for (i__ = 1; i__ <= 35; ++i__) {
	do_fio(&c__1, (char *)&keep[i__ - 1], (ftnlen)sizeof(integer));
    }
    do_fio(&c__1, (char *)&ifder, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifm, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ifr, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&xlamda, (ftnlen)sizeof(doublereal));
    e_wsfe();
    nobs = knobs[lc1];
    s_wsfe(&io___725);
    e_wsfe();
    if (ifder == 0) {
	ktr = 5;
    }
    s_wsfe(&io___726);
    e_wsfe();
    s_wsfe(&io___727);
    e_wsfe();
    i__1 = nlvc;
    for (ib = 1; ib <= i__1; ++ib) {
	ist = knobs[ib] + 1;
	ib1 = ib + 1;
	isp = knobs[ib1];
	i__2 = isp;
	for (i__ = ist; i__ <= i__2; ++i__) {
	    switch (ktr) {
		case 1:  goto L5;
		case 2:  goto L6;
		case 3:  goto L7;
		case 4:  goto L8;
		case 5:  goto L96;
	    }
L5:
	    s_wsfe(&io___728);
	    i__3 = ncoeff;
	    i__4 = nobs;
	    for (j = i__; i__4 < 0 ? j >= i__3 : j <= i__3; j += i__4) {
		do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal))
			;
	    }
	    e_wsfe();
	    goto L96;
L6:
	    s_wsfe(&io___729);
	    i__4 = ncoeff;
	    i__3 = nobs;
	    for (j = i__; i__3 < 0 ? j >= i__4 : j <= i__4; j += i__3) {
		do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal))
			;
	    }
	    e_wsfe();
	    goto L96;
L7:
	    s_wsfe(&io___730);
	    i__3 = ncoeff;
	    i__4 = nobs;
	    for (j = i__; i__4 < 0 ? j >= i__3 : j <= i__3; j += i__4) {
		do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal))
			;
	    }
	    e_wsfe();
	    goto L96;
L8:
	    s_wsfe(&io___731);
	    i__4 = ncoeff;
	    i__3 = nobs;
	    for (j = i__; i__3 < 0 ? j >= i__4 : j <= i__4; j += i__3) {
		do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal))
			;
	    }
	    e_wsfe();
L96:
	    ;
	}
    }
    if (ko <= 1) {
	goto L70;
    }
    if (ibef == 1) {
	goto L70;
    }
    i__2 = ncoeff;
    for (j = 1; j <= i__2; ++j) {
/* L62: */
	hold[j - 1] = obs[j - 1];
    }
    if (kdisk == 0) {
	goto L73;
    }
    al__1.aerr = 0;
    al__1.aunit = 9;
    f_rew(&al__1);
    s_wsfe(&io___732);
    i__2 = ncoeff;
    for (j = 1; j <= i__2; ++j) {
	do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal));
    }
    e_wsfe();
L73:
L70:
    s_wsfe(&io___733);
    e_wsfe();
    i__2 = nlvc;
    for (ib = 1; ib <= i__2; ++ib) {
	ist = knobs[ib] + 1;
	ib1 = ib + 1;
	isp = knobs[ib1];
	nois = noise[ib - 1];
	i__1 = isp;
	for (i__ = ist; i__ <= i__1; ++i__) {
	    if (ib > nvc) {
		goto L444;
	    }
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE modification: */

/*     ROOTWT=dsqrt(WT(I))/(100.d0*SIGMA(IB)) */

/*     This is level-dependent weighting for RV curves: */
	    rootwt = sqrt(weights[i__]) / sigma[ib - 1];

/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	    goto L445;
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE modification: */

/* 444 ROOTWT=dsqrt(WT(I))/(100.d0*SIGMA(IB)*dsqrt(FLUX(I))**NOIS) */

/*     This is level-dependent weighting for light curves: */
L444:
	    d__1 = sqrt(fluxes[i__]);
	    rootwt = sqrt(weights[i__]) / (sigma[ib - 1] * pow_di(&d__1, &
		    nois));

/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
L445:
	    i__3 = ncoeff;
	    i__4 = nobs;
	    for (lob = i__; i__4 < 0 ? lob >= i__3 : lob <= i__3; lob += i__4)
		     {
/* L97: */
		obs[lob - 1] *= rootwt;
	    }
	}
    }
    if (ifder != 0) {
	s_wsfe(&io___737);
	e_wsfe();
    }
    if (ifder != 0) {
	s_wsfe(&io___738);
	e_wsfe();
    }
    i__4 = nobs;
    for (i__ = 1; i__ <= i__4; ++i__) {
	switch (ktr) {
	    case 1:  goto L45;
	    case 2:  goto L46;
	    case 3:  goto L47;
	    case 4:  goto L48;
	    case 5:  goto L98;
	}
L45:
	s_wsfe(&io___739);
	i__3 = ncoeff;
	i__1 = nobs;
	for (j = i__; i__1 < 0 ? j >= i__3 : j <= i__3; j += i__1) {
	    do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
	goto L98;
L46:
	s_wsfe(&io___740);
	i__1 = ncoeff;
	i__3 = nobs;
	for (j = i__; i__3 < 0 ? j >= i__1 : j <= i__1; j += i__3) {
	    do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
	goto L98;
L47:
	s_wsfe(&io___741);
	i__3 = ncoeff;
	i__1 = nobs;
	for (j = i__; i__1 < 0 ? j >= i__3 : j <= i__3; j += i__1) {
	    do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
	goto L98;
L48:
	s_wsfe(&io___742);
	i__1 = ncoeff;
	i__3 = nobs;
	for (j = i__; i__3 < 0 ? j >= i__1 : j <= i__1; j += i__3) {
	    do_fio(&c__1, (char *)&obs[j - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
L98:
	;
    }
    square_(obs, &nobs, &mat, out, sd, &xlamda, &deter, cn, cnn, cnc, clc, &s,
	     ccl, ll, mm);
    msq = mat * mat;
    if (ifm == 0) {
	goto L436;
    }
    s_wsfe(&io___755);
    e_wsfe();
    s_wsfe(&io___756);
    e_wsfe();
    s_wsfe(&io___757);
    e_wsfe();
    i__4 = mat;
    for (jr = 1; jr <= i__4; ++jr) {
/* L38: */
	s_wsfe(&io___759);
	i__3 = msq;
	i__1 = mat;
	for (jx = jr; i__1 < 0 ? jx >= i__3 : jx <= i__3; jx += i__1) {
	    do_fio(&c__1, (char *)&cn[jx - 1], (ftnlen)sizeof(doublereal));
	}
	do_fio(&c__1, (char *)&ccl[jr - 1], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    s_wsfe(&io___761);
    e_wsfe();
    s_wsfe(&io___762);
    e_wsfe();
    s_wsfe(&io___763);
    e_wsfe();
L436:
    no1 = 23;
    no2 = 24;
    nrm = 25;
    for (irm = 1; irm <= 24; ++irm) {
	if (irm <= 23) {
	    no1 -= keep[irm - 1];
	}
	no2 -= keep[irm - 1];
/* L334: */
	nrm -= keep[irm - 1];
    }
    coro1 = (doublereal) (1 - keep[22]);
    coro2 = (doublereal) (1 - keep[23]);
    corq = (doublereal) (1 - keep[24]);
    i__1 = mat;
    for (jm = 1; jm <= i__1; ++jm) {
	i__3 = mat;
	for (jq = 1; jq <= i__3; ++jq) {
	    jt = jm + mat * (jq - 1);
	    ijm = (mat + 1) * (jm - 1) + 1;
	    ijq = (mat + 1) * (jq - 1) + 1;
	    v[jq - 1] = cnn[jt - 1] / sqrt(cnn[ijm - 1] * cnn[ijq - 1]);
	    cormat[(jm - 1) * mat + jq] = v[jq - 1];
/* L33: */
	}
	co1q = 0.;
	co2q = 0.;
	if (jm == nrm && no1 > 0) {
	    co1q = v[no1 - 1] * corq * coro1;
	}
	if (jm == nrm && no2 > 0) {
	    co2q = v[no2 - 1] * corq * coro2;
	}
/* L34: */
	s_wsfe(&io___779);
	i__3 = mat;
	for (im = 1; im <= i__3; ++im) {
	    do_fio(&c__1, (char *)&v[im - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
    }
    if (ifm == 0) {
	goto L36;
    }
    s_wsfe(&io___781);
    e_wsfe();
    s_wsfe(&io___782);
    e_wsfe();
    s_wsfe(&io___783);
    e_wsfe();
    dgmprd_(cn, cnn, cnout, &mat, &mat, &mat);
    i__3 = mat;
    for (j8 = 1; j8 <= i__3; ++j8) {
/* L116: */
	s_wsfe(&io___786);
	i__1 = msq;
	i__4 = mat;
	for (j7 = j8; i__4 < 0 ? j7 >= i__1 : j7 <= i__1; j7 += i__4) {
	    do_fio(&c__1, (char *)&cnout[j7 - 1], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
    }
    s_wsfe(&io___788);
    e_wsfe();
    s_wsfe(&io___789);
    e_wsfe();
    s_wsfe(&io___790);
    e_wsfe();
    ansch = 0.;
    i__4 = mat;
    for (j5 = 1; j5 <= i__4; ++j5) {
	v[j5 - 1] = 0.;
	i__1 = mat;
	for (j6 = 1; j6 <= i__1; ++j6) {
	    int__ = mat * (j6 - 1);
	    idi = j6 + int__;
	    i9 = j5 + int__;
/* L117: */
	    v[j5 - 1] = out[j6 - 1] * cn[i9 - 1] * sqrt(cnc[idi - 1]) + v[j5 
		    - 1];
	}
	err = v[j5 - 1] - ccl[j5 - 1];
/* L118: */
	ansch += abs(err);
    }
    s_wsfe(&io___798);
    i__4 = mat;
    for (j4 = 1; j4 <= i__4; ++j4) {
	do_fio(&c__1, (char *)&v[j4 - 1], (ftnlen)sizeof(doublereal));
    }
    e_wsfe();
    s_wsfe(&io___800);
    e_wsfe();
    s_wsfe(&io___801);
    do_fio(&c__1, (char *)&ansch, (ftnlen)sizeof(doublereal));
    e_wsfe();
L36:
    s_wsfe(&io___802);
    e_wsfe();
    s_wsfe(&io___803);
    e_wsfe();
    s_wsfe(&io___804);
    e_wsfe();
    s_wsfe(&io___805);
    e_wsfe();
    s_wsfe(&io___806);
    e_wsfe();
    iout = 0;
    for (kpar = 1; kpar <= 35; ++kpar) {
	imax = 1;
	if (kpar > 30) {
	    imax = nlc;
	}
	if (keep[kpar - 1] == 1) {
	    goto L93;
	}
	i__4 = imax;
	for (kurv = 1; kurv <= i__4; ++kurv) {
	    kcurv = kurv;
	    if (kpar <= 30) {
		kcurv = 0;
	    }
	    ++iout;
	    ipar = kpar;
	    if (kpar > 30) {
		ipar = kurv + 30 + (kpar - 31) * nlc;
	    }
	    parout = para[ipar - 1] + out[iout - 1];
	    s_wsfe(&io___814);
	    do_fio(&c__1, (char *)&kpar, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&kcurv, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&para[ipar - 1], (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&out[iout - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&parout, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&sd[iout - 1], (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* L94: */
	}
L93:
	;
    }
    s_wsfe(&io___815);
    e_wsfe();
    s_wsfe(&io___816);
    e_wsfe();
    s_wsfe(&io___817);
    e_wsfe();
    s_wsfe(&io___818);
    e_wsfe();
    s_wsfe(&io___819);
    e_wsfe();
    iout = 0;
    for (kpar = 1; kpar <= 35; ++kpar) {
	imax = 1;
	if (kpar > 30) {
	    imax = nlc;
	}
	if (keep[kpar - 1] == 1) {
	    goto L53;
	}
	i__4 = imax;
	for (kurv = 1; kurv <= i__4; ++kurv) {
	    kcurv = kurv;
	    if (kpar <= 30) {
		kcurv = 0;
	    }
	    ++iout;
	    ipar = kpar;
	    if (kpar > 30) {
		ipar = kurv + 30 + (kpar - 31) * nlc;
	    }
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

/*     The following block supports third light to be computed from the */
/*     passed percentage of third luminosity. */

	    hlum = hla[kcurv - 1];
	    if (kpar == 31) {
		hlum = para[ipar - 1] + out[iout - 1];
	    }
	    clum = cla[kcurv - 1];
	    if (kpar == 32) {
		clum = para[ipar - 1] + out[iout - 1];
	    }
	    if (kpar == 35 && *l3perc == 1) {
		out[iout - 1] = out[iout - 1] * 12.5663704 / (hlum + clum + 
			out[iout - 1] * 12.5663704);
		sd[iout - 1] = sd[iout - 1] * 12.5663704 / (hlum + clum + sd[
			iout - 1] * 12.5663704);
	    }

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	    parout = para[ipar - 1] + out[iout - 1];
	    s_wsfe(&io___822);
	    do_fio(&c__1, (char *)&kpar, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&kcurv, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&para[ipar - 1], (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&out[iout - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&parout, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&sd[iout - 1], (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

	    corrs[iout] = out[iout - 1];
	    stdevs[iout] = sd[iout - 1];

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* L52: */
	}
L53:
	;
    }
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

    i__4 = nlc;
    for (icla = 1; icla <= i__4; ++icla) {
	ccla[icla] = cla[nvc + icla - 1];
/* L99999: */
    }

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    s_wsfe(&io___824);
    e_wsfe();
    ressq = 0.;
    jst = mat * nobs + 1;
    i__4 = ncoeff;
    for (jres = jst; jres <= i__4; ++jres) {
/* L199: */
/* Computing 2nd power */
	d__1 = obs[jres - 1];
	ressq += d__1 * d__1;
    }
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

    *cfval = ressq;

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    s_wsfe(&io___827);
    e_wsfe();
    s_wsfe(&io___828);
    e_wsfe();
    s_wsfe(&io___829);
    do_fio(&c__1, (char *)&ressq, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&s, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&deter, (ftnlen)sizeof(doublereal));
    e_wsfe();
    ibef = 1;
    if (ifr == 0) {
	goto L71;
    }
    s_wsfe(&io___830);
    e_wsfe();
    s_wsfe(&io___831);
    e_wsfe();
    s_wsfe(&io___832);
    e_wsfe();
    s_wsfe(&io___833);
    e_wsfe();
    s_wsfe(&io___834);
    e_wsfe();
    s_wsfe(&io___835);
    e_wsfe();
    s_wsfe(&io___836);
    e_wsfe();
    do1 = 0.f;
    if (no1 != 0) {
	do1 = sd[no1 - 1] * coro1;
    }
    do2 = 0.f;
    if (no2 != 0) {
	do2 = sd[no2 - 1] * coro2;
    }
    if (mod == 1) {
	do2 = do1;
    }
    if (mod == 1) {
	co2q = co1q;
    }
    dq = sd[nrm - 1] * corq;
    coq = co1q;
    f = f1;
    flvar_2.dp = 1. - e;
    ome = phsv;
    dom = do1;
    atmmessages_1.komp = 0;
L925:
    ++atmmessages_1.komp;
    for (kd = 1; kd <= 4; ++kd) {
	if (kd != 2) {
	    goto L928;
	}
	if (po[atmmessages_1.komp - 1] >= omcr[atmmessages_1.komp - 1]) {
	    goto L928;
	}
	goto L926;
L928:
	th = xtha[kd - 1];
	fi = xfia[kd - 1];
	romq_(&ome, &rm, &f, &flvar_2.dp, &e, &th, &fi, &r__, &drdo, &drdq, &
		dodq, &atmmessages_1.komp, &mode);
/* Computing 2nd power */
	d__1 = drdq;
/* Computing 2nd power */
	d__2 = dq;
/* Computing 2nd power */
	d__3 = drdo;
/* Computing 2nd power */
	d__4 = dom;
	dr = sqrt(d__1 * d__1 * (d__2 * d__2) + d__3 * d__3 * (d__4 * d__4) + 
		coq * 2. * drdq * drdo * dq * dom);
	s_wsfe(&io___852);
	do_fio(&c__1, (char *)&atmmessages_1.komp, (ftnlen)sizeof(integer));
	do_fio(&c__1, arad + (kd - 1) * 10, (ftnlen)10);
	do_fio(&c__1, (char *)&r__, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&drdo, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&drdq, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&dr, (ftnlen)sizeof(doublereal));
	e_wsfe();
L926:
	;
    }
    do2dq = dodq;
    if (atmmessages_1.komp == 1) {
	do1dq = dodq;
    }
    coq = co2q;
    f = f2;
    ome = pcsv;
    dom = do2;
    s_wsfe(&io___855);
    e_wsfe();
    if (atmmessages_1.komp == 1) {
	goto L925;
    }
    s_wsfe(&io___856);
    e_wsfe();
    s_wsfe(&io___857);
    e_wsfe();
    if (atmmessages_1.komp == 2) {
	s_wsfe(&io___858);
	do_fio(&c__1, (char *)&do1dq, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&do2dq, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&co1q, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&co2q, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&do1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&do2, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&dq, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    goto L71;
} /* dc_ */

/* Subroutine */ int dgmprd_(doublereal *a, doublereal *b, doublereal *r__, 
	integer *n, integer *m, integer *l)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k, ib, ji, ik, ir;

/*  Version of April 9, 1992 */
    /* Parameter adjustments */
    --r__;
    --b;
    --a;

    /* Function Body */
    ir = 0;
    ik = -(*m);
    i__1 = *l;
    for (k = 1; k <= i__1; ++k) {
	ik += *m;
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    ++ir;
	    ji = j - *n;
	    ib = ik;
	    r__[ir] = 0.;
	    i__3 = *m;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		ji += *n;
		++ib;
/* L10: */
		r__[ir] += a[ji] * b[ib];
	    }
	}
    }
    return 0;
} /* dgmprd_ */

/* Subroutine */ int dminv_(doublereal *a, integer *n, doublereal *d__, 
	integer *l, integer *m)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Local variables */
    static integer i__, j, k, ij, ki, ji, kk, jk, ik, nk, jp, kj, jq, jr, iz;
    static doublereal biga, hold;

/*  Version of January 9, 2002 */
    /* Parameter adjustments */
    --m;
    --l;
    --a;

    /* Function Body */
    *d__ = 1.;
    nk = -(*n);
    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
	nk += *n;
	l[k] = k;
	m[k] = k;
	kk = nk + k;
	biga = a[kk];
	i__2 = *n;
	for (j = k; j <= i__2; ++j) {
	    iz = *n * (j - 1);
	    i__3 = *n;
	    for (i__ = k; i__ <= i__3; ++i__) {
		ij = iz + i__;
		if (abs(biga) >= (d__1 = a[ij], abs(d__1))) {
		    goto L20;
		}
		biga = a[ij];
		l[k] = i__;
		m[k] = j;
L20:
		;
	    }
	}
	j = l[k];
	if (j <= k) {
	    goto L35;
	}
	ki = k - *n;
	i__3 = *n;
	for (i__ = 1; i__ <= i__3; ++i__) {
	    ki += *n;
	    hold = -a[ki];
	    ji = ki - k + j;
	    a[ki] = a[ji];
/* L30: */
	    a[ji] = hold;
	}
L35:
	i__ = m[k];
	if (i__ <= k) {
	    goto L45;
	}
	jp = *n * (i__ - 1);
	i__3 = *n;
	for (j = 1; j <= i__3; ++j) {
	    jk = nk + j;
	    ji = jp + j;
	    hold = -a[jk];
	    a[jk] = a[ji];
/* L40: */
	    a[ji] = hold;
	}
L45:
	if (biga != 0.) {
	    goto L48;
	}
	*d__ = 0.;
	return 0;
L48:
	i__3 = *n;
	for (i__ = 1; i__ <= i__3; ++i__) {
	    if (i__ == k) {
		goto L55;
	    }
	    ik = nk + i__;
	    a[ik] /= -biga;
L55:
	    ;
	}
	i__3 = *n;
	for (i__ = 1; i__ <= i__3; ++i__) {
	    ik = nk + i__;
	    hold = a[ik];
	    ij = i__ - *n;
	    i__2 = *n;
	    for (j = 1; j <= i__2; ++j) {
		ij += *n;
		if (i__ == k) {
		    goto L65;
		}
		if (j == k) {
		    goto L65;
		}
		kj = ij - i__ + k;
		a[ij] = hold * a[kj] + a[ij];
L65:
		;
	    }
	}
	kj = k - *n;
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    kj += *n;
	    if (j == k) {
		goto L75;
	    }
	    a[kj] /= biga;
L75:
	    ;
	}
	*d__ *= biga;
	a[kk] = 1. / biga;
/* L80: */
    }
    k = *n;
L100:
    --k;
    if (k <= 0) {
	return 0;
    }
    i__ = l[k];
    if (i__ <= k) {
	goto L120;
    }
    jq = *n * (k - 1);
    jr = *n * (i__ - 1);
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	jk = jq + j;
	hold = a[jk];
	ji = jr + j;
	a[jk] = -a[ji];
/* L110: */
	a[ji] = hold;
    }
L120:
    j = m[k];
    if (j <= k) {
	goto L100;
    }
    ki = k - *n;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ki += *n;
	hold = a[ki];
	ji = ki - k + j;
	a[ki] = -a[ji];
/* L130: */
	a[ji] = hold;
    }
    goto L100;
} /* dminv_ */

/* Subroutine */ int dura_(doublereal *f, doublereal *xincl, doublereal *rm, 
	doublereal *d__, doublereal *the, doublereal *omeg, doublereal *r__)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal), sqrt(doublereal);

    /* Local variables */
    static doublereal x, y, z__, c1, c2, c3, c4, c5, c6, c7, fc, ci, ct, th, 
	    si, st, tt, yz2, rmd, par, dsq, fsq, rmd1, par32, par52, delx, 
	    coti, xinc, rpar, dfcdx, abdelx;

/*  Version of May 19, 1996 */

/*     PARAMETER 'THE' IS THE SEMI-DURATION OF X-RAY ECLIPSE, AND SHOULD */
/*     BE IN CIRCULAR MEASURE. */
    delx = 0.;
    fsq = *f * *f;
    rmd = 1. / *rm;
    rmd1 = rmd + 1.;
    xinc = *xincl * .017453293;
    th = *the * 6.2831853071795865;
    ci = cos(xinc);
    si = sin(xinc);
    dsq = *d__ * *d__;
    st = sin(th);
    ct = cos(th);
    coti = ci / si;
    tt = st / ct;
    c1 = ct * si;
    c2 = tt * st * si;
    c3 = c1 + c2;
    c4 = coti * ci / ct;
    c5 = c3 + c4;
    c6 = c2 + c4;
/* Computing 2nd power */
    d__1 = ct;
    c7 = (st * st + coti * coti) / (d__1 * d__1);
    x = *d__ * (si * si * st * st + ci * ci) + 1e-5;
L15:
    x += delx;
/* Computing 2nd power */
    d__1 = *d__ - x;
    par = x * x + c7 * (d__1 * d__1);
    rpar = sqrt(par);
    par32 = par * rpar;
    par52 = par * par32;
/* Computing 3rd power */
    d__1 = c1;
/* Computing 2nd power */
    d__2 = *d__ - x;
    fc = (c6 * *d__ - c5 * x) / par32 + d__1 * (d__1 * d__1) * c5 * rmd / (
	    d__2 * d__2) + c3 * fsq * rmd1 * x - c2 * fsq * *d__ * rmd1 - c1 *
	     rmd / dsq;
/* Computing 3rd power */
    d__1 = c1;
/* Computing 3rd power */
    d__2 = *d__ - x;
    dfcdx = (-c5 * par - (c6 * *d__ - c5 * x) * 3. * ((c7 + 1.) * x - c7 * *
	    d__)) / par52 + d__1 * (d__1 * d__1) * 2. * c5 * rmd / (d__2 * (
	    d__2 * d__2)) + c3 * fsq * rmd1;
    delx = -fc / dfcdx;
    abdelx = abs(delx);
    if (abdelx > 1e-7) {
	goto L15;
    }
    y = -(*d__ - x) * tt;
    z__ = -(*d__ - x) * coti / ct;
    yz2 = y * y + z__ * z__;
/* Computing 2nd power */
    d__1 = *d__ - x;
    *omeg = 1. / sqrt(x * x + yz2) + rmd / sqrt(d__1 * d__1 + yz2) + rmd1 * 
	    .5 * fsq * (x * x + y * y) - rmd * x / dsq;
    *omeg = *rm * *omeg + (1. - *rm) * .5;
    *r__ = sqrt(x * x + yz2);
    return 0;
} /* dura_ */

/* Subroutine */ int ellone_(doublereal *ff, doublereal *dd, doublereal *rm, 
	doublereal *xl1, doublereal *om1, doublereal *xl2, doublereal *om2)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal d__, f;
    static integer i__;
    static doublereal p, rp, ot, xl, rm1, dsq, prp, xsq, xmu3, rfac, abdel;
    static integer icase;
    static doublereal dxldf, delxl, oldxl, rmass;
    static integer kount;
    static doublereal xmu3cr, d2xldf2;

/*  Version of December 4, 2003 */
/*     XL2 AND OM2 VALUES ASSUME SYNCHRONOUS ROTATION AND CIRCULAR ORBIT. */
/*     THEY ARE NOT NEEDED FOR NON-SYNCHRONOUS OR NON-CIRCULAR CASES. */

/*  Starting on August 13, 2003, ELLONE includes a 2nd derivative term */
/*    in the N-R solution for the null point of effective gravity (XL1) */

    ot = .33333333333333331;
    icase = 2;
    if (*ff != 1. || eccen_3.ecc > 0.) {
	icase = 1;
    }
    rmass = *rm;
    d__ = *dd;
    xl = d__ / (sqrt(*rm) + 1.);
    oldxl = xl;
    i__1 = icase;
    for (i__ = 1; i__ <= i__1; ++i__) {
	rfac = *ff * *ff;
	if (i__ == 2) {
	    rfac = 1.;
	}
	if (i__ == 2) {
	    d__ = 1.;
	}
	dsq = d__ * d__;
	delxl = 0.;
	rm1 = rmass + 1.;
	kount = 0;
L88:
	xl += delxl;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*  The next block of lines halves the delxl step in case */
/*  xl were to jump beyond the value d or below value */
/*  0.0 during the iteration. */
	if (i__ == 2) {
	    goto L170;
	}
	if (xl < *dd && xl > 0.) {
	    goto L170;
	}
	delxl *= .5;
	xl = oldxl;
	goto L88;
L170:
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	++kount;
	xsq = xl * xl;
/* Computing 2nd power */
	d__1 = d__ - xl;
	p = d__1 * d__1;
	rp = (d__1 = d__ - xl, abs(d__1));
	prp = p * rp;
	f = rfac * rm1 * xl - 1. / xsq - rmass * (xl - d__) / prp - rmass / 
		dsq;
	dxldf = 1. / (rfac * rm1 + 2. / (xsq * xl) + rmass * 2. / prp);
/* Computing 3rd power */
	d__1 = dxldf;
/* Computing 4th power */
	d__2 = xl, d__2 *= d__2;
/* Computing 4th power */
	d__3 = rp, d__3 *= d__3;
	d2xldf2 = d__1 * (d__1 * d__1) * 6. * (1. / (d__2 * d__2) - rmass / (
		d__3 * d__3));
	delxl = -f * dxldf + f * .5 * f * d2xldf2;
	abdel = abs(delxl);
	oldxl = xl;
	if (abdel > 1e-10) {
	    goto L88;
	}
	if (i__ == 2) {
	    goto L8;
	}
	*xl1 = xl;
	*om1 = 1. / xl + rmass * (1. / rp - xl / dsq) + rm1 * .5 * xsq * rfac;
	if (*rm > 1.) {
	    rmass = 1. / rmass;
	}
	xmu3 = rmass / ((rmass + 1.) * 3.);
	xmu3cr = pow_dd(&xmu3, &ot);
/* L5: */
	xl = xmu3cr + 1. + xmu3cr * xmu3cr / 3. + xmu3 / 9.;
    }
L8:
    if (*rm > 1.) {
	xl = d__ - xl;
    }
    rm1 = *rm + 1.;
    *xl2 = xl;
    *om2 = 1. / abs(xl) + *rm * (1. / sqrt(1. - xl - xl + xl * xl) - xl) + 
	    rm1 * .5 * xl * xl;
    return 0;
} /* ellone_ */

/* Subroutine */ int fourls_(doublereal *th, doublereal *ro, integer *nobs, 
	integer *nth, doublereal *aa, doublereal *bb)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal);

    /* Local variables */
    static doublereal d__;
    static integer i__, j, k, ic;
    static doublereal cl[14], cn[196];
    static integer ii, jj, kk, ll[14], ml, mm[14], is, iz;
    static doublereal cs2, cs3, cs4, cs5, sn3;
    static integer iii, nob;
    static doublereal obs[50000];
    static integer ipl, mpl;
    static doublereal out[14], sncs, cost, sint;
    static integer jjmax;
    extern /* Subroutine */ int dminv_(doublereal *, integer *, doublereal *, 
	    integer *, integer *), dgmprd_(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *);
    static integer nobmpl, nobsml;

/*   version of September 14, 1998 */

/*    Input integer nth is the largest Fourier term fitted (e.g. */
/*       for nth=6, terms up to sine & cosine of 6 theta are */
/*       evaluated). */
/*    This subroutine can handle nth only up to 6. Additional */
/*      programming is needed for larger values. */

    /* Parameter adjustments */
    --bb;
    --aa;
    --ro;
    --th;

    /* Function Body */
    mpl = *nth + 1;
    ml = mpl + *nth;
    jjmax = ml * ml;
    nobsml = *nobs * ml;
    nobmpl = *nobs * mpl;
    i__1 = *nobs;
    for (i__ = 1; i__ <= i__1; ++i__) {
	obs[i__ - 1] = 1.;
	iz = nobsml + i__;
	obs[iz - 1] = ro[i__];
	if (*nth == 0) {
	    goto L90;
	}
	ic = i__ + *nobs;
	is = i__ + nobmpl;
	sint = sin(th[i__]);
	cost = cos(th[i__]);
	obs[ic - 1] = cost;
	obs[is - 1] = sint;
	if (*nth == 1) {
	    goto L90;
	}
	ic += *nobs;
	is += *nobs;
	sncs = sint * cost;
	cs2 = cost * cost;
	obs[ic - 1] = cs2 + cs2 - 1.;
	obs[is - 1] = sncs + sncs;
	if (*nth == 2) {
	    goto L90;
	}
	ic += *nobs;
	is += *nobs;
	sn3 = sint * sint * sint;
	cs3 = cs2 * cost;
	obs[ic - 1] = cs3 * 4. - cost * 3.;
	obs[is - 1] = sint * 3. - sn3 * 4.;
	if (*nth == 3) {
	    goto L90;
	}
	ic += *nobs;
	is += *nobs;
	cs4 = cs2 * cs2;
	obs[ic - 1] = (cs4 - cs2) * 8. + 1.;
	obs[is - 1] = (cs3 * 2. * sint - sncs) * 4.;
	if (*nth == 4) {
	    goto L90;
	}
	ic += *nobs;
	is += *nobs;
	cs5 = cs3 * cs2;
	obs[ic - 1] = cs5 * 16. - cs3 * 20. + cost * 5.;
	obs[is - 1] = sn3 * 16. * sint * sint - sn3 * 20. + sint * 5.;
	if (*nth == 5) {
	    goto L90;
	}
	ic += *nobs;
	is += *nobs;
	obs[ic - 1] = cs3 * 32. * cs3 - cs4 * 48. + cs2 * 18. - 1.;
	obs[is - 1] = sint * 32. * (cs5 - cs3) + sncs * 6.;
L90:
	;
    }
    i__1 = jjmax;
    for (jj = 1; jj <= i__1; ++jj) {
/* L20: */
	cn[jj - 1] = 0.;
    }
    i__1 = ml;
    for (j = 1; j <= i__1; ++j) {
/* L21: */
	cl[j - 1] = 0.;
    }
    i__1 = *nobs;
    for (nob = 1; nob <= i__1; ++nob) {
	iii = nob + nobsml;
	i__2 = ml;
	for (k = 1; k <= i__2; ++k) {
	    i__3 = ml;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		ii = nob + *nobs * (i__ - 1);
		kk = nob + *nobs * (k - 1);
		j = i__ + (k - 1) * ml;
/* L23: */
		cn[j - 1] += obs[ii - 1] * obs[kk - 1];
	    }
	}
	i__3 = ml;
	for (i__ = 1; i__ <= i__3; ++i__) {
	    ii = nob + *nobs * (i__ - 1);
/* L24: */
	    cl[i__ - 1] += obs[iii - 1] * obs[ii - 1];
	}
    }
    dminv_(cn, &ml, &d__, ll, mm);
    dgmprd_(cn, cl, out, &ml, &ml, &c__1);
    i__3 = mpl;
    for (i__ = 2; i__ <= i__3; ++i__) {
	aa[i__] = out[i__ - 1];
	ipl = i__ + *nth;
	bb[i__] = out[ipl - 1];
/* L51: */
    }
    aa[1] = out[0];
    bb[1] = 0.;
    return 0;
} /* fourls_ */

/* Subroutine */ int gabs_(integer *komp, doublereal *smaxis, doublereal *qq, 
	doublereal *ecc, doublereal *period, doublereal *dd, doublereal *rad, 
	doublereal *xm, doublereal *xmo, doublereal *absgr, doublereal *glog)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double sqrt(doublereal), d_lg10(doublereal *);

    /* Local variables */
    static doublereal gmnomsun, qf, av, gz, acm, dcm, rcm, qfm, gxo, gzo, hyp,
	     gxs, gzs, efac, gxcf, psec, sign, avsq, gbigm, csalf, snalf, 
	    dcmsq, rcmsq, twopi, hypsq, gbigmo, sunrad;

/*  Version of September 17, 2004 */

/*  Input definitions: */
/*   smaxis is the length of the orbital semi-major axis in solar radii. */
/*   qq is the mass ratio in the sense m2/m1. Stars 1 and 2 are as defined */
/*     in the external program (star 1 is near superior conjunction at */
/*     phase zero). */
/*   ecc is orbital eccentricity */
/*   period is orbit period in days */
/*   dd is the instantaneous separation of the star centers in unit of th */
/*     orbital semi-major axis */
/*   rad is the polar radius if the star at issue in unit of the orbital */
/*     semi-major axis */
/*  Output definitions: */
/*   absgr is the polar acceleration due to effective gravity in cm/sec^2 */
/*   glog is log_10 of absgr */

    twopi = 6.28318530718;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE substitution: */

/*     gbig=6.670d-8 */
/*     sunmas=1.989d33 */
/*     sunrad=6.9599d10 */
    gmnomsun = 1.3271244e26f;
    sunrad = 6.957e10;
    psec = *period * 86400.;
    acm = sunrad * *smaxis;
/*     pyears=period/365.2422d0 */
/*     aau=smaxis/214.9426d0 */
/*     tmass=aau**3/pyears**2 */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    qf = 1. / (*qq + 1.);
    qfm = *qq * qf;
    sign = -1.;
    if (*komp == 2) {
	goto L10;
    }
    qfm = qf;
    qf = *qq * qf;
    sign = 1.;
L10:
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE substitution: */

/*     xm=tmass*qfm */
/*     xmo=tmass*qf */
/*     gbigm=gbig*xm*sunmas */
/*     gbigmo=gbig*xmo*sunmas */
/* Computing 3rd power */
    d__1 = acm;
/* Computing 2nd power */
    d__2 = psec;
/* Computing 2nd power */
    d__3 = twopi;
    gbigm = d__1 * (d__1 * d__1) / (d__2 * d__2) * (d__3 * d__3) * qfm;
    *xm = gbigm / gmnomsun;
/* Computing 3rd power */
    d__1 = acm;
/* Computing 2nd power */
    d__2 = psec;
/* Computing 2nd power */
    d__3 = twopi;
    gbigmo = d__1 * (d__1 * d__1) / (d__2 * d__2) * (d__3 * d__3) * qf;
    *xmo = gbigmo / gmnomsun;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    rcm = *rad * acm;
    dcm = *dd * acm;
    dcmsq = dcm * dcm;
    efac = sqrt((*ecc + 1.) * (1. - *ecc));
    av = twopi * efac / (psec * *dd * *dd);
    avsq = av * av;
    rcmsq = rcm * rcm;
    hypsq = rcmsq + dcmsq;
    hyp = sqrt(hypsq);
    snalf = rcm / hyp;
    csalf = dcm / hyp;
    gz = -gbigm / rcmsq;
    gzo = -snalf * gbigmo / hypsq;
    gxo = sign * csalf * gbigmo / hypsq;
    gxcf = -sign * avsq * dcm * qf;
    gxs = gxo + gxcf;
    gzs = gz + gzo;
    *absgr = sqrt(gxs * gxs + gzs * gzs);
    *glog = d_lg10(absgr);
    return 0;
} /* gabs_ */

/* Subroutine */ int jdph_(doublereal *xjdin, doublereal *phin, doublereal *
	t0, doublereal *p0, doublereal *dpdt, doublereal *xjdout, doublereal *
	phout)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3, d__4, d__5;

    /* Builtin functions */
    double log(doublereal), exp(doublereal);

    /* Local variables */
    static doublereal fc, tol, fccb, fcsq, fc4th, fc5th, pddph, abdpdt, 
	    deltop;

/*  Version of February 2, 1999 */

/*  Subroutine jdph computes a phase (phout) based on an input */
/*   JD (xjdin), reference epoch (t0), period (p0), and dP/dt (dpdt). */
/*   It also computes a JD (xjdout) from an input phase (phin) and the */
/*   same ephemeris. So jdph can be used either to get phase from */
/*   JD or JD from phase. */

    tol = 1e-6;
    abdpdt = abs(*dpdt);
    deltop = (*xjdin - *t0) / *p0;
    fcsq = 0.;
    fccb = 0.;
    fc4th = 0.;
    fc5th = 0.;
    fc = deltop * *dpdt;
    if (abs(fc) < 1e-18) {
	goto L25;
    }
    fcsq = fc * fc;
    if (abs(fcsq) < 1e-24) {
	goto L25;
    }
    fccb = fc * fcsq;
    if (abs(fccb) < 1e-27) {
	goto L25;
    }
    fc4th = fc * fccb;
    if (abs(fc4th) < 1e-28) {
	goto L25;
    }
    fc5th = fc * fc4th;
L25:
    *phout = deltop * (1. - fc * .5 + fcsq / 3. - fccb * .25 + fc4th * .2 - 
	    fc5th / 6.);
    pddph = *dpdt * *phin;
/* Computing 2nd power */
    d__1 = pddph;
/* Computing 3rd power */
    d__2 = pddph;
/* Computing 4th power */
    d__3 = pddph, d__3 *= d__3;
/* Computing 5th power */
    d__4 = pddph, d__5 = d__4, d__4 *= d__4;
    *xjdout = *p0 * *phin * (pddph * .5 + 1. + d__1 * d__1 / 6. + d__2 * (
	    d__2 * d__2) / 24. + d__3 * d__3 / 120. + d__5 * (d__4 * d__4) / 
	    720.) + *t0;
    if (abdpdt < tol) {
	return 0;
    }
    *phout = log(deltop * *dpdt + 1.) / *dpdt;
    *xjdout = (exp(*dpdt * *phin) - 1.) * *p0 / *dpdt + *t0;
    return 0;
} /* jdph_ */

/* Subroutine */ int kepler_(doublereal *xm, doublereal *ec, doublereal *ecan,
	 doublereal *tr)
{
    /* Builtin functions */
    double sin(doublereal), cos(doublereal), sqrt(doublereal), tan(doublereal)
	    , atan(doublereal);

    /* Local variables */
    static doublereal xmc, tol, dedm, abdlec, dlecan;

/*  Version of October 6, 1995 */
    tol = 1e-8;
    dlecan = 0.;
    *ecan = *xm;
L18:
    *ecan += dlecan;
    xmc = *ecan - *ec * sin(*ecan);
    dedm = 1. / (1. - *ec * cos(*ecan));
    dlecan = (*xm - xmc) * dedm;
    abdlec = abs(dlecan);
    if (abdlec > tol) {
	goto L18;
    }
    *tr = atan(sqrt((*ec + 1.) / (1. - *ec)) * tan(*ecan * .5)) * 2.;
    if (*tr < 0.f) {
	*tr += 6.2831853071795865;
    }
    return 0;
} /* kepler_ */

/* Subroutine */ int lcr_(doublereal *rv, doublereal *grx, doublereal *gry, 
	doublereal *grz, doublereal *rvq, doublereal *grxq, doublereal *gryq, 
	doublereal *grzq, integer *mmsave, doublereal *fr1, doublereal *fr2, 
	doublereal *hld, doublereal *slump1, doublereal *slump2, doublereal *
	rm, doublereal *poth, doublereal *potc, integer *n1, integer *n2, 
	doublereal *f1, doublereal *f2, doublereal *d__, doublereal *hlum, 
	doublereal *clum, doublereal *xh, doublereal *xc, doublereal *yh, 
	doublereal *yc, doublereal *gr1, doublereal *gr2, doublereal *sm1, 
	doublereal *sm2, doublereal *tpolh, doublereal *tpolc, doublereal *
	sbrh, doublereal *sbrc, integer *ifat1, integer *ifat2, doublereal *
	tavh, doublereal *tavc, doublereal *alb1, doublereal *alb2, 
	doublereal *xbol1, doublereal *xbol2, doublereal *ybol1, doublereal *
	ybol2, doublereal *vol1, doublereal *vol2, doublereal *snth, 
	doublereal *csth, doublereal *snfi, doublereal *csfi, doublereal *tld,
	 doublereal *glump1, doublereal *glump2, doublereal *xx1, doublereal *
	xx2, doublereal *yy1, doublereal *yy2, doublereal *zz1, doublereal *
	zz2, doublereal *dint1, doublereal *dint2, doublereal *grv1, 
	doublereal *grv2, doublereal *csbt1, doublereal *csbt2, doublereal *
	rftemp, doublereal *rf1, doublereal *rf2, doublereal *gmag1, 
	doublereal *gmag2, doublereal *glog1, doublereal *glog2, integer *
	mode, integer *iband, doublereal *tloc1, doublereal *tloc2, 
	doublereal *xinorm1, doublereal *xinorm2)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal xintlog1, xintlog2;
    static integer i__;
    static doublereal g1, g2;
    extern /* Subroutine */ int planckint_(doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal dp, rb;
    static integer lt, nr, nn1;
    static doublereal vl1, vl2, tpc, tph;
    extern /* Subroutine */ int lum_(doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, integer *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *);
    static doublereal sm1d, sm2d, vold;
    extern /* Subroutine */ int atmx_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal sbrt;
    extern /* Subroutine */ int lump_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *);
    static doublereal sbr1b, sbr2b;
    static integer imax1, imax2;
    static doublereal xint1, xint2, potcd, pothd;
    extern /* Subroutine */ int olump_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *);
    static doublereal summ1d, summ2d, radrat, ratbol;
    extern /* Subroutine */ int volume_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *);

/*  Version of January 8, 2003 */
    /* Parameter adjustments */
    --xinorm2;
    --xinorm1;
    --tloc2;
    --tloc1;
    --glog2;
    --glog1;
    --gmag2;
    --gmag1;
    --rf2;
    --rf1;
    --rftemp;
    --csbt2;
    --csbt1;
    --grv2;
    --grv1;
    --zz2;
    --zz1;
    --yy2;
    --yy1;
    --xx2;
    --xx1;
    --glump2;
    --glump1;
    --tld;
    --csfi;
    --snfi;
    --csth;
    --snth;
    --slump2;
    --slump1;
    --hld;
    --fr2;
    --fr1;
    --mmsave;
    --grzq;
    --gryq;
    --grxq;
    --rvq;
    --grz;
    --gry;
    --grx;
    --rv;

    /* Function Body */
    nn1 = *n1;
    vl1 = *vol1;
    vl2 = *vol2;
    dp = 1. - eccen_4.e;
    if (invar_3.irvol1 == 1) {
	goto L88;
    }
    volume_(&vl1, rm, poth, &dp, f1, &nn1, n1, &c__1, &rv[1], &grx[1], &gry[1]
	    , &grz[1], &rvq[1], &grxq[1], &gryq[1], &grzq[1], &mmsave[1], &
	    fr1[1], &fr2[1], &hld[1], &snth[1], &csth[1], &snfi[1], &csfi[1], 
	    &summ_1.summ1, sm1, &grv1[1], &grv2[1], &xx1[1], &yy1[1], &zz1[1],
	     &xx2[1], &yy2[1], &zz2[1], &csbt1[1], &csbt2[1], &glump1[1], &
	    glump2[1], &gmag1[1], &gmag2[1], &glog1[1], &glog2[1], gr1, &c__1,
	     &tloc1[1], &tloc2[1], &xinorm1[1], &xinorm2[1]);
    if (eccen_4.e == 0.) {
	goto L88;
    }
    pothd = dpdx_2.phsv;
    if (eccen_4.ifc == 2) {
	pothd = dpdx_2.phsv + dpdx_2.dpdx1 * (1. / *d__ - 1. / (1. - 
		eccen_4.e));
    }
    volume_(&vl1, rm, &pothd, d__, f1, &nn1, n1, &c__1, &rv[1], &grx[1], &gry[
	    1], &grz[1], &rvq[1], &grxq[1], &gryq[1], &grzq[1], &mmsave[1], &
	    fr1[1], &fr2[1], &hld[1], &snth[1], &csth[1], &snfi[1], &csfi[1], 
	    &summ_1.summ1, sm1, &grv1[1], &grv2[1], &xx1[1], &yy1[1], &zz1[1],
	     &xx2[1], &yy2[1], &zz2[1], &csbt1[1], &csbt2[1], &glump1[1], &
	    glump2[1], &gmag1[1], &gmag2[1], &glog1[1], &glog2[1], gr1, &
	    eccen_4.ifc, &tloc1[1], &tloc2[1], &xinorm1[1], &xinorm2[1]);
L88:
    if (invar_3.irvol2 == 1) {
	goto L86;
    }
    volume_(&vl2, rm, potc, &dp, f2, n2, n1, &c__2, &rv[1], &grx[1], &gry[1], 
	    &grz[1], &rvq[1], &grxq[1], &gryq[1], &grzq[1], &mmsave[1], &fr1[
	    1], &fr2[1], &hld[1], &snth[1], &csth[1], &snfi[1], &csfi[1], &
	    summ_1.summ2, sm2, &grv1[1], &grv2[1], &xx1[1], &yy1[1], &zz1[1], 
	    &xx2[1], &yy2[1], &zz2[1], &csbt1[1], &csbt2[1], &glump1[1], &
	    glump2[1], &gmag1[1], &gmag2[1], &glog1[1], &glog2[1], gr2, &c__1,
	     &tloc1[1], &tloc2[1], &xinorm1[1], &xinorm2[1]);
    if (eccen_4.e == 0.) {
	goto L86;
    }
    potcd = dpdx_2.pcsv;
    if (eccen_4.ifc == 2) {
	potcd = dpdx_2.pcsv + dpdx_2.dpdx2 * (1. / *d__ - 1. / (1. - 
		eccen_4.e));
    }
    volume_(&vl2, rm, &potcd, d__, f2, n2, n1, &c__2, &rv[1], &grx[1], &gry[1]
	    , &grz[1], &rvq[1], &grxq[1], &gryq[1], &grzq[1], &mmsave[1], &
	    fr1[1], &fr2[1], &hld[1], &snth[1], &csth[1], &snfi[1], &csfi[1], 
	    &summ_1.summ2, sm2, &grv1[1], &grv2[1], &xx1[1], &yy1[1], &zz1[1],
	     &xx2[1], &yy2[1], &zz2[1], &csbt1[1], &csbt2[1], &glump1[1], &
	    glump2[1], &gmag1[1], &gmag2[1], &glog1[1], &glog2[1], gr2, &
	    eccen_4.ifc, &tloc1[1], &tloc2[1], &xinorm1[1], &xinorm2[1]);
L86:
    *tpolh = *tavh * sqrt(sqrt(*sm1 / summ_1.summ1));
    *tpolc = *tavc * sqrt(sqrt(*sm2 / summ_1.summ2));
    g1 = gmag1[1];
    g2 = gmag2[1];
    if (*mode == 1) {
	d__1 = g2 / g1;
	*tpolc = *tpolh * sqrt(sqrt(pow_dd(&d__1, gr1)));
    }
    if (*mode == 1) {
	*tavc = *tpolc / sqrt(sqrt(*sm2 / summ_1.summ2));
    }
    tph = *tpolh * 1e4;
    tpc = *tpolc * 1e4;
    atmmessages_1.komp = 1;
    coflimbdark_1.xld = *xh;
    coflimbdark_1.yld = *yh;
    if (*ifat1 == 0) {
	planckint_(&tph, iband, &xintlog1, &xint1);
    }
    if (*ifat1 != 0) {
	atmx_(&tph, &gpoles_1.gplog1, iband, &xintlog1, &xint1);
    }
    lum_(hlum, xh, yh, tpolh, n1, n1, &c__1, sbrh, &rv[1], &rvq[1], &glump1[1]
	    , &glump2[1], &glog1[1], &glog2[1], &grv1[1], &grv2[1], &mmsave[1]
	    , &summ1d, &fr1[1], &sm1d, ifat1, &vold, rm, poth, f1, d__, &snth[
	    1], iband, &tloc1[1], &tloc2[1], &xinorm1[1], &xinorm2[1]);
    atmmessages_1.komp = 2;
    coflimbdark_1.xld = *xc;
    coflimbdark_1.yld = *yc;
    if (*ifat2 == 0) {
	planckint_(&tpc, iband, &xintlog2, &xint2);
    }
    if (*ifat2 != 0) {
	atmx_(&tpc, &gpoles_1.gplog2, iband, &xintlog2, &xint2);
    }
    *sbrc = *sbrh * xint2 / xint1;
    lum_(clum, xc, yc, tpolc, n2, n1, &c__2, &sbrt, &rv[1], &rvq[1], &glump1[
	    1], &glump2[1], &glog1[1], &glog2[1], &grv1[1], &grv2[1], &mmsave[
	    1], &summ2d, &fr2[1], &sm2d, ifat2, &vold, rm, potc, f2, d__, &
	    snth[1], iband, &tloc1[1], &tloc2[1], &xinorm1[1], &xinorm2[1]);
    if (invar_3.ipb == 1) {
	*sbrc = sbrt;
    }
    if (*mode > 0) {
	*clum = *clum * *sbrc / sbrt;
    }
    if (*mode <= 0) {
	*sbrc = sbrt;
    }
    if (invar_3.mref == 2) {
	goto L30;
    }
    d__1 = *vol1 / *vol2;
    radrat = pow_dd(&d__1, &c_b886);
/* Computing 2nd power */
    d__1 = radrat;
/* Computing 4th power */
    d__2 = *tavh / *tavc, d__2 *= d__2;
    ratbol = d__1 * d__1 * (d__2 * d__2);
    rb = 1. / ratbol;
    coflimbdark_1.xld = *xh;
    coflimbdark_1.yld = *yh;
    olump_(&rv[1], &grx[1], &gry[1], &grz[1], &rvq[1], &grxq[1], &gryq[1], &
	    grzq[1], &slump1[1], &slump2[1], &mmsave[1], gr1, alb1, &rb, 
	    tpolh, sbrh, &summ_1.summ1, n1, n2, &c__1, ifat1, xc, yc, d__, &
	    snth[1], &csth[1], &snfi[1], &csfi[1], &tld[1], &glump1[1], &
	    glump2[1], &glog1[1], &glog2[1], &grv1[1], &grv2[1], iband);
    rb = ratbol;
    coflimbdark_1.xld = *xc;
    coflimbdark_1.yld = *yc;
    olump_(&rv[1], &grx[1], &gry[1], &grz[1], &rvq[1], &grxq[1], &gryq[1], &
	    grzq[1], &slump1[1], &slump2[1], &mmsave[1], gr2, alb2, &rb, 
	    tpolc, sbrc, &summ_1.summ2, n1, n2, &c__2, ifat2, xh, yh, d__, &
	    snth[1], &csth[1], &snfi[1], &csfi[1], &tld[1], &glump1[1], &
	    glump2[1], &glog1[1], &glog2[1], &grv1[1], &grv2[1], iband);
    return 0;
L30:
/* Computing 4th power */
    d__1 = *tpolh, d__1 *= d__1;
    sbr1b = d__1 * d__1 / *dint1;
/* Computing 4th power */
    d__1 = *tpolc, d__1 *= d__1;
    sbr2b = d__1 * d__1 / *dint2;
    lt = *n1 + 1;
    imax1 = mmsave[lt];
    i__1 = imax1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	rftemp[i__] = 1.;
/* L80: */
	rf1[i__] = 1.;
    }
    lt = *n1 + *n2 + 2;
    imax2 = mmsave[lt];
    i__1 = imax2;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L81: */
	rf2[i__] = 1.;
    }
    i__1 = invar_3.nref;
    for (nr = 1; nr <= i__1; ++nr) {
	coflimbdark_1.xld = *xh;
	coflimbdark_1.yld = *yh;
	lump_(&grx[1], &gry[1], &grz[1], &grxq[1], &gryq[1], &grzq[1], &
		slump1[1], &slump2[1], &mmsave[1], alb1, tpolh, sbrh, n1, n2, 
		&c__1, ifat1, &fr1[1], &snth[1], &tld[1], &glump1[1], &glump2[
		1], &xx1[1], &xx2[1], &yy1[1], &yy2[1], &zz1[1], &zz2[1], 
		xbol2, ybol2, &grv1[1], &grv2[1], &sbr1b, &sbr2b, &rftemp[1], 
		&rf2[1], &gmag1[1], &gmag2[1], &glog1[1], &glog2[1], dint1, 
		iband);
	coflimbdark_1.xld = *xc;
	coflimbdark_1.yld = *yc;
	lump_(&grx[1], &gry[1], &grz[1], &grxq[1], &gryq[1], &grzq[1], &
		slump1[1], &slump2[1], &mmsave[1], alb2, tpolc, sbrc, n1, n2, 
		&c__2, ifat2, &fr2[1], &snth[1], &tld[1], &glump1[1], &glump2[
		1], &xx1[1], &xx2[1], &yy1[1], &yy2[1], &zz1[1], &zz2[1], 
		xbol1, ybol1, &grv1[1], &grv2[1], &sbr1b, &sbr2b, &rf2[1], &
		rf1[1], &gmag1[1], &gmag2[1], &glog1[1], &glog2[1], dint2, 
		iband);
	i__2 = imax1;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* L70: */
	    rf1[i__] = rftemp[i__];
	}
/* L93: */
    }
    return 0;
} /* lcr_ */

/* Subroutine */ int lc_(char *plf, doublereal *pltab, char *atmf, doublereal 
	*atmtab, char *lcin, integer *request, integer *vertno, integer *
	l3perc, doublereal *indeps, doublereal *deps, doublereal *skycoy, 
	doublereal *skycoz, doublereal *params, doublereal *args, char *lcout,
	 integer *mswitch, doublereal *mesh1, doublereal *mesh2, integer *
	hswitch, doublereal *hrho, doublereal *htheta, doublereal *hac, 
	doublereal *has, ftnlen plf_len, ftnlen atmf_len, ftnlen lcin_len, 
	ftnlen lcout_len)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    double acos(doublereal);
    integer s_cmp(char *, char *, ftnlen, ftnlen), f_open(olist *), s_rsle(
	    cilist *), do_lio(integer *, integer *, char *, ftnlen), e_rsle(
	    void), f_clos(cllist *);
    double log(doublereal), sin(doublereal), cos(doublereal), pow_dd(
	    doublereal *, doublereal *), pow_di(doublereal *, integer *), 
	    sqrt(doublereal);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal d__, f;
    static integer i__;
    static doublereal f1, f2;
    static integer n1, n2;
    static doublereal aa[20], bb[20];
    static integer nc, ii;
    static doublereal pi, xc;
    static integer nn, it;
    static doublereal po[2], rm, xh, yh, ot, yc, wl;
    static integer kp;
    static doublereal rv[33202], en0, el3, fr1[33202], fr2[33202], rf1[33202],
	     rf2[33202], op1[100], wl1[100000], wl2[100000], gr1, gr2;
    static integer np1, np2, nn1;
    static doublereal vl1, vl2, sm1, sm2, xx1[33202], xx2[33202], yy1[33202], 
	    yy2[33202], zz1[33202], zz2[33202], rr1, rr2, sr1, sr2;
    static integer ns1, iab, ns2;
    extern /* Subroutine */ int bbl_(doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal dif;
    static integer ll1;
    static doublereal fcl[100], dap, hld[33202], all;
    static integer ll2;
    static doublereal gau, rcl[100], the, tld[66404];
    static integer iln;
    static doublereal phn, xcl[100], ycl[100], zcl[100], rho[800];
    static integer imm, mod;
    static doublereal smd, hot, grx[33202], gry[33202], grz[33202];
    static integer idx;
    static doublereal htt;
    static integer imp;
    static doublereal tot, rvq[33202], alb1, alb2, dif1, dif2, emm1[100], 
	    emm2[100], p1ap, p2ap;
    static integer lll1, lll2;
    static doublereal tau1[100], tau2[100], tav1, grv1[33202], grv2[33202], 
	    wll1[100], wll2[100], tav2, sms1, sms2, xlg1, xlg2;
    static integer npp2, ibef;
    static doublereal hjdi, seed, encl[100], flam, csfi[66504], emmg[100000], 
	    dens[100], snfi[66504], taug[100000], csth[400], xlat[200]	/* 
	    was [2][100] */, snth[400], xmue[100], grxq[33202], gryq[33202], 
	    grzq[33202], dpdt, phin, yskp[132908], zskp[132908];
    static integer mode;
    static doublereal tavh, tavc, gmag1[33202], gmag2[33202], poth, fbin1[
	    100000], fbin2[100000], potc, hlum, clum;
    static integer ifat1, ifat2;
    static doublereal zero, glog1[33202], glog2[33202], ewid1[100], csbt1[
	    33202], csbt2[33202], ewid2[100], delv1[100000], tloc1[33202], 
	    tloc2[33202], delv2[100000], resf1[100000], resf2[100000], dvks1[
	    100], dvks2[100], xbol1, xbol2, ybol1, ybol2, dint1, dint2, sbrh, 
	    sbrc, cool;
    extern /* Subroutine */ int mlrg_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static integer iband;
    static doublereal bolm1, bolm2;
    static integer llll1, llll2;
    static doublereal step;
    extern /* Subroutine */ int jdph_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal hjdo, phas, ranf, drdq, hjdin, colam, edens[100], smagg,
	     dodq, phasi, theta[800];
    static integer noise;
    static doublereal hjdst, hjdsp, xincl, tpolc, stdev, xlong[200]	/* 
	    was [2][100] */, summd, tpolh, phaso, total, start, stopp;
    static integer nstot;
    static doublereal hbarw1[100], depth1[100], depth2[100], hbarw2[100], 
	    delwl1[100000], delwl2[100000], binwm1, binwm2, glump1[33202], 
	    glump2[33202], count1[100000], count2[100000], slump1[33202], 
	    slump2[33202];
    extern /* Subroutine */ int rddata_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, integer 
	    *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *);
    static doublereal abunin, factor, abunir;
    static integer mmsave[404];
    static doublereal rftemp[33202];
    extern /* Subroutine */ int binnum_(doublereal *, integer *, doublereal *,
	     integer *);
    static doublereal rsuncm;
    extern /* Subroutine */ int sincos_(integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    , modlog_(doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), volume_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *), wrhead_(integer *, integer *, integer *, integer *
	    , integer *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, integer 
	    *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , doublereal *, doublereal *, doublereal *, doublereal *, integer 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *);
    static integer igsidx;
    static doublereal phstop, totall;
    extern /* Subroutine */ int rangau_(doublereal *, integer *, doublereal *,
	     doublereal *), wrdata_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, integer 
	    *, integer *, integer *);
    static doublereal phstrt;
    extern /* Subroutine */ int wrfoot_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *);
    static doublereal xinorm1[33202], xinorm2[33202];

    /* Fortran I/O blocks */
    static cilist io___1048 = { 0, 22, 0, 0, 0 };
    static cilist io___1049 = { 0, 23, 0, 0, 0 };



/*  Main program for computing light and radial velocity curves, */
/*      line profiles, and images */

/*  Version of March 8, 2007 */

/*     TO PRINT VELOCITIES IN KM/SEC, SET VUNIT=1. */
/*     TO PRINT NORMALIZED VELOCITIES IN SAME COLUMNS, SET VUNIT EQUAL TO */
/*     DESIRED VELOCITY UNIT IN KM/SEC. */

/*     PARAMETER PSHIFT IS DEFINED AS THE PHASE AT WHICH PRIMARY */
/*     CONJUNCTION (STAR 1 AWAY FROM OBSERVER) WOULD OCCUR IF THE */
/*     ARGUMENT OF PERIASTRON WERE 2 pi radians. SINCE THE NOMINAL VALUE */
/*     OF THIS QUANTITY IS ZERO, PSHIFT MAY BE USED TO INTRODUCE AN */
/*     ARBITRARY PHASE SHIFT. */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*                      ARRAY DIMENSIONING WRAPPER */
/*                             May 8, 2008 */

/*     The following parameters determine array sizing in the program. */
/*     There is no need to change any numbers in the code except these */
/*     in order to accomodate finer grids. */

/*        Nmax    ..    maximum grid fineness (parameters N1, N2) */
/*                        default:   Nmax =     60 */
/*      igsmax    ..    maximum grid size depending on the grid fineness, */
/*                        i.e. igsmax=762 for N=30, 3011 for N=60 etc. */
/*                        default: igsmax =   3011 */
/*      lpimax    ..    maximum dimension of line profile input arrays */
/*                        default: lpimax =    100 */
/*      lpomax    ..    maximum dimension of line profile output arrays */
/*                        default: lpomax = 100000 */
/*      ispmax    ..    maximum number of spots */
/*                        default: ispmax =    100 */
/*      iclmax    ..    maximum number of clouds */
/*                        default: iclmax =    100 */
/*      iplmax    ..    number of defined passbands */
/*                        default: iplmax =     25 */


/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     Model atmosphere grid properties: */

/*       itemppts  ..   number of temperature coefficients per spectrum */
/*                        default: itemppts=48 (4x12) */
/*       iloggpts  ..   number of log(g) nodes */
/*                        default: iloggpts=11 (atmosphere grid) */
/*       imetpts   ..   number of metallicity nodes */
/*                        default: imetpts=19  (atmosphere grid) */
/*       iatmpts   ..   size of the atmosphere grid per passband per */
/*                      metallicity */
/*                        default: iatmpts = 11*48 = 528 */
/*                        11 log(g) values and */
/*                        48=4x12 temperature coefficients */
/*       iatmchunk ..   size of the atmosphere grid per metallicity */
/*                        default: iatmchunk = 528*25 = 13200 */
/*       iatmsize  ..   size of the atmosphere grid */
/*                        default: iatmsize = 13200*19 = 250800 */


/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     Locations of the auxiliary files atmcof.dat and atmcofplanck.dat: */


/*     parameter (atmf='atmcof.dat') */
/*     parameter (plf='atmcofplanck.dat') */

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     Other array dimensions that are set automatically are listed */
/*     below and should not be changed, as the above parameter statements */
/*     determine their values. */

/*        MMmax    ..    dimension of the array MMSAVE */
/*        immax    ..    maximum number of surface grid points in sky */
/*                       images */
/*       ifrmax    ..    dimension of the Fourier arrays */
/*       iplcof    ..    dimension of the atmcofplanck matrix, 50 per */
/*                       passband */


/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     Finally, the following dimensions are considered static and */
/*     their size does not depend on parameters. */


/*     Nothing needs to be changed beyond this point to accomodate */
/*     finer grids. */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extensions: */

/*         atmf   ..   model atmosphere filename */
/*          plf   ..   blackbody atmosphere filename */
/*       atmtab   ..   Kurucz atmosphere table */
/*        pltab   ..   Planck atmosphere table */
/*         lcin   ..   input lci filename */
/*      request   ..   what do we want to compute: */
/*                       1  ..  light curve */
/*                       2  ..  primary RV curve */
/*                       3  ..  secondary RV curve */
/*                       4  ..  star shape */
/*       vertno   ..   number of vertices in a light/RV curve */
/*       L3perc   ..   3rd light switch: */
/*                       0  ..  3rd light passed in flux units (default) */
/*                       1  ..  3rd light computed from the passed */
/*                              percentage of L3, x=L3/(L1+L2+L3) */
/*       indeps   ..   an array of vertices (HJDs or phases) */
/*         deps   ..   an array of computed values (fluxes or RVs) */
/*       skycoy   ..   an array of y-coordinates of the plane of sky */
/*       skycoz   ..   an array of z-coordinates of the plane of sky */
/*       params   ..   an array of computed parameters: */

/*                     params( 1) = L1     star 1 passband luminosity */
/*                     params( 2) = L2     star 2 passband luminosity */
/*                     params( 3) = M1     star 1 mass in solar masses */
/*                     params( 4) = M2     star 2 mass in solar masses */
/*                     params( 5) = R1     star 1 radius in solar radii */
/*                     params( 6) = R2     star 2 radius in solar radii */
/*                     params( 7) = Mbol1  star 1 absolute magnitude */
/*                     params( 8) = Mbol2  star 2 absolute magnitude */
/*                     params( 9) = logg1  star 1 log gravity */
/*                     params(10) = logg2  star 2 log gravity */
/*                     params(11) = SBR1   star 1 polar surface brightness */
/*                     params(12) = SBR2   star 2 polar surface brightness */
/*                     params(13) = phsv   star 1 potential */
/*                     params(14) = pcsv   star 2 potential */
/*                     params(15) = vol1   star 1 volume */
/*                     params(16) = vol2   star 2 volume */
/*                     params(17) = ifr    length of horizon arrays */

/*         args   ..   an array of passed parameters (arguments): */

/*                     args( 1) = phase shift */
/*                     args( 2) = inclination */
/*                     args( 3) = bolometric LD coefficient x1 */
/*                     args( 4) = bolometric LD coefficient y1 */
/*                     args( 5) = bolometric LD coefficient x2 */
/*                     args( 6) = bolometric LD coefficient y2 */
/*                     args( 7) = gamma velocity */
/*                     args( 8) = third light */
/*                     args( 9) = surface potential 1 */
/*                     args(10) = surface potential 2 */
/*                     args(11) = effective temperature 1 */
/*                     args(12) = effective temperature 2 */
/*                     args(13) = eccentricity */
/*                     args(14) = argument of periastron */
/*                     args(15) = mass ratio */
/*                     args(16) = semi-major axis */
/*                     args(17) = orbital period */
/*                     args(18) = passband luminosity */

/*                     Incorporating args was necessary to circumvent */
/*                     rounding problems in WD when using I/O. */
/*      mswitch   ..   should the meshes be exported to phoebe? */
/*        mesh1   ..   a matrix of primary star mesh values, useful for debugging */
/*        mesh2   ..   a matrix of secondary star mesh values, useful for debugging */
/*         hrho   ..   horizon rho, useful for debugging */
/*       htheta   ..   horizon theta, useful for debugging */
/*          hAc   ..   Fourier cosine coefficients, useful for debugging */
/*          hAs   ..   Fourier sine coefficients, useful for debugging */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*           Bandpass Label Assignments for Stellar Atmospheres */

/*    Label   Bandpass   Reference for Response Function */
/*    -----   --------   ------------------------------- */
/*       1        u      Crawford, D.L. and Barnes, J.V. 1974, AJ, 75, 978 */
/*       2        v          "                "           " */
/*       3        b          "                "           " */
/*       4        y          "                "           " */
/*       5        U      Buser, R. 1978, Ang, 62, 411 */
/*       6        B      Azusienis and Straizys 1969, Sov. Astron., 13, 316 */
/*       7        V          "             "                " */
/*       8        R      Johnson, H.L. 1965, ApJ, 141, 923 */
/*       9        I         "            "    " */
/*      10        J         "            "    " */
/*      11        K         "            "    " */
/*      12        L         "            "    " */
/*      13        M         "            "    " */
/*      14        N         "            "    " */
/*      15        R_c    Bessell, M.S. 1983, PASP, 95, 480 */
/*      16        I_c       "            "    " */
/*      17      230      Kallrath, J., Milone, E.F., Terrell, D., Young, A.T. */
/*                          1998, ApJ, 508, 308 */
/*      18      250         "             "             "           " */
/*      19      270         "             "             "           " */
/*      20      290         "             "             "           " */
/*      21      310         "             "             "           " */
/*      22      330         "             "             "           " */
/*      23     'TyB'    Tycho catalog B */
/*      24     'TyV'    Tycho catalog V */
/*      25     'HIP'    Hipparcos catalog */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*      PHOEBE extensions: */

/*      26   CoRoT-exo  Carla Maceroni, private communication */
/*      27   CoRoT-sis  Carla Maceroni, private communication */
/*      28       H      Johnson, H.L. 1965, ApJ, 141, 923 */
/*      29   Geneva U   Golay, M. 1962, Pub. Obs. Geneve No. 15 (serie A), 29 */
/*      30   Geneva B       "             "             "           " */
/*      31   Geneva B1      "             "             "           " */
/*      32   Geneva B2      "             "             "           " */
/*      33   Geneva V       "             "             "           " */
/*      34   Geneva V1      "             "             "           " */
/*      35   Geneva G       "             "             "           " */
/*      36   Kepler     Kepler Science Book */
/*      37   SDSS u     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      38   SDSS g     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      39   SDSS r     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      40   SDSS i     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      41   SDSS z     Sloan DSS instrument book, Fukugita et al. (1996) */
/*      42   LSST u     LSST science book */
/*      43   LSST g     LSST science book */
/*      44   LSST r     LSST science book */
/*      45   LSST i     LSST science book */
/*      46   LSST z     LSST science book */
/*      47   LSST y3    LSST science book */
/*      48   LSST y4    LSST science book */
/*      49   Walraven w Lub, J. & Pel, J. W. A&A 54, 137 (1963) */
/*      50   Walraven u     "             "             " */
/*      51   Walraven l     "             "             " */
/*      52   Walraven b     "             "             " */
/*      53   Walraven v     "             "             " */
/*      54   MOST       Walker et al. 2003 PASP  115, 1023 */
/*      55   SWASP 2004 Gomez Maqueo Chew, priv.comm. */
/*      56   SWASP 2006 Gomez Maqueo Chew, priv.comm. */
/*      57   BRITE blue Weiss et al. (2014), PASP 126, 573 */
/*      58   BRITE red  Weiss et al. (2014), PASP 126, 573 */
    /* Parameter adjustments */
    --has;
    --hac;
    --htheta;
    --hrho;
    --mesh2;
    --mesh1;
    --args;
    --params;
    --skycoz;
    --skycoy;
    --deps;
    --indeps;
    --atmtab;
    --pltab;

    /* Function Body */
    for (i__ = 1; i__ <= 800; ++i__) {
	theta[i__ - 1] = 0.;
	rho[i__ - 1] = 0.;
/* L15067: */
    }
    ot = .33333333333333331;
    pi = acos(-1.);
    prof2_3.clight = 299792.458;
    en0 = 6.0221409e23;
    rsuncm = 6.957e10;
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*  Ramp ranges are set below. The following values seem to work. */
/*  They may be changed. */
    ramprange_1.tlowtol = 1500.;
    ramprange_1.thightol = 5e4;
    ramprange_1.glowtol = 4.;
    ramprange_1.ghightol = 4.;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    abung_1.abun[0] = 1.;
    abung_1.abun[1] = .5;
    abung_1.abun[2] = .3;
    abung_1.abun[3] = .2;
    abung_1.abun[4] = .1;
    abung_1.abun[5] = 0.;
    abung_1.abun[6] = -.1;
    abung_1.abun[7] = -.2;
    abung_1.abun[8] = -.3;
    abung_1.abun[9] = -.5;
    abung_1.abun[10] = -1.;
    abung_1.abun[11] = -1.5;
    abung_1.abun[12] = -2.;
    abung_1.abun[13] = -2.5;
    abung_1.abun[14] = -3.;
    abung_1.abun[15] = -3.5;
    abung_1.abun[16] = -4.;
    abung_1.abun[17] = -4.5;
    abung_1.abun[18] = -5.;
    abung_1.glog[0] = 0.;
    abung_1.glog[1] = .5;
    abung_1.glog[2] = 1.;
    abung_1.glog[3] = 1.5;
    abung_1.glog[4] = 2.;
    abung_1.glog[5] = 2.5;
    abung_1.glog[6] = 3.;
    abung_1.glog[7] = 3.5;
    abung_1.glog[8] = 4.;
    abung_1.glog[9] = 4.5;
    abung_1.glog[10] = 5.;
    nn = 100;
    gau = 0.;
    if (s_cmp(atmf, "", atmf_len, (ftnlen)0) == 0) {
	for (i__ = 1; i__ <= 581856; ++i__) {
	    arrayleg_1.grand[i__ - 1] = atmtab[i__];
	}
    } else {
	o__1.oerr = 0;
	o__1.ounit = 22;
	o__1.ofnmlen = atmf_len;
	o__1.ofnm = atmf;
	o__1.orl = 0;
	o__1.osta = "old";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
	s_rsle(&io___1048);
	do_lio(&c__5, &c_b900, (char *)&arrayleg_1.grand[0], (ftnlen)sizeof(
		doublereal));
	e_rsle();
	cl__1.cerr = 0;
	cl__1.cunit = 22;
	cl__1.csta = 0;
	f_clos(&cl__1);
    }
    if (s_cmp(plf, "", plf_len, (ftnlen)0) == 0) {
	for (i__ = 1; i__ <= 2900; ++i__) {
	    planckleg_2.plcof[i__ - 1] = pltab[i__];
	}
    } else {
	o__1.oerr = 0;
	o__1.ounit = 23;
	o__1.ofnmlen = plf_len;
	o__1.ofnm = plf;
	o__1.orl = 0;
	o__1.osta = "old";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
	s_rsle(&io___1049);
	do_lio(&c__5, &c__2900, (char *)&planckleg_2.plcof[0], (ftnlen)sizeof(
		doublereal));
	e_rsle();
	cl__1.cerr = 0;
	cl__1.cunit = 23;
	cl__1.csta = 0;
	f_clos(&cl__1);
    }
    o__1.oerr = 0;
    o__1.ounit = 15;
    o__1.ofnmlen = lcin_len;
    o__1.ofnm = lcin;
    o__1.orl = 0;
    o__1.osta = "old";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    if (s_cmp(lcout, "", lcout_len, (ftnlen)0) != 0) {
	o__1.oerr = 0;
	o__1.ounit = 16;
	o__1.ofnmlen = lcout_len;
	o__1.ofnm = lcout;
	o__1.orl = 0;
	o__1.osta = 0;
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
    }
    ibef = 0;
    ipro_1.nf1 = 1;
    ipro_1.nf2 = 1;
    for (it = 1; it <= 1000; ++it) {
	invar_2.kh = 17;
	rddata_(&inprof_1.mpage, &invar_2.nref, &invar_2.mref, &
		invar_2.ifsmv1, &invar_2.ifsmv2, &invar_2.icor1, &
		invar_2.icor2, &invar_2.ld, &invar_2.jdphs, &ardot_1.hjd0, &
		eccen_1.period, &dpdt, &flvar_1.pshift, &stdev, &noise, &seed,
		 &hjdst, &hjdsp, &hjdin, &phstrt, &phstop, &phin, &phn, &mode,
		 &invar_2.ipb, &ifat1, &ifat2, &n1, &n2, &flvar_1.perr0, &
		ardot_1.dperdt, &the, &flvar_1.vunit, &eccen_1.e, &eccen_1.a, 
		&f1, &f2, &eccen_1.vga, &xincl, &gr1, &gr2, &abunin, &tavh, &
		tavc, &alb1, &alb2, &poth, &potc, &rm, &xbol1, &xbol2, &ybol1,
		 &ybol2, &iband, &hlum, &clum, &xh, &xc, &yh, &yc, &el3, &
		cld_1.opsf, &zero, &factor, &wl, &binwm1, &prof2_3.sc1, &
		prof2_3.sl1, wll1, ewid1, depth1, spots_2.kks, &binwm2, &
		prof2_3.sc2, &prof2_3.sl2, wll2, ewid2, depth2, xlat, xlong, 
		spots_2.radsp, spots_2.temsp, xcl, ycl, zcl, rcl, op1, fcl, 
		edens, xmue, encl, &c__100, &c__100, &c__100);
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*     Override the read-in values with passed values: */
	flvar_1.pshift = args[1];
	xincl = args[2];
	xbol1 = args[3];
	ybol1 = args[4];
	xbol2 = args[5];
	ybol2 = args[6];
	eccen_1.vga = args[7];
	el3 = args[8];
	poth = args[9];
	potc = args[10];
	tavh = args[11];
	tavc = args[12];
	eccen_1.e = args[13];
	flvar_1.perr0 = args[14];
	rm = args[15];
	eccen_1.a = args[16];
	eccen_1.period = args[17];
	hlum = args[18];
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	if (inprof_1.mpage != 9) {
	    goto L414;
	}
	cl__1.cerr = 0;
	cl__1.cunit = 15;
	cl__1.csta = 0;
	f_clos(&cl__1);
	if (s_cmp(lcout, "", lcout_len, (ftnlen)0) != 0) {
	    cl__1.cerr = 0;
	    cl__1.cunit = 16;
	    cl__1.csta = 0;
	    f_clos(&cl__1);
	}
	return 0;
L414:
	atmmessages_1.message[0] = 0;
	atmmessages_1.message[2] = 0;
	atmmessages_1.message[1] = 0;
	atmmessages_1.message[3] = 0;
	atmmessages_1.message[4] = 0;
	atmmessages_1.message[6] = 0;
	atmmessages_1.message[5] = 0;
	atmmessages_1.message[7] = 0;
/* *************************************************************** */
/*  The following lines take care of abundances that may not be among */
/*  the 19 Kurucz values (see abun array). abunin is reset at the allowed value nearest */
/*  the input value. */
	binnum_(abung_1.abun, &c__19, &abunin, &iab);
	dif1 = abunin - abung_1.abun[iab - 1];
	if (iab == 19) {
	    goto L702;
	}
	dif2 = abung_1.abun[iab] - abung_1.abun[iab - 1];
	dif = dif1 / dif2;
	if (dif >= 0. && dif <= .5) {
	    goto L702;
	}
	++iab;
L702:
	abunir = abunin;
	abunin = abung_1.abun[iab - 1];
	arrayleg_1.istart = (iab - 1) * 30624 + 1;
/* *************************************************************** */
	if (inprof_1.mpage != 3) {
	    goto L897;
	}
	colam = prof2_3.clight / wl;
	prof2_3.binw1 = colam * binwm1;
	for (iln = 1; iln <= 100; ++iln) {
	    if (wll1[iln - 1] < 0.) {
		goto L89;
	    }
	    emm1[iln - 1] = 0.;
	    if (depth1[iln - 1] < 0.) {
		emm1[iln - 1] = depth1[iln - 1];
	    }
	    tau1[iln - 1] = 0.;
	    if (depth1[iln - 1] > 0.) {
		tau1[iln - 1] = -log(1. - depth1[iln - 1]);
	    }
	    hbarw1[iln - 1] = 0.;
	    if (depth1[iln - 1] != 0.) {
		hbarw1[iln - 1] = prof2_3.clight * .5 * ewid1[iln - 1] / (
			wll1[iln - 1] * (d__1 = depth1[iln - 1], abs(d__1)));
	    }
	    inprof_1.nl1 = iln;
/* L86: */
	}
L89:
	prof2_3.binw2 = colam * binwm2;
	for (iln = 1; iln <= 100; ++iln) {
	    if (wll2[iln - 1] < 0.) {
		goto L91;
	    }
	    emm2[iln - 1] = 0.;
	    if (depth2[iln - 1] < 0.) {
		emm2[iln - 1] = depth2[iln - 1];
	    }
	    tau2[iln - 1] = 0.;
	    if (depth2[iln - 1] > 0.) {
		tau2[iln - 1] = -log(1. - depth2[iln - 1]);
	    }
	    hbarw2[iln - 1] = 0.;
	    if (depth2[iln - 1] != 0.) {
		hbarw2[iln - 1] = prof2_3.clight * .5 * ewid2[iln - 1] / (
			wll2[iln - 1] * (d__1 = depth2[iln - 1], abs(d__1)));
	    }
	    inprof_1.nl2 = iln;
/* L99: */
	}
L91:
	i__1 = inprof_1.nl1;
	for (iln = 1; iln <= i__1; ++iln) {
/* Computing 2nd power */
	    d__1 = wll1[iln - 1] / wl;
	    flam = d__1 * d__1;
/* L622: */
	    dvks1[iln - 1] = prof2_3.clight * (flam - 1.) / (flam + 1.);
	}
	i__1 = inprof_1.nl2;
	for (iln = 1; iln <= i__1; ++iln) {
/* Computing 2nd power */
	    d__1 = wll2[iln - 1] / wl;
	    flam = d__1 * d__1;
/* L623: */
	    dvks2[iln - 1] = prof2_3.clight * (flam - 1.) / (flam + 1.);
	}
L897:
	nspt_1.nsp1 = 0;
	nspt_1.nsp2 = 0;
	for (kp = 1; kp <= 2; ++kp) {
	    for (i__ = 1; i__ <= 100; ++i__) {
		spots_2.xlng[kp + (i__ << 1) - 3] = xlong[kp + (i__ << 1) - 3]
			;
		if (xlat[kp + (i__ << 1) - 3] >= 200.) {
		    goto L88;
		}
		spots_2.sinlat[kp + (i__ << 1) - 3] = sin(xlat[kp + (i__ << 1)
			 - 3]);
		spots_2.coslat[kp + (i__ << 1) - 3] = cos(xlat[kp + (i__ << 1)
			 - 3]);
		spots_2.sinlng[kp + (i__ << 1) - 3] = sin(xlong[kp + (i__ << 
			1) - 3]);
		spots_2.coslng[kp + (i__ << 1) - 3] = cos(xlong[kp + (i__ << 
			1) - 3]);
		if (kp == 1) {
		    ++nspt_1.nsp1;
		}
/* L87: */
		if (kp == 2) {
		    ++nspt_1.nsp2;
		}
	    }
L88:
	    ;
	}
	invar_2.ncl = 0;
	for (i__ = 1; i__ <= 100; ++i__) {
	    if (xcl[i__ - 1] > 100.) {
		goto L66;
	    }
	    ++invar_2.ncl;
	    dens[i__ - 1] = edens[i__ - 1] * xmue[i__ - 1] / en0;
/* L62: */
	}
L66:
	dint1 = pi * (1. - xbol1 / 3.);
	dint2 = pi * (1. - xbol2 / 3.);
	if (invar_2.ld == 2) {
	    dint1 += pi * 2. * ybol1 / 9.;
	}
	if (invar_2.ld == 2) {
	    dint2 += pi * 2. * ybol2 / 9.;
	}
	if (invar_2.ld == 3) {
	    dint1 -= pi * .2 * ybol1;
	}
	if (invar_2.ld == 3) {
	    dint2 -= pi * .2 * ybol2;
	}
	nstot = nspt_1.nsp1 + nspt_1.nsp2;
	np1 = n1 + 1;
	np2 = n1 + n2 + 2;
	invar_2.irte = 0;
	invar_2.irvol1 = 0;
	invar_2.irvol2 = 0;
	for (imm = 1; imm <= 404; ++imm) {
/* L421: */
	    mmsave[imm - 1] = 0;
	}
	nn1 = n1;
	sincos_(&c__1, &nn1, &n1, snth, csth, snfi, csfi, mmsave);
	sincos_(&c__2, &n2, &n1, snth, csth, snfi, csfi, mmsave);
	ardot_1.hjd = ardot_1.hjd0;
	modlog_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, mmsave, fr1, fr2, 
		hld, &rm, &poth, &potc, &gr1, &gr2, &alb1, &alb2, &n1, &n2, &
		f1, &f2, &mod, &xincl, &the, &mode, snth, csth, snfi, csfi, 
		grv1, grv2, xx1, yy1, zz1, xx2, yy2, zz2, glump1, glump2, 
		csbt1, csbt2, gmag1, gmag2, glog1, glog2, tloc1, tloc2, 
		xinorm1, xinorm2);
	volume_(&eccen_1.vol1, &rm, &poth, &flvar_1.dp, &f1, &nn1, &n1, &c__1,
		 rv, grx, gry, grz, rvq, grxq, gryq, grzq, mmsave, fr1, fr2, 
		hld, snth, csth, snfi, csfi, &summd, &smd, grv1, grv2, xx1, 
		yy1, zz1, xx2, yy2, zz2, csbt1, csbt2, glump1, glump2, gmag1, 
		gmag2, glog1, glog2, &gr1, &c__1, tloc1, tloc2, xinorm1, 
		xinorm2);
	volume_(&eccen_1.vol2, &rm, &potc, &flvar_1.dp, &f2, &n2, &n1, &c__2, 
		rv, grx, gry, grz, rvq, grxq, gryq, grzq, mmsave, fr1, fr2, 
		hld, snth, csth, snfi, csfi, &summd, &smd, grv1, grv2, xx1, 
		yy1, zz1, xx2, yy2, zz2, csbt1, csbt2, glump1, glump2, gmag1, 
		gmag2, glog1, glog2, &gr2, &c__1, tloc1, tloc2, xinorm1, 
		xinorm2);
	if (eccen_1.e == 0.) {
	    goto L117;
	}
	dap = eccen_1.e + 1.;
	p1ap = poth - eccen_1.e * 2. * rm / (1. - eccen_1.e * eccen_1.e);
	vl1 = eccen_1.vol1;
	volume_(&vl1, &rm, &p1ap, &dap, &f1, &nn1, &n1, &c__1, rv, grx, gry, 
		grz, rvq, grxq, gryq, grzq, mmsave, fr1, fr2, hld, snth, csth,
		 snfi, csfi, &summd, &smd, grv1, grv2, xx1, yy1, zz1, xx2, 
		yy2, zz2, csbt1, csbt2, glump1, glump2, gmag1, gmag2, glog1, 
		glog2, &gr1, &c__2, tloc1, tloc2, xinorm1, xinorm2);
	dpdx_2.dpdx1 = (poth - p1ap) * (1. - eccen_1.e * eccen_1.e) * .5 / 
		eccen_1.e;
	p2ap = potc - eccen_1.e * 2. / (1. - eccen_1.e * eccen_1.e);
	vl2 = eccen_1.vol2;
	volume_(&vl2, &rm, &p2ap, &dap, &f2, &n2, &n1, &c__2, rv, grx, gry, 
		grz, rvq, grxq, gryq, grzq, mmsave, fr1, fr2, hld, snth, csth,
		 snfi, csfi, &summd, &smd, grv1, grv2, xx1, yy1, zz1, xx2, 
		yy2, zz2, csbt1, csbt2, glump1, glump2, gmag1, gmag2, glog1, 
		glog2, &gr2, &c__2, tloc1, tloc2, xinorm1, xinorm2);
	dpdx_2.dpdx2 = (potc - p2ap) * (1. - eccen_1.e * eccen_1.e) * .5 / 
		eccen_1.e;
L117:
	dpdx_2.phsv = poth;
	dpdx_2.pcsv = potc;
	bbl_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, mmsave, fr1, fr2, hld, 
		slump1, slump2, theta, rho, aa, bb, &poth, &potc, &n1, &n2, &
		f1, &f2, &d__, &hlum, &clum, &xh, &xc, &yh, &yc, &gr1, &gr2, &
		wl, &sm1, &sm2, &tpolh, &tpolc, &sbrh, &sbrc, &tavh, &tavc, &
		alb1, &alb2, &xbol1, &xbol2, &ybol1, &ybol2, &phn, &rm, &
		xincl, &hot, &cool, snth, csth, snfi, csfi, tld, glump1, 
		glump2, xx1, xx2, yy1, yy2, zz1, zz2, &dint1, &dint2, grv1, 
		grv2, rftemp, rf1, rf2, csbt1, csbt2, gmag1, gmag2, glog1, 
		glog2, fbin1, fbin2, delv1, delv2, count1, count2, delwl1, 
		delwl2, resf1, resf2, wl1, wl2, dvks1, dvks2, tau1, tau2, 
		emm1, emm2, hbarw1, hbarw2, xcl, ycl, zcl, rcl, op1, fcl, 
		dens, encl, edens, taug, emmg, yskp, zskp, &mode, &iband, &
		ifat1, &ifat2, &c__1, tloc1, tloc2, xinorm1, xinorm2);
	invar_2.kh = 0;
/*     (3/4pi)^(1/3) = .6203505d0 */
	rr1 = pow_dd(&eccen_1.vol1, &ot) * .6203505;
	rr2 = pow_dd(&eccen_1.vol2, &ot) * .6203505;
	tav1 = tavh * 1e4;
	tav2 = tavc * 1e4;
	mlrg_(&eccen_1.a, &eccen_1.period, &rm, &rr1, &rr2, &tav1, &tav2, &
		sms1, &sms2, &sr1, &sr2, &bolm1, &bolm2, &xlg1, &xlg2);
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

	params[1] = hlum;
	params[2] = clum;
	params[3] = sms1;
	params[4] = sms2;
	params[5] = sr1;
	params[6] = sr2;
	params[7] = bolm1;
	params[8] = bolm2;
	params[9] = xlg1;
	params[10] = xlg2;
	params[11] = sbrh;
	params[12] = sbrc;
	params[13] = dpdx_2.phsv;
	params[14] = dpdx_2.pcsv;
	params[15] = eccen_1.vol1;
	params[16] = eccen_1.vol2;
/* ~       params(17) = ifr */

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	if (s_cmp(lcout, "", lcout_len, (ftnlen)0) != 0) {
	    wrhead_(&ibef, &invar_2.nref, &invar_2.mref, &invar_2.ifsmv1, &
		    invar_2.ifsmv2, &invar_2.icor1, &invar_2.icor2, &
		    invar_2.ld, &invar_2.jdphs, &ardot_1.hjd0, &
		    eccen_1.period, &dpdt, &flvar_1.pshift, &stdev, &noise, &
		    seed, &hjdst, &hjdsp, &hjdin, &phstrt, &phstop, &phin, &
		    phn, &mode, &invar_2.ipb, &ifat1, &ifat2, &n1, &n2, &
		    flvar_1.perr0, &ardot_1.dperdt, &the, &flvar_1.vunit, &
		    eccen_1.vfac, &eccen_1.e, &eccen_1.a, &f1, &f2, &
		    eccen_1.vga, &xincl, &gr1, &gr2, &nspt_1.nsp1, &
		    nspt_1.nsp2, &abunin, &tavh, &tavc, &alb1, &alb2, &
		    dpdx_2.phsv, &dpdx_2.pcsv, &rm, &xbol1, &xbol2, &ybol1, &
		    ybol2, &iband, &hlum, &clum, &xh, &xc, &yh, &yc, &el3, &
		    cld_1.opsf, &zero, &factor, &wl, &binwm1, &prof2_3.sc1, &
		    prof2_3.sl1, &binwm2, &prof2_3.sc2, &prof2_3.sl2, wll1, 
		    ewid1, depth1, wll2, ewid2, depth2, spots_2.kks, xlat, 
		    xlong, spots_2.radsp, spots_2.temsp, &invar_2.ncl, xcl, 
		    ycl, zcl, rcl, op1, fcl, edens, xmue, encl, dens, &ns1, &
		    sms1, &sr1, &bolm1, &xlg1, &ns2, &sms2, &sr2, &bolm2, &
		    xlg2, mmsave, &sbrh, &sbrc, &sm1, &sm2, &flvar_1.phperi, &
		    flvar_1.pconsc, &flvar_1.pconic, &dif1, &abunir, 
		    abung_1.abun, &mod);
	}
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

/*     The following block supports third light to be computed from the */
/*     passed percentage of third luminosity. */

	if (*l3perc == 1) {
	    el3 = (hlum + clum) * el3 / ((1. - el3) * 12.566371999999999);
	}

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	all = hot + cool + el3;
	if (mode == -1) {
	    all = cool + el3;
	}
	ll1 = mmsave[n1 - 1] + 1;
	npp2 = np2 - 1;
	ll2 = mmsave[npp2 - 1] + 1;
	lll1 = mmsave[np1 - 1];
	lll2 = mmsave[np2 - 1];
	llll1 = (ll1 + lll1) / 2;
	llll2 = (ll2 + lll2) / 2;
	poth = dpdx_2.phsv;
	potc = dpdx_2.pcsv;
	po[0] = poth;
	po[1] = potc;
	if (eccen_1.e == 0.) {
	    invar_2.irvol1 = 1;
	}
	if (eccen_1.e == 0.) {
	    invar_2.irvol2 = 1;
	}
	if (eccen_1.e == 0.) {
	    invar_2.irte = 1;
	}
	start = hjdst;
	stopp = hjdsp;
	step = hjdin;
	if (invar_2.jdphs != 2) {
	    goto L887;
	}
	start = phstrt;
	stopp = phstop;
	step = phin;
L887:
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

/*     do 20 phjd=start,stopp,step */
/*     hjdi=phjd */
/*     phasi=phjd */

	i__1 = *vertno;
	for (idx = 1; idx <= i__1; ++idx) {
	    hjdi = indeps[idx];
	    phasi = indeps[idx];

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	    jdph_(&hjdi, &phasi, &ardot_1.hjd0, &eccen_1.period, &dpdt, &hjdo,
		     &phaso);
	    ardot_1.hjd = hjdi;
	    phas = phasi;
	    if (invar_2.jdphs != 1) {
		ardot_1.hjd = hjdo;
	    }
	    if (invar_2.jdphs != 2) {
		phas = phaso;
	    }
	    modlog_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, mmsave, fr1, 
		    fr2, hld, &rm, &poth, &potc, &gr1, &gr2, &alb1, &alb2, &
		    n1, &n2, &f1, &f2, &mod, &xincl, &the, &mode, snth, csth, 
		    snfi, csfi, grv1, grv2, xx1, yy1, zz1, xx2, yy2, zz2, 
		    glump1, glump2, csbt1, csbt2, gmag1, gmag2, glog1, glog2, 
		    tloc1, tloc2, xinorm1, xinorm2);
	    bbl_(rv, grx, gry, grz, rvq, grxq, gryq, grzq, mmsave, fr1, fr2, 
		    hld, slump1, slump2, theta, rho, aa, bb, &poth, &potc, &
		    n1, &n2, &f1, &f2, &d__, &hlum, &clum, &xh, &xc, &yh, &yc,
		     &gr1, &gr2, &wl, &sm1, &sm2, &tpolh, &tpolc, &sbrh, &
		    sbrc, &tavh, &tavc, &alb1, &alb2, &xbol1, &xbol2, &ybol1, 
		    &ybol2, &phas, &rm, &xincl, &hot, &cool, snth, csth, snfi,
		     csfi, tld, glump1, glump2, xx1, xx2, yy1, yy2, zz1, zz2, 
		    &dint1, &dint2, grv1, grv2, rftemp, rf1, rf2, csbt1, 
		    csbt2, gmag1, gmag2, glog1, glog2, fbin1, fbin2, delv1, 
		    delv2, count1, count2, delwl1, delwl2, resf1, resf2, wl1, 
		    wl2, dvks1, dvks2, tau1, tau2, emm1, emm2, hbarw1, hbarw2,
		     xcl, ycl, zcl, rcl, op1, fcl, dens, encl, edens, taug, 
		    emmg, yskp, zskp, &mode, &iband, &ifat1, &ifat2, &c__0, 
		    tloc1, tloc2, xinorm1, xinorm2);
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

/*     grv1(igsmax),grv2(igsmax),rftemp(igsmax), */
/*     $rf1(igsmax),rf2(igsmax) */

	    if (*mswitch == 1) {
		nc = 15;
		i__2 = mmsave[n1];
		for (igsidx = 1; igsidx <= i__2; ++igsidx) {
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 1]
			     = xx1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 2]
			     = yy1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 3]
			     = zz1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 4]
			     = rv[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 5]
			     = grx[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 6]
			     = gry[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 7]
			     = grz[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 8]
			     = fr1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 9]
			     = slump1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 
			    10] = glump1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 
			    11] = gmag1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 
			    12] = glog1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 
			    13] = csbt1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 
			    14] = tloc1[igsidx - 1];
		    mesh1[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 
			    15] = xinorm1[igsidx - 1];
/* L665: */
		}
		i__2 = mmsave[n2];
		for (igsidx = 1; igsidx <= i__2; ++igsidx) {
		    mesh2[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 1]
			     = xx2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 2]
			     = yy2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n1] * nc + (igsidx - 1) * nc + 3]
			     = zz2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 4]
			     = rvq[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 5]
			     = grxq[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 6]
			     = gryq[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 7]
			     = grzq[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 8]
			     = fr2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 9]
			     = slump2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 
			    10] = glump2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 
			    11] = gmag2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 
			    12] = glog2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 
			    13] = csbt2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 
			    14] = tloc2[igsidx - 1];
		    mesh2[(idx - 1) * mmsave[n2] * nc + (igsidx - 1) * nc + 
			    15] = xinorm2[igsidx - 1];
/* L666: */
		}
	    }
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	    htt = hot;
	    if (mode == -1) {
		htt = 0.;
	    }
	    total = htt + cool + el3;
	    totall = total / all;
	    tot = totall * factor;
	    if (stdev <= 0.) {
		goto L348;
	    }
	    rangau_(&seed, &nn, &stdev, &gau);
	    ranf = gau * sqrt(pow_di(&totall, &noise)) + 1.;
	    total *= ranf;
	    tot *= ranf;
	    totall *= ranf;
L348:
	    smagg = log(totall) * -1.085736 + zero;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE extension: */

	    if (*request == 1) {
		deps[idx] = total;
	    }
	    if (*request == 2) {
		deps[idx] = flvar_1.vkm1;
	    }
	    if (*request == 3) {
		deps[idx] = flvar_1.vkm2;
	    }
	    if (*request == 4) {
		i__2 = invar_2.ipc;
		for (imp = 1; imp <= i__2; ++imp) {
		    skycoy[imp] = yskp[imp - 1];
		    skycoz[imp] = zskp[imp - 1];
/* L129: */
		}
	    }
	    if (*hswitch == 1) {
		for (imp = 1; imp <= 800; ++imp) {
		    hrho[imp] = rho[imp - 1];
		    htheta[imp] = theta[imp - 1];
/* L130: */
		}
		for (imp = 1; imp <= 6; ++imp) {
		    hac[imp] = aa[imp - 1];
		    has[imp] = bb[imp - 1];
/* L131: */
		}
	    }

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
	    if (s_cmp(lcout, "", lcout_len, (ftnlen)0) != 0) {
		wrdata_(&ardot_1.hjd, &phas, yskp, zskp, &htt, &cool, &total, 
			&tot, &d__, &smagg, &flvar_1.vsum1, &flvar_1.vsum2, &
			flvar_1.vra1, &flvar_1.vra2, &flvar_1.vkm1, &
			flvar_1.vkm2, delv1, delwl1, wl1, fbin1, resf1, delv2,
			 delwl2, wl2, fbin2, resf2, rv, rvq, mmsave, &ll1, &
			lll1, &llll1, &ll2, &lll2, &llll2);
	    }
/* L20: */
	}
	if (s_cmp(lcout, "", lcout_len, (ftnlen)0) != 0) {
	    wrfoot_(atmmessages_1.message, &f1, &f2, po, &rm, &f, &flvar_1.dp,
		     &eccen_1.e, &drdq, &dodq, &ii, &mode, &inprof_1.mpage);
	}
	ibef = 1;
/* L1000: */
    }
    s_stop("", (ftnlen)0);
    return 0;
} /* lc_ */

/* Subroutine */ int legendre_(doublereal *x, doublereal *pleg, integer *n)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static doublereal fac1, fac2, denom;

/*  Version of January 7, 2002 */
    /* Parameter adjustments */
    --pleg;

    /* Function Body */
    pleg[1] = 1.;
    pleg[2] = *x;
    if (*n <= 2) {
	return 0;
    }
    denom = 1.;
    i__1 = *n;
    for (i__ = 3; i__ <= i__1; ++i__) {
	fac1 = *x * (denom * 2. + 1.);
	fac2 = denom;
	denom += 1.;
	pleg[i__] = (fac1 * pleg[i__ - 1] - fac2 * pleg[i__ - 2]) / denom;
/* L1: */
    }
    return 0;
} /* legendre_ */

/* Subroutine */ int light_(doublereal *phs, doublereal *xincl, doublereal *
	xh, doublereal *xc, doublereal *yh, doublereal *yc, integer *n1, 
	integer *n2, doublereal *sumhot, doublereal *sumkul, doublereal *rv, 
	doublereal *grx, doublereal *gry, doublereal *grz, doublereal *rvq, 
	doublereal *grxq, doublereal *gryq, doublereal *grzq, integer *mmsave,
	 doublereal *theta, doublereal *rho, doublereal *aa, doublereal *bb, 
	doublereal *slump1, doublereal *slump2, doublereal *somhot, 
	doublereal *somkul, doublereal *d__, doublereal *wl, doublereal *snth,
	 doublereal *csth, doublereal *snfi, doublereal *csfi, doublereal *
	tld, doublereal *gmag1, doublereal *gmag2, doublereal *glog1, 
	doublereal *glog2, doublereal *fbin1, doublereal *fbin2, doublereal *
	delv1, doublereal *delv2, doublereal *count1, doublereal *count2, 
	doublereal *delwl1, doublereal *delwl2, doublereal *resf1, doublereal 
	*resf2, doublereal *wl1, doublereal *wl2, doublereal *dvks1, 
	doublereal *dvks2, doublereal *tau1, doublereal *tau2, doublereal *
	emm1, doublereal *emm2, doublereal *hbarw1, doublereal *hbarw2, 
	doublereal *xcl, doublereal *ycl, doublereal *zcl, doublereal *rcl, 
	doublereal *op1, doublereal *fcl, doublereal *edens, doublereal *encl,
	 doublereal *dens, doublereal *taug, doublereal *emmg, doublereal *
	yskp, doublereal *zskp, integer *iband, integer *ifat1, integer *
	ifat2, integer *ifphn)
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double acos(doublereal), sin(doublereal), cos(doublereal), sqrt(
	    doublereal), asin(doublereal), log(doublereal);

    /* Local variables */
    static doublereal xintbase, xintspot;
    static integer i__, j, k, l, n;
    static doublereal r__, v;
    extern /* Subroutine */ int planckint_(doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal ab;
    static integer kf;
    static doublereal em, en;
    static integer nf;
    static doublereal ar;
    static integer kk;
    static doublereal br;
    static integer ik;
    static doublereal pi;
    static integer mm, np, mh, ip, iy;
    static doublereal xm, gx, gy, gz;
    static integer jk, ix, is, jn;
    static doublereal ri, dx, xx;
    static integer lk;
    static doublereal yy, zz;
    static integer ll1, ll2, np1, np2;
    static doublereal ffc, dif, ang;
    static integer icl;
    static doublereal pha, pih, dtr, som, cmp, voc, sum;
    static integer nph;
    static doublereal enf, asq, bsq;
    static integer npp, mpp;
    static doublereal stp, tsp, rit, tau, vks;
    static integer ifn, jfn;
    static doublereal dlr, ffi, vdc, vfc;
    static integer nfm1, lll1, lll2, ipn1, npp2;
    static doublereal dfif, diff, fact, cicp, cirf;
    static integer ifat;
    static doublereal absq, asbs, cmpd, temf, cosi, xinc, sini, cisp, comp, 
	    cmpp, somj, sumj, test, stsf;
    static integer kstp;
    static doublereal xlos, ylos, zlos, stcf, binc1, binc2;
    extern /* Subroutine */ int spot_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal yskr, zskr, prod, ysky;
    static integer marm1, marm2;
    static doublereal zsky;
    static integer marp1, marp2, llll1, llll2;
    extern /* Subroutine */ int atmx_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal vcks, dvdr, dthf, rmax, rmin, sign, drho, rrho, thet, 
	    rhho, ennn, rdif, corr, delfi, dvdfi, grmag, delth, glogg, oldif, 
	    cmppd, cosfi, cosph, compp, costh, sinph, tanth, sinfi;
    extern /* Subroutine */ int cloud_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal sinth, dvdth, safty, corrr, sumdr, snthl, sinsq, twopi, 
	    tests;
    static integer nspot;
    static doublereal rptsq, r2nfdf, r2nfdt, corfac, dvdfib, darken, cosgam, 
	    opsfcl, oldrho, olsign, enthet, cossav, rtleft, sinsqe, vfvuff;
    extern /* Subroutine */ int linpro_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal vflump, updown;
    extern /* Subroutine */ int fourls_(doublereal *, doublereal *, integer *,
	     integer *, doublereal *, doublereal *);
    static doublereal rtstsq, xintlog;

/*   Version of October 18, 2004 */
    /* Parameter adjustments */
    --zskp;
    --yskp;
    --emmg;
    --taug;
    --dens;
    --encl;
    --edens;
    --fcl;
    --op1;
    --rcl;
    --zcl;
    --ycl;
    --xcl;
    --hbarw2;
    --hbarw1;
    --emm2;
    --emm1;
    --tau2;
    --tau1;
    --dvks2;
    --dvks1;
    --wl2;
    --wl1;
    --resf2;
    --resf1;
    --delwl2;
    --delwl1;
    --count2;
    --count1;
    --delv2;
    --delv1;
    --fbin2;
    --fbin1;
    --glog2;
    --glog1;
    --gmag2;
    --gmag1;
    --tld;
    --csfi;
    --snfi;
    --csth;
    --snth;
    --slump2;
    --slump1;
    --bb;
    --aa;
    --rho;
    --theta;
    --mmsave;
    --grzq;
    --gryq;
    --grxq;
    --rvq;
    --grz;
    --gry;
    --grx;
    --rv;

    /* Function Body */
    pi = acos(-1.);
    twopi = pi + pi;
    pih = pi * .5;
    dtr = pi / 180.;
    kstp = 4;
    cirf = .002;
    if (*ifphn == 1) {
	goto L16;
    }
    if (inprof_1.mpage != 3) {
	goto L16;
    }
    ipro_1.nbins = 90000;
    binc1 = (doublereal) ipro_1.nbins * .5;
    binc2 = binc1;
    inprof_1.in1max = 0;
    inprof_1.in2max = 0;
    inprof_1.in1min = 300000;
    inprof_1.in2min = 300000;
    marm1 = 10;
    marp1 = 10;
    marm2 = 10;
    marp2 = 10;
    i__1 = ipro_1.nbins;
    for (i__ = 1; i__ <= i__1; ++i__) {
	fbin1[i__] = 0.;
	fbin2[i__] = 0.;
	count1[i__] = 0.;
	count2[i__] = 0.;
	delv1[i__] = 0.;
	delv2[i__] = 0.;
/* L916: */
    }
L16:
    pha = *phs * twopi;
    k = 6;
    kk = k + 1;
    xinc = *xincl * dtr;
    l = 1;
/* Computing 2nd power */
    d__1 = *phs - .5;
    test = d__1 * d__1;
/* Computing 2nd power */
    d__1 = test - .071525;
    tests = d__1 * d__1;
    sini = sin(xinc);
    cosph = cos(pha);
    sinph = sin(pha);
/* Computing 2nd power */
    d__1 = sinph;
    sinsq = d__1 * d__1;
    cosi = cos(xinc);
    np1 = *n1 + 1;
    np2 = *n1 + *n2 + 2;
    lll1 = mmsave[np1];
    lll2 = mmsave[np2];
    npp2 = np2 - 1;
    ll1 = mmsave[*n1] + 1;
    ll2 = mmsave[npp2] + 1;
    llll1 = (ll1 + lll1) / 2;
    llll2 = (ll2 + lll2) / 2;
    sinsqe = 0.;
    if (sini > 0.) {
/* Computing 2nd power */
	d__1 = (rv[lll1] + rvq[lll2]) * 1.1 / *d__;
/* Computing 2nd power */
	d__2 = cosi;
/* Computing 2nd power */
	d__3 = sini;
	sinsqe = (d__1 * d__1 - d__2 * d__2) / (d__3 * d__3);
    }
    cicp = cosi * cosph;
    cisp = cosi * sinph;
    xlos = cosph * sini;
    ylos = -sinph * sini;
    zlos = cosi;
    sum = 0.;
    som = 0.;
    if (test <= .0625) {
	goto L18;
    }
    comp = -1.;
    cmp = 1.;
    compp = 1.;
    atmmessages_1.komp = 2;
    ipro_1.nl = inprof_1.nl2;
    ffc = prof2_4.ff2;
    voc = prof2_4.vo2 * flvar_3.vfvu;
    nspot = nspt_1.nsp2;
    ifat = *ifat2;
    cmpp = 0.;
    coflimbdark_2.x = *xc;
    coflimbdark_2.y = *yc;
    en = (doublereal) (*n2);
    nph = *n2;
    np = *n2 << 1;
    nf = ipro_1.nf2;
    goto L28;
L18:
    coflimbdark_2.x = *xh;
    coflimbdark_2.y = *yh;
    comp = 1.;
    atmmessages_1.komp = 1;
    ipro_1.nl = inprof_1.nl1;
    ffc = prof2_4.ff1;
    voc = prof2_4.vo1 * flvar_3.vfvu;
    nspot = nspt_1.nsp1;
    ifat = *ifat1;
    cmp = 0.;
    compp = -1.;
    cmpp = 1.;
    en = (doublereal) (*n1);
    nph = *n1;
    np = *n1 << 1;
    nf = ipro_1.nf1;
L28:
    delth = pih / en;
    enf = (doublereal) nf;
    flpro_1.renfsq = 1. / (enf * enf);
    nfm1 = nf - 1;
    r2nfdt = delth * .5 / enf;
    vfvuff = flvar_3.vfvu * ffc;
    ar = cmpp * rv[llll1] + cmp * rvq[llll2];
    br = cmpp * rv[1] + cmp * rvq[1];
    asq = ar * ar;
    bsq = br * br;
    ab = ar * br;
    absq = ab * ab;
    asbs = asq - bsq;
    kf = (2 - atmmessages_1.komp) * kfac_1.kff1 + (atmmessages_1.komp - 1) * 
	    kfac_1.kff2;
    cmppd = cmpp * *d__;
    cmpd = cmp * *d__;
    npp = np + 1;
    temf = 1.;
    invar_4.ipc = 0;
    i__1 = np;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (i__ > nph) {
	    goto L54;
	}
	updown = 1.;
	ik = i__;
	goto L55;
L54:
	updown = -1.;
	ik = npp - i__;
L55:
	ipn1 = ik + (atmmessages_1.komp - 1) * *n1;
	sinth = snth[ipn1];
	costh = csth[ipn1] * updown;
	tanth = sinth / costh;
	em = sinth * en * 1.3;
	mm = (integer) (em + 1.);
	xm = (doublereal) mm;
	mh = mm;
	mm <<= 1;
	delfi = pi / xm;
	r2nfdf = .5 / enf;
	flpro_1.deldel = delth * delfi;
	ip = (atmmessages_1.komp - 1) * np1 + ik;
	iy = mmsave[ip] + 1;
	if (test <= .0625) {
	    goto L19;
	}
	gx = grxq[iy];
	gy = -gryq[iy];
	gz = updown * grzq[iy];
	grmag = gmag2[iy];
	goto L29;
L19:
	gx = grx[iy];
	gy = -gry[iy];
	gz = updown * grz[iy];
	grmag = gmag1[iy];
L29:
	cossav = (xlos * gx + ylos * gy + zlos * gz) / grmag;
	sumj = 0.;
	somj = 0.;
	mpp = mm + 1;
	--iy;
	i__2 = mm;
	for (j = 1; j <= i__2; ++j) {
	    if (j > mh) {
		goto L58;
	    }
	    rtleft = 1.;
	    jk = j;
	    goto L59;
L58:
	    rtleft = -1.;
	    jk = mpp - j;
L59:
	    ix = iy + jk;
	    is = ix + (atmmessages_1.komp - 1) * lll1;
	    sinfi = snfi[is] * rtleft;
	    cosfi = csfi[is];
	    stsf = sinth * sinfi;
	    stcf = sinth * cosfi;
	    if (test <= .0625) {
		goto L39;
	    }
	    if (rvq[ix] == -1.) {
		goto L26;
	    }
	    gx = grxq[ix];
	    gy = rtleft * gryq[ix];
	    gz = updown * grzq[ix];
	    r__ = rvq[ix];
	    grmag = gmag2[ix];
	    goto L49;
L39:
	    if (rv[ix] == -1.) {
		goto L26;
	    }
	    gx = grx[ix];
	    gy = rtleft * gry[ix];
	    gz = updown * grz[ix];
	    r__ = rv[ix];
	    grmag = gmag1[ix];
L49:
	    cosgam = (xlos * gx + ylos * gy + zlos * gz) / grmag;
	    zz = r__ * costh;
	    yy = r__ * comp * stsf;
	    xx = cmpd + comp * stcf * r__;
	    if (inprof_1.mpage != 5) {
		goto L174;
	    }
	    if (cosgam > 0.) {
		goto L174;
	    }
	    ++invar_4.ipc;
	    yskp[invar_4.ipc] = (xx - flvar_3.qfacd) * sinph + yy * cosph;
	    zskp[invar_4.ipc] = (-xx + flvar_3.qfacd) * cicp + yy * cisp + zz 
		    * sini;
	    if (nspot == 0) {
		goto L174;
	    }
	    spot_(&atmmessages_1.komp, &nspot, &sinth, &costh, &sinfi, &cosfi,
		     &temf);
	    if (temf == 1.) {
		goto L174;
	    }
	    yskr = yskp[invar_4.ipc];
	    zskr = zskp[invar_4.ipc];
	    kstp = 4;
	    cirf = .002;
	    stp = twopi / (doublereal) kstp;
	    d__1 = twopi;
	    d__2 = stp;
	    for (ang = stp; d__2 < 0 ? ang >= d__1 : ang <= d__1; ang += d__2)
		     {
		++invar_4.ipc;
		yskp[invar_4.ipc] = yskr + sin(ang) * cirf;
		zskp[invar_4.ipc] = zskr + cos(ang) * cirf;
/* L179: */
	    }
L174:
	    if (sinsq > sinsqe) {
		goto L27;
	    }
	    if (tests < .0022562) {
		goto L170;
	    }
	    if (stcf * r__ > setest_1.sefac * (cmp + comp * misc_1.x1)) {
		goto L129;
	    }
L170:
	    prod = cossav * cosgam;
	    if (prod > 0.) {
		goto L22;
	    }
	    cossav = -cossav;
	    ysky = xx * sinph + yy * cosph - cmpd * sinph;
	    zsky = -xx * cicp + yy * cisp + zz * sini + cmpd * cicp;
/* Computing 2nd power */
	    d__2 = ysky;
/* Computing 2nd power */
	    d__1 = zsky;
	    rho[l] = sqrt(d__2 * d__2 + d__1 * d__1);
	    theta[l] = asin(zsky / rho[l]);
	    if (ysky < 0.) {
		goto L92;
	    }
	    theta[l] = twopi + theta[l];
	    goto L93;
L92:
	    theta[l] = pi - theta[l];
L93:
	    if (theta[l] >= twopi) {
		theta[l] -= twopi;
	    }
	    ++l;
	    goto L27;
L22:
	    cossav = cosgam;
	    goto L27;
L129:
	    cossav = cosgam;
	    if (kf <= 0) {
		goto L27;
	    }
	    zz = r__ * costh;
	    yy = r__ * comp * stsf;
	    xx = cmpd + comp * stcf * r__;
	    ysky = xx * sinph + yy * cosph - cmpd * sinph;
	    zsky = -xx * cicp + yy * cisp + zz * sini + cmpd * cicp;
/* Computing 2nd power */
	    d__2 = ysky;
/* Computing 2nd power */
	    d__1 = zsky;
	    rptsq = d__2 * d__2 + d__1 * d__1;
/* Computing 2nd power */
	    d__2 = zsky;
	    rtstsq = absq / (bsq + asbs * (d__2 * d__2 / rptsq));
	    if (rptsq <= rtstsq) {
		goto L26;
	    }
L27:
	    if (cosgam >= 0.) {
		goto L26;
	    }
	    cosgam = -cosgam;
	    darken = 1. - coflimbdark_2.x + coflimbdark_2.x * cosgam;
	    if (invar_4.ld != 2) {
		goto L141;
	    }
	    if (cosgam == 0.) {
		goto L141;
	    }
	    darken -= coflimbdark_2.y * cosgam * log(cosgam);
	    goto L147;
L141:
	    if (invar_4.ld == 3) {
		darken -= coflimbdark_2.y * (1. - sqrt(cosgam));
	    }
L147:
	    if (darken < 0.) {
		darken = 0.;
	    }
	    corfac = 1.;
	    i__3 = ipro_1.nl;
	    for (jn = 1; jn <= i__3; ++jn) {
		spots_3.lspot[atmmessages_1.komp + (jn << 1) - 3] = 0;
/* L923: */
		if (spots_3.kks[atmmessages_1.komp + (jn << 1) - 3] == 0) {
		    spots_3.lspot[atmmessages_1.komp + (jn << 1) - 3] = 1;
		}
	    }
	    if (nspot == 0) {
		goto L640;
	    }
	    spot_(&atmmessages_1.komp, &nspot, &sinth, &costh, &sinfi, &cosfi,
		     &temf);
	    if (temf == 1.) {
		goto L640;
	    }
	    tsp = tld[is] * temf;
	    if (ifat == 0) {
		planckint_(&tld[is], iband, &xintlog, &xintbase);
	    }
	    if (ifat == 0) {
		planckint_(&tsp, iband, &xintlog, &xintspot);
	    }
	    if (ifat == 0) {
		goto L941;
	    }
	    glogg = cmpp * glog1[ix] + cmp * glog2[ix];
	    atmx_(&tld[is], &glogg, iband, &xintlog, &xintbase);
	    atmx_(&tsp, &glogg, iband, &xintlog, &xintspot);
L941:
	    corfac = xintspot / xintbase;
L640:
	    rit = 1.;
	    if (invar_4.ncl == 0) {
		goto L818;
	    }
	    i__3 = invar_4.ncl;
	    for (icl = 1; icl <= i__3; ++icl) {
		opsfcl = cld_1.opsf * fcl[icl];
		cloud_(&xlos, &ylos, &zlos, &xx, &yy, &zz, &xcl[icl], &ycl[
			icl], &zcl[icl], &rcl[icl], wl, &op1[icl], &opsfcl, &
			edens[icl], &cld_1.acm, &encl[icl], &cmpd, &ri, &dx, &
			dens[icl], &tau);
		rit *= ri;
/* L815: */
	    }
L818:
	    dif = rit * cosgam * darken * corfac * (cmp * slump2[ix] + cmpp * 
		    slump1[ix]);
	    v = -r__ * (stcf * ylos - stsf * xlos) * comp;
	    if (*ifphn == 1) {
		goto L423;
	    }
	    if (inprof_1.mpage != 3) {
		goto L423;
	    }
	    vflump = vfvuff * r__ * comp * costh;
	    vcks = v * vfvuff;
	    vks = vcks + voc;
	    flpro_1.vksf = vks;
	    dvdr = vcks / r__;
	    dvdth = vcks / tanth;
	    dvdfib = vfvuff * r__ * comp * (sinfi * ylos + cosfi * xlos);
/*     dvdfic=dvdfib*sinth */
	    flpro_1.difp = dif * flpro_1.deldel * flpro_1.renfsq;
/*  dvdth and dvdfi (below) each need another term involving dr/d(theta) */
/*    or dr/d(fi), that I will put in later. There will be a small loss */
/*    of accuracy for distorted stars without those terms. See notes. */
	    if (atmmessages_1.komp == 2) {
		goto L422;
	    }
	    flpro_1.binc = binc1;
	    flpro_1.binw = prof2_4.binw1;
	    i__3 = nfm1;
	    for (ifn = -nfm1; ifn <= i__3; ifn += 2) {
		dthf = (doublereal) ifn * r2nfdt;
		dvdfi = dvdfib * (sinth + costh * dthf);
		i__4 = nfm1;
		for (jfn = -nfm1; jfn <= i__4; jfn += 2) {
		    if (nf == 1) {
			goto L1047;
		    }
		    dfif = (doublereal) jfn * r2nfdf * delfi;
		    dvdth = -vflump * ((cosfi - sinfi * dfif) * ylos - (sinfi 
			    + cosfi * dfif) * xlos);
		    dlr = 0.;
		    flpro_1.vksf = vks + dvdr * dlr + dvdth * dthf + dvdfi * 
			    dfif;
L1047:
		    linpro_(&atmmessages_1.komp, &dvks1[1], &hbarw1[1], &tau1[
			    1], &emm1[1], &count1[1], &taug[1], &emmg[1], &
			    fbin1[1], &delv1[1]);
		    if (ipro_1.inmin < inprof_1.in1min) {
			inprof_1.in1min = ipro_1.inmin;
		    }
		    if (ipro_1.inmax > inprof_1.in1max) {
			inprof_1.in1max = ipro_1.inmax;
		    }
/* L1046: */
		}
/* L1045: */
	    }
	    goto L423;
L422:
	    flpro_1.binc = binc2;
	    flpro_1.binw = prof2_4.binw2;
	    i__3 = nfm1;
	    for (ifn = -nfm1; ifn <= i__3; ifn += 2) {
		dthf = (doublereal) ifn * r2nfdt;
		dvdfi = dvdfib * (sinth + costh * dthf);
		i__4 = nfm1;
		for (jfn = -nfm1; jfn <= i__4; jfn += 2) {
		    if (nf == 1) {
			goto L1147;
		    }
		    dfif = (doublereal) jfn * r2nfdf * delfi;
		    dvdth = -vflump * ((cosfi - sinfi * dfif) * ylos - (sinfi 
			    + cosfi * dfif) * xlos);
		    dlr = 0.;
		    flpro_1.vksf = vks + dvdr * dlr + dvdth * dthf + dvdfi * 
			    dfif;
		    ffi = acos(cosfi);
		    if (sinfi < 0.) {
			ffi = twopi - ffi;
		    }
L1147:
		    linpro_(&atmmessages_1.komp, &dvks2[1], &hbarw2[1], &tau2[
			    1], &emm2[1], &count2[1], &taug[1], &emmg[1], &
			    fbin2[1], &delv2[1]);
		    if (ipro_1.inmin < inprof_1.in2min) {
			inprof_1.in2min = ipro_1.inmin;
		    }
		    if (ipro_1.inmax > inprof_1.in2max) {
			inprof_1.in2max = ipro_1.inmax;
		    }
/* L1146: */
		}
/* L1145: */
	    }
L423:
	    diff = dif * v;
	    somj += diff;
	    sumj += dif;
L26:
	    ;
	}
	somj *= delfi;
	sumj *= delfi;
	som += somj;
/* L36: */
	sum += sumj;
    }
    if (sinsq >= sinsqe) {
	goto L75;
    }
    --l;
    lk = k;
    if (l < 14) {
	lk = l / 2 - 1;
    }
    fourls_(&theta[1], &rho[1], &l, &lk, &aa[1], &bb[1]);
L75:
    if (test <= .0625) {
	goto L118;
    }
    *sumkul = sum * delth;
    *somkul = som * delth;
    coflimbdark_2.x = *xh;
    coflimbdark_2.y = *yh;
    atmmessages_1.komp = 1;
    ipro_1.nl = inprof_1.nl1;
    ffc = prof2_4.ff1;
    voc = prof2_4.vo1 * flvar_3.vfvu;
    nspot = nspt_1.nsp1;
    ifat = *ifat1;
    en = (doublereal) (*n1);
    safty = rv[lll1] * 2.6 / en;
    rmax = rvq[lll2] + safty;
    rmin = rvq[1] - safty;
    nph = *n1;
    np = *n1 << 1;
    nf = ipro_1.nf1;
    goto L128;
L118:
    coflimbdark_2.x = *xc;
    coflimbdark_2.y = *yc;
    atmmessages_1.komp = 2;
    ipro_1.nl = inprof_1.nl2;
    ffc = prof2_4.ff2;
    voc = prof2_4.vo2 * flvar_3.vfvu;
    nspot = nspt_1.nsp2;
    ifat = *ifat2;
    *sumhot = sum * delth;
    *somhot = som * delth;
    if (ipro_1.inmax > inprof_1.in1max) {
	inprof_1.in1max = ipro_1.inmax;
    }
    if (ipro_1.inmin < inprof_1.in1min) {
	inprof_1.in1min = ipro_1.inmin;
    }
    en = (doublereal) (*n2);
    safty = rvq[lll2] * 2.6 / en;
    rmax = rv[lll1] + safty;
    rmin = rv[1] - safty;
    nph = *n2;
    np = *n2 << 1;
    nf = ipro_1.nf2;
L128:
    delth = pih / en;
    enf = (doublereal) nf;
    nfm1 = nf - 1;
    flpro_1.renfsq = 1. / (enf * enf);
    r2nfdt = delth * .5 / enf;
    vfvuff = flvar_3.vfvu * ffc;
    som = 0.;
    sum = 0.;
    npp = np + 1;
    temf = 1.;
    ipro_1.inmin = 300000;
    ipro_1.inmax = 0;
    i__1 = np;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (i__ > nph) {
	    goto L154;
	}
	updown = 1.;
	ik = i__;
	goto L155;
L154:
	updown = -1.;
	ik = npp - i__;
L155:
	ipn1 = ik + (atmmessages_1.komp - 1) * *n1;
	sinth = snth[ipn1];
	costh = csth[ipn1] * updown;
	tanth = sinth / costh;
	em = sinth * en * 1.3;
	mm = (integer) (em + 1.);
	xm = (doublereal) mm;
	mh = mm;
	mm <<= 1;
	delfi = pi / xm;
	flpro_1.deldel = delth * delfi;
	somj = 0.;
	sumj = 0.;
	sign = 0.;
	drho = 1.;
	mpp = mm + 1;
	i__2 = mm;
	for (j = 1; j <= i__2; ++j) {
	    if (j > mh) {
		goto L158;
	    }
	    rtleft = 1.;
	    jk = j;
	    goto L159;
L158:
	    rtleft = -1.;
	    jk = mpp - j;
L159:
	    ip = (atmmessages_1.komp - 1) * np1 + ik;
	    ix = mmsave[ip] + jk;
	    is = ix + lll1 * (atmmessages_1.komp - 1);
	    sinfi = snfi[is] * rtleft;
	    cosfi = csfi[is];
	    stsf = sinth * sinfi;
	    stcf = sinth * cosfi;
	    if (test <= .0625) {
		goto L139;
	    }
	    if (rv[ix] == -1.) {
		goto L126;
	    }
	    gx = grx[ix];
	    gy = rtleft * gry[ix];
	    gz = updown * grz[ix];
	    r__ = rv[ix];
	    grmag = gmag1[ix];
	    goto L149;
L139:
	    if (rvq[ix] == -1.) {
		goto L126;
	    }
	    gx = grxq[ix];
	    gy = rtleft * gryq[ix];
	    gz = updown * grzq[ix];
	    r__ = rvq[ix];
	    grmag = gmag2[ix];
L149:
	    cosgam = (xlos * gx + ylos * gy + zlos * gz) / grmag;
	    if (cosgam < 0.) {
		goto L104;
	    }
	    sign = 0.;
	    olsign = 0.;
	    goto L126;
L104:
	    cosgam = -cosgam;
	    zz = r__ * costh;
	    yy = r__ * compp * stsf;
	    xx = cmppd + compp * stcf * r__;
	    darken = 1. - coflimbdark_2.x + coflimbdark_2.x * cosgam;
	    if (invar_4.ld != 2) {
		goto L142;
	    }
	    if (cosgam == 0.) {
		goto L142;
	    }
	    darken -= coflimbdark_2.y * cosgam * log(cosgam);
	    goto L148;
L142:
	    if (invar_4.ld == 3) {
		darken -= coflimbdark_2.y * (1. - sqrt(cosgam));
	    }
L148:
	    if (darken < 0.) {
		darken = 0.;
	    }
	    oldif = dif;
	    corfac = 1.;
	    i__3 = ipro_1.nl;
	    for (jn = 1; jn <= i__3; ++jn) {
		spots_3.lspot[atmmessages_1.komp + (jn << 1) - 3] = 0;
/* L823: */
		if (spots_3.kks[atmmessages_1.komp + (jn << 1) - 3] == 0) {
		    spots_3.lspot[atmmessages_1.komp + (jn << 1) - 3] = 1;
		}
	    }
	    if (nspot == 0) {
		goto L660;
	    }
	    spot_(&atmmessages_1.komp, &nspot, &sinth, &costh, &sinfi, &cosfi,
		     &temf);
	    if (temf == 1.) {
		goto L660;
	    }
	    tsp = tld[is] * temf;
	    if (ifat == 0) {
		planckint_(&tld[is], iband, &xintlog, &xintbase);
	    }
	    if (ifat == 0) {
		planckint_(&tsp, iband, &xintlog, &xintspot);
	    }
	    if (ifat == 0) {
		goto L661;
	    }
	    glogg = cmp * glog1[ix] + cmpp * glog2[ix];
	    atmx_(&tld[is], &glogg, iband, &xintlog, &xintbase);
	    atmx_(&tsp, &glogg, iband, &xintlog, &xintspot);
L661:
	    corfac = xintspot / xintbase;
L660:
	    rit = 1.;
	    if (invar_4.ncl == 0) {
		goto L718;
	    }
	    i__3 = invar_4.ncl;
	    for (icl = 1; icl <= i__3; ++icl) {
		opsfcl = cld_1.opsf * fcl[icl];
		cloud_(&xlos, &ylos, &zlos, &xx, &yy, &zz, &xcl[icl], &ycl[
			icl], &zcl[icl], &rcl[icl], wl, &op1[icl], &opsfcl, &
			edens[icl], &cld_1.acm, &encl[icl], &cmppd, &ri, &dx, 
			&dens[icl], &tau);
		rit *= ri;
/* L715: */
	    }
L718:
	    dif = rit * cosgam * darken * corfac * (cmpp * slump2[ix] + cmp * 
		    slump1[ix]);
	    v = r__ * (stcf * ylos - stsf * xlos) * comp;
	    diff = dif * v;
	    if (sinsq > sinsqe) {
		goto L63;
	    }
	    olsign = sign;
	    oldrho = drho;
	    ysky = xx * sinph + yy * cosph - cmpd * sinph;
	    zsky = -xx * cicp + yy * cisp + zz * sini + cmpd * cicp;
	    rrho = sqrt(ysky * ysky + zsky * zsky);
	    if (rrho > rmax) {
		goto L63;
	    }
	    if (rrho < rmin) {
		goto L126;
	    }
	    thet = asin(zsky / rrho);
	    if (ysky < 0.) {
		goto L192;
	    }
	    thet = twopi + thet;
	    goto L193;
L192:
	    thet = pi - thet;
L193:
	    if (thet >= twopi) {
		thet -= twopi;
	    }
	    rhho = 0.;
	    i__3 = kk;
	    for (n = 1; n <= i__3; ++n) {
		ennn = (doublereal) (n - 1);
		enthet = ennn * thet;
/* L52: */
		rhho = rhho + aa[n] * cos(enthet) + bb[n] * sin(enthet);
	    }
	    sign = 1.;
	    if (rrho <= rhho) {
		sign = -1.;
	    }
	    if (inprof_1.mpage == 3) {
		goto L861;
	    }
	    drho = (d__2 = rrho - rhho, abs(d__2));
	    if (sign * olsign >= 0.) {
		goto L60;
	    }
	    sumdr = drho + oldrho;
	    fact = -(.5 - drho / sumdr);
	    if (fact < 0.) {
		goto L198;
	    }
	    rdif = oldif;
	    goto L199;
L198:
	    rdif = dif;
L199:
	    corr = fact * rdif * sign;
	    corrr = corr * v;
	    sumj += corr;
	    somj += corrr;
L60:
	    if (sign < 0.) {
		goto L126;
	    }
L63:
	    sumj += dif;
	    somj += diff;
	    if (inprof_1.mpage != 5) {
		goto L127;
	    }
	    ++invar_4.ipc;
	    yskp[invar_4.ipc] = (xx - flvar_3.qfacd) * sinph + yy * cosph;
	    zskp[invar_4.ipc] = (-xx + flvar_3.qfacd) * cicp + yy * cisp + zz 
		    * sini;
	    if (nspot == 0) {
		goto L126;
	    }
	    spot_(&atmmessages_1.komp, &nspot, &sinth, &costh, &sinfi, &cosfi,
		     &temf);
	    if (temf == 1.) {
		goto L126;
	    }
	    yskr = yskp[invar_4.ipc];
	    zskr = zskp[invar_4.ipc];
	    stp = twopi / (doublereal) kstp;
	    d__2 = twopi;
	    d__1 = stp;
	    for (ang = stp; d__1 < 0 ? ang >= d__2 : ang <= d__2; ang += d__1)
		     {
		++invar_4.ipc;
		yskp[invar_4.ipc] = yskr + sin(ang) * cirf;
		zskp[invar_4.ipc] = zskr + cos(ang) * cirf;
/* L189: */
	    }
	    goto L126;
L127:
	    if (inprof_1.mpage != 3) {
		goto L126;
	    }
	    if (*ifphn == 1) {
		goto L126;
	    }
L861:
	    vflump = vfvuff * r__ * comp * costh;
	    vcks = v * vfvuff;
	    vks = vcks + voc;
	    flpro_1.vksf = vks;
	    dvdr = vcks / r__;
	    dvdth = vcks / tanth;
	    dvdfib = vfvuff * r__ * comp * (sinfi * ylos + cosfi * xlos);
	    flpro_1.difp = dif * flpro_1.deldel * flpro_1.renfsq;
	    if (atmmessages_1.komp == 2) {
		goto L452;
	    }
	    flpro_1.binc = binc1;
	    flpro_1.binw = prof2_4.binw1;
	    i__3 = nfm1;
	    for (ifn = -nfm1; ifn <= i__3; ifn += 2) {
		dthf = (doublereal) ifn * r2nfdt;
		snthl = costh * dthf;
		zz = r__ * (costh - sinth * dthf);
		dvdfi = dvdfib * (sinth + costh * dthf);
		i__4 = nfm1;
		for (jfn = -nfm1; jfn <= i__4; jfn += 2) {
		    if (nf == 1) {
			goto L1247;
		    }
		    dfif = (doublereal) jfn * r2nfdf * delfi;
		    dlr = 0.;
		    xx = cmppd + compp * r__ * snthl * (cosfi - sinfi * dfif);
		    yy = r__ * compp * snthl * (sinfi + cosfi * dfif);
		    ysky = (xx - cmpd) * sinph + yy * cosph;
		    zsky = (cmpd - xx) * cicp + yy * cisp + zz * sini;
		    rrho = sqrt(ysky * ysky + zsky * zsky);
		    if (rrho < rhho) {
			goto L1246;
		    }
		    dvdth = -vflump * ((cosfi - sinfi * dfif) * ylos - (sinfi 
			    + cosfi * dfif) * xlos);
		    flpro_1.vksf = vks + dvdr * dlr + dvdth * dthf + dvdfi * 
			    dfif;
L1247:
		    linpro_(&atmmessages_1.komp, &dvks1[1], &hbarw1[1], &tau1[
			    1], &emm1[1], &count1[1], &taug[1], &emmg[1], &
			    fbin1[1], &delv1[1]);
		    if (ipro_1.inmax > inprof_1.in1max) {
			inprof_1.in1max = ipro_1.inmax;
		    }
		    if (ipro_1.inmin < inprof_1.in1min) {
			inprof_1.in1min = ipro_1.inmin;
		    }
L1246:
		    ;
		}
/* L1245: */
	    }
	    goto L126;
L452:
	    flpro_1.binc = binc2;
	    flpro_1.binw = prof2_4.binw2;
	    i__3 = nfm1;
	    for (ifn = -nfm1; ifn <= i__3; ifn += 2) {
		dthf = (doublereal) ifn * r2nfdt;
		snthl = costh * dthf;
		zz = r__ * (costh - sinth * dthf);
		dvdfi = dvdfib * (sinth + costh * dthf);
		i__4 = nfm1;
		for (jfn = -nfm1; jfn <= i__4; jfn += 2) {
		    if (nf == 1) {
			goto L1447;
		    }
		    dfif = (doublereal) jfn * r2nfdf * delfi;
		    dvdth = -vflump * ((cosfi - sinfi * dfif) * ylos - (sinfi 
			    + cosfi * dfif) * xlos);
		    dlr = 0.;
		    xx = cmppd + compp * r__ * snthl * (cosfi - sinfi * dfif);
		    yy = r__ * compp * snthl * (sinfi + cosfi * dfif);
		    ysky = (xx - cmpd) * sinph + yy * cosph;
		    zsky = (cmpd - xx) * cicp + yy * cisp + zz * sini;
		    rrho = sqrt(ysky * ysky + zsky * zsky);
		    if (rrho < rhho) {
			goto L1446;
		    }
		    flpro_1.vksf = vks + dvdr * dlr + dvdth * dthf + dvdfi * 
			    dfif;
L1447:
		    linpro_(&atmmessages_1.komp, &dvks2[1], &hbarw2[1], &tau2[
			    1], &emm2[1], &count2[1], &taug[1], &emmg[1], &
			    fbin2[1], &delv2[1]);
		    if (ipro_1.inmax > inprof_1.in2max) {
			inprof_1.in2max = ipro_1.inmax;
		    }
		    if (ipro_1.inmin < inprof_1.in2min) {
			inprof_1.in2min = ipro_1.inmin;
		    }
L1446:
		    ;
		}
/* L1445: */
	    }
L126:
	    ;
	}
	somj *= delfi;
	sumj *= delfi;
	som += somj;
/* L136: */
	sum += sumj;
    }
    if (inprof_1.mpage == 5) {
	return 0;
    }
    if (test <= .0625) {
	goto L120;
    }
    *somhot = som * delth;
    *sumhot = sum * delth;
    goto L121;
L120:
    *sumkul = sum * delth;
    *somkul = som * delth;
L121:
    if (*ifphn == 1) {
	return 0;
    }
    if (inprof_1.mpage != 3) {
	return 0;
    }
    inprof_1.in1min -= marm1;
    inprof_1.in1max += marp1;
    inprof_1.in2min -= marm2;
    inprof_1.in2max += marp2;
    if (inprof_1.nl1 == 0) {
	goto L3115;
    }
    i__1 = inprof_1.in1max;
    for (i__ = inprof_1.in1min; i__ <= i__1; ++i__) {
	fbin1[i__] = 1. - fbin1[i__] / *sumhot;
	if (count1[i__] == 0.) {
	    goto L2918;
	}
	delv1[i__] /= count1[i__];
	goto L2919;
L2918:
	delv1[i__] = prof2_4.binw1 * ((doublereal) i__ - binc1);
L2919:
	vdc = delv1[i__] / prof2_4.clight;
	vfc = sqrt((vdc + 1.) / (1. - vdc));
	delwl1[i__] = *wl * (vfc - 1.);
	wl1[i__] = *wl * vfc;
	resf1[i__] = (prof2_4.sl1 * delwl1[i__] + prof2_4.sc1) * fbin1[i__];
/* L2912: */
    }
L3115:
    if (inprof_1.nl2 == 0) {
	return 0;
    }
    i__1 = inprof_1.in2max;
    for (i__ = inprof_1.in2min; i__ <= i__1; ++i__) {
	fbin2[i__] = 1. - fbin2[i__] / *sumkul;
	if (count2[i__] == 0.) {
	    goto L2917;
	}
	delv2[i__] /= count2[i__];
	goto L2920;
L2917:
	delv2[i__] = prof2_4.binw2 * ((doublereal) i__ - binc2);
L2920:
	vdc = delv2[i__] / prof2_4.clight;
	vfc = sqrt((vdc + 1.) / (1. - vdc));
	delwl2[i__] = *wl * (vfc - 1.);
	wl2[i__] = *wl * vfc;
	resf2[i__] = (prof2_4.sl2 * delwl2[i__] + prof2_4.sc2) * fbin2[i__];
/* L2914: */
    }
    return 0;
} /* light_ */

/* Subroutine */ int linpro_(integer *komp, doublereal *dvks, doublereal *
	hbarw, doublereal *tau, doublereal *emm, doublereal *count, 
	doublereal *taug, doublereal *emmg, doublereal *fbin, doublereal *
	delv)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer i__, id;
    static doublereal fr1, fr2;
    static integer ind, iln;
    static doublereal vks1, vks2;
    static integer indm, indp;
    static doublereal vksb, vksg, vksm, vksp;
    static integer idmax;

/*  Version of November 3, 2000 */
    /* Parameter adjustments */
    --delv;
    --fbin;
    --emmg;
    --taug;
    --count;
    --emm;
    --tau;
    --hbarw;
    --dvks;

    /* Function Body */
    ipro_2.inmin = 300000;
    ipro_2.inmax = 0;

/*  The 83 loop pre-computes the limiting bin numbers, encompassing all lines */

    i__1 = ipro_2.nl;
    for (iln = 1; iln <= i__1; ++iln) {
	if (spots_3.lspot[*komp + (iln << 1) - 3] == 0) {
	    goto L83;
	}
	vksg = flpro_2.vks + dvks[iln];
	vksp = vksg + hbarw[iln];
	vksm = vksg - hbarw[iln];
	indp = (integer) (vksp / flpro_2.binw + flpro_2.binc);
	indm = (integer) (vksm / flpro_2.binw + flpro_2.binc);
	if (indm < ipro_2.inmin) {
	    ipro_2.inmin = indm;
	}
	if (indp > ipro_2.inmax) {
	    ipro_2.inmax = indp;
	}
L83:
	;
    }
    i__1 = ipro_2.inmax;
    for (i__ = ipro_2.inmin; i__ <= i__1; ++i__) {
	emmg[i__] = 0.;
/* L82: */
	taug[i__] = 0.;
    }

/*  The 84 loop puts fractional contributions into the two end bins */
/*    (first part, up to 28 continue) and puts full contributions */
/*    into the middle bins (the 26 loop). */

    i__1 = ipro_2.nl;
    for (iln = 1; iln <= i__1; ++iln) {
	if (spots_3.lspot[*komp + (iln << 1) - 3] == 0) {
	    goto L84;
	}
	vksg = flpro_2.vks + dvks[iln];
	vksp = vksg + hbarw[iln];
	vksm = vksg - hbarw[iln];
	indp = (integer) (vksp / flpro_2.binw + flpro_2.binc);
	indm = (integer) (vksm / flpro_2.binw + flpro_2.binc);
	vks1 = ((doublereal) (indm + 1) - flpro_2.binc) * flpro_2.binw;
	vks2 = ((doublereal) indp - flpro_2.binc) * flpro_2.binw;
	fr1 = (vks1 - vksm) / flpro_2.binw;
	fr2 = (vksp - vks2) / flpro_2.binw;
	taug[indm] += fr1 * tau[iln];
	emmg[indm] += fr1 * emm[iln];
	delv[indm] += fr1 * vksm;
	count[indm] += fr1;
	taug[indp] += fr2 * tau[iln];
	emmg[indp] += fr2 * emm[iln];
	delv[indp] += fr2 * vksp;
	count[indp] += fr2;
	if (indp != indm) {
	    goto L28;
	}
	taug[indp] -= tau[iln];
	emmg[indp] -= emm[iln];
	delv[indp] -= (vksm + vksp) * .5;
	count[indp] += -1.;
L28:
	ind = indm;
	idmax = indp - indm - 1;
	if (idmax <= 0) {
	    goto L84;
	}
	i__2 = idmax;
	for (id = 1; id <= i__2; ++id) {
	    ++ind;
	    vksb = ((doublereal) ind - flpro_2.binc) * flpro_2.binw;
	    taug[ind] += tau[iln];
	    emmg[ind] += emm[iln];
	    delv[ind] += vksb;
	    count[ind] += 1.;
/* L26: */
	}
L84:
	;
    }

/*  The 85 loop collects the absorption and emission contributions to all */
/*     active bins, with the absorption lines summed via an optical thickness */
/*     treatment and the emission lines summed directly according to contributed */
/*     flux. The sign on emmg is negative because emmg is negative. */

    i__1 = ipro_2.inmax;
    for (i__ = ipro_2.inmin; i__ <= i__1; ++i__) {
/* L85: */
	fbin[i__] += (1. - exp(-taug[i__]) + emmg[i__]) * flpro_2.difp;
    }
    return 0;
} /* linpro_ */

/* Subroutine */ int lum_(doublereal *xlum, doublereal *x, doublereal *y, 
	doublereal *tpoll, integer *n, integer *n1, integer *komp, doublereal 
	*sbr, doublereal *rv, doublereal *rvq, doublereal *glump1, doublereal 
	*glump2, doublereal *glog1, doublereal *glog2, doublereal *grv1, 
	doublereal *grv2, integer *mmsave, doublereal *summ, doublereal *fr, 
	doublereal *sm, integer *ifat, doublereal *vol, doublereal *rm, 
	doublereal *om, doublereal *f, doublereal *d__, doublereal *snth, 
	integer *iband, doublereal *tloc1, doublereal *tloc2, doublereal *
	xinorm1, doublereal *xinorm2)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal r__;
    extern /* Subroutine */ int planckint_(doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal r1, di, em, en;
    static integer ip, mm, kr;
    static doublereal zd;
    static integer ix;
    static doublereal rl, xm, xl1, dif, cmp, omd, xld, smj, sum;
    static integer ipn1;
    static doublereal diff, cmpp, dfst, grav;
    extern /* Subroutine */ int atmx_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal volj, sumj, xint, delfi, glogg, delth, gplog, gravm, 
	    polin, omdum, tpole, sinth, summj, darkin, tlocal;
    extern /* Subroutine */ int ellone_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), nekmin_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal pollog, xinlog;

/*   Version of January 8, 2003 */
    /* Parameter adjustments */
    --xinorm2;
    --xinorm1;
    --tloc2;
    --tloc1;
    --snth;
    --fr;
    --mmsave;
    --grv2;
    --grv1;
    --glog2;
    --glog1;
    --glump2;
    --glump1;
    --rvq;
    --rv;

    /* Function Body */
    atmmessages_2.kompcom = *komp;
    tpole = *tpoll * 1e4;
    kr = 0;
    cmp = (doublereal) (*komp - 1);
    cmpp = (doublereal) (2 - *komp);
    gplog = cmpp * gpoles_1.gplog1 + cmp * gpoles_1.gplog2;
    if (*ifat == 0) {
	planckint_(&tpole, iband, &pollog, &polin);
    }
    if (*ifat != 0) {
	atmx_(&tpole, &gplog, iband, &pollog, &polin);
    }
    en = (doublereal) (*n);
    delth = 1.570796326794897 / en;
    sum = 0.;
    *summ = 0.;
    *sm = 0.;
    *vol = 0.;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ipn1 = i__ + *n1 * (*komp - 1);
	sinth = snth[ipn1];
	em = sinth * en * 1.3;
	mm = (integer) (em + 1.);
	xm = (doublereal) mm;
	delfi = 3.141592653589793 / xm;
	dfst = delfi * sinth;
	sumj = 0.;
	summj = 0.;
	smj = 0.;
	volj = 0.;
	i__2 = mm;
	for (j = 1; j <= i__2; ++j) {
	    ip = (*komp - 1) * (*n1 + 1) + i__;
	    ix = mmsave[ip] + j;
	    if (*komp == 1) {
		goto L39;
	    }
	    if (rvq[ix] == -1.) {
		goto L25;
	    }
	    r__ = rvq[ix];
	    goto L49;
L39:
	    if (rv[ix] == -1.) {
		goto L25;
	    }
	    r__ = rv[ix];
L49:
	    grav = cmpp * grv1[ix] + cmp * grv2[ix];
	    tlocal = tpole * sqrt(sqrt(grav));
	    if (*komp == 1) {
		tloc1[ix] = tlocal;
	    }
	    if (*komp == 2) {
		tloc2[ix] = tlocal;
	    }
	    glogg = cmpp * glog1[ix] + cmp * glog2[ix];
	    if (*ifat == 0) {
		planckint_(&tlocal, iband, &xinlog, &xint);
	    }
	    if (*ifat != 0) {
		atmx_(&tlocal, &glogg, iband, &xinlog, &xint);
	    }
	    if (*komp == 1) {
		xinorm1[ix] = xint;
	    }
	    if (*komp == 2) {
		xinorm2[ix] = xint;
	    }
	    gravm = xint / polin;
	    di = cmpp * glump1[ix] + cmp * glump2[ix];
	    dif = di * gravm;
	    diff = di * grav;
	    smj += di;
	    sumj += dif;
	    summj += diff;
	    volj += r__ * r__ * r__ * fr[ix];
	    goto L26;
L25:
	    kr = 1;
L26:
	    ;
	}
	smj *= delfi;
	sumj *= delfi;
	summj *= delfi;
	*sm += smj;
	sum += sumj;
	*summ += summj;
/* L36: */
	*vol += volj * dfst;
    }
    darkin = (1. - *x / 3.) * 3.141592653589793;
    if (invar_5.ld == 2) {
	darkin += *y * .6981317;
    }
    if (invar_5.ld == 3) {
	darkin -= *y * .6283185;
    }
    *sm = *sm * delth * 4.;
    sum = sum * delth * 4.;
    *summ = *summ * delth * 4.;
    *sbr = *xlum / (sum * darkin);
    *vol = *vol * 1.3333333333333 * delth;
    if (kr == 0) {
	return 0;
    }
    ellone_(f, d__, rm, &xl1, &omd, &xld, &omdum);
    nekmin_(rm, om, &xl1, &zd);
    if (*komp == 2) {
	xl1 = *d__ - xl1;
    }
    r1 = cmpp * radi_1.r1h + cmp * radi_1.r1c;
    rl = cmpp * radi_1.rlh + cmp * radi_1.rlc;
    *vol += xl1 * 1.047198 * r1 * rl;
    return 0;
} /* lum_ */

/* Subroutine */ int lump_(doublereal *grx, doublereal *gry, doublereal *grz, 
	doublereal *grxq, doublereal *gryq, doublereal *grzq, doublereal *
	slump1, doublereal *slump2, integer *mmsave, doublereal *alb, 
	doublereal *tpoll, doublereal *sbr, integer *n1, integer *n2, integer 
	*komp, integer *ifat, doublereal *fr, doublereal *snth, doublereal *
	tld, doublereal *glump1, doublereal *glump2, doublereal *xx1, 
	doublereal *xx2, doublereal *yy1, doublereal *yy2, doublereal *zz1, 
	doublereal *zz2, doublereal *xbol, doublereal *ybol, doublereal *grv1,
	 doublereal *grv2, doublereal *sbr1b, doublereal *sbr2b, doublereal *
	rf, doublereal *rfo, doublereal *gmag1, doublereal *gmag2, doublereal 
	*glog1, doublereal *glog2, doublereal *dint, integer *iband)
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4;

    /* Builtin functions */
    double sqrt(doublereal), log(doublereal);

    /* Local variables */
    static integer i__, j, n;
    extern /* Subroutine */ int planckint_(doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal em, en;
    static integer iq;
    static doublereal pi;
    static integer is, no, mm, ip;
    static doublereal dx;
    static integer ix, iy;
    static doublereal dy, dz, x1c, x2c, y1c, y2c, z1c, gx2;
    static integer ix1, ix2;
    static doublereal gy2, gz2, z2c, gx1, gy1, gz1, cmp, pih;
    static integer nod;
    static doublereal eno, emo;
    static integer mmo, ipo;
    static doublereal grv;
    static integer ixo, iyo;
    static doublereal sum, xmo;
    static integer ipn1;
    static doublereal upd1, upd2, rtl1, rtl2, dmag;
    static integer jofi, mmod;
    static doublereal cmpp, comp;
    static integer ioth;
    static doublereal cnst;
    static integer ipno;
    extern /* Subroutine */ int atmx_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal pint;
    static integer jofu;
    static doublereal dsum, tnew, xint, dgam1, dgam2, csgm1, csgm2, glogg, 
	    gplog, compp, tpole, sinth;
    static integer ioths;
    static doublereal dlrsq, csnum2, csnum1, delfio, deltho, grrefl, pollog, 
	    sintho, xintlog;

/*   Version of January 8, 2003 */
    /* Parameter adjustments */
    --glog2;
    --glog1;
    --gmag2;
    --gmag1;
    --rfo;
    --rf;
    --grv2;
    --grv1;
    --zz2;
    --zz1;
    --yy2;
    --yy1;
    --xx2;
    --xx1;
    --glump2;
    --glump1;
    --tld;
    --snth;
    --fr;
    --mmsave;
    --slump2;
    --slump1;
    --grzq;
    --gryq;
    --grxq;
    --grz;
    --gry;
    --grx;

    /* Function Body */
    atmmessages_2.kompcom = *komp;
    iq = (*komp - 1) * (*n1 + 1);
    is = 0;
    if (*komp == 2) {
	is = mmsave[iq];
    }
    pi = 3.141592653589793;
    pih = pi * .5;
    tpole = *tpoll * 1e4;
    cmp = (doublereal) (*komp - 1);
    cmpp = (doublereal) (2 - *komp);
    gplog = cmpp * gpoles_1.gplog1 + cmp * gpoles_1.gplog2;
    if (*ifat == 0) {
	planckint_(&tpole, iband, &pollog, &pint);
    }
    if (*ifat != 0) {
	atmx_(&tpole, &gplog, iband, &pollog, &pint);
    }
    compp = (doublereal) ((*komp << 1) - 3);
    comp = -compp;
    n = (2 - *komp) * *n1 + (*komp - 1) * *n2;
    no = (2 - *komp) * *n2 + (*komp - 1) * *n1;
    nod = no << 1;
    en = (doublereal) n;
    eno = (doublereal) no;
    deltho = pih / eno;
    cnst = *alb * deltho * *sbr2b / (*dint * *sbr1b);
    if (*komp == 2) {
	cnst = *alb * deltho * *sbr1b / (*dint * *sbr2b);
    }
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ipn1 = i__ + *n1 * (*komp - 1);
	sinth = snth[ipn1];
	em = sinth * en * 1.3;
	mm = (integer) (em + 1.);
	ip = (*komp - 1) * (*n1 + 1) + i__;
	iy = mmsave[ip];
	i__2 = mm;
	for (j = 1; j <= i__2; ++j) {
	    ix = iy + j;
	    sum = 0.;
	    if (fr[ix] == 0.) {
		goto L193;
	    }
	    i__3 = nod;
	    for (ioth = 1; ioth <= i__3; ++ioth) {
		ioths = ioth;
		if (ioth > no) {
		    ioths = nod - ioth + 1;
		}
		ipno = ioths + *n1 * (2 - *komp);
		sintho = snth[ipno];
		emo = sintho * eno * 1.3;
		mmo = (integer) (emo + 1.);
		mmod = mmo << 1;
		ipo = (2 - *komp) * (*n1 + 1) + ioths;
		iyo = mmsave[ipo];
		xmo = (doublereal) mmo;
		delfio = pi / xmo;
		i__4 = mmod;
		for (jofi = 1; jofi <= i__4; ++jofi) {
		    jofu = jofi;
		    if (jofi > mmo) {
			jofu = mmod - jofi + 1;
		    }
		    ixo = iyo + jofu;
		    ix1 = ix;
		    ix2 = ixo;
		    if (*komp == 1) {
			goto L200;
		    }
		    if (glump1[ixo] == 0.) {
			goto L184;
		    }
		    ix1 = ixo;
		    ix2 = ix;
		    goto L201;
L200:
		    if (glump2[ixo] == 0.) {
			goto L179;
		    }
L201:
		    rtl1 = 1.;
		    rtl2 = 1.;
		    upd1 = 1.;
		    upd2 = 1.;
		    if (*komp == 2) {
			goto L22;
		    }
		    if (jofi > mmo) {
			rtl2 = -1.;
		    }
		    if (ioth > no) {
			upd2 = -1.;
		    }
		    goto L23;
L22:
		    if (jofi > mmo) {
			rtl1 = -1.;
		    }
		    if (ioth > no) {
			upd1 = -1.;
		    }
L23:
		    gx2 = grxq[ix2];
		    gy2 = gryq[ix2] * rtl2;
		    gz2 = grzq[ix2] * upd2;
		    x1c = xx1[ix1];
		    x2c = xx2[ix2];
		    y1c = yy1[ix1] * rtl1;
		    y2c = yy2[ix2] * rtl2;
		    z1c = zz1[ix1] * upd1;
		    z2c = zz2[ix2] * upd2;
		    dx = (x2c - x1c) * comp;
		    dy = (y2c - y1c) * comp;
		    dz = (z2c - z1c) * comp;
		    dlrsq = dx * dx + dy * dy + dz * dz;
		    csnum2 = (dx * gx2 + dy * gy2 + dz * gz2) * compp;
		    if (csnum2 >= 0.) {
			goto L190;
		    }
		    gx1 = grx[ix1];
		    gy1 = gry[ix1] * rtl1;
		    gz1 = grz[ix1] * upd1;
		    csnum1 = (dx * gx1 + dy * gy1 + dz * gz1) * comp;
		    if (csnum1 >= 0.) {
			goto L190;
		    }
		    dmag = sqrt(dlrsq);
		    csgm1 = -csnum1 / (dmag * gmag1[ix1]);
		    csgm2 = -csnum2 / (dmag * gmag2[ix2]);
		    if (*komp == 2) {
			goto L181;
		    }
		    dgam2 = 1. - *xbol + *xbol * csgm2;
		    if (invar_4.ld != 2) {
			goto L179;
		    }
		    if (csgm2 == 0.) {
			goto L179;
		    }
		    dgam2 -= *ybol * csgm2 * log(csgm2);
		    goto L147;
L179:
		    if (invar_4.ld == 3) {
			dgam2 -= *ybol * (1. - sqrt(csgm2));
		    }
L147:
		    if (dgam2 < 0.) {
			dgam2 = 0.;
		    }
		    dsum = grv2[ixo] * glump2[ixo] * rfo[ixo] * csgm1 * csgm2 
			    * dgam2 / dlrsq;
		    goto L182;
L181:
		    dgam1 = 1. - *xbol + *xbol * csgm1;
		    if (invar_4.ld != 2) {
			goto L184;
		    }
		    if (csgm1 == 0.) {
			goto L184;
		    }
		    dgam1 -= *ybol * csgm1 * log(csgm1);
		    goto L148;
L184:
		    if (invar_4.ld == 3) {
			dgam1 -= *ybol * (1. - sqrt(csgm1));
		    }
L148:
		    if (dgam1 < 0.) {
			dgam1 = 0.;
		    }
		    dsum = grv1[ixo] * glump1[ixo] * rfo[ixo] * csgm2 * csgm1 
			    * dgam1 / dlrsq;
L182:
		    sum += dsum * delfio;
L190:
		    ;
		}
	    }
	    rf[ix] = cnst * sum / (cmpp * grv1[ix] + cmp * grv2[ix]) + 1.;
L193:
	    ;
	}
/* L191: */
    }
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ipn1 = i__ + *n1 * (*komp - 1);
	sinth = snth[ipn1];
	em = sinth * en * 1.3;
	mm = (integer) (em + 1.);
	ip = (*komp - 1) * (*n1 + 1) + i__;
	iy = mmsave[ip];
	i__2 = mm;
	for (j = 1; j <= i__2; ++j) {
	    ++is;
	    ix = iy + j;
	    if (fr[ix] == 0.) {
		goto L8;
	    }
	    glogg = cmpp * glog1[ix] + cmp * glog2[ix];
	    grv = cmpp * grv1[ix] + cmp * grv2[ix];
	    tnew = tpole * sqrt(sqrt(grv * rf[ix]));
	    tld[is] = tnew;
	    if (*ifat == 0) {
		planckint_(&tnew, iband, &xintlog, &xint);
	    }
	    if (*ifat != 0) {
		atmx_(&tnew, &glogg, iband, &xintlog, &xint);
	    }
	    grrefl = xint / pint;
	    if (*komp == 1) {
		goto L77;
	    }
	    slump2[ix] = glump2[ix] * grrefl * *sbr;
	    goto L8;
L77:
	    slump1[ix] = glump1[ix] * grrefl * *sbr;
L8:
	    ;
	}
    }
    return 0;
} /* lump_ */

/* Subroutine */ int mlrg_(doublereal *a, doublereal *p, doublereal *q, 
	doublereal *r1, doublereal *r2, doublereal *t1, doublereal *t2, 
	doublereal *sm1, doublereal *sm2, doublereal *sr1, doublereal *sr2, 
	doublereal *bolm1, doublereal *bolm2, doublereal *xlg1, doublereal *
	xlg2)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double d_lg10(doublereal *);

    /* Local variables */
    static doublereal gmnomsun, gmr, bol1, bol2, tsun, sunmb, sunrad;

/*  Version of January 16, 2002 */

/*  This subroutine computes absolute dimensions and other quantities */
/*  for the stars of a binary star system. */
/*  a = orbital semi-major axis, the sum of the two a's for the two */
/*  stars. The unit is a solar radius. */
/*  r1,r2 = relative mean (equivalent sphere) radii for stars 1 and 2. Th */
/*  unit is the orbital semimajor axis. */
/*  p = orbit period in days. */
/*  q = mass ratio, m2/m1. */
/*  t1,t2= flux-weighted mean surface temperatures for stars 1 and 2,in K */
/*  sm1,sm2= masses of stars 1 and 2 in solar units. */
/*  sr1,sr2= mean radii of stars 1 and 2 in solar units. */
/*  bolm1, bolm2= absolute bolometric magnitudes of stars 1, 2. */
/*  xlg1, xlg2= log (base 10) of mean surface acceleration (effective gra */
/*  for stars 1 and 2. */

/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */

/*     PHOEBE substitution: */

/*     G=6.668d-8 */
/*     tsun=5800.d0 */
/*     rsunau=214.8d0 */
/*     sunmas=1.991d33 */
/*     sunrad=6.960d10 */
/*     sunmb=4.77d0 */
/*     yrsid=365.2564d0 */
    tsun = 5772.;
/*     rsunau=215.044520d0 */
    gmnomsun = 1.3271244e26f;
    sunrad = 6.957e10;
    sunmb = 4.74;
/*     yrsid=365.256363d0 */
/* Computing 2nd power */
    d__1 = sunrad;
    gmr = gmnomsun / (d__1 * d__1);
    *sr1 = *r1 * *a;
    *sr2 = *r2 * *a;
/*     tmass=(a/rsunau)**3/(p/yrsid)**2 */
/*     sm1=tmass/(1.d0+q) */
/*     sm2=tmass*q/(1.d0+q) */
/* Computing 3rd power */
    d__1 = *a * sunrad;
/* Computing 2nd power */
    d__2 = *p * 86400.;
    *sm1 = d__1 * (d__1 * d__1) / (d__2 * d__2) * 39.47841760435743f / (*q + 
	    1.) / gmnomsun;
/* Computing 3rd power */
    d__1 = *a * sunrad;
/* Computing 2nd power */
    d__2 = *p * 86400.;
    *sm2 = d__1 * (d__1 * d__1) / (d__2 * d__2) * 39.47841760435743f * *q / (*
	    q + 1.) / gmnomsun;
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/* Computing 4th power */
    d__1 = *t1 / tsun, d__1 *= d__1;
/* Computing 2nd power */
    d__2 = *sr1;
    bol1 = d__1 * d__1 * (d__2 * d__2);
/* Computing 4th power */
    d__1 = *t2 / tsun, d__1 *= d__1;
/* Computing 2nd power */
    d__2 = *sr2;
    bol2 = d__1 * d__1 * (d__2 * d__2);
    *bolm1 = sunmb - d_lg10(&bol1) * 2.5;
    *bolm2 = sunmb - d_lg10(&bol2) * 2.5;
/* Computing 2nd power */
    d__2 = *sr1;
    d__1 = gmr * *sm1 / (d__2 * d__2);
    *xlg1 = d_lg10(&d__1);
/* Computing 2nd power */
    d__2 = *sr2;
    d__1 = gmr * *sm2 / (d__2 * d__2);
    *xlg2 = d_lg10(&d__1);
    return 0;
} /* mlrg_ */

/* Subroutine */ int modlog_(doublereal *rv, doublereal *grx, doublereal *gry,
	 doublereal *grz, doublereal *rvq, doublereal *grxq, doublereal *gryq,
	 doublereal *grzq, integer *mmsave, doublereal *fr1, doublereal *fr2, 
	doublereal *hld, doublereal *rm, doublereal *poth, doublereal *potc, 
	doublereal *gr1, doublereal *gr2, doublereal *alb1, doublereal *alb2, 
	integer *n1, integer *n2, doublereal *f1, doublereal *f2, integer *
	mod, doublereal *xincl, doublereal *the, integer *mode, doublereal *
	snth, doublereal *csth, doublereal *snfi, doublereal *csfi, 
	doublereal *grv1, doublereal *grv2, doublereal *xx1, doublereal *yy1, 
	doublereal *zz1, doublereal *xx2, doublereal *yy2, doublereal *zz2, 
	doublereal *glump1, doublereal *glump2, doublereal *csbt1, doublereal 
	*csbt2, doublereal *gmag1, doublereal *gmag2, doublereal *glog1, 
	doublereal *glog2, doublereal *tloc1, doublereal *tloc2, doublereal *
	xinorm1, doublereal *xinorm2)
{
    /* Format strings */
    static char fmt_95[] = "(\002 WARNING: ALTHOUGH COMPONENT 2 DOES NOT EXC"
	    "EED ITS LIMITING LOBE AT THE END OF ECLIPSE, IT DOES EXCEED THE "
	    "LOBE AT PERIASTRON\002)";
    static char fmt_99[] = "(\002 SPECIFIED ECLIPSE DURATION INCONSISTENT WI"
	    "TH OTHER PARAMETERS\002)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sin(doublereal), sqrt(doublereal), tan(doublereal), atan(
	    doublereal), cos(doublereal);
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Local variables */
    static integer ib;
    static doublereal ra;
    static integer lx[2], mx[2], md4, md5;
    static doublereal ds1, ds2, om1, om2, xl1, xl2, tr0, xm0, xm1, xm2, tr1, 
	    tr2, vs1, vs2, doc, ans[2], smd, xla, dum, drr[4], res[2], xmc, 
	    dxm, xld, omp, rmr, po2c, omo1, omo2, dtr1, dtr2, htr0, tre1, 
	    tre2, trr1, trr2, efcc, ecan, dthe;
    extern /* Subroutine */ int dura_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal htrc, tric, xmic, ther, dvol, trsc, xmsc, dumm, vthe, 
	    potr, ecan0, ecan1, ecan2, po1cr, po2cr, deltr;
    extern /* Subroutine */ int dminv_(doublereal *, integer *, doublereal *, 
	    integer *, integer *);
    static doublereal summd, ddmdn1, ddmdn2, econic, econsc;
    extern /* Subroutine */ int dgmprd_(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *), ellone_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), conjph_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), kepler_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal dxmtol;
    extern /* Subroutine */ int volume_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *);
    static doublereal voltol;

    /* Fortran I/O blocks */
    static cilist io___1645 = { 0, 16, 0, fmt_99, 0 };
    static cilist io___1649 = { 0, 16, 0, fmt_95, 0 };


/*    Version of December 18, 2003 */
    /* Parameter adjustments */
    --xinorm2;
    --xinorm1;
    --tloc2;
    --tloc1;
    --glog2;
    --glog1;
    --gmag2;
    --gmag1;
    --csbt2;
    --csbt1;
    --glump2;
    --glump1;
    --zz2;
    --yy2;
    --xx2;
    --zz1;
    --yy1;
    --xx1;
    --grv2;
    --grv1;
    --csfi;
    --snfi;
    --csth;
    --snth;
    --hld;
    --fr2;
    --fr1;
    --mmsave;
    --grzq;
    --gryq;
    --grxq;
    --rvq;
    --grz;
    --gry;
    --grx;
    --rv;

    /* Function Body */
/* L95: */
/* L99: */
    ardot_1.perr = flvar_1.perr0 + ardot_1.dperdt * (ardot_1.hjd - 
	    ardot_1.hjd0);
    flvar_1.dp = 1. - eccen_1.e;
/* Computing 2nd power */
    i__1 = *mode - 2;
    *mod = i__1 * i__1;
    if (*mode == 1) {
	*gr2 = *gr1;
    }
    if (*mode == 1) {
	*alb2 = *alb1;
    }
    if (*mod == 1) {
	*potc = *poth;
    }
/* Computing 2nd power */
    i__1 = *mode - 5;
    md4 = i__1 * i__1;
/* Computing 2nd power */
    i__1 = (*mode << 1) - 11;
    md5 = i__1 * i__1;
    ellone_(f1, &flvar_1.dp, rm, &xl1, &po1cr, &xl2, &omo1);
    setest_1.sefac = .8712;
    doc = (po1cr - *poth) / (po1cr - omo1);
    if (doc > 0.) {
	setest_1.sefac = doc * .201 * doc - doc * .386 + .8712;
    }
    rmr = 1. / *rm;
    ellone_(f2, &flvar_1.dp, &rmr, &xl1, &po2c, &xl2, &omo2);
    po2cr = *rm * po2c + (1. - *rm) * .5;
    if (md4 == 1) {
	*poth = po1cr;
    }
    if (md5 == 1) {
	*potc = po2cr;
    }
    kfac_1.kff1 = 0;
    kfac_1.kff2 = 0;
    if (*poth < po1cr) {
	kfac_1.kff1 = 1;
    }
    if (*potc < po2cr) {
	kfac_1.kff2 = 1;
    }
    kfac_1.kfo1 = 0;
    kfac_1.kfo2 = 0;
    if (eccen_1.e != 0.) {
	goto L100;
    }
    if (*f1 != 1.) {
	goto L105;
    }
    if (*poth < omo1) {
	kfac_1.kfo1 = 1;
    }
L105:
    if (*f2 != 1.) {
	goto L100;
    }
    if (*potc < omo1) {
	kfac_1.kfo2 = 1;
    }
L100:
    eccen_1.sini = sin(*xincl * .017453292519943);
/*     the magical number below is 2*pi*RSun/86400, and it's wrong. */
/* ~       VF=50.61455d0/PERIOD */
    eccen_1.vf = 50.592731692186 / eccen_1.period;
    eccen_1.vfac = eccen_1.vf * eccen_1.a;
    eccen_1.vgam = eccen_1.vga * flvar_1.vunit / eccen_1.vfac;
    flvar_1.vfvu = eccen_1.vfac;
    eccen_1.ifc = 2;
    if (eccen_1.e != 0.) {
	goto L60;
    }
    ardot_1.perr = 1.570796326794897;
    eccen_1.ifc = 1;
L60:
    flvar_1.trc = 1.570796326794897 - ardot_1.perr;
L39:
    if (flvar_1.trc < 0.) {
	flvar_1.trc += 6.283185307179586;
    }
    if (flvar_1.trc < 0.) {
	goto L39;
    }
L40:
    if (flvar_1.trc >= 6.283185307179586) {
	flvar_1.trc += -6.283185307179586;
    }
    if (flvar_1.trc >= 6.283185307179586) {
	goto L40;
    }
    htrc = flvar_1.trc * .5;
    if ((d__1 = 1.570796326794897 - htrc, abs(d__1)) < 7e-6) {
	goto L101;
    }
    if ((d__1 = 4.71238898038469 - htrc, abs(d__1)) < 7e-6) {
	goto L101;
    }
    ecan = atan(sqrt((1. - eccen_1.e) / (eccen_1.e + 1.)) * tan(htrc)) * 2.;
    goto L103;
L101:
    ecan = 3.141592653589793;
L103:
    xmc = ecan - eccen_1.e * sin(ecan);
    if (xmc < 0.) {
	xmc += 6.283185307179586;
    }
    flvar_1.phper = 1. - xmc / 6.283185307179586;
    conjph_(&eccen_1.e, &ardot_1.perr, &flvar_1.pshift, &trsc, &tric, &econsc,
	     &econic, &xmsc, &xmic, &flvar_1.pconsc, &flvar_1.pconic);
L38:
    if (flvar_1.pconsc >= 1.) {
	flvar_1.pconsc += -1.;
    }
    if (flvar_1.pconsc >= 1.) {
	goto L38;
    }
L41:
    if (flvar_1.pconsc < 0.) {
	flvar_1.pconsc += 1.;
    }
    if (flvar_1.pconsc < 0.) {
	goto L41;
    }
L68:
    if (flvar_1.pconic >= 1.) {
	flvar_1.pconic += -1.;
    }
    if (flvar_1.pconic >= 1.) {
	goto L68;
    }
L71:
    if (flvar_1.pconic < 0.) {
	flvar_1.pconic += 1.;
    }
    if (flvar_1.pconic < 0.) {
	goto L71;
    }
    flvar_1.phperi = flvar_1.phper + flvar_1.pconsc;
    flvar_1.ef = 1. - eccen_1.e * eccen_1.e;
    flvar_1.efc = sqrt(flvar_1.ef);
    flvar_1.ecos = eccen_1.e * cos(ardot_1.perr);
    if (*mode != -1) {
	return 0;
    }
    if (invar_1.kh == 17) {
	goto L241;
    }
/* Computing 2nd power */
    i__1 = invar_1.kh - 12;
    if (i__1 * i__1 == 1) {
	goto L241;
    }
/* Computing 2nd power */
    i__1 = invar_1.kh - 12;
    if (i__1 * i__1 == 4) {
	goto L241;
    }
/* Computing 2nd power */
    i__1 = invar_1.kh - 11;
    if (i__1 * i__1 <= 1) {
	goto L241;
    }
/* Computing 2nd power */
    i__1 = (invar_1.kh << 1) - 41;
    if (i__1 * i__1 == 81) {
	goto L241;
    }
    return 0;
L241:
    efcc = sqrt((1. - eccen_1.e) / (eccen_1.e + 1.));
    ther = *the * 6.283185307179586;
    deltr = .001;
    dtr1 = 0.;
    dtr2 = 0.;
    voltol = 5e-6;
    dxmtol = 5e-6;
    tr0 = 1.570796326794897 - ardot_1.perr;
    htr0 = tr0 * .5;
    if (1.570796326794897 - abs(htr0) < 7e-6) {
	goto L201;
    }
    if (4.71238898038469 - abs(htr0) < 7e-6) {
	goto L201;
    }
    ecan0 = atan(sqrt((1. - eccen_1.e) / (eccen_1.e + 1.)) * tan(htr0)) * 2.;
    goto L203;
L201:
    ecan0 = 3.141592653589793;
L203:
    xm0 = ecan0 - eccen_1.e * sin(ecan0);
    xm1 = xm0 - ther * (1. - eccen_1.e * .2);
    xm2 = xm0 + ther * (1. - eccen_1.e * .2);
    kepler_(&xm1, &eccen_1.e, &dum, &trr1);
    kepler_(&xm2, &eccen_1.e, &dum, &trr2);
L160:
    trr1 += dtr1;
    trr2 += dtr2;
    for (ib = 1; ib <= 3; ++ib) {
	tr1 = trr1;
	tr2 = trr2;
	if (ib == 2) {
	    tr1 = trr1 + deltr;
	}
	if (ib == 3) {
	    tr2 = trr2 + deltr;
	}
	if (tr1 > tr0) {
	    tr0 += 6.283185307179586;
	}
	if (tr0 > tr2) {
	    tr2 += 6.283185307179586;
	}
	ds1 = flvar_1.ef / (eccen_1.e * cos(tr1) + 1.);
	ds2 = flvar_1.ef / (eccen_1.e * cos(tr2) + 1.);
	tre1 = (tr0 - tr1) / 6.283185307179586;
	tre2 = (tr2 - tr0) / 6.283185307179586;
	dura_(f2, xincl, rm, &ds1, &tre1, &potr, &ra);
	volume_(&vs1, rm, &potr, &ds1, f2, n2, n1, &c__2, &rv[1], &grx[1], &
		gry[1], &grz[1], &rvq[1], &grxq[1], &gryq[1], &grzq[1], &
		mmsave[1], &fr1[1], &fr2[1], &hld[1], &snth[1], &csth[1], &
		snfi[1], &csfi[1], &summd, &smd, &grv1[1], &grv2[1], &xx1[1], 
		&yy1[1], &zz1[1], &xx2[1], &yy2[1], &zz2[1], &csbt1[1], &
		csbt2[1], &glump1[1], &glump2[1], &gmag1[1], &gmag2[1], &
		glog1[1], &glog2[1], gr1, &c__1, &tloc1[1], &tloc2[1], &
		xinorm1[1], &xinorm2[1]);
	dura_(f2, xincl, rm, &ds2, &tre2, &potr, &ra);
	volume_(&vs2, rm, &potr, &ds2, f2, n2, n1, &c__2, &rv[1], &grx[1], &
		gry[1], &grz[1], &rvq[1], &grxq[1], &gryq[1], &grzq[1], &
		mmsave[1], &fr1[1], &fr2[1], &hld[1], &snth[1], &csth[1], &
		snfi[1], &csfi[1], &summd, &smd, &grv1[1], &grv2[1], &xx1[1], 
		&yy1[1], &zz1[1], &xx2[1], &yy2[1], &zz2[1], &csbt1[1], &
		csbt2[1], &glump1[1], &glump2[1], &gmag1[1], &gmag2[1], &
		glog1[1], &glog2[1], gr2, &c__1, &tloc1[1], &tloc2[1], &
		xinorm1[1], &xinorm2[1]);
	if (ib != 1) {
	    goto L185;
	}
	ecan1 = atan(sqrt((1. - eccen_1.e) / (eccen_1.e + 1.)) * tan(tr1 * .5)
		) * 2.;
	ecan2 = atan(sqrt((1. - eccen_1.e) / (eccen_1.e + 1.)) * tan(tr2 * .5)
		) * 2.;
	*potc = potr;
	dthe = ds2;
	dvol = vs2 - vs1;
	xm1 = ecan1 - eccen_1.e * sin(ecan1);
	xm2 = ecan2 - eccen_1.e * sin(ecan2);
	if (xm1 < 0.) {
	    xm1 += 6.283185307179586;
	}
	if (xm2 < 0.) {
	    xm2 += 6.283185307179586;
	}
	dxm = xm2 - xm1 - ther * 2.;
/* Computing 2nd power */
	d__1 = cos(ecan1 * .5);
/* Computing 2nd power */
	d__2 = cos(tr1 * .5);
	ddmdn1 = -efcc * (1. - eccen_1.e * cos(ecan1)) * (d__1 * d__1) / (
		d__2 * d__2);
/* Computing 2nd power */
	d__1 = cos(ecan2 * .5);
/* Computing 2nd power */
	d__2 = cos(tr2 * .5);
	ddmdn2 = efcc * (1. - eccen_1.e * cos(ecan2)) * (d__1 * d__1) / (d__2 
		* d__2);
L185:
	if (ib != 2) {
	    goto L162;
	}
	drr[0] = (vs2 - vs1 - dvol) / deltr;
	drr[1] = ddmdn1;
L162:
	if (ib != 3) {
	    goto L161;
	}
	drr[2] = (vs2 - vs1 - dvol) / deltr;
	drr[3] = ddmdn2;
L161:
	;
    }
    res[0] = -dvol;
    res[1] = -dxm;
    dminv_(drr, &c__2, &dumm, lx, mx);
    dgmprd_(drr, res, ans, &c__2, &c__2, &c__1);
    dtr1 = ans[0];
    dtr2 = ans[1];
    if (abs(dtr1) > voltol) {
	goto L160;
    }
    if (abs(dtr2) > dxmtol) {
	goto L160;
    }
    *poth = 9999.99;
    rmr = 1. / *rm;
    ellone_(f2, &dthe, &rmr, &xla, &om1, &xl2, &om2);
    om1 = *rm * om1 + (1. - *rm) * .5;
    if (*potc < om1) {
	goto L22;
    }
    if (ra <= xla) {
	goto L28;
    }
L22:
    s_wsfe(&io___1645);
    e_wsfe();
    return 0;
L28:
    if (eccen_1.e != 0.) {
	volume_(&vthe, rm, potc, &dthe, f2, n2, n1, &c__2, &rv[1], &grx[1], &
		gry[1], &grz[1], &rvq[1], &grxq[1], &gryq[1], &grzq[1], &
		mmsave[1], &fr1[1], &fr2[1], &hld[1], &snth[1], &csth[1], &
		snfi[1], &csfi[1], &summd, &smd, &grv1[1], &grv2[1], &xx1[1], 
		&yy1[1], &zz1[1], &xx2[1], &yy2[1], &zz2[1], &csbt1[1], &
		csbt2[1], &glump1[1], &glump2[1], &gmag1[1], &gmag2[1], &
		glog1[1], &glog2[1], gr2, &c__1, &tloc1[1], &tloc2[1], &
		xinorm1[1], &xinorm2[1]);
    }
    if (eccen_1.e != 0.) {
	volume_(&vthe, rm, potc, &flvar_1.dp, f2, n2, n1, &c__2, &rv[1], &grx[
		1], &gry[1], &grz[1], &rvq[1], &grxq[1], &gryq[1], &grzq[1], &
		mmsave[1], &fr1[1], &fr2[1], &hld[1], &snth[1], &csth[1], &
		snfi[1], &csfi[1], &summd, &smd, &grv1[1], &grv2[1], &xx1[1], 
		&yy1[1], &zz1[1], &xx2[1], &yy2[1], &zz2[1], &csbt1[1], &
		csbt2[1], &glump1[1], &glump2[1], &gmag1[1], &gmag2[1], &
		glog1[1], &glog2[1], gr2, &c__2, &tloc1[1], &tloc2[1], &
		xinorm1[1], &xinorm2[1]);
    }
    ellone_(f2, &flvar_1.dp, &rmr, &xld, &omp, &xl2, &om2);
    omp = *rm * omp + (1. - *rm) * .5;
    if (*potc < omp) {
	s_wsfe(&io___1649);
	e_wsfe();
    }
    return 0;
} /* modlog_ */

/* Subroutine */ int nekmin_(doublereal *rm, doublereal *omeg, doublereal *x, 
	doublereal *z__)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal d__, p1, p2, dn[4], en[2];
    static integer ll[2], mm[2];
    static doublereal om, p115, p215, p125, p225, dt1, dt2, rp1, rp2, ome, 
	    out[2], abdx, abdz, delz, dodz, delom;
    extern /* Subroutine */ int dminv_(doublereal *, integer *, doublereal *, 
	    integer *, integer *);
    static doublereal abdelz;
    extern /* Subroutine */ int dgmprd_(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *);

/*  Version of October 9, 1995 */
    *z__ = .05;
L15:
    p1 = *x * *x + *z__ * *z__;
    rp1 = sqrt(p1);
    p115 = p1 * rp1;
/* Computing 2nd power */
    d__1 = 1. - *x;
    p2 = d__1 * d__1 + *z__ * *z__;
    rp2 = sqrt(p2);
    p215 = p2 * rp2;
    dodz = -(*z__) / p115 - *rm * *z__ / p215;
    om = 1. / rp1 + *rm / rp2 + (*rm + 1.) * .5 * *x * *x - *rm * *x;
    delom = *omeg - om;
    delz = delom / dodz;
    *z__ = (d__1 = *z__ + delz, abs(d__1));
    abdelz = abs(delz);
    if (abdelz > 1e-5) {
	goto L15;
    }
L16:
    p1 = *x * *x + *z__ * *z__;
    rp1 = sqrt(p1);
    p115 = p1 * rp1;
    p125 = p1 * p115;
/* Computing 2nd power */
    d__1 = 1. - *x;
    p2 = d__1 * d__1 + *z__ * *z__;
    rp2 = sqrt(p2);
    p215 = p2 * rp2;
    p225 = p2 * p215;
    dn[0] = -(*x) / p115 + *rm * (1. - *x) / p215 + (*rm + 1.) * *x - *rm;
/* Computing 2nd power */
    d__1 = 1. - *x;
/* Computing 2nd power */
    d__2 = 1. - *x;
    dn[1] = (*x * 3. * *x - p1) / p125 + (*rm * 3. * (d__1 * d__1) - *rm * (
	    d__2 * d__2 + *z__ * *z__)) / p225 + (*rm + 1.);
    dn[2] = -(*z__) / p115 - *rm * *z__ / p215;
    dn[3] = *x * 3. * *z__ / p125 - *rm * 3. * *z__ * (1. - *x) / p225;
    ome = 1. / rp1 + *rm / rp2 + (*rm + 1.) * .5 * *x * *x - *rm * *x;
    en[0] = *omeg - ome;
    en[1] = -dn[0];
    dminv_(dn, &c__2, &d__, ll, mm);
    dgmprd_(dn, en, out, &c__2, &c__2, &c__1);
    dt1 = out[0];
    dt2 = out[1];
    abdx = abs(dt1);
    *x += dt1;
    abdz = abs(dt2);
    *z__ += dt2;
    if (abdx > 1e-8) {
	goto L16;
    }
    if (abdz > 1e-8) {
	goto L16;
    }
    return 0;
} /* nekmin_ */

/* Subroutine */ int olump_(doublereal *rv, doublereal *grx, doublereal *gry, 
	doublereal *grz, doublereal *rvq, doublereal *grxq, doublereal *gryq, 
	doublereal *grzq, doublereal *slump1, doublereal *slump2, integer *
	mmsave, doublereal *grexp, doublereal *alb, doublereal *rb, 
	doublereal *tpoll, doublereal *sbr, doublereal *summ, integer *n1, 
	integer *n2, integer *komp, integer *ifat, doublereal *x, doublereal *
	y, doublereal *d__, doublereal *snth, doublereal *csth, doublereal *
	snfi, doublereal *csfi, doublereal *tld, doublereal *glump1, 
	doublereal *glump2, doublereal *glog1, doublereal *glog2, doublereal *
	grv1, doublereal *grv2, integer *iband)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal), asin(doublereal), acos(doublereal), sin(
	    doublereal), cos(doublereal);

    /* Local variables */
    static doublereal e, f[3];
    static integer i__, j, n;
    static doublereal p, r__, w[3], z__;
    extern /* Subroutine */ int planckint_(doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal cc, ah, df, fe, em, ar, br, fp, cr;
    static integer ll;
    static doublereal pi;
    static integer iq;
    static doublereal en;
    static integer is, mm, np, ip;
    static doublereal gx;
    static integer ix, iy;
    static doublereal gy, gz, rc, rp;
    static integer it;
    static doublereal xx, yy, zz, boa, fii, hcn, pi32, cmp, pih, enn, par;
    static integer lll;
    static doublereal rtf;
    static integer npp;
    static doublereal sum, rmx, boc2;
    static integer ipn1;
    static doublereal cot2, abar, boal, fsec, cmpd, deno, comp, cmpp;
    static integer llll;
    static doublereal stcf, grav, dist, fist, rpar;
    extern /* Subroutine */ int atmx_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal pint, ftri, xcos, ycos, stsf, zcos, cosq, tnew, xint, 
	    albep, grmag, glogg, cmppd, gplog, compp, costh, tpole, sinth, 
	    xxref, tlocal, cosine, grrefl, pollog, xintlog;

/*   Version of January 8, 2003 */
    /* Parameter adjustments */
    --grv2;
    --grv1;
    --glog2;
    --glog1;
    --glump2;
    --glump1;
    --tld;
    --csfi;
    --snfi;
    --csth;
    --snth;
    --mmsave;
    --slump2;
    --slump1;
    --grzq;
    --gryq;
    --grxq;
    --rvq;
    --grz;
    --gry;
    --grx;
    --rv;

    /* Function Body */
    atmmessages_2.kompcom = *komp;
    iq = (*komp - 1) * (*n1 + 1);
    is = (*komp - 1) * mmsave[iq];
    fp = .07957747;
    pi = 3.141592653589793;
    pih = 1.570796326794897;
    pi32 = 4.71238898038469;
    f[0] = .1127017;
    f[1] = .5;
    f[2] = .8872983;
    w[0] = .277777777777777;
    w[1] = .444444444444444;
    w[2] = .277777777777777;
    tpole = *tpoll * 1e4;
    cmp = (doublereal) (*komp - 1);
    cmpp = (doublereal) (2 - *komp);
    gplog = cmpp * gpoles_1.gplog1 + cmp * gpoles_1.gplog2;
    if (*ifat == 0) {
	planckint_(&tpole, iband, &pollog, &pint);
    }
    if (*ifat != 0) {
	atmx_(&tpole, &gplog, iband, &pollog, &pint);
    }
    compp = (doublereal) ((*komp << 1) - 3);
    comp = -compp;
    cmpd = cmp * *d__;
    cmppd = cmpp * *d__;
    n = (2 - *komp) * *n1 + (*komp - 1) * *n2;
    enn = (*x + 15.) * (*grexp + 1.) / (15. - *x * 5.);
    np = *n1 + 1 + (2 - *komp) * (*n2 + 1);
    npp = *n1 * (*komp - 1) + (np - 1) * (2 - *komp);
    ll = mmsave[npp] + 1;
    lll = mmsave[np];
    llll = (ll + lll) / 2;
    ar = rv[lll] * cmp + rvq[lll] * cmpp;
    br = rv[llll] * cmp + rvq[llll] * cmpp;
    cr = rv[1] * cmp + rvq[1] * cmpp;
    boa = br / ar;
    boal = 1. - boa * boa;
/* Computing 2nd power */
    d__1 = br / cr;
    boc2 = d__1 * d__1;
/* Computing 2nd power */
    d__1 = boa;
    cc = 1. / (1. - enn * .25 * (1. - d__1 * d__1) * (.9675 - boa * .3008));
    hcn = cc * .5 * enn;
    df = 1. - *x / 3.;
    if (invar_4.ld == 2) {
	df += *y * 2. / 9.;
    }
    if (invar_4.ld == 3) {
	df -= *y * .2;
    }
    en = (doublereal) n;
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ipn1 = i__ + *n1 * (*komp - 1);
	sinth = snth[ipn1];
	costh = csth[ipn1];
	em = sinth * en * 1.3;
	mm = (integer) (em + 1.);
	ip = (*komp - 1) * (*n1 + 1) + i__;
	iy = mmsave[ip];
	i__2 = mm;
	for (j = 1; j <= i__2; ++j) {
	    ++is;
	    stcf = sinth * csfi[is];
	    stsf = sinth * snfi[is];
	    ix = iy + j;
	    if (*komp == 1) {
		goto L39;
	    }
	    if (rvq[ix] == -1.) {
		goto L8;
	    }
	    gx = grxq[ix];
	    gy = gryq[ix];
	    gz = grzq[ix];
	    r__ = rvq[ix];
	    goto L49;
L39:
	    if (rv[ix] == -1.) {
		goto L8;
	    }
	    gx = grx[ix];
	    gy = gry[ix];
	    gz = grz[ix];
	    r__ = rv[ix];
L49:
	    grmag = sqrt(gx * gx + gy * gy + gz * gz);
	    zz = r__ * costh;
	    yy = r__ * comp * stsf;
	    xx = cmpd + comp * stcf * r__;
	    xxref = (cmppd + compp * xx) * compp;
	    grav = cmpp * grv1[ix] + cmp * grv2[ix];
	    tlocal = tpole * sqrt(sqrt(grav));
	    dist = sqrt(xxref * xxref + yy * yy + zz * zz);
	    rmx = asin((br + cr) * .5 / dist);
	    xcos = xxref / dist;
	    ycos = yy / dist;
	    zcos = zz / dist;
	    cosine = (xcos * gx + ycos * gy + zcos * gz) / grmag;
	    rc = pih - acos(cosine);
	    ah = rc / rmx;
	    rp = abs(ah);
	    if (ah <= .99999) {
		goto L22;
	    }
	    p = 1.;
	    goto L16;
L22:
	    if (ah >= -.99999) {
		goto L24;
	    }
	    albep = 0.;
	    goto L19;
L24:
	    sum = 0.;
	    fist = asin(rp);
	    fii = pih - fist;
	    for (it = 1; it <= 3; ++it) {
		fe = fii * f[it - 1] + fist;
/* Computing 2nd power */
		d__1 = rp / sin(fe);
		par = 1. - d__1 * d__1;
		rpar = sqrt(par);
		sum = par * rpar * w[it - 1] + sum;
/* L15: */
	    }
/* Computing 2nd power */
	    d__1 = rp;
	    ftri = (1. - *x) * rp * sqrt(1. - d__1 * d__1) + *x * 
		    .666666666666666 * fii - *x * .666666666666667 * sum * 
		    fii;
	    fsec = (pih + fist) * df;
	    p = (ftri + fsec) / (pi * df);
	    if (cosine < 0.) {
		p = 1. - p;
	    }
/* Computing 2nd power */
	    d__1 = ah;
	    rtf = sqrt(1. - d__1 * d__1);
	    deno = pi32 - (ah * rtf + asin(ah)) * 3.;
	    if (deno != 0.) {
		goto L117;
	    }
	    abar = 1.;
	    goto L116;
L117:
/* Computing 3rd power */
	    d__1 = rtf;
	    abar = d__1 * (d__1 * d__1) * 2. / deno;
L116:
	    cosine = cos(pih - rmx * abar);
L16:
/* Computing 2nd power */
	    d__1 = yy / xxref;
	    cosq = 1. / (d__1 * d__1 + 1.);
/* Computing 2nd power */
	    d__1 = zz / xxref;
	    cot2 = d__1 * d__1;
	    z__ = boal / (boc2 * cot2 + 1.);
	    e = cc - hcn * cosq * z__;
	    albep = *alb * e * p;
L19:
	    if (cosine <= 0.) {
		albep = 0.;
	    }
	    tnew = tlocal * sqrt(sqrt(fp * *summ / (dist * dist * grav) * 
		    cosine * *rb * albep + 1.));
	    tld[is] = tnew;
	    glogg = cmpp * glog1[ix] + cmp * glog2[ix];
	    if (*ifat == 0) {
		planckint_(&tnew, iband, &xintlog, &xint);
	    }
	    if (*ifat != 0) {
		atmx_(&tnew, &glogg, iband, &xintlog, &xint);
	    }
	    grrefl = xint / pint;
	    if (*komp == 1) {
		goto L77;
	    }
	    slump2[ix] = glump2[ix] * grrefl * *sbr;
	    goto L8;
L77:
	    slump1[ix] = glump1[ix] * grrefl * *sbr;
L8:
	    ;
	}
    }
    return 0;
} /* olump_ */

/* Subroutine */ int planckint_(doublereal *t, integer *ifil, doublereal *
	ylog, doublereal *y)
{
    /* Builtin functions */
    double d_lg10(doublereal *), pow_dd(doublereal *, doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int legendre_(doublereal *, doublereal *, integer 
	    *);
    static integer j, ib, jj;
    static doublereal tb, te, pl[10];
    static integer ibin;
    static doublereal dark, phas;

    /* Fortran I/O blocks */
    static cilist io___1773 = { 0, 16, 0, 0, 0 };


/*  Version of January 9, 2002 */
/* cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
/*  IMPORTANT README */
/*  This subroutine returns the log10 (ylog) of a Planck central */
/*  intensity (y), as well as the Planck central intensity (y) itself. */
/*  The subroutine ONLY WORKS FOR TEMPERATURES GREATER THAN OR EQUAL */
/*  500 K OR LOWER THAN 500,300 K. For teperatures outside this range, */
/*  the program stops and prints a message. */
/* ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc */
    if (*t < 500.) {
	goto L11;
    }
    if (*t >= 1900.) {
	goto L1;
    }
    tb = 500.;
    te = 2e3;
    ibin = 1;
    goto L5;
L1:
    if (*t >= 5500.) {
	goto L2;
    }
    tb = 1800.;
    te = 5600.;
    ibin = 2;
    goto L5;
L2:
    if (*t >= 2e4) {
	goto L3;
    }
    tb = 5400.;
    te = 20100.;
    ibin = 3;
    goto L5;
L3:
    if (*t >= 1e5) {
	goto L4;
    }
    tb = 19900.;
    te = 100100.;
    ibin = 4;
    goto L5;
L4:
    if (*t > 500300.) {
	goto L11;
    }
    tb = 99900.;
    te = 500300.;
    ibin = 5;
L5:
    ib = (*ifil - 1) * 50 + (ibin - 1) * 10;
    phas = (*t - tb) / (te - tb);
    legendre_(&phas, pl, &c__10);
    *y = 0.;
    for (j = 1; j <= 10; ++j) {
	jj = j + ib;
/* L6: */
	*y += pl[j - 1] * planckleg_3.plcof[jj - 1];
    }
    dark = 1. - coflimbdark_1.xld / 3.;
    if (invar_6.ld == 2) {
	dark += coflimbdark_1.yld / 4.5;
    }
    if (invar_6.ld == 3) {
	dark -= coflimbdark_1.yld * .2;
    }
    *ylog = *y - d_lg10(&dark) - .49714987269413;
    *y = pow_dd(&c_b18, ylog);
    return 0;
L11:
    s_wsle(&io___1773);
    do_lio(&c__9, &c__1, "planckint subroutine problem: T=", (ftnlen)32);
    do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
    do_lio(&c__9, &c__1, " is illegal.", (ftnlen)12);
    e_wsle();
    s_stop("", (ftnlen)0);
/* 80  format('Program stopped in PLANCKINT, */
/*    $T outside 500 - 500,300 K range.') */
    return 0;
} /* planckint_ */

/* Subroutine */ int rangau_(doublereal *smod, integer *nn, doublereal *sd, 
	doublereal *gau)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal g1, sn, ffac, sfac, sm1p1;
    extern /* Subroutine */ int ranuni_(doublereal *, doublereal *, 
	    doublereal *);

/*  Version of February 6, 1997 */
    ffac = .961;
    sfac = ffac * 3. * *sd / sqrt((doublereal) (*nn) * 3.);
    g1 = 0.;
    i__1 = *nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	sn = *smod;
	ranuni_(&sn, smod, &sm1p1);
	g1 += sm1p1;
/* L22: */
    }
    *gau = sfac * g1;
    return 0;
} /* rangau_ */

/* Subroutine */ int ranuni_(doublereal *sn, doublereal *smod, doublereal *
	sm1p1)
{
    static doublereal st, xmod;

/*  Version of January 17, 2003 */

/*   On each call, subroutine ranuni generates a pseudo-random number, */
/*     sm1p1, distributed with uniform probability over the range */
/*     -1. to +1. */

/*   The input number sn, from which both output numbers are generated, */
/*     should be larger than the modulus 1.00000001d8 and smaller */
/*     than twice the modulus. The returned number smod will be in */
/*     that range and can be used as the input sn on the next call */

    st = 23.;
    xmod = 100000001.;
    *smod = st * *sn;
    goto L2;
L1:
    *smod -= xmod;
L2:
    if (*smod > xmod) {
	goto L1;
    }
    *sm1p1 = *smod * 2. / xmod - 1.;
    return 0;
} /* ranuni_ */

/* Subroutine */ int rddata_(integer *mpage, integer *nref, integer *mref, 
	integer *ifsmv1, integer *ifsmv2, integer *icor1, integer *icor2, 
	integer *ld, integer *jdphs, doublereal *hjd0, doublereal *period, 
	doublereal *dpdt, doublereal *pshift, doublereal *stdev, integer *
	noise, doublereal *seed, doublereal *hjdst, doublereal *hjdsp, 
	doublereal *hjdin, doublereal *phstrt, doublereal *phstop, doublereal 
	*phin, doublereal *phn, integer *mode, integer *ipb, integer *ifat1, 
	integer *ifat2, integer *n1, integer *n2, doublereal *perr0, 
	doublereal *dperdt, doublereal *the, doublereal *vunit, doublereal *e,
	 doublereal *a, doublereal *f1, doublereal *f2, doublereal *vga, 
	doublereal *xincl, doublereal *gr1, doublereal *gr2, doublereal *
	abunin, doublereal *tavh, doublereal *tavc, doublereal *alb1, 
	doublereal *alb2, doublereal *poth, doublereal *potc, doublereal *rm, 
	doublereal *xbol1, doublereal *xbol2, doublereal *ybol1, doublereal *
	ybol2, integer *iband, doublereal *hlum, doublereal *clum, doublereal 
	*xh, doublereal *xc, doublereal *yh, doublereal *yc, doublereal *el3, 
	doublereal *opsf, doublereal *zero, doublereal *factor, doublereal *
	wl, doublereal *binwm1, doublereal *sc1, doublereal *sl1, doublereal *
	wll1, doublereal *ewid1, doublereal *depth1, integer *kks, doublereal 
	*binwm2, doublereal *sc2, doublereal *sl2, doublereal *wll2, 
	doublereal *ewid2, doublereal *depth2, doublereal *xlat, doublereal *
	xlong, doublereal *radsp, doublereal *temsp, doublereal *xcl, 
	doublereal *ycl, doublereal *zcl, doublereal *rcl, doublereal *op1, 
	doublereal *fcl, doublereal *edens, doublereal *xmue, doublereal *
	encl, integer *lpimax, integer *ispmax, integer *iclmax)
{
    /* Format strings */
    static char fmt_22[] = "(8(i1,1x))";
    static char fmt_649[] = "(i1,f15.6,d15.10,d13.6,f10.4,d10.4,i2,f11.0)";
    static char fmt_217[] = "(f14.6,f15.6,f13.6,4f12.6)";
    static char fmt_1[] = "(4i2,2i4,f13.6,d12.5,f7.5,f8.2)";
    static char fmt_2[] = "(f6.5,d13.6,2f10.4,f10.4,f9.3,2f7.3,f7.2)";
    static char fmt_6[] = "(2(f7.4,1x),2f7.3,3d13.6,4f7.3)";
    static char fmt_4[] = "(i3,2f10.5,4f10.6,f8.4,d10.4,f8.3,f8.4,f9.6)";
    static char fmt_2048[] = "(d11.5,f9.4,f9.2,i3)";
    static char fmt_138[] = "(f9.6,d12.5,f10.5,i5)";
    static char fmt_85[] = "(4f9.5)";
    static char fmt_63[] = "(3f9.4,f7.4,d11.4,f9.4,d11.3,f9.4,f7.3)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_rsfe(cilist *), do_fio(integer *, char *, ftnlen), e_rsfe(void);

    /* Local variables */
    static integer i__, kp, iln;

    /* Fortran I/O blocks */
    static cilist io___1782 = { 0, 15, 0, fmt_22, 0 };
    static cilist io___1783 = { 0, 15, 0, fmt_649, 0 };
    static cilist io___1784 = { 0, 15, 0, fmt_217, 0 };
    static cilist io___1785 = { 0, 15, 0, fmt_1, 0 };
    static cilist io___1786 = { 0, 15, 0, fmt_2, 0 };
    static cilist io___1787 = { 0, 15, 0, fmt_6, 0 };
    static cilist io___1788 = { 0, 15, 0, fmt_4, 0 };
    static cilist io___1789 = { 0, 15, 0, fmt_2048, 0 };
    static cilist io___1791 = { 0, 15, 0, fmt_138, 0 };
    static cilist io___1792 = { 0, 15, 0, fmt_2048, 0 };
    static cilist io___1793 = { 0, 15, 0, fmt_138, 0 };
    static cilist io___1796 = { 0, 15, 0, fmt_85, 0 };
    static cilist io___1797 = { 0, 15, 0, fmt_63, 0 };


    /* Parameter adjustments */
    --encl;
    --xmue;
    --edens;
    --fcl;
    --op1;
    --rcl;
    --zcl;
    --ycl;
    --xcl;
    temsp -= 3;
    radsp -= 3;
    xlong -= 3;
    xlat -= 3;
    --depth2;
    --ewid2;
    --wll2;
    kks -= 3;
    --depth1;
    --ewid1;
    --wll1;

    /* Function Body */
/* L22: */
/* L649: */
/* L217: */
/* L1: */
/* L2: */
/* L6: */
/* L4: */
/* L2048: */
/* L138: */
/* L85: */
/* L63: */
    s_rsfe(&io___1782);
    do_fio(&c__1, (char *)&(*mpage), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nref), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*mref), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifsmv1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifsmv2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*icor1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*icor2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ld), (ftnlen)sizeof(integer));
    e_rsfe();
    if (*mpage == 9) {
	return 0;
    }
    s_rsfe(&io___1783);
    do_fio(&c__1, (char *)&(*jdphs), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*hjd0), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*period), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dpdt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pshift), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*stdev), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*noise), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*seed), (ftnlen)sizeof(doublereal));
    e_rsfe();
    s_rsfe(&io___1784);
    do_fio(&c__1, (char *)&(*hjdst), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*hjdsp), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*hjdin), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phstrt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phstop), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phin), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phn), (ftnlen)sizeof(doublereal));
    e_rsfe();
    s_rsfe(&io___1785);
    do_fio(&c__1, (char *)&(*mode), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ipb), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifat1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifat2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*perr0), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dperdt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*the), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*vunit), (ftnlen)sizeof(doublereal));
    e_rsfe();
    s_rsfe(&io___1786);
    do_fio(&c__1, (char *)&(*e), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*a), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*f1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*f2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*vga), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xincl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*gr1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*gr2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*abunin), (ftnlen)sizeof(doublereal));
    e_rsfe();
    s_rsfe(&io___1787);
    do_fio(&c__1, (char *)&(*tavh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*tavc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*alb1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*alb2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*poth), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*potc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*rm), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xbol1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xbol2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ybol1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ybol2), (ftnlen)sizeof(doublereal));
    e_rsfe();
    s_rsfe(&io___1788);
    do_fio(&c__1, (char *)&(*iband), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*hlum), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*clum), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*yh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*yc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*el3), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*opsf), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*zero), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*factor), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*wl), (ftnlen)sizeof(doublereal));
    e_rsfe();
    if (*mpage != 3) {
	goto L897;
    }
    s_rsfe(&io___1789);
    do_fio(&c__1, (char *)&(*binwm1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sc1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sl1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ipro_1.nf1, (ftnlen)sizeof(integer));
    e_rsfe();
    i__1 = *lpimax;
    for (iln = 1; iln <= i__1; ++iln) {
	s_rsfe(&io___1791);
	do_fio(&c__1, (char *)&wll1[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ewid1[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&depth1[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&kks[(iln << 1) + 1], (ftnlen)sizeof(integer));
	e_rsfe();
	if (wll1[iln] < 0.) {
	    goto L89;
	}
/* L86: */
    }
L89:
    s_rsfe(&io___1792);
    do_fio(&c__1, (char *)&(*binwm2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sc2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sl2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ipro_1.nf2, (ftnlen)sizeof(integer));
    e_rsfe();
    i__1 = *lpimax;
    for (iln = 1; iln <= i__1; ++iln) {
	s_rsfe(&io___1793);
	do_fio(&c__1, (char *)&wll2[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ewid2[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&depth2[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&kks[(iln << 1) + 2], (ftnlen)sizeof(integer));
	e_rsfe();
	if (wll2[iln] < 0.) {
	    goto L91;
	}
/* L99: */
    }
L91:
L897:
    for (kp = 1; kp <= 2; ++kp) {
	i__1 = *ispmax;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    s_rsfe(&io___1796);
	    do_fio(&c__1, (char *)&xlat[kp + (i__ << 1)], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&xlong[kp + (i__ << 1)], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&radsp[kp + (i__ << 1)], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temsp[kp + (i__ << 1)], (ftnlen)sizeof(
		    doublereal));
	    e_rsfe();
	    if (xlat[kp + (i__ << 1)] >= 200.) {
		goto L88;
	    }
/* L87: */
	}
L88:
	;
    }
    i__1 = *iclmax;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_rsfe(&io___1797);
	do_fio(&c__1, (char *)&xcl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ycl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&zcl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rcl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&op1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&fcl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&edens[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&xmue[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&encl[i__], (ftnlen)sizeof(doublereal));
	e_rsfe();
	if (xcl[i__] > 100.) {
	    goto L66;
	}
/* L62: */
    }
L66:
    return 0;
} /* rddata_ */

/* Subroutine */ int ring_(doublereal *q, doublereal *om, integer *komp, 
	integer *l, doublereal *fr, doublereal *hld, doublereal *r1, 
	doublereal *rl)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double log(doublereal), exp(doublereal), cos(doublereal), sqrt(doublereal)
	    , sin(doublereal), tan(doublereal), asin(doublereal), atan(
	    doublereal);

    /* Local variables */
    static doublereal f;
    static integer i__, j, k, n;
    static doublereal p, r__, z__, a0, a1, a2, b1, b2, aa[3], bb[3], fe;
    static integer jb, ja;
    static doublereal fi[150], el, em;
    static integer ij;
    static doublereal en;
    static integer ll, mm, ir, it, lr;
    static doublereal th;
    static integer ix;
    static doublereal qq, ey, xl, rr, xm, xj;
    static integer ll1;
    static doublereal ph2, ph1, om1, om2, th1, th2, xl2, del, arc, rad[100], 
	    phb, tha[150], dis, the, dth;
    static integer ipl;
    static doublereal cot, csq, eyj, omn, omp, x2r2, eyt, rsq, rrr, cth1, 
	    cth2, cos4, c4sq, sin4, sth1, sth2, dcth, delr, omdp, ctht, thet[
	    100], cosq, rmax, xm2r2, snth, r90sq, rx2r2;
    static integer kntr;
    static doublereal xlsq, xlsv, abdel, delfi, omega, tanfe, delth, domdr, 
	    costh, sinth, cossq, rxm2r2, sinsq, abdelr, hdelfi, dfdsin;
    extern /* Subroutine */ int ellone_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal delsin;
    extern /* Subroutine */ int nekmin_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal dpdsin, drdsin, enthet, sincos;

/*   Version of September 14, 1998 */
    /* Parameter adjustments */
    --hld;
    --fr;

    /* Function Body */
    ix = 0;
    lr = *l + 1;
    i__1 = lr;
    for (i__ = 1; i__ <= i__1; ++i__) {
	tha[i__ - 1] = 0.;
/* L92: */
	fi[i__ - 1] = -.1;
    }
    omega = *om;
    k = 3;
    el = (doublereal) (*l);
    del = 2. / el;
    ellone_(&c_b1275, &c_b1275, q, &xlsv, &om1, &xl2, &om2);
    nekmin_(q, om, &xlsv, &z__);
    xl = xlsv;
    qq = *q;
    xlsq = xl * xl;
    if (*q > 1.) {
	qq = 1. / *q;
    }
    rmax = exp(log(qq) * .345 - 1.125);
    r__ = rmax * (om1 - omega) / (om1 - om2);
    i__1 = *l;
    for (it = 1; it <= i__1; ++it) {
	eyt = (doublereal) it;
	th = eyt * 1.570796326794897 / el;
/* Computing 2nd power */
	d__1 = cos(th);
	cosq = d__1 * d__1;
	delr = 0.;
L14:
	r__ = (d__1 = r__ + delr, abs(d__1));
	rsq = r__ * r__;
	x2r2 = xlsq + rsq;
	rx2r2 = sqrt(x2r2);
/* Computing 2nd power */
	d__1 = xl - 1.;
	xm2r2 = d__1 * d__1 + rsq;
	rxm2r2 = sqrt(xm2r2);
	*om = 1. / rx2r2 + *q * (1. / rxm2r2 - xl) + (*q + 1.) * .5 * (xlsq + 
		rsq * cosq);
	domdr = -r__ / (x2r2 * rx2r2) - *q * r__ / (xm2r2 * rxm2r2) + (*q + 
		1.) * cosq * r__;
	delr = (omega - *om) / domdr;
	abdelr = abs(delr);
	if (abdelr > 1e-5) {
	    goto L14;
	}
	rad[it - 1] = r__;
/* L22: */
	thet[it - 1] = th * 4.;
    }
    *r1 = rad[0];
    *rl = rad[*l - 1];
    r90sq = *rl * *rl;
    i__1 = *l;
    for (ij = 1; ij <= i__1; ++ij) {
	eyj = (doublereal) ij;
	rad[ij - 1] -= (*rl - *r1) * (eyj - 1.) / el;
/* L18: */
    }
    i__1 = k;
    for (n = 1; n <= i__1; ++n) {
	aa[n - 1] = 0.;
/* L65: */
	bb[n - 1] = 0.;
    }
    i__1 = *l;
    for (j = 1; j <= i__1; ++j) {
	i__2 = k;
	for (n = 1; n <= i__2; ++n) {
	    en = (doublereal) (n - 1);
	    enthet = en * thet[j - 1];
	    aa[n - 1] += rad[j - 1] * cos(enthet) * del;
/* L29: */
	    bb[n - 1] += rad[j - 1] * sin(enthet) * del;
	}
    }
    aa[0] *= .5;
    if (*komp == 2) {
	xl = 1. - xlsv;
    }
    xlsq = xl * xl;
    dis = *rl / xl - 5e-4;
    i__2 = *l;
    for (ir = 1; ir <= i__2; ++ir) {
	ll = ir - 1;
	ey = (doublereal) (*l + 1 - ir);
	tha[ir - 1] = ey * 1.570796326794897 / el;
	if (tha[ir - 1] < 1.570796326794897) {
	    goto L82;
	}
	cot = 0.;
	goto L83;
L82:
	cot = 1. / tan(tha[ir - 1]);
L83:
	if (cot >= dis) {
	    goto L50;
	}
/* Computing 2nd power */
	d__1 = cos(tha[ir - 1]);
	cossq = d__1 * d__1;
	a0 = aa[0];
	a1 = aa[1];
	a2 = aa[2];
	b1 = bb[1];
	b2 = bb[2];
	delsin = 0.;
	kntr = 0;
	sinth = sqrt(cossq * (xlsq + r90sq) / r90sq);
L88:
	sinth += delsin;
	++kntr;
	if (sinth > 1.) {
	    sinth = 1. / sinth;
	}
	csq = 1. - sinth * sinth;
	costh = sqrt(csq);
	sinsq = sinth * sinth;
/* Computing 3rd power */
	d__1 = costh;
	sin4 = d__1 * (d__1 * d__1) * 8. * sinth - costh * 4. * sinth;
	cos4 = csq * 8. * (csq - 1.) + 1.;
	c4sq = cos4 * cos4;
	sincos = sin4 * cos4;
	rrr = a0 + a1 * cos4 + a2 * (c4sq + c4sq - 1.) + b1 * sin4 + (b2 + b2)
		 * sincos;
	arc = asin(sinth);
	rr = rrr + (*rl - *r1) * (arc * 2. / 3.141592653589793 - 1. / el);
	if (kntr > 30) {
	    goto L42;
	}
	p = rr * sinth;
	drdsin = -a1 * sinth / costh - a2 * 4. * sinth + b1 - (b2 + b2) * 
		sinsq / costh + (b2 + b2) * costh + (*rl + *rl - *r1 - *r1) / 
		(costh * 3.141592653589793);
	dpdsin = rr + sinth * drdsin;
	f = p * p / cossq - rr * rr - xlsq;
	dfdsin = (p + p) * dpdsin / cossq - (rr + rr) * drdsin;
	delsin = -f / dfdsin;
	abdel = abs(delsin);
	if (abdel > 1e-5) {
	    goto L88;
	}
L42:
	fi[ir - 1] = atan(rr * costh / xl);
    }
L50:
    ll1 = ll + 1;
    delth = 1.570796326794897 / el;
    i__2 = *l;
    for (i__ = 1; i__ <= i__2; ++i__) {
	ey = (doublereal) (*l + 1 - i__) - .5;
	the = ey * 1.570796326794897 / el;
	snth = sin(the);
	em = sin(the) * el * 1.3;
	mm = (integer) (em + 1.);
	xm = (doublereal) mm;
	delfi = 3.141592653589793 / xm;
	hdelfi = 1.570796326794897 / xm;
	i__1 = mm;
	for (j = 1; j <= i__1; ++j) {
	    ++ix;
	    if (i__ <= ll1) {
		goto L43;
	    }
	    hld[ix] = 1.;
	    goto L75;
L43:
	    xj = (doublereal) (mm + 1 - j);
	    fe = (xj - .5) * 3.141592653589793 / xm;
	    ph2 = fe + hdelfi;
	    phb = ph2;
	    if (fi[i__ - 1] > fe - hdelfi) {
		goto L51;
	    }
	    hld[ix] = 1.;
	    goto L75;
L51:
	    ipl = i__ + 1;
	    if (fi[ipl - 1] > 0.) {
		goto L66;
	    }
	    rr = a0 + a1 - a2 + (*rl - *r1) * (1. - 1. / el);
	    ph1 = delfi * (xj - 1.);
	    th1 = atan(xl / rr);
	    goto L56;
L66:
	    if (fi[ipl - 1] < fe + hdelfi) {
		goto L52;
	    }
	    hld[ix] = 0.;
	    goto L75;
L52:
	    if (fi[ipl - 1] < fe - hdelfi) {
		goto L53;
	    }
	    ph1 = fi[ipl - 1];
	    th1 = tha[ipl - 1];
	    goto L56;
L53:
	    delsin = 0.;
	    sinth = sqrt(cossq * (xlsq + r90sq) / r90sq);
	    tanfe = tan(fe - hdelfi);
L77:
	    sinth += delsin;
	    if (sinth > 1.) {
		sinth = 1. / sinth;
	    }
	    sinsq = sinth * sinth;
	    csq = 1. - sinsq;
	    costh = sqrt(csq);
/* Computing 3rd power */
	    d__1 = costh;
	    sin4 = d__1 * (d__1 * d__1) * 8. * sinth - costh * 4. * sinth;
	    cos4 = csq * 8. * (csq - 1.) + 1.;
	    c4sq = cos4 * cos4;
	    sincos = sin4 * cos4;
	    rrr = a0 + a1 * cos4 + a2 * (c4sq + c4sq - 1.) + b1 * sin4 + (b2 
		    + b2) * sincos;
	    arc = asin(sinth);
	    rr = rrr + (*rl - *r1) * (arc * 2. / 3.141592653589793 - 1. / el);
	    drdsin = -a1 * sinth / costh - a2 * 4. * sinth + b1 - (b2 + b2) * 
		    sinsq / costh + (b2 + b2) * costh + (*rl + *rl - *r1 - *
		    r1) / (costh * 3.141592653589793);
	    f = rr * costh - xl * tanfe;
	    dfdsin = costh * drdsin - rr * sinth / costh;
	    delsin = -f / dfdsin;
	    abdel = abs(delsin);
	    if (abdel > 1e-5) {
		goto L77;
	    }
	    ph1 = fe - hdelfi;
	    th1 = atan(xl / (rr * sinth * cos(ph1)));
L56:
	    if (fi[i__ - 1] > fe + hdelfi) {
		goto L57;
	    }
	    phb = fi[i__ - 1];
	    th2 = tha[i__ - 1];
	    goto L60;
L57:
	    delsin = 0.;
	    sinth = sqrt(cossq * (xlsq + r90sq) / r90sq);
	    tanfe = tan(fe + hdelfi);
L78:
	    sinth += delsin;
	    if (sinth > 1.) {
		sinth = 1. / sinth;
	    }
	    sinsq = sinth * sinth;
	    csq = 1. - sinsq;
	    costh = sqrt(csq);
/* Computing 3rd power */
	    d__1 = costh;
	    sin4 = d__1 * (d__1 * d__1) * 8. * sinth - costh * 4. * sinth;
	    cos4 = csq * 8. * (csq - 1.) + 1.;
	    c4sq = cos4 * cos4;
	    sincos = sin4 * cos4;
	    rrr = a0 + a1 * cos4 + a2 * (c4sq + c4sq - 1.) + b1 * sin4 + (b2 
		    + b2) * sincos;
	    arc = asin(sinth);
	    rr = rrr + (*rl - *r1) * (arc * 2. / 3.141592653589793 - 1. / el);
	    drdsin = -a1 * sinth / costh - a2 * 4. * sinth + b1 - (b2 + b2) * 
		    sinsq / costh + (b2 + b2) * costh + (*rl + *rl - *r1 - *
		    r1) / (costh * 3.141592653589793);
	    f = rr * costh - xl * tanfe;
	    dfdsin = costh * drdsin - rr * sinth / costh;
	    delsin = -f / dfdsin;
	    abdel = abs(delsin);
	    if (abdel > 1e-5) {
		goto L78;
	    }
	    th2 = atan(xl / (rr * sinth * cos(ph2)));
L60:
	    ctht = cos(tha[ipl - 1]);
	    cth1 = cos(th1);
	    cth2 = cos(th2);
	    sth1 = sin(th1);
	    sth2 = sin(th2);
	    dth = th2 - th1;
	    dcth = cth1 - cth2;
	    omdp = ph2 * dcth - (ph1 * sth1 + phb * sth2) * .5 * dth;
	    omp = delfi * (ctht - cth1);
	    omn = omp + omdp;
	    hld[ix] = omn / (delth * delfi * snth);
L75:
	    ;
	}
    }
    i__1 = ix;
    for (jb = 1; jb <= i__1; ++jb) {
	ja = ix + 1 - jb;
/* L94: */
	fr[jb] = hld[ja];
    }
    return 0;
} /* ring_ */

/* Subroutine */ int romq_(doublereal *omein, doublereal *q, doublereal *f, 
	doublereal *d__, doublereal *ec, doublereal *th, doublereal *fi, 
	doublereal *r__, doublereal *drdo, doublereal *drdq, doublereal *dodq,
	 integer *komp, integer *mode)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal), sqrt(doublereal);

    /* Local variables */
    static doublereal x, dp, dq, qf, ds, rf, om, qp, xp, rm1, rma, ome, omd, 
	    par, qfm, xld, omp, tol, pot, rsq, delr;
    static integer mod46, mod56;
    static doublereal omeg, rmap, theq, xlam, domr, rpar, sinth;
    static integer kount;
    static doublereal xnusq, om2sav, abdelr;
    extern /* Subroutine */ int ellone_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer modkom;
    static doublereal domrsv;

/*  Version of December 5, 2003 */
    theq = 1.570796326794897;
/* Computing 2nd power */
    i__1 = *mode - 5;
    mod46 = i__1 * i__1;
/* Computing 2nd power */
    i__1 = (*mode << 1) - 11;
    mod56 = i__1 * i__1;
    modkom = *mode * (*komp + *komp - 3);
    ome = *omein;
    dq = *q * 1e-4;
    qp = *q + dq;
    tol = 5e-8;
/*     TH, FI SHOULD BE IN RADIANS. */
    sinth = sin(*th);
    xnusq = sinth * sinth;
    xlam = sinth * cos(*fi);
    rma = *q;
    qf = 1.;
    dp = 1. - *ec;
    qfm = 1.;
    if (*komp != 2) {
	goto L23;
    }
    rma = 1. / *q;
    qf = 1. / *q;
/* Computing 2nd power */
    d__1 = *q;
    qfm = -1. / (d__1 * d__1);
L23:
    ellone_(f, &dp, &rma, &x, &omeg, &xld, &omd);
    om2sav = omeg;
    rmap = qp;
    if (*komp != 2) {
	goto L92;
    }
    omeg = omeg * *q + (1. - *q) * .5;
    if (mod56 == 1) {
	ome = omeg;
    }
    rmap = 1. / qp;
    goto L93;
L92:
    if (mod46 == 1) {
	ome = omeg;
    }
L93:
    pot = ome;
    if (*komp == 2) {
	pot = ome / *q + (*q - 1.) * .5 / *q;
    }
    ellone_(f, &dp, &rmap, &xp, &omp, &xld, &omd);
    *dodq = (omp - om2sav) / dq;
    rm1 = rma + 1.;
    ds = *d__ * *d__;
    rf = *f * *f;
    *r__ = 1. / pot;
    kount = 0;
    delr = 0.;
    if (*fi != 0.) {
	goto L85;
    }
    if (*th != theq) {
	goto L85;
    }
    if (*mode == 6) {
	goto L114;
    }
    if (*mode != 4) {
	goto L80;
    }
    if (*komp == 1) {
	goto L114;
    }
    goto L85;
L80:
    if (*mode != 5) {
	goto L85;
    }
    if (*komp == 2) {
	goto L114;
    }
L85:
L14:
    *r__ += delr;
    ++kount;
    if (kount < 20) {
	goto L70;
    }
L217:
    if (*mode == 6) {
	goto L114;
    }
    if (modkom == -4) {
	goto L114;
    }
    if (modkom == 5) {
	goto L114;
    }
    domr = -1e15;
    *r__ = -1.;
    goto L116;
L70:
    rsq = *r__ * *r__;
    par = ds - xlam * 2. * *r__ * *d__ + rsq;
    rpar = sqrt(par);
    om = 1. / *r__ + rma * (1. / rpar - xlam * *r__ / ds) + rm1 * .5 * rsq * 
	    xnusq * rf;
    domr = 1. / (rf * rm1 * xnusq * *r__ - 1. / rsq - rma * (*r__ - xlam * *
	    d__) / (par * rpar) - rma * xlam / ds);
    delr = (pot - om) * domr;
    abdelr = abs(delr);
    if (abdelr > tol) {
	goto L14;
    }
    domrsv = domr;
    if (*r__ >= 1.) {
	goto L217;
    }
    if (*fi != 0.) {
	goto L116;
    }
    if (*th != theq) {
	goto L116;
    }
    if ((d__1 = ome - omeg) < 0.) {
	goto L217;
    } else if (d__1 == 0) {
	goto L114;
    } else {
	goto L116;
    }
L114:
    domr = 1e15;
    *r__ = x;
    goto L118;
L116:
    *drdq = (1. / rpar - *r__ * xlam / ds + rf * .5 * rsq * xnusq) / (1. / 
	    rsq + rma * (1. / (par * rpar) * (*r__ - xlam * *d__) + xlam / ds)
	     - rf * xnusq * rm1 * *r__);
    *drdq *= qfm;
L118:
    *drdo = domr * qf;
    if (*mode == 6) {
	goto L215;
    }
    if (*mode != 4) {
	goto L180;
    }
    if (*komp == 1) {
	goto L215;
    }
    return 0;
L180:
    if (*mode != 5) {
	return 0;
    }
    if (*komp == 2) {
	goto L215;
    }
    return 0;
L215:
    if (*fi != 0.) {
	goto L230;
    }
    if (*th != theq) {
	goto L230;
    }
    *drdq = (xp - x) / dq;
    return 0;
L230:
    *drdq += domrsv * *dodq;
    return 0;
} /* romq_ */

/* Subroutine */ int sincos_(integer *komp, integer *n, integer *n1, 
	doublereal *snth, doublereal *csth, doublereal *snfi, doublereal *
	csfi, integer *mmsave)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double sin(doublereal), cos(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal fi, em, en;
    static integer ip, iq, mm, is;
    static doublereal th, xj, xm, eye;
    static integer ipn1;

/*  Version of November 9, 1995 */
    /* Parameter adjustments */
    --mmsave;
    --csfi;
    --snfi;
    --csth;
    --snth;

    /* Function Body */
    ip = (*komp - 1) * (*n1 + 1) + 1;
    iq = ip - 1;
    is = 0;
    if (*komp == 2) {
	is = mmsave[iq];
    }
    mmsave[ip] = 0;
    en = (doublereal) (*n);
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	eye = (doublereal) i__;
	eye += -.5;
	th = eye * 1.570796326794897 / en;
	ipn1 = i__ + *n1 * (*komp - 1);
	snth[ipn1] = sin(th);
	csth[ipn1] = cos(th);
	em = snth[ipn1] * en * 1.3;
	mm = (integer) (em + 1.);
	xm = (doublereal) mm;
	ip = (*komp - 1) * (*n1 + 1) + i__ + 1;
	iq = ip - 1;
	mmsave[ip] = mmsave[iq] + mm;
	i__2 = mm;
	for (j = 1; j <= i__2; ++j) {
	    ++is;
	    xj = (doublereal) j;
	    fi = (xj - .5) * 3.141592653589793 / xm;
	    csfi[is] = cos(fi);
	    snfi[is] = sin(fi);
/* L8: */
	}
    }
    return 0;
} /* sincos_ */

/* Subroutine */ int spot_(integer *komp, integer *n, doublereal *sinth, 
	doublereal *costh, doublereal *sinfi, doublereal *cosfi, doublereal *
	temf)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double acos(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal s;
    static integer kk, nl;
    static doublereal cosdfi;


/*   If a surface point is in more than one spot, this subroutine */
/*      adopts the product of the spot temperature factors. */

/*   "Latitudes" here actually run from 0 at one pole to 180 deg. */
/*      at the other. */

/*   Version of February 11, 1998 */

    *temf = 1.;
    nl = (2 - *komp) * inprof_1.nl1 + (*komp - 1) * inprof_1.nl2;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = nl;
	for (j = 1; j <= i__2; ++j) {
/* L42: */
	    if (spots_3.kks[*komp + (j << 1) - 3] == -i__) {
		++spots_3.lspot[*komp + (j << 1) - 3];
	    }
	}
	cosdfi = *cosfi * spots_3.coslng[*komp + (i__ << 1) - 3] + *sinfi * 
		spots_3.sinlng[*komp + (i__ << 1) - 3];
	s = acos(*costh * spots_3.coslat[*komp + (i__ << 1) - 3] + *sinth * 
		spots_3.sinlat[*komp + (i__ << 1) - 3] * cosdfi);
	if (s > spots_3.rad[*komp + (i__ << 1) - 3]) {
	    goto L15;
	}
	*temf *= spots_3.temsp[*komp + (i__ << 1) - 3];
	if (inprof_1.mpage != 3) {
	    goto L15;
	}
	i__2 = nl;
	for (j = 1; j <= i__2; ++j) {
	    kk = spots_3.kks[*komp + (j << 1) - 3];
	    if (kk == -i__) {
		spots_3.lspot[*komp + (j << 1) - 3] = 0;
	    }
	    if (kk == i__) {
		++spots_3.lspot[*komp + (j << 1) - 3];
	    }
/* L24: */
	}
L15:
	;
    }
    return 0;
} /* spot_ */

/* Subroutine */ int square_(doublereal *obs, integer *nobs, integer *ml, 
	doublereal *out, doublereal *sd, doublereal *xlamda, doublereal *d__, 
	doublereal *cn, doublereal *cnn, doublereal *cnc, doublereal *clc, 
	doublereal *ss, doublereal *cl, integer *ll, integer *mm)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, j, k;
    static doublereal s;
    static integer ii, ji, ki, jj, kk;
    static doublereal arg, cll;
    static integer iii;
    static doublereal cay;
    static integer nob;
    static doublereal xlf, cnjj;
    static integer jmax;
    static doublereal obsii, obskk;
    extern /* Subroutine */ int dminv_(doublereal *, integer *, doublereal *, 
	    integer *, integer *);
    static doublereal obsqq, sigsq;
    extern /* Subroutine */ int dgmprd_(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *);

/*  Version of January 16, 2002 */

/*  cnc ("cn copy") is the original normal equation matrix */
/*  cn is the re-scaled version of cnc */
/*  cnn comes in as the original n.e. matrix, then is copied */
/*    from cn to become the re-scaled n.e.'s, and finally is */
/*    inverted by DMINV to become the inverse of the re-scaled */
/*    n.e. matrix. */

    /* Parameter adjustments */
    --mm;
    --ll;
    --cl;
    --clc;
    --cnc;
    --cnn;
    --cn;
    --sd;
    --out;
    --obs;

    /* Function Body */
    s = 0.;
    cll = 0.;
    cay = (doublereal) (*nobs - *ml);
    jmax = *ml * *ml;
    i__1 = jmax;
    for (j = 1; j <= i__1; ++j) {
/* L20: */
	cn[j] = 0.;
    }
    i__1 = *ml;
    for (j = 1; j <= i__1; ++j) {
/* L21: */
	cl[j] = 0.;
    }
    i__1 = *nobs;
    for (nob = 1; nob <= i__1; ++nob) {
	iii = nob + *nobs * *ml;
	obsqq = obs[iii];
	i__2 = *ml;
	for (k = 1; k <= i__2; ++k) {
	    i__3 = *ml;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		ii = nob + *nobs * (i__ - 1);
		kk = nob + *nobs * (k - 1);
		j = i__ + (k - 1) * *ml;
		obsii = obs[ii];
		obskk = obs[kk];
		cn[j] += obsii * obskk;
/* L23: */
		cnc[j] = cn[j];
	    }
	}
	i__3 = *ml;
	for (i__ = 1; i__ <= i__3; ++i__) {
	    ii = nob + *nobs * (i__ - 1);
	    obsii = obs[ii];
/* L24: */
	    cl[i__] += obsqq * obsii;
	}
/* L25: */
	cll += obsqq * obsqq;
    }
    i__1 = *ml;
    for (k = 1; k <= i__1; ++k) {
	i__3 = *ml;
	for (i__ = 1; i__ <= i__3; ++i__) {
	    xlf = 0.;
	    if (i__ == k) {
		xlf = *xlamda;
	    }
	    j = i__ + (k - 1) * *ml;
	    ji = i__ + (i__ - 1) * *ml;
	    ki = k + (k - 1) * *ml;
/* L123: */
	    cn[j] = cn[j] / sqrt(cnc[ji] * cnc[ki]) + xlf;
	}
    }
    i__3 = *ml;
    for (i__ = 1; i__ <= i__3; ++i__) {
	ji = i__ + (i__ - 1) * *ml;
	clc[i__] = cl[i__];
/* L124: */
	cl[i__] /= sqrt(cnc[ji]);
    }
    i__3 = jmax;
    for (j = 1; j <= i__3; ++j) {
/* L50: */
	cnn[j] = cn[j];
    }
    dminv_(&cnn[1], ml, d__, &ll[1], &mm[1]);
    dgmprd_(&cnn[1], &cl[1], &out[1], ml, ml, &c__1);
    i__3 = *ml;
    for (i__ = 1; i__ <= i__3; ++i__) {
	ji = i__ + (i__ - 1) * *ml;
/* L125: */
	out[i__] /= sqrt(cnc[ji]);
    }
    i__3 = *ml;
    for (i__ = 1; i__ <= i__3; ++i__) {
/* L26: */
	s += clc[i__] * out[i__];
    }
    s = cll - s;
    *ss = s;
    sigsq = s / cay;
    i__3 = *ml;
    for (j = 1; j <= i__3; ++j) {
	jj = j * *ml + j - *ml;
	cnjj = cnn[jj];
	arg = sigsq * cnjj;
/* L27: */
	sd[j] = sqrt(arg / cnc[jj]);
    }
    return 0;
} /* square_ */

/* Subroutine */ int surfas_(doublereal *rmass, doublereal *potent, integer *
	n, integer *n1, integer *komp, doublereal *rv, doublereal *grx, 
	doublereal *gry, doublereal *grz, doublereal *rvq, doublereal *grxq, 
	doublereal *gryq, doublereal *grzq, integer *mmsave, doublereal *fr1, 
	doublereal *fr2, doublereal *hld, doublereal *ff, doublereal *d__, 
	doublereal *snth, doublereal *csth, doublereal *snfi, doublereal *
	csfi, doublereal *grv1, doublereal *grv2, doublereal *xx1, doublereal 
	*yy1, doublereal *zz1, doublereal *xx2, doublereal *yy2, doublereal *
	zz2, doublereal *csbt1, doublereal *csbt2, doublereal *glump1, 
	doublereal *glump2, doublereal *gmag1, doublereal *gmag2, doublereal *
	glog1, doublereal *glog2, doublereal *grexp)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *), d_lg10(
	    doublereal *);

    /* Local variables */
    static doublereal a, b, c__;
    static integer i__, j;
    static doublereal r__, x, y, z__, x2, em, en, rf;
    static integer ip, iq, mm, is;
    static doublereal om, rm, xl, zz, om2, rm1, xl2, x2t, abr, cmp, par;
    static integer ipl;
    static doublereal dsq;
    static integer knt, iss, isx;
    static doublereal rms, pot, rsq, omz, omx, xnu, xmu, omy, zsq, par1, par2;
    static integer ipn1;
    static doublereal rm1s, afac, bfac, efac;
    extern /* Subroutine */ int gabs_(integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal cmpd, delr, par32, par52, comp, oldr, rmas, domr, rpar, 
	    xlam;
    static integer knth;
    static doublereal xmas, grav;
    extern /* Subroutine */ int ring_(doublereal *, doublereal *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *)
	    ;
    static doublereal tolr, rpar1, rpar2, xnum1, xnum2;
    static integer kflag;
    static doublereal omega, d2rdo2, grmag, absgr, glogg, rcube, denom, cosfi,
	     rsave, rpole, xmaso, sinth;
    static integer kount;
    static doublereal rtest, xlump, sumsq, xnusq, abdelr;
    extern /* Subroutine */ int ellone_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal cosbet;
    extern /* Subroutine */ int nekmin_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal grpole, grvrat, tester;

/*  Version of June 9, 2004 */
    /* Parameter adjustments */
    --glog2;
    --glog1;
    --gmag2;
    --gmag1;
    --glump2;
    --glump1;
    --csbt2;
    --csbt1;
    --zz2;
    --yy2;
    --xx2;
    --zz1;
    --yy1;
    --xx1;
    --grv2;
    --grv1;
    --csfi;
    --snfi;
    --csth;
    --snth;
    --hld;
    --fr2;
    --fr1;
    --mmsave;
    --grzq;
    --gryq;
    --grxq;
    --rvq;
    --grz;
    --gry;
    --grx;
    --rv;

    /* Function Body */
    dsq = *d__ * *d__;
    rmas = *rmass;
    if (*komp == 2) {
	rmas = 1. / *rmass;
    }
/* Computing 2nd power */
    d__1 = *ff;
    rf = d__1 * d__1;
    rtest = 0.;
    ip = (*komp - 1) * (*n1 + 1) + 1;
    iq = ip - 1;
    is = 0;
    isx = (*komp - 1) * mmsave[iq];
    mmsave[ip] = 0;
    kflag = 0;
    ellone_(ff, d__, &rmas, &misc_1.x1, &omega, &xl2, &om2);
    if (*komp == 2) {
	omega = *rmass * omega + (1. - *rmass) * .5;
    }
    x2 = misc_1.x1;
    if (*komp == 2) {
	misc_1.x1 = 1. - misc_1.x1;
    }
    if (eccen_5.e != 0.) {
	goto L43;
    }
    if (*potent < omega) {
	nekmin_(rmass, potent, &misc_1.x1, &zz);
    }
    if (*potent < omega) {
	x2 = 1. - misc_1.x1;
    }
L43:
    comp = (doublereal) (3 - (*komp << 1));
    cmp = (doublereal) (*komp - 1);
    cmpd = cmp * *d__;
    tester = cmpd + comp * misc_1.x1;
    rm1 = *rmass + 1.;
    rms = *rmass;
    rm1s = rm1;
    if (*komp != 2) {
	goto L15;
    }
    pot = *potent / *rmass + (*rmass - 1.) * .5 / *rmass;
    rm = 1. / *rmass;
    rm1 = rm + 1.;
    goto L20;
L15:
    pot = *potent;
    rm = *rmass;
L20:
    en = (doublereal) (*n);
/* ******************************************** */
/*  Find the relative polar radius, R/a */
    delr = 0.;
    r__ = 1. / pot;
    knt = 0;
L714:
    r__ += delr;
    ++knt;
    tolr = abs(r__) * 1e-8;
    rsq = r__ * r__;
    par = dsq + rsq;
    rpar = sqrt(par);
    om = 1. / r__ + rm / rpar;
    domr = 1. / (-1. / rsq - rm * r__ / (par * rpar));
    delr = (pot - om) * domr;
    abdelr = abs(delr);
    if (abdelr > tolr) {
	goto L714;
    }
    rpole = r__;
    rsave = r__;
/* ******************************************** */
/*  Now compute GRPOLE (exactly at the pole) */
    x = cmpd;
    zsq = rpole * rpole;
    par1 = x * x + zsq;
    rpar1 = sqrt(par1);
    xnum1 = 1. / (par1 * rpar1);
    xl = *d__ - x;
/* Computing 2nd power */
    d__1 = xl;
    par2 = d__1 * d__1 + zsq;
    rpar2 = sqrt(par2);
    xnum2 = 1. / (par2 * rpar2);
    omz = -rpole * (xnum1 + rms * xnum2);
    omx = rms * xl * xnum2 - x * xnum1 + rm1s * x * rf - rms / dsq;
    if (*komp == 2) {
	omx = rms * xl * xnum2 - x * xnum1 - rm1s * xl * rf + 1. / dsq;
    }
    grpole = sqrt(omx * omx + omz * omz);
/* ******************************************** */
    gabs_(komp, &eccen_5.smaxis, rmass, &eccen_5.e, &eccen_5.period, d__, &
	    rpole, &xmas, &xmaso, &absgr, &glogg);
    if (*komp == 1) {
	gpoles_1.gplog1 = glogg;
    }
    if (*komp == 2) {
	gpoles_1.gplog2 = glogg;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (i__ != 2) {
	    goto L82;
	}
	if (*komp == 1) {
	    rtest = rv[1] * .3;
	}
	if (*komp == 2) {
	    rtest = rvq[1] * .3;
	}
L82:
	ipn1 = i__ + *n1 * (*komp - 1);
	sinth = snth[ipn1];
	xnu = csth[ipn1];
/* Computing 2nd power */
	d__1 = xnu;
	xnusq = d__1 * d__1;
	em = sinth * en * 1.3;
	xlump = 1. - xnusq;
	mm = (integer) (em + 1.);
	afac = rf * rm1 * xlump;
	i__2 = mm;
	for (j = 1; j <= i__2; ++j) {
	    kount = 0;
	    ++is;
	    ++isx;
	    delr = 0.;
	    cosfi = csfi[isx];
	    xmu = snfi[isx] * sinth;
	    xlam = sinth * cosfi;
	    bfac = xlam * *d__;
	    efac = rm * xlam / dsq;
	    r__ = rsave;
	    oldr = r__;
	    knth = 0;
L14:
	    r__ += delr;
	    tolr = abs(r__) * 1e-8;
	    if (kount < 1) {
		goto L170;
	    }
	    if (knth > 20) {
		goto L170;
	    }
	    if (r__ > 0. && r__ < tester) {
		goto L170;
	    }
	    ++knth;
	    delr *= .5;
	    r__ = oldr;
	    goto L14;
L170:
	    ++kount;
	    if (kount < 80) {
		goto L70;
	    }
	    kflag = 1;
	    r__ = -1.;
	    goto L86;
L70:
	    rsq = r__ * r__;
	    rcube = r__ * rsq;
	    par = dsq - xlam * 2. * r__ * *d__ + rsq;
	    rpar = sqrt(par);
	    par32 = par * rpar;
	    par52 = par * par32;
	    om = 1. / r__ + rm * (1. / rpar - xlam * r__ / dsq) + rm1 * .5 * 
		    rsq * xlump * rf;
	    denom = rf * rm1 * xlump * r__ - 1. / rsq - rm * (r__ - xlam * *
		    d__) / par32 - efac;
	    domr = 1. / denom;
/* Computing 2nd power */
	    d__1 = r__ - bfac;
/* Computing 2nd power */
	    d__2 = denom;
	    d2rdo2 = -domr * (afac + 2. / rcube - rm * (1. / par32 - d__1 * 
		    d__1 * 3. / par52)) / (d__2 * d__2);
/* Computing 2nd power */
	    d__1 = pot - om;
	    delr = (pot - om) * domr + d__1 * d__1 * .5 * d2rdo2;
	    oldr = r__;
	    abdelr = abs(delr);
	    if (abdelr > tolr) {
		goto L14;
	    }
	    abr = abs(r__);
	    if (r__ > rtest) {
		goto L74;
	    }
	    kflag = 1;
	    r__ = -1.;
	    if (*komp == 2) {
		goto L98;
	    }
	    goto L97;
L74:
	    if (abr < tester) {
		rsave = r__;
	    }
	    z__ = r__ * xnu;
	    y = comp * r__ * xmu;
	    x2t = abr * xlam;
	    x = cmpd + comp * x2t;
	    if (*komp == 2) {
		goto L62;
	    }
	    if (x < misc_1.x1) {
		goto L65;
	    }
	    kflag = 1;
	    r__ = -1.;
	    goto L97;
L62:
	    if (x2t < x2) {
		goto L65;
	    }
	    kflag = 1;
	    r__ = -1.;
	    goto L98;
L65:
/* Computing 2nd power */
	    d__1 = y;
/* Computing 2nd power */
	    d__2 = z__;
	    sumsq = d__1 * d__1 + d__2 * d__2;
/* Computing 2nd power */
	    d__1 = x;
	    par1 = d__1 * d__1 + sumsq;
	    rpar1 = sqrt(par1);
	    xnum1 = 1. / (par1 * rpar1);
	    xl = *d__ - x;
/* Computing 2nd power */
	    d__1 = xl;
	    par2 = d__1 * d__1 + sumsq;
	    rpar2 = sqrt(par2);
	    xnum2 = 1. / (par2 * rpar2);
	    omz = -z__ * (xnum1 + rms * xnum2);
	    omy = y * (rm1s * rf - xnum1 - rms * xnum2);
	    omx = rms * xl * xnum2 - x * xnum1 + rm1s * x * rf - rms / dsq;
	    if (*komp == 2) {
		omx = rms * xl * xnum2 - x * xnum1 - rm1s * xl * rf + 1. / 
			dsq;
	    }
	    grmag = sqrt(omx * omx + omy * omy + omz * omz);
	    grvrat = grmag / grpole;
	    grav = pow_dd(&grvrat, grexp);
	    a = comp * xlam * omx;
	    b = comp * xmu * omy;
	    c__ = xnu * omz;
	    cosbet = -(a + b + c__) / grmag;
	    if (cosbet < .7) {
		cosbet = .7;
	    }
L86:
	    if (*komp == 2) {
		goto L98;
	    }
L97:
	    rv[is] = r__;
	    grx[is] = omx;
	    gry[is] = omy;
	    grz[is] = omz;
	    gmag1[is] = sqrt(omx * omx + omy * omy + omz * omz);
	    d__1 = grvrat * absgr;
	    glog1[is] = d_lg10(&d__1);
	    fr1[is] = 1.;
	    glump1[is] = r__ * r__ * sinth / cosbet;
	    grv1[is] = grav;
	    xx1[is] = x;
	    yy1[is] = y;
	    zz1[is] = z__;
	    csbt1[is] = cosbet;
	    goto L8;
L98:
	    rvq[is] = r__;
	    grxq[is] = omx;
	    gryq[is] = omy;
	    grzq[is] = omz;
	    gmag2[is] = sqrt(omx * omx + omy * omy + omz * omz);
	    d__1 = grvrat * absgr;
	    glog2[is] = d_lg10(&d__1);
	    fr2[is] = 1.;
	    glump2[is] = r__ * r__ * sinth / cosbet;
	    grv2[is] = grav;
	    xx2[is] = x;
	    yy2[is] = y;
	    zz2[is] = z__;
	    csbt2[is] = cosbet;
L8:
	    ;
	}
    }
    if (eccen_5.e != 0. || *ff != 1.) {
	goto L53;
    }
    if (kflag == 0) {
	goto L53;
    }
    iss = is - 1;
    if (*komp != 1) {
	goto L50;
    }
    ring_(rmass, potent, &c__1, n, &fr1[1], &hld[1], &radi_1.r1h, &radi_1.rlh)
	    ;
    i__2 = iss;
    for (i__ = 1; i__ <= i__2; ++i__) {
	ipl = i__ + 1;
	if (rv[i__] >= 0.) {
	    goto L55;
	}
	fr1[ipl] += fr1[i__];
	fr1[i__] = 0.;
L55:
	;
    }
L53:
    if (*komp == 2) {
	goto L54;
    }
    is = 0;
    i__2 = *n;
    for (i__ = 1; i__ <= i__2; ++i__) {
	ipn1 = i__ + *n1 * (*komp - 1);
	em = snth[ipn1] * en * 1.3;
	mm = (integer) (em + 1.);
	i__1 = mm;
	for (j = 1; j <= i__1; ++j) {
	    ++is;
	    glump1[is] = fr1[is] * glump1[is];
/* L208: */
	}
    }
    return 0;
L50:
    if (eccen_5.e != 0. || *ff != 1.) {
	goto L54;
    }
    ring_(rmass, potent, &c__2, n, &fr2[1], &hld[1], &radi_1.r1c, &radi_1.rlc)
	    ;
    i__1 = is;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ipl = i__ + 1;
	if (rvq[i__] >= 0.) {
	    goto L56;
	}
	fr2[ipl] += fr2[i__];
	fr2[i__] = 0.;
L56:
	;
    }
L54:
    is = 0;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ipn1 = i__ + *n1 * (*komp - 1);
	em = snth[ipn1] * en * 1.3;
	mm = (integer) (em + 1.);
	i__2 = mm;
	for (j = 1; j <= i__2; ++j) {
	    ++is;
	    glump2[is] = fr2[is] * glump2[is];
/* L108: */
	}
    }
    return 0;
} /* surfas_ */

/* Subroutine */ int volume_(doublereal *v, doublereal *q, doublereal *p, 
	doublereal *d__, doublereal *ff, integer *n, integer *n1, integer *
	komp, doublereal *rv, doublereal *grx, doublereal *gry, doublereal *
	grz, doublereal *rvq, doublereal *grxq, doublereal *gryq, doublereal *
	grzq, integer *mmsave, doublereal *fr1, doublereal *fr2, doublereal *
	hld, doublereal *snth, doublereal *csth, doublereal *snfi, doublereal 
	*csfi, doublereal *summ, doublereal *sm, doublereal *grv1, doublereal 
	*grv2, doublereal *xx1, doublereal *yy1, doublereal *zz1, doublereal *
	xx2, doublereal *yy2, doublereal *zz2, doublereal *csbt1, doublereal *
	csbt2, doublereal *glump1, doublereal *glump2, doublereal *gmag1, 
	doublereal *gmag2, doublereal *glog1, doublereal *glog2, doublereal *
	grexp, integer *ifc, doublereal *tloc1, doublereal *tloc2, doublereal 
	*xinorm1, doublereal *xinorm2)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal domdrabs;
    static integer i__;
    static doublereal dp, ot, ps;
    extern /* Subroutine */ int lum_(doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, integer *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *);
    static doublereal vol, vol1, vol2, delp, sbrd, dpdv;
    static integer kntr;
    static doublereal tolp, tolr, vols, rmsq, rmean, abdelp;
    extern /* Subroutine */ int surfas_(doublereal *, doublereal *, integer *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/*  Version of December 5, 2003 */
    /* Parameter adjustments */
    --xinorm2;
    --xinorm1;
    --tloc2;
    --tloc1;
    --glog2;
    --glog1;
    --gmag2;
    --gmag1;
    --glump2;
    --glump1;
    --csbt2;
    --csbt1;
    --zz2;
    --yy2;
    --xx2;
    --zz1;
    --yy1;
    --xx1;
    --grv2;
    --grv1;
    --csfi;
    --snfi;
    --csth;
    --snth;
    --hld;
    --fr2;
    --fr1;
    --mmsave;
    --grzq;
    --gryq;
    --grxq;
    --rvq;
    --grz;
    --gry;
    --grx;
    --rv;

    /* Function Body */
    if (*ifc == 1) {
	*v = 0.;
    }
    dp = *p * 1e-5;
    ot = .33333333333333331;
    if (*ifc == 1) {
	dp = 0.;
    }
    tolr = 1e-8;
    delp = 0.;
    kntr = 0;
L16:
    *p += delp;
    ++kntr;
    if (kntr >= 20) {
	tolr += tolr;
    }
    ps = *p;
    i__1 = *ifc;
    for (i__ = 1; i__ <= i__1; ++i__) {
	*p = ps;
	if (i__ == 1) {
	    *p += dp;
	}
	surfas_(q, p, n, n1, komp, &rv[1], &grx[1], &gry[1], &grz[1], &rvq[1],
		 &grxq[1], &gryq[1], &grzq[1], &mmsave[1], &fr1[1], &fr2[1], &
		hld[1], ff, d__, &snth[1], &csth[1], &snfi[1], &csfi[1], &
		grv1[1], &grv2[1], &xx1[1], &yy1[1], &zz1[1], &xx2[1], &yy2[1]
		, &zz2[1], &csbt1[1], &csbt2[1], &glump1[1], &glump2[1], &
		gmag1[1], &gmag2[1], &glog1[1], &glog2[1], grexp);
	if (*komp == 2) {
	    goto L14;
	}
	lum_(&c_b1275, &c_b1275, &c_b15, &c_b1275, n, n1, &c__1, &sbrd, &rv[1]
		, &rvq[1], &glump1[1], &glump2[1], &glog1[1], &glog2[1], &
		grv1[1], &grv2[1], &mmsave[1], summ, &fr1[1], sm, &c__0, &vol,
		 q, p, ff, d__, &snth[1], &c__7, &tloc1[1], &tloc2[1], &
		xinorm1[1], &xinorm2[1]);
	goto L15;
L14:
	lum_(&c_b1275, &c_b1275, &c_b15, &c_b1275, n, n1, &c__2, &sbrd, &rv[1]
		, &rvq[1], &glump1[1], &glump2[1], &glog1[1], &glog2[1], &
		grv1[1], &grv2[1], &mmsave[1], summ, &fr2[1], sm, &c__0, &vol,
		 q, p, ff, d__, &snth[1], &c__7, &tloc1[1], &tloc2[1], &
		xinorm1[1], &xinorm2[1]);
L15:
	if (i__ == 1) {
	    vols = vol;
	}
	vol2 = vols;
/* L17: */
	vol1 = vol;
    }
    d__1 = vol * .238732414;
    rmean = pow_dd(&d__1, &ot);
/* Computing 2nd power */
    d__1 = rmean;
    rmsq = d__1 * d__1;

/*  Here use a polar estimate for d(potential)/dr (absolute value). */

    domdrabs = 1. / rmsq + *q * rmean / (*d__ * *d__ + rmsq);
    tolp = domdrabs * tolr;
    if (*ifc == 1) {
	*v = vol;
    }
    if (*ifc == 1) {
	return 0;
    }
    dpdv = dp / (vol2 - vol1);
    delp = (*v - vol1) * dpdv;
    abdelp = abs(delp);
    if (abdelp > tolp) {
	goto L16;
    }
    *p = ps;
    return 0;
} /* volume_ */

/* Subroutine */ int wrfoot_(integer *message, doublereal *f1, doublereal *f2,
	 doublereal *po, doublereal *rm, doublereal *f, doublereal *dp, 
	doublereal *e, doublereal *drdq, doublereal *dodq, integer *ii, 
	integer *mode, integer *mpage)
{
    /* Initialized data */

    static doublereal xtha[4] = { 0.,1.570796,1.570796,1.570796 };
    static doublereal xfia[4] = { 0.,0.,1.5707963,3.14159365 };

    /* Format strings */
    static char fmt_283[] = "(\002log g below ramp range for at least one po"
	    "int\002,\002 on star\002,i2,\002, black body applied locally."
	    "\002)";
    static char fmt_284[] = "(\002log g above ramp range for at least one po"
	    "int\002,\002 on star\002,i2,\002, black body applied locally."
	    "\002)";
    static char fmt_285[] = "(\002T above ramp range for at least one\002"
	    ",\002 point on star\002,i2,\002, black body applied locally.\002)"
	    ;
    static char fmt_286[] = "(\002T below ramp range for at least one poin"
	    "t\002,\002 on star\002,i2,\002, black body applied locally.\002)";
    static char fmt_41[] = "(\002star\002,4x,\002r pole\002,5x,\002deriv\002"
	    ",5x,\002r point\002,5x,\002deriv\002,6x,\002r side\002,6x,\002de"
	    "riv\002,5x,\002r back\002,6x,\002deriv\002)";
    static char fmt_40[] = "(i3,8f11.5)";
    static char fmt_74[] = "(\002 DIMENSIONLESS RADIAL VELOCITIES CONTAIN FA"
	    "CTOR P/(2PI*A)\002)";

    /* Builtin functions */
    integer s_wsle(cilist *), e_wsle(void), s_wsfe(cilist *), do_fio(integer *
	    , char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__;
    static doublereal gt1, gt2, rad[4], drdo[4];
    static integer komp;
    extern /* Subroutine */ int romq_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *);

    /* Fortran I/O blocks */
    static cilist io___2088 = { 0, 16, 0, 0, 0 };
    static cilist io___2089 = { 0, 16, 0, fmt_283, 0 };
    static cilist io___2090 = { 0, 16, 0, fmt_284, 0 };
    static cilist io___2091 = { 0, 16, 0, fmt_285, 0 };
    static cilist io___2092 = { 0, 16, 0, fmt_286, 0 };
    static cilist io___2093 = { 0, 16, 0, 0, 0 };
    static cilist io___2094 = { 0, 16, 0, fmt_41, 0 };
    static cilist io___2095 = { 0, 16, 0, 0, 0 };
    static cilist io___2101 = { 0, 16, 0, fmt_40, 0 };
    static cilist io___2102 = { 0, 16, 0, 0, 0 };
    static cilist io___2103 = { 0, 16, 0, fmt_74, 0 };


    /* Parameter adjustments */
    --po;
    message -= 3;

    /* Function Body */
/* L283: */
/* L284: */
/* L285: */
/* L286: */
/* L41: */
/* L40: */
/* L74: */
    for (komp = 1; komp <= 2; ++komp) {
	s_wsle(&io___2088);
	e_wsle();
	if (message[komp + 2] == 1) {
	    s_wsfe(&io___2089);
	    do_fio(&c__1, (char *)&komp, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
	if (message[komp + 4] == 1) {
	    s_wsfe(&io___2090);
	    do_fio(&c__1, (char *)&komp, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
	if (message[komp + 6] == 1) {
	    s_wsfe(&io___2091);
	    do_fio(&c__1, (char *)&komp, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
	if (message[komp + 8] == 1) {
	    s_wsfe(&io___2092);
	    do_fio(&c__1, (char *)&komp, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
/* L909: */
    }
    if (*mpage == 5) {
	return 0;
    }
    s_wsle(&io___2093);
    e_wsle();
    s_wsfe(&io___2094);
    e_wsfe();
    s_wsle(&io___2095);
    e_wsle();
    for (*ii = 1; *ii <= 2; ++(*ii)) {
	gt1 = (doublereal) (2 - *ii);
	gt2 = (doublereal) (*ii - 1);
	*f = *f1 * gt1 + *f2 * gt2;
	for (i__ = 1; i__ <= 4; ++i__) {
	    romq_(&po[*ii], rm, f, dp, e, &xtha[i__ - 1], &xfia[i__ - 1], &
		    rad[i__ - 1], &drdo[i__ - 1], drdq, dodq, ii, mode);
/* L118: */
	}
	s_wsfe(&io___2101);
	do_fio(&c__1, (char *)&(*ii), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&rad[0], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&drdo[0], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rad[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&drdo[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rad[2], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&drdo[2], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rad[3], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&drdo[3], (ftnlen)sizeof(doublereal));
	e_wsfe();
/* L119: */
    }
    s_wsle(&io___2102);
    e_wsle();
    if (*mpage == 2) {
	s_wsfe(&io___2103);
	e_wsfe();
    }
    return 0;
} /* wrfoot_ */

/* Subroutine */ int wrdata_(doublereal *hjd, doublereal *phas, doublereal *
	yskp, doublereal *zskp, doublereal *htt, doublereal *cool, doublereal 
	*total, doublereal *tot, doublereal *d__, doublereal *smagg, 
	doublereal *vsum1, doublereal *vsum2, doublereal *vra1, doublereal *
	vra2, doublereal *vkm1, doublereal *vkm2, doublereal *delv1, 
	doublereal *delwl1, doublereal *wl1, doublereal *fbin1, doublereal *
	resf1, doublereal *delv2, doublereal *delwl2, doublereal *wl2, 
	doublereal *fbin2, doublereal *resf2, doublereal *rv, doublereal *rvq,
	 integer *mmsave, integer *ll1, integer *lll1, integer *llll1, 
	integer *ll2, integer *lll2, integer *llll2)
{
    /* Format strings */
    static char fmt_128[] = "(\002HJD = \002,f14.5,\002    Phase = \002,f14."
	    "5)";
    static char fmt_131[] = "(3x,\002Y Sky Coordinate\002,4x,\002Z Sky Coord"
	    "inate\002)";
    static char fmt_130[] = "(f16.6,f20.6)";
    static char fmt_3[] = "(f15.6,f15.5,4f12.8,f10.5,f10.4)";
    static char fmt_93[] = "(f14.6,f13.5,4f12.6,2d13.4)";
    static char fmt_92[] = "(\002Phase =\002,f14.6)";
    static char fmt_167[] = "(30x,\002star\002,i2)";
    static char fmt_907[] = "(6x,\002del v\002,6x,\002del wl (mic.)\002,7x"
	    ",\002wl\002,9x,\002profile\002,6x,\002res flux\002)";
    static char fmt_903[] = "(6f14.7)";
    static char fmt_205[] = "(\002******************************************"
	    "****************************\002)";
    static char fmt_296[] = "(f14.6,f13.5,8f10.5)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(cilist *), e_wsle(void), s_wsfe(cilist *), do_fio(integer *
	    , char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, ns1, ns2, imp;

    /* Fortran I/O blocks */
    static cilist io___2104 = { 0, 16, 0, 0, 0 };
    static cilist io___2105 = { 0, 16, 0, 0, 0 };
    static cilist io___2106 = { 0, 16, 0, fmt_128, 0 };
    static cilist io___2107 = { 0, 16, 0, 0, 0 };
    static cilist io___2108 = { 0, 16, 0, fmt_131, 0 };
    static cilist io___2110 = { 0, 16, 0, fmt_130, 0 };
    static cilist io___2111 = { 0, 16, 0, fmt_3, 0 };
    static cilist io___2112 = { 0, 16, 0, fmt_93, 0 };
    static cilist io___2115 = { 0, 16, 0, fmt_92, 0 };
    static cilist io___2116 = { 0, 16, 0, 0, 0 };
    static cilist io___2117 = { 0, 16, 0, fmt_167, 0 };
    static cilist io___2118 = { 0, 16, 0, fmt_907, 0 };
    static cilist io___2120 = { 0, 16, 0, fmt_903, 0 };
    static cilist io___2121 = { 0, 16, 0, 0, 0 };
    static cilist io___2122 = { 0, 16, 0, fmt_167, 0 };
    static cilist io___2123 = { 0, 16, 0, fmt_907, 0 };
    static cilist io___2124 = { 0, 16, 0, fmt_903, 0 };
    static cilist io___2125 = { 0, 16, 0, 0, 0 };
    static cilist io___2126 = { 0, 16, 0, fmt_205, 0 };
    static cilist io___2127 = { 0, 16, 0, 0, 0 };
    static cilist io___2128 = { 0, 16, 0, 0, 0 };
    static cilist io___2129 = { 0, 16, 0, fmt_296, 0 };


    /* Parameter adjustments */
    --mmsave;
    --rvq;
    --rv;
    --resf2;
    --fbin2;
    --wl2;
    --delwl2;
    --delv2;
    --resf1;
    --fbin1;
    --wl1;
    --delwl1;
    --delv1;
    --zskp;
    --yskp;

    /* Function Body */
/* L128: */
/* L131: */
/* L130: */
/* L3: */
/* L93: */
/* L92: */
/* L167: */
/* L907: */
/* L903: */
/* L205: */
/* L296: */
    if (inprof_1.mpage != 5) {
	goto L127;
    }
    s_wsle(&io___2104);
    e_wsle();
    s_wsle(&io___2105);
    e_wsle();
    s_wsfe(&io___2106);
    do_fio(&c__1, (char *)&(*hjd), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phas), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsle(&io___2107);
    e_wsle();
    s_wsfe(&io___2108);
    e_wsfe();
    i__1 = invar_2.ipc;
    for (imp = 1; imp <= i__1; ++imp) {
	s_wsfe(&io___2110);
	do_fio(&c__1, (char *)&yskp[imp], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&zskp[imp], (ftnlen)sizeof(doublereal));
	e_wsfe();
/* L129: */
    }
    return 0;
L127:
    if (inprof_1.mpage == 1) {
	s_wsfe(&io___2111);
	do_fio(&c__1, (char *)&(*hjd), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*phas), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*htt), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*cool), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*total), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*tot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*d__), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*smagg), (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (inprof_1.mpage == 2) {
	s_wsfe(&io___2112);
	do_fio(&c__1, (char *)&(*hjd), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*phas), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*vsum1), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*vsum2), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*vra1), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*vra2), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*vkm1), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*vkm2), (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    ns1 = 1;
    ns2 = 2;
    if (inprof_1.mpage != 3) {
	goto L81;
    }
    s_wsfe(&io___2115);
    do_fio(&c__1, (char *)&(*phas), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsle(&io___2116);
    e_wsle();
    s_wsfe(&io___2117);
    do_fio(&c__1, (char *)&ns1, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___2118);
    e_wsfe();
    i__1 = inprof_1.in1max;
    for (i__ = inprof_1.in1min; i__ <= i__1; ++i__) {
/* L906: */
	s_wsfe(&io___2120);
	do_fio(&c__1, (char *)&delv1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&delwl1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&wl1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&fbin1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&resf1[i__], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    s_wsle(&io___2121);
    e_wsle();
    s_wsfe(&io___2122);
    do_fio(&c__1, (char *)&ns2, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___2123);
    e_wsfe();
    i__1 = inprof_1.in2max;
    for (i__ = inprof_1.in2min; i__ <= i__1; ++i__) {
/* L908: */
	s_wsfe(&io___2124);
	do_fio(&c__1, (char *)&delv2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&delwl2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&wl2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&fbin2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&resf2[i__], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    s_wsle(&io___2125);
    e_wsle();
    s_wsfe(&io___2126);
    e_wsfe();
    s_wsle(&io___2127);
    e_wsle();
    s_wsle(&io___2128);
    e_wsle();
L81:
    if (inprof_1.mpage == 4) {
	s_wsfe(&io___2129);
	do_fio(&c__1, (char *)&(*hjd), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*phas), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rv[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rv[*ll1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rv[*llll1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rv[*lll1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rvq[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rvq[*ll2], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rvq[*llll2], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rvq[*lll2], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    return 0;
} /* wrdata_ */

/* Subroutine */ int wrdci_(char *fn, doublereal *del, integer *kep, integer *
	ifder, integer *ifm, integer *ifr, doublereal *xlamda, integer *kspa, 
	integer *nspa, integer *kspb, integer *nspb, integer *ifvc1, integer *
	ifvc2, integer *nlc, integer *k0, integer *kdisk, integer *isym, 
	integer *nppl, integer *nref, integer *mref, integer *ifsmv1, integer 
	*ifsmv2, integer *icor1, integer *icor2, integer *ld, integer *jdphs, 
	doublereal *hjd0, doublereal *period, doublereal *dpdt, doublereal *
	pshift, integer *mode, integer *ipb, integer *ifat1, integer *ifat2, 
	integer *n1, integer *n2, integer *n1l, integer *n2l, doublereal *
	perr0, doublereal *dperdt, doublereal *the, doublereal *vunit, 
	doublereal *e, doublereal *a, doublereal *f1, doublereal *f2, 
	doublereal *vga, doublereal *xincl, doublereal *gr1, doublereal *gr2, 
	doublereal *abunin, doublereal *tavh, doublereal *tavc, doublereal *
	alb1, doublereal *alb2, doublereal *phsv, doublereal *pcsv, 
	doublereal *rm, doublereal *xbol1, doublereal *xbol2, doublereal *
	ybol1, doublereal *ybol2, integer *iband, doublereal *hla, doublereal 
	*cla, doublereal *x1a, doublereal *x2a, doublereal *y1a, doublereal *
	y2a, doublereal *el3, doublereal *opsf, integer *noise, doublereal *
	sigma, doublereal *wla, integer *nsp1, doublereal *xlat1, doublereal *
	xlong1, doublereal *radsp1, doublereal *temsp1, integer *nsp2, 
	doublereal *xlat2, doublereal *xlong2, doublereal *radsp2, doublereal 
	*temsp2, integer *knobs, doublereal *indep, doublereal *dep, 
	doublereal *weight, ftnlen fn_len)
{
    /* Format strings */
    static char fmt_1[] = "(10(1x,d7.1))";
    static char fmt_2[] = "(1x,2(4i1,1x),7i1,1x,4(5i1,1x),i1,1x,i1,1x,i1,d10"
	    ".3)";
    static char fmt_3[] = "(4i3)";
    static char fmt_4[] = "(i1,1x,i1,1x,5i2)";
    static char fmt_5[] = "(7(i1,1x))";
    static char fmt_6[] = "(i1,f15.6,d17.10,d14.6,f10.4)";
    static char fmt_7[] = "(4i2,4i4,f13.6,d12.5,f8.5,f9.3)";
    static char fmt_8[] = "(f6.5,d13.6,2f10.4,f10.4,f9.3,2f7.3,f7.2)";
    static char fmt_9[] = "(f7.4,f8.4,2f7.3,3d13.6,4f7.3)";
    static char fmt_10[] = "(i3,2f10.5,4f7.3,d10.3,d12.5,f10.6)";
    static char fmt_11[] = "(i3,2f10.5,4f7.3,f8.4,d10.3,i2,d12.5,f10.6)";
    static char fmt_12[] = "(4f9.5)";
    static char fmt_13[] = "(1x,f4.0)";
    static char fmt_14[] = "(f4.0)";
    static char fmt_15[] = "(5(f14.5,f8.4,f6.2))";
    static char fmt_16[] = "(i2)";

    /* System generated locals */
    integer i__1, i__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_wsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_wsfe(void), f_clos(cllist *);

    /* Local variables */
    static integer i__, j;
    static doublereal wt;

    /* Fortran I/O blocks */
    static cilist io___2130 = { 0, 1, 0, fmt_1, 0 };
    static cilist io___2131 = { 0, 1, 0, fmt_1, 0 };
    static cilist io___2132 = { 0, 1, 0, fmt_1, 0 };
    static cilist io___2133 = { 0, 1, 0, fmt_2, 0 };
    static cilist io___2135 = { 0, 1, 0, fmt_3, 0 };
    static cilist io___2136 = { 0, 1, 0, fmt_4, 0 };
    static cilist io___2137 = { 0, 1, 0, fmt_5, 0 };
    static cilist io___2138 = { 0, 1, 0, fmt_6, 0 };
    static cilist io___2139 = { 0, 1, 0, fmt_7, 0 };
    static cilist io___2140 = { 0, 1, 0, fmt_8, 0 };
    static cilist io___2141 = { 0, 1, 0, fmt_9, 0 };
    static cilist io___2142 = { 0, 1, 0, fmt_10, 0 };
    static cilist io___2143 = { 0, 1, 0, fmt_11, 0 };
    static cilist io___2144 = { 0, 1, 0, fmt_12, 0 };
    static cilist io___2145 = { 0, 1, 0, fmt_13, 0 };
    static cilist io___2146 = { 0, 1, 0, fmt_12, 0 };
    static cilist io___2147 = { 0, 1, 0, fmt_13, 0 };
    static cilist io___2148 = { 0, 1, 0, fmt_14, 0 };
    static cilist io___2151 = { 0, 1, 0, fmt_15, 0 };
    static cilist io___2152 = { 0, 1, 0, fmt_15, 0 };
    static cilist io___2153 = { 0, 1, 0, fmt_16, 0 };


    /* Parameter adjustments */
    --weight;
    --dep;
    --indep;
    --knobs;
    --temsp2;
    --radsp2;
    --xlong2;
    --xlat2;
    --temsp1;
    --radsp1;
    --xlong1;
    --xlat1;
    --wla;
    --sigma;
    --noise;
    --opsf;
    --el3;
    --y2a;
    --y1a;
    --x2a;
    --x1a;
    --cla;
    --hla;
    --iband;
    --kep;
    --del;

    /* Function Body */
/* L1: */
/* L2: */
/* L3: */
/* L4: */
/* L5: */
/* L6: */
/* L7: */
/* L8: */
/* L9: */
/* L10: */
/* L11: */
/* L12: */
/* L13: */
/* L14: */
/* L15: */
/* L16: */
    o__1.oerr = 0;
    o__1.ounit = 1;
    o__1.ofnmlen = fn_len;
    o__1.ofnm = fn;
    o__1.orl = 0;
    o__1.osta = "UNKNOWN";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_wsfe(&io___2130);
    do_fio(&c__1, (char *)&del[1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[2], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[3], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[4], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[5], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[6], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[7], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[8], (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2131);
    do_fio(&c__1, (char *)&del[10], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[11], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[12], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[13], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[14], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[16], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[17], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[18], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[19], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[20], (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2132);
    do_fio(&c__1, (char *)&del[21], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[22], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[23], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[24], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[25], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[31], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[32], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[33], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&del[34], (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2133);
    for (i__ = 1; i__ <= 35; ++i__) {
	do_fio(&c__1, (char *)&kep[i__], (ftnlen)sizeof(integer));
    }
    do_fio(&c__1, (char *)&(*ifder), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifm), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifr), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*xlamda), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2135);
    do_fio(&c__1, (char *)&(*kspa), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nspa), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*kspb), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nspb), (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___2136);
    do_fio(&c__1, (char *)&(*ifvc1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifvc2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nlc), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*k0), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*kdisk), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*isym), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nppl), (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___2137);
    do_fio(&c__1, (char *)&(*nref), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*mref), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifsmv1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifsmv2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*icor1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*icor2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ld), (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___2138);
    do_fio(&c__1, (char *)&(*jdphs), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*hjd0), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*period), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dpdt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pshift), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2139);
    do_fio(&c__1, (char *)&(*mode), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ipb), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifat1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifat2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n1l), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n2l), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*perr0), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dperdt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*the), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*vunit), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2140);
    do_fio(&c__1, (char *)&(*e), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*a), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*f1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*f2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*vga), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xincl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*gr1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*gr2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*abunin), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2141);
    do_fio(&c__1, (char *)&(*tavh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*tavc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*alb1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*alb2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phsv), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pcsv), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*rm), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xbol1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xbol2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ybol1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ybol2), (ftnlen)sizeof(doublereal));
    e_wsfe();
    i__1 = *ifvc1 + *ifvc2;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___2142);
	do_fio(&c__1, (char *)&iband[i__], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hla[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cla[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x1a[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x2a[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y1a[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y2a[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&opsf[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sigma[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&wla[i__], (ftnlen)sizeof(doublereal));
	e_wsfe();
/* L90: */
    }
    i__1 = *ifvc1 + *ifvc2 + *nlc;
    for (i__ = *ifvc1 + *ifvc2 + 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___2143);
	do_fio(&c__1, (char *)&iband[i__], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hla[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cla[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x1a[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&x2a[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y1a[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&y2a[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&el3[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&opsf[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&noise[i__], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&sigma[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&wla[i__], (ftnlen)sizeof(doublereal));
	e_wsfe();
/* L91: */
    }
    i__1 = *nsp1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___2144);
	do_fio(&c__1, (char *)&xlat1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&xlong1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&radsp1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&temsp1[i__], (ftnlen)sizeof(doublereal));
	e_wsfe();
/* L92: */
    }
    s_wsfe(&io___2145);
    do_fio(&c__1, (char *)&c_b1630, (ftnlen)sizeof(doublereal));
    e_wsfe();
    i__1 = *nsp2;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___2146);
	do_fio(&c__1, (char *)&xlat2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&xlong2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&radsp2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&temsp2[i__], (ftnlen)sizeof(doublereal));
	e_wsfe();
/* L93: */
    }
    s_wsfe(&io___2147);
    do_fio(&c__1, (char *)&c_b1630, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2148);
    do_fio(&c__1, (char *)&c_b1639, (ftnlen)sizeof(doublereal));
    e_wsfe();
    i__1 = *ifvc1 + *ifvc2 + *nlc;
    for (j = 1; j <= i__1; ++j) {
	i__2 = knobs[j + 1];
	for (i__ = knobs[j] + 1; i__ <= i__2; ++i__) {
	    wt = weight[i__];
	    if (weight[i__] > 99.9f) {
		wt = -1.;
	    }
	    s_wsfe(&io___2151);
	    do_fio(&c__1, (char *)&indep[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dep[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&wt, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* L94: */
	}
	s_wsfe(&io___2152);
	do_fio(&c__1, (char *)&c_b1646, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&c_b15, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&c_b15, (ftnlen)sizeof(doublereal));
	e_wsfe();
/* L95: */
    }
    s_wsfe(&io___2153);
    do_fio(&c__1, (char *)&c__2, (ftnlen)sizeof(integer));
    e_wsfe();
    cl__1.cerr = 0;
    cl__1.cunit = 1;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* wrdci_ */

/* Subroutine */ int wrhead_(integer *ibef, integer *nref, integer *mref, 
	integer *ifsmv1, integer *ifsmv2, integer *icor1, integer *icor2, 
	integer *ld, integer *jdphs, doublereal *hjd0, doublereal *period, 
	doublereal *dpdt, doublereal *pshift, doublereal *stdev, integer *
	noise, doublereal *seed, doublereal *hjdst, doublereal *hjdsp, 
	doublereal *hjdin, doublereal *phstrt, doublereal *phstop, doublereal 
	*phin, doublereal *phn, integer *mode, integer *ipb, integer *ifat1, 
	integer *ifat2, integer *n1, integer *n2, doublereal *perr0, 
	doublereal *dperdt, doublereal *the, doublereal *vunit, doublereal *
	vfac, doublereal *e, doublereal *a, doublereal *f1, doublereal *f2, 
	doublereal *vga, doublereal *xincl, doublereal *gr1, doublereal *gr2, 
	integer *nsp1, integer *nsp2, doublereal *abunin, doublereal *tavh, 
	doublereal *tavc, doublereal *alb1, doublereal *alb2, doublereal *
	phsv, doublereal *pcsv, doublereal *rm, doublereal *xbol1, doublereal 
	*xbol2, doublereal *ybol1, doublereal *ybol2, integer *iband, 
	doublereal *hlum, doublereal *clum, doublereal *xh, doublereal *xc, 
	doublereal *yh, doublereal *yc, doublereal *el3, doublereal *opsf, 
	doublereal *zero, doublereal *factor, doublereal *wl, doublereal *
	binwm1, doublereal *sc1, doublereal *sl1, doublereal *binwm2, 
	doublereal *sc2, doublereal *sl2, doublereal *wll1, doublereal *ewid1,
	 doublereal *depth1, doublereal *wll2, doublereal *ewid2, doublereal *
	depth2, integer *kks, doublereal *xlat, doublereal *xlong, doublereal 
	*radsp, doublereal *temsp, integer *ncl, doublereal *xcl, doublereal *
	ycl, doublereal *zcl, doublereal *rcl, doublereal *op1, doublereal *
	fcl, doublereal *edens, doublereal *xmue, doublereal *encl, 
	doublereal *dens, integer *ns1, doublereal *sms1, doublereal *sr1, 
	doublereal *bolm1, doublereal *xlg1, integer *ns2, doublereal *sms2, 
	doublereal *sr2, doublereal *bolm2, doublereal *xlg2, integer *mmsave,
	 doublereal *sbrh, doublereal *sbrc, doublereal *sm1, doublereal *sm2,
	 doublereal *phperi, doublereal *pconsc, doublereal *pconic, 
	doublereal *dif1, doublereal *abunir, doublereal *abun, integer *mod)
{
    /* Format strings */
    static char fmt_204[] = "(\002*************  Next block of output   ****"
	    "****************************\002)";
    static char fmt_287[] = "(\002Input [M/H] = \002,f6.3,\002 is not a valu"
	    "e recognized by \002,\002the program. Replaced by \002,f5.2)";
    static char fmt_49[] = "(\002 PROGRAM SHOULD NOT BE USED IN MODE 1 OR 3 "
	    "WITH NON-ZERO ECCENTRICITY\002)";
    static char fmt_350[] = "(\002 Primary star exceeds outer contact surf"
	    "ace\002)";
    static char fmt_50[] = "(\002 PRIMARY COMPONENT EXCEEDS CRITICAL LOBE"
	    "\002)";
    static char fmt_351[] = "(\002 Secondary star exceeds outer contact surf"
	    "ace\002)";
    static char fmt_51[] = "(\002 SECONDARY COMPONENT EXCEEDS CRITICAL LOB"
	    "E\002)";
    static char fmt_148[] = "(\002   mpage  nref   mref   ifsmv1   ifsmv2   "
	    "icor1   icor2   ld\002)";
    static char fmt_149[] = "(i6,2i7,i8,i9,i9,i8,i6)";
    static char fmt_171[] = "(\002JDPHS\002,5x,\002J.D. zero\002,7x,\002Peri"
	    "od\002,11x,\002dPdt\002,6x,\002Ph. shift\002,3x,\002fract. sd"
	    ".\002,2x,\002noise\002,5x,\002seed\002)";
    static char fmt_170[] = "(i3,f17.6,d18.10,d14.6,f10.4,d13.4,i5,f13.0)";
    static char fmt_219[] = "(5x,\002JD start\002,9x,\002JD stop\002,6x,\002"
	    "JD incr\002,6x,\002Ph start\002,4x,\002Ph. stop\002,5x,\002Ph in"
	    "cr\002,5x,\002Ph norm\002)";
    static char fmt_218[] = "(f14.6,f16.6,f14.6,4f12.6)";
    static char fmt_10[] = "(\002MODE   IPB  IFAT1 IFAT2   N1   N2\002,4x"
	    ",\002Arg. Per\002,7x,\002dPerdt\002,4x,\002Th e\002,4x,\002V UNI"
	    "T(km/s)    V FAC\002)";
    static char fmt_33[] = "(i4,i5,i6,i6,i7,i5,f13.6,d14.5,f9.5,f10.2,d16.4)";
    static char fmt_48[] = "(\002  ecc\002,5x,\002s-m axis\002,7x,\002F1\002"
	    ",9x,\002F2\002,7x,\002Vgam\002,7x,\002Incl\002,6x,\002g1\002,6x"
	    ",\002g2  Nspot1 Nspot 2\002,4x,\002[M/H]\002)";
    static char fmt_5[] = "(f6.5,d13.6,2f11.4,f11.4,f10.3,2f8.3,i5,i7,f10.2)";
    static char fmt_54[] = "(2x,\002T1\002,6x,\002T2\002,5x,\002Alb 1  Alb "
	    "2\002,4x,\002Pot 1\002,8x,\002Pot 2\002,11x,\002M2/M1\002,2x,"
	    "\002x1(bolo) x2(bolo) y1(bolo) y2(bolo)\002)";
    static char fmt_8[] = "(f7.4,f8.4,2f7.3,3d13.6,f8.3,f9.3,f9.3,f9.3)";
    static char fmt_47[] = "(2x,\002band\002,7x,\002L1\002,9x,\002L2\002,7x"
	    ",\002x1\002,6x,\002x2\002,6x,\002y1\002,6x,\002y2\002,6x,\002el3"
	    "     opsf      m zero   factor\002,2x,\002wv lth\002)";
    static char fmt_34[] = "(i5,1x,2f11.5,4f8.3,f9.4,d11.4,f9.3,f9.4,f9.6)";
    static char fmt_142[] = "(\002star\002,4x,\002bin width (microns)\002,"
	    "3x,\002continuum scale\002,4x,\002continuum slope\002,2x,\002nfi"
	    "ne\002)";
    static char fmt_2049[] = "(i3,d14.5,f18.2,f20.2,i14)";
    static char fmt_157[] = "(\002star \002,i1,\002   line wavelength\002,"
	    "4x,\002equivalent width (microns)\002,5x,\002rect. line depth"
	    "\002,2x,\002kks\002)";
    static char fmt_152[] = "(f20.6,d23.5,17x,f13.5,i6)";
    static char fmt_83[] = "(1x,\002STAR  CO-LATITUDE  LONGITUDE  SPOT RADIU"
	    "S  TEMP. FACTOR\002)";
    static char fmt_84[] = "(1x,i4,4f12.5)";
    static char fmt_69[] = "(\002      xcl       ycl       zcl      rcl     "
	    "  op1         fcl        ne       mu e      encl     dens\002)";
    static char fmt_64[] = "(3f10.4,f9.4,d12.4,f10.4,d12.4,f9.4,f9.3,d12.4)";
    static char fmt_150[] = "(\002 Star\002,9x,\002M/Msun   (Mean Radius)/Rs"
	    "un\002,5x,\002M Bol\002,4x,\002Log g (cgs)\002)";
    static char fmt_250[] = "(4x,i1,4x,f12.3,11x,f7.2,6x,f6.2,8x,f5.2)";
    static char fmt_43[] = "(91x,\002superior\002,5x,\002inferior\002)";
    static char fmt_44[] = "(76x,\002periastron\002,2x,\002conjunction\002,2"
	    "x,\002conjunction\002)";
    static char fmt_46[] = "(\002grid1/4    grid2/4\002,2x,\002polar sbr "
	    "1\002,3x,\002polar sbr 2\002,3x,\002surf. area 1\002,2x,\002surf"
	    ". area 2\002,7x,\002phase\002,8x,\002phase\002,8x,\002phase\002)";
    static char fmt_94[] = "(i6,i11,4f14.6,f13.6,f13.6,f13.6)";
    static char fmt_244[] = "(\002Note: The light curve output contains simu"
	    "lated observa\002,\002tional scatter, as requested,\002)";
    static char fmt_245[] = "(\002with standard deviation\002,f9.5,\002 of l"
	    "ight at the reference\002,\002 phase.\002)";
    static char fmt_79[] = "(6x,\002JD\002,17x,\002Phase     light 1     lig"
	    "ht 2     (1+2+3)    norm lite   dist      mag+K\002)";
    static char fmt_45[] = "(6x,\002JD\002,14x,\002Phase     V Rad 1     V R"
	    "ad 2      del V1      del V2   V1 km/s      V2 km/s\002)";
    static char fmt_96[] = "(6x,\002JD\002,13x,\002Phase\002,5x,\002r1pol"
	    "\002,6x,\002r1pt\002,5x,\002r1sid\002,5x,\002r1bak\002,5x,\002r2"
	    "pol\002,5x,\002r2pt\002,6x,\002r2sid\002,5x,\002r2bak\002)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(cilist *), e_wsle(void), s_wsfe(cilist *), e_wsfe(void), 
	    do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static integer i__, kp, np1, np2, iln, nspot, nstot;

    /* Fortran I/O blocks */
    static cilist io___2154 = { 0, 16, 0, 0, 0 };
    static cilist io___2155 = { 0, 16, 0, 0, 0 };
    static cilist io___2156 = { 0, 16, 0, 0, 0 };
    static cilist io___2157 = { 0, 16, 0, 0, 0 };
    static cilist io___2158 = { 0, 16, 0, 0, 0 };
    static cilist io___2159 = { 0, 16, 0, fmt_204, 0 };
    static cilist io___2160 = { 0, 16, 0, 0, 0 };
    static cilist io___2161 = { 0, 16, 0, 0, 0 };
    static cilist io___2162 = { 0, 16, 0, 0, 0 };
    static cilist io___2163 = { 0, 16, 0, 0, 0 };
    static cilist io___2164 = { 0, 16, 0, fmt_287, 0 };
    static cilist io___2165 = { 0, 16, 0, fmt_49, 0 };
    static cilist io___2166 = { 0, 16, 0, fmt_350, 0 };
    static cilist io___2167 = { 0, 16, 0, fmt_50, 0 };
    static cilist io___2168 = { 0, 16, 0, fmt_351, 0 };
    static cilist io___2169 = { 0, 16, 0, fmt_51, 0 };
    static cilist io___2170 = { 0, 16, 0, 0, 0 };
    static cilist io___2171 = { 0, 16, 0, fmt_148, 0 };
    static cilist io___2172 = { 0, 16, 0, fmt_149, 0 };
    static cilist io___2173 = { 0, 16, 0, 0, 0 };
    static cilist io___2174 = { 0, 16, 0, fmt_171, 0 };
    static cilist io___2175 = { 0, 16, 0, fmt_170, 0 };
    static cilist io___2176 = { 0, 16, 0, 0, 0 };
    static cilist io___2177 = { 0, 16, 0, fmt_219, 0 };
    static cilist io___2178 = { 0, 16, 0, fmt_218, 0 };
    static cilist io___2179 = { 0, 16, 0, 0, 0 };
    static cilist io___2180 = { 0, 16, 0, fmt_10, 0 };
    static cilist io___2181 = { 0, 16, 0, fmt_33, 0 };
    static cilist io___2182 = { 0, 16, 0, 0, 0 };
    static cilist io___2183 = { 0, 16, 0, fmt_48, 0 };
    static cilist io___2184 = { 0, 16, 0, fmt_5, 0 };
    static cilist io___2185 = { 0, 16, 0, 0, 0 };
    static cilist io___2186 = { 0, 16, 0, fmt_54, 0 };
    static cilist io___2187 = { 0, 16, 0, fmt_8, 0 };
    static cilist io___2188 = { 0, 16, 0, 0, 0 };
    static cilist io___2189 = { 0, 16, 0, fmt_47, 0 };
    static cilist io___2190 = { 0, 16, 0, fmt_34, 0 };
    static cilist io___2191 = { 0, 16, 0, 0, 0 };
    static cilist io___2192 = { 0, 16, 0, fmt_142, 0 };
    static cilist io___2193 = { 0, 16, 0, fmt_2049, 0 };
    static cilist io___2194 = { 0, 16, 0, fmt_2049, 0 };
    static cilist io___2195 = { 0, 16, 0, 0, 0 };
    static cilist io___2196 = { 0, 16, 0, fmt_157, 0 };
    static cilist io___2198 = { 0, 16, 0, fmt_152, 0 };
    static cilist io___2199 = { 0, 16, 0, 0, 0 };
    static cilist io___2200 = { 0, 16, 0, fmt_157, 0 };
    static cilist io___2201 = { 0, 16, 0, fmt_152, 0 };
    static cilist io___2202 = { 0, 16, 0, 0, 0 };
    static cilist io___2203 = { 0, 16, 0, 0, 0 };
    static cilist io___2205 = { 0, 16, 0, fmt_83, 0 };
    static cilist io___2209 = { 0, 16, 0, fmt_84, 0 };
    static cilist io___2210 = { 0, 16, 0, 0, 0 };
    static cilist io___2211 = { 0, 16, 0, fmt_69, 0 };
    static cilist io___2212 = { 0, 16, 0, fmt_64, 0 };
    static cilist io___2213 = { 0, 16, 0, 0, 0 };
    static cilist io___2214 = { 0, 16, 0, fmt_150, 0 };
    static cilist io___2215 = { 0, 16, 0, fmt_250, 0 };
    static cilist io___2216 = { 0, 16, 0, fmt_250, 0 };
    static cilist io___2219 = { 0, 16, 0, 0, 0 };
    static cilist io___2220 = { 0, 16, 0, fmt_43, 0 };
    static cilist io___2221 = { 0, 16, 0, fmt_44, 0 };
    static cilist io___2222 = { 0, 16, 0, fmt_46, 0 };
    static cilist io___2223 = { 0, 16, 0, fmt_94, 0 };
    static cilist io___2224 = { 0, 16, 0, 0, 0 };
    static cilist io___2225 = { 0, 16, 0, fmt_244, 0 };
    static cilist io___2226 = { 0, 16, 0, fmt_245, 0 };
    static cilist io___2227 = { 0, 16, 0, 0, 0 };
    static cilist io___2228 = { 0, 16, 0, fmt_79, 0 };
    static cilist io___2229 = { 0, 16, 0, fmt_45, 0 };
    static cilist io___2230 = { 0, 16, 0, fmt_96, 0 };


    /* Parameter adjustments */
    --abun;
    --mmsave;
    --dens;
    --encl;
    --xmue;
    --edens;
    --fcl;
    --op1;
    --rcl;
    --zcl;
    --ycl;
    --xcl;
    temsp -= 3;
    radsp -= 3;
    xlong -= 3;
    xlat -= 3;
    kks -= 3;
    --depth2;
    --ewid2;
    --wll2;
    --depth1;
    --ewid1;
    --wll1;

    /* Function Body */
/* L204: */
/* L287: */
/* L49: */
/* L350: */
/* L50: */
/* L351: */
/* L51: */
/* L148: */
/* L149: */
/* L171: */
/* L170: */
/* L219: */
/* L218: */
/* L10: */
/* L33: */
/* L48: */
/* L5: */
/* L54: */
/* L8: */
/* L47: */
/* L34: */
/* L142: */
/* L2049: */
/* L157: */
/* L152: */
/* L83: */
/* L84: */
/* L69: */
/* L64: */
/* L150: */
/* L250: */
/* L43: */
/* L44: */
/* L46: */
/* L94: */
/* L244: */
/* L245: */
/* L79: */
/* L45: */
/* L96: */
    if (*ibef == 0) {
	goto L335;
    }
    s_wsle(&io___2154);
    e_wsle();
    s_wsle(&io___2155);
    e_wsle();
    s_wsle(&io___2156);
    e_wsle();
    s_wsle(&io___2157);
    e_wsle();
    s_wsle(&io___2158);
    e_wsle();
    s_wsfe(&io___2159);
    e_wsfe();
    s_wsle(&io___2160);
    e_wsle();
    s_wsle(&io___2161);
    e_wsle();
    s_wsle(&io___2162);
    e_wsle();
    s_wsle(&io___2163);
    e_wsle();
L335:
    if (*dif1 != 0.) {
	s_wsfe(&io___2164);
	do_fio(&c__1, (char *)&(*abunir), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*abunin), (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    if (*mod == 1) {
	s_wsfe(&io___2165);
	e_wsfe();
    }
    if (kfac_1.kfo1 == 0) {
	goto L380;
    }
    s_wsfe(&io___2166);
    e_wsfe();
    goto L381;
L380:
    if (kfac_1.kff1 == 1) {
	s_wsfe(&io___2167);
	e_wsfe();
    }
L381:
    if (kfac_1.kfo2 == 0) {
	goto L382;
    }
    s_wsfe(&io___2168);
    e_wsfe();
    goto L383;
L382:
    if (kfac_1.kff2 == 1) {
	s_wsfe(&io___2169);
	e_wsfe();
    }
L383:
    if (kfac_1.kff1 + kfac_1.kff2 + kfac_1.kfo1 + kfac_1.kfo2 > 0) {
	s_wsle(&io___2170);
	e_wsle();
    }
    s_wsfe(&io___2171);
    e_wsfe();
    s_wsfe(&io___2172);
    do_fio(&c__1, (char *)&inprof_1.mpage, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nref), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*mref), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifsmv1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifsmv2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*icor1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*icor2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ld), (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsle(&io___2173);
    e_wsle();
    s_wsfe(&io___2174);
    e_wsfe();
    s_wsfe(&io___2175);
    do_fio(&c__1, (char *)&(*jdphs), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*hjd0), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*period), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dpdt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pshift), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*stdev), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*noise), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*seed), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsle(&io___2176);
    e_wsle();
    s_wsfe(&io___2177);
    e_wsfe();
    s_wsfe(&io___2178);
    do_fio(&c__1, (char *)&(*hjdst), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*hjdsp), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*hjdin), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phstrt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phstop), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phin), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phn), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsle(&io___2179);
    e_wsle();
    s_wsfe(&io___2180);
    e_wsfe();
    s_wsfe(&io___2181);
    do_fio(&c__1, (char *)&(*mode), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ipb), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifat1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifat2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*perr0), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dperdt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*the), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*vunit), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*vfac), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsle(&io___2182);
    e_wsle();
    s_wsfe(&io___2183);
    e_wsfe();
    s_wsfe(&io___2184);
    do_fio(&c__1, (char *)&(*e), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*a), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*f1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*f2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*vga), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xincl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*gr1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*gr2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*nsp1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nsp2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*abunin), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsle(&io___2185);
    e_wsle();
    s_wsfe(&io___2186);
    e_wsfe();
    s_wsfe(&io___2187);
    do_fio(&c__1, (char *)&(*tavh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*tavc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*alb1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*alb2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phsv), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pcsv), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*rm), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xbol1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xbol2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ybol1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ybol2), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsle(&io___2188);
    e_wsle();
    s_wsfe(&io___2189);
    e_wsfe();
    s_wsfe(&io___2190);
    do_fio(&c__1, (char *)&(*iband), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*hlum), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*clum), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*yh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*yc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*el3), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*opsf), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*zero), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*factor), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*wl), (ftnlen)sizeof(doublereal));
    e_wsfe();
    *ns1 = 1;
    *ns2 = 2;
    if (inprof_1.mpage != 3) {
	goto L174;
    }
    s_wsle(&io___2191);
    e_wsle();
    s_wsfe(&io___2192);
    e_wsfe();
    s_wsfe(&io___2193);
    do_fio(&c__1, (char *)&(*ns1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*binwm1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sc1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sl1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ipro_1.nf1, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___2194);
    do_fio(&c__1, (char *)&(*ns2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*binwm2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sc2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sl2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ipro_1.nf2, (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsle(&io___2195);
    e_wsle();
    s_wsfe(&io___2196);
    do_fio(&c__1, (char *)&(*ns1), (ftnlen)sizeof(integer));
    e_wsfe();
    i__1 = inprof_1.nl1;
    for (iln = 1; iln <= i__1; ++iln) {
/* L155: */
	s_wsfe(&io___2198);
	do_fio(&c__1, (char *)&wll1[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ewid1[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&depth1[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&kks[(iln << 1) + 1], (ftnlen)sizeof(integer));
	e_wsfe();
    }
    s_wsle(&io___2199);
    e_wsle();
    s_wsfe(&io___2200);
    do_fio(&c__1, (char *)&(*ns2), (ftnlen)sizeof(integer));
    e_wsfe();
    i__1 = inprof_1.nl2;
    for (iln = 1; iln <= i__1; ++iln) {
/* L151: */
	s_wsfe(&io___2201);
	do_fio(&c__1, (char *)&wll2[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ewid2[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&depth2[iln], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&kks[(iln << 1) + 2], (ftnlen)sizeof(integer));
	e_wsfe();
    }
L174:
    s_wsle(&io___2202);
    e_wsle();
    s_wsle(&io___2203);
    e_wsle();
    nstot = *nsp1 + *nsp2;
    if (nstot > 0) {
	s_wsfe(&io___2205);
	e_wsfe();
    }
    for (kp = 1; kp <= 2; ++kp) {
	if (*nsp1 + kp - 1 == 0) {
	    goto L188;
	}
/* Computing 2nd power */
	i__1 = kp - 2;
	if (*nsp2 + i__1 * i__1 == 0) {
	    goto L188;
	}
	nspot = *nsp1;
	if (kp == 2) {
	    nspot = *nsp2;
	}
	i__1 = nspot;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* L187: */
	    s_wsfe(&io___2209);
	    do_fio(&c__1, (char *)&kp, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&xlat[kp + (i__ << 1)], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&xlong[kp + (i__ << 1)], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&radsp[kp + (i__ << 1)], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temsp[kp + (i__ << 1)], (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
	}
L188:
	s_wsle(&io___2210);
	e_wsle();
    }
    if (*ncl == 0) {
	goto L67;
    }
    s_wsfe(&io___2211);
    e_wsfe();
    i__1 = *ncl;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L68: */
	s_wsfe(&io___2212);
	do_fio(&c__1, (char *)&xcl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ycl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&zcl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rcl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&op1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&fcl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&edens[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&xmue[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&encl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&dens[i__], (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    s_wsle(&io___2213);
    e_wsle();
L67:
    s_wsfe(&io___2214);
    e_wsfe();
    s_wsfe(&io___2215);
    do_fio(&c__1, (char *)&(*ns1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*sms1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sr1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*bolm1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xlg1), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2216);
    do_fio(&c__1, (char *)&(*ns2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*sms2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sr2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*bolm2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xlg2), (ftnlen)sizeof(doublereal));
    e_wsfe();
    np1 = *n1 + 1;
    np2 = *n1 + *n2 + 2;
    s_wsle(&io___2219);
    e_wsle();
    s_wsfe(&io___2220);
    e_wsfe();
    s_wsfe(&io___2221);
    e_wsfe();
    s_wsfe(&io___2222);
    e_wsfe();
    s_wsfe(&io___2223);
    do_fio(&c__1, (char *)&mmsave[np1], (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&mmsave[np2], (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*sbrh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sbrc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sm1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sm2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phperi), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pconsc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pconic), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsle(&io___2224);
    e_wsle();
    if (*stdev == 0. || inprof_1.mpage != 1) {
	goto L246;
    }
    s_wsfe(&io___2225);
    e_wsfe();
    s_wsfe(&io___2226);
    do_fio(&c__1, (char *)&(*stdev), (ftnlen)sizeof(doublereal));
    e_wsfe();
L246:
    s_wsle(&io___2227);
    e_wsle();
    if (inprof_1.mpage == 1) {
	s_wsfe(&io___2228);
	e_wsfe();
    }
    if (inprof_1.mpage == 2) {
	s_wsfe(&io___2229);
	e_wsfe();
    }
    if (inprof_1.mpage == 4) {
	s_wsfe(&io___2230);
	e_wsfe();
    }
    return 0;
} /* wrhead_ */

/* Subroutine */ int wrlci_(char *fn, integer *mpage, integer *nref, integer *
	mref, integer *ifsmv1, integer *ifsmv2, integer *icor1, integer *
	icor2, integer *ld, integer *jdphs, doublereal *hjd0, doublereal *
	period, doublereal *dpdt, doublereal *pshift, doublereal *stddev, 
	integer *noise, doublereal *seed, doublereal *jdstrt, doublereal *
	jdend, doublereal *jdinc, doublereal *phstrt, doublereal *phend, 
	doublereal *phinc, doublereal *phnorm, integer *mode, integer *ipb, 
	integer *ifat1, integer *ifat2, integer *n1, integer *n2, doublereal *
	perr0, doublereal *dperdt, doublereal *the, doublereal *vunit, 
	doublereal *e, doublereal *sma, doublereal *f1, doublereal *f2, 
	doublereal *vga, doublereal *xincl, doublereal *gr1, doublereal *gr2, 
	doublereal *abunin, doublereal *tavh, doublereal *tavc, doublereal *
	alb1, doublereal *alb2, doublereal *phsv, doublereal *pcsv, 
	doublereal *rm, doublereal *xbol1, doublereal *xbol2, doublereal *
	ybol1, doublereal *ybol2, integer *iband, doublereal *hla, doublereal 
	*cla, doublereal *x1a, doublereal *x2a, doublereal *y1a, doublereal *
	y2a, doublereal *el3, doublereal *opsf, doublereal *mzero, doublereal 
	*factor, doublereal *wla, integer *nsp1, doublereal *xlat1, 
	doublereal *xlong1, doublereal *radsp1, doublereal *temsp1, integer *
	nsp2, doublereal *xlat2, doublereal *xlong2, doublereal *radsp2, 
	doublereal *temsp2, ftnlen fn_len)
{
    /* Format strings */
    static char fmt_1[] = "(8(i1,1x))";
    static char fmt_2[] = "(i1,f15.6,d15.10,d13.6,f10.4,d10.4,i2,f11.0)";
    static char fmt_3[] = "(f14.6,f15.6,f13.6,4f12.6)";
    static char fmt_4[] = "(4i2,2i4,f13.6,d12.5,f7.5,f8.2)";
    static char fmt_5[] = "(f6.5,d13.6,2f10.4,f10.4,f9.3,2f7.3,f7.2)";
    static char fmt_6[] = "(2(f7.4,1x),2f7.3,3d13.6,4f7.3)";
    static char fmt_7[] = "(i3,2f10.5,4f10.6,f8.4,d10.4,f8.3,f8.4,f9.6)";
    static char fmt_8[] = "(4f9.5)";
    static char fmt_9[] = "(1x,f4.0)";
    static char fmt_10[] = "(f4.0)";
    static char fmt_11[] = "(i1)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_wsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_wsfe(void), f_clos(cllist *);

    /* Local variables */
    static integer i__;

    /* Fortran I/O blocks */
    static cilist io___2231 = { 0, 1, 0, fmt_1, 0 };
    static cilist io___2232 = { 0, 1, 0, fmt_2, 0 };
    static cilist io___2233 = { 0, 1, 0, fmt_3, 0 };
    static cilist io___2234 = { 0, 1, 0, fmt_4, 0 };
    static cilist io___2235 = { 0, 1, 0, fmt_5, 0 };
    static cilist io___2236 = { 0, 1, 0, fmt_6, 0 };
    static cilist io___2237 = { 0, 1, 0, fmt_7, 0 };
    static cilist io___2239 = { 0, 1, 0, fmt_8, 0 };
    static cilist io___2240 = { 0, 1, 0, fmt_9, 0 };
    static cilist io___2241 = { 0, 1, 0, fmt_8, 0 };
    static cilist io___2242 = { 0, 1, 0, fmt_9, 0 };
    static cilist io___2243 = { 0, 1, 0, fmt_10, 0 };
    static cilist io___2244 = { 0, 1, 0, fmt_11, 0 };


    /* Parameter adjustments */
    --temsp2;
    --radsp2;
    --xlong2;
    --xlat2;
    --temsp1;
    --radsp1;
    --xlong1;
    --xlat1;

    /* Function Body */
/* L1: */
/* L2: */
/* L3: */
/* L4: */
/* L5: */
/* L6: */
/* L7: */
/* L8: */
/* L9: */
/* L10: */
/* L11: */
    o__1.oerr = 0;
    o__1.ounit = 1;
    o__1.ofnmlen = fn_len;
    o__1.ofnm = fn;
    o__1.orl = 0;
    o__1.osta = "UNKNOWN";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_wsfe(&io___2231);
    do_fio(&c__1, (char *)&(*mpage), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*nref), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*mref), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifsmv1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifsmv2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*icor1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*icor2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ld), (ftnlen)sizeof(integer));
    e_wsfe();
    s_wsfe(&io___2232);
    do_fio(&c__1, (char *)&(*jdphs), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*hjd0), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*period), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dpdt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pshift), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*stddev), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*noise), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*seed), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2233);
    do_fio(&c__1, (char *)&(*jdstrt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*jdend), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*jdinc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phstrt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phend), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phinc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phnorm), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2234);
    do_fio(&c__1, (char *)&(*mode), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ipb), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifat1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ifat2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n1), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*n2), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*perr0), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dperdt), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*the), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*vunit), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2235);
    do_fio(&c__1, (char *)&(*e), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*sma), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*f1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*f2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*vga), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xincl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*gr1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*gr2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*abunin), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2236);
    do_fio(&c__1, (char *)&(*tavh), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*tavc), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*alb1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*alb2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*phsv), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pcsv), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*rm), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xbol1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*xbol2), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ybol1), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ybol2), (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2237);
    do_fio(&c__1, (char *)&(*iband), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*hla), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*cla), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*x1a), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*x2a), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*y1a), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*y2a), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*el3), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*opsf), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*mzero), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*factor), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*wla), (ftnlen)sizeof(doublereal));
    e_wsfe();
    i__1 = *nsp1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___2239);
	do_fio(&c__1, (char *)&xlat1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&xlong1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&radsp1[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&temsp1[i__], (ftnlen)sizeof(doublereal));
	e_wsfe();
/* L95: */
    }
    s_wsfe(&io___2240);
    do_fio(&c__1, (char *)&c_b1630, (ftnlen)sizeof(doublereal));
    e_wsfe();
    i__1 = *nsp2;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s_wsfe(&io___2241);
	do_fio(&c__1, (char *)&xlat2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&xlong2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&radsp2[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&temsp2[i__], (ftnlen)sizeof(doublereal));
	e_wsfe();
/* L96: */
    }
    s_wsfe(&io___2242);
    do_fio(&c__1, (char *)&c_b1630, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2243);
    do_fio(&c__1, (char *)&c_b1639, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___2244);
    do_fio(&c__1, (char *)&c__9, (ftnlen)sizeof(integer));
    e_wsfe();
    cl__1.cerr = 0;
    cl__1.cunit = 1;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* wrlci_ */

