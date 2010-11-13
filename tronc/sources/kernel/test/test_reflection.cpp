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

        TextSerialiser serialiser ;
        Trait* trait = serialiser.deserialiseTrait(text) ;

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

        TextSerialiser serialiser ;
        Trait* trait = serialiser.deserialiseTrait(text) ;

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

    }
  }
}

