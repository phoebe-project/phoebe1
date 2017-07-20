      subroutine mlrg(a,p,q,r1,r2,t1,t2,sm1,sm2,sr1,sr2,bolm1,
     $bolm2,xlg1,xlg2)
c  Version of January 16, 2002
c
c  This subroutine computes absolute dimensions and other quantities
c  for the stars of a binary star system.
c  a = orbital semi-major axis, the sum of the two a's for the two
c  stars. The unit is a solar radius.
c  r1,r2 = relative mean (equivalent sphere) radii for stars 1 and 2. Th
c  unit is the orbital semimajor axis.
c  p = orbit period in days.
c  q = mass ratio, m2/m1.
c  t1,t2= flux-weighted mean surface temperatures for stars 1 and 2,in K
c  sm1,sm2= masses of stars 1 and 2 in solar units.
c  sr1,sr2= mean radii of stars 1 and 2 in solar units.
c  bolm1, bolm2= absolute bolometric magnitudes of stars 1, 2.
c  xlg1, xlg2= log (base 10) of mean surface acceleration (effective gra
c  for stars 1 and 2.
c
      implicit real*8 (a-h,o-z)
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c
c     PHOEBE substitution:
c
c     G=6.668d-8
c     tsun=5800.d0
c     rsunau=214.8d0
c     sunmas=1.991d33
c     sunrad=6.960d10
c     sunmb=4.77d0
c     yrsid=365.2564d0
      tsun=5772.d0
c     rsunau=215.044520d0
      GMnomSun=1.3271244e26
      sunrad=6.957d10
      sunmb=4.74d0
c     yrsid=365.256363d0
      gmr=GMnomSun/sunrad**2
      sr1=r1*a
      sr2=r2*a
c     tmass=(a/rsunau)**3/(p/yrsid)**2
c     sm1=tmass/(1.d0+q)
c     sm2=tmass*q/(1.d0+q)
      sm1=(a*sunrad)**3/(p*8.64d4)**2*39.47841760435743/(1.d0+q)/
     $GMnomSun
      sm2=(a*sunrad)**3/(p*8.64d4)**2*39.47841760435743*q/(1.d0+q)/
     $GMnomSun
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      bol1=(t1/tsun)**4*sr1**2
      bol2=(t2/tsun)**4*sr2**2
      bolm1=sunmb-2.5d0*dlog10(bol1)
      bolm2=sunmb-2.5d0*dlog10(bol2)
      xlg1=dlog10(gmr*sm1/sr1**2)
      xlg2=dlog10(gmr*sm2/sr2**2)
      return
      end
