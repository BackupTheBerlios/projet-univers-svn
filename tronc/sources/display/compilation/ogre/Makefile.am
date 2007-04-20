lib_LTLIBRARIES = libdisplayogre.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libdisplayogre_la_SOURCES = \
$(SOURCES)/display/implementation/ogre/destroyable.cpp \
$(SOURCES)/display/implementation/ogre/observer.cpp \
$(SOURCES)/display/implementation/ogre/ogre.cpp \
$(SOURCES)/display/implementation/ogre/positionned.cpp \
$(SOURCES)/display/implementation/ogre/real_world_view_point.cpp \
$(SOURCES)/display/implementation/ogre/solid.cpp \
$(SOURCES)/display/implementation/ogre/universe.cpp

libdisplayogre_la_LDFLAGS = \
	$(SHARED_FLAGS) \
	-L$(SOURCES)/kernel/compilation \
	-L$(SOURCES)/model/compilation 

libdisplayogre_la_LIBADD = -lkernel -lmodel $(OGRE_LIBS)

