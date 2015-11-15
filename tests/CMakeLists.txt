find_package(Boost 1.39.0 COMPONENTS unit_test_framework)
if(Boost_UNIT_TEST_FRAMEWORK_FOUND)
	ENABLE_TESTING()

    include_directories(${CUBMARK_INTERFACE_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

	add_executable (MethodInterface
			MethodInterface.cpp)

	target_link_libraries (MethodInterface
			cubmark_core
			${CMAKE_THREAD_LIBS_INIT}
			${Boost_SERIALIZATION_LIBRARY}
			${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

	if(Boost_USE_STATIC_LIBS)
		set_target_properties (MethodInterface PROPERTIES
				LINK_FLAGS  "-DBOOST_TEST_MAIN"
				COMPILE_FLAGS "-DBOOST_TEST_MAIN")
	else(Boost_USE_STATIC_LIBS)
		set_target_properties (MethodInterface PROPERTIES
				LINK_FLAGS  "-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN"
				COMPILE_FLAGS "-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN")
	endif(Boost_USE_STATIC_LIBS)

	add_test(MethodInterface MethodInterface)
endif()


