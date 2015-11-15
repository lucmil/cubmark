# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

add_library(cubmark_functions STATIC
		urng.cpp
		F1.cpp
		G1.cpp
		G2.cpp
		G3.cpp
		G4.cpp
		G5.cpp
		G6.cpp
		W1.cpp
		W2.cpp
		W3.cpp
		QP1.cpp
		RandomFunctorBuilder.cpp
		TestFunctorBuilder.cpp
		TestFunctorFactory.cpp
		F1Builder.cpp
		G1Builder.cpp
		G2Builder.cpp
		G3Builder.cpp
		G4Builder.cpp
		G5Builder.cpp
		G6Builder.cpp
		W1Builder.cpp
		W2Builder.cpp
		W3Builder.cpp
		QP1Builder.cpp
		P1Builder.cpp
		RD28Builder.cpp
		RD29Builder.cpp
		RD31Builder.cpp
		RD35Builder.cpp
		wavefunc/W1WaveFunc.cpp
		wavefunc/W3WaveFunc.cpp
		wavefunc/W2WaveFunc.cpp)

target_link_libraries(cubmark_functions
		cubmark_core
		cubmark_adapter)
