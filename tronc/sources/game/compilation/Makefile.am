lib_LTLIBRARIES = libgame.la

AUTOMAKE_OPTIONS=subdir-objects

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libgame_la_SOURCES = \
../implementation/game.cpp \
../implementation/game_state.cpp \
../implementation/game_with_lifetime.cpp \
../implementation/controler/game_controler_set.cpp \
../implementation/controler/game_state.cpp


libgame_la_LDFLAGS = -no-undefined
libgame_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/input/compilation/libinput.la \
$(SOURCES)/physic/compilation/libphysic.la \
$(SOURCES)/artificial_intelligence/compilation/libai.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

# tests

TESTS = test_game

check_PROGRAMS = $(TESTS)

test_game_SOURCES = \
../test/test_game.cpp \
../test/test_game_state.cpp 

test_game_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS) 
test_game_LDADD = \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/input/compilation/libinput.la \
$(SOURCES)/physic/compilation/libphysic.la \
$(SOURCES)/artificial_intelligence/compilation/libai.la \
$(SOURCES)/game/compilation/libgame.la \
$(CPPUNIT_LIBS) \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase



