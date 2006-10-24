# Makefile pour action
lib_LTLIBRARIES = libaction.la 


SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libaction_la_SOURCES = \
$(SOURCES)/action/implantation/action.cpp

libaction_la_LIBADD = \
$(SOURCES)/base/compilation/libbase.la 

#all-local :
#	cp libaction.la $(SOURCES)/compilation/libaction.la
