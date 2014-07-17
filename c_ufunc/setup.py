from distutils.core import setup
from distutils.extension import Extension
setup(name='c_ufunc',
      ext_modules=[
          Extension(
              'c_ufunc',
              ['c_ufunc.c'],
              libraries=['erfa']
          )],
      )
