noinst_LIBRARIES = libbase.a

INCLUDES = -I.. -I../implantation

libbase_a_SOURCES = ../implantation/association.cpp \
../implantation/chaine.cpp \
../implantation/composition.cpp \
../implantation/ensemble_association.cpp \
../implantation/ensemble_composition.cpp \
../implantation/exception_base.cpp \
../implantation/exception.cpp \
../implantation/iterateur_liste_abstrait.cpp \
../implantation/iterateur_liste_association.cpp \
../implantation/iterateur_liste_composition.cpp \
../implantation/iterateur_liste.cpp \
../implantation/iterateur_tampon_liste_association.cpp \
../implantation/joli_affichage.cpp \
../implantation/liste_abstraite.cpp \
../implantation/liste_association.cpp \
../implantation/liste_composition.cpp \
../implantation/noeud_abstrait.cpp \
../implantation/noeud_association.cpp \
../implantation/noeud_composition.cpp \
../implantation/iterateur_liste_abstrait.h \
../implantation/iterateur_liste_association.h \
../implantation/iterateur_liste_composition.h \
../implantation/iterateur_liste.h \
../implantation/iterateur_tampon_liste_association.h \
../implantation/liste_abstraite.h \
../implantation/liste_association.h \
../implantation/liste_composition.h \
../implantation/noeud_abstrait.h \
../implantation/noeud_association.h \
../implantation/noeud_composition.h \
../implantation/tampon_chaine.h \
../implantation/tampon_liste_association.h

TESTS = test_base
check_PROGRAMS = $(TESTS)


test_base_SOURCES = ../test/test_base.cpp \
../test/test_composition.cpp \
../test/test_composition.h \
../test/test_ensemble_composition.cpp \
../test/test_ensemble_composition.h \
../test/test_ensemble_association.cpp \
../test/test_ensemble_association.h

test_base_CXXFLAGS = $(CPPUNIT_CFLAGS)
test_base_LDFLAGS = $(CPPUNIT_LIBS)
test_base_LDADD = libbase.a 
