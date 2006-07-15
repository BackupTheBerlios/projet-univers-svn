AC_PREREQ(2.50)

# Version
AC_INIT([ProjetUnivers], 0.1.0)
AC_CONFIG_SRCDIR([sources/demonstration/demonstration.cpp])
AM_CONFIG_HEADER(sources/config.h)
AM_INIT_AUTOMAKE([ProjetUnivers], 0.1.0)
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL


################
# Defines
################


# le code des templates doit être inclus
# obsolete ?
AC_DEFINE(_INC_TEMP_CODE_, 1, \ 
	[Mis si le code des templates doit être inclus dans les spécifications])


#############################################
# Vérification de la présences des programmes
#############################################


# Vérifie la présence d'un compilateur C++
AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CC


# Vérifie la présence de ranlib
AC_PROG_RANLIB


# Vérifie la présence de xsltproc
# pour transformer les docbooks en html
AC_CHECK_PROG(GENERER_DOCBOOK, xsltproc, true, false)


# Vérifie la présence de doxygen
# pour générer la doc du programme en html
AC_CHECK_PROG(GENERER_DOCUMENTATION_PROGRAMME, doxygen, true, false)

# vérifie la présence de open c++ pour compiler les méta-programmes
# \todo
#   si ce n'ets pas présent ne pas provoquer d'erreur mais empecher la 
#   compilation du module meta...
AC_PATH_PROG(OCC, occ2, occ2)
AC_PATH_PROG(LIBOCC_CONFIG, libocc-config, no)
AC_SUBST(OCC_LIBS, "-L/usr/local/lib -locc -lltdl")
AC_SUBST(OCC_CXXFLAGS, `$LIBOCC_CONFIG --cflags`)

#if test "$LIBOCC_CONFIG" != "no" ; then
#OCC_LIBS = `$LIBOCC_CONFIG --libs`
#OCC_CXXFLAGS = `$LIBOCC_CONFIG --cflags`
#fi


######################################
# Vérification de la présences des lib
######################################


# Vérifie la présence de cppunit 
# pour gerer les tests de non régrétion

# définit les variables CPPUNIT_CFLAGS et CPPUNIT_LIBS
AM_PATH_CPPUNIT(1.1.0)


# Vérifie la présence de glib
# et définit les variables 
# GLIB_LIBS et GLIB_CFLAGS
#AM_PATH_GLIB(1.2)

# Vérifie la présence de flex
# et définit LEXLIB
AC_PROG_LEX

# vérifie la présence de Ogre3d
PKG_CHECK_MODULES(OGRE, [OGRE >= 1.2])
AC_SUBST(OGRE_CFLAGS)
AC_SUBST(OGRE_LIBS)

# vérifie la présence de boost signals
AX_BOOST_SIGNALS


# vérifie la présence de OIS
PKG_CHECK_MODULES(OIS, [OIS >= 0.7])
AC_SUBST(OIS_CFLAGS)
AC_SUBST(OIS_LIBS)

# vérifie la présence de RLOG
PKG_CHECK_MODULES(librlog, [librlog >= 1.3])
AC_SUBST(librlog_CFLAGS)
AC_SUBST(librlog_LIBS)


####################################
# Configuration des libs utilisaires
####################################


# Configuration de AceDB
# définit les variables ACEDB_CFLAGS et ACEDB_LIBS
if test `uname -o` == GNU/Linux; then
  AC_SUBST(ACEDDB_CFLAGS, "-fwritable-strings -Wall -DACEDB4 -DLINUX")
  AC_SUBST(ACEDB_LIBS, "libace.a libfree.a")
else
  AC_SUBST(ACEDDB_CFLAGS, "-fwritable-strings -Wall -DACEDB4 -DWIN32")
  AC_SUBST(ACEDB_LIBS, "libace.dll libfree.dll")
fi


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([limits.h stdlib.h])


# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# la liste des makefile à générer
AC_CONFIG_FILES([Makefile \
                 sources/Makefile \
                 sources/base/Makefile \
                 sources/base/compilation/Makefile \
                 sources/noyau/Makefile \
                 sources/noyau/compilation/Makefile \
                 sources/modele/Makefile \
                 sources/modele/compilation/Makefile \
                 sources/meta/Makefile \
                 sources/meta/compilation/Makefile \
                 sources/controle/compilation/Makefile \
                 sources/controle/Makefile \
                 sources/affichage/Makefile \
                 sources/affichage/compilation/Makefile \
                 sources/affichage/compilation/ogre/Makefile \
                 sources/test-acedb/Makefile \
                 sources/outils/Makefile \
                 sources/outils/compilateur/Makefile \
                 sources/outils/compilateur/compilation/Makefile \
                 sources/demonstration/Makefile \
                 sources/demonstration/compilation/Makefile \
                 sources/entrees/Makefile \
                 sources/entrees/compilation/Makefile \
                 sources/action/Makefile \
                 sources/action/compilation/Makefile \
                 ])

AC_OUTPUT
