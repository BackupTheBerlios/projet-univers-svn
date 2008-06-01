lib_LTLIBRARIES = libsoundcode.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libsoundcode_la_SOURCES = \
$(SOURCES)/sound/implementation/openal/openal.cpp \
$(SOURCES)/sound/implementation/openal/real_world_view_point.cpp \
$(SOURCES)/sound/implementation/openal/manager.cpp \
$(SOURCES)/sound/implementation/openal/reader.cpp \
$(SOURCES)/sound/implementation/openal/wav_reader.cpp \
$(SOURCES)/sound/implementation/openal/ogg_reader.cpp \
$(SOURCES)/sound/implementation/openal/sound_listener.cpp \
$(SOURCES)/sound/implementation/openal/listener.cpp \
$(SOURCES)/sound/implementation/openal/sound_emitter.cpp \
$(SOURCES)/sound/implementation/openal/background_sound.cpp \
$(SOURCES)/sound/implementation/openal/collision.cpp \
$(SOURCES)/sound/implementation/openal/engine.cpp \
$(SOURCES)/sound/implementation/openal/sound_environnement.cpp \
$(SOURCES)/sound/implementation/openal/filter.cpp \
$(SOURCES)/sound/implementation/openal/efx/@efx_name@.cpp 



libsoundcode_la_LDFLAGS = -no-undefined
libsoundcode_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(openal_LIBS) \
$(ogg_LIBS) \
$(libsndfile_LIBS) \
$(vorbis_LIBS) \
$(vorbisfile_LIBS)
