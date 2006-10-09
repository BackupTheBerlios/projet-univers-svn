# Makefile pour Affichage

SUBDIRS = ogre

lib_LTLIBRARIES = libaffichage.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libaffichage_la_SOURCES = \
$(SOURCES)/affichage/implantation/affichage.cpp \
$(SOURCES)/affichage/implantation/exception.cpp \
$(SOURCES)/affichage/implantation/facette.cpp \
$(SOURCES)/affichage/implantation/objet.cpp \
$(SOURCES)/affichage/implantation/point_de_vue.cpp 


libaffichage_la_LIBADD = \
$(SOURCES)/base/compilation/libbase.la \
$(BOOST_SIGNALS_LIB)

#all-local :
#	cp libaffichage.la $(SOURCES)/compilation/libaffichage.la

# tests

TESTS = test_affichage

check_PROGRAMS = $(TESTS) 

test_affichage_SOURCES = \
$(SOURCES)/affichage/test/test_affichage.cpp \
$(SOURCES)/affichage/test/test_point_de_vue.cpp 

test_affichage_CXXFLAGS = $(CPPUNIT_CFLAGS) 
test_affichage_LDFLAGS = $(CPPUNIT_LIBS) -l$(BOOST_SIGNALS_LIB)

test_affichage_LDADD = \
$(SOURCES)/affichage/compilation/libaffichage.la \
$(SOURCES)/affichage/compilation/ogre/libaffichageogre.la \
$(SOURCES)/base/compilation/libbase.la \
$(SOURCES)/modele/compilation/libmodele.la \
$(librlog_LIBS) 

