SUBDIRS = openal

lib_LTLIBRARIES = libsound.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

LDADD=ode/libsoundcode.la

libsound_la_SOURCES = \
$(SOURCES)/sound/implementation/engine.cpp \
$(SOURCES)/sound/implementation/listener.cpp \
$(SOURCES)/sound/implementation/sound.cpp

libsound_la_LDFLAGS = -no-undefined
libsound_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/sound/compilation/openal/libsoundcode.la \
$(OGRE_LIBS) \
$(librlog_LIBS) \
$(libXML_LIBS) \
$(openal_LIBS) \
$(ogg_LIBS) \
$(libsndfile_LIBS) \
$(vorbis_LIBS) \
$(vorbisfile_LIBS)

# made of several tests because 
# @see https://bugs.launchpad.net/ubuntu/+source/openal/+bug/187997
TESTS = test_background_sound test_cone_property test_moving_object \
test_openal_lib test_sound_environnement test_filter

check_PROGRAMS = $(TESTS)

LDADD_OPTIONS = \
libsound.la \
openal/libsoundcode.la \
../../model/compilation/libmodel.la \
../../kernel/compilation/libkernel.la \
$(OGRE_LIBS) \
$(librlog_LIBS) \
$(libXML_LIBS) \
$(openal_LIBS) \
$(ogg_LIBS) \
$(libsndfile_LIBS) \
$(vorbis_LIBS) \
$(vorbisfile_LIBS) \
$(freealut_LIBS)

test_background_sound_SOURCES = \
../test/test_sound.cpp \
../test/test_background_sound.cpp
test_background_sound_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_background_sound_LDFLAGS = $(CPPUNIT_LIBS)
test_background_sound_LDADD = $(LDADD_OPTIONS)

test_cone_property_SOURCES = \
../test/test_sound.cpp \
../test/test_cone_property.cpp
test_cone_property_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_cone_property_LDFLAGS = $(CPPUNIT_LIBS)
test_cone_property_LDADD = $(LDADD_OPTIONS)

test_moving_object_SOURCES = \
../test/test_sound.cpp \
../test/test_moving_object.cpp
test_moving_object_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_moving_object_LDFLAGS = $(CPPUNIT_LIBS)
test_moving_object_LDADD = $(LDADD_OPTIONS)

test_openal_lib_SOURCES = \
../test/test_sound.cpp \
../test/test_openal_lib.cpp
test_openal_lib_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_openal_lib_LDFLAGS = $(CPPUNIT_LIBS)
test_openal_lib_LDADD = $(LDADD_OPTIONS)

test_sound_environnement_SOURCES = \
../test/test_sound.cpp \
../test/test_sound_environnement.cpp
test_sound_environnement_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_sound_environnement_LDFLAGS = $(CPPUNIT_LIBS)
test_sound_environnement_LDADD = $(LDADD_OPTIONS)

test_filter_SOURCES = \
../test/test_sound.cpp \
../test/test_filter.cpp
test_filter_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_filter_LDFLAGS = $(CPPUNIT_LIBS)
test_filter_LDADD = $(LDADD_OPTIONS)
