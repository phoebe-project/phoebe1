import sys
import libphoebe_legacy

import os
packagedir = os.path.dirname(libphoebe_legacy.__file__) + "/phoebe_legacy"

from libphoebe_legacy import *
import tempfile


def auto_configure():

  def f(s):
    return s if sys.version_info > (3,) else bytes(s)

  startup = os.getcwd()
  homedir = os.path.expanduser("~")
  tmpdir = tempfile.gettempdir()
  basedir = packagedir + "/tables"
  datadir = basedir
  ptfdir = datadir + "/ptf"
  ldswitch = 0
  ldintern = 0
  lddir =  datadir + "/ld"
  vhdir =  datadir + "/vanhamme"
  loadatm = 1
  dumplco = 1

  verbose_warnings = os.environ.get('VERBOSE_WARNINGS', 1)
  verbose_errors = os.environ.get('VERBOSE_ERRORS', 1)


  return  custom_configure(f(startup), f(homedir),
            f(basedir), f(tmpdir),f(datadir),
            f(ptfdir), ldswitch, ldintern, f(lddir),
            f(vhdir), loadatm, dumplco,
            verbose_warnings, verbose_errors)

auto_configure()
