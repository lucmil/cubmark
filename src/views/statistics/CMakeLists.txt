# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

add_library(cubmark_statistics STATIC
		ResultAverage.cpp
		ResultMedian.cpp
		ResultQuantiles.cpp
		ResultStatistic.cpp
		ResultQuality.cpp)

