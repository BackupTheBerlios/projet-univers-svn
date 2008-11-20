AUTOMAKE_OPTIONS=subdir-objects

lib_LTLIBRARIES = libgui.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libgui_la_SOURCES = \
../implementation/gui.cpp \
../implementation/active_menu.cpp \
../implementation/edited_player_configuration.cpp \
../implementation/cegui/cegui.cpp \
../implementation/cegui/command_interpretor.cpp \
../implementation/cegui/gui_controler_set.cpp \
../implementation/cegui/menu.cpp \
../implementation/cegui/player_configuration.cpp \
../implementation/cegui/scripting_module.cpp


libgui_la_LDFLAGS = -no-undefined
libgui_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/input/compilation/libinput.la \
$(OGRE_LIBS) \
$(librlog_LIBS) \
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
  
TESTS = test_gui 

check_PROGRAMS = $(TESTS)

test_gui_SOURCES = \
../test/test_gui.cpp \
../test/test_menu.cpp


test_gui_CXXFLAGS = $(PU_CXXFLAGS) $(CPPUNIT_CFLAGS)
test_gui_LDFLAGS = $(CPPUNIT_LIBS)
test_gui_LDADD = \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/input/compilation/libinput.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/gui/compilation/libgui.la \
$(OIS_LIBS) 
