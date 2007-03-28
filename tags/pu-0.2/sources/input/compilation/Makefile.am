#Makefile pour entrees

lib_LTLIBRARIES = libinput.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OIS_CFLAGS)

libinput_la_SOURCES = \
$(SOURCES)/input/implementation/input.cpp \
$(SOURCES)/input/implementation/keyboard.cpp

libinput_la_LIBADD = \
$(SOURCES)/action/compilation/libaction.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/kernel/compilation/libkernel.la 

