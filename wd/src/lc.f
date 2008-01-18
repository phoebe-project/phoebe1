      program lc
c
c  Main program for computing light and radial velocity curves,
c      line profiles, and images
c
c  Version of March 8, 2007
C
C     TO PRINT VELOCITIES IN KM/SEC, SET VUNIT=1.
C     TO PRINT NORMALIZED VELOCITIES IN SAME COLUMNS, SET VUNIT EQUAL TO
C     DESIRED VELOCITY UNIT IN KM/SEC.
C
C     PARAMETER PSHIFT IS DEFINED AS THE PHASE AT WHICH PRIMARY
C     CONJUNCTION (STAR 1 AWAY FROM OBSERVER) WOULD OCCUR IF THE
C     ARGUMENT OF PERIASTRON WERE 2 pi radians. SINCE THE NOMINAL VALUE
C     OF THIS QUANTITY IS ZERO, PSHIFT MAY BE USED TO INTRODUCE AN
C     ARBITRARY PHASE SHIFT.

      implicit real*8(a-h,o-z)

cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c
c                      ARRAY DIMENSIONING WRAPPER
c                            March 6, 2007
c
c     The following parameters determine array sizing in the program.
c     There is no need to change any numbers in the code except these
c     in order to accomodate finer grids.
c
c        Nmax    ..    maximum grid fineness (parameters N1, N2)
c                        default:   Nmax =     60
c      igsmax    ..    maximum grid size depending on the grid fineness,
c                        i.e. igsmax=762 for N=30, 3011 for N=60 etc.
c                        default: igsmax =   3011
c      lpimax    ..    maximum dimension of line profile input arrays
c                        default: lpimax =    100
c      lpomax    ..    maximum dimension of line profile output arrays
c                        default: lpomax = 100000
c      ispmax    ..    maximum number of spots
c                        default: ispmax =    100
c      iclmax    ..    maximum number of clouds
c                        default: iclmax =    100
c
      parameter (Nmax=     100)
      parameter (igsmax=  8331)
      parameter (lpimax=   100)
      parameter (lpomax=100000)
      parameter (ispmax=   100)
      parameter (iclmax=   100)
c
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c
c     Other array dimensions that are set automatically are listed
c     below and should not be changed, as the above parameter statements
c     determine their values.
c
c        MMmax    ..    dimension of the array MMSAVE
c        immax    ..    maximum number of surface grid points in sky
c                       images
c       ifrmax    ..    dimension of the Fourier arrays
c
      parameter (MMmax=2*Nmax+4)
      parameter (immax=4*igsmax+100)
      parameter (ifrmax=4*Nmax)
c
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c
c     Finally, the following dimensions are considered static and
c     their size does not depend on parameters.
c
      dimension rad(4),drdo(4),xtha(4),xfia(4),po(2)
      dimension abun(19),glog(11),grand(250800),plcof(1250)
      dimension message(2,4)
      dimension aa(20),bb(20)
