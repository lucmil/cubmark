# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

add_subdirectory(statistics)

add_library(cubmark_views STATIC
		FullViewBuilder.cpp
		HistogramViewBuilder.cpp
		TestpackViewBuilder.cpp
		RawViewBuilder.cpp
		ResultFormat.cpp
		ViewBuilder.cpp
		ViewFactory.cpp)

target_link_libraries(cubmark_views
		${Boost_SERIALIZATION_LIBRARY}
		cubmark_statistics
		cubmark_core)
