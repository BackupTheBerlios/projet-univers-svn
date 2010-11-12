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

#include <kernel/test/reflection/meta.h>

#include <kernel/test/test_meta.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestMeta) ;

      void TestMeta::testIsInstance()
      {
        Meta::A a ;
        Meta::B b ;
        Meta::C c ;

        CPPUNIT_ASSERT(getClassTypeIdentifier(Meta::A).isInstance(&a)) ;
        CPPUNIT_ASSERT(getClassTypeIdentifier(Meta::B).isInstance(&b)) ;
        CPPUNIT_ASSERT(getClassTypeIdentifier(Meta::C).isInstance(&c)) ;
        CPPUNIT_ASSERT(getClassTypeIdentifier(Meta::A).isInstance(&b)) ;

        CPPUNIT_ASSERT(!(getClassTypeIdentifier(Meta::B).isInstance(&a))) ;
        CPPUNIT_ASSERT(!(getClassTypeIdentifier(Meta::B).isInstance(&c))) ;
        CPPUNIT_ASSERT(!(getClassTypeIdentifier(Meta::A).isInstance(&c))) ;
      }

      void TestMeta::testClassName()
      {
        CPPUNIT_ASSERT_EQUAL(std::string("Kernel::Test::Meta::A"),getClassTypeIdentifier(Meta::A).fullName()) ;
        CPPUNIT_ASSERT_EQUAL(std::string("Kernel::Test::Meta::IHaveALongName"),getClassTypeIdentifier(Meta::IHaveALongName).fullName()) ;
      }

      void TestMeta::compare()
      {
        // non reflexive
        CPPUNIT_ASSERT(!(getClassTypeIdentifier(Meta::A) < getClassTypeIdentifier(Meta::A))) ;

        // anti symetric
        CPPUNIT_ASSERT(getClassTypeIdentifier(Meta::A) < getClassTypeIdentifier(Meta::B) ||
                       getClassTypeIdentifier(Meta::B) < getClassTypeIdentifier(Meta::A)) ;
        CPPUNIT_ASSERT(!(getClassTypeIdentifier(Meta::A) < getClassTypeIdentifier(Meta::B) &&
                       getClassTypeIdentifier(Meta::B) < getClassTypeIdentifier(Meta::A))) ;
      }

      void TestMeta::inherits()
      {
        TypeIdentifier type_A(getClassTypeIdentifier(Meta::A)) ;
        TypeIdentifier type_B(getClassTypeIdentifier(Meta::B)) ;
        TypeIdentifier type_C(getClassTypeIdentifier(Meta::C)) ;
        TypeIdentifier type_trait(getClassTypeIdentifier(Trait)) ;
        CPPUNIT_ASSERT(type_B.inherits(type_A)) ;
        CPPUNIT_ASSERT(!type_B.inherits(type_C)) ;
        CPPUNIT_ASSERT(type_A.inherits(type_trait)) ;
        CPPUNIT_ASSERT(type_B.inherits(type_trait)) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)2,type_A.subTypes().size()) ;
      }

      namespace Local
      {
        class A
        {};
      }

      void TestMeta::subTypes()
      {
        TypeIdentifier type_A(getClassTypeIdentifier(Local::A)) ;
        CPPUNIT_ASSERT(!type_A.subTypes().empty()) ;
      }

    }
  }
}
