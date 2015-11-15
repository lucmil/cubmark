# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

macro(ADD_INTERFACE PACKAGE)
	if(${PACKAGE}_FOUND)
		set(CUBMARK_INTERFACE_SOURCES ${CUBMARK_INTERFACE_SOURCES}
				${ARGN})
	endif(${PACKAGE}_FOUND)
endmacro(ADD_INTERFACE PACKAGE)

ADD_INTERFACE(GSL
		MonteCarlo.cpp
		Qag2D.cpp
		QagRule.cpp
		RuleChain2D.cpp)

ADD_INTERFACE(Cubpack++
		CubpackIntegrand.cpp
		Cubpack.cpp)

ADD_INTERFACE(r2d2lri
		Constant.cpp
		R2d2lri.cpp)

ADD_INTERFACE(DCUHRE
		Dcuhre.cpp
		DcuhreIntegrand.cpp)

ADD_INTERFACE(HIntLib
		HIntLib.cpp
		HIntLibIntegrand.cpp)

include_directories(${CUBMARK_INTERFACE_INCLUDE_DIRS})

add_library(cubmark_method STATIC
		Adaptive.cpp
		TraceMethod.cpp
		MethodFactory.cpp
		Method.cpp
		${CUBMARK_INTERFACE_SOURCES})

target_link_libraries(cubmark_method
		cubmark_adapter
		cubmark_debug
		${CUBMARK_INTERFACE_LIBRARIES})

if(STATIC AND DCUHRE_FOUND)
	target_link_libraries(cubmark_method
			gfortran)
endif(STATIC AND DCUHRE_FOUND)
