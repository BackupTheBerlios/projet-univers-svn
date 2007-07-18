AC_PREREQ(2.50)

# Version
AC_INIT([ProjetUnivers], 0.2.2)
AC_CONFIG_SRCDIR([sources/demonstration/demonstration.cpp])
#AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([ProjetUnivers], 0.2.2, NO-DEFINE)
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL
#AC_PROG_RANLIB


#########################
# Check programs presence
#########################


# Vérifie la présence d'un compilateur C++
AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CC

#####################
# Check libs presence
#####################

# Check/config CPPUNIT
AM_PATH_CPPUNIT(1.1.0)

# Vérifie la présence de flex
# et définit LEXLIB
AC_PROG_LEX

# Check/config Ogre3d
PKG_CHECK_MODULES(OGRE, [OGRE >= 1.0])
AC_SUBST(OGRE_CFLAGS)
AC_SUBST(OGRE_LIBS)

# Check boost
AX_BOOST_BASE

# Check/config OIS
PKG_CHECK_MODULES(OIS, [OIS >= 1.0])
AC_SUBST(OIS_CFLAGS)
AC_SUBST(OIS_LIBS)

# Check/config RLOG
PKG_CHECK_MODULES(librlog, [librlog >= 1.3])
AC_SUBST(librlog_CFLAGS)
AC_SUBST(librlog_LIBS)

# Check/config ODE
AC_CHECK_HEADERS([ode/ode.h],,
 			  AC_MSG_ERROR([ODE development library needed]))
AC_SUBST(ODE_LIBS, "-lode")

##################
# Config used libs
##################


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([limits.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Makefiles
AC_CONFIG_FILES([Makefile \
                 sources/Makefile \
                 sources/kernel/Makefile \
                 sources/kernel/compilation/Makefile \
                 sources/model/Makefile \
                 sources/model/compilation/Makefile \
                 sources/display/Makefile \
                 sources/display/compilation/Makefile \
                 sources/display/compilation/ogre/Makefile \
                 sources/demonstration/Makefile \
                 sources/demonstration/compilation/Makefile \
                 sources/input/Makefile \
                 sources/input/compilation/Makefile \
                 sources/action/Makefile \
                 sources/action/compilation/Makefile \
                 sources/physic/Makefile \
                 sources/physic/compilation/Makefile \
                 sources/physic/compilation/ode/Makefile \
                 ])

AC_OUTPUT
