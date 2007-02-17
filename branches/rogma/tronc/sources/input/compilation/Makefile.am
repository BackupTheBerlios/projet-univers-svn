#Makefile pour entrees

lib_LTLIBRARIES = libentrees.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OIS_CFLAGS)

libentrees_la_SOURCES = \
$(SOURCES)/entrees/implantation/entrees.cpp \
$(SOURCES)/entrees/implantation/clavier.cpp

libentrees_la_LIBADD = \
$(SOURCES)/action/compilation/libaction.la \
$(SOURCES)/affichage/compilation/libaffichage.la \
$(SOURCES)/base/compilation/libbase.la 

#all-local :
#	cp libentrees.la $(SOURCES)/compilation/libentrees.la
