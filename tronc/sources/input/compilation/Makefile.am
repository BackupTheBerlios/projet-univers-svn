#Makefile pour entrees

lib_LTLIBRARIES = libinput.la 

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(OIS_CFLAGS) $(OGRE_CFLAGS)

libinput_la_SOURCES = \
$(SOURCES)/input/implementation/input.cpp \
$(SOURCES)/input/implementation/keyboard.cpp \
$(SOURCES)/input/implementation/mouse.cpp \
$(SOURCES)/input/implementation/joystick.cpp

libinput_la_LDFLAGS = -no-undefined
libinput_la_LDFLAGS += \
$(SOURCES)/kernel/compilation/libkernel.la \
$(SOURCES)/display/compilation/libdisplay.la \
$(SOURCES)/display/compilation/ogre/libdisplayogre.la \
$(SOURCES)/action/compilation/libaction.la \
$(OIS_LIBS) \
$(OGRE_LIBS) \
$(librlog_LIBS)

