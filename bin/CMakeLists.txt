# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

add_executable(cubmark cubmark.cpp)
set_target_properties(cubmark PROPERTIES LINKER_LANGUAGE CXX)

find_package(Boost 1.34.0 COMPONENTS program_options REQUIRED)

target_link_libraries(cubmark
		cubmark_core
		${CMAKE_THREAD_LIBS_INIT}
		${Boost_PROGRAM_OPTIONS_LIBRARY}
		${Boost_SERIALIZATION_LIBRARY})
