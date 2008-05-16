SUBDIRS = ode

lib_LTLIBRARIES = libphysic.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

LDADD=ode/libphysicode.la

libphysic_la_SOURCES = \
$(SOURCES)/physic/implementation/physic.cpp \
$(SOURCES)/physic/implementation/laser_beam.cpp

libphysic_la_LDFLAGS = -no-undefined
libphysic_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/physic/compilation/ode/libphysicode.la \
$(ODE_LIBS) \
$(librlog_LIBS)

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
ode/libphysicode.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(ODE_LIBS) \
$(libXML_LIBS)

memory_check : test_physic
	valgrind ./test_physic