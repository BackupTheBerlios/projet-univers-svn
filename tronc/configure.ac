AC_PREREQ(2.50)

AC_INIT([ProjetUnivers], 0.1.0)
AC_CONFIG_SRCDIR([sources/demonstration/demonstration.cpp])


AM_CONFIG_HEADER(sources/config.h)
AM_INIT_AUTOMAKE([ProjetUnivers], 0.1.0)

AC_DEFINE(_INC_TEMP_CODE_, 1, [Mis si le code des templates doit être inclus \
dans les spécifications])

# Checks for programs.
AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CC

# vérifie la présence de xsltproc pour générer les docs
AC_CHECK_PROG(xsltproc)

# vérifie la présence de cppunit pour gerer les tests
AM_PATH_CPPUNIT(1.1.0)
AC_PROG_RANLIB

# vérifie la présence de open c++ pour compiler les méta-programmes
AC_PATH_PROG(OCC, occ2, occ2)

# vérifie la présence de Ogre3d
PKG_CHECK_MODULES(OGRE, [OGRE >= 0.13])
AC_SUBST(OGRE_CFLAGS)
AC_SUBST(OGRE_LIBS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([limits.h stdlib.h])


# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

AC_CONFIG_FILES([Makefile \
                 sources/Makefile \
                 sources/base/Makefile \
                 sources/base/compilation/Makefile \
                 sources/noyau/Makefile \
                 sources/noyau/compilation/Makefile \
                 sources/modele/Makefile \
                 sources/modele/compilation/Makefile \
                 sources/meta/Makefile \
                 sources/meta/compilation/Makefile] \
                 sources/controle/compilation/Makefile \
                 sources/controle/Makefile)
                 
#                 sources/demonstration/Makefile])
# Checks for library functions.
AC_OUTPUT
