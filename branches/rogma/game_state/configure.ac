AC_PREREQ(2.50)

# Version
AC_INIT([ProjetUnivers], 0.3)
AC_CONFIG_SRCDIR([sources/demonstration/demonstration.cpp])
AM_INIT_AUTOMAKE([ProjetUnivers], 0.3, NO-DEFINE)

AC_LIBTOOL_WIN32_DLL 
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL

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

# Check/config Ogre3d
PKG_CHECK_MODULES(OGRE, [OGRE >= 1.4])
AC_SUBST(OGRE_CFLAGS)
AC_SUBST(OGRE_LIBS)

# Check/config boost
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
AC_CHECK_HEADERS([ode/ode.h])
AC_SUBST(ODE_LIBS, "-lode")

# check OpenAL
PKG_CHECK_MODULES(openal, [openal >= 0.0.8])
AC_SUBST(openal_LIBS)
AC_SUBST(openal_CFLAGS)

# OpenAL efx extension : windows only 
AC_CHECK_HEADER([AL/efx.h],efx=efx,efx=efx_none)
# the header used for efx, either
# sound/implementation/openal/efx/efx.h
# sound/implementation/openal/efx/efx_none.h
AC_SUBST(efx_name,$efx)

PKG_CHECK_MODULES(freealut, [freealut >= 1.1])
AC_SUBST(freealut_LIBS)


# check Ogg
PKG_CHECK_MODULES(ogg, [ogg >= 1.1.3])
AC_SUBST(ogg_LIBS)

# check Vorbis
PKG_CHECK_MODULES(vorbis, [vorbis >= 1.2])
AC_SUBST(vorbis_LIBS)

# check Vorbisfile
PKG_CHECK_MODULES(vorbisfile, [vorbisfile >= 1.2])
AC_SUBST(vorbisfile_LIBS)

# check Libsndfile
PKG_CHECK_MODULES(libsndfile, [sndfile >= 1.0.17])
AC_SUBST(libsndfile_LIBS)

# check CEGUI
PKG_CHECK_MODULES(CEGUI, [CEGUI >= 0.5])
AC_SUBST(CEGUI_LIBS)

# check CEGUI-OGRE
PKG_CHECK_MODULES(CEGUI_OGRE, [CEGUI-OGRE >= 1.4])
AC_SUBST(CEGUI_OGRE_LIBS)
AC_SUBST(CEGUI_OGRE_CFLAGS)

# check libxml2
PKG_CHECK_MODULES(libXML, [libxml-2.0 >= 2.0])
AC_SUBST(libXML_LIBS)
AC_SUBST(libXML_CFLAGS)

# check clanlib
AC_PATH_PROG(CLANLIB_CONFIG, clanlib-config, no)
if test "x$CLANLIB_CONFIG" = xno; then
  AC_SUBST(CLAN_LIBS,"")
  AC_SUBST(CLAN_CXXFLAGS,"")
  
else
  AC_SUBST(CLAN_LIBS, `$CLANLIB_CONFIG --libs`)
  AC_SUBST(CLAN_CXXFLAGS, `$CLANLIB_CONFIG --cflags`)
fi
AM_CONDITIONAL(HAVE_CLANLIB, test "x$CLANLIB_CONFIG" != "xno")

# Global c++ variable :
PU_CXXFLAGS="$OGRE_CFLAGS $OIS_CFLAGS $librlog_CFLAGS $CEGUI_OGRE_CFLAGS $libXML_CFLAGS"
AC_SUBST(PU_CXXFLAGS)

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
                 sources/game/Makefile \
                 sources/game/compilation/Makefile \
                 sources/input/Makefile \
                 sources/input/compilation/Makefile \
                 sources/action/Makefile \
                 sources/action/compilation/Makefile \
                 sources/physic/Makefile \
                 sources/physic/compilation/Makefile \
                 sources/physic/compilation/ode/Makefile \
                 sources/sound/Makefile \
                 sources/sound/compilation/Makefile \
                 sources/sound/compilation/openal/Makefile \
                 sources/sound/implementation/openal/extension.h \
                 sources/artificial_intelligence/Makefile \
                 sources/artificial_intelligence/compilation/Makefile \
                 ])

AC_OUTPUT
