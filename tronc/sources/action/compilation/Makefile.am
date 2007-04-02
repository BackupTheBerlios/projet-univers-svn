# Makefile pour action
lib_LTLIBRARIES = libaction.la 


SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OGRE_CFLAGS)

libaction_la_SOURCES = \
$(SOURCES)/action/implementation/action.cpp

libaction_la_LDFLAGS = 
	$(SHARED_FLAGS) \
	-L$(top_srcdir)/sources/kernel/compilation \
	-L$(top_srcdir)/sources/model/compilation

libaction_la_LIBADD = -lkernel -lmodel -lOgreMain


