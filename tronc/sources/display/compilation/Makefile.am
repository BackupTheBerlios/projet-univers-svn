# Makefile pour Affichage

SUBDIRS = ogre

lib_LTLIBRARIES = libdisplay.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libdisplay_la_SOURCES = \
$(SOURCES)/display/implementation/display.cpp \
$(SOURCES)/display/implementation/exception.cpp \
$(SOURCES)/display/implementation/real_world_view_point.cpp 


libdisplay_la_LIBADD = \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la 


