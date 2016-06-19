#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(util, 0.1, ryan-p-daly@uiowa.edu)
AM_INIT_AUTOMAKE([])
AC_CONFIG_SRCDIR([symtab.c])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h strings.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_C_CONST
AC_PROG_RANLIB

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero memmove])
AC_CONFIG_FILES( [Makefile test/Makefile examples/Makefile util.pc] )
AC_OUTPUT
