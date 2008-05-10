# Makefile pour Affichage

SUBDIRS = ogre

lib_LTLIBRARIES = libdisplay.la 
noinst_PROGRAMS = test_ogre 

LDADD=ogre/libdisplay.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libdisplay_la_SOURCES = \
$(SOURCES)/display/implementation/display.cpp \
$(SOURCES)/display/implementation/explosion.cpp \
$(SOURCES)/display/implementation/target.cpp \
$(SOURCES)/display/implementation/ideal_target.cpp \
$(SOURCES)/display/implementation/identified_target.cpp 

libdisplay_la_LDFLAGS = -no-undefined
libdisplay_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/display/compilation/ogre/libdisplayogre.la \
$(OGRE_LIBS) \
$(librlog_LIBS)

TESTS = test_display

check_PROGRAMS = $(TESTS)

# unit tests 
# at first basic tests
# then game logic test
# finally a global test
test_display_SOURCES = \
../test/test_display.cpp \
../test/test_model_view.cpp \
../test/test_target.cpp

test_display_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_display_LDFLAGS = $(CPPUNIT_LIBS)
test_display_LDADD = \
libdisplay.la \
ogre/libdisplayogre.la \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

test_ogre_SOURCES = \
../test/test_ogre.cpp

test_ogre_LDADD = \
$(OIS_LIBS) \
$(OGRE_LIBS) 
