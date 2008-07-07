lib_LTLIBRARIES = libphysic.la

AUTOMAKE_OPTIONS=subdir-objects

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libphysic_la_SOURCES = \
../implementation/laser_beam.cpp \
../implementation/physic.cpp \
../implementation/solid_physical_object.cpp \
../implementation/ode/mass_property.cpp \
../implementation/ode/ode.cpp \
../implementation/ode/physic_system.cpp \
../implementation/ode/physical_object.cpp \
../implementation/ode/physical_world.cpp \
../implementation/ode/solid.cpp \
../implementation/ode/torque_generator.cpp \
../implementation/ode/force_generator.cpp \
../implementation/ode/collideable.cpp \
../implementation/ode/laser_beam.cpp 


libphysic_la_LDFLAGS = -no-undefined
libphysic_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(ODE_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS)

TESTS = test_physic

check_PROGRAMS = $(TESTS)

test_physic_SOURCES = \
../test/test_physic.cpp \
../test/test_demonstration.cpp \
../test/test_dragger.cpp \
../test/test_collision.cpp \
../test/test_shooting_helper.cpp \
../test/test_ode.cpp 


test_physic_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_physic_LDFLAGS = $(CPPUNIT_LIBS)
test_physic_LDADD = \
../../kernel/compilation/libkernel.la \
../../model/compilation/libmodel.la \
libphysic.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(ODE_LIBS) \
$(libXML_LIBS)

memory_check : test_physic
	valgrind ./test_physic