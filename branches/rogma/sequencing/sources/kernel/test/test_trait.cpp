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
#include <iostream>
#include <kernel/deduced_trait.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/test/test_trait.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Kernel::Test::TestTrait) ;

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {


      namespace
      {
        class Trait1 : public Trait
        {
        public:

          Trait1()
          : Trait(),
            value(0)
          {}

          void change(const int& i_new_value)
          {
            value = i_new_value ;
            notify() ;
          }

          int getValue() const
          {
            return value ;
          }

        private:

          int value ;

        };

        class Trait2 : public Trait
        {
        public:

          Trait2()
          : Trait(),
            value(0)
          {}

          void change(const int& i_new_value)
          {
            value = i_new_value ;
            notify() ;
          }

          int getValue() const
          {
            return value ;
          }

        private:

          int value ;

        };

        class Trait3 : public Trait
        {
        public:

          Trait3()
          : Trait(),
            value(0)
          {}

          void change(const int& i_new_value)
          {
            value = i_new_value ;
            notify() ;
          }

          int getValue() const
          {
            return value ;
          }

        private:

          int value ;

        };

        class SubTrait : public Trait1
        {};

        class DeducedTrait1 : public Kernel::DeducedTrait
        {};


        /// A deduced trait.
        DeclareDeducedTrait(DeducedTrait1,
                            And(HasTrait(Trait1),
                                HasTrait(Trait2),
                                HasTrait(Trait3))) ;

        class Parent : public Trait
        {
        public:

          void modify()
          {
            notify() ;
          }
        };

        class HasParentTrait1 : public DeducedTrait
        {};

        DeclareDeducedTrait(HasParentTrait1,
                            HasParent(Parent)) ;

        class Child : public Trait
        {
        public:

          void modify()
          {
            notify() ;
          }
        };

        class HasChildTrait1 : public DeducedTrait
        {};


        DeclareDeducedTrait(HasChildTrait1,HasChild(Child)) ;

        class Trait1Or : public Trait
        {};

        class Trait2Or : public Trait
        {};

        class DeducedTrait2 : public Kernel::DeducedTrait
        {};

        /// A deduced trait.
        DeclareDeducedTrait(DeducedTrait2,
                            Or(HasTrait(Trait1Or),
                               HasTrait(Trait2Or))) ;

      }

      void TestTrait::depedentTrait()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;

        Trait1* t1 = new Trait1() ;
        object->addTrait(t1) ;

        CPPUNIT_ASSERT(t1->getDependentTraits().empty()) ;

        Trait2* t2 = new Trait2() ;
        object->addTrait(t2) ;

        CPPUNIT_ASSERT(t2->getDependentTraits().empty()) ;

        Trait3* t3 = new Trait3() ;
        object->addTrait(t3) ;

        DeducedTrait1* dt1 = object->getTrait<DeducedTrait1>() ;

        CPPUNIT_ASSERT(!t3->getDependentTraits().empty()) ;
        CPPUNIT_ASSERT(t3->getDependentTraits().find(dt1) != t3->getDependentTraits().end()) ;
        CPPUNIT_ASSERT(t1->getDependentTraits().find(dt1) != t1->getDependentTraits().end()) ;
        CPPUNIT_ASSERT(t2->getDependentTraits().find(dt1) != t2->getDependentTraits().end()) ;
      }

      void TestTrait::removeDeducedTrait()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;
        Trait1* t1 = new Trait1() ;
        object->addTrait(t1) ;
        Trait2* t2 = new Trait2() ;
        object->addTrait(t2) ;
        Trait3* t3 = new Trait3() ;
        object->addTrait(t3) ;
        DeducedTrait1* dt1 = object->getTrait<DeducedTrait1>() ;

        CPPUNIT_ASSERT(t3->getDependentTraits().find(dt1) != t3->getDependentTraits().end()) ;
        object->destroyTrait(t1) ;
        CPPUNIT_ASSERT(t3->getDependentTraits().empty()) ;
      }

      void TestTrait::parentTrait()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;
        Parent* parent = new Parent() ;
        object->addTrait(parent) ;

        Object* child = object->createObject() ;
        HasParentTrait1* dt = child->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt) ;
        CPPUNIT_ASSERT(parent->getDependentTraits().find(dt) != parent->getDependentTraits().end()) ;
      }

      void TestTrait::childTrait()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        Child* child_trait = new Child() ;
        child->addTrait(child_trait) ;

        HasChildTrait1* dt = object->getTrait<HasChildTrait1>() ;

        CPPUNIT_ASSERT(dt) ;
        CPPUNIT_ASSERT(child_trait->getDependentTraits().find(dt) != child_trait->getDependentTraits().end()) ;
      }

      void TestTrait::orAddNewTrait()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;

        Trait1Or* t1 = new Trait1Or() ;
        object->addTrait(t1) ;

        DeducedTrait2* dtor = object->getTrait<DeducedTrait2>() ;

        CPPUNIT_ASSERT(t1->getDependentTraits().find(dtor) != t1->getDependentTraits().end()) ;

        Trait2Or* t2 = new Trait2Or() ;
        object->addTrait(t2) ;

        CPPUNIT_ASSERT(t2->getDependentTraits().find(dtor) != t2->getDependentTraits().end()) ;
      }

      void TestTrait::changeParent()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* grand_father = model->createObject() ;
        Parent* parent = new Parent() ;
        grand_father->addTrait(parent) ;

        Object* father = grand_father->createObject() ;
        HasParentTrait1* dt_father = father->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt_father) ;

        Object* child = father->createObject() ;
        HasParentTrait1* dt_child = child->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt_child) ;

        CPPUNIT_ASSERT(parent->getDependentTraits().find(dt_father) != parent->getDependentTraits().end()) ;
        CPPUNIT_ASSERT(parent->getDependentTraits().find(dt_child) != parent->getDependentTraits().end()) ;
        // add an intermediate trait will change dependencies
        Parent* parent2 = new Parent() ;
        father->addTrait(parent2) ;
        CPPUNIT_ASSERT(parent->getDependentTraits().find(dt_father) == parent->getDependentTraits().end()) ;
        CPPUNIT_ASSERT(parent->getDependentTraits().find(dt_child) == parent->getDependentTraits().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentTraits().find(dt_father) != parent2->getDependentTraits().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentTraits().find(dt_child) != parent2->getDependentTraits().end()) ;
      }


    }
  }
}
