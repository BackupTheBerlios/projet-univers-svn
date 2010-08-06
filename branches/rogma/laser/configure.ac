AC_PREREQ(2.50)

# Version
AC_INIT([ProjetUnivers], 0.3.3)
AC_CONFIG_SRCDIR([sources/demonstration/demonstration.cpp])
AM_INIT_AUTOMAKE([1.9 tar-pax -Wall])

# svn revision
AC_SUBST(SVN_REVISION, `svnversion|tr -d '\n'`)

AC_CONFIG_MACRO_DIR([m4])

AC_LIBTOOL_WIN32_DLL 
AC_PROG_LIBTOOL
AM_PROG_LIBTOOL

#########################
# Check programs presence
#########################


AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CC

#####################
# Check libs presence
#####################

# Check/config CPPUNIT
AM_PATH_CPPUNIT(1.1.0)

# Check/config Ogre3d
PKG_CHECK_MODULES(OGRE, [OGRE >= 1.6])
AC_SUBST(OGRE_CFLAGS)
AC_SUBST(OGRE_LIBS)

# Check/config boost
AX_BOOST_BASE(1.34.1)

# Check/config OIS
PKG_CHECK_MODULES(OIS, [OIS >= 1.0])
AC_SUBST(OIS_CFLAGS)
AC_SUBST(OIS_LIBS)

# Check/config RLOG
PKG_CHECK_MODULES(librlog, [librlog >= 1.3])
AC_SUBST(librlog_CFLAGS)
AC_SUBST(librlog_LIBS)

# Check/config ODE
PKG_CHECK_MODULES(libode, [ode >= 0.11])
AC_SUBST(libode_CFLAGS)
AC_SUBST(libode_LIBS)

# check OpenAL
PKG_CHECK_MODULES(openal, [openal >= 1.1])
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
PKG_CHECK_MODULES(CEGUI_OGRE, [CEGUI-OGRE >= 1.6])
AC_SUBST(CEGUI_OGRE_LIBS)
AC_SUBST(CEGUI_OGRE_CFLAGS)

# check libxml2
PKG_CHECK_MODULES(libXML, [libxml-2.0 >= 2.0])
AC_SUBST(libXML_LIBS)
AC_SUBST(libXML_CFLAGS)

# Global c++ variable :
PU_CXXFLAGS="$OGRE_CFLAGS $OIS_CFLAGS $librlog_CFLAGS $CEGUI_OGRE_CFLAGS $libXML_CFLAGS $libode_CFLAGS -DdNODEBUG"
AC_SUBST(PU_CXXFLAGS)

PU_WARNINGS="-W -Wall -Wconversion -Wshadow -Wwrite-strings"
AC_SUBST(PU_WARNINGS)

PU_TESTS_WARNINGS="-W -Wall -Wconversion -Wshadow -Wwrite-strings"
AC_SUBST(PU_TESTS_WARNINGS)

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

AC_CHECK_HEADER([tclap/CmdLine.h],[havetclap=yes],[havetclap=no])
if test "x$havetclap" = xno; then
  AC_MSG_ERROR("Error : you need libtclap-dev")
fi

## platform dependent configuration
# ogre plugin configuration 
# generates plugin.cfg and ogre.cfg for tests
# we define variables depending on platform
if test "x$build_os" = xmingw32; then
  # windows+mingw
  # caculate path for ogre plugins 
  ogre_path=`find / -name "RenderSystem_GL.dll" | sed -e 's/RenderSystem_GL.dll//'`
  # we must transform the cygwin path to a windows path with escaped backslash
  AC_SUBST(OGRE_PLUGIN_FOLDER,`./winpath.sh $ogre_path 1`)
  AC_SUBST(OGRE_PLUGIN_EXTENSION,"dll")
  AC_SUBST(OGRE_PLUGIN_RENDER_SYSTEM,"RenderSystem_Direct3D9")
  AC_SUBST(OGRE_USED_RENDER_SYSTEM,"Direct3D9 Rendering Subsystem")
  # on Windows platform, ogre dlls are inside the release
  AC_SUBST(INSTALL_OGRE_PLUGIN_FOLDER,".")
  # on Windows platform, media folder is inside the release
  AC_SUBST(MEDIA_FOLDER,"media")
  # on windows we use direct input 8 for joystick autoconfig
  PKG_CHECK_MODULES(dinput8, [dinput8 >= 1])
elif test "x$build_os" = xlinux-gnu; then
  # linux
  # path for ogre plugins 
  AC_SUBST(OGRE_PLUGIN_FOLDER,`pkg-config --variable=plugindir OGRE`)
  AC_SUBST(OGRE_PLUGIN_EXTENSION,"so")
  AC_SUBST(OGRE_PLUGIN_RENDER_SYSTEM,"RenderSystem_GL")
  AC_SUBST(OGRE_USED_RENDER_SYSTEM,"OpenGL Rendering Subsystem")
  # on Linux platform, ogre so are globals 
  AC_SUBST(INSTALL_OGRE_PLUGIN_FOLDER,`pkg-config --variable=plugindir OGRE`)
  # on Linux platform, media folder is inside the /usr/share... like folder
  AC_SUBST(MEDIA_FOLDER,'${pkgdatadir}')
  # on linux joystick autoconfig is self evident
  dinput8_LIBS=''
fi
AC_SUBST(dinput8_LIBS)

AM_CONDITIONAL(WINDOWS_COMPILATION,test "x$build_os" = xmingw32)
AM_CONDITIONAL(LINUX_COMPILATION,test "x$build_os" = xlinux-gnu)


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
                 print-version \
                 Doxyfile \
                 readme \
								 sources/projet_univers.h \
                 sources/Makefile \
                 sources/kernel/Makefile \
                 sources/kernel/compilation/Makefile \
                 sources/model/Makefile \
                 sources/model/compilation/Makefile \
                 sources/display/Makefile \
                 sources/display/compilation/Makefile \
                 sources/display/compilation/ogre.cfg \
                 sources/demonstration/Makefile \
                 sources/demonstration/compilation/Makefile \
                 sources/demonstration/compilation/ogre.cfg \
                 sources/input/Makefile \
                 sources/input/compilation/Makefile \
                 sources/input/compilation/ogre.cfg \
                 sources/physic/Makefile \
                 sources/physic/compilation/Makefile \
                 sources/sound/Makefile \
                 sources/sound/compilation/Makefile \
                 sources/sound/implementation/openal/extension.h \
                 sources/artificial_intelligence/Makefile \
                 sources/artificial_intelligence/compilation/Makefile \
                 sources/gui/Makefile \
                 sources/gui/compilation/Makefile \
                 sources/gui/compilation/ogre.cfg \
                 ])

AC_OUTPUT
