lib_LTLIBRARIES = libkernel.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES) $(librlog_CFLAGS)

libkernel_la_SOURCES = \
$(SOURCES)/kernel/implementation/object.cpp \
$(SOURCES)/kernel/implementation/base_controler.cpp \
$(SOURCES)/kernel/implementation/base_trait_view.cpp \
$(SOURCES)/kernel/implementation/controler.cpp \
$(SOURCES)/kernel/implementation/controler_set.cpp \
$(SOURCES)/kernel/implementation/exception.cpp \
$(SOURCES)/kernel/implementation/exception_kernel.cpp \
$(SOURCES)/kernel/implementation/deduced_trait.cpp \
$(SOURCES)/kernel/implementation/log.cpp \
$(SOURCES)/kernel/implementation/meta.cpp \
$(SOURCES)/kernel/implementation/model.cpp \
$(SOURCES)/kernel/implementation/pretty_print.cpp \
$(SOURCES)/kernel/implementation/string.cpp \
$(SOURCES)/kernel/implementation/timer.cpp \
$(SOURCES)/kernel/implementation/trait.cpp \
$(SOURCES)/kernel/implementation/trait_view.cpp \
$(SOURCES)/kernel/implementation/view_point.cpp \
$(SOURCES)/kernel/implementation/command_delegator.cpp \
$(SOURCES)/kernel/implementation/parameters.cpp


libkernel_la_LDFLAGS = -lrlog

# tests

TESTS = test_kernel

check_PROGRAMS = $(TESTS) test_inherits.o

test_kernel_SOURCES = \
$(SOURCES)/kernel/test/test_error.cpp \
$(SOURCES)/kernel/test/test_kernel.cpp \
$(SOURCES)/kernel/test/test_meta.cpp \
$(SOURCES)/kernel/test/test_model_controler.cpp \
$(SOURCES)/kernel/test/test_model_view.cpp \
$(SOURCES)/kernel/test/test_deduced_trait.cpp \
$(SOURCES)/kernel/test/test_command.cpp \
$(SOURCES)/kernel/test/test_parameters.cpp 


# checks that "test_inherits.cpp" does not compile
# its is a neagtive test for inherits : class does not inhertits and should 
# produce compile error.
test_inherits.o : $(SOURCES)/kernel/test/test_inherits.cpp
	if $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) \
	-c $(SOURCES)/kernel/test/inherits.cpp 2> test_inherits_error; \
	then echo "test_inherits : Erreur"; exit 1; else echo "test_inherits : OK"; exit 0; fi


test_kernel_CXXFLAGS = $(CPPUNIT_CFLAGS) 
test_kernel_LDFLAGS = $(CPPUNIT_LIBS)
test_kernel_LDADD = libkernel.la $(librlog_LIBS)




