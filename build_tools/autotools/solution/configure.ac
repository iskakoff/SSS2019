#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(FULL-PACKAGE-NAME, VERSION, BUG-REPORT-ADDRESS)

m4_include([m4/ax_boost_base.m4])
m4_include([m4/ax_boost_filesystem.m4])

AC_CONFIG_SRCDIR([])
AC_CONFIG_HEADER([config.h])

AC_LANG(C++)
AC_PROG_CXX


AX_BOOST_BASE([1.66.0])
AX_BOOST_FILESYSTEM([])

LIBS=-L$(BOOST_LDFLAGS) $(BOOST_FILESYSTEM_LIB)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
