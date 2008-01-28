# Makefile pour Affichage

SUBDIRS = ogre

lib_LTLIBRARIES = libdisplay.la 

LDADD=ogre/libdisplay.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libdisplay_la_SOURCES = \
$(SOURCES)/display/implementation/display.cpp \
$(SOURCES)/display/implementation/hud_system.cpp


libdisplay_la_LDFLAGS = -no-undefined
libdisplay_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/display/compilation/ogre/libdisplayogre.la \
$(OGRE_LIBS) \
$(librlog_LIBS)


