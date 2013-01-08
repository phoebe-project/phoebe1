      SUBROUTINE DURA(F,XINCL,RM,D,THE,OMEG,R)
c  Version of May 19, 1996
C
C     PARAMETER 'THE' IS THE SEMI-DURATION OF X-RAY ECLIPSE, AND SHOULD
C     BE IN CIRCULAR MEASURE.
      IMPLICIT REAL*8(A-H,O-Z)
      DELX=0.D0
      FSQ=F*F
      RMD=1.d0/RM
      RMD1=RMD+1.D0
      XINC=.017453293d0*XINCL
      TH=6.2831853071795865d0*THE
      CI=DCOS(XINC)
      SI=DSIN(XINC)
      DSQ=D*D
      ST=DSIN(TH)
      CT=DCOS(TH)
      COTI=CI/SI
      TT=ST/CT
      C1=CT*SI
      C2=TT*ST*SI
      C3=C1+C2
      C4=COTI*CI/CT
      C5=C3+C4
      C6=C2+C4
      C7=(ST*ST+COTI*COTI)/CT**2
      X=D*(SI*SI*ST*ST+CI*CI)+.00001D0
   15 X=X+DELX
      PAR=X*X+C7*(D-X)**2
      RPAR=DSQRT(PAR)
      PAR32=PAR*RPAR
      PAR52=PAR*PAR32
      FC=(C6*D-C5*X)/PAR32+C1**3*C5*RMD/(D-X)**2+C3*FSQ*RMD1*X-C2*FSQ*D*
     $RMD1-C1*RMD/DSQ
      DFCDX=(-C5*PAR-3.D0*(C6*D-C5*X)*((1.D0+C7)*X-C7*D))/PAR52+2.D0*C1
     $**3*C5*RMD/(D-X)**3+C3*FSQ*RMD1
      DELX=-FC/DFCDX
      ABDELX=DABS(DELX)
      IF(ABDELX.GT.1.d-7) GOTO 15
      Y=-(D-X)*TT
      Z=-(D-X)*COTI/CT
      YZ2=Y*Y+Z*Z
      OMEG=1.D0/DSQRT(X*X+YZ2)+RMD/DSQRT((D-X)**2+YZ2)+.5D0*RMD1*FSQ*
     $(X*X+Y*Y)-RMD*X/DSQ
      OMEG=RM*OMEG+.5d0*(1.d0-RM)
      R=DSQRT(X*X+YZ2)
      RETURN
      END
