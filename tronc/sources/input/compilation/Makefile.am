#Makefile pour entrees

lib_LTLIBRARIES = libinput.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OIS_CFLAGS)

libinput_la_SOURCES = \
$(SOURCES)/input/implementation/input.cpp \
$(SOURCES)/input/implementation/keyboard.cpp

libinput_la_LDFLAGS = \
	$(SHARED_FLAGS) \
	-L$(SOURCES)/kernel/compilation \
	-L$(SOURCES)/action/compilation \
	-L$(SOURCES)/display/compilation/ogre

libinput_la_LIBADD = -laction -ldisplay -lkernel $(OIS_LIBS) 


