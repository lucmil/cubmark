# cubmark
A benchmarking tool for multi-variate integration software.

Abstract from the associated paper
==================================

A set of readily available procedures for multivariate integration are tested in
the context of calculations in the quantum phase space.
Performance and reliability is measured against a set of test functions
including, but not limited to, the quantum probability mass of the
distribution.
A new benchmarking application written in C++ is described, inspired by the
TESTPACK algorithm by A.Genz.

Usage
=====

```bash
$ ./cubmark -m dcuhre -m montecarlo -f G5:h=100,e=5.0 -c 1000000 -v testpack
```

This will run the DCUHRE and GSL Monte Carlo integration using Genz C0 test function with difficulty level h = 100 and exponent 5.0. Limit the number of calls to 1 million for each run. Compile the results into parameters defined by TESTPACK.

Building
========

```bash
$ mkdir benchmark
$ cd benchmark
$ cmake ..
$ make
```

To configure non-standard library paths you need to set CMake's include and library
paths:

```bash
$ cmake \
	-DCMAKE_INCLUDE_PATH="/path/to/Cubpack++/Code;/path/to/dcuhre;/path/to/r2d2lri;/path/to/HIntlib/include" \
	-DCMAKE_LIBRARY_PATH="/path/to/Cubpack++/Code;/path/to/dcuhre;/path/to/r2d2lri;/path/to/HIntlib/lib"
```

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
- Boost 1.34+ (serialization, program-options, test)

Supported libraries
-------------------

- Cubpack++ <http://nines.cs.kuleuven.be/software/cubpack/>
- r2d2lri <http://dl.acm.org/citation.cfm?id=513006>
- HIntLib <https://github.com/JohannesBuchner/HIntLib>
- DCUHRE <http://dl.acm.org/citation.cfm?id=210234>
- GSL <https://www.gnu.org/software/gsl/>

Documentation
-------------

- <a href="https://lucmil.github.io/cubmark/doxygen/">Doxygen documentation</a>
- <a href="https://lucmil.github.io/cubmark/">Project page</a>
- <a href="https://lucmil.github.io/cubmark/bibliography.html">Bibliography</a>

Source
------

- <a href="https://github.com/lucmil/cubmark/">GitHub repository</a>

