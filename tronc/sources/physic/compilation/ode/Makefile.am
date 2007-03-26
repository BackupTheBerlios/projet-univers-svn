lib_LTLIBRARIES = libphysicode.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libphysicode_la_SOURCES = \
$(SOURCES)/physic/implementation/ode/real_world_view_point.cpp \
$(SOURCES)/physic/implementation/ode/physical_object.cpp \
$(SOURCES)/physic/implementation/ode/physical_world.cpp \
$(SOURCES)/physic/implementation/ode/solid.cpp 

libphysicode_la_LIBADD = \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(ODE_LIBS) 