c
c     Nothing needs to be changed beyond this point to accomodate
c     finer grids.
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

      dimension rv(igsmax),grx(igsmax),gry(igsmax),grz(igsmax),
     $rvq(igsmax),grxq(igsmax),gryq(igsmax),grzq(igsmax),slump1(igsmax),
     $slump2(igsmax),fr1(igsmax),fr2(igsmax),glump1(igsmax),
     $glump2(igsmax),xx1(igsmax),xx2(igsmax),yy1(igsmax),yy2(igsmax),
     $zz1(igsmax),zz2(igsmax),grv1(igsmax),grv2(igsmax),rftemp(igsmax),
     $rf1(igsmax),rf2(igsmax),csbt1(igsmax),csbt2(igsmax),gmag1(igsmax),
     $gmag2(igsmax),glog1(igsmax),glog2(igsmax)
      dimension dvks1(lpimax),dvks2(lpimax),wll1(lpimax),wll2(lpimax),
     $tau1(lpimax),tau2(lpimax),emm1(lpimax),emm2(lpimax),ewid1(lpimax),
     $ewid2(lpimax),depth1(lpimax),depth2(lpimax),hbarw1(lpimax),
     $hbarw2(lpimax)
      dimension fbin1(lpomax),fbin2(lpomax),delv1(lpomax),delv2(lpomax),
     $count1(lpomax),count2(lpomax),delwl1(lpomax),delwl2(lpomax),
     $resf1(lpomax),resf2(lpomax),wl1(lpomax),wl2(lpomax),taug(lpomax),
     $emmg(lpomax)
      dimension XLAT(2,ispmax),xlong(2,ispmax)
      dimension xcl(iclmax),ycl(iclmax),zcl(iclmax),rcl(iclmax),
     $op1(iclmax),fcl(iclmax),dens(iclmax),encl(iclmax),edens(iclmax),
     $xmue(iclmax)
      dimension mmsave(MMmax),snth(2*Nmax),csth(2*Nmax),
     $snfi(2*igsmax+100),csfi(2*igsmax+100)
      dimension yskp(immax),zskp(immax)
      dimension theta(ifrmax),rho(ifrmax)
      dimension hld(igsmax),tld(2*igsmax)

      common /abung/ abun,glog
      common /arrayleg/ grand,istart
      common /planckleg/ plcof
      common /atmmessages/ message,komp
      common /ramprange/ tlowtol,thightol,glowtol,ghightol
      COMMON /FLVAR/ PSHIFT,DP,EF,EFC,ECOS,perr0,PHPER,pconsc,pconic,
     $PHPERI,VSUM1,VSUM2,VRA1,VRA2,VKM1,VKM2,VUNIT,vfvu,trc,qfacd
      COMMON /DPDX/ DPDX1,DPDX2,PHSV,PCSV
      COMMON /ECCEN/ E,A,PERIOD,VGA,SINI,VF,VFAC,VGAM,VOL1,VOL2,IFC
      COMMON /KFAC/ KFF1,KFF2,kfo1,kfo2
      COMMON /INVAR/ KH,IPB,IRTE,NREF,IRVOL1,IRVOL2,mref,ifsmv1,ifsmv2,
     $icor1,icor2,ld,ncl,jdphs,ipc
      COMMON /SPOTS/ SINLAT(2,ispmax),COSLAT(2,ispmax),SINLNG(2,ispmax),
     $COSLNG(2,ispmax),RADSP(2,ispmax),temsp(2,ispmax),xlng(2,ispmax),
     $kks(2,ispmax),Lspot(2,ispmax)
      common /cld/ acm,opsf
      common /ardot/ dperdt,hjd,hjd0,perr
      common /prof2/ du1,du2,du3,du4,binw1,binw2,sc1,sc2,sl1,sl2,
     $clight
      common /inprof/ in1min,in1max,in2min,in2max,mpage,nl1,nl2
      common /ipro/ nbins,nl,inmax,inmin,nf1,nf2
      common /NSPT/ NSP1,NSP2

      data xtha(1),xtha(2),xtha(3),xtha(4),xfia(1),xfia(2),xfia(3),
     $xfia(4)/0.d0,1.570796d0,1.570796d0,1.570796d0,
     $0.d0,0.d0,1.5707963d0,3.14159365d0/
