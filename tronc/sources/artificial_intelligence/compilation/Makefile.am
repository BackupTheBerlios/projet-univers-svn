# Makefile for ArtificialIntelligence

lib_LTLIBRARIES = libai.la 

SOURCES = $(top_srcdir)/sources
AM_CPPFLAGS = -I$(SOURCES)
AM_CXXFLAGS = $(PU_CXXFLAGS)

libai_la_SOURCES = \
$(SOURCES)/artificial_intelligence/implementation/agent_target_controler.cpp \
$(SOURCES)/artificial_intelligence/implementation/agent.cpp \
$(SOURCES)/artificial_intelligence/implementation/ai_system.cpp \
$(SOURCES)/artificial_intelligence/implementation/artificial_intelligence.cpp \
$(SOURCES)/artificial_intelligence/implementation/autonomous_agent.cpp \
$(SOURCES)/artificial_intelligence/implementation/steering_behaviour.cpp \
$(SOURCES)/artificial_intelligence/implementation/vehicle.cpp \
$(SOURCES)/artificial_intelligence/implementation/with_vehicle.cpp \
$(SOURCES)/artificial_intelligence/implementation/with_vehicle_controler.cpp

libai_la_LDFLAGS = -no-undefined
libai_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(librlog_LIBS) \
$(OGRE_LIBS)

libai_la_DEPENDENCIES = ../../kernel/compilation/libkernel.la ../../model/compilation/libmodel.la

all-local:ressources.cfg

# generates a correct ressources.cfg from main template
ressources.cfg:../../ressources.cfg.in
	cat ../../ressources.cfg.in | sed 's,@MEDIA_FOLDER\@,../../media,' > ressources.cfg

TESTS = test_ai

# compile tests program without launching them so make build them
noinst_PROGRAMS = $(TESTS)

# launch tests in case of make check
check_PROGRAMS = $(TESTS)

# unit tests 
# at first basic tests
# then game logic test
# finally a global test
test_ai_SOURCES = \
../test/test_agent.cpp \
../test/test_artificial_intelligence.cpp \
../test/test_model_controler.cpp \
../test/test_steering_behaviour.cpp \
../test/test_vehicle.cpp

test_ai_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS)
test_ai_LDFLAGS = $(CPPUNIT_LIBS)
test_ai_LDADD = \
libai.la \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(SOURCES)/physic/compilation/libphysic.la \
$(librlog_LIBS) \
$(libXML_LIBS)  \
$(OGRE_LIBS)
