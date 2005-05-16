noinst_LIBRARIES = libcompilateur.a

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
$(COMPILATEUR_IMPLANTATION)/utilitaires_opencxx.cpp

