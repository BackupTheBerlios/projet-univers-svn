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
#include <kernel/test/reflection/int_trait.h>
#include <kernel/test/reflection/meta.h>
#include <kernel/test/test_text_serialiser.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestTextSerialiser) ;

      void TestTextSerialiser::parseMembers()
      {
        TextSerialiser serialiser ;

        std::list<std::pair<std::string,std::string> > result =
        serialiser.parseValues("(m_name=toto,m_value=1.8)") ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,result.size()) ;
        std::list<std::pair<std::string,std::string> >::iterator member = result.begin() ;

        CPPUNIT_ASSERT_EQUAL(std::string("m_name"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("toto"),member->second) ;

        ++member ;

        CPPUNIT_ASSERT_EQUAL(std::string("m_value"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("1.8"),member->second) ;
      }

      void TestTextSerialiser::parseRecursiveMember()
      {
        TextSerialiser serialiser ;

        std::list<std::pair<std::string,std::string> > result =
        serialiser.parseValues("(m_name=Value(m_value=1),m_value=1.8)") ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,result.size()) ;
        std::list<std::pair<std::string,std::string> >::iterator member = result.begin() ;

        CPPUNIT_ASSERT_EQUAL(std::string("m_name"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("Value(m_value=1)"),member->second) ;

        ++member ;

        CPPUNIT_ASSERT_EQUAL(std::string("m_value"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("1.8"),member->second) ;
      }

      void TestTextSerialiser::parseRecursiveMemberWithMultipleMembers()
      {
        TextSerialiser serialiser ;

        std::list<std::pair<std::string,std::string> > result =
        serialiser.parseValues("(m_name=Value(m_value=1,m_unit=4),m_value=1.8)") ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,result.size()) ;
        std::list<std::pair<std::string,std::string> >::iterator member = result.begin() ;

        CPPUNIT_ASSERT_EQUAL(std::string("m_name"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("Value(m_value=1,m_unit=4)"),member->second) ;

        ++member ;

        CPPUNIT_ASSERT_EQUAL(std::string("m_value"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("1.8"),member->second) ;
      }

      void TestTextSerialiser::parseRecursiveMemberAsLastElement()
      {
        TextSerialiser serialiser ;

        std::list<std::pair<std::string,std::string> > result =
        serialiser.parseValues("(m_value=1.8,m_name=Value(m_value=1,m_unit=4))") ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,result.size()) ;
        std::list<std::pair<std::string,std::string> >::iterator member = result.begin() ;

        CPPUNIT_ASSERT_EQUAL(std::string("m_value"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("1.8"),member->second) ;

        ++member ;

        CPPUNIT_ASSERT_EQUAL(std::string("m_name"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("Value(m_value=1,m_unit=4)"),member->second) ;
      }

      void TestTextSerialiser::deserialiseValue()
      {
        Reflex::Type value_type(Reflex::Type::ByTypeInfo(typeid(Reflection::Value))) ;
        void* memory = value_type.Allocate() ;
        Reflex::Object result(value_type,memory) ;

        Reflection::Value expected ;
        expected.m_value = 1 ;

        TextSerialiser serialiser ;
        serialiser.fillTrait("(m_value=1)",result,value_type,NULL) ;

        CPPUNIT_ASSERT_EQUAL(expected,*(Reflection::Value*)result.Address()) ;
        value_type.Deallocate(memory) ;
      }

      void TestTextSerialiser::parseListValues()
      {
        TextSerialiser serialiser ;

        std::list<std::string> result = serialiser.parseListValues("std::set(1.8,1)") ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,result.size()) ;
        std::list<std::string>::iterator member = result.begin() ;

        CPPUNIT_ASSERT_EQUAL(std::string("1.8"),*member) ;

        ++member ;

        CPPUNIT_ASSERT_EQUAL(std::string("1"),*member) ;
      }

      void TestTextSerialiser::parseListValuesWithStructMember()
      {
        TextSerialiser serialiser ;

        std::list<std::string> result = serialiser.parseListValues("std::set(T(m=1.8),1)") ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,result.size()) ;
        std::list<std::string>::iterator member = result.begin() ;

        CPPUNIT_ASSERT_EQUAL(std::string("T(m=1.8)"),*member) ;

        ++member ;

        CPPUNIT_ASSERT_EQUAL(std::string("1"),*member) ;
      }

      void TestTextSerialiser::parseListValuesWithStructMemberAtEnd()
      {
        TextSerialiser serialiser ;

        std::list<std::string> result = serialiser.parseListValues("std::set(1,T(m=1.8))") ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,result.size()) ;
        std::list<std::string>::iterator member = result.begin() ;

        CPPUNIT_ASSERT_EQUAL(std::string("1"),*member) ;

        ++member ;

        CPPUNIT_ASSERT_EQUAL(std::string("T(m=1.8)"),*member) ;
      }


      void TestTextSerialiser::parseMapValues()
      {
        TextSerialiser serialiser ;

        std::map<std::string,std::string> result = serialiser.parseMapValues("std::map(1,1.8,-1,9)") ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,result.size()) ;

        std::map<std::string,std::string>::iterator member = result.begin() ;

        // maps are stored in 'correct' order
        CPPUNIT_ASSERT_EQUAL(std::string("-1"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("9"),member->second) ;

        ++member ;

        CPPUNIT_ASSERT_EQUAL(std::string("1"),member->first) ;
        CPPUNIT_ASSERT_EQUAL(std::string("1.8"),member->second) ;
      }

    }
  }
}

