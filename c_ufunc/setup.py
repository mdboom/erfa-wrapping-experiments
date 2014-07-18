from distutils.core import setup
from distutils.extension import Extension

import numpy as np

try:
    numpy_include = np.get_include()
except AttributeError:
    numpy_include = np.get_numpy_include()

setup(name='c_ufunc',
      ext_modules=[
          Extension(
              'c_ufunc',
              ['c_ufunc.c'],
              libraries=['erfa'],
              include_dirs=[numpy_include]
          )],
      )
