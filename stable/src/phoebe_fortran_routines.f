			SUBROUTINE OPENSTREAM(FN)
			implicit none
			character FN*(*)
			open(unit=1, file=FN, status='UNKNOWN')
			END

			SUBROUTINE CLOSESTREAM()
			close(unit=1)
			END

      SUBROUTINE CREATELCILINE1(MPAGE,NREF,MREF,IFSMV1,IFSMV2,ICOR1,
     +                          ICOR2,LD)
			implicit none
			integer MPAGE,NREF,MREF,IFSMV1,IFSMV2,ICOR1,ICOR2,LD
			write(1,1) MPAGE,NREF,MREF,IFSMV1,IFSMV2,ICOR1,ICOR2,LD
    1 format(8(I1,1X))
			END
			
			SUBROUTINE CREATELCILINE2(JDPHS,HJD0,PERIOD,DPDT,PSHIFT,STDDEV,
     +                          NOISE,SEED)
      implicit none
			integer JDPHS,NOISE
			double precision HJD0,PERIOD,DPDT,PSHIFT,STDDEV,SEED
			write(1,2) JDPHS,HJD0,PERIOD,DPDT,PSHIFT,STDDEV,NOISE,SEED
    2 format(I1,F15.6,D15.10,D13.6,F10.4,D10.4,I2,F11.0)
      END

			SUBROUTINE CREATELCILINE3(JDSTRT,JDEND,JDINC,PHSTRT,PHEND,PHINC,
     +                          PHNORM)
      implicit none
			double precision JDSTRT,JDEND,JDINC,PHSTRT,PHEND,PHINC,PHNORM
			write(1,3) JDSTRT,JDEND,JDINC,PHSTRT,PHEND,PHINC,PHNORM
    3 format(F14.6,F15.6,F13.6,4F10.4)
      END

			SUBROUTINE CREATELCILINE4(MODE,IPB,IFAT1,IFAT2,N1,N2,PERR0,
     +                          DPERDT,THE,VUNIT)
      implicit none
      integer MODE,IPB,IFAT1,IFAT2,N1,N2
			double precision PERR0,DPERDT,THE,VUNIT
			write(1,4) MODE,IPB,IFAT1,IFAT2,N1,N2,PERR0,DPERDT,THE,VUNIT
    4 format(4I2,2I3,F13.6,E12.5,F7.5,F8.2)
      END

			SUBROUTINE CREATELCILINE5(E,SMA,F1,F2,VGA,XINCL,GR1,GR2,ABUNIN)
      implicit none
			double precision E,SMA,F1,F2,VGA,XINCL,GR1,GR2,ABUNIN
			write(1,5) E,SMA,F1,F2,VGA,XINCL,GR1,GR2,ABUNIN
    5 format(F6.5,F10.4,2F10.4,F10.4,F9.3,2F7.3,F7.2)
      END

			SUBROUTINE CREATELCILINE6(TAVH,TAVC,ALB1,ALB2,PHSV,PCSV,RM,
     +                          XBOL1,XBOL2,YBOL1,YBOL2)
      implicit none
			double precision TAVH,TAVC,ALB1,ALB2,PHSV,PCSV,RM,XBOL1,XBOL2,
     +                 YBOL1,YBOL2
			write(1,6) TAVH,TAVC,ALB1,ALB2,PHSV,PCSV,RM,XBOL1,XBOL2,YBOL1,
     +           YBOL2
    6 format(2(F7.4,1X),2F7.3,2D12.5,F10.5,4F7.3)
      END

			SUBROUTINE CREATELCILINE7(IBAND,HLA,CLA,X1A,X2A,Y1A,Y2A,EL3,
     +                          OPSF,MZERO,FACTOR,WLA)
      implicit none
      integer IBAND
			double precision WLA,HLA,CLA,X1A,X2A,Y1A,Y2A,EL3,OPSF,MZERO,
     +                 FACTOR
			write(1,7) IBAND,HLA,CLA,X1A,X2A,Y1A,Y2A,EL3,OPSF,MZERO,FACTOR,
     +           WLA
    7 format(I3,2F10.5,4F7.3,F8.4,D10.4,F8.3,F8.4,F9.6)
      END

			SUBROUTINE CREATELCILINE8(XLAT1,XLONG1,RADSP1,TEMSP1)
      implicit none
			double precision XLAT1,XLONG1,RADSP1,TEMSP1
			write(1,8) XLAT1,XLONG1,RADSP1,TEMSP1
    8 format(4F9.5)
      END

			SUBROUTINE CREATELCILINE10(XLAT2,XLONG2,RADSP2,TEMSP2)
      implicit none
			double precision XLAT2,XLONG2,RADSP2,TEMSP2
			write(1,10) XLAT2,XLONG2,RADSP2,TEMSP2
   10 format(4F9.5)
      END

			SUBROUTINE CREATELCILINE13(SEP4)
      implicit none
			double precision SEP4
			write(1,13) SEP4
   13 format(I1)
      END

			SUBROUTINE CREATEDCILINE1(DEL1,DEL2,DEL3,DEL4,DEL5,DEL6,DEL7,
     +                          DEL8)
			implicit none
			double precision DEL1,DEL2,DEL3,DEL4,DEL5,DEL6,DEL7,DEL8
			write(1,1) DEL1,DEL2,DEL3,DEL4,DEL5,DEL6,DEL7,DEL8
    1 format(10(1X,D7.1))
			END

			SUBROUTINE CREATEDCILINE2(DEL10,DEL11,DEL12,DEL13,DEL14,DEL16,
     +                          DEL17,DEL18,DEL19,DEL20)
			implicit none
			double precision DEL10,DEL11,DEL12,DEL13,DEL14,DEL16,DEL17,DEL18,
     +                 DEL19,DEL20
			write(1,2) DEL10,DEL11,DEL12,DEL13,DEL14,DEL16,DEL17,DEL18,DEL19,
     +           DEL20
    2 format(10(1X,D7.1))
			END

			SUBROUTINE CREATEDCILINE3(DEL21,DEL22,DEL23,DEL24,DEL25,DEL31,
     +                          DEL32,DEL33,DEL34)
			implicit none
			double precision DEL21,DEL22,DEL23,DEL24,DEL25,DEL31,DEL32,DEL33,
     +                 DEL34
			write(1,3) DEL21,DEL22,DEL23,DEL24,DEL25,DEL31,DEL32,DEL33,DEL34
    3 format(10(1X,D7.1))
			END

			SUBROUTINE CREATEDCILINE4(KEP,IFDER,IFM,IFR,XLAMDA)
			implicit none
			integer I,KEP(35),IFDER,IFM,IFR
			double precision XLAMDA
			write(1,4) (KEP(I),I=1,35),IFDER,IFM,IFR,XLAMDA
    4 format(1X,2(4I1,1X),7I1,1X,4(5I1,1X),I1,1X,I1,1X,I1,D10.3)
			END

			SUBROUTINE CREATEDCILINE5(KSPA,NSPA,KSPB,NSPB)
			implicit none
			integer KSPA,NSPA,KSPB,NSPB
			write(1,5) KSPA,NSPA,KSPB,NSPB
    5 format(4I3)
			END

			SUBROUTINE CREATEDCILINE6(IFVC1,IFVC2,NLC,K0,KDISK,ISYM,NPPL)
			implicit none
			integer IFVC1,IFVC2,NLC,K0,KDISK,ISYM,NPPL
			write(1,6) IFVC1,IFVC2,NLC,K0,KDISK,ISYM,NPPL
    6 format(I1,1X,I1,1X,5I2)
			END

			SUBROUTINE CREATEDCILINE7(NREF,MREF,IFSMV1,IFSMV2,ICOR1,ICOR2,LD)
			implicit none
			integer NREF,MREF,IFSMV1,IFSMV2,ICOR1,ICOR2,LD
			write(1,7) NREF,MREF,IFSMV1,IFSMV2,ICOR1,ICOR2,LD
    7 format(7(I1,1X))
			END

			SUBROUTINE CREATEDCILINE8(JDPHS,HJD0,PERIOD,DPDT,PSHIFT)
			implicit none
			integer JDPHS
			double precision HJD0,PERIOD,DPDT,PSHIFT
			write(1,8) JDPHS,HJD0,PERIOD,DPDT,PSHIFT
    8 format(I1,F15.6,D17.10,D14.6,F10.4)
			END

			SUBROUTINE CREATEDCILINE9(MODE,IPB,IFAT1,IFAT2,N1,N2,N1L,N2L,
     +                          PERR0,DPERDT,THE,VUNIT)
			implicit none
			integer MODE,IPB,IFAT1,IFAT2,N1,N2,N1L,N2L
			double precision PERR0,DPERDT,THE,VUNIT
			write(1,9) MODE,IPB,IFAT1,IFAT2,N1,N2,N1L,N2L,PERR0,DPERDT,THE,
     +           VUNIT
    9 format(4I2,4I3,F13.6,D12.5,F8.5,F9.3)
			END

			SUBROUTINE CREATEDCILINE10(E,A,F1,F2,VGA,XINCL,GR1,GR2,ABUNIN)
			implicit none
			double precision E,A,F1,F2,VGA,XINCL,GR1,GR2,ABUNIN
			write(1,10) E,A,F1,F2,VGA,XINCL,GR1,GR2,ABUNIN
   10 format(F6.5,F10.4,2F10.4,F10.4,F9.3,3F7.3)
			END

			SUBROUTINE CREATEDCILINE11(TAVH,TAVC,ALB1,ALB2,PHSV,PCSV,RM,
     +                           XBOL1,XBOL2,YBOL1,YBOL2)
			implicit none
			double precision TAVH,TAVC,ALB1,ALB2,PHSV,PCSV,RM,XBOL1,XBOL2,
     +                 YBOL1,YBOL2
			write(1,11) TAVH,TAVC,ALB1,ALB2,PHSV,PCSV,RM,XBOL1,XBOL2,YBOL1,
     +            YBOL2
   11 format(F7.4,F8.4,2F7.3,2D13.6,F10.5,4F7.3)
			END

      SUBROUTINE CREATEDCILINERV(IBAND,HLA,CLA,X1A,X2A,Y1A,Y2A,
     +                           OPSF,SIGMA,WLA)
			implicit none
      integer IBAND
			double precision WLA,HLA,CLA,X1A,X2A,Y1A,Y2A,OPSF,SIGMA
			write(1,12) IBAND,HLA,CLA,X1A,X2A,Y1A,Y2A,OPSF,SIGMA,WLA
   12 format(I3,2F10.5,4F7.3,D10.3,D12.5,F10.6)
			END

      SUBROUTINE CREATEDATALINE(INDEP,DEP,WEIGHT)
			implicit none
			double precision INDEP,DEP,WEIGHT
      write(1,1) INDEP,DEP,WEIGHT
    1 format(5(F14.5,F8.4,F6.2))
		  END

      SUBROUTINE CREATEDCILINELC(IBAND,HLA,CLA,X1A,X2A,Y1A,Y2A,EL3,
     +                            OPSF,NOISE,SIGMA,WLA)
			implicit none
			integer NOISE,IBAND
			double precision WLA,HLA,CLA,X1A,X2A,Y1A,Y2A,EL3,OPSF,SIGMA
			write(1,13) IBAND,HLA,CLA,X1A,X2A,Y1A,Y2A,EL3,OPSF,NOISE,
     +            SIGMA,WLA
   13 format(I3,2F10.5,4F7.3,F8.4,D10.3,I2,D12.5,F10.6)
			END

			SUBROUTINE CREATESPOTSSTOPLINE()
      implicit none
			double precision SEP
			SEP = 300.0
			write(1,1) SEP
    1 format(1X,F4.0)
      END

			SUBROUTINE CREATECLOUDSSTOPLINE()
      implicit none
			double precision SEP
			SEP = 150.0
			write(1,2) SEP
    2 format(F4.0)
      END

			SUBROUTINE CREATEDATASTOPLINE ()
      implicit none
			double precision SEP
			SEP = -10001.0
			write (1,3) SEP
    3 format(F9.0)
      END

      SUBROUTINE CREATELCIENDLINE ()
			implicit none
			integer SEP
			SEP = 9
			write(1,1) SEP
    1 format(I1)
		  END

      SUBROUTINE CREATEDCIENDLINE ()
			implicit none
			integer SEP
			SEP = 2
			write(1,2) SEP
    2 format(I2)
		  END
