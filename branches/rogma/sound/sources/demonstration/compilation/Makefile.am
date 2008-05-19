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
$(SOURCES)/artificial_intelligence/compilation/libai.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

TESTS = demonstration
check_PROGRAMS = $(TESTS)
