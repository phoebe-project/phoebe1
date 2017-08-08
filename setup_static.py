#!/usr/bin/env python

import sys, glob

if len(sys.argv)>1 and sys.argv[1] in ['build', 'install']:

  """
    Making static library
  """

  #
  # WD library (libwd)
  #

  print "WD library (libwd)"

  import numpy.distutils.fcompiler as Fcompiler
  import numpy.distutils.ccompiler as Ccompiler

  c = Fcompiler.new_fcompiler()

  workdir = './phoebe_legacy/libwd'

  src = glob.glob(workdir+'/*.f')

  # Optionally add include directories etc.
  c.add_include_dir(workdir)

  c.customize()

  # Compile into .o files
  objects = c.compile(src, output_dir="./build", extra_preargs=["-fPIC"])

  # Create static library
  c = Ccompiler.new_compiler()   # linking does not work with fcompiler
  c.create_static_lib(objects, "wd", output_dir="./build")


  #
  # PHOEBE library (libphoebe)
  #
  print "PHOEBE library methods (libphoebe)"

  c = Ccompiler.new_compiler()
  workdir = "./phoebe_legacy/libphoebe_methods"
  src = glob.glob(workdir+"/*.c")

  # Optionally add include directories etc.
  c.add_include_dir(workdir)

  #c.set_libraries(['wd','gsl','gslcblas','m'])

  c.set_library_dirs("./phoebe_legacy/libwd")

  # Compile into .o files
  objects = c.compile(src, output_dir="./build", extra_preargs=["-fPIC"])

  # Create static
  c.create_static_lib(objects, "phoebe_methods", output_dir="./build")


"""
  Making python module
"""

from distutils.core import setup, Extension

ext_modules = [
    Extension(
      'libphoebe_legacy',
      sources = ['./phoebe_legacy/libphoebe_legacy.c'],
      include_dirs = ['./phoebe_legacy/libphoebe_methods'],
      extra_link_args= ["-L./build"],
      libraries = ['phoebe_methods', 'wd', 'gfortran']
    )
  ]

setup (name = 'phoebe_legacy',
       version = '0.40',
       description = 'PHOEBE legacy python package',
       packages = ['phoebe_legacy'],
       package_data={'phoebe_legacy': ['tables/wd/*','tables/ptf/*', 'tables/vanhamme/*', 'tables/ld/*'], },
       ext_modules = ext_modules)

