lib_LTLIBRARIES = libphysicode.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libphysicode_la_SOURCES = \
$(SOURCES)/physic/implementation/ode/mass_property.cpp \
$(SOURCES)/physic/implementation/ode/ode.cpp \
$(SOURCES)/physic/implementation/ode/physic_system.cpp \
$(SOURCES)/physic/implementation/ode/physical_object.cpp \
$(SOURCES)/physic/implementation/ode/physical_world.cpp \
$(SOURCES)/physic/implementation/ode/solid.cpp \
$(SOURCES)/physic/implementation/ode/torque_generator.cpp \
$(SOURCES)/physic/implementation/ode/force_generator.cpp \
$(SOURCES)/physic/implementation/ode/collideable.cpp \
$(SOURCES)/physic/implementation/ode/laser_beam.cpp 


libphysicode_la_LDFLAGS = -no-undefined
libphysicode_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(ODE_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS)

