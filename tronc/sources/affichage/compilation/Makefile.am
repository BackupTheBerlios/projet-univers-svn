SUBDIRS = ogre

noinst_LIBRARIES = libaffichage.a 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libaffichage_a_SOURCES = \
$(SOURCES)/affichage/implantation/affichage.cpp \
$(SOURCES)/affichage/implantation/point_de_vue.cpp