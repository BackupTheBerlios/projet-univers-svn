lib_LTLIBRARIES = libmodel.la

INCLUDES = -I../.. $(OGRE_CFLAGS)

libmodel_la_SOURCES = \
../implementation/acceleration.cpp \
../implementation/angular_speed.cpp \
../implementation/distance.cpp \
../implementation/destroyable.cpp \
../implementation/duration.cpp \
../implementation/energy.cpp \
../implementation/exception.cpp \
../implementation/mass.cpp \
../implementation/massive.cpp \
../implementation/mobile.cpp \
../implementation/model.cpp \
../implementation/mesh.cpp \
../implementation/name.cpp \
../implementation/observer.cpp \
../implementation/orientation.cpp \
../implementation/physical_object.cpp \
../implementation/physical_world.cpp \
../implementation/position.cpp \
../implementation/positionned.cpp \
../implementation/solid.cpp \
../implementation/speed.cpp \
../implementation/stellar_system.cpp \
../implementation/universe.cpp


TESTS = test_model

check_PROGRAMS = $(TESTS)

test_model_SOURCES = \
../test/test_distance.cpp \
../test/test_model.cpp \
../test/test_positionned.cpp \
../test/test_speed.cpp \
../test/test_demonstration.cpp 

test_model_CXXFLAGS = $(CPPUNIT_CFLAGS)
test_model_LDFLAGS = $(CPPUNIT_LIBS)
test_model_LDADD = \
libmodel.la \
../../kernel/compilation/libkernel.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) 

