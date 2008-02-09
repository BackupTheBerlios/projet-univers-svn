lib_LTLIBRARIES = libcompilateur.la
noinst_PROGRAMS = compilateur

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)

COMPILATEUR = $(SOURCES)/tools/compilateur
COMPILATEUR_IMPLANTATION = $(SOURCES)/tools/compilateur/implantation

libcompilateur_la_SOURCES = \
$(COMPILATEUR_IMPLANTATION)/traceur.cpp

libcompilateur_la_CXXFLAGS = -DRLOG_COMPONENT="compilateur"
libcompilateur_la_LDFLAGS = \
$(OCC_LIBS)


compilateur_DEPENDENCIES = \
$(COMPILATEUR_IMPLANTATION)/test_meta_class.mc \
$(COMPILATEUR)/test_meta_class.h \
libcompilateur.la

compilateur_LDFLAGS = -L.
compilateur_LDADD = $(OCC_LIBS) -lrlog -lgc -lcompilateur


compilateur : $(compilateur_DEPENDENCIES)
	$(OCC) $(INCLUDES) $(COMPILATEUR_IMPLANTATION)/test_meta_class.mc -o $@ $(compilateur_LDFLAGS) $(compilateur_LDADD) 

check-am : compilateur libcompilateur.la
	./compilateur $(INCLUDES) -v -- ../test/test_trait.cpp
	./compilateur $(INCLUDES) -v -- ../test/test2.cc
	./compilateur $(INCLUDES) -v -- ../test/test1.cpp


#all-am : compilateur	

