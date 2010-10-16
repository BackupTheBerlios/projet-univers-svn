lib_LTLIBRARIES = libinput.la 
bin_PROGRAMS = autoconfig_joystick 

AUTOMAKE_OPTIONS=subdir-objects

SOURCES = $(top_srcdir)/sources
AM_CPPFLAGS = -I$(SOURCES)
AM_CXXFLAGS = $(PU_WARNINGS) $(PU_CXXFLAGS)

libinput_la_SOURCES = \
../implementation/active_menu.cpp \
../implementation/input.cpp \
../implementation/input_listener.cpp \
../implementation/input_object.cpp \
../implementation/edited_player_configuration.cpp \
../implementation/ois/edited_player_configuration.cpp \
../implementation/ois/input_controler_set.cpp \
../implementation/ois/input_menu.cpp \
../implementation/ois/joystick.cpp \
../implementation/ois/keyboard.cpp \
../implementation/ois/menu.cpp \
../implementation/ois/mouse.cpp \
../implementation/ois/ois.cpp \
../implementation/ois/player.cpp \
../implementation/ois/player_configuration.cpp

libinput_la_LDFLAGS = -no-undefined
libinput_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OIS_LIBS) \
$(OGRE_LIBS) \
$(librlog_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

if WINDOWS_COMPILATION
autoconfig_joystick_SOURCES=../implementation/ois/autoconfig_joystick_windows.cpp
endif

if LINUX_COMPILATION
autoconfig_joystick_SOURCES=../implementation/ois/autoconfig_joystick_linux.cpp
endif 

autoconfig_joystick_LDFLAGS = -no-undefined
autoconfig_joystick_LDFLAGS += $(dinput8_LIBS)

# 
all-local:ressources.cfg plugins.cfg

# generates a correct ressources.cfg from main template
ressources.cfg:../../ressources.cfg.in
	cat ../../ressources.cfg.in | sed 's,@MEDIA_FOLDER\@,../../media,' > ressources.cfg

plugins.cfg:../../plugins.cfg.in
	cat ../../plugins.cfg.in \
	| sed 's,@INSTALL_OGRE_PLUGIN_FOLDER\@,@OGRE_PLUGIN_FOLDER@,' \
	| sed 's,@OGRE_PLUGIN_RENDER_SYSTEM\@,@OGRE_PLUGIN_RENDER_SYSTEM@,' \
	| sed 's,@OGRE_PLUGIN_EXTENSION\@,@OGRE_PLUGIN_EXTENSION@,'> plugins.cfg


TESTS = test_input 

# compile tests program without launching them so make build them
noinst_PROGRAMS = $(TESTS)

# launch tests in case of make check
check_PROGRAMS = $(TESTS)

test_input_SOURCES = \
../test/test_input.cpp \
../test/test_input_system.cpp \
../test/test_player_configuration.cpp

test_input_CXXFLAGS = $(PU_CXXFLAGS) $(CPPUNIT_CFLAGS)
test_input_LDFLAGS = $(CPPUNIT_LIBS)
test_input_LDADD = \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/display/compilation/libdisplay.la \
libinput.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OIS_LIBS) 

