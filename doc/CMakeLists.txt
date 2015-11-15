# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

find_package (Doxygen)

if (DOXYGEN_FOUND)
	add_custom_target(doc
			${DOXYGEN_EXECUTABLE}
			${CMAKE_CURRENT_SOURCE_DIR}/benchmark_doxygen.cfg
			DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/benchmark_doxygen.cfg
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif (DOXYGEN_FOUND)
