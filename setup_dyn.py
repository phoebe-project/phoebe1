#!/usr/bin/env python

import sys, glob, site
from sysconfig import get_platform

build_dir = './build/lib.%s-%d.%d' % (get_platform(), sys.version_info[0], sys.version_info[1])

if '--user' in sys.argv:
  install_dir = site.getusersitepackages()
else:
  install_dir = site.getsitepackages()[0]


"""
  Making python module
"""

from setuptools import Extension, setup

ext_modules = [

    Extension(
      'libphoebe_legacy',
      sources = ['./phoebe_legacy/libphoebe_legacy.c','./phoebe_legacy/libwd/wd.c'] +
                glob.glob('./phoebe_legacy/libphoebe_methods/*.c') ,
      include_dirs = ['./phoebe_legacy/libphoebe_methods'],
      libraries = ['gsl','gslcblas','m','f2c'],
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
