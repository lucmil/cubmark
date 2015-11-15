# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

include(LibFindMacros)

# - Try to find a library for a method
# Once done, this will define

#  ${PREFIX}_FOUND - system has PREFIX
#  ${PREFIX}_INCLUDE_DIRS - the PREFIX include directories
#  ${PREFIX}_LIBRARIES - link these to use PREFIX or use the library target
macro(cubmark_find_method_library PREFIX PATHNAME LIBNAME)
	# Use pkg-config to get hints about paths
	libfind_pkg_check_modules(${PREFIX}_PKGCONF ${PREFIX})

	# Include dir
	find_path(${PREFIX}_INCLUDE_DIR
		NAMES "${PATHNAME}"
		PATHS ${${PREFIX}_PKGCONF_INCLUDE_DIRS})

	set(TMP "${CMAKE_FIND_LIBRARY_SUFFIXES}")
	if(${PREFIX}_USE_STATIC_LIBS)
		if(WIN32)
			set(CMAKE_FIND_LIBRARY_SUFFIXES
					.lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
		else(WIN32)
			set(CMAKE_FIND_LIBRARY_SUFFIXES
					.a ${CMAKE_FIND_LIBRARY_SUFFIXES})
		endif(WIN32)
	endif(${PREFIX}_USE_STATIC_LIBS)

	# Finally the library itself
	find_library(${PREFIX}_LIBRARY
		NAMES ${LIBNAME}
		PATHS ${${PREFIX}_PKGCONF_LIBRARY_DIRS})

	set(CMAKE_FIND_LIBRARY_SUFFIXES "${TMP}")

	# Set the include dir variables and the libraries and let libfind_process do the rest.
	# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
	set(${PREFIX}_PROCESS_INCLUDES ${PREFIX}_INCLUDE_DIR)
	set(${PREFIX}_PROCESS_LIBS ${PREFIX}_LIBRARY)
	libfind_process(${PREFIX})

endmacro(cubmark_find_method_library PREFIX LIB)
