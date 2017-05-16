cmake_minimum_required (VERSION 3.5)
project (FFMaxFlow)

set(CMAKE_CXX_COMPILER /usr/bin/g++-5)
enable_testing()

# Download and unpack googletest at configure time
configure_file(CMakeListsGoogleTest.txt googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

include_directories($ENV{BOOST_ROOT})
include_directories(../src)

set(SOURCES ../src/ResidualGraph.cpp
			../src/Graph.cpp 
			../src/DijkstraFattestPath.cpp
			../src/FordFulkersonFattestPath.cpp
			../src/DimacsReader.cpp )

add_executable(push_relabel_boost push_relabel_boost.cpp ${SOURCES})

set_target_properties(push_relabel_boost PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# set(MEASURE_SOURCES )

# #For each *.cpp file in /measure folder, generate a executable
# foreach( measure_source ${MEASURE_SOURCES} )
# 	#string( REPLACE ".cpp" "" measure_name ${measure_source} )
# 	get_filename_component(measure_name ${measure_source} NAME_WE)
# 	add_executable( ${measure_name} ${measure_source} ${SOURCES} )

# 	set_target_properties(${measure_name} PROPERTIES
# 	    CXX_STANDARD 11
# 	    CXX_STANDARD_REQUIRED YES
# 	    CXX_EXTENSIONS NO
# 	)
# endforeach( measure_source ${MEASURE_SOURCES} )

set(TESTS_SOURCES tests/tests_residual_graph.cpp
				  tests/tests_dijkstrafattestpath.cpp
				  tests/tests_ff_fattest_path.cpp
				  tests/tests_dimacs_reader.cpp)

foreach( tests_source ${TESTS_SOURCES} )
	get_filename_component(tests_name ${tests_source} NAME_WE)
	add_executable(${tests_name} ${tests_source} ${SOURCES})
	set_target_properties(${tests_name} PROPERTIES
	    CXX_STANDARD 11
	    CXX_STANDARD_REQUIRED YES
	    CXX_EXTENSIONS NO
	)
	target_link_libraries(${tests_name} gtest_main)
	add_test(${tests_name} ${tests_name})
endforeach( tests_source ${TESTS_SOURCES} )


