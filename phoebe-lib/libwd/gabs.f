      subroutine gabs(komp,smaxis,qq,ecc,period,dd,rad,xm,xmo,absgr,
     $glog)
      implicit real*8(a-h,o-z)
c  Version of September 17, 2004
c
c  Input definitions:
c   smaxis is the length of the orbital semi-major axis in solar radii.
c   qq is the mass ratio in the sense m2/m1. Stars 1 and 2 are as defined
c     in the external program (star 1 is near superior conjunction at
c     phase zero).
c   ecc is orbital eccentricity
c   period is orbit period in days
c   dd is the instantaneous separation of the star centers in unit of th
c     orbital semi-major axis
c   rad is the polar radius if the star at issue in unit of the orbital
c     semi-major axis
c  Output definitions:
c   absgr is the polar acceleration due to effective gravity in cm/sec^2
c   glog is log_10 of absgr
c
      twopi=6.2831853072d0
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c
c     PHOEBE substitution:
c
c     gbig=6.670d-8
c     sunmas=1.989d33
c     sunrad=6.9599d10
      gbig=6.67384d-8
      sunmas=1.988547d33
      sunrad=6.9566d10
      psec=8.64d4*period
      acm=sunrad*smaxis
c     pyears=period/365.2422d0
c     aau=smaxis/214.9426d0
c     tmass=aau**3/pyears**2
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      qf=1.d0/(1.d0+qq)
      qfm=qq*qf
      sign=-1.d0
      if(komp.eq.2) goto 10
      qfm=qf
      qf=qq*qf
      sign=1.d0
   10 continue
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
c
c     PHOEBE substitution:
c
c     xm=tmass*qfm
c     xmo=tmass*qf
c     gbigm=gbig*xm*sunmas
c     gbigmo=gbig*xmo*sunmas
      gbigm=acm**3/psec**2*twopi**2*qfm
      xm=gbigm/gbig/sunmas
      gbigmo=acm**3/psec**2*twopi**2*qf
      xmo=gbigmo/gbig/sunmas
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      rcm=rad*acm
      dcm=dd*acm
      dcmsq=dcm*dcm
      efac=dsqrt((1.d0+ecc)*(1.d0-ecc))
      av=twopi*efac/(psec*dd*dd)
      avsq=av*av
      rcmsq=rcm*rcm
      hypsq=rcmsq+dcmsq
      hyp=dsqrt(hypsq)
      snalf=rcm/hyp
      csalf=dcm/hyp
      gz=-gbigm/rcmsq
      gzo=-snalf*gbigmo/hypsq
      gxo=sign*csalf*gbigmo/hypsq
      gxcf=-sign*avsq*dcm*qf
      gxs=gxo+gxcf
      gzs=gz+gzo
      absgr=dsqrt(gxs*gxs+gzs*gzs)
      glog=dlog10(absgr)
      return
      end
