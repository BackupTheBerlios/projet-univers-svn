lib_LTLIBRARIES = libnetwork.la 

SOURCES = $(top_srcdir)/sources
AM_CPPFLAGS = -I$(SOURCES) $(PU_CFLAGS)
AM_CXXFLAGS = $(PU_CXXFLAGS) $(enet_CFLAGS)

libnetwork_la_SOURCES = \
../implementation/network.cpp \
../implementation/enet/network_system.cpp \
../implementation/enet/packet.cpp \
../implementation/enet/client.cpp \
../implementation/enet/server_object.cpp \
../implementation/enet/server_relation.cpp \
../implementation/enet/server_trait.cpp \
../implementation/enet/server.cpp 

libnetwork_la_LDFLAGS = -no-undefined
libnetwork_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OGRE_LIBS) \
$(librlog_LIBS) \
$(enet_LIBS)

noinst_PROGRAMS = test_enet test_network

test_enet_SOURCES = ../test/test_enet.cpp

test_enet_CXXFLAGS = $(enet_CFLAGS)
test_enet_LDFLAGS = $(enet_LIBS)

TESTS = test_network

# launch tests in case of make check
check_PROGRAMS = $(TESTS)

%.reflect.cpp : ../test/local/%.h
	export GCCXML_COMPILER="$(REFLEX_COMPILER)" && python $(SOURCES)/tools/reflex/genreflex.py $< -o $@ --comments -I$(SOURCES) $(PU_CFLAGS) ;

# unit tests 
test_network_SOURCES = \
r1.reflect.cpp \
t1.reflect.cpp \
../test/test_connection.cpp \
../test/test_network.cpp \
../test/test_replication.cpp

test_network_CXXFLAGS = $(CPPUNIT_CFLAGS) $(PU_CXXFLAGS) $(enet_CFLAGS)
test_network_LDFLAGS = $(CPPUNIT_LIBS)
test_network_LDADD = \
libnetwork.la \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(librlog_LIBS) \
$(OGRE_LIBS) \
$(libXML_LIBS) \
$(enet_LIBS)

