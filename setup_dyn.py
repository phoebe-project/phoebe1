#!/usr/bin/env python

import sys, glob, site
from distutils.util import get_platform

if 'build' in sys.argv:
  print("In dynamic version nly install is supported.")
  quit()
  
build_dir = './build/lib.%s-%d.%d' % (get_platform(), sys.version_info[0], sys.version_info[1])

if '--user' in sys.argv:
  install_dir = site.getusersitepackages()
else:
  install_dir = site.getsitepackages()[0]
 

"""
  Making python module
"""

from numpy.distutils.core import setup, Extension

ext_modules = [
    
    Extension('libwd',
      sources = glob.glob('./phoebe_legacy/libwd/*.F')
    ),
    
    Extension(
      'libphoebe_methods',
      sources = glob.glob('./phoebe_legacy/libphoebe_methods/*.c'),
      library_dirs=[build_dir],
      libraries = ['wd','gsl','gslcblas','m'],
    ),

    Extension(
      'libphoebe_legacy',
      sources = ['./phoebe_legacy/libphoebe_legacy.c'],
      include_dirs = ['./phoebe_legacy/libphoebe_methods'],
      libraries = ['phoebe_methods','wd', 'gfortran'],
      library_dirs=[build_dir],
      runtime_library_dirs = [install_dir]
    )
  ]

setup (name = 'phoebe_legacy',
       version = '0.40',
       description = 'PHOEBE legacy python package',
       packages = ['phoebe_legacy'],
       package_data={'phoebe_legacy': ['tables/*'], },
       ext_modules = ext_modules)

