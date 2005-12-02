noinst_LIBRARIES = libmodele.a

INCLUDES = -I../.. $(OGRE_CFLAGS)

libmodele_a_SOURCES = \
../implantation/gestionnaire_objet.cpp \
../implantation/objet_physique.cpp \
../implantation/objet_abstrait.cpp \
../implantation/bien.cpp \
../implantation/planetoide.cpp \
../implantation/composant.cpp \
../implantation/systeme_stellaire.cpp \
../implantation/etat_mission.cpp \
../implantation/univers.cpp \
../implantation/etoile.cpp \
../implantation/vaisseau.cpp \
../implantation/monde.cpp \
../implantation/destructible.cpp \
../implantation/societe.cpp \
../implantation/nom.cpp \
../implantation/objet.cpp \
../implantation/position.cpp \
../implantation/distance.cpp \
../implantation/orientation.cpp



TESTS = test_modele

check_PROGRAMS = $(TESTS)

test_modele_SOURCES = \
../test/test_modele.cpp \
../test/test_type_de_vaisseau.cpp \
../test/test_vaisseau.cpp \
../test/test_distance.cpp

test_modele_CXXFLAGS = $(CPPUNIT_CFLAGS)
test_modele_LDFLAGS = $(CPPUNIT_LIBS)
test_modele_LDADD = libmodele.a ../../base/compilation/libbase.a
