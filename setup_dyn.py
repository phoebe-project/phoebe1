#!/usr/bin/env python

import sys, glob

build_dir = './build/lib.linux-x86_64-2.7'
install_dir = '/home/horvat/.local/lib/python2.7/site-packages'

"""
  Making python module
"""

from numpy.distutils.core import setup, Extension

ext_modules = [
    
    Extension('libwd',
      sources = glob.glob('./phoebe_legacy/libwd/*.f'),
      runtime_library_dirs = [install_dir]
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

