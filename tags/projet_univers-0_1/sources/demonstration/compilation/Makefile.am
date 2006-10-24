bin_PROGRAMS = demonstration 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I../..

demonstration_SOURCES = \
../demonstration.cpp

demonstration_LDFLAGS='-ldl'
demonstration_LDADD = \
$(SOURCES)/base/compilation/libbase.la \
$(SOURCES)/affichage/compilation/libaffichage.la \
$(SOURCES)/affichage/compilation/ogre/libaffichageogre.la \
$(SOURCES)/action/compilation/libaction.la \
$(SOURCES)/entrees/compilation/libentrees.la \
$(SOURCES)/modele/compilation/libmodele.la \
$(OIS_LIBS) \
$(librlog_LIBS) 
