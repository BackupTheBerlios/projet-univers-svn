noinst_LIBRARIES = libbase.a

INCLUDES = -I../..

libbase_a_SOURCES = \
../implantation/association.cpp \
../implantation/chaine.cpp \
../implantation/composition.cpp \
../implantation/ensemble_association.cpp \
../implantation/ensemble_composition.cpp \
../implantation/ensemble_valeur.cpp \
../implantation/exception_base.cpp \
../implantation/exception.cpp \
../implantation/iterateur_liste.cpp \
../implantation/iterateur_liste_abstrait.cpp \
../implantation/iterateur_liste_association.cpp \
../implantation/iterateur_liste_composition.cpp \
../implantation/iterateur_tampon_liste_association.cpp \
../implantation/iterateur_tampon_liste_valeur.cpp \
../implantation/joli_affichage.cpp \
../implantation/liste_abstraite.cpp \
../implantation/liste_association.cpp \
../implantation/liste_composition.cpp \
../implantation/liste_valeur.cpp \
../implantation/noeud_abstrait.cpp \
../implantation/noeud_association.cpp \
../implantation/noeud_composition.cpp \
../implantation/noeud_valeur.cpp \
../implantation/tampon_liste_association.cpp \
../implantation/tampon_liste_valeur.cpp


TESTS = test_base
check_PROGRAMS = $(TESTS)


test_base_SOURCES = ../test/test_base.cpp \
../test/test_composition.cpp \
../test/test_ensemble_association.cpp \
../test/test_ensemble_composition.cpp \
../test/test_ensemble_valeur.cpp \
../test/test_association_virtuelle.cpp \
../test/test_liste.cpp

test_base_CXXFLAGS = $(CPPUNIT_CFLAGS)
test_base_LDFLAGS = $(CPPUNIT_LIBS)
test_base_LDADD = libbase.a 
