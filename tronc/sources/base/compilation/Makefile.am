lib_LTLIBRARIES = libbase.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(librlog_CFLAGS)

libbase_la_SOURCES = \
$(SOURCES)/base/implantation/association.cpp \
$(SOURCES)/base/implantation/agregation.cpp \
$(SOURCES)/base/implantation/base_vue.cpp \
$(SOURCES)/base/implantation/chaine.cpp \
$(SOURCES)/base/implantation/composition.cpp \
$(SOURCES)/base/implantation/ensemble_association.cpp \
$(SOURCES)/base/implantation/ensemble_composition.cpp \
$(SOURCES)/base/implantation/ensemble_valeur.cpp \
$(SOURCES)/base/implantation/evenement.cpp \
$(SOURCES)/base/implantation/exception_base.cpp \
$(SOURCES)/base/implantation/exception.cpp \
$(SOURCES)/base/implantation/fonction_association_objet_objet.cpp \
$(SOURCES)/base/implantation/fonction_association_valeur_objet.cpp \
$(SOURCES)/base/implantation/fonction_composition_valeur_objet.cpp \
$(SOURCES)/base/implantation/fonction_objet_valeur.cpp \
$(SOURCES)/base/implantation/fonction_valeur_valeur.cpp \
$(SOURCES)/base/implantation/iterateur_liste.cpp \
$(SOURCES)/base/implantation/iterateur_liste_abstrait.cpp \
$(SOURCES)/base/implantation/iterateur_liste_association.cpp \
$(SOURCES)/base/implantation/iterateur_liste_composition.cpp \
$(SOURCES)/base/implantation/iterateur_tampon_liste_association.cpp \
$(SOURCES)/base/implantation/iterateur_tampon_liste_valeur.cpp \
$(SOURCES)/base/implantation/joli_affichage.cpp \
$(SOURCES)/base/implantation/liste_abstraite.cpp \
$(SOURCES)/base/implantation/liste_association.cpp \
$(SOURCES)/base/implantation/liste_composition.cpp \
$(SOURCES)/base/implantation/liste_valeur.cpp \
$(SOURCES)/base/implantation/modele.cpp \
$(SOURCES)/base/implantation/noeud_abstrait.cpp \
$(SOURCES)/base/implantation/noeud_association.cpp \
$(SOURCES)/base/implantation/noeud_composition.cpp \
$(SOURCES)/base/implantation/noeud_valeur.cpp \
$(SOURCES)/base/implantation/point_de_vue.cpp \
$(SOURCES)/base/implantation/tampon_liste_association.cpp \
$(SOURCES)/base/implantation/tampon_liste_valeur.cpp \
$(SOURCES)/base/implantation/traceur.cpp \
$(SOURCES)/base/implantation/vue.cpp 


# tests

TESTS = test_base

check_PROGRAMS = $(TESTS) test_derive_de.o

test_base_SOURCES = $(SOURCES)/base/test/test_base.cpp \
$(SOURCES)/base/test/test_agregation.cpp \
$(SOURCES)/base/test/test_association.cpp \
$(SOURCES)/base/test/test_association_virtuelle.cpp \
$(SOURCES)/base/test/test_chaine.cpp \
$(SOURCES)/base/test/test_composition.cpp \
$(SOURCES)/base/test/test_ensemble_association.cpp \
$(SOURCES)/base/test/test_ensemble_composition.cpp \
$(SOURCES)/base/test/test_ensemble_valeur.cpp \
$(SOURCES)/base/test/test_erreur.cpp \
$(SOURCES)/base/test/test_iterateur_ensemble_association.cpp \
$(SOURCES)/base/test/test_fonction_association_objet_objet.cpp \
$(SOURCES)/base/test/test_fonction_association_valeur_objet.cpp \
$(SOURCES)/base/test/test_fonction_composition_valeur_objet.cpp \
$(SOURCES)/base/test/test_fonction_valeur_valeur.cpp \
$(SOURCES)/base/test/test_liste.cpp \
$(SOURCES)/base/test/test_mvc.cpp 

# vérifie que "test_derive_de.cpp" ne compile pas
test_derive_de.o : $(SOURCES)/base/test/test_derive_de.cpp
	if $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) \
	-c $(SOURCES)/base/test/test_derive_de.cpp 2> test_derive_erreurs; \
	then echo "test_derive_de : Erreur"; exit 1; else echo "test_derive_de : OK"; exit 0; fi


test_base_CXXFLAGS = $(CPPUNIT_CFLAGS) 
test_base_LDFLAGS = $(CPPUNIT_LIBS) -l$(BOOST_SIGNALS_LIB)
test_base_LDADD = libbase.la $(librlog_LIBS)

#-l



