from distutils.core import setup, Extension
import numpy 

module1 = Extension('phoebeBackend',
                    sources = ['phoebe_backend.c'],
		    libraries = ['phoebe'],
                    include_dirs=[numpy.get_include()])
                    
setup (name = 'PHOEBE backend',
       version = '0.40',
       description = 'PHOEBE python package',
       ext_modules = [module1])

