lib_LTLIBRARIES = libkernel.la

SOURCES = $(top_srcdir)/sources
AM_CPPFLAGS = -I$(SOURCES) $(PU_CFLAGS)
AM_CXXFLAGS = $(PU_CXXFLAGS) $(PU_WARNINGS) 

#trait.reflect.cpp : ../trait.h
#	export GCCXML_COMPILER="g++-4.2" && genreflex $< --pool -o $@ -I$(SOURCES) $(PU_CFLAGS) ;

libkernel_la_SOURCES = \
$(SOURCES)/kernel/implementation/algorithm.cpp \
$(SOURCES)/kernel/implementation/base_controler.cpp \
$(SOURCES)/kernel/implementation/base_relation_controler.cpp \
$(SOURCES)/kernel/implementation/base_relation_view.cpp \
$(SOURCES)/kernel/implementation/base_trait_view.cpp \
$(SOURCES)/kernel/implementation/command_delegator.cpp \
$(SOURCES)/kernel/implementation/controler.cpp \
$(SOURCES)/kernel/implementation/controler_set.cpp \
$(SOURCES)/kernel/implementation/cppunit_multi_outputter.cpp \
$(SOURCES)/kernel/implementation/debugger.cpp \
$(SOURCES)/kernel/implementation/event_listener.cpp \
$(SOURCES)/kernel/implementation/exception.cpp \
$(SOURCES)/kernel/implementation/exception_kernel.cpp \
$(SOURCES)/kernel/implementation/deduced_trait.cpp \
$(SOURCES)/kernel/implementation/deduction_element.cpp \
$(SOURCES)/kernel/implementation/interpretor.cpp \
$(SOURCES)/kernel/implementation/log.cpp \
$(SOURCES)/kernel/implementation/meta.cpp \
$(SOURCES)/kernel/implementation/model.cpp \
$(SOURCES)/kernel/implementation/notifiable.cpp \
$(SOURCES)/kernel/implementation/number.cpp \
$(SOURCES)/kernel/implementation/object.cpp \
$(SOURCES)/kernel/implementation/object_reference.cpp \
$(SOURCES)/kernel/implementation/observer.cpp \
$(SOURCES)/kernel/implementation/operation.cpp \
$(SOURCES)/kernel/implementation/parameters.cpp \
$(SOURCES)/kernel/implementation/percentage.cpp \
$(SOURCES)/kernel/implementation/profiler.cpp \
$(SOURCES)/kernel/implementation/reader.cpp \
$(SOURCES)/kernel/implementation/relation.cpp \
$(SOURCES)/kernel/implementation/relation_controler.cpp \
$(SOURCES)/kernel/implementation/relation_observer.cpp \
$(SOURCES)/kernel/implementation/relation_view.cpp \
$(SOURCES)/kernel/implementation/statistics.cpp \
$(SOURCES)/kernel/implementation/string.cpp \
$(SOURCES)/kernel/implementation/timer.cpp \
$(SOURCES)/kernel/implementation/timer_test_listener.cpp \
$(SOURCES)/kernel/implementation/timer_test_result.cpp \
$(SOURCES)/kernel/implementation/timer_xml_outputter_hook.cpp \
$(SOURCES)/kernel/implementation/trait.cpp \
$(SOURCES)/kernel/implementation/trait_view.cpp \
$(SOURCES)/kernel/implementation/transaction.cpp \
$(SOURCES)/kernel/implementation/view_point.cpp \
$(SOURCES)/kernel/implementation/xml_outputter.cpp \
$(SOURCES)/kernel/implementation/xml_reader.cpp \
$(SOURCES)/kernel/implementation/xml_writer.cpp \
$(SOURCES)/kernel/implementation/writer.cpp \
$(SOURCES)/kernel/implementation/reflex/AnnotationList.cxx \
$(SOURCES)/kernel/implementation/reflex/AnnotationListImpl.cxx \
$(SOURCES)/kernel/implementation/reflex/Any.cxx \
$(SOURCES)/kernel/implementation/reflex/Array.cxx \
$(SOURCES)/kernel/implementation/reflex/Base.cxx  \
$(SOURCES)/kernel/implementation/reflex/BuilderContainer.cxx  \
$(SOURCES)/kernel/implementation/reflex/Callback.cxx                       \
$(SOURCES)/kernel/implementation/reflex/Class.cxx                          \
$(SOURCES)/kernel/implementation/reflex/ClassBuilder.cxx                   \
$(SOURCES)/kernel/implementation/reflex/ClassTemplateInstance.cxx          \
$(SOURCES)/kernel/implementation/reflex/DataMember.cxx                     \
$(SOURCES)/kernel/implementation/reflex/Dictionary.cxx            \
$(SOURCES)/kernel/implementation/reflex/DictionaryBuilder.cxx            \
$(SOURCES)/kernel/implementation/reflex/DictionaryGenerator.cxx            \
$(SOURCES)/kernel/implementation/reflex/Enum.cxx                           \
$(SOURCES)/kernel/implementation/reflex/EnumBuilder.cxx                    \
$(SOURCES)/kernel/implementation/reflex/FuncHandler.cxx                    \
$(SOURCES)/kernel/implementation/reflex/Function.cxx                       \
$(SOURCES)/kernel/implementation/reflex/FunctionBuilder.cxx                \
$(SOURCES)/kernel/implementation/reflex/FunctionMember.cxx                 \
$(SOURCES)/kernel/implementation/reflex/FunctionMemberTemplateInstance.cxx \
$(SOURCES)/kernel/implementation/reflex/Fundamental.cxx                    \
$(SOURCES)/kernel/implementation/reflex/GenreflexMemberBuilder.cxx \
$(SOURCES)/kernel/implementation/reflex/Kernel.cxx                         \
$(SOURCES)/kernel/implementation/reflex/LiteralString.cxx                         \
$(SOURCES)/kernel/implementation/reflex/Member.cxx                         \
$(SOURCES)/kernel/implementation/reflex/MemberBase.cxx                     \
$(SOURCES)/kernel/implementation/reflex/MemberTemplate.cxx                 \
$(SOURCES)/kernel/implementation/reflex/MemberTemplateImpl.cxx             \
$(SOURCES)/kernel/implementation/reflex/MemberTemplateName.cxx             \
$(SOURCES)/kernel/implementation/reflex/NameLookup.cxx                     \
$(SOURCES)/kernel/implementation/reflex/Names.cxx                     \
$(SOURCES)/kernel/implementation/reflex/Namespace.cxx                      \
$(SOURCES)/kernel/implementation/reflex/NamespaceBuilder.cxx               \
$(SOURCES)/kernel/implementation/reflex/Object.cxx                         \
$(SOURCES)/kernel/implementation/reflex/OnDemandBuilder.cxx \
$(SOURCES)/kernel/implementation/reflex/OwnedAnnotationList.cxx \
$(SOURCES)/kernel/implementation/reflex/OwnedPropertyList.cxx              \
$(SOURCES)/kernel/implementation/reflex/PluginFactoryMap.cxx \
$(SOURCES)/kernel/implementation/reflex/Pointer.cxx                        \
$(SOURCES)/kernel/implementation/reflex/PointerToMember.cxx                \
$(SOURCES)/kernel/implementation/reflex/PropertyList.cxx                   \
$(SOURCES)/kernel/implementation/reflex/PropertyListImpl.cxx               \
$(SOURCES)/kernel/implementation/reflex/Scope.cxx                          \
$(SOURCES)/kernel/implementation/reflex/ScopeBase.cxx                      \
$(SOURCES)/kernel/implementation/reflex/ScopedType.cxx \
$(SOURCES)/kernel/implementation/reflex/ScopeName.cxx                      \
$(SOURCES)/kernel/implementation/reflex/SharedLibraryUtils.cxx \
$(SOURCES)/kernel/implementation/reflex/TemplateInstance.cxx               \
$(SOURCES)/kernel/implementation/reflex/Tools.cxx                          \
$(SOURCES)/kernel/implementation/reflex/Type.cxx                           \
$(SOURCES)/kernel/implementation/reflex/TypeBase.cxx                       \
$(SOURCES)/kernel/implementation/reflex/TypeBuilder.cxx                    \
$(SOURCES)/kernel/implementation/reflex/TypeName.cxx                       \
$(SOURCES)/kernel/implementation/reflex/TypeTemplate.cxx                   \
$(SOURCES)/kernel/implementation/reflex/TypeTemplateImpl.cxx               \
$(SOURCES)/kernel/implementation/reflex/TypeTemplateName.cxx               \
$(SOURCES)/kernel/implementation/reflex/Typedef.cxx                        \
$(SOURCES)/kernel/implementation/reflex/TypedefBuilder.cxx                 \
$(SOURCES)/kernel/implementation/reflex/Union.cxx                          \
$(SOURCES)/kernel/implementation/reflex/UnionBuilder.cxx                   \
$(SOURCES)/kernel/implementation/reflex/VariableBuilder.cxx                \
$(SOURCES)/kernel/implementation/reflex/Array.h                            \
$(SOURCES)/kernel/implementation/reflex/Class.h                            \
$(SOURCES)/kernel/implementation/reflex/ClassTemplateInstance.h            \
$(SOURCES)/kernel/implementation/reflex/DataMember.h                       \
$(SOURCES)/kernel/implementation/reflex/Enum.h                             \
$(SOURCES)/kernel/implementation/reflex/FuncHandler.h                      \
$(SOURCES)/kernel/implementation/reflex/Function.h                         \
$(SOURCES)/kernel/implementation/reflex/FunctionMember.h                   \
$(SOURCES)/kernel/implementation/reflex/FunctionMemberTemplateInstance.h   \
$(SOURCES)/kernel/implementation/reflex/Fundamental.h                      \
$(SOURCES)/kernel/implementation/reflex/NameLookup.h                       \
$(SOURCES)/kernel/implementation/reflex/Namespace.h                        \
$(SOURCES)/kernel/implementation/reflex/Pointer.h                          \
$(SOURCES)/kernel/implementation/reflex/PointerToMember.h                  \
$(SOURCES)/kernel/implementation/reflex/stl_hash.h                         \
$(SOURCES)/kernel/implementation/reflex/TemplateInstance.h                 \
$(SOURCES)/kernel/implementation/reflex/Typedef.h                          \
$(SOURCES)/kernel/implementation/reflex/Union.h



