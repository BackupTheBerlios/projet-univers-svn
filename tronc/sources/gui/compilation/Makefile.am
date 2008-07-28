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
$(OGRE_LIBS) \
$(librlog_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

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

