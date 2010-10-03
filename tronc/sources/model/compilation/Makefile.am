lib_LTLIBRARIES = libmodel.la

AUTOMAKE_OPTIONS=subdir-objects

SOURCES = $(top_srcdir)/sources
AM_CPPFLAGS = -I$(SOURCES)
AM_CXXFLAGS = $(PU_CXXFLAGS)

libmodel_la_SOURCES = \
../implementation/acceleration.cpp \
../implementation/active.cpp \
../implementation/activated_end_of_simulation.cpp \
../implementation/activated_flying_group.cpp \
../implementation/activated_mission.cpp \
../implementation/angular_speed.cpp \
../implementation/area.cpp \
../implementation/autonomous_character.cpp \
../implementation/background_sound.cpp \
../implementation/collision.cpp \
../implementation/control_connection.cpp \
../implementation/component.cpp \
../implementation/computer.cpp \
../implementation/computer_data.cpp \
../implementation/custom_mission.cpp \
../implementation/data_connection.cpp \
../implementation/destroyable.cpp \
../implementation/detector.cpp \
../implementation/detectable.cpp \
../implementation/displayed.cpp \
../implementation/distance.cpp \
../implementation/dragger.cpp \
../implementation/duration.cpp \
../implementation/edited.cpp \
../implementation/end_of_simulation.cpp \
../implementation/energy.cpp \
../implementation/engine.cpp \
../implementation/engine_controler.cpp \
../implementation/exception.cpp \
../implementation/explosion.cpp \
../implementation/flying_group.cpp \
../implementation/force.cpp \
../implementation/force_generator.cpp \
../implementation/guidance_system.cpp \
../implementation/guidance_controler.cpp \
../implementation/ideal_target.cpp \
../implementation/image.cpp \
../implementation/laser.cpp \
../implementation/laser_beam.cpp \
../implementation/listener.cpp \
../implementation/mass.cpp \
../implementation/massive.cpp \
../implementation/menu.cpp \
../implementation/mesh.cpp \
../implementation/mission.cpp \
../implementation/mobile.cpp \
../implementation/model.cpp \
../implementation/observer.cpp \
../implementation/objective.cpp \
../implementation/orientation.cpp \
../implementation/oriented.cpp \
../implementation/physical_object.cpp \
../implementation/physical_world.cpp \
../implementation/played.cpp \
../implementation/player.cpp \
../implementation/player_configuration.cpp \
../implementation/player_in_activated_flying_group.cpp \
../implementation/position.cpp \
../implementation/positioned.cpp \
../implementation/selection.cpp \
../implementation/solid.cpp \
../implementation/speed.cpp \
../implementation/shot.cpp \
../implementation/shooting_helper.cpp \
../implementation/sized.cpp \
../implementation/sound_environnement.cpp \
../implementation/stabilizer.cpp \
../implementation/state.cpp \
../implementation/stellar_system.cpp \
../implementation/stick.cpp \
../implementation/target.cpp \
../implementation/targeting_system.cpp \
../implementation/head_up_display.cpp \
../implementation/team.cpp \
../implementation/throttle.cpp \
../implementation/torque_generator.cpp \
../implementation/transponder.cpp \
../implementation/universe.cpp \
../implementation/with_flying_group.cpp \
../implementation/with_lifetime.cpp \
../implementation/with_objectives.cpp \
../implementation/whole.cpp \
../implementation/logic/activated_mission.cpp \
../implementation/logic/collision.cpp \
../implementation/logic/component.cpp \
../implementation/logic/destroyable.cpp \
../implementation/logic/end_of_simulation.cpp \
../implementation/logic/flying_group.cpp \
../implementation/logic/laser.cpp \
../implementation/logic/logic.cpp \
../implementation/logic/logic_system.cpp \
../implementation/logic/player.cpp \
../implementation/logic/selection.cpp \
../implementation/logic/shot.cpp \
../implementation/logic/state.cpp \
../implementation/logic/target.cpp \
../implementation/logic/with_flying_group.cpp \
../implementation/logic/with_lifetime.cpp 

libmodel_la_LDFLAGS = -no-undefined
libmodel_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(OIS_LIBS) \
$(OGRE_LIBS) \
$(librlog_LIBS)

libmodel_la_DEPENDENCIES = ../../kernel/compilation/libkernel.la

all-local:ressources.cfg

# generates a correct ressources.cfg from main template
ressources.cfg:../../ressources.cfg.in
	cat ../../ressources.cfg.in | sed 's,@MEDIA_FOLDER\@,../../media,' > ressources.cfg

TESTS = test_model

# compile tests program without launching them so make build them
noinst_PROGRAMS = $(TESTS)

# launch tests in case of make check
check_PROGRAMS = $(TESTS)

# unit tests 
# at first basic tests
# then game logic test
# finally a global test
test_model_SOURCES = \
../test/test_area.cpp \
../test/test_detector.cpp \
../test/test_distance.cpp \
../test/test_engine_control.cpp \
../test/test_guidance_control.cpp \
../test/test_laser.cpp \
../test/test_load.cpp \
../test/test_logic.cpp \
../test/test_mesh.cpp \
../test/test_mission.cpp \
../test/test_model.cpp \
../test/test_oriented.cpp \
../test/test_orientation.cpp \
../test/test_player_configuration.cpp \
../test/test_position.cpp \
../test/test_positioned.cpp \
../test/test_save.cpp \
../test/test_shooting_helper.cpp \
../test/test_speed.cpp \
../test/test_state.cpp \
../test/test_stick.cpp \
../test/test_targeting_system.cpp \
../test/test_throttle.cpp 


test_model_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_model_LDFLAGS = $(CPPUNIT_LIBS)
test_model_LDADD = \
libmodel.la \
$(SOURCES)/kernel/compilation/libkernel.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS)
