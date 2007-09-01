SUBDIRS = openal

lib_LTLIBRARIES = libsound.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

LDADD=ode/libsoundcode.la

libsound_la_SOURCES = \
$(SOURCES)/sound/implementation/sound.cpp

libphysic_la_LDFLAGS = -no-undefined
libphysic_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/sound/compilation/openal/libsoundcode.la \
$(OPENAL_LIBS) \
$(librlog_LIBS)