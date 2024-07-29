cmake_minimum_required (VERSION 2.6)
project (util)

include (GNUInstallDirs)

set (util_VERSION_MAJOR 1)
set (util_VERSION_MINOR 0)

option (OPENMPI
	"Turn on MPI functions"
	OFF)

add_library(util SHARED parse.c symtab.c cfgread.c graph.c combinadic.c trees.c)

# Search source directory for compile headers
include_directories("${CMAKE_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_BINARY_DIR}")
include_directories("${CMAKE_BINARY_DIR}/include")

# Configure the project header
configure_file (
	"${CMAKE_SOURCE_DIR}/util_config.h.in"
    	"${CMAKE_BINARY_DIR}/util_config.h"
)

configure_file (
	"${CMAKE_SOURCE_DIR}/util.pc.in"
	"${CMAKE_BINARY_DIR}/util.pc"
	)

# Build the documentation (Sphinx, Doxygen)
add_subdirectory(doc)

install (
	FILES "${CMAKE_BINARY_DIR}/util.pc"
	DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig"
    )

# Install everything and headers
install (
    TARGETS util
    ARCHIVE
      DESTINATION lib
    INCLUDES
      DESTINATION include
    )

# vim: set tabstop=4:expandtab:smarttab
