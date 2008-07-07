AUTOMAKE_OPTIONS=subdir-objects

lib_LTLIBRARIES = libdisplay.la 
noinst_PROGRAMS = test_ogre 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libdisplay_la_SOURCES = \
../implementation/display.cpp \
../implementation/explosion.cpp \
../implementation/target.cpp \
../implementation/ideal_target.cpp \
../implementation/identified_target.cpp \
../implementation/observer.cpp \
../implementation/space_dust.cpp \
../implementation/target_with_selection.cpp \
../implementation/ogre/explosion.cpp \
../implementation/ogre/image.cpp \
../implementation/ogre/observer.cpp \
../implementation/ogre/ogre.cpp \
../implementation/ogre/oriented.cpp \
../implementation/ogre/positionned.cpp \
../implementation/ogre/real_world_view_point.cpp \
../implementation/ogre/solid.cpp \
../implementation/ogre/universe.cpp \
../implementation/ogre/utility.cpp \
../implementation/ogre/laser_beam.cpp \
../implementation/ogre/menu.cpp \
../implementation/ogre/space_dust.cpp \
../implementation/ogre/target_displayer.cpp \
../implementation/ogre/head_up_display/target.cpp \
../implementation/ogre/head_up_display/ideal_target.cpp \
../implementation/ogre/head_up_display/identified_target.cpp \
../implementation/ogre/head_up_display/target_with_selection.cpp \
../implementation/ogre/head_up_display/target_displayer_viewpoint.cpp


libdisplay_la_LDFLAGS = -no-undefined
libdisplay_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OGRE_LIBS) \
$(librlog_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

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
