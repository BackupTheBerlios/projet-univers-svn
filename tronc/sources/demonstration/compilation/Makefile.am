bin_PROGRAMS = demonstration ship test pu

SOURCES = $(top_srcdir)/sources
AM_CPPFLAGS = -I../..
AM_CXXFLAGS=$(PU_CXXFLAGS)

libraries = \
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
$(libode_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase

bindirdir=$(bindir)
bindir_DATA = demonstration.config ogre.cfg

demonstration_SOURCES = ../demonstration.cpp
ship_SOURCES = ../ship.cpp
test_SOURCES = ../test.cpp
pu_SOURCES = ../pu.cpp

demonstration_LDADD = $(libraries)
ship_LDADD = $(libraries)
test_LDADD = $(libraries)
pu_LDADD = $(libraries)

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
	
TESTS = test_demonstration

# compile tests program without launching them so make build them
noinst_PROGRAMS = $(TESTS)

# launch tests in case of make check
check_PROGRAMS = $(TESTS)

test_demonstration_SOURCES = \
../test/test_demonstration.cpp \
../test/test_model_controler.cpp

test_demonstration_LDADD = \
../../kernel/compilation/libkernel.la \
../../model/compilation/libmodel.la \
../../display/compilation/libdisplay.la \
../../physic/compilation/libphysic.la \
../../artificial_intelligence/compilation/libai.la \
../../sound/compilation/libsound.la \
$(CPPUNIT_LIBS) \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(libode_LIBS) \
$(CEGUI_LIBS) \
$(CEGUI_OGRE_LIBS) \
-lCEGUIFalagardWRBase
