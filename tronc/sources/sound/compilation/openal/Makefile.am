lib_LTLIBRARIES = libsoundcode.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libsoundcode_la_SOURCES = \
$(SOURCES)/sound/implementation/openal/observer.cpp \
$(SOURCES)/sound/implementation/openal/openal.cpp \
$(SOURCES)/sound/implementation/openal/real_world_view_point.cpp \
$(SOURCES)/sound/implementation/openal/background_sound.cpp \
$(SOURCES)/sound/implementation/openal/sound_emitter.cpp \
$(SOURCES)/sound/implementation/openal/sound_listener.cpp


libsoundcode_la_LDFLAGS = -no-undefined
libsoundcode_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(openal_LIBS) \
$(librlog_LIBS)

