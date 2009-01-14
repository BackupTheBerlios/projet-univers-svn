lib_LTLIBRARIES = libkernel.la

SOURCES = $(top_srcdir)/sources
INCLUDES = -I$(SOURCES)
AM_CXXFLAGS=$(PU_CXXFLAGS)

libkernel_la_SOURCES = \
$(SOURCES)/kernel/implementation/algorithm.cpp \
$(SOURCES)/kernel/implementation/base_controler.cpp \
$(SOURCES)/kernel/implementation/base_trait_reference.cpp \
$(SOURCES)/kernel/implementation/base_trait_view.cpp \
$(SOURCES)/kernel/implementation/concurrent_block.cpp \
$(SOURCES)/kernel/implementation/controler.cpp \
$(SOURCES)/kernel/implementation/controler_set.cpp \
$(SOURCES)/kernel/implementation/exception.cpp \
$(SOURCES)/kernel/implementation/exception_kernel.cpp \
$(SOURCES)/kernel/implementation/deduced_trait.cpp \
$(SOURCES)/kernel/implementation/interpretor.cpp \
$(SOURCES)/kernel/implementation/log.cpp \
$(SOURCES)/kernel/implementation/meta.cpp \
$(SOURCES)/kernel/implementation/model.cpp \
$(SOURCES)/kernel/implementation/object.cpp \
$(SOURCES)/kernel/implementation/object_reference.cpp \
$(SOURCES)/kernel/implementation/operation.cpp \
$(SOURCES)/kernel/implementation/cppunit_multi_outputter.cpp \
$(SOURCES)/kernel/implementation/string.cpp \
$(SOURCES)/kernel/implementation/timer.cpp \
$(SOURCES)/kernel/implementation/trait.cpp \
$(SOURCES)/kernel/implementation/trait_reference.cpp \
$(SOURCES)/kernel/implementation/trait_view.cpp \
$(SOURCES)/kernel/implementation/view_point.cpp \
$(SOURCES)/kernel/implementation/command_delegator.cpp \
$(SOURCES)/kernel/implementation/parameters.cpp \
$(SOURCES)/kernel/implementation/percentage.cpp \
$(SOURCES)/kernel/implementation/reader.cpp \
$(SOURCES)/kernel/implementation/timer_test_listener.cpp \
$(SOURCES)/kernel/implementation/timer_test_result.cpp \
$(SOURCES)/kernel/implementation/timer_xml_outputter_hook.cpp \
$(SOURCES)/kernel/implementation/transaction.cpp \
$(SOURCES)/kernel/implementation/xml_outputter.cpp \
$(SOURCES)/kernel/implementation/xml_reader.cpp \
$(SOURCES)/kernel/implementation/xml_writer.cpp \
$(SOURCES)/kernel/implementation/writer.cpp


libkernel_la_LDFLAGS = -no-undefined
libkernel_la_LDFLAGS += $(librlog_LIBS) $(libXML_LIBS) $(OGRE_LIBS) $(CPPUNIT_LIBS)

# tests

TESTS = test_kernel test_kernel_automatic_registration test_performance_kernel

check_PROGRAMS = $(TESTS)

test_kernel_SOURCES = \
$(SOURCES)/kernel/test/test_algorithm.cpp \
$(SOURCES)/kernel/test/test_error.cpp \
$(SOURCES)/kernel/test/test_kernel.cpp \
$(SOURCES)/kernel/test/test_meta.cpp \
$(SOURCES)/kernel/test/test_model_controler.cpp \
$(SOURCES)/kernel/test/test_model_view.cpp \
$(SOURCES)/kernel/test/test_deduced_trait.cpp \
$(SOURCES)/kernel/test/test_command.cpp \
$(SOURCES)/kernel/test/test_interpretor.cpp \
$(SOURCES)/kernel/test/test_parameters.cpp \
$(SOURCES)/kernel/test/test_percentage.cpp \
$(SOURCES)/kernel/test/test_xml_reader.cpp \
$(SOURCES)/kernel/test/test_xml_writer.cpp \
$(SOURCES)/kernel/test/test_model.cpp 

# checks that "test_inherits.cpp" does not compile
# its is a neagtive test for inherits : class does not inhertits and should 
# produce compile error.
test_inherits.o : $(SOURCES)/kernel/test/test_inherits.cpp
	if $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) \
	-c $(SOURCES)/kernel/test/inherits.cpp 2> test_inherits_error; \
	then echo "test_inherits : Erreur"; exit 1; else echo "test_inherits : OK"; exit 0; fi


test_kernel_CXXFLAGS = $(PU_CXXFLAGS) 
test_kernel_LDFLAGS = $(CPPUNIT_LIBS) 
test_kernel_LDADD = libkernel.la $(librlog_LIBS) $(libXML_LIBS)

test_kernel_automatic_registration_SOURCES = \
$(SOURCES)/kernel/test/test_viewpoint_registration.cpp \
$(SOURCES)/kernel/test/test_kernel_automatic_registration.cpp

test_kernel_automatic_registration_CXXFLAGS = $(PU_CXXFLAGS) 
test_kernel_automatic_registration_LDFLAGS = $(CPPUNIT_LIBS) 
test_kernel_automatic_registration_LDADD = libkernel.la $(librlog_LIBS) $(libXML_LIBS)

test_performance_kernel_SOURCES = \
$(SOURCES)/kernel/test/performance/model.cpp \
$(SOURCES)/kernel/test/performance/test_meta.cpp \
$(SOURCES)/kernel/test/performance/test_performance_model.cpp \
$(SOURCES)/kernel/test/performance/test_performance_kernel.cpp

test_performance_kernel_CXXFLAGS = $(PU_CXXFLAGS) 
test_performance_kernel_LDFLAGS = $(CPPUNIT_LIBS) 
test_performance_kernel_LDADD = libkernel.la $(librlog_LIBS) $(libXML_LIBS)



