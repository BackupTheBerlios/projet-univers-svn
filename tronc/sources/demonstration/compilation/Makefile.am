bin_PROGRAMS = demonstration 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I../..
AM_CXXFLAGS=$(PU_CXXFLAGS)

bindirdir=$(bindir)
bindir_DATA = demonstration.config ogre.cfg

demonstration_SOURCES = \
../demonstration.cpp

demonstration_LDADD = \
../../kernel/compilation/libkernel.la \
../../model/compilation/libmodel.la \
../../display/compilation/libdisplay.la \
../../input/compilation/libinput.la \
../../physic/compilation/libphysic.la \
../../artificial_intelligence/compilation/libai.la \
../../gui/compilation/libgui.la \
../../sound/compilation/libsound.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase


