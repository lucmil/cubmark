Description
===========

A benchmark tool for multi-variate integration software.

Abstract from the paper
=======================

A set of readily available procedures for multivariate integration are tested in
the context of calculations in the quantum phase space.
Performance and reliability is measured against a set of test functions
including, but not limited to, the quantum probability mass of the
distribution.
A new benchmarking application written in C++ is described, inspired by the
TESTPACK algorithm by A.Genz.

Usage
=====

    $ ./cubmark -m dcuhre -m montecarlo -f G5:h=100,e=5.0 -c 1000000 -v testpack

This will run the DCUHRE and GSL Monte Carlo integration using Genz C0 test function with difficulty level h = 100 and exponent 5.0. Limit the number of calls to 1 million for each run. Compile the results into parameters defined by TESTPACK.

Example output
--------------

The results can be displayed directly on a console in different post-processed
formats or written to a file for later processing. There are three result
views available: testpack, gnuplot and view.

### TESTPACK view

    $ ./cubmark -m dcuhre -m montecarlo -f G5:h=100,e=5.0 -c 1000000 -v testpack

<a href="http://people.sc.fsu.edu/~jburkardt/m_src/testpack/testpack.html">TESTPACK</a> format.
```bash
# Test function: G5
# Parameters: G5:h=100,e=5.0
# Boundary is infinite: 0
# RET EE RE ROB Calls Time Q Fail
# Method: dcuhre
5.0e-02 { 2.03e-02 3.71e-02 } { 4.23e-04 1.06e-03 } 100% { 1.95e+02 1.95e+02 } { 0.00e+00 0.00e+00 } 1.8 0%
5.0e-03 { 4.16e-03 4.27e-03 } { 1.76e-04 2.17e-04 } 100% { 9.75e+02 1.24e+03 } { 0.00e+00 0.00e+00 } 2.2 0%
(...)

# Method: montecarlo
5.0e-02 { 6.07e-03 7.10e-03 } { 2.18e-03 2.67e-03 } 100% { 5.00e+03 5.00e+03 } { 0.00e+00 0.00e+00 } 1.3 0%
5.0e-03 { 6.16e-03 6.99e-03 } { 2.47e-05 4.41e-05 } 0% { 1.00e+07 1.00e+07 } { 5.50e+02 5.50e+02 } 1.0 0%
(...)
```

- RET - given relative error tolerance
- EE - error estimate reported by the library (tertiles)
- RE - real error (tertiles)
- ROB - success/failure reporting reliability (average)
- CALLS - number of function evaluations (tertiles)
- TIME - cpu time used in milliseconds (tertiles)
- Q - result quality, as defined by A. Genz
- FAIL - failed results reported as sucessful

### Raw dump

A raw dump of the results allows to calculate the above statistics at a later time or in a different application

    $ ./cubmark -m dcuhre -m montecarlo -f G5:h=100,e=5.0 -c 1000000 -v raw -o run_G5.dat
    $ ./cubmark -i run_G5.dat -v testpack

Test functions
==============

The following test functions are available:

### G family
Defined by <a href="http://people.sc.fsu.edu/~jburkardt/cpp_src/test_interp_nd/test_interp_nd.html">A.Genz</a>

    $ ./cubmark -m r2d2lri -f G1:h=100,e=5.0 -v testpack

- `cb::G1` - Oscillatory
- `cb::G2` - Product Peak
- `cb::G3` - Corner Peak
- `cb::G4` - Gaussian
- `cb::G5` - "C0"
- `cb::G6` - Discontinuous

### RD family
Defined by 

    $ ./cubmark -m r2d2lri -f RD28 -v testpack

- `cb::RD28Builder::compute`
- `cb::RD29Builder::compute`
- `cb::RD31Builder::compute`
- `cb::RD35Builder::compute`

### Wigner distributions

    $ ./cubmark -m r2d2lri -f W3:h=5 -v testpack

- `cb::W1` - Wigner distribution of a constant wavefunction
- `cb::W2` - Wigner distribution of a triangle wavefunction
- `cb::W3` - Wigner distribution of an infinite-potential well

Building
========

    $ cd benchmark
    $ cmake .
    $ make

To configure non-standard library paths you need to set CMake's include and library paths:


    $ cmake \
        -DCMAKE_INCLUDE_PATH="/path/to/Cubpack++/Code;/path/to/dcuhre;/path/to/r2d2lri;/path/to/HIntlib/include" \
        -DCMAKE_LIBRARY_PATH="/path/to/Cubpack++/Code;/path/to/dcuhre;/path/to/r2d2lri;/path/to/HIntlib/lib"

For each library this should yield:

```bash
-- checking for module 'HIntLib'
--   package 'HIntLib' not found
-- Found HIntLib 
HIntLib libraries found. Integration method will be available.
```

Requirements
------------

- gcc 4.4.0+
- cmake 2.6+
- Boost 1.34+ (serialization, program-options)

Supported libraries
-------------------

- Cubpack++ <http://nines.cs.kuleuven.be/software/cubpack/>
- r2d2lri <http://dl.acm.org/citation.cfm?id=513006>
- HIntLib <http://mint.sbg.ac.at/HIntLib/>
- DCUHRE <http://dl.acm.org/citation.cfm?id=210234>
- GSL <https://www.gnu.org/software/gsl/>

Documentation
-------------

- <a href="doxygen/index.html">Doxygen documentation with annotated function equations</a>
- <a href="bibliography.html">Bibliography</a>

Source
------

- <a href="https://github.com/lucmil/cubmark/">GitHub repository</a>
