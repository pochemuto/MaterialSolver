cmake_minimum_required(VERSION 3.1)
project(MaterialSolver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

enable_testing ()
add_subdirectory (test build/test)

# SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR}/../.. ${CMAKE_BINARY_DIR}/../../common/cmake)

add_executable(solver ${SOURCE_FILES} math/integrate.h MaterialSolver.cpp MaterialSolver.h struct/Material.h sqlite/sqlite3.h sqlite/sqlite3.c sqlite/sqlite3ext.h sqlite3pp/sqlite3pp.h sqlite3pp/sqlite3pp.cpp Database.cpp Database.h struct/Polynomial.h minimizer/CompassSearch.h struct/Result.h function/FixedThickness.cpp function/FixedThickness.h struct/Result.cpp minimizer/ExhaustiveSearch.h)
