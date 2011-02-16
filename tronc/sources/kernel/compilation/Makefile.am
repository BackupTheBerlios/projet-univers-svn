lib_LTLIBRARIES = libkernel.la

AUTOMAKE_OPTIONS=subdir-objects

SOURCES = $(top_srcdir)/sources
AM_CPPFLAGS = -I$(SOURCES) $(PU_CFLAGS)
AM_CXXFLAGS = $(PU_CXXFLAGS) $(PU_WARNINGS) 

libkernel_la_SOURCES = \
../implementation/algorithm.cpp \
../implementation/base_controler.cpp \
../implementation/base_relation_controler.cpp \
../implementation/base_relation_view.cpp \
../implementation/base_trait_view.cpp \
../implementation/command_delegator.cpp \
../implementation/controler.cpp \
../implementation/controler_set.cpp \
../implementation/cppunit_multi_outputter.cpp \
../implementation/debugger.cpp \
../implementation/event_listener.cpp \
../implementation/exception.cpp \
../implementation/exception_kernel.cpp \
../implementation/deduced_trait.cpp \
../implementation/deduction_element.cpp \
../implementation/interpretor.cpp \
../implementation/log.cpp \
../implementation/meta.cpp \
../implementation/model.cpp \
../implementation/notifiable.cpp \
../implementation/number.cpp \
../implementation/object.cpp \
../implementation/object_reference.cpp \
../implementation/observer.cpp \
../implementation/operation.cpp \
../implementation/parameters.cpp \
../implementation/percentage.cpp \
../implementation/profiler.cpp \
../implementation/reader.cpp \
../implementation/relation.cpp \
../implementation/relation.reflect.cpp \
../implementation/relation_controler.cpp \
../implementation/relation_observer.cpp \
../implementation/relation_view.cpp \
../implementation/serialiser.cpp \
../implementation/statistics.cpp \
../implementation/string.cpp \
../implementation/text_serialiser.cpp \
../implementation/timer.cpp \
../implementation/timer_test_listener.cpp \
../implementation/timer_test_result.cpp \
../implementation/timer_xml_outputter_hook.cpp \
../implementation/trait.cpp \
../implementation/trait.reflect.cpp \
../implementation/trait_view.cpp \
../implementation/transaction.cpp \
../implementation/view_point.cpp \
../implementation/xml_outputter.cpp \
../implementation/xml_reader.cpp \
../implementation/xml_writer.cpp \
../implementation/writer.cpp \
../implementation/reflex/AnnotationList.cxx \
../implementation/reflex/AnnotationListImpl.cxx \
../implementation/reflex/Any.cxx \
../implementation/reflex/Array.cxx \
../implementation/reflex/Base.cxx  \
../implementation/reflex/BuilderContainer.cxx  \
../implementation/reflex/Callback.cxx                       \
../implementation/reflex/Class.cxx                          \
../implementation/reflex/ClassBuilder.cxx                   \
../implementation/reflex/ClassTemplateInstance.cxx          \
../implementation/reflex/DataMember.cxx                     \
../implementation/reflex/Dictionary.cxx            \
../implementation/reflex/DictionaryBuilder.cxx            \
../implementation/reflex/DictionaryGenerator.cxx            \
../implementation/reflex/Enum.cxx                           \
../implementation/reflex/EnumBuilder.cxx                    \
../implementation/reflex/FuncHandler.cxx                    \
../implementation/reflex/Function.cxx                       \
../implementation/reflex/FunctionBuilder.cxx                \
../implementation/reflex/FunctionMember.cxx                 \
../implementation/reflex/FunctionMemberTemplateInstance.cxx \
../implementation/reflex/Fundamental.cxx                    \
../implementation/reflex/GenreflexMemberBuilder.cxx \
../implementation/reflex/Kernel.cxx                         \
../implementation/reflex/LiteralString.cxx                         \
../implementation/reflex/Member.cxx                         \
../implementation/reflex/MemberBase.cxx                     \
../implementation/reflex/MemberTemplate.cxx                 \
../implementation/reflex/MemberTemplateImpl.cxx             \
../implementation/reflex/MemberTemplateName.cxx             \
../implementation/reflex/NameLookup.cxx                     \
../implementation/reflex/Names.cxx                     \
../implementation/reflex/Namespace.cxx                      \
../implementation/reflex/NamespaceBuilder.cxx               \
../implementation/reflex/Object.cxx                         \
../implementation/reflex/OnDemandBuilder.cxx \
../implementation/reflex/OwnedAnnotationList.cxx \
../implementation/reflex/OwnedPropertyList.cxx              \
../implementation/reflex/PluginFactoryMap.cxx \
../implementation/reflex/Pointer.cxx                        \
../implementation/reflex/PointerToMember.cxx                \
../implementation/reflex/PropertyList.cxx                   \
../implementation/reflex/PropertyListImpl.cxx               \
../implementation/reflex/Scope.cxx                          \
../implementation/reflex/ScopeBase.cxx                      \
../implementation/reflex/ScopedType.cxx \
../implementation/reflex/ScopeName.cxx                      \
../implementation/reflex/SharedLibraryUtils.cxx \
../implementation/reflex/TemplateInstance.cxx               \
../implementation/reflex/Tools.cxx                          \
../implementation/reflex/Type.cxx                           \
../implementation/reflex/TypeBase.cxx                       \
../implementation/reflex/TypeBuilder.cxx                    \
../implementation/reflex/TypeName.cxx                       \
../implementation/reflex/TypeTemplate.cxx                   \
../implementation/reflex/TypeTemplateImpl.cxx               \
../implementation/reflex/TypeTemplateName.cxx               \
../implementation/reflex/Typedef.cxx                        \
../implementation/reflex/TypedefBuilder.cxx                 \
../implementation/reflex/Union.cxx                          \
../implementation/reflex/UnionBuilder.cxx                   \
../implementation/reflex/VariableBuilder.cxx                \
../implementation/reflex/Array.h                            \
../implementation/reflex/Class.h                            \
../implementation/reflex/ClassTemplateInstance.h            \
../implementation/reflex/DataMember.h                       \
../implementation/reflex/Enum.h                             \
../implementation/reflex/FuncHandler.h                      \
../implementation/reflex/Function.h                         \
../implementation/reflex/FunctionMember.h                   \
../implementation/reflex/FunctionMemberTemplateInstance.h   \
../implementation/reflex/Fundamental.h                      \
../implementation/reflex/NameLookup.h                       \
../implementation/reflex/Namespace.h                        \
../implementation/reflex/Pointer.h                          \
../implementation/reflex/PointerToMember.h                  \
../implementation/reflex/stl_hash.h                         \
../implementation/reflex/TemplateInstance.h                 \
../implementation/reflex/Typedef.h                          \
../implementation/reflex/Union.h



