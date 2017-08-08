import libphoebe_legacy

import os 
basedir = os.path.dirname(libphoebe_legacy.__file__) + "/phoebe_legacy"

from libphoebe_legacy import *
import tempfile
  
def phoebeAutoConfigure():
  
  startup = os.getcmd()
  homedir = os.path.expanduser("~")
  basedir = basedir
  tmpdir = tempfile.gettempdir()
  datadir = basedir + "/tables"
  ptfdir = datadir + "/ptf"
  ldswitch = 0
  ldintern = 0
  lddir =  datadir + "/ld"
  vhdir =  datadir + "/vanhamme"
  loadatm = 1
  dumplco = 1
  
  return  phoebeCustomConfigure( bytes(startup),bytes(homedir), 
            bytes(basedir), bytes(tmpdir), bytes(datadir),
            bytes(ptfdir), ldswitch, ldintern, bytes(lddir), 
            bytes(vhdir), loadatm, dumplco)
