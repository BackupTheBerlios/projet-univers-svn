# Makefile pour Affichage

SUBDIRS = ogre

lib_LTLIBRARIES = libdisplay.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libdisplay_la_SOURCES = \
$(SOURCES)/display/implementation/display.cpp \
$(SOURCES)/display/implementation/exception.cpp \
$(SOURCES)/display/implementation/trait.cpp \
$(SOURCES)/display/implementation/object.cpp \
$(SOURCES)/display/implementation/view_point.cpp 


libdisplay_la_LIBADD = \
$(SOURCES)/base/compilation/libkernel.la \
$(SOURCES)/modele/compilation/libmodel.la 

#all-local :
#	cp libdisplay.la $(SOURCES)/compilation/libdisplay.la

# tests

TESTS = test_display

check_PROGRAMS = $(TESTS) 

test_display_SOURCES = \
$(SOURCES)/display/test/test_display.cpp \
$(SOURCES)/display/test/test_view_point.cpp 

test_display_CXXFLAGS = $(CPPUNIT_CFLAGS) 
test_display_LDFLAGS = $(CPPUNIT_LIBS) 

test_display_LDADD = \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/display/compilation/ogre/libdisplayogre.la \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(librlog_LIBS) 

