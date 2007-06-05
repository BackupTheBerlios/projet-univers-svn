# Makefile pour action
lib_LTLIBRARIES = libaction.la 


SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libaction_la_SOURCES = \
$(SOURCES)/action/implementation/action.cpp


libaction_la_LIBADD = \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OGRE_LIBS)


