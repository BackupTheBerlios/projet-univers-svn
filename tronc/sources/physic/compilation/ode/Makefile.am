lib_LTLIBRARIES = libphysicode.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libphysicode_la_SOURCES = \
$(SOURCES)/physic/implementation/ode/real_world_view_point.cpp \
$(SOURCES)/physic/implementation/ode/physical_object.cpp \
$(SOURCES)/physic/implementation/ode/physical_world.cpp \
$(SOURCES)/physic/implementation/ode/solid.cpp 

libphysicode_la_LDFLAGS = \
	$(SHARED_FLAGS) \
	-L$(SOURCES)/kernel/compilation \
	-L$(SOURCES)/model/compilation \
	-L$(SOURCES)/physic/compilation

libphysicode_la_LIBADD = -lkernel -lmodel -lphysic $(ODE_LIBS) 

