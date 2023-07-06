#!/usr/bin/env python

import sys, glob, site
from setuptools import Extension, setup

ext_modules = [

    Extension(
      'libphoebe_legacy',
      sources = ['./phoebe_legacy/libphoebe_legacy.c','./phoebe_legacy/libwd/wd.c'] +
                glob.glob('./phoebe_legacy/libphoebe_methods/*.c') ,
      include_dirs = ['./phoebe_legacy/libphoebe_methods'],
      libraries = ['gsl','gslcblas','m','f2c']
    )
  ]

setup (name = 'phoebe_legacy',
       version = '0.40',
       description = 'PHOEBE legacy python package',
       packages = ['phoebe_legacy'],
       package_data={'phoebe_legacy': ['tables/*'], },
       ext_modules = ext_modules)
