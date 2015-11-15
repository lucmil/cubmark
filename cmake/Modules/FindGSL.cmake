# Try to find gnu scientific library GSL
# See
# http://www.gnu.org/software/gsl/  and
# http://gnuwin32.sourceforge.net/packages/gsl.htm
#
# Once run this will define:
#
# GSL_FOUND       = system has GSL lib
#
# GSL_LIBRARIES   = full path to the libraries
#    on Unix/Linux with additional linker flags from "gsl-config --libs"
#
# CMAKE_GSL_CXX_FLAGS  = Unix compiler flags for GSL, essentially "`gsl-config --cxxflags`"
#
# GSL_INCLUDE_DIR      = where to find headers
#
# GSL_LINK_DIRECTORIES = link directories, useful for rpath on Unix
# GSL_EXE_LINKER_FLAGS = rpath on Unix
#
# Łukasz Lis 09/2008
# Felix Woelk 07/2004
# Jan Woetzel
#
# www.mip.informatik.uni-kiel.de
# --------------------------------

SET(TMP "${CMAKE_FIND_LIBRARY_SUFFIXES}")
IF(GSL_USE_STATIC_LIBS)
	IF(WIN32)
		SET(CMAKE_FIND_LIBRARY_SUFFIXES
				.lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
	ELSE(WIN32)
		SET(CMAKE_FIND_LIBRARY_SUFFIXES
				.a ${CMAKE_FIND_LIBRARY_SUFFIXES})
	ENDIF(WIN32)
ENDIF(GSL_USE_STATIC_LIBS)

IF(WIN32)
  # JW tested with gsl-1.8, Windows XP, MSVS 7.1
  SET(GSL_POSSIBLE_ROOT_DIRS
    ${GSL_ROOT_DIR}
    $ENV{GSL_ROOT_DIR}
    ${GSL_DIR}
    ${GSL_HOME}
    $ENV{GSL_DIR}
    $ENV{GSL_HOME}
    $ENV{EXTRA}
    )
  FIND_PATH(GSL_INCLUDE_DIR
    NAMES gsl/gsl_cdf.h gsl/gsl_randist.h
    PATHS ${GSL_POSSIBLE_ROOT_DIRS}
    PATH_SUFFIXES include
    DOC "GSL header include dir"
    )

  FIND_LIBRARY(GSL_GSL_LIBRARY
    NAMES gsl libgsl
    PATHS  ${GSL_POSSIBLE_ROOT_DIRS}
    PATH_SUFFIXES lib
    DOC "GSL library dir" )

  FIND_LIBRARY(GSL_GSLCBLAS_LIBRARY
    NAMES gslcblas libgslcblas
    PATHS  ${GSL_POSSIBLE_ROOT_DIRS}
    PATH_SUFFIXES lib
    DOC "GSL cblas library dir" )

  SET(GSL_LIBRARIES ${GSL_GSL_LIBRARY})

  #MESSAGE("DBG\n"
  #  "GSL_GSL_LIBRARY=${GSL_GSL_LIBRARY}\n"
  #  "GSL_GSLCBLAS_LIBRARY=${GSL_GSLCBLAS_LIBRARY}\n"
  #  "GSL_LIBRARIES=${GSL_LIBRARIES}")


ELSE(WIN32)

  IF(UNIX)
    SET(GSL_CONFIG_PREFER_PATH
      "$ENV{GSL_DIR}/bin"
      "$ENV{GSL_DIR}"
      "$ENV{GSL_HOME}/bin"
      "$ENV{GSL_HOME}"
      CACHE STRING "preferred path to GSL (gsl-config)")
    FIND_PROGRAM(GSL_CONFIG gsl-config
      ${GSL_CONFIG_PREFER_PATH}
      /usr/bin/
      /usr/local/bin/
      )

    IF (GSL_CONFIG)
      # set CXXFLAGS to be fed into CXX_FLAGS by the user:
	  EXECUTE_PROCESS(COMMAND ${GSL_CONFIG} --cflags
        OUTPUT_VARIABLE GSL_CXX_FLAGS
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)

      # set INCLUDE_DIRS to prefix+include
      EXECUTE_PROCESS(COMMAND ${GSL_CONFIG} --prefix
        OUTPUT_VARIABLE GSL_PREFIX
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)
      SET(GSL_INCLUDE_DIR ${GSL_PREFIX}/include CACHE STRING INTERNAL)

      # set link libraries and link flags
	  EXECUTE_PROCESS(COMMAND ${GSL_CONFIG} --libs
        OUTPUT_VARIABLE GSL_LIBRARIES
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)

      # extract link dirs for rpath
      EXECUTE_PROCESS(COMMAND ${GSL_CONFIG} --libs
        OUTPUT_VARIABLE GSL_CONFIG_LIBS
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)

      # split off the link dirs (for rpath)
      # use regular expression to match wildcard equivalent "-L*<endchar>"
      # with <endchar> is a space or a semicolon
      STRING(REGEX MATCHALL "[-][L]([^ ;])+"
        GSL_LINK_DIRECTORIES_WITH_PREFIX
        "${GSL_CONFIG_LIBS}" )

      # remove prefix -L because we need the pure directory for LINK_DIRECTORIES

      IF (GSL_LINK_DIRECTORIES_WITH_PREFIX)
        STRING(REGEX REPLACE "[-][L]" "" GSL_LINK_DIRECTORIES ${GSL_LINK_DIRECTORIES_WITH_PREFIX} )
      ENDIF (GSL_LINK_DIRECTORIES_WITH_PREFIX)
      SET(GSL_EXE_LINKER_FLAGS "-Wl,-rpath,${GSL_LINK_DIRECTORIES}" CACHE STRING INTERNAL)

      #      ADD_DEFINITIONS("-DHAVE_GSL")
      #      SET(GSL_DEFINITIONS "-DHAVE_GSL")
      MARK_AS_ADVANCED(
        GSL_CXX_FLAGS
        GSL_INCLUDE_DIR
        GSL_LIBRARIES
        GSL_LINK_DIRECTORIES
        GSL_DEFINITIONS
	)
      MESSAGE(STATUS "Using GSL from ${GSL_PREFIX}")

    ELSE(GSL_CONFIG)
      MESSAGE("FindGSL.cmake: gsl-config not found. Please set it manually. GSL_CONFIG=${GSL_CONFIG}")
    ENDIF(GSL_CONFIG)

  ENDIF(UNIX)
ENDIF(WIN32)


IF(GSL_LIBRARIES)
  IF(GSL_INCLUDE_DIR OR GSL_CXX_FLAGS)

    SET(GSL_FOUND 1)

  ENDIF(GSL_INCLUDE_DIR OR GSL_CXX_FLAGS)
ENDIF(GSL_LIBRARIES)

set(CMAKE_FIND_LIBRARY_SUFFIXES "${TMP}")
