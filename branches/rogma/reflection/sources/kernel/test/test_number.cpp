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
#include <kernel/implementation/number.h>
#include <kernel/test/test_number.h>


namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {
      CPPUNIT_TEST_SUITE_REGISTRATION(TestNumber) ;

      void TestNumber::defaultContructorSetToZero()
      {
        Implementation::Number number ;

        CPPUNIT_ASSERT(number == 0) ;
      }

      void TestNumber::add()
      {
        Implementation::Number number1(10) ;
        Implementation::Number number2(32) ;

        CPPUNIT_ASSERT(number1+number2 == 42) ;
        CPPUNIT_ASSERT(number1+56 == 66) ;
      }

      void TestNumber::subtract()
      {
        Implementation::Number number1(10) ;
        Implementation::Number number2(32) ;

        CPPUNIT_ASSERT(number2-number1 == 22) ;
        CPPUNIT_ASSERT(number2-12 == 20) ;
      }


    }
  }
}
