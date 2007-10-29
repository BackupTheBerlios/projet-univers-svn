SUBDIRS = openal

lib_LTLIBRARIES = libsound.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

LDADD=ode/libsoundcode.la

libsound_la_SOURCES = \
$(SOURCES)/sound/implementation/sound.cpp

libsound_la_LDFLAGS = -no-undefined
libsound_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/sound/compilation/openal/libsoundcode.la \
$(openal_LIBS) \
$(librlog_LIBS)

TESTS = test_sound

check_PROGRAMS = $(TESTS)

test_sound_SOURCES = \
../test/test_sound.cpp \
../test/test_cone_propertie.cpp



test_sound_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_sound_LDFLAGS = $(CPPUNIT_LIBS)
test_sound_LDADD = \
libsound.la \
openal/libsoundcode.la \
../../model/compilation/libmodel.la \
../../kernel/compilation/libkernel.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(openal_LIBS)