libkernel_la_LDFLAGS = -no-undefined
libkernel_la_LDFLAGS += $(librlog_LIBS) $(libXML_LIBS) $(OGRE_LIBS) $(CPPUNIT_LIBS)

# tests
AM_COLOR_TESTS = always

TESTS = test_kernel test_kernel_automatic_registration test_performance_kernel 

# compile tests program without launching them
noinst_PROGRAMS = $(TESTS)

# launch tests in case of make check
check_PROGRAMS = $(TESTS)

test_kernel_SOURCES = \
$(SOURCES)/kernel/test/test_algorithm.cpp \
$(SOURCES)/kernel/test/test_command.cpp \
$(SOURCES)/kernel/test/test_deduced_trait.cpp \
$(SOURCES)/kernel/test/test_error.cpp \
$(SOURCES)/kernel/test/test_interpretor.cpp \
$(SOURCES)/kernel/test/test_kernel.cpp \
$(SOURCES)/kernel/test/test_meta.cpp \
$(SOURCES)/kernel/test/test_model.cpp \
$(SOURCES)/kernel/test/test_model_controler.cpp \
$(SOURCES)/kernel/test/test_model_view.cpp \
$(SOURCES)/kernel/test/test_number.cpp \
$(SOURCES)/kernel/test/test_parameters.cpp \
$(SOURCES)/kernel/test/test_percentage.cpp \
$(SOURCES)/kernel/test/test_relation.cpp \
$(SOURCES)/kernel/test/test_relation_view.cpp \
$(SOURCES)/kernel/test/test_trait.cpp \
$(SOURCES)/kernel/test/test_xml_reader.cpp \
$(SOURCES)/kernel/test/test_xml_writer.cpp

# checks that "test_inherits.cpp" does not compile
# its is a negative test for inherits : class does not inherits and should 
# produce compile error.
test_inherits.o : $(SOURCES)/kernel/test/test_inherits.cpp
	if $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) \
	-c $(SOURCES)/kernel/test/inherits.cpp 2> test_inherits_error; \
	then echo "test_inherits : Erreur"; exit 1; else echo "test_inherits : OK"; exit 0; fi


test_kernel_CXXFLAGS = $(PU_TESTS_WARNINGS) $(PU_CXXFLAGS) 
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



