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
#pragma once

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      /// Tests for TextSerialiser
      class TestTextSerialiser : public CppUnit::TestFixture
      {
      protected:

      /// @name Tests methods
      // @{

        void parseMembers() ;
        void parseRecursiveMember() ;
        void parseRecursiveMemberWithMultipleMembers() ;
        void parseRecursiveMemberAsLastElement() ;
        void deserialiseValue() ;
        void parseListValues() ;
        void parseListValuesWithStructMember() ;
        void parseListValuesWithStructMemberAtEnd() ;
        void parseMapValues() ;

      // @}


        CPPUNIT_TEST_SUITE(TestTextSerialiser) ;

        CPPUNIT_TEST(parseMembers) ;
        CPPUNIT_TEST(parseRecursiveMember) ;
        CPPUNIT_TEST(parseRecursiveMemberWithMultipleMembers) ;
        CPPUNIT_TEST(parseRecursiveMemberAsLastElement) ;
        CPPUNIT_TEST(deserialiseValue) ;
        CPPUNIT_TEST(parseListValues) ;
        CPPUNIT_TEST(parseListValuesWithStructMember) ;
        CPPUNIT_TEST(parseListValuesWithStructMemberAtEnd) ;
        CPPUNIT_TEST(parseMapValues) ;

        CPPUNIT_TEST_SUITE_END() ;


      };
    }
  }
}
