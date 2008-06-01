# Makefile pour action
lib_LTLIBRARIES = libaction.la 


SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libaction_la_SOURCES = \
$(SOURCES)/action/implementation/action.cpp


libaction_la_LDFLAGS = -no-undefined
libaction_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/model/compilation/libmodel.la \
$(OGRE_LIBS) \
$(librlog_LIBS)