libkernel_la_LDFLAGS = $(COVERAGE_LDFLAGS) -no-undefined
libkernel_la_LDFLAGS += $(librlog_LIBS) $(libXML_LIBS) $(OGRE_LIBS) $(CPPUNIT_LIBS)

# tests
AM_COLOR_TESTS = always

TESTS = test_kernel test_kernel_automatic_registration test_performance_kernel 

# compile tests program without launching them
noinst_PROGRAMS = $(TESTS)

# launch tests in case of make check
check_PROGRAMS = $(TESTS)

%.reflect.cpp : ../test/reflection/%.h
	export GCCXML_COMPILER="$(REFLEX_COMPILER)" && python $(SOURCES)/tools/reflex/genreflex.py $< -o $@ --comments -I$(SOURCES) $(PU_CFLAGS) ;

test_kernel_SOURCES = \
../test/test_algorithm.cpp \
../test/test_command.cpp \
../test/test_deduced_trait.cpp \
../test/test_error.cpp \
../test/test_interpretor.cpp \
../test/test_kernel.cpp \
meta.reflect.cpp \
../test/test_meta.cpp \
../test/test_model.cpp \
../test/test_model_controler.cpp \
../test/test_model_view.cpp \
../test/test_number.cpp \
../test/test_parameters.cpp \
../test/test_percentage.cpp \
../test/test_reflection.cpp \
../test/test_relation.cpp \
../test/test_relation_view.cpp \
../test/test_trait.cpp \
../test/test_xml_reader.cpp \
../test/test_xml_writer.cpp \
primitive_trait.reflect.cpp \
../test/reflection/primitive_trait.cpp \
int_trait.reflect.cpp \
../test/reflection/int_trait.cpp

# checks that "test_inherits.cpp" does not compile
# its is a negative test for inherits : class does not inherits and should 
# produce compile error.
test_inherits.o : ../test/test_inherits.cpp
	if $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) \
	-c ../test/inherits.cpp 2> test_inherits_error; \
	then echo "test_inherits : Erreur"; exit 1; else echo "test_inherits : OK"; exit 0; fi


test_kernel_CXXFLAGS = $(PU_CXXFLAGS) 
test_kernel_LDFLAGS = $(COVERAGE_LDFLAGS) $(CPPUNIT_LIBS) 
test_kernel_LDADD = libkernel.la $(librlog_LIBS) $(libXML_LIBS)

test_kernel_automatic_registration_SOURCES = \
../test/test_viewpoint_registration.cpp \
../test/test_kernel_automatic_registration.cpp

test_kernel_automatic_registration_CXXFLAGS = $(PU_CXXFLAGS) 
test_kernel_automatic_registration_LDFLAGS = $(COVERAGE_LDFLAGS) $(CPPUNIT_LIBS) 
test_kernel_automatic_registration_LDADD = libkernel.la $(librlog_LIBS) $(libXML_LIBS)

test_performance_kernel_SOURCES = \
../test/performance/model.cpp \
../test/performance/test_meta.cpp \
../test/performance/test_performance_model.cpp \
../test/performance/test_performance_kernel.cpp

test_performance_kernel_CXXFLAGS = $(PU_CXXFLAGS) 
test_performance_kernel_LDFLAGS = $(COVERAGE_LDFLAGS) $(CPPUNIT_LIBS) 
test_performance_kernel_LDADD = libkernel.la $(librlog_LIBS) $(libXML_LIBS)

clean-local: gcov-clean

gcov-clean:
	find $(SOURCES)/kernel -name "*.gcda" -o -name "*.gcov" -o -name "*.gcno" | xargs -r rm


