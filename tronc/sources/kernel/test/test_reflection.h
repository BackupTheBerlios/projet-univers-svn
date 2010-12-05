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

      /// Tests for automatic serialisation
      class TestReflection : public CppUnit::TestFixture
      {
      protected:

      /// @name Tests methods
      // @{

        void serialisationOfStringFloat() ;
        void deserialisationOfStringFloat() ;
        void serialisationOfInt() ;
        void deserialisationOfInt() ;
        void serialisationOfRelation() ;
        void addRelation() ;
        void removeRelation() ;
        void serialisationOfObjectReference() ;
        void deserialisationOfObjectReference() ;
        void serialisationOfBoolean() ;
        void deserialisationOfBoolean() ;

      // @}


        CPPUNIT_TEST_SUITE(TestReflection) ;

        CPPUNIT_TEST(serialisationOfStringFloat) ;
        CPPUNIT_TEST(deserialisationOfStringFloat) ;
        CPPUNIT_TEST(serialisationOfInt) ;
        CPPUNIT_TEST(deserialisationOfInt) ;
        CPPUNIT_TEST(serialisationOfRelation) ;
        CPPUNIT_TEST(addRelation) ;
        CPPUNIT_TEST(removeRelation) ;
        CPPUNIT_TEST(serialisationOfObjectReference) ;
        CPPUNIT_TEST(deserialisationOfObjectReference) ;
        CPPUNIT_TEST(serialisationOfBoolean) ;
        CPPUNIT_TEST(deserialisationOfBoolean) ;

        CPPUNIT_TEST_SUITE_END() ;


      };
    }
  }
}
