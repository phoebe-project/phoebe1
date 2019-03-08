from distutils.core import setup, Extension

module1 = Extension('phoebeBackendPhoenix',
                    sources = ['phoebe_backend.c'],
		    libraries = ['phoebe_phoenix'])

setup (name = 'PHOEBE backend',
       version = '1.00',
       description = 'PHOEBE python package',
       ext_modules = [module1])