c
c           Bandpass Label Assignments for Stellar Atmospheres
c
c    Label   Bandpass   Reference for Response Function
c    -----   --------   -------------------------------
c       1        u      Crawford, D.L. and Barnes, J.V. 1974, AJ, 75, 978
c       2        v          "                "           "
c       3        b          "                "           "
c       4        y          "                "           "
c       5        U      Buser, R. 1978, Ang, 62, 411
c       6        B      Azusienis and Straizys 1969, Sov. Astron., 13, 316
c       7        V          "             "                "
c       8        R      Johnson, H.L. 1965, ApJ, 141, 923
c       9        I         "            "    "
c      10        J         "            "    "
c      11        K         "            "    "
c      12        L         "            "    "
c      13        M         "            "    "
c      14        N         "            "    "
c      15        R_c    Bessell, M.S. 1983, PASP, 95, 480
c      16        I_c       "            "    "
c      17      230      Kallrath, J., Milone, E.F., Terrell, D., Young, A.T.
c                          1998, ApJ, 508, 308
c      18      250         "             "             "           "
c      19      270         "             "             "           "
c      20      290         "             "             "           "
c      21      310         "             "             "           "
c      22      330         "             "             "           "
c      23     'TyB'    Tycho catalog B
c      24     'TyV'    Tycho catalog V
c      25     'HIP'    Hipparcos catalog
c

  205 format('**********************************************************
     $************')
  204 format('*************  Next block of output   ********************
     $************')
   79 format(6x,'JD',17x,'Phase     light 1     light 2     (1+2+3)    n
     $orm lite   dist      mag+K')
   96 FORMAT(6x,'JD',13x,'Phase',5x,'r1pol',6x,'r1pt',5x,'r1sid',5x,'r1b
     $ak',5x,'r2pol',5x,'r2pt',6x,'r2sid',5x,'r2bak')
  296 format(f14.6,f13.5,8f10.5)
   45 FORMAT(6x,'JD',14x,'Phase     V Rad 1     V Rad 2      del V1
     $ del V2   V1 km/s      V2 km/s')
   93 format(f14.6,f13.5,4f12.6,2d13.4)
   47 FORMAT(2x,'band',7x,'L1',9x,'L2',7x,'x1',6x,'x2',6x,'y1',6x,
     $'y2',6x,'el3     opsf      m zero   factor',2x,'wv lth')
   48 FORMAT('  ecc',5x,'s-m axis',7x,'F1',9x,'F2',7x,'Vgam',7x,
     $'Incl',6x,'g1',6x,'g2  Nspot1 Nspot 2',4x,'[M/H]')
   54 FORMAT(2x,'T1',6x,'T2',5x,'Alb 1  Alb 2',4x,'Pot 1',8x,'Pot 2',
     $11x,'M2/M1',2x,'x1(bolo) x2(bolo) y1(bolo) y2(bolo)')
   33 FORMAT(I4,I5,I6,I6,I7,I5,f13.6,d14.5,f9.5,f10.2,d16.4)
   74 FORMAT(' DIMENSIONLESS RADIAL VELOCITIES CONTAIN FACTOR P/(2PI*A)'
     $)
   43 format(91x,'superior',5x,'inferior')
   44 format(76x,'periastron',2x,'conjunction',2x,'conjunction')
   46 FORMAT('grid1/4    grid2/4',2X,'polar sbr 1',3X,'polar sbr 2'
     $,3X,'surf. area 1',2X,'surf. area 2',7X,'phase',8X,
     $'phase',8x,'phase')
   50 FORMAT(40H PRIMARY COMPONENT EXCEEDS CRITICAL LOBE)
   51 FORMAT(42H SECONDARY COMPONENT EXCEEDS CRITICAL LOBE)
   41 FORMAT('star',4X,'r pole',5X,'deriv',5X,'r point',5X,'deriv',
     $6X,'r side',6X,'deriv',5X,'r back',6X,'deriv')
    2 FORMAT(F6.5,d13.6,2F10.4,F10.4,f9.3,2f7.3,f7.2)
    5 FORMAT(F6.5,d13.6,2F11.4,F11.4,F10.3,2f8.3,i5,i7,f10.2)
    6 FORMAT(2(F7.4,1X),2f7.3,3d13.6,4F7.3)
    8 FORMAT(f7.4,f8.4,2F7.3,3d13.6,f8.3,f9.3,f9.3,f9.3)
    3 FORMAT(f15.6,F15.5,4F12.8,F10.5,f10.4)
    1 FORMAT(4I2,2I4,f13.6,d12.5,f7.5,F8.2)
    4 FORMAT(i3,2F10.5,4F7.3,F8.4,d10.4,F8.3,F8.4,f9.6)
   34 FORMAT(i5,1X,2F11.5,4f8.3,F9.4,d11.4,F9.3,F9.4,f9.6)
   49 FORMAT(' PROGRAM SHOULD NOT BE USED IN MODE 1 OR 3 WITH NON-ZERO E
     $CCENTRICITY')
   10 FORMAT('MODE   IPB  IFAT1 IFAT2   N1   N2',4x,'Arg. Per',7x,'dPerd
     $t',4x,'Th e',4x,'V UNIT(km/s)    V FAC')
  148 format('   mpage  nref   mref   ifsmv1   ifsmv2   icor1   icor2
     $ld')
  171 format('JDPHS',5x,'J.D. zero',7x,'Period',11x,'dPdt',
     $6x,'Ph. shift',3x,'fract. sd.',2x,'noise',5x,'seed')
  244 format('Note: The light curve output contains simulated observa',
     $'tional scatter, as requested,')
  245 format('with standard deviation',f9.5,' of light at the reference'
     $,' phase.')
  149 format(i6,2i7,i8,i9,i9,i8,i6)
  170 format(i3,f17.6,d18.10,d14.6,f10.4,d13.4,i5,f13.0)
   40 FORMAT(I3,8F11.5)
   94 FORMAT(i6,i11,4F14.6,F13.6,f13.6,f13.6)
   84 FORMAT(1X,I4,4F12.5)
   85 FORMAT(4f9.5)
   83 FORMAT(1X,'STAR  CO-LATITUDE  LONGITUDE  SPOT RADIUS  TEMP. FACTOR
     $')
  150 format(' Star',9x,'M/Msun   (Mean Radius)/Rsun',5x,'M Bol',4x,'Log
     $ g (cgs)')
  250 format(4x,I1,4x,f12.3,11x,f7.2,6x,f6.2,8x,f5.2)
  350 format(' Primary star exceeds outer contact surface')
  351 format(' Secondary star exceeds outer contact surface')
   22 format(8(i1,1x))
  649 format(i1,f15.6,d15.10,d13.6,f10.4,d10.4,i2,f11.0)
   63 format(3f9.4,f7.4,d11.4,f9.4,d11.3,f9.4,f7.3)
   64 format(3f10.4,f9.4,d12.4,f10.4,d12.4,f9.4,f9.3,d12.4)
   69 format('      xcl       ycl       zcl      rcl       op1         f
     $cl        ne       mu e      encl     dens')
 2048 format(d11.5,f9.4,f9.2,i3)
 2049 format(i3,d14.5,f18.2,f20.2,i14)
  907 format(6x,'del v',6x,'del wl (mic.)',7x,'wl',9x,'profile',6x,'res
     $flux')
  903 format(6f14.7)
   92 format('Phase =',f14.6)
  142 format('star',4x,'bin width (microns)',3x,'continuum scale',4x,'co
     $ntinuum slope',2x,'nfine')
  167 format(30x,'star',i2)
  138 format(f9.6,d12.5,f10.5,i5)
  152 format(f20.6,d23.5,17x,f13.5,i6)
  157 format('star ',i1,'   line wavelength',4x,'equivalent width (micro
     $ns)',5x,'rect. line depth',2x,'kks')
  217 format(f14.6,f15.6,f13.6,4f12.6)
  218 format(f14.6,f16.6,f14.6,4f12.6)
  219 format(5x,'JD start',9x,'JD stop',6x,'JD incr',6x,
     $'Ph start',4x,'Ph. stop',5x,'Ph incr',5x,'Ph norm')
  283 format('log g below ramp range for at least one point',
     $' on star',i2,', black body applied locally.')
  284 format('log g above ramp range for at least one point',
     $' on star',i2,', black body applied locally.')
  285 format('T above ramp range for at least one',
     $' point on star',i2,', black body applied locally.')
  286 format('T below ramp range for at least one point',
     $' on star',i2,', black body applied locally.')
  287 format('Input [M/H] = ',f6.3,' is not a value recognized by ',
     $'the program. Replaced by ',f5.2)
  128 format('HJD = ',f14.5,'    Phase = ',f14.5)
  131 format(3x,'Y Sky Coordinate',4x,'Z Sky Coordinate')
  130 format(f16.6,f20.6)
      ot=1.d0/3.d0
      pi=dacos(-1.d0)
      clight=2.99792458d5
      en0=6.0254d23
      rsuncm=6.960d10
ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c  Ramp ranges are set below. The following values seem to work.
c  They may be changed.
      tlowtol=1500.d0
      thightol=50000.d0
      glowtol=4.0d0
      ghightol=4.0d0
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      abun(1)=1.d0
      abun(2)=0.5d0
      abun(3)=0.3d0
      abun(4)=0.2d0
      abun(5)=0.1d0
      abun(6)=0.0d0
      abun(7)=-0.1d0
      abun(8)=-0.2d0
      abun(9)=-0.3d0
      abun(10)=-0.5d0
      abun(11)=-1.0d0
      abun(12)=-1.5d0
      abun(13)=-2.0d0
      abun(14)=-2.5d0
      abun(15)=-3.0d0
      abun(16)=-3.5d0
      abun(17)=-4.0d0
      abun(18)=-4.5d0
      abun(19)=-5.0d0
      glog(1)=0.0d0
      glog(2)=0.5d0
      glog(3)=1.0d0
      glog(4)=1.5d0
      glog(5)=2.0d0
      glog(6)=2.5d0
      glog(7)=3.0d0
      glog(8)=3.5d0
      glog(9)=4.0d0
      glog(10)=4.5d0
      glog(11)=5.0d0
      nn=100
      gau=0.d0
      open(unit=22,file='atmcof.dat',status='old')
      read(22,*) grand
      open(unit=23,file='phoebe_atmcofplanck.dat',status='old')
      read(23,*) plcof
      close(22)
      close(23)
c     open(unit=5,file='lcin.active',status='old')
c     open(unit=6,file='lcout.active')
      ibef=0
      DO 1000 IT=1,1000
      KH=17
      read(5,22) mpage,nref,mref,ifsmv1,ifsmv2,icor1,icor2,ld
      if(mpage.ne.9) goto 414
      close(5)
      close(6)
      stop
  414 continue
      if(ibef.eq.0) goto 335
      write(6,*)
      write(6,*)
      write(6,*)
      write(6,*)
      write(6,*)
      write(6,204)
      write(6,*)
      write(6,*)
      write(6,*)
      write(6,*)
  335 ibef=1
      message(1,1)=0
      message(1,2)=0
      message(2,1)=0
      message(2,2)=0
      message(1,3)=0
      message(1,4)=0
      message(2,3)=0
      message(2,4)=0
      read(5,649) jdphs,hjd0,period,dpdt,pshift,stdev,noise,seed
      read(5,217) hjdst,hjdsp,hjdin,phstrt,phstop,phin,phn
      READ(5,1) MODE,IPB,IFAT1,IFAT2,N1,N2,perr0,dperdt,the,VUNIT
      READ(5,2) E,A,F1,F2,VGA,XINCL,GR1,GR2,abunin
      read(5,6) tavh,tavc,alb1,alb2,poth,potc,rm,xbol1,xbol2,ybol1,
     $ybol2
      READ(5,4)iband,HLUM,CLUM,XH,xc,yh,yc,EL3,opsf,ZERO,FACTOR,wl
      acm=rsuncm*a
c***************************************************************
c  The following lines take care of abundances that may not be among
c  the 19 Kurucz values (see abun array). abunin is reset at the allowed value nearest
c  the input value.
      call binnum(abun,19,abunin,iab)
      dif1=abunin-abun(iab)
      if(iab.eq.19) goto 702
      dif2=abun(iab+1)-abun(iab)
      dif=dif1/dif2
      if((dif.ge.0.d0).and.(dif.le.0.5d0)) goto 702
      iab=iab+1
  702 continue
      if(dif1.ne.0.d0) write(6,287) abunin,abun(iab)
      abunin=abun(iab)
      istart=1+(iab-1)*13200
c***************************************************************
      nf1=1
      nf2=1
      if(mpage.ne.3) goto 897
      colam=clight/wl
      read(5,2048) binwm1,sc1,sl1,nf1
      binw1=colam*binwm1
      do 86 iln=1,lpimax
      read(5,138) wll1(iln),ewid1(iln),depth1(iln),kks(1,iln)
      if(wll1(iln).lt.0.d0) goto 89
      emm1(iln)=0.d0
      if(depth1(iln).lt.0.d0) emm1(iln)=depth1(iln)
      tau1(iln)=0.d0
      if(depth1(iln).gt.0.d0) tau1(iln)=-dlog(1.d0-depth1(iln))
      hbarw1(iln)=0.d0
      if(depth1(iln).ne.0.d0) hbarw1(iln)=.5d0*clight*ewid1(iln)/
     $(wll1(iln)*dabs(depth1(iln)))
      nl1=iln
   86 continue
   89 continue
      read(5,2048) binwm2,sc2,sl2,nf2
      binw2=colam*binwm2
      do 99 iln=1,lpimax
      read(5,138) wll2(iln),ewid2(iln),depth2(iln),kks(2,iln)
      if(wll2(iln).lt.0.d0) goto 91
      emm2(iln)=0.d0
      if(depth2(iln).lt.0.d0) emm2(iln)=depth2(iln)
      tau2(iln)=0.d0
      if(depth2(iln).gt.0.d0) tau2(iln)=-dlog(1.d0-depth2(iln))
      hbarw2(iln)=0.d0
      if(depth2(iln).ne.0.d0) hbarw2(iln)=.5d0*clight*ewid2(iln)/
     $(wll2(iln)*dabs(depth2(iln)))
      nl2=iln
   99 continue
   91 continue
      do 622 iln=1,nl1
      flam=(wll1(iln)/wl)**2
  622 dvks1(iln)=clight*(flam-1.d0)/(flam+1.d0)
      do 623 iln=1,nl2
      flam=(wll2(iln)/wl)**2
  623 dvks2(iln)=clight*(flam-1.d0)/(flam+1.d0)
  897 continue
      NSP1=0
      NSP2=0
      DO 88 KP=1,2
      DO 87 I=1,ispmax
      READ(5,85)XLAT(KP,I),XLONG(KP,I),RADSP(KP,I),TEMSP(KP,I)
      xlng(kp,i)=xlong(kp,i)
      IF(XLAT(KP,I).GE.200.d0) GOTO 88
      SINLAT(KP,I)=dsin(XLAT(KP,I))
      COSLAT(KP,I)=dcos(XLAT(KP,I))
      SINLNG(KP,I)=dsin(XLONG(KP,I))
      COSLNG(KP,I)=dcos(XLONG(KP,I))
      IF(KP.EQ.1)NSP1=NSP1+1
   87 IF(KP.EQ.2)NSP2=NSP2+1
   88 CONTINUE
      ncl=0
      do 62 i=1,iclmax
      read(5,63) xcl(i),ycl(i),zcl(i),rcl(i),op1(i),fcl(i),edens(i),
     $xmue(i),encl(i)
      if(xcl(i).gt.100.d0) goto 66
      ncl=ncl+1
      dens(i)=edens(i)*xmue(i)/en0
   62 continue
   66 dint1=pi*(1.d0-xbol1/3.d0)
      dint2=pi*(1.d0-xbol2/3.d0)
      if(ld.eq.2) DINT1=dint1+PI*2.d0*ybol1/9.d0
      if(ld.eq.2) DINT2=dint2+PI*2.d0*ybol2/9.d0
      if(ld.eq.3) dint1=dint1-.2d0*pi*ybol1
      if(ld.eq.3) dint2=dint2-.2d0*pi*ybol2
      NSTOT=NSP1+NSP2
      NP1=N1+1
      NP2=N1+N2+2
      IRTE=0
      IRVOL1=0
      IRVOL2=0
      do 421 imm=1,MMmax
  421 mmsave(imm)=0
      nn1=n1
      CALL SINCOS(1,nn1,N1,SNTH,CSTH,SNFI,CSFI,MMSAVE)
      CALL SINCOS(2,N2,N1,SNTH,CSTH,SNFI,CSFI,MMSAVE)
      hjd=hjd0
      CALL modlog(RV,GRX,GRY,GRZ,RVQ,GRXQ,GRYQ,GRZQ,MMSAVE,FR1,FR2,HLD,
     $rm,poth,potc,gr1,gr2,alb1,alb2,n1,n2,f1,f2,mod,xincl,the,mode,
     $snth,csth,snfi,csfi,grv1,grv2,xx1,yy1,zz1,xx2,yy2,zz2,glump1,
     $glump2,csbt1,csbt2,gmag1,gmag2,glog1,glog2)
      CALL VOLUME(VOL1,RM,POTH,DP,F1,nn1,N1,1,RV,GRX,GRY,GRZ,RVQ,
     $GRXQ,GRYQ,GRZQ,MMSAVE,FR1,FR2,HLD,SNTH,CSTH,SNFI,CSFI,SUMMD,SMD,
     $GRV1,GRV2,XX1,YY1,ZZ1,XX2,YY2,ZZ2,CSBT1,CSBT2,GLUMP1,GLUMP2,
     $GMAG1,GMAG2,glog1,glog2,GR1,1)
      CALL VOLUME(VOL2,RM,POTC,DP,F2,N2,N1,2,RV,GRX,GRY,GRZ,RVQ,
     $GRXQ,GRYQ,GRZQ,MMSAVE,FR1,FR2,HLD,SNTH,CSTH,SNFI,CSFI,SUMMD,SMD,
     $GRV1,GRV2,XX1,YY1,ZZ1,XX2,YY2,ZZ2,CSBT1,CSBT2,GLUMP1,GLUMP2,
     $GMAG1,GMAG2,glog1,glog2,GR2,1)
      if(e.eq.0.d0) goto 117
      DAP=1.d0+E
      P1AP=POTH-2.d0*E*RM/(1.d0-E*E)
      VL1=VOL1
      CALL VOLUME(VL1,RM,P1AP,DAP,F1,nn1,N1,1,RV,GRX,GRY,GRZ,RVQ,
     $GRXQ,GRYQ,GRZQ,MMSAVE,FR1,FR2,HLD,SNTH,CSTH,SNFI,CSFI,SUMMD,SMD,
     $GRV1,GRV2,XX1,YY1,ZZ1,XX2,YY2,ZZ2,CSBT1,CSBT2,GLUMP1,GLUMP2,
     $GMAG1,GMAG2,glog1,glog2,GR1,2)
      DPDX1=(POTH-P1AP)*(1.d0-E*E)*.5d0/E
      P2AP=POTC-2.d0*E/(1.d0-E*E)
      VL2=VOL2
      CALL VOLUME(VL2,RM,P2AP,DAP,F2,N2,N1,2,RV,GRX,GRY,GRZ,RVQ,
     $GRXQ,GRYQ,GRZQ,MMSAVE,FR1,FR2,HLD,SNTH,CSTH,SNFI,CSFI,SUMMD,SMD,
     $GRV1,GRV2,XX1,YY1,ZZ1,XX2,YY2,ZZ2,CSBT1,CSBT2,GLUMP1,GLUMP2,
     $GMAG1,GMAG2,glog1,glog2,GR2,2)
      DPDX2=(POTC-P2AP)*(1.d0-E*E)*.5d0/E
  117 CONTINUE
      PHSV=POTH
      PCSV=POTC
      IF(E.EQ.0.d0) GOTO 61
      IF(MOD.EQ.1) WRITE(6,49)
   61 CONTINUE
      CALL BBL(RV,GRX,GRY,GRZ,RVQ,GRXQ,GRYQ,GRZQ,MMSAVE,FR1,FR2,HLD,
     $SLUMP1,SLUMP2,THETA,RHO,AA,BB,POTH,POTC,N1,N2,F1,F2,D,HLUM
     $,clum,xh,xc,yh,yc,gr1,gr2,wl,sm1,sm2,tpolh,tpolc,sbrh,sbrc,
     $tavh,tavc,alb1,alb2,xbol1,xbol2,ybol1,ybol2,phn,rm,xincl,
     $hot,cool,snth,csth,snfi,csfi,tld,glump1,glump2,xx1,xx2,yy1,yy2,
     $zz1,zz2,dint1,dint2,grv1,grv2,rftemp,rf1,rf2,csbt1,csbt2,gmag1,
     $gmag2,glog1,glog2,fbin1,fbin2,delv1,delv2,count1,count2,delwl1,
     $delwl2,resf1,resf2,wl1,wl2,dvks1,dvks2,tau1,tau2,emm1,emm2,hbarw1,
     $hbarw2,xcl,ycl,zcl,rcl,op1,fcl,dens,encl,edens,taug,emmg,yskp,
     $zskp,mode,iband,ifat1,ifat2,1)
      KH=0
      if(kfo1.eq.0) goto 380
      write(6,350)
      goto 381
  380 IF(KFF1.EQ.1) WRITE(6,50)
  381 if(kfo2.eq.0) goto 382
      write(6,351)
      goto 383
  382 IF(KFF2.EQ.1) WRITE(6,51)
  383 IF((KFF1+KFF2+kfo1+kfo2).GT.0) WRITE(6,*)
      write(6,148)
      write(6,149) mpage,nref,mref,ifsmv1,ifsmv2,icor1,icor2,ld
      write(6,*)
      write(6,171)
      write(6,170) jdphs,hjd0,period,dpdt,pshift,stdev,noise,seed
      write(6,*)
      write(6,219)
      write(6,218) hjdst,hjdsp,hjdin,phstrt,phstop,phin,phn
      write(6,*)
      WRITE(6,10)
      WRITE(6,33)MODE,IPB,IFAT1,IFAT2,N1,N2,perr0,dperdt,the,VUNIT,vfac
      WRITE(6,*)
      WRITE(6,48)
      WRITE(6,5)E,A,F1,F2,VGA,XINCL,GR1,GR2,NSP1,NSP2,abunin
      WRITE(6,*)
      WRITE(6,54)
      WRITE(6,8)TAVH,TAVC,ALB1,ALB2,PHSV,PCSV,rm,XBOL1,xbol2,ybol1,
     $ybol2
      WRITE(6,*)
      WRITE(6,47)
      WRITE(6,34)iband,HLUM,CLUM,XH,XC,yh,yc,el3,opsf,ZERO,FACTOR,wl
      ns1=1
      ns2=2
      if(mpage.ne.3) goto 174
      write(6,*)
      write(6,142)
      write(6,2049) ns1,binwm1,sc1,sl1,nf1
      write(6,2049) ns2,binwm2,sc2,sl2,nf2
      write(6,*)
      write(6,157) ns1
      do 155 iln=1,nl1
  155 write(6,152) wll1(iln),ewid1(iln),depth1(iln),kks(1,iln)
      write(6,*)
      write(6,157) ns2
      do 151 iln=1,nl2
  151 write(6,152) wll2(iln),ewid2(iln),depth2(iln),kks(2,iln)
  174 continue
      write(6,*)
      WRITE(6,*)
      IF(NSTOT.GT.0) WRITE(6,83)
      DO 188 KP=1,2
      IF((NSP1+KP-1).EQ.0) GOTO 188
      IF((NSP2+(KP-2)**2).EQ.0) GOTO 188
      NSPOT=NSP1
      IF(KP.EQ.2) NSPOT=NSP2
      DO 187 I=1,NSPOT
  187 WRITE(6,84)KP,XLAT(KP,I),XLONG(KP,I),RADSP(KP,I),TEMSP(KP,I)
  188 WRITE(6,*)
      if(ncl.eq.0) goto 67
      write(6,69)
      do 68 i=1,ncl
   68 write(6,64) xcl(i),ycl(i),zcl(i),rcl(i),op1(i),fcl(i),edens(i),
     $xmue(i),encl(i),dens(i)
      write(6,*)
   67 continue
      write(6,150)
      rr1=.6203505d0*vol1**ot
      rr2=.6203505d0*vol2**ot
      tav1=10000.d0*tavh
      tav2=10000.d0*tavc
      call mlrg(a,period,rm,rr1,rr2,tav1,tav2,sms1,sms2,sr1,sr2,
     $bolm1,bolm2,xlg1,xlg2)
      write(6,250) ns1,sms1,sr1,bolm1,xlg1
      write(6,250) ns2,sms2,sr2,bolm2,xlg2
      write(6,*)
      write(6,43)
      write(6,44)
      WRITE(6,46)
      WRITE(6,94) MMSAVE(NP1),MMSAVE(NP2),SBRH,SBRC,SM1,SM2,PHPERI,
     $pconsc,pconic
      WRITE(6,*)
      if(stdev.eq.0.d0.or.mpage.ne.1) goto 246
      write(6,244)
      write(6,245) stdev
  246 continue
      WRITE(6,*)
      ALL=HOT+COOL+EL3
      IF(MODE.EQ.-1) ALL=COOL+EL3
      if(mpage.eq.1) write(6,79)
      if(mpage.eq.2) write(6,45)
      if(mpage.eq.4) write(6,96)
      LL1=MMSAVE(N1)+1
      NPP2=NP2-1
      LL2=MMSAVE(NPP2)+1
      LLL1=MMSAVE(NP1)
      LLL2=MMSAVE(NP2)
      LLLL1=(LL1+LLL1)/2
      LLLL2=(LL2+LLL2)/2
      POTH=PHSV
      POTC=PCSV
      PO(1)=POTH
      PO(2)=POTC
      IF(E.EQ.0.d0) IRVOL1=1
      IF(E.EQ.0.d0) IRVOL2=1
      IF(E.EQ.0.d0) IRTE=1
      start=hjdst
      stopp=hjdsp
      step=hjdin
      if(jdphs.ne.2) goto 887
      start=phstrt
      stopp=phstop
      step=phin
  887 continue
      do 20 phjd=start,stopp,step
      hjdi=phjd
      phasi=phjd
      call jdph(hjdi,phasi,hjd0,period,dpdt,hjdo,phaso)
      hjd=hjdi
      phas=phasi
      if(jdphs.ne.1) hjd=hjdo
      if(jdphs.ne.2) phas=phaso
      CALL modlog(RV,GRX,GRY,GRZ,RVQ,GRXQ,GRYQ,GRZQ,MMSAVE,FR1,FR2,HLD,
     $rm,poth,potc,gr1,gr2,alb1,alb2,n1,n2,f1,f2,mod,xincl,the,mode,
     $snth,csth,snfi,csfi,grv1,grv2,xx1,yy1,zz1,xx2,yy2,zz2,glump1,
     $glump2,csbt1,csbt2,gmag1,gmag2,glog1,glog2)
      CALL BBL(RV,GRX,GRY,GRZ,RVQ,GRXQ,GRYQ,GRZQ,MMSAVE,FR1,FR2,HLD,
     $SLUMP1,SLUMP2,THETA,RHO,AA,BB,POTH,POTC,N1,N2,F1,F2,D,hlum,
     $clum,xh,xc,yh,yc,gr1,gr2,wl,sm1,sm2,tpolh,tpolc,sbrh,sbrc,
     $tavh,tavc,alb1,alb2,xbol1,xbol2,ybol1,ybol2,phas,rm,xincl,
     $hot,cool,snth,csth,snfi,csfi,tld,glump1,glump2,xx1,xx2,yy1,yy2,
     $zz1,zz2,dint1,dint2,grv1,grv2,rftemp,rf1,rf2,csbt1,csbt2,gmag1,
     $gmag2,glog1,glog2,fbin1,fbin2,delv1,delv2,count1,count2,delwl1,
     $delwl2,resf1,resf2,wl1,wl2,dvks1,dvks2,tau1,tau2,emm1,emm2,hbarw1,
     $hbarw2,xcl,ycl,zcl,rcl,op1,fcl,dens,encl,edens,taug,emmg,yskp,
     $zskp,mode,iband,ifat1,ifat2,0)
      if(mpage.ne.5) goto 127
      write(6,*)
      write(6,*)
      write(6,128) hjd,phas
      write(6,*)
      write(6,131)
      do 129 imp=1,ipc
      write(6,130) yskp(imp),zskp(imp)
  129 continue
      goto 20
  127 continue
      HTT=HOT
      IF(MODE.EQ.-1) HTT=0.d0
      TOTAL=HTT+COOL+EL3
      TOTALL=TOTAL/ALL
      TOT=TOTALL*FACTOR
      if(stdev.le.0.d0) goto 348
      call rangau(seed,nn,stdev,gau)
      ranf=1.d0+gau*dsqrt(totall**noise)
      total=total*ranf
      tot=tot*ranf
      totall=totall*ranf
  348 continue
      SMAGG=-1.085736d0*dlog(TOTALL)+ZERO
      if(mpage.eq.1) write(6,3) hjd,phas,htt,cool,total,tot,d,smagg
      if(mpage.eq.2) write(6,93) hjd,phas,vsum1,vsum2,vra1,vra2,vkm1,
     $vkm2
      if(mpage.ne.3) goto 81
      write(6,92) phas
      write(6,*)
      write(6,167) ns1
      write(6,907)
      do 906 i=in1min,in1max
  906 write(6,903) delv1(i),delwl1(i),wl1(i),fbin1(i),resf1(i)
      write(6,*)
      write(6,167) ns2
      write(6,907)
      do 908 i=in2min,in2max
  908 write(6,903) delv2(i),delwl2(i),wl2(i),fbin2(i),resf2(i)
      write(6,*)
      write(6,205)
      write(6,*)
      write(6,*)
   81 continue
      if(mpage.eq.4) write(6,296) hjd,phas,rv(1),rv(ll1),rv(llll1),
     $rv(lll1),rvq(1),rvq(ll2),rvq(llll2),rvq(lll2)
   20 CONTINUE
      do 909 komp=1,2
      write(6,*)
      if(message(komp,1).eq.1) write(6,283) komp
      if(message(komp,2).eq.1) write(6,284) komp
      if(message(komp,3).eq.1) write(6,285) komp
      if(message(komp,4).eq.1) write(6,286) komp
  909  continue
      if(mpage.eq.5) stop
      WRITE(6,*)
      WRITE(6,41)
      WRITE(6,*)
      do 119 ii=1,2
      gt1=dfloat(2-ii)
      gt2=dfloat(ii-1)
      f=f1*gt1+f2*gt2
      do 118 i=1,4
      call romq(po(ii),rm,f,dp,e,xtha(i),xfia(i),rad(i),drdo(i),
     $drdq,dodq,ii,mode)
  118 continue
      write(6,40) ii,rad(1),drdo(1),rad(2),drdo(2),rad(3),drdo(3),
     $rad(4),drdo(4)
  119 continue
      WRITE(6,*)
      if(mpage.eq.2) write(6,74)
 1000 CONTINUE
      STOP
      END
