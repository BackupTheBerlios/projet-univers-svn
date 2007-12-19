bin_PROGRAMS = demonstration 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I../..
AM_CXXFLAGS=$(PU_CXXFLAGS)

demonstration_SOURCES = \
../demonstration.cpp

demonstration_LDADD = \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/display/compilation/ogre/libdisplayogre.la \
$(SOURCES)/input/compilation/libinput.la \
$(SOURCES)/action/compilation/libaction.la \
$(SOURCES)/physic/compilation/libphysic.la \
$(SOURCES)/physic/compilation/ode/libphysicode.la \
$(OIS_LIBS)  \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase \
$(libXML_LIBS)
