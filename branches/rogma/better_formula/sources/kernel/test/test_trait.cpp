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
                            HasParent(HasTrait(Parent))) ;

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

        class HasParentTrait2 : public DeducedTrait
        {};

        DeclareDeducedTrait(HasParentTrait2,
                            And(HasTrait(Trait2),HasParent(HasTrait(Parent)))) ;

        class HasParentDeducedTrait1 : public DeducedTrait
        {};

        DeclareDeducedTrait(HasParentDeducedTrait1,
                            And(HasTrait(Trait2),HasParent(HasTrait(DeducedTrait1)))) ;

        class Played : public Trait
        {};
        class Mission : public Trait
        {};
        class ActivatedMission : public DeducedTrait
        {};
        DeclareDeducedTrait(ActivatedMission,
                            And(HasTrait(Played),
                                HasTrait(Mission))) ;

        class FlyingGroup : public Trait
        {};
        class ActivatedFlyingGroup : public DeducedTrait
        {};
        DeclareDeducedTrait(ActivatedFlyingGroup,
                            And(HasTrait(FlyingGroup),
                                HasParent(HasTrait(ActivatedMission)))) ;

      }

      void TestTrait::andBecomesTrueDepedentTrait()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;

        Trait1* t1 = new Trait1() ;
        object->addTrait(t1) ;

        CPPUNIT_ASSERT(t1->getDependentDeducedTraits().empty()) ;

        Trait2* t2 = new Trait2() ;
        object->addTrait(t2) ;

        CPPUNIT_ASSERT(t2->getDependentDeducedTraits().empty()) ;

        Trait3* t3 = new Trait3() ;
        object->addTrait(t3) ;

        DeducedTrait1* dt1 = object->getTrait<DeducedTrait1>() ;

        CPPUNIT_ASSERT(!t3->getDependentDeducedTraits().empty()) ;
        CPPUNIT_ASSERT(t3->getDependentDeducedTraits().find(dt1) != t3->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(t1->getDependentDeducedTraits().find(dt1) != t1->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(t2->getDependentDeducedTraits().find(dt1) != t2->getDependentDeducedTraits().end()) ;
      }

      void TestTrait::removeDeducedTraitOnAndDepedentTrait()
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

        CPPUNIT_ASSERT(t3->getDependentDeducedTraits().find(dt1) != t3->getDependentDeducedTraits().end()) ;
        object->destroyTrait(t1) ;
        CPPUNIT_ASSERT(t3->getDependentDeducedTraits().empty()) ;
      }

      void TestTrait::parentTraitIsHasParentDependency()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;
        Parent* parent = new Parent() ;
        object->addTrait(parent) ;

        Object* child = object->createObject() ;
        HasParentTrait1* dt = child->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt) ;
        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(dt) != parent->getDependentDeducedTraits().end()) ;
      }

      void TestTrait::childTraitIsHasChildDependency()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        Child* child_trait = new Child() ;
        child->addTrait(child_trait) ;

        HasChildTrait1* dt = object->getTrait<HasChildTrait1>() ;

        CPPUNIT_ASSERT(dt) ;
        CPPUNIT_ASSERT(child_trait->getDependentDeducedTraits().find(dt) != child_trait->getDependentDeducedTraits().end()) ;
      }

      void TestTrait::addNewTraitOnOrChangeDepedencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;

        Trait1Or* t1 = new Trait1Or() ;
        object->addTrait(t1) ;

        DeducedTrait2* dtor = object->getTrait<DeducedTrait2>() ;

        CPPUNIT_ASSERT(t1->getDependentDeducedTraits().find(dtor) != t1->getDependentDeducedTraits().end()) ;

        Trait2Or* t2 = new Trait2Or() ;
        object->addTrait(t2) ;

        CPPUNIT_ASSERT(t2->getDependentDeducedTraits().find(dtor) != t2->getDependentDeducedTraits().end()) ;
      }

      void TestTrait::addIntermediateTraitChangeHasParentDependencies()
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

        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(dt_father) != parent->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(dt_child) != parent->getDependentDeducedTraits().end()) ;

        // tested event : add an intermediate trait will change dependencies
        Parent* parent2 = new Parent() ;
        father->addTrait(parent2) ;

        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(dt_father) == parent->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(dt_child) == parent->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentDeducedTraits().find(dt_father) != parent2->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentDeducedTraits().find(dt_child) != parent2->getDependentDeducedTraits().end()) ;
      }

      void TestTrait::removeIntermediateTraitChangeHasParentDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* grand_father = model->createObject() ;
        Parent* parent = new Parent() ;
        grand_father->addTrait(parent) ;

        Object* father = grand_father->createObject() ;
        Parent* parent2 = new Parent() ;
        father->addTrait(parent2) ;
        HasParentTrait1* dt_father = father->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt_father) ;

        Object* child = father->createObject() ;
        HasParentTrait1* dt_child = child->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt_child) ;

        // check initial situation for sure-ness
        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(dt_father) == parent->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(dt_child) == parent->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentDeducedTraits().find(dt_father) != parent2->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentDeducedTraits().find(dt_child) != parent2->getDependentDeducedTraits().end()) ;

        // tested event : remove an intermediate trait will change dependencies
        father->destroyTrait(parent2) ;

        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(dt_father) != parent->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(dt_child) != parent->getDependentDeducedTraits().end()) ;
      }

      void TestTrait::removeTraitChangeHasParentDependenciesByBecommingFalse()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* grand_father = model->createObject() ;

        Object* father = grand_father->createObject() ;
        Parent* parent2 = new Parent() ;
        father->addTrait(parent2) ;
        HasParentTrait1* dt_father = father->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt_father) ;

        Object* child = father->createObject() ;
        HasParentTrait1* dt_child = child->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt_child) ;

        // check initial situation for sure-ness
        CPPUNIT_ASSERT(parent2->getDependentDeducedTraits().find(dt_father) != parent2->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentDeducedTraits().find(dt_child) != parent2->getDependentDeducedTraits().end()) ;

        // tested event : remove an intermediate trait will change dependencies
        father->destroyTrait(parent2) ;

        // no more traits so no more dependencies to check
      }

      void TestTrait::changeParentChangeHasParentDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* father1 = model->createObject() ;
        Parent* parent1 = new Parent() ;
        father1->addTrait(parent1) ;

        Object* father2 = model->createObject() ;
        Parent* parent2 = new Parent() ;
        father2->addTrait(parent2) ;

        Object* child = father1->createObject() ;
        HasParentTrait1* dt_child = child->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt_child) ;

        CPPUNIT_ASSERT(parent1->getDependentDeducedTraits().find(dt_child) != parent1->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentDeducedTraits().find(dt_child) == parent2->getDependentDeducedTraits().end()) ;

        // tested event : switch child parent
        child->changeParent(father2) ;

        CPPUNIT_ASSERT(parent1->getDependentDeducedTraits().find(dt_child) == parent1->getDependentDeducedTraits().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentDeducedTraits().find(dt_child) != parent2->getDependentDeducedTraits().end()) ;
      }

      void TestTrait::addTraitOnEmptyStructure()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* grand_father = model->createObject() ;

        Object* father = grand_father->createObject() ;
        CPPUNIT_ASSERT(!father->getTrait<HasParentTrait1>()) ;

        Object* child = father->createObject() ;
        CPPUNIT_ASSERT(!child->getTrait<HasParentTrait1>()) ;

        Parent* parent = new Parent() ;
        grand_father->addTrait(parent) ;

      }

      void TestTrait::hasParentFormulaDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* father = model->createObject() ;
        father->addTrait(new Parent()) ;

        Object* child = father->createObject() ;
        DeducedTrait* deduced = child->getTrait<HasParentTrait1>() ;
        Formula* formula = deduced->getFormula() ;
        std::set<DeducedTrait*> dependencies = formula->getDependentDeducedTraits(father) ;
        CPPUNIT_ASSERT(father->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(father->getTrait<HasParentTrait1>()->getFormula() == formula) ;
        CPPUNIT_ASSERT(dependencies.find(father->getTrait<HasParentTrait1>()) != dependencies.end()) ;
        CPPUNIT_ASSERT(dependencies.find(child->getTrait<HasParentTrait1>()) == dependencies.end()) ;
      }

      void TestTrait::andHasParentAddTraitChangeHasParentDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* grand_father = model->createObject() ;

        Object* father = grand_father->createObject() ;
        CPPUNIT_ASSERT(!father->getTrait<HasParentTrait2>()) ;

        Object* child1 = father->createObject() ;
        child1->addTrait(new Trait2()) ;
        CPPUNIT_ASSERT(!child1->getTrait<HasParentTrait2>()) ;

        Object* child2 = father->createObject() ;
        child2->addTrait(new Trait2()) ;
        CPPUNIT_ASSERT(!child2->getTrait<HasParentTrait2>()) ;

        Parent* parent = new Parent() ;
        grand_father->addTrait(parent) ;

        CPPUNIT_ASSERT(child1->getTrait<HasParentTrait2>()) ;

        CPPUNIT_ASSERT(parent->getDependentDeducedTraits().find(child1->getTrait<HasParentTrait2>()) != parent->getDependentDeducedTraits().end()) ;
      }

      void TestTrait::hasParentOnDeducedTrait()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Mission()) ;

        {
          Kernel::Object* team = mission->createObject() ;

          Kernel::Object* flying_group = team->createObject() ;
          flying_group->addTrait(new FlyingGroup()) ;
        }

        {
          Kernel::Object* team = mission->createObject() ;

          Kernel::Object* flying_group = team->createObject() ;
          flying_group->addTrait(new FlyingGroup()) ;


          /// @temp
          CPPUNIT_ASSERT(!flying_group->getTrait<ActivatedFlyingGroup>()) ;
        }

        mission->addTrait(new Played()) ;
      }

      namespace
      {
        class T1 : public Trait
        {};

        class HasT1 : public DeducedTrait
        {};

        DeclareDeducedTrait(HasT1,HasTrait(T1)) ;

      }

      void TestTrait::hasTraitFormulaUpdaterTraits()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* object = model->createObject() ;
        object->addTrait(new T1()) ;

        Formula* formula = ((DeducedTrait*)object->getTrait<HasT1>())->getFormula() ;

        std::set<Trait*> updater_traits(formula->getUpdaterTraits(object)) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,updater_traits.size()) ;
        CPPUNIT_ASSERT(updater_traits.find(object->getTrait<T1>()) != updater_traits.end()) ;
      }

      void TestTrait::andUpdaterTraits()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* object = model->createObject() ;
        object->addTrait(new Trait1()) ;
        object->addTrait(new Trait2()) ;
        object->addTrait(new Trait3()) ;

        Formula* formula = ((DeducedTrait*)object->getTrait<DeducedTrait1>())->getFormula() ;

        std::set<Trait*> updater_traits(formula->getUpdaterTraits(object)) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)3,updater_traits.size()) ;
        CPPUNIT_ASSERT(updater_traits.find(object->getTrait<Trait1>()) != updater_traits.end()) ;
        CPPUNIT_ASSERT(updater_traits.find(object->getTrait<Trait2>()) != updater_traits.end()) ;
        CPPUNIT_ASSERT(updater_traits.find(object->getTrait<Trait3>()) != updater_traits.end()) ;
      }

      void TestTrait::hasParentUpdaterTraits()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* object = model->createObject() ;
        object->addTrait(new Parent()) ;

        Kernel::Object* object2 = object->createObject() ;

        Formula* formula = ((DeducedTrait*)object->getTrait<HasParentTrait1>())->getFormula() ;

        {
          std::set<Trait*> updater_traits(formula->getUpdaterTraits(object)) ;
          CPPUNIT_ASSERT_EQUAL((unsigned int)1,updater_traits.size()) ;
          CPPUNIT_ASSERT(updater_traits.find(object->getTrait<Parent>()) != updater_traits.end()) ;
        }
        {
          std::set<Trait*> updater_traits(formula->getUpdaterTraits(object2)) ;
          CPPUNIT_ASSERT_EQUAL((unsigned int)1,updater_traits.size()) ;
          CPPUNIT_ASSERT(updater_traits.find(object->getTrait<Parent>()) != updater_traits.end()) ;
        }

      }

    }
  }
}
