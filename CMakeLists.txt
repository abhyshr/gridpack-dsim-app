cmake_minimum_required(VERSION 2.6.4)

set(GRIDPACK_DIR $ENV{GRIDPACK_DIR})
message(${GRIDPACK_DIR})
if (DEFINED $GRIDPACK_DIR)
   message( FATAL_ERROR "Need to set environmental variable GRIDPACK_DIR to the localtion of GRIDPACK INSTALLATION")
endif()

include("${GRIDPACK_DIR}/lib/GridPACK.cmake")

project(DSim)

set(CMAKE_BUILD_TYPE DEBUG)

enable_language(CXX)

gridpack_setup()

add_definitions(${GRIDPACK_DEFINITIONS})
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(BEFORE ${GRIDPACK_INCLUDE_DIRS})

add_executable(dsim.x
	dsim_app.cpp
	src/dsim.cpp
	src/dsimnetwork.cpp
	src/dsimfactory.cpp
	src/base_gen_model.cpp
	src/classical_gen_model.cpp
)

target_link_libraries(dsim.x ${GRIDPACK_LIBS})
