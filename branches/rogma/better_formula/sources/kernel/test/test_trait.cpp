/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

        DeclareDeducedTrait(HasChildTrait1,HasChild(HasTrait(Child))) ;

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

        CPPUNIT_ASSERT(t1->getDependentNotifiables().empty()) ;

        Trait2* t2 = new Trait2() ;
        object->addTrait(t2) ;

        CPPUNIT_ASSERT(t2->getDependentNotifiables().empty()) ;

        Trait3* t3 = new Trait3() ;
        object->addTrait(t3) ;

        DeducedTrait1* dt1 = object->getTrait<DeducedTrait1>() ;

        CPPUNIT_ASSERT(!t3->getDependentNotifiables().empty()) ;
        CPPUNIT_ASSERT(t3->getDependentNotifiables().find(dt1) != t3->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(t1->getDependentNotifiables().find(dt1) != t1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(t2->getDependentNotifiables().find(dt1) != t2->getDependentNotifiables().end()) ;
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

        CPPUNIT_ASSERT(t3->getDependentNotifiables().find(dt1) != t3->getDependentNotifiables().end()) ;
        object->destroyTrait(t1) ;
        CPPUNIT_ASSERT(t3->getDependentNotifiables().empty()) ;
      }

      void TestTrait::parentTraitHasParentDependency()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;
        Parent* parent = new Parent() ;
        object->addTrait(parent) ;

        Object* child = object->createObject() ;
        HasParentTrait1* dt = child->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt) ;
        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(dt) != parent->getDependentNotifiables().end()) ;
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
        CPPUNIT_ASSERT(child_trait->getDependentNotifiables().find(dt) != child_trait->getDependentNotifiables().end()) ;
      }

      void TestTrait::addNewTraitOnOrChangeDepedencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;

        Trait1Or* t1 = new Trait1Or() ;
        object->addTrait(t1) ;

        DeducedTrait2* dtor = object->getTrait<DeducedTrait2>() ;

        CPPUNIT_ASSERT(t1->getDependentNotifiables().find(dtor) != t1->getDependentNotifiables().end()) ;

        Trait2Or* t2 = new Trait2Or() ;
        object->addTrait(t2) ;

        CPPUNIT_ASSERT(t2->getDependentNotifiables().find(dtor) != t2->getDependentNotifiables().end()) ;
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

        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(dt_father) != parent->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(dt_child) != parent->getDependentNotifiables().end()) ;

        // tested event : add an intermediate trait will change dependencies
        Parent* parent2 = new Parent() ;
        father->addTrait(parent2) ;

        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(dt_father) == parent->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(dt_child) == parent->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_father) != parent2->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_child) != parent2->getDependentNotifiables().end()) ;
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
        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(dt_father) == parent->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(dt_child) == parent->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_father) != parent2->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_child) != parent2->getDependentNotifiables().end()) ;

        // tested event : remove an intermediate trait will change dependencies
        father->destroyTrait(parent2) ;

        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(dt_father) != parent->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(dt_child) != parent->getDependentNotifiables().end()) ;
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
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_father) != parent2->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_child) != parent2->getDependentNotifiables().end()) ;

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

        CPPUNIT_ASSERT(parent1->getDependentNotifiables().find(dt_child) != parent1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_child) == parent2->getDependentNotifiables().end()) ;

        // tested event : switch child parent
        child->changeParent(father2) ;

        CPPUNIT_ASSERT(parent1->getDependentNotifiables().find(dt_child) == parent1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_child) != parent2->getDependentNotifiables().end()) ;
      }

      void TestTrait::changeParentChangeHasParentDependenciesRecursivelly()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* father1 = model->createObject() ;
        Parent* parent1 = new Parent() ;
        father1->addTrait(parent1) ;

        Object* father2 = model->createObject() ;
        Parent* parent2 = new Parent() ;
        father2->addTrait(parent2) ;

        Object* child = father1->createObject() ;
        Object* grand_child = child->createObject() ;
        HasParentTrait1* dt_child = grand_child->getTrait<HasParentTrait1>() ;
        CPPUNIT_ASSERT(dt_child) ;

        CPPUNIT_ASSERT(parent1->getDependentNotifiables().find(dt_child) != parent1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_child) == parent2->getDependentNotifiables().end()) ;

        // tested event : switch child parent
        child->changeParent(father2) ;

        CPPUNIT_ASSERT(parent1->getDependentNotifiables().find(dt_child) == parent1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(parent2->getDependentNotifiables().find(dt_child) != parent2->getDependentNotifiables().end()) ;
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
        std::set<Notifiable*> dependencies(formula->getDependentNotifiables(father)) ;
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

        CPPUNIT_ASSERT(parent->getDependentNotifiables().find(child1->getTrait<HasParentTrait2>()) != parent->getDependentNotifiables().end()) ;
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

          CPPUNIT_ASSERT(!flying_group->getTrait<ActivatedFlyingGroup>()) ;
        }

        mission->addTrait(new Played()) ;
      }

      void TestTrait::destroyParentObject()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        root->addTrait(new Parent()) ;

        Kernel::Object* mission = root->createObject() ;
        mission->addTrait(new Mission()) ;

        Kernel::Object* team = mission->createObject() ;

        Kernel::Object* flying_group = team->createObject() ;
        flying_group->addTrait(new FlyingGroup()) ;

        mission->addTrait(new Played()) ;

        CPPUNIT_ASSERT(mission->getTrait<HasParentTrait1>()) ;

        mission->destroyObject() ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,root->getTrait<Parent>()->getDependentNotifiables().size()) ;
      }

      void TestTrait::changeParentChangingNothing()
      {
        // Trait2^Parent
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        Kernel::Object* root2 = model->createObject() ;
        root2->addTrait(new Parent()) ;

        Kernel::Object* object = root2->createObject() ;
        object->addTrait(new Trait2()) ;

        root2->changeParent(root) ;
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

      namespace
      {
        class Ancestor : public Trait
        {};

        class WithAncestor : public DeducedTrait
        {};

        DeclareDeducedTrait(WithAncestor,HasAncestor(HasTrait(Ancestor))) ;
      }

      void TestTrait::hasAncestorHasDependencies()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* object = model->createObject() ;
        Trait* a = new Ancestor() ;
        object->addTrait(a) ;

        Kernel::Object* object2 = object->createObject() ;
        WithAncestor* d = object2->getTrait<WithAncestor>() ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,a->getDependentNotifiables().size()) ;
        CPPUNIT_ASSERT(a->getDependentNotifiables().find(d) != a->getDependentNotifiables().end()) ;
      }

      void TestTrait::addIntermediateTraitChangeHasAncestorDependencies()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        Trait* a = new Ancestor() ;
        root->addTrait(a) ;

        Kernel::Object* object1 = root->createObject() ;

        Kernel::Object* object2 = object1->createObject() ;
        WithAncestor* d = object2->getTrait<WithAncestor>() ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,a->getDependentNotifiables().size()) ;
        CPPUNIT_ASSERT(a->getDependentNotifiables().find(d) != a->getDependentNotifiables().end()) ;

        Trait* a1 = new Ancestor() ;
        object1->addTrait(a1) ;

        CPPUNIT_ASSERT(a->getDependentNotifiables().find(d) == a->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,a1->getDependentNotifiables().size()) ;
        CPPUNIT_ASSERT(a1->getDependentNotifiables().find(d) != a1->getDependentNotifiables().end()) ;
      }

      void TestTrait::removeIntermediateTraitChangeHasAncestorDependencies()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* root = model->createObject() ;
        Trait* a = new Ancestor() ;
        root->addTrait(a) ;

        Kernel::Object* object1 = root->createObject() ;
        Trait* a1 = new Ancestor() ;
        object1->addTrait(a1) ;

        Kernel::Object* object2 = object1->createObject() ;
        WithAncestor* d = object2->getTrait<WithAncestor>() ;

        CPPUNIT_ASSERT(a->getDependentNotifiables().find(d) == a->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,a1->getDependentNotifiables().size()) ;
        CPPUNIT_ASSERT(a1->getDependentNotifiables().find(d) != a1->getDependentNotifiables().end()) ;

        object1->destroyTrait(a1) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,a->getDependentNotifiables().size()) ;
        CPPUNIT_ASSERT(a->getDependentNotifiables().find(d) != a->getDependentNotifiables().end()) ;
      }

      void TestTrait::changeParentChangeHasAncestorDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* father1 = model->createObject() ;
        Ancestor* a1 = new Ancestor() ;
        father1->addTrait(a1) ;

        Object* father2 = model->createObject() ;
        Ancestor* a2 = new Ancestor() ;
        father2->addTrait(a2) ;

        Object* child = father1->createObject() ;
        WithAncestor* dt_child = child->getTrait<WithAncestor>() ;
        CPPUNIT_ASSERT(dt_child) ;

        CPPUNIT_ASSERT(a1->getDependentNotifiables().find(dt_child) != a1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(a2->getDependentNotifiables().find(dt_child) == a2->getDependentNotifiables().end()) ;

        // tested event : switch child parent
        child->changeParent(father2) ;

        CPPUNIT_ASSERT(a1->getDependentNotifiables().find(dt_child) == a1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(a2->getDependentNotifiables().find(dt_child) != a2->getDependentNotifiables().end()) ;
      }

      void TestTrait::destroyAncestorObject()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* father1 = model->createObject() ;
        Ancestor* a1 = new Ancestor() ;
        father1->addTrait(a1) ;

        Object* father2 = model->createObject() ;
        Ancestor* a2 = new Ancestor() ;
        father2->addTrait(a2) ;

        Object* child = father1->createObject() ;
        WithAncestor* dt_child = child->getTrait<WithAncestor>() ;
        CPPUNIT_ASSERT(dt_child) ;

        father1->destroyObject() ;
      }

      namespace
      {
        class Positionned : public Trait
        {};

        class RecursivelyPositionned : public DeducedTrait
        {};

        DeclareDeducedTrait(RecursivelyPositionned,
                            Or(HasTrait(Positionned),
                               HasAncestor(HasTrait(RecursivelyPositionned)))) ;
      }

      void TestTrait::destroyObjectOnRecusiveFormula()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;
        root->addTrait(new Positionned()) ;

        Object* child = root->createObject() ;
        child->addTrait(new Positionned()) ;

        child->destroyTrait(child->getTrait<Positionned>()) ;

        child->destroyObject() ;
      }

      void TestTrait::hasChildHasDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;

        Object* child = root->createObject() ;
        Child* c = new Child() ;
        child->addTrait(c) ;

        HasChildTrait1* dt_root = root->getTrait<HasChildTrait1>() ;
        CPPUNIT_ASSERT(dt_root) ;

        CPPUNIT_ASSERT(c->getDependentNotifiables().find(dt_root) != c->getDependentNotifiables().end()) ;
      }

      void TestTrait::addingIntermediateTraitChangeHasChildDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Object* grand_child = child->createObject() ;
        Child* gc = new Child() ;
        grand_child->addTrait(gc) ;

        HasChildTrait1* dt_root = root->getTrait<HasChildTrait1>() ;
        CPPUNIT_ASSERT(dt_root) ;

        CPPUNIT_ASSERT(gc->getDependentNotifiables().find(dt_root) != gc->getDependentNotifiables().end()) ;

        Child* c = new Child() ;
        child->addTrait(c) ;

        CPPUNIT_ASSERT(c->getDependentNotifiables().find(dt_root) != c->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(gc->getDependentNotifiables().find(dt_root) == gc->getDependentNotifiables().end()) ;
      }

      void TestTrait::removingIntermediateTraitChangeHasChildDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Child* c = new Child() ;
        child->addTrait(c) ;
        Object* grand_child = child->createObject() ;
        Child* gc = new Child() ;
        grand_child->addTrait(gc) ;

        HasChildTrait1* dt_root = root->getTrait<HasChildTrait1>() ;
        CPPUNIT_ASSERT(dt_root) ;

        CPPUNIT_ASSERT(gc->getDependentNotifiables().find(dt_root) == gc->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(c->getDependentNotifiables().find(dt_root) != c->getDependentNotifiables().end()) ;

        child->destroyTrait(c) ;

        CPPUNIT_ASSERT(gc->getDependentNotifiables().find(dt_root) != gc->getDependentNotifiables().end()) ;
      }

      namespace
      {
        class Active : public Trait
        {};

        class ActiveObserver : public DeducedTrait
        {};

        DeclareDeducedTrait(ActiveObserver,HasTrait(Active)) ;

        class DisplayedSolid : public DeducedTrait
        {};

        DeclareDeducedTrait(DisplayedSolid,HasChild(HasTrait(ActiveObserver))) ;
      }

      void TestTrait::destroyChildObjectShouldNotCrash()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Object* grand_child = child->createObject() ;
        grand_child->addTrait(new Active()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(DisplayedSolid)) ;

        CPPUNIT_ASSERT_EQUAL((short)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,root->getNumberOfTrueChildFormulae(formula)) ;

        grand_child->destroyObject() ;
      }

      namespace
      {
        class R : public Relation
        {};

        class TR : public Trait
        {};

        class LinkedToTR : public DeducedTrait
        {};

        DeclareDeducedTrait(LinkedToTR,IsRelated(R,HasTrait(TR))) ;
      }


      void TestTrait::isRelatedHasDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination = model->createObject() ;

        Trait* tr = destination->addTrait(new TR()) ;

        Link<R>(source,destination) ;

        DeducedTrait* dt = source->getTrait<LinkedToTR>() ;

        CPPUNIT_ASSERT(tr->getDependentNotifiables().find(dt) != tr->getDependentNotifiables().end()) ;
      }

      void TestTrait::addRelatedChangeDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination1 = model->createObject() ;

        Trait* tr1 = destination1->addTrait(new TR()) ;

        Link<R>(source,destination1) ;

        Object* destination2 = model->createObject() ;
        Trait* tr2 = destination2->addTrait(new TR()) ;

        Link<R>(source,destination2) ;

        DeducedTrait* dt = source->getTrait<LinkedToTR>() ;

        CPPUNIT_ASSERT(tr1->getDependentNotifiables().find(dt) != tr1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(tr2->getDependentNotifiables().find(dt) != tr2->getDependentNotifiables().end()) ;
      }

      void TestTrait::removeRelatedChangeDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination1 = model->createObject() ;

        Trait* tr1 = destination1->addTrait(new TR()) ;

        Link<R>(source,destination1) ;

        Object* destination2 = model->createObject() ;
        Trait* tr2 = destination2->addTrait(new TR()) ;

        Link<R>(source,destination2) ;

        UnLink<R>(source,destination1) ;

        DeducedTrait* dt = source->getTrait<LinkedToTR>() ;

        CPPUNIT_ASSERT(tr1->getDependentNotifiables().find(dt) == tr1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(tr2->getDependentNotifiables().find(dt) != tr2->getDependentNotifiables().end()) ;
      }

      namespace
      {
        class ROnly : public Relation
        {};

        class TROnly : public Trait
        {};

        class LinkedToTROnly : public DeducedTrait
        {};

        DeclareDeducedTrait(LinkedToTROnly,IsOnlyRelated(ROnly,HasTrait(TROnly))) ;
      }

      void TestTrait::isOnlyRelatedHasDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination = model->createObject() ;

        Trait* tr = destination->addTrait(new TROnly()) ;

        Link<ROnly>(source,destination) ;

        DeducedTrait* dt = source->getTrait<LinkedToTROnly>() ;

        CPPUNIT_ASSERT(tr->getDependentNotifiables().find(dt) != tr->getDependentNotifiables().end()) ;
      }

      void TestTrait::addOnlyRelatedChangeDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination1 = model->createObject() ;

        Trait* tr1 = destination1->addTrait(new TROnly()) ;

        Link<ROnly>(source,destination1) ;

        Object* destination2 = model->createObject() ;
        Trait* tr2 = destination2->addTrait(new TROnly()) ;

        Link<ROnly>(source,destination2) ;

        DeducedTrait* dt = source->getTrait<LinkedToTROnly>() ;

        CPPUNIT_ASSERT(tr1->getDependentNotifiables().find(dt) != tr1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(tr2->getDependentNotifiables().find(dt) != tr2->getDependentNotifiables().end()) ;
      }

      void TestTrait::addFalseOnlyRelatedChangeDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination1 = model->createObject() ;

        Trait* tr1 = destination1->addTrait(new TROnly()) ;

        Link<ROnly>(source,destination1) ;

        Object* destination2 = model->createObject() ;

        Link<ROnly>(source,destination2) ;

        CPPUNIT_ASSERT(!source->getTrait<LinkedToTROnly>()) ;

        CPPUNIT_ASSERT(tr1->getDependentNotifiables().empty()) ;
      }


      namespace
      {
        class Starter : public Trait
        {};

        class Reflexive : public DeducedTrait
        {};

        DeclareDeducedTrait(Reflexive,
                            Or(HasTrait(Starter),
                               HasParent(HasTrait(Reflexive)))) ;
      }

      void TestTrait::updaterTraitsShouldNotBeReflexive()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;
        root->addTrait(new Starter()) ;

        std::set<Notifiable*> dependencies(root->getTrait<Reflexive>()->getDependentNotifiables()) ;
        CPPUNIT_ASSERT(dependencies.find(root->getTrait<Reflexive>()) == dependencies.end()) ;
      }

      void TestTrait::addingAncestorChangeNumberOfTrueChildFormulae()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(WithAncestor)) ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Object* grand_child = child->createObject() ;

        CPPUNIT_ASSERT_EQUAL((short)0,root->getNumberOfTrueChildFormulae(formula)) ;

        child->addTrait(new Ancestor()) ;

        CPPUNIT_ASSERT_EQUAL((short)0,root->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)0,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;

        root->addTrait(new Ancestor()) ;

        CPPUNIT_ASSERT_EQUAL((short)0,root->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)2,grand_child->getNumberOfTrueChildFormulae(formula)) ;
      }

      void TestTrait::addingParentChangeNumberOfTrueChildFormulae()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(HasParentTrait1)) ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Object* grand_child = child->createObject() ;

        CPPUNIT_ASSERT_EQUAL((short)0,root->getNumberOfTrueChildFormulae(formula)) ;

        child->addTrait(new Parent()) ;

        CPPUNIT_ASSERT_EQUAL((short)0,root->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;

        root->addTrait(new Parent()) ;

        CPPUNIT_ASSERT_EQUAL((short)1,root->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)2,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)2,grand_child->getNumberOfTrueChildFormulae(formula)) ;
      }

      void TestTrait::addingChildChangeNumberOfTrueChildFormulae()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(HasChildTrait1)) ;
        {
          Object* root = model->createObject() ;
          Object* child = root->createObject() ;
          Object* grand_child = child->createObject() ;

          CPPUNIT_ASSERT_EQUAL((short)0,root->getNumberOfTrueChildFormulae(formula)) ;

          child->addTrait(new Child()) ;

          CPPUNIT_ASSERT_EQUAL((short)1,root->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((short)1,child->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((short)0,grand_child->getNumberOfTrueChildFormulae(formula)) ;

          root->addTrait(new Child()) ;

          CPPUNIT_ASSERT_EQUAL((short)2,root->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((short)1,child->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((short)0,grand_child->getNumberOfTrueChildFormulae(formula)) ;
        }
        {
          Object* root = model->createObject() ;
          Object* child = root->createObject() ;
          Object* grand_child = child->createObject() ;

          CPPUNIT_ASSERT_EQUAL((short)0,root->getNumberOfTrueChildFormulae(formula)) ;

          child->addTrait(new Child()) ;

          CPPUNIT_ASSERT_EQUAL((short)1,root->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((short)1,child->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((short)0,grand_child->getNumberOfTrueChildFormulae(formula)) ;

          grand_child->addTrait(new Child()) ;

          CPPUNIT_ASSERT_EQUAL((short)2,root->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((short)2,child->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((short)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;
        }
      }

      void TestTrait::changingParentOfHasParentChangesNumberOfTrueChildFormulae()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(HasParentTrait1)) ;

        Object* root1 = model->createObject() ;
        Object* child = root1->createObject() ;
        Object* grand_child = child->createObject() ;

        Object* root2 = model->createObject() ;

        child->addTrait(new Parent()) ;
        root1->addTrait(new Parent()) ;

        CPPUNIT_ASSERT_EQUAL((short)1,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)0,root2->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)2,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)2,grand_child->getNumberOfTrueChildFormulae(formula)) ;

        child->changeParent(root2) ;

        CPPUNIT_ASSERT_EQUAL((short)1,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)0,root2->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;
      }

      void TestTrait::changingParentOfHasAncestorChangesNumberOfTrueChildFormulae()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(WithAncestor)) ;

        Object* root1 = model->createObject() ;
        Object* child = root1->createObject() ;
        Object* grand_child = child->createObject() ;

        child->addTrait(new Ancestor()) ;
        root1->addTrait(new Ancestor()) ;

        Object* root2 = model->createObject() ;

        CPPUNIT_ASSERT_EQUAL((short)0,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)0,root2->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)2,grand_child->getNumberOfTrueChildFormulae(formula)) ;

        child->changeParent(root2) ;

        CPPUNIT_ASSERT_EQUAL((short)0,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)0,root2->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)0,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;
      }

      void TestTrait::changingParentOfHasChildChangesNumberOfTrueChildFormulae()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(HasChildTrait1)) ;

        Object* root1 = model->createObject() ;

        Object* child = root1->createObject() ;
        Object* grand_child = child->createObject() ;

        Object* root2 = model->createObject() ;

        child->addTrait(new Child()) ;
        grand_child->addTrait(new Child()) ;

        CPPUNIT_ASSERT_EQUAL((short)2,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)0,root2->getNumberOfTrueChildFormulae(formula)) ;

        child->changeParent(root2) ;

        CPPUNIT_ASSERT_EQUAL((short)0,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((short)2,root2->getNumberOfTrueChildFormulae(formula)) ;
      }



    }
  }
}
