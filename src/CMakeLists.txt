# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

file(GLOB_RECURSE CPP_FILES FOLLOW_SYMLINKS "*.cpp")
file(GLOB_RECURSE TEMPLATE_FILES FOLLOW_SYMLINKS "*.hpp")
file(GLOB_RECURSE HEADER_FILES FOLLOW_SYMLINKS "*.h")
set (SRC ${CPP_FILES} ${TEMPLATE_FILES} ${HEADER_FILES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
		${CMAKE_CURRENT_SOURCE_DIR}/cubmark/config.h)

add_library(cubmark_core STATIC
		IncompleteError.cpp
		InvalidNameError.cpp
		InvalidValueError.cpp
		Benchmark.cpp
		Definition.cpp
		Boundary.cpp
		Builder.cpp
		CaseResults.cpp
		SuiteResults.cpp
		CaseSpecification.cpp
		SuiteSpecification.cpp
		Sample.cpp
		Result.cpp
		StopTimer.cpp
		Scanner.cpp)

target_link_libraries(cubmark_core
		cubmark_debug
		cubmark_views
		cubmark_functions
		cubmark_method)

add_subdirectory(debug)
add_subdirectory(adapter)
add_subdirectory(views)
add_subdirectory(functions)
add_subdirectory(method)

add_custom_command(OUTPUT cscope.in.out cscope.out cscope.po.out
		COMMAND "cscope" "-q" "-b" ${SRC})

add_custom_command(OUTPUT tags
		COMMAND "ctags" "--extra=+q" "--fields=+m+s" ${SRC})

add_custom_target(dev-index DEPENDS tags cscope.in.out cscope.out cscope.po.out
		SOURCES ${SRC})

if(BUILD_TAGS)
	add_dependencies(cubmark_core dev-index)
endif(BUILD_TAGS)

