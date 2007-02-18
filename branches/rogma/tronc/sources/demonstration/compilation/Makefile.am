bin_PROGRAMS = demonstration 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I../..

demonstration_SOURCES = \
../demonstration.cpp

demonstration_LDFLAGS='-ldl'
demonstration_LDADD = \
$(OIS_LIBS) \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/display/compilation/ogre/libdisplayogre.la \
$(SOURCES)/action/compilation/libaction.la \
$(SOURCES)/input/compilation/libinput.la \
$(SOURCES)/model/compilation/libmodel.la \
$(librlog_LIBS) 
