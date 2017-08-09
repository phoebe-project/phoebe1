import libphoebe_legacy

import os 
packegedir = os.path.dirname(libphoebe_legacy.__file__) + "/phoebe_legacy"

from libphoebe_legacy import *
import tempfile
  
def auto_configure():
  
  startup = os.getcwd()
  homedir = os.path.expanduser("~")
  tmpdir = tempfile.gettempdir()
  basedir = packegedir + "/tables"
  datadir = basedir
  ptfdir = datadir + "/ptf"
  ldswitch = 0
  ldintern = 0
  lddir =  datadir + "/ld"
  vhdir =  datadir + "/vanhamme"
  loadatm = 1
  dumplco = 1
  
  return  custom_configure( bytes(startup),bytes(homedir), 
            bytes(basedir), bytes(tmpdir), bytes(datadir),
            bytes(ptfdir), ldswitch, ldintern, bytes(lddir), 
            bytes(vhdir), loadatm, dumplco)
