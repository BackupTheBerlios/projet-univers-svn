lib_LTLIBRARIES = libsound.la

AUTOMAKE_OPTIONS=subdir-objects

SOURCES = $(top_srcdir)/sources
AM_CPPFLAGS = -I$(SOURCES)
AM_CXXFLAGS = $(PU_CXXFLAGS)

libsound_la_SOURCES = \
../implementation/collision.cpp \
../implementation/engine.cpp \
../implementation/listener.cpp \
../implementation/recursively_positionned.cpp \
../implementation/shot.cpp \
../implementation/sound.cpp \
../implementation/openal/background_sound.cpp \
../implementation/openal/collision.cpp \
../implementation/openal/engine.cpp \
../implementation/openal/file_stream.cpp \
../implementation/openal/filter.cpp \
../implementation/openal/listener.cpp \
../implementation/openal/manager.cpp \
../implementation/openal/ogg_cached_stream.cpp \
../implementation/openal/ogg_file_stream.cpp \
../implementation/openal/openal.cpp \
../implementation/openal/reader.cpp \
../implementation/openal/real_world_view_point.cpp \
../implementation/openal/shot.cpp \
../implementation/openal/sound_emitter.cpp \
../implementation/openal/sound_environnement.cpp \
../implementation/openal/sound_listener.cpp \
../implementation/openal/stream.cpp \
../implementation/openal/wav_file_stream.cpp \
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

all-local:ressources.cfg

# generates a correct ressources.cfg from main template
ressources.cfg:../../ressources.cfg.in
	cat ../../ressources.cfg.in | sed 's,@MEDIA_FOLDER\@,../../media,' > ressources.cfg

TESTS = test_sound 

# compile tests program without launching them so make build them
noinst_PROGRAMS = $(TESTS)

# launch tests in case of make check
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
../test/test_demonstration.cpp \
../test/test_openal_lib.cpp \
../test/test_moving_object.cpp \
../test/test_sound_environnement.cpp \
../test/test_sound_event.cpp

test_sound_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_sound_LDFLAGS = $(CPPUNIT_LIBS)
test_sound_LDADD = $(LDADD_OPTIONS)

