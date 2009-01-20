AUTOMAKE_OPTIONS=subdir-objects

lib_LTLIBRARIES = libdisplay.la 
noinst_PROGRAMS = test_ogre 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libdisplay_la_SOURCES = \
../implementation/display.cpp \
../implementation/displayed_solid.cpp \
../implementation/explosion.cpp \
../implementation/ideal_target.cpp \
../implementation/identified_target.cpp \
../implementation/image.cpp \
../implementation/observer.cpp \
../implementation/oriented.cpp \
../implementation/positionned.cpp \
../implementation/space_dust.cpp \
../implementation/speed_indicator.cpp \
../implementation/target.cpp \
../implementation/target_with_selection.cpp \
../implementation/ogre/explosion.cpp \
../implementation/ogre/image.cpp \
../implementation/ogre/observer.cpp \
../implementation/ogre/ogre.cpp \
../implementation/ogre/oriented.cpp \
../implementation/ogre/positionned.cpp \
../implementation/ogre/real_world_view_point.cpp \
../implementation/ogre/speed_indicator.cpp \
../implementation/ogre/solid.cpp \
../implementation/ogre/universe.cpp \
../implementation/ogre/utility.cpp \
../implementation/ogre/laser_beam.cpp \
../implementation/ogre/space_dust.cpp \
../implementation/ogre/head_up_display.cpp \
../implementation/ogre/head_up_display/target.cpp \
../implementation/ogre/head_up_display/ideal_target.cpp \
../implementation/ogre/head_up_display/identified_target.cpp \
../implementation/ogre/head_up_display/target_with_selection.cpp \
../implementation/ogre/head_up_display/head_up_display_viewpoint.cpp


libdisplay_la_LDFLAGS = -no-undefined
libdisplay_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OGRE_LIBS) \
$(librlog_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

all-local:ressources.cfg plugins.cfg

# generates a correct ressources.cfg from main template
ressources.cfg:../../ressources.cfg.in
	cat ../../ressources.cfg.in | sed 's,@MEDIA_FOLDER\@,../../media,' > ressources.cfg

plugins.cfg:../../plugins.cfg.in
	cat ../../plugins.cfg.in \
	| sed 's,@INSTALL_OGRE_PLUGIN_FOLDER\@,@OGRE_PLUGIN_FOLDER@,' \
	| sed 's,@OGRE_PLUGIN_RENDER_SYSTEM\@,@OGRE_PLUGIN_RENDER_SYSTEM@,' \
	| sed 's,@OGRE_PLUGIN_EXTENSION\@,@OGRE_PLUGIN_EXTENSION@,'> plugins.cfg


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
