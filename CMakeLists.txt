cmake_minimum_required (VERSION 2.6)
project (tutorial)

set (tutorial_VERSION_MAJOR 1)
set (tutorial_VERSION_MINOR 0)

option (OPENMPI
	"Turn on MPI functions"
	OFF)

add_library(util tutorial.cxx)

include_directories("${PROJECT_BINARY_DIR}")

if (USE_MYMATH)
	add_subdirectory(stat)
	include_directories("${PROJECT_SOURCE_DIR}/stat")
	set (EXTRA_LIBS ${EXTRA_LIBS} stat)
	target_link_libraries(tutorial stat)
endif (USE_MYMATH)

configure_file (
	"${PROJECT_SOURCE_DIR}/tutorial_config.h.in"
	"${PROJECT_BINARY_DIR}/tutorial_config.h"
	)

install (TARGETS tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/tutorial_config.h" DESTINATION include)

# vim: set tabstop=4:expandtab:smarttab
