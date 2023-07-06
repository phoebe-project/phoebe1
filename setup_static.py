#!/usr/bin/env python

import sys, glob

import numpy

if len(sys.argv)>1 and sys.argv[1] in ['build', 'install']:

  from setuptools._distutils import ccompiler as Ccompiler

  """
    Making static library
  """

  #
  # WD library (libwd) Fortran 77 (legacy)
  #

  print("WD library (libwd)")

  c = Ccompiler.new_compiler()
  workdir = './phoebe_legacy/libwd'

  src = glob.glob(workdir+'/wd.c')

  # Optionally add include directories etc.
  c.add_include_dir(workdir)

  # Compile into .o files
  objects = c.compile(src, output_dir="./build", extra_preargs=["-fPIC"])

  # Create static library
  c = Ccompiler.new_compiler()

  c.create_static_lib(objects, "wd", output_dir="./build")

  #
  # PHOEBE library (libphoebe)
  #
  print("PHOEBE library methods (libphoebe)")

  c = Ccompiler.new_compiler()
  workdir = "./phoebe_legacy/libphoebe_methods"
  src = glob.glob(workdir+"/*.c")

  # Optionally add include directories etc.
  c.add_include_dir(workdir)

  c.set_library_dirs("./phoebe_legacy/libwd")

  c.define_macro("PHOEBE_GSL_DISABLED")

  # Compile into .o files
  objects = c.compile(src, output_dir="./build", extra_preargs=["-fPIC"])

  # Create static
  c.create_static_lib(objects, "phoebe_methods", output_dir="./build")


"""
  Making python module
"""

from setuptools import Extension, setup

ext_modules = [
    Extension(
      'libphoebe_legacy',
      sources = ['./phoebe_legacy/libphoebe_legacy.c'],
      include_dirs = ['./phoebe_legacy/libphoebe_methods', numpy.get_include()],
      extra_link_args= ["-L./build"],
      libraries = ['phoebe_methods', "wd", "f2c", "m"]
    )
  ]

setup (name = 'phoebe_legacy',
       version = '0.40',
       description = 'PHOEBE legacy python package',
       packages = ['phoebe_legacy'],
       package_data={'phoebe_legacy': ['tables/wd/*','tables/ptf/*', 'tables/vanhamme/*', 'tables/ld/*'], },
       ext_modules = ext_modules)
