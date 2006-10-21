lib_LTLIBRARIES = libaffichageogre.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libaffichageogre_la_SOURCES = \
$(SOURCES)/affichage/implantation/ogre/destructible.cpp \
$(SOURCES)/affichage/implantation/ogre/vue.cpp \
$(SOURCES)/affichage/implantation/ogre/observateur.cpp \
$(SOURCES)/affichage/implantation/ogre/ogre.cpp \
$(SOURCES)/affichage/implantation/ogre/point_de_vue.cpp \
$(SOURCES)/affichage/implantation/ogre/positionne.cpp \
$(SOURCES)/affichage/implantation/ogre/solide.cpp \
$(SOURCES)/affichage/implantation/ogre/univers.cpp

libaffichageogre_la_LIBADD = \
$(SOURCES)/base/compilation/libbase.la \
$(SOURCES)/modele/compilation/libmodele.la \
$(OGRE_LIBS) 

