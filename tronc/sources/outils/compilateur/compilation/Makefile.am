noinst_LIBRARIES = libcompilateur.a
noinst_PROGRAMS = compilateur


SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)

COMPILATEUR = $(SOURCES)/outils/compilateur
COMPILATEUR_IMPLANTATION = $(SOURCES)/outils/compilateur/implantation


libcompilateur_a_SOURCES = \
$(COMPILATEUR_IMPLANTATION)/type_classe.cpp \
$(COMPILATEUR_IMPLANTATION)/type_enumere.cpp \
$(COMPILATEUR_IMPLANTATION)/type_predefini.cpp \
$(COMPILATEUR_IMPLANTATION)/type_template.cpp \
$(COMPILATEUR_IMPLANTATION)/type.cpp \
$(COMPILATEUR_IMPLANTATION)/utilitaires_opencxx.cpp \
$(COMPILATEUR_IMPLANTATION)/attribut.cpp \
$(COMPILATEUR_IMPLANTATION)/traceur.cpp

libcompilateur_a_CXXFLAGS = -DRLOG_COMPONENT="compilateur"

compilateur_DEPENDENCIES = \
$(COMPILATEUR_IMPLANTATION)/meta_classe.mc \
$(COMPILATEUR)/meta_classe.h \
$(SOURCES)/base/compilation/libbase.a \
libcompilateur.a

compilateur_LDFLAGS = -L$(SOURCES)/base/compilation -L.
compilateur_LDADD = -locc -lltdl -lcompilateur -lbase -lrlog
compilateur_CXXFLAGS = -Wp,-DRLOG_COMPONENT="compilateur"


compilateur : $(compilateur_DEPENDENCIES)
	$(OCC) $(compilateur_CXXFLAGS) $(INCLUDES) $(COMPILATEUR_IMPLANTATION)/meta_classe.mc -o $@ $(compilateur_LDFLAGS) $(compilateur_LDADD) 

check-am : compilateur libcompilateur.a
	./compilateur $(INCLUDES) -v -- ../test/test2.cc



#all-am : compilateur	

