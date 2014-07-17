Experiments with wrapping ERFA
==============================

This explores different ways of provinding a vectorized Python interface to
ERFA. We experiment with the ``eraD2dtf`` function. Currently we will try the
following, but feel free to add other methods::

* ``cython`` - a pure Cython-based wrapper
* ``c_numpy`` - a pure C (with Numpy API) wrapper
* ``c_auto`` - a hand-written vectorized C wrapper with an auto-generated Python wrapper from the vectorized C wrappers.
* ``c_ufunc`` - a pure C using the Numpy UFunc API wrapper
