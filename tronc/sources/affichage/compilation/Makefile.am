# Makefile pour Affichage

SUBDIRS = ogre

lib_LTLIBRARIES = libaffichage.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libaffichage_la_SOURCES = \
$(SOURCES)/affichage/implantation/affichage.cpp \
$(SOURCES)/affichage/implantation/point_de_vue.cpp

libaffichage_la_LIBADD = \
$(SOURCES)/base/compilation/libbase.la \
$(BOOST_SIGNALS_LIB)

#all-local :
#	cp libaffichage.la $(SOURCES)/compilation/libaffichage.la
