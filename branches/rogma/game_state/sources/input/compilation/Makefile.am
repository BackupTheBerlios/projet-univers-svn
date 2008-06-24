#Makefile pour entrees

lib_LTLIBRARIES = libinput.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libinput_la_SOURCES = \
$(SOURCES)/input/implementation/game_state.cpp \
$(SOURCES)/input/implementation/input.cpp \
$(SOURCES)/input/implementation/input_controler_set.cpp \
$(SOURCES)/input/implementation/input_object.cpp \
$(SOURCES)/input/implementation/keyboard.cpp \
$(SOURCES)/input/implementation/menu.cpp \
$(SOURCES)/input/implementation/mouse.cpp \
$(SOURCES)/input/implementation/player.cpp \
$(SOURCES)/input/implementation/joystick.cpp

libinput_la_LDFLAGS = -no-undefined
libinput_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/display/compilation/ogre/libdisplayogre.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OIS_LIBS) \
$(OGRE_LIBS) \
$(librlog_LIBS)

TESTS = test_input 

check_PROGRAMS = $(TESTS)

test_input_SOURCES = \
../test/test_input.cpp \
../test/test_input_system.cpp \
../test/test_menu.cpp \
../test/test_player_configuration.cpp

test_input_CXXFLAGS = $(PU_CXXFLAGS) $(CPPUNIT_CFLAGS)
test_input_LDFLAGS = $(CPPUNIT_LIBS)
test_input_LDADD = \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/display/compilation/ogre/libdisplayogre.la \
$(SOURCES)/input/compilation/libinput.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OIS_LIBS)
