/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <iostream>

#include <kernel/percentage.h>

#include <kernel/text_serialiser.h>
#include <kernel/test/reflection/primitive_trait.h>
#include <kernel/test/test_reflection.h>
#include <kernel/test/reflection/int_trait.h>
#include <kernel/test/reflection/meta.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestReflection) ;

      class TestObjectMapper : public ObjectMapper
      {
      public:

        virtual int getMappedIdentifier(Object* object)
        {
          return object->getIdentifier() ;
        }

        virtual ObjectReference getMappedObject(Model* model,const int& identifier)
        {
          return model->getObject(identifier) ;
        }

      };

      void TestReflection::serialisationOfStringFloat()
      {
        Reflection::PrimitiveTrait trait ;
        trait.setName("toto") ;
        trait.setValue(1.8f) ;

        TextSerialiser serialiser ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::PrimitiveTrait("
                        "m_name=toto,m_value=1.8)"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfStringFloat()
      {
        std::string text("ProjetUnivers::Kernel::Test::Reflection::PrimitiveTrait("
                         "m_name=toto,m_value=1.8)") ;

        Model model ;
        TextSerialiser serialiser ;
        Trait* trait = serialiser.deserialiseTrait(text,&model) ;

        Reflection::PrimitiveTrait* primitive = dynamic_cast<Reflection::PrimitiveTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;

        CPPUNIT_ASSERT_EQUAL(float(1.8f),primitive->getValue()) ;
        CPPUNIT_ASSERT_EQUAL(std::string("toto"),primitive->getName()) ;
      }

      void TestReflection::serialisationOfInt()
      {
        Reflection::IntTrait trait ;
        trait.setUInt(7) ;
        trait.setInt(1) ;

        TextSerialiser serialiser ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::IntTrait("
                        "m_uint=7,m_int=1)"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfInt()
      {
        std::string text("ProjetUnivers::Kernel::Test::Reflection::IntTrait("
                         "m_uint=7,m_int=1)") ;

        Model model ;
        TextSerialiser serialiser ;
        Trait* trait = serialiser.deserialiseTrait(text,&model) ;

        Reflection::IntTrait* primitive = dynamic_cast<Reflection::IntTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)7,primitive->getUInt()) ;
        CPPUNIT_ASSERT_EQUAL(1,primitive->getInt()) ;
      }

      void TestReflection::serialisationOfRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Meta::Selection>(o1,o2) ;

        Relation* r = Relation::getRelation(getClassTypeIdentifier(Meta::Selection),o1,o2) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Meta::Selection(") +
                        toString(o1->getIdentifier()) + "," +
                        toString(o2->getIdentifier()) + ")",
            serialiser.serialiseRelation(*r)) ;
      }

      void TestReflection::addRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        std::string text("ProjetUnivers::Kernel::Test::Meta::Selection(" +
                         toString(o1->getIdentifier()) + "," +
                         toString(o2->getIdentifier()) + ")") ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        serialiser.addRelation(text,model.get()) ;

        CPPUNIT_ASSERT(Relation::areLinked<Meta::Selection>(o1,o2)) ;
      }

      void TestReflection::removeRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Meta::Selection>(o1,o2) ;

        std::string text("ProjetUnivers::Kernel::Test::Meta::Selection(" +
                         toString(o1->getIdentifier()) + "," +
                         toString(o2->getIdentifier()) + ")") ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        serialiser.removeRelation(text,model.get()) ;

        CPPUNIT_ASSERT(!Relation::areLinked<Meta::Selection>(o1,o2)) ;
      }

      void TestReflection::serialisationOfObjectReference()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* o1 = model->createObject() ;

        Reflection::ReferenceTrait trait ;
        trait.setReference(o1) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::ReferenceTrait(m_reference=") +
                        toString(o1->getIdentifier()) + ")",
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfObjectReference()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* o1 = model->createObject() ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::ReferenceTrait(m_reference=" +
                         toString(o1->getIdentifier()) + ")") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::ReferenceTrait* primitive = dynamic_cast<Reflection::ReferenceTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;
        CPPUNIT_ASSERT(primitive->getReference()) ;

        CPPUNIT_ASSERT(o1 == primitive->getReference()) ;
      }

      void TestReflection::serialisationOfBoolean()
      {
        Reflection::BoolTrait trait ;
        trait.setBoolean(false) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::BoolTrait(m_value=0)"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfBoolean()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::BoolTrait(m_value=1)") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::BoolTrait* primitive = dynamic_cast<Reflection::BoolTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;
        CPPUNIT_ASSERT(primitive->getBoolean()) ;
      }


      void TestReflection::serialisationOfOgreVector()
      {
        Reflection::Ogre3DTrait trait ;
        trait.setVector(::Ogre::Vector3(1,2,3)) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::Ogre3DTrait(m_value=1 2 3)"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfOgreVector()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::Ogre3DTrait(m_value=5 3 1)") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::Ogre3DTrait* primitive = dynamic_cast<Reflection::Ogre3DTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;
        CPPUNIT_ASSERT(primitive->getVector() == ::Ogre::Vector3(5,3,1)) ;
      }

      void TestReflection::serialisationOfOgreQuaternion()
      {
        Reflection::QuaternionTrait trait ;
        trait.setValue(::Ogre::Quaternion(1,2,3,8)) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::QuaternionTrait(m_value=1 2 3 8)"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfOgreQuaternion()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::QuaternionTrait(m_value=5 3 1 9)") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::QuaternionTrait* primitive = dynamic_cast<Reflection::QuaternionTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;
        CPPUNIT_ASSERT(primitive->getValue() == ::Ogre::Quaternion(5,3,1,9)) ;
      }

      void TestReflection::serialisationOfValueClass()
      {
        Reflection::ValueTrait trait ;
        Reflection::Value value ;
        value.m_value = 8 ;
        trait.setValue(value) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::ValueTrait(m_value=ProjetUnivers::Kernel::Test::Reflection::Value(m_value=8))"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfValueClass()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::ValueTrait(m_value=ProjetUnivers::Kernel::Test::Reflection::Value(m_value=1))") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::ValueTrait* primitive = dynamic_cast<Reflection::ValueTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;

        Reflection::Value value ;
        value.m_value = 1 ;

        CPPUNIT_ASSERT_EQUAL(value,primitive->getValue()) ;
      }

      void TestReflection::serialisationOfEnum()
      {
        Reflection::EnumTrait trait ;
        trait.setValue(Reflection::EnumTrait::_Value1) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::EnumTrait(m_value=0)"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfEnum()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::EnumTrait(m_value=1)") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::EnumTrait* primitive = dynamic_cast<Reflection::EnumTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;
        CPPUNIT_ASSERT(primitive->getValue() == Reflection::EnumTrait::_Value2) ;
      }

      void TestReflection::serialisationOfSet()
      {
        Reflection::SetTrait trait ;
        std::set<int> value ;
        value.insert(1) ;
        value.insert(5) ;
        trait.setValue(value) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::SetTrait(m_value=std::set(1,5))"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfSet()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::SetTrait(m_value=std::set(1,5))") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::SetTrait* primitive = dynamic_cast<Reflection::SetTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;

        const std::set<int>& value = primitive->getValue() ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,value.size()) ;
        CPPUNIT_ASSERT(value.find(1) != value.end()) ;
        CPPUNIT_ASSERT(value.find(5) != value.end()) ;
      }

      void TestReflection::serialisationOfVector()
      {
        Reflection::VectorTrait trait ;
        std::vector<int> value ;
        value.push_back(1) ;
        value.push_back(5) ;
        trait.setValue(value) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::VectorTrait(m_value=std::vector(1,5))"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfVector()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::VectorTrait(m_value=std::vector(1,5))") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::VectorTrait* primitive = dynamic_cast<Reflection::VectorTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;

        const std::vector<int>& value = primitive->getValue() ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)2,value.size()) ;

        std::vector<int>::const_iterator element = value.begin() ;

        CPPUNIT_ASSERT_EQUAL(1,*element) ;
        ++element ;
        CPPUNIT_ASSERT_EQUAL(5,*element) ;
      }

      void TestReflection::serialisationOfList()
      {
        Reflection::ListTrait trait ;
        std::list<int> value ;
        value.push_back(1) ;
        value.push_back(5) ;
        trait.setValue(value) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::ListTrait(m_value=std::list(1,5))"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfList()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::ListTrait(m_value=std::list(1,5))") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::ListTrait* primitive = dynamic_cast<Reflection::ListTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;

        const std::list<int>& value = primitive->getValue() ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)2,value.size()) ;

        std::list<int>::const_iterator element = value.begin() ;

        CPPUNIT_ASSERT_EQUAL(1,*element) ;
        ++element ;
        CPPUNIT_ASSERT_EQUAL(5,*element) ;
      }

      void TestReflection::serialisationOfMap()
      {
        Reflection::MapTrait trait ;
        std::map<int,float> value ;
        value[1] = 0.8 ;
        value[-1] = 10 ;
        trait.setValue(value) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            // stored in correct order
            std::string("ProjetUnivers::Kernel::Test::Reflection::MapTrait(m_value=std::map(-1,10,1,0.8))"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfMap()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::MapTrait(m_value=std::map(1,0.8,-1,10))") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::MapTrait* primitive = dynamic_cast<Reflection::MapTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;

        const std::map<int,float>& value = primitive->getValue() ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)2,value.size()) ;

        std::map<int,float>::const_iterator element = value.begin() ;

        CPPUNIT_ASSERT(value.find(1) != value.end()) ;
        CPPUNIT_ASSERT_EQUAL(0.8f,value.find(1)->second) ;

        CPPUNIT_ASSERT(value.find(-1) != value.end()) ;
        CPPUNIT_ASSERT_EQUAL(10.0f,value.find(-1)->second) ;
      }

      void TestReflection::serialisationOfOgreDegree()
      {
        Reflection::DegreeTrait trait ;
        trait.setValue(::Ogre::Degree(90)) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        CPPUNIT_ASSERT_EQUAL(
            std::string("ProjetUnivers::Kernel::Test::Reflection::DegreeTrait(m_value=90)"),
            serialiser.serialiseTrait(trait)) ;
      }

      void TestReflection::deserialisationOfOgreDegree()
      {
        std::auto_ptr<Model> model(new Model()) ;

        TestObjectMapper mapper ;
        TextSerialiser serialiser(&mapper) ;

        std::string text("ProjetUnivers::Kernel::Test::Reflection::DegreeTrait(m_value=90)") ;

        Trait* trait = serialiser.deserialiseTrait(text,model.get()) ;

        Reflection::DegreeTrait* primitive = dynamic_cast<Reflection::DegreeTrait*>(trait) ;
        CPPUNIT_ASSERT(primitive) ;
        CPPUNIT_ASSERT(primitive->getValue() == ::Ogre::Degree(90)) ;
      }

    }
  }
}

