lib_LTLIBRARIES = libdisplayogre.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libdisplayogre_la_SOURCES = \
$(SOURCES)/display/implementation/ogre/destroyable.cpp \
$(SOURCES)/display/implementation/ogre/explosion.cpp \
$(SOURCES)/display/implementation/ogre/observer.cpp \
$(SOURCES)/display/implementation/ogre/ogre.cpp \
$(SOURCES)/display/implementation/ogre/oriented.cpp \
$(SOURCES)/display/implementation/ogre/positionned.cpp \
$(SOURCES)/display/implementation/ogre/real_world_view_point.cpp \
$(SOURCES)/display/implementation/ogre/solid.cpp \
$(SOURCES)/display/implementation/ogre/universe.cpp \
$(SOURCES)/display/implementation/ogre/utility.cpp \
$(SOURCES)/display/implementation/ogre/laser_beam.cpp \
$(SOURCES)/display/implementation/ogre/menu.cpp \
$(SOURCES)/display/implementation/ogre/target_displayer.cpp \
$(SOURCES)/display/implementation/ogre/head_up_display/target.cpp \
$(SOURCES)/display/implementation/ogre/head_up_display/ideal_target.cpp \
$(SOURCES)/display/implementation/ogre/head_up_display/identified_target.cpp \
$(SOURCES)/display/implementation/ogre/head_up_display/target_with_selection.cpp \
$(SOURCES)/display/implementation/ogre/head_up_display/target_displayer_viewpoint.cpp

libdisplayogre_la_LDFLAGS = -no-undefined
libdisplayogre_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OGRE_LIBS) \
$(librlog_LIBS)

