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


# le code des templates doit �tre inclus
# obsolete ?
AC_DEFINE(_INC_TEMP_CODE_, 1, \ 
	[Mis si le code des templates doit �tre inclus dans les sp�cifications])


#############################################
# V�rification de la pr�sences des programmes
#############################################


# V�rifie la pr�sence d'un compilateur C++
AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CC


# V�rifie la pr�sence de ranlib
AC_PROG_RANLIB


# V�rifie la pr�sence de xsltproc
# pour transformer les docbooks en html
AC_CHECK_PROG(GENERER_DOCBOOK, xsltproc, true, false)


# V�rifie la pr�sence de doxygen
# pour g�n�rer la doc du programme en html
AC_CHECK_PROG(GENERER_DOCUMENTATION_PROGRAMME, doxygen, true, false)

# v�rifie la pr�sence de open c++ pour compiler les m�ta-programmes
# \todo
#   si ce n'ets pas pr�sent ne pas provoquer d'erreur mais empecher la 
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
# V�rification de la pr�sences des lib
######################################


# V�rifie la pr�sence de cppunit 
# pour gerer les tests de non r�gr�tion

# d�finit les variables CPPUNIT_CFLAGS et CPPUNIT_LIBS
AM_PATH_CPPUNIT(1.1.0)


# V�rifie la pr�sence de glib
# et d�finit les variables 
# GLIB_LIBS et GLIB_CFLAGS
#AM_PATH_GLIB(1.2)

# V�rifie la pr�sence de flex
# et d�finit LEXLIB
AC_PROG_LEX

# v�rifie la pr�sence de Ogre3d
PKG_CHECK_MODULES(OGRE, [OGRE >= 1.2])
AC_SUBST(OGRE_CFLAGS)
AC_SUBST(OGRE_LIBS)

# v�rifie la pr�sence de boost signals et de serialization (shared_ptr)
AX_BOOST_BASE
AX_BOOST_SIGNALS
AX_BOOST_SERIALIZATION

# v�rifie la pr�sence de OIS
PKG_CHECK_MODULES(OIS, [OIS >= 0.7])
AC_SUBST(OIS_CFLAGS)
AC_SUBST(OIS_LIBS)

# v�rifie la pr�sence de RLOG
PKG_CHECK_MODULES(librlog, [librlog >= 1.3])
AC_SUBST(librlog_CFLAGS)
AC_SUBST(librlog_LIBS)


####################################
# Configuration des libs utilisaires
####################################


# Configuration de AceDB
# d�finit les variables ACEDB_CFLAGS et ACEDB_LIBS
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

# la liste des makefile � g�n�rer
AC_CONFIG_FILES([Makefile \
                 sources/Makefile \
                 sources/base/Makefile \
                 sources/base/compilation/Makefile \
                 sources/modele/Makefile \
                 sources/modele/compilation/Makefile \
                 sources/affichage/Makefile \
                 sources/affichage/compilation/Makefile \
                 sources/affichage/compilation/ogre/Makefile \
                 sources/demonstration/Makefile \
                 sources/demonstration/compilation/Makefile \
                 sources/entrees/Makefile \
                 sources/entrees/compilation/Makefile \
                 sources/action/Makefile \
                 sources/action/compilation/Makefile \
                 ])

AC_OUTPUT
