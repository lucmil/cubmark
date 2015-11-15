# CMakeLists.txt for Cubature Benchmark
# Copyright (C) 2009 Łukasz Lis
#
# This file is free software. You have unlimited permission to copy, modify
# and distribute it.

if(BUILD_EXAMPLES)
	add_executable (adapter_benchmark
			adapter_benchmark.cpp)

	add_executable (adapter_function_template
			adapter_function_template.cpp)

	add_executable (adapter_function_template_stl
			adapter_function_template_stl.cpp)

	add_executable (wigner_grid
			wigner_grid.cpp)

	target_link_libraries (adapter_benchmark
			cubmark_adapter
			cubmark_core)

	target_link_libraries (adapter_function_template
			cubmark_adapter)

	target_link_libraries (adapter_function_template_stl
			cubmark_adapter)

	target_link_libraries (wigner_grid
			cubmark_debug
			cubmark_core
			cubmark_functions
			cubmark_adapter)

	if(CUBMARK_HAS_GSL)
		add_executable (integration
				integration.cpp)

		target_link_libraries (integration cubmark_core)

	endif(CUBMARK_HAS_GSL)

endif(BUILD_EXAMPLES)
