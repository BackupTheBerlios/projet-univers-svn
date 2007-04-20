bin_PROGRAMS = demonstration 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I../..

demonstration_SOURCES = \
../demonstration.cpp

demonstration_LDFLAGS= '-ldl' \
	-L$(SOURCES)/kernel/compilation \
	-L$(SOURCES)/model/compilation \
	-L$(SOURCES)/display/compilation \
	-L$(SOURCES)/display/compilation/ogre \
	-L$(SOURCES)/action/compilation \
	-L$(SOURCES)/input/compilation \
	-L$(SOURCES)/physic/compilation \
	-L$(SOURCES)/physic/compilation/ode 
	
demonstration_LDADD = \
-lkernel -lmodel -ldisplay -ldisplayogre \
-linput -laction $(OIS_LIBS) -lphysic -lphysicode
