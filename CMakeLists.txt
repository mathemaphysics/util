cmake_minimum_required (VERSION 2.6)
project (util)

set (util_VERSION_MAJOR 1)
set (util_VERSION_MINOR 0)

option (OPENMPI
	"Turn on MPI functions"
	OFF)

add_library(util parse.c symtab.c cfgread.c graph.c combinadic.c trees.c)

# Search source directory for compile headers
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_BINARY_DIR}/include")

# Configure the project header
configure_file (
	"${PROJECT_SOURCE_DIR}/util_config.h.in"
    "${PROJECT_BINARY_DIR}/util_config.h"
	)

# Build the documentation (Sphinx, Doxygen)
add_subdirectory(doc)

# Install the configuration header
install (
    FILES "${PROJECT_BINARY_DIR}/util_config.h"
    DESTINATION "${PROJECT_SOURCE_DIR}"
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
