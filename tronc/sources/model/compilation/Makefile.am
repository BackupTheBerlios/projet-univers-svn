lib_LTLIBRARIES = libmodel.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS = $(PU_CXXFLAGS)

libmodel_la_SOURCES = \
../implementation/acceleration.cpp \
../implementation/angular_speed.cpp \
../implementation/distance.cpp \
../implementation/destroyable.cpp \
../implementation/dragger.cpp \
../implementation/duration.cpp \
../implementation/energy.cpp \
../implementation/engine.cpp \
../implementation/engine_control.cpp \
../implementation/exception.cpp \
../implementation/force.cpp \
../implementation/force_generator.cpp \
../implementation/mass.cpp \
../implementation/massive.cpp \
../implementation/mobile.cpp \
../implementation/model.cpp \
../implementation/mesh.cpp \
../implementation/name.cpp \
../implementation/observer.cpp \
../implementation/orientation.cpp \
../implementation/oriented.cpp \
../implementation/physical_object.cpp \
../implementation/physical_world.cpp \
../implementation/position.cpp \
../implementation/positionned.cpp \
../implementation/solid.cpp \
../implementation/speed.cpp \
../implementation/guidance_system.cpp \
../implementation/guidance_control.cpp \
../implementation/stabilizer.cpp \
../implementation/stellar_system.cpp \
../implementation/torque_generator.cpp \
../implementation/universe.cpp \
../implementation/whole.cpp \
../implementation/stick.cpp \
../implementation/throttle.cpp \
../implementation/laser.cpp \
../implementation/laser_beam.cpp \
$(SOURCES)/model/implementation/logic.cpp \
$(SOURCES)/model/implementation/logic_laser_beam.cpp \
$(SOURCES)/model/implementation/logic_system.cpp 


libmodel_la_LDFLAGS = -no-undefined
libmodel_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(OGRE_LIBS) \
$(librlog_LIBS)

TESTS = test_model

check_PROGRAMS = $(TESTS)

# unit tests 
# at first basic tests
# then game logic test
# finally a global test
test_model_SOURCES = \
../test/test_distance.cpp \
../test/test_model.cpp \
../test/test_oriented.cpp \
../test/test_positionned.cpp \
../test/test_speed.cpp \
../test/test_engine_control.cpp \
../test/test_guidance_control.cpp \
../test/test_throttle.cpp \
../test/test_stick.cpp \
../test/test_mesh.cpp \
../test/test_laser.cpp \
../test/test_demonstration.cpp \
$(SOURCES)/model/test/test_logic_laser_beam.cpp

test_model_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_model_LDFLAGS = $(CPPUNIT_LIBS)
test_model_LDADD = \
libmodel.la \
../../kernel/compilation/libkernel.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) 

