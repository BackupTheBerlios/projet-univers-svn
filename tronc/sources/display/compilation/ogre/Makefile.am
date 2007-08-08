lib_LTLIBRARIES = libdisplayogre.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libdisplayogre_la_SOURCES = \
$(SOURCES)/display/implementation/ogre/destroyable.cpp \
$(SOURCES)/display/implementation/ogre/observer.cpp \
$(SOURCES)/display/implementation/ogre/ogre.cpp \
$(SOURCES)/display/implementation/ogre/oriented.cpp \
$(SOURCES)/display/implementation/ogre/positionned.cpp \
$(SOURCES)/display/implementation/ogre/real_world_view_point.cpp \
$(SOURCES)/display/implementation/ogre/solid.cpp \
$(SOURCES)/display/implementation/ogre/universe.cpp \
$(SOURCES)/display/implementation/ogre/utility.cpp 

libdisplayogre_la_LDFLAGS = -no-undefined
libdisplayogre_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OGRE_LIBS) \
$(librlog_LIBS)

