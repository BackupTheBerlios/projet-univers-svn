#Makefile pour entrees

lib_LTLIBRARIES = libinput.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libinput_la_SOURCES = \
../implementation/active_menu.cpp \
../implementation/input.cpp \
../implementation/input_object.cpp \
../implementation/edited_player_configuration.cpp \
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

TESTS = test_input 

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

