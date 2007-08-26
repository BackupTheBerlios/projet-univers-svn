/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <kernel/trait.h>
#include <kernel/meta.h>

#include <kernel/test/test_meta.h>



CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Test::TestMeta) ;

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {

      /// local classes
      namespace
      {
        class A : public Trait
        {};
        
        class B : public A
        {};

        class C : public Trait
        {};
        
      }
      
      void TestMeta::testIsInstance()
      {
        A a ;
        B b ;
        C c ;
        
        CPPUNIT_ASSERT(getClassTypeIdentifier(A).isInstance(&a)) ;
        CPPUNIT_ASSERT(getClassTypeIdentifier(B).isInstance(&b)) ;
        CPPUNIT_ASSERT(getClassTypeIdentifier(C).isInstance(&c)) ;
        CPPUNIT_ASSERT(getClassTypeIdentifier(A).isInstance(&b)) ;
        
        CPPUNIT_ASSERT(!(getClassTypeIdentifier(B).isInstance(&a))) ;
        CPPUNIT_ASSERT(!(getClassTypeIdentifier(B).isInstance(&c))) ;
        CPPUNIT_ASSERT(!(getClassTypeIdentifier(A).isInstance(&c))) ;
      }

      void TestMeta::setUp()
      {
      }

      void TestMeta::tearDown()
      {
      }

    }
  }
}
