lib_LTLIBRARIES = libphysicode.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libphysicode_la_SOURCES = \
$(SOURCES)/physic/implementation/ode/physic_system.cpp \
$(SOURCES)/physic/implementation/ode/physical_object.cpp \
$(SOURCES)/physic/implementation/ode/physical_world.cpp \
$(SOURCES)/physic/implementation/ode/solid.cpp \
$(SOURCES)/physic/implementation/ode/torque_generator.cpp \
$(SOURCES)/physic/implementation/ode/force_generator.cpp 


libphysicode_la_LIBADD = \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(ODE_LIBS) 

