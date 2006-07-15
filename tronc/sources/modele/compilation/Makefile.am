lib_LTLIBRARIES = libmodele.la

INCLUDES = -I../.. $(OGRE_CFLAGS)

libmodele_la_SOURCES = \
../implantation/acceleration.cpp \
../implantation/assemblage.cpp \
../implantation/composant.cpp \
../implantation/contrainte.cpp \
../implantation/destructible.cpp \
../implantation/distance.cpp \
../implantation/energie.cpp \
../implantation/exception.cpp \
../implantation/gestionnaire_objets.cpp \
../implantation/identificateur.cpp \
../implantation/masse.cpp \
../implantation/mobile.cpp \
../implantation/nom.cpp \
../implantation/objet.cpp \
../implantation/orientation.cpp \
../implantation/plan_d_assemblage.cpp \
../implantation/plan_d_etat_de_composant.cpp \
../implantation/plan_de_contrainte.cpp \
../implantation/plan_de_point_d_attache.cpp \
../implantation/plan_de_composant.cpp \
../implantation/point_d_attache.cpp \
../implantation/position.cpp \
../implantation/positionne.cpp \
../implantation/vaisseau.cpp \
../implantation/vitesse.cpp  \
../implantation/modele.cpp


TESTS = test_modele

check_PROGRAMS = $(TESTS)

test_modele_SOURCES = \
../test/test_distance.cpp \
../test/test_modele.cpp \
../test/test_plan_de_vaisseau.cpp \
../test/test_vaisseau.cpp 

test_modele_CXXFLAGS = $(CPPUNIT_CFLAGS)
test_modele_LDFLAGS = $(CPPUNIT_LIBS)
test_modele_LDADD = libmodele.la ../../base/compilation/libbase.la
