lib_LTLIBRARIES = libmodel.la

AUTOMAKE_OPTIONS=subdir-objects

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS = $(PU_CXXFLAGS)

libmodel_la_SOURCES = \
../implementation/acceleration.cpp \
../implementation/angular_speed.cpp \
../implementation/autonomous_character.cpp \
../implementation/distance.cpp \
../implementation/destroyable.cpp \
../implementation/dragger.cpp \
../implementation/duration.cpp \
../implementation/component.cpp \
../implementation/computer.cpp \
../implementation/computer_data.cpp \
../implementation/energy.cpp \
../implementation/engine.cpp \
../implementation/engine_controler.cpp \
../implementation/exception.cpp \
../implementation/explosion.cpp \
../implementation/force.cpp \
../implementation/force_generator.cpp \
../implementation/mass.cpp \
../implementation/massive.cpp \
../implementation/mobile.cpp \
../implementation/model.cpp \
../implementation/mesh.cpp \
../implementation/observer.cpp \
../implementation/objective.cpp \
../implementation/orientation.cpp \
../implementation/oriented.cpp \
../implementation/physical_object.cpp \
../implementation/physical_world.cpp \
../implementation/position.cpp \
../implementation/positionned.cpp \
../implementation/solid.cpp \
../implementation/background_sound.cpp \
../implementation/speed.cpp \
../implementation/guidance_system.cpp \
../implementation/guidance_controler.cpp \
../implementation/stabilizer.cpp \
../implementation/stellar_system.cpp \
../implementation/torque_generator.cpp \
../implementation/universe.cpp \
../implementation/whole.cpp \
../implementation/stick.cpp \
../implementation/throttle.cpp \
../implementation/laser.cpp \
../implementation/laser_beam.cpp \
../implementation/collision.cpp \
../implementation/shot.cpp \
../implementation/detector.cpp \
../implementation/detector_view_point.cpp \
../implementation/detectable.cpp \
../implementation/detector_object_view.cpp \
../implementation/menu.cpp \
../implementation/hearing.cpp \
../implementation/selected.cpp \
../implementation/shooting_helper.cpp \
../implementation/sound_environnement.cpp \
../implementation/targeting_system.cpp \
../implementation/target_displayer.cpp \
../implementation/detection_data.cpp \
../implementation/ideal_target.cpp \
../implementation/transponder.cpp \
../implementation/target.cpp \
../implementation/with_lifetime.cpp \
../implementation/with_objectives.cpp \
../implementation/shootable.cpp \
../implementation/sized.cpp \
../implementation/logic/logic.cpp \
../implementation/logic/with_lifetime.cpp \
../implementation/logic/logic_system.cpp \
../implementation/logic/collision.cpp \
../implementation/logic/destroyable.cpp \
../implementation/logic/detector.cpp \
../implementation/logic/target.cpp \
../implementation/logic/laser.cpp \
../implementation/logic/shooting_helper_viewpoint.cpp \
../implementation/logic/shooting_helper.cpp \
../implementation/logic/shot.cpp 

libmodel_la_LDFLAGS = -no-undefined
libmodel_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(OGRE_LIBS) \
$(librlog_LIBS)

libmodel_la_DEPENDENCIES = ../../kernel/compilation/libkernel.la

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
../test/test_orientation.cpp \
../test/test_positionned.cpp \
../test/test_speed.cpp \
../test/test_engine_control.cpp \
../test/test_guidance_control.cpp \
../test/test_throttle.cpp \
../test/test_stick.cpp \
../test/test_mesh.cpp \
../test/test_laser.cpp \
../test/test_logic.cpp \
../test/test_detector.cpp \
../test/test_load.cpp \
../test/test_targeting_system.cpp \
../test/test_shooting_helper.cpp \
../test/test_demonstration.cpp 


test_model_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_model_LDFLAGS = $(CPPUNIT_LIBS)
test_model_LDADD = \
libmodel.la \
$(SOURCES)/kernel/compilation/libkernel.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS)
