lib_LTLIBRARIES = libsound.la

AUTOMAKE_OPTIONS=subdir-objects

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS = $(PU_CXXFLAGS)

libsound_la_SOURCES = \
../implementation/listener.cpp \
../implementation/engine.cpp \
../implementation/sound.cpp \
../implementation/openal/openal.cpp \
../implementation/openal/real_world_view_point.cpp \
../implementation/openal/manager.cpp \
../implementation/openal/reader.cpp \
../implementation/openal/wav_reader.cpp \
../implementation/openal/ogg_reader.cpp \
../implementation/openal/sound_listener.cpp \
../implementation/openal/listener.cpp \
../implementation/openal/sound_emitter.cpp \
../implementation/openal/background_sound.cpp \
../implementation/openal/collision.cpp \
../implementation/openal/engine.cpp \
../implementation/openal/sound_environnement.cpp \
../implementation/openal/filter.cpp \
../implementation/openal/efx/@efx_name@.cpp 

libsound_la_CXXFLAGS = $(PU_CXXFLAGS)
libsound_la_LDFLAGS = -no-undefined
libsound_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
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
TESTS = test_sound 

check_PROGRAMS = $(TESTS)

LDADD_OPTIONS = \
libsound.la \
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

test_sound_SOURCES = \
../test/test_sound.cpp \
../test/test_background_sound.cpp \
../test/test_cone_property.cpp \
../test/test_openal_lib.cpp \
../test/test_moving_object.cpp \
../test/test_sound_environnement.cpp \
../test/test_sound_event.cpp

test_sound_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_sound_LDFLAGS = $(CPPUNIT_LIBS)
test_sound_LDADD = $(LDADD_OPTIONS)

