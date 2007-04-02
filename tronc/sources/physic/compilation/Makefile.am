SUBDIRS = ode

lib_LTLIBRARIES = libphysic.la

INCLUDES = -I../.. $(OGRE_CFLAGS)
SOURCES = $(top_srcdir)/sources

libphysic_la_SOURCES = \
$(SOURCES)/physic/implementation/physic.cpp

libphysic_la_LDFLAGS = \
	$(SHARED_FLAGS) \
	-L$(SOURCES)/kernel/compilation \
	-L$(SOURCES)/model/compilation \
	-L$(SOURCES)/physic/compilation/ode

libphysic_la_LIBADD = -lkernel -lmodel -lphysicode $(ODE_LIBS) 

TESTS = test_physic

check_PROGRAMS = $(TESTS)

test_physic_SOURCES = \
../test/test_physic.cpp \
../test/test_demonstration.cpp 

test_physic_CXXFLAGS = $(CPPUNIT_CFLAGS)
test_physic_LDFLAGS = $(CPPUNIT_LIBS)
test_physic_LDADD = \
libphysic.la \
ode/libphysicode.la \
../../model/compilation/libmodel.la \
../../kernel/compilation/libkernel.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
$(OGRE_LIBS) 
