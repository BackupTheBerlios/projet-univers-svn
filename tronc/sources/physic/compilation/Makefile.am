lib_LTLIBRARIES = libphysic.la

AUTOMAKE_OPTIONS=subdir-objects

SOURCES = $(top_srcdir)/sources
AM_CPPFLAGS = -I$(SOURCES) $(PU_CFLAGS)
AM_CXXFLAGS = $(PU_CXXFLAGS)

libphysic_la_SOURCES = \
../implementation/physic.cpp \
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
$(libode_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS)

all-local:ressources.cfg

# generates a correct ressources.cfg from main template
ressources.cfg:../../ressources.cfg.in
	cat ../../ressources.cfg.in | sed 's,@MEDIA_FOLDER\@,../../media,' > ressources.cfg

TESTS = test_physic

# compile tests program without launching them so make build them
noinst_PROGRAMS = $(TESTS)

# launch tests in case of make check
check_PROGRAMS = $(TESTS)

test_physic_SOURCES = \
../test/test_collision.cpp \
../test/test_demonstration.cpp \
../test/test_dragger.cpp \
../test/test_model_controler.cpp \
../test/test_ode.cpp \
../test/test_physic.cpp \
../test/test_shooting_helper.cpp


test_physic_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_physic_LDFLAGS = $(CPPUNIT_LIBS)
test_physic_LDADD = \
../../kernel/compilation/libkernel.la \
../../model/compilation/libmodel.la \
libphysic.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libode_LIBS) \
$(libXML_LIBS)

memory_check : test_physic
	valgrind ./test_physic