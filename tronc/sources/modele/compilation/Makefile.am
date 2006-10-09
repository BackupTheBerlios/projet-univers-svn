lib_LTLIBRARIES = libmodele.la

INCLUDES = -I../.. $(OGRE_CFLAGS)

libmodele_la_SOURCES = \
../implantation/acceleration.cpp \
../implantation/distance.cpp \
../implantation/energie.cpp \
../implantation/exception.cpp \
../implantation/facette.cpp \
../implantation/identificateur.cpp \
../implantation/masse.cpp \
../implantation/mobile.cpp \
../implantation/modele.cpp \
../implantation/nom.cpp \
../implantation/objet.cpp \
../implantation/observateur.cpp \
../implantation/orientation.cpp \
../implantation/position.cpp \
../implantation/positionne.cpp \
../implantation/solide.cpp \
../implantation/systeme_stellaire.cpp \
../implantation/univers.cpp \
../implantation/vitesse.cpp  


TESTS = test_modele

check_PROGRAMS = $(TESTS)

test_modele_SOURCES = \
../test/test_distance.cpp \
../test/test_modele.cpp \
../test/test_demonstration.cpp 

test_modele_CXXFLAGS = $(CPPUNIT_CFLAGS)
test_modele_LDFLAGS = $(CPPUNIT_LIBS)
test_modele_LDADD = \
libmodele.la \
../../base/compilation/libbase.la \
$(OIS_LIBS) \
$(librlog_LIBS) \
-l$(BOOST_SIGNALS_LIB)

