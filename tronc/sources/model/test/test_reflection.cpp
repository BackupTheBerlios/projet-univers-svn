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
#include <Reflex/Reflex.h>

#include <kernel/object.h>
#include <kernel/model.h>

#include <model/model.h>
#include <model/positioned.h>
#include <model/oriented.h>

#include <model/test/test_reflection.h>


namespace ProjetUnivers
{
  namespace Model
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestReflection) ;

      void TestReflection::spike()
      {
        // get a meta type
        Reflex::Type type_positioned(Reflex::Type::ByTypeInfo(typeid(Positioned))) ;
        CPPUNIT_ASSERT_EQUAL(std::string("ProjetUnivers::Model::Positioned"),
                             type_positioned.Name(Reflex::SCOPED)) ;

        // check that it is a trait
        Reflex::Type trait_type(Reflex::Type::ByName("ProjetUnivers::Kernel::Trait")) ;
        CPPUNIT_ASSERT(type_positioned.HasBase(trait_type)) ;

        trait_type.SetTypeInfo(typeid(Kernel::Trait)) ;

        // create an object from this meta type
        Positioned* positioned = static_cast<Positioned*>(type_positioned.Construct().Address()) ;
        CPPUNIT_ASSERT(positioned) ;
        CPPUNIT_ASSERT(!positioned->getObject()) ;

        Reflex::Type type_recursively_positioned(Reflex::Type::ByTypeInfo(typeid(RecursivelyPositioned))) ;
        Reflex::Type type_deduced_trait(Reflex::Type::ByName("ProjetUnivers::Kernel::DeducedTrait")) ;
        CPPUNIT_ASSERT(type_recursively_positioned.HasBase(type_deduced_trait)) ;
      }

      void TestReflection::primitiveTraits()
      {
        Reflex::Type trait_type(Reflex::Type::ByName("ProjetUnivers::Kernel::Trait")) ;
        Reflex::Type relation_type(Reflex::Type::ByName("ProjetUnivers::Kernel::Relation")) ;

        bool has_sub_types = false ;

        // all types
        for(Reflex::Type_Iterator type = Reflex::Type::Type_Begin() ;
            type != Reflex::Type::Type_End() ;
            ++type)
        {
          if (type->IsClass())
          {
            Reflex::Type Class = *type ;
            // only primitive traits or primitive relations
            if (Class.HasBase(trait_type) || Class.HasBase(relation_type))
            {
              std::cout << Class.Name(Reflex::SCOPED) << std::endl ;

              for(Reflex::Member_Iterator member = Class.Member_Begin() ; member != Class.Member_End() ; ++member)
              {
                std::cout << member->Name(Reflex::SCOPED) << std::endl ;
              }

              has_sub_types = true ;
            }
          }
        }

        CPPUNIT_ASSERT(has_sub_types) ;
      }


    }
  }
}


