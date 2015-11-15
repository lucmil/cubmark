# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

cmake_minimum_required (VERSION 2.6)
project (CUBMARK)
enable_language(Fortran)

option(STATIC		"Prefer static libraries"	OFF)
option(STATIC_STDLIB "Link standard library statically" OFF)
option(WITH_GSL		"Build GSL interface"		ON)
option(WITH_R2D2LRI	"Build r2d2lri interface"	ON)
option(WITH_CUBPACK	"Build Cubpack++ interface"	ON)
option(WITH_HINTLIB	"Build HIntLib interface"	ON)
option(WITH_DCUHRE	"Build DCUHRE interface"	ON)
option(PROFILE		"Enable profiling"			OFF)
option(NDEBUG		"Disable debugging code"	OFF)
option(BUILD_TAGS	"Build tags file and cscope database"	OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
		${CMAKE_SOURCE_DIR}/cmake/Modules/)

file(STRINGS "GIT-VERSION-FILE" CUBMARK_VERSION)

include(CheckCXXCompilerFlag)
include(FindThreads)

check_cxx_compiler_flag(-std=c++0x CXX0X)
if(NOT CXX0X)
	message(ERROR "Compiler c++0x support required.")
endif(NOT CXX0X)

set(CUBMARK_USE_EXCEPTIONS 1)

if(STATIC_STDLIB)
	set(STATIC ${STATIC_STDLIB})
	# Remove "-rdynamic"
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
	# Remove "-Bdynamic"
	set(CMAKE_EXE_LINK_DYNAMIC_CXX_FLAGS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc")
	set(LINK_FLAGS "${LINK_FLAGS} -static -static-libgcc")
endif(STATIC_STDLIB)

if(NDEBUG)
	set(CUBMARK_NDEBUG 1)
else(NDEBUG)
	check_cxx_compiler_flag(-ggdb FLAG_GDB_DEBUG)
	check_cxx_compiler_flag(-g FLAG_GDB_DEBUG)
	check_cxx_compiler_flag(-rdynamic FLAG_RDYNAMIC)

	if(NOT FLAG_GDB_DEBUG AND NOT FLAG_DEBUG)
		message(FATAL_ERROR "Don't know how to enable debugging symbols")
	endif(NOT FLAG_GDB_DEBUG AND NOT FLAG_DEBUG)

	if(FLAG_GDB_DEBUG)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
	else(FLAG_GDB_DEBUG)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
	endif(FLAG_GDB_DEBUG)

	if(FLAG_RDYNAMIC AND NOT STATIC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic")
	endif(FLAG_RDYNAMIC AND NOT STATIC)
endif(NDEBUG)

if(PROFILE)
	check_cxx_compiler_flag(-pg FLAG_GDB_PROFILE)
	check_cxx_compiler_flag(-p FLAG_PROFILE)

	if(NOT (FLAG_GDB_PROFILE OR FLAG_PROFILE ))
		message(FATAL_ERROR "Don't know how to enable profiling")
	endif(NOT (FLAG_GDB_PROFILE OR FLAG_PROFILE ))

	if(FLAG_GDB_PROFILE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
		set(LINK_FLAGS "${LINK_FLAGS} -pg")
	else(FLAG_GDB_PROFILE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -p")
		set(LINK_FLAGS "${LINK_FLAGS} -p")
	endif(FLAG_GDB_PROFILE)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fno-inline-functions -fno-inline-functions-called-once")
endif(PROFILE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wconversion -Wall -W -pedantic -fpermissive")

set(Boost_USE_STATIC_LIBS ${STATIC})
set(Boost_USE_MULTITHREADED OFF)

find_package(Boost 1.34.0 COMPONENTS serialization REQUIRED)

# std::unique_ptr is supported from gcc 4.4.0 upwards
try_compile(HAVE_UNIQUE_PTR
		${CMAKE_BINARY_DIR}
		${CMAKE_SOURCE_DIR}/cmake/tests/has_unique_ptr.cpp)

macro(COMPILE_WITH_INTERFACE PACKAGE SYMBOL)
	if(WITH_${SYMBOL})
		set(${PACKAGE}_USE_STATIC_LIBS ${STATIC})

		find_package(${PACKAGE})
		set(CUBMARK_HAS_${SYMBOL} ${${PACKAGE}_FOUND})

		set(CUBMARK_INTERFACE_INCLUDE_DIRS ${CUBMARK_INTERFACE_INCLUDE_DIRS}
				${${PACKAGE}_INCLUDE_DIRS})

		set(CUBMARK_INTERFACE_LIBRARIES ${CUBMARK_INTERFACE_LIBRARIES}
				${${PACKAGE}_LIBRARIES})

		foreach(VAR ${ARGN})
			set(CUBMARK_INTERFACE_LIBRARIES  ${CUBMARK_INTERFACE_LIBRARIES}
					${${VAR}})
		endforeach(VAR ${ARGN})

		if(${PACKAGE}_FOUND)
			message("${PACKAGE} libraries found. Integration method will be available.")
		else(${PACKAGE}_FOUND)
			message("${PACKAGE} libraries NOT found. Check your include and library paths.")
		endif(${PACKAGE}_FOUND)
	endif(WITH_${SYMBOL})
endmacro(COMPILE_WITH_INTERFACE)

COMPILE_WITH_INTERFACE(Cubpack++ CUBPACK)
COMPILE_WITH_INTERFACE(r2d2lri R2D2LRI)
COMPILE_WITH_INTERFACE(HIntLib HINTLIB)
COMPILE_WITH_INTERFACE(GSL GSL GSLCBLAS_LIBRARIES)

if(CMAKE_Fortran_COMPILER MATCHES "gfortran.*")
	COMPILE_WITH_INTERFACE(DCUHRE DCUHRE)
else(CMAKE_Fortran_COMPILER MATCHES "gfortran.*")
	message("Could not find a working gfortran compiler. DCUHRE will not be available.")
endif(CMAKE_Fortran_COMPILER MATCHES "gfortran.*")

include_directories(src)

add_subdirectory (bin)
add_subdirectory (examples)
add_subdirectory (src)
add_subdirectory (doc)
add_subdirectory (tests)

