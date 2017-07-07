cmake_minimum_required (VERSION 3.5)
project (MatchingHopcroftKarp)

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

#include_directories($ENV{BOOST_ROOT})
#link_directories("$ENV{BOOST_ROOT}/stage/lib/")
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
find_package(Boost 1.63 REQUIRED COMPONENTS filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(../src)
include_directories(../blossom5-v2.05)

set(SOURCES ../src/tsp_aprox_christofides.cpp
			../src/tspaprox_christofides_enhanced.cpp
			../blossom5-v2.05/PMduals.cpp
			../blossom5-v2.05/PMexpand.cpp
			../blossom5-v2.05/PMinterface.cpp
			../blossom5-v2.05/PMrepair.cpp
			../blossom5-v2.05/PMmain.cpp
			../blossom5-v2.05/PMshrink.cpp
			../blossom5-v2.05/PMinit.cpp
			../blossom5-v2.05/MinCost/MinCost.cpp
			../blossom5-v2.05/GEOM/GPMinit.cpp
			../blossom5-v2.05/GEOM/GPMinterface.cpp
			../blossom5-v2.05/GEOM/GPMkdtree.cpp
			../blossom5-v2.05/GEOM/GPMmain.cpp)

add_executable(tsp_aprox tsp_aprox.cpp ${SOURCES})
set_target_properties(tsp_aprox PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_executable(tsp_aprox_enhanced tsp_aprox_enhanced.cpp ${SOURCES})
set_target_properties(tsp_aprox_enhanced PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

set(MEASURE_SOURCES measure/measure.cpp)

#For each *.cpp file in /measure folder, generate a executable
foreach( measure_source ${MEASURE_SOURCES} )
	#string( REPLACE ".cpp" "" measure_name ${measure_source} )
	get_filename_component(measure_name ${measure_source} NAME_WE)
	add_executable( ${measure_name} ${measure_source} ${SOURCES} )
	target_link_libraries(${measure_name} ${Boost_LIBRARIES})
	set_target_properties(${measure_name} PROPERTIES
	    CXX_STANDARD 14
	    CXX_STANDARD_REQUIRED YES
	    CXX_EXTENSIONS NO
	)
endforeach( measure_source ${MEASURE_SOURCES} )

set(TESTS_SOURCES tests/tests_mst_prim.cpp
				  tests/tests_odd_degree.cpp
				  tests/tests_min_perf_match.cpp
				  tests/tests_greedy_perf_match.cpp
				  tests/tests_eulerian_circuit.cpp
				  tests/tests_hamiltonian_transf.cpp
				  tests/tests_tsp_aprox.cpp
				  tests/tests_enhanced_mst_prim.cpp)

foreach( tests_source ${TESTS_SOURCES} )
	get_filename_component(tests_name ${tests_source} NAME_WE)
	add_executable(${tests_name} ${tests_source} ${SOURCES})
	set_target_properties(${tests_name} PROPERTIES
	    CXX_STANDARD 14
	    CXX_STANDARD_REQUIRED YES
	    CXX_EXTENSIONS NO
	)
	target_link_libraries(${tests_name} gtest_main)
	add_test(${tests_name} ${tests_name})
endforeach( tests_source ${TESTS_SOURCES} )


