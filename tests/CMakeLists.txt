find_package(GTest REQUIRED)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/lib)

add_definitions(-DUNIT_TESTING=ON)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

file(GLOB cpp_sources ${CMAKE_SOURCE_DIR}/lib/*.cc)

file(GLOB cpp_tests test_*.cc)

foreach(file ${cpp_tests})
	get_filename_component(test_name ${file} NAME_WE)
	add_executable(${test_name} ${file} ${cpp_sources})

	target_link_libraries(${test_name} GTest::GTest)

	add_test(NAME ${test_name}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND ${test_name})
	add_dependencies(check ${test_name})
endforeach()
