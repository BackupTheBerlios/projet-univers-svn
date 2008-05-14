# Makefile for ArtificialIntelligence

lib_LTLIBRARIES = libai.la 

# if we have clan lib we can compile an additional program
if HAVE_CLANLIB
  noinst_PROGRAMS = test_behaviour_display
endif

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS = $(PU_CXXFLAGS)

libai_la_SOURCES = \
$(SOURCES)/artificial_intelligence/implementation/artificial_intelligence.cpp \
$(SOURCES)/artificial_intelligence/implementation/agent_vehicle.cpp \
$(SOURCES)/artificial_intelligence/implementation/agent_view_point.cpp \
$(SOURCES)/artificial_intelligence/implementation/agent.cpp \
$(SOURCES)/artificial_intelligence/implementation/ai_system.cpp \
$(SOURCES)/artificial_intelligence/implementation/autonomous_agent.cpp \
$(SOURCES)/artificial_intelligence/implementation/detected_vehicle.cpp \
$(SOURCES)/artificial_intelligence/implementation/selected_target.cpp \
$(SOURCES)/artificial_intelligence/implementation/selected_vehicle.cpp \
$(SOURCES)/artificial_intelligence/implementation/steering_behaviour.cpp \
$(SOURCES)/artificial_intelligence/implementation/target.cpp \
$(SOURCES)/artificial_intelligence/implementation/vehicle.cpp

libai_la_LDFLAGS = -no-undefined
libai_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(librlog_LIBS) \
$(OGRE_LIBS)

libai_la_DEPENDENCIES = ../../kernel/compilation/libkernel.la ../../model/compilation/libmodel.la


TESTS = test_ai

check_PROGRAMS = $(TESTS)

# unit tests 
# at first basic tests
# then game logic test
# finally a global test
test_ai_SOURCES = \
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
$(SOURCES)/physic/compilation/ode/libphysicode.la \
$(librlog_LIBS) \
$(libXML_LIBS)  \
$(OGRE_LIBS)

test_behaviour_display_SOURCES = ../test/test_behaviour_display.cpp
test_behaviour_display_CXXFLAGS = $(PU_CXXFLAGS) $(CLAN_CXXFLAGS)
test_behaviour_display_LDFLAGS = $(CLAN_LIBS) -lclanDisplay -lclanTTF
test_behaviour_display_LDADD = \
libai.la \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OGRE_LIBS) \
$(librlog_LIBS) \
$(libXML_LIBS) 
