bin_PROGRAMS = demonstration ship 

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
$(CPPUNIT_LIBS) \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

ship_SOURCES = \
../ship.cpp

ship_LDADD = \
../../kernel/compilation/libkernel.la \
../../model/compilation/libmodel.la \
../../display/compilation/libdisplay.la \
../../input/compilation/libinput.la \
../../physic/compilation/libphysic.la \
../../artificial_intelligence/compilation/libai.la \
../../gui/compilation/libgui.la \
../../sound/compilation/libsound.la \
$(CPPUNIT_LIBS) \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

all-local:ressources.cfg plugins.cfg copy_joystick_configurator

# generates a correct ressources.cfg from main template
ressources.cfg:../../ressources.cfg.in
	cat ../../ressources.cfg.in | sed 's,@MEDIA_FOLDER\@,../../media,' > ressources.cfg

plugins.cfg:../../plugins.cfg.in
	cat ../../plugins.cfg.in \
	| sed 's,@INSTALL_OGRE_PLUGIN_FOLDER\@,@OGRE_PLUGIN_FOLDER@,' \
	| sed 's,@OGRE_PLUGIN_RENDER_SYSTEM\@,@OGRE_PLUGIN_RENDER_SYSTEM@,' \
	| sed 's,@OGRE_PLUGIN_EXTENSION\@,@OGRE_PLUGIN_EXTENSION@,'> plugins.cfg

copy_joystick_configurator:
	cp $(SOURCES)/input/compilation/autoconfig_joystick* .
	