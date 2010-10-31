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
#include <kernel/log.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/test/test_trait.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestTrait) ;

      namespace TestTraitLocal
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

      using namespace TestTraitLocal ;

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

      void TestTrait::removeTraitOnOrChangeDepedencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* object = model->createObject() ;
        Trait1Or* t1 = new Trait1Or() ;
        object->addTrait(t1) ;
        Trait2Or* t2 = new Trait2Or() ;
        object->addTrait(t2) ;

        DeducedTrait2* dtor = object->getTrait<DeducedTrait2>() ;

        CPPUNIT_ASSERT(dtor->getDependencies().find(t1) != dtor->getDependencies().end()) ;
        CPPUNIT_ASSERT(dtor->getDependencies().find(t2) != dtor->getDependencies().end()) ;

        object->destroyTrait(t2) ;

        CPPUNIT_ASSERT(dtor->getDependencies().find(t1) != dtor->getDependencies().end()) ;
        CPPUNIT_ASSERT(dtor->getDependencies().find(t2) == dtor->getDependencies().end()) ;
      }

      namespace TestTraitLocal1
      {
        class ROr : public Relation
        {};

        class OrFrom : public Trait
        {};

        class OrTo : public Trait
        {};

        class DeducedOr : public DeducedRelation
        {};

        DeclareDeducedRelation(DeducedOr,ROr,Or(IsFrom(HasTrait(OrFrom)),IsTo(HasTrait(OrTo)))) ;

      }

      using namespace TestTraitLocal1 ;

      void TestTrait::addNewTraitOnOrRelationChangeDepedencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination = model->createObject() ;

        OrFrom* from = new OrFrom() ;
        source->addTrait(from) ;

        Link<ROr>(source,destination) ;

        Relation* deduced(Relation::getRelation(getClassTypeIdentifier(DeducedOr),source,destination)) ;

        CPPUNIT_ASSERT(from->getDependentNotifiables().find(deduced) != from->getDependentNotifiables().end()) ;

        OrTo* to = new OrTo() ;
        destination->addTrait(to) ;

        CPPUNIT_ASSERT(to->getDependentNotifiables().find(deduced) != to->getDependentNotifiables().end()) ;
      }

      void TestTrait::removeTraitOnOrRelationChangeDepedencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination = model->createObject() ;

        OrFrom* from = new OrFrom() ;
        source->addTrait(from) ;
        OrTo* to = new OrTo() ;
        destination->addTrait(to) ;

        Link<ROr>(source,destination) ;

        Relation* deduced(Relation::getRelation(getClassTypeIdentifier(DeducedOr),source,destination)) ;

        CPPUNIT_ASSERT(deduced->getDependencies().find(from) != deduced->getDependencies().end()) ;
        CPPUNIT_ASSERT(deduced->getDependencies().find(to) != deduced->getDependencies().end()) ;

        destination->destroyTrait(to) ;

        CPPUNIT_ASSERT(deduced->getDependencies().find(from) != deduced->getDependencies().end()) ;
        CPPUNIT_ASSERT(deduced->getDependencies().find(to) == deduced->getDependencies().end()) ;
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

      namespace TestTraitLocal2
      {
        class T1 : public Trait
        {};

        class HasT1 : public DeducedTrait
        {};

        DeclareDeducedTrait(HasT1,HasTrait(T1)) ;

      }

      using namespace TestTraitLocal2 ;

      void TestTrait::hasTraitFormulaUpdaterTraits()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* object = model->createObject() ;
        object->addTrait(new T1()) ;

        Formula* formula = ((DeducedTrait*)object->getTrait<HasT1>())->getFormula() ;

        std::set<Notifiable*> updater_traits(formula->getUpdaterNotifiables(object)) ;

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

        std::set<Notifiable*> updater_traits(formula->getUpdaterNotifiables(object)) ;

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
          std::set<Notifiable*> updater_traits(formula->getUpdaterNotifiables(object)) ;
          CPPUNIT_ASSERT_EQUAL((unsigned int)1,updater_traits.size()) ;
          CPPUNIT_ASSERT(updater_traits.find(object->getTrait<Parent>()) != updater_traits.end()) ;
        }
        {
          std::set<Notifiable*> updater_traits(formula->getUpdaterNotifiables(object2)) ;
          CPPUNIT_ASSERT_EQUAL((unsigned int)1,updater_traits.size()) ;
          CPPUNIT_ASSERT(updater_traits.find(object->getTrait<Parent>()) != updater_traits.end()) ;
        }
      }

      namespace TestTraitLocal3
      {
        class Ancestor : public Trait
        {};

        class WithAncestor : public DeducedTrait
        {};

        DeclareDeducedTrait(WithAncestor,HasAncestor(HasTrait(Ancestor))) ;
      }

      using namespace TestTraitLocal3 ;

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

      namespace TestTraitLocal4
      {
        class Positioned : public Trait
        {};

        class RecursivelyPositioned : public DeducedTrait
        {};

        DeclareDeducedTrait(RecursivelyPositioned,
                            Or(HasTrait(Positioned),
                               HasAncestor(HasTrait(RecursivelyPositioned)))) ;
      }

      using namespace TestTraitLocal4 ;

      void TestTrait::destroyObjectOnRecusiveFormula()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;
        root->addTrait(new Positioned()) ;

        Object* child = root->createObject() ;
        child->addTrait(new Positioned()) ;

        child->destroyTrait(child->getTrait<Positioned>()) ;

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

      void TestTrait::changeParentChangeHasChildDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Child* c = new Child() ;
        child->addTrait(c) ;

        Object* other_root = model->createObject() ;

        HasChildTrait1* dt_root = root->getTrait<HasChildTrait1>() ;
        CPPUNIT_ASSERT(dt_root) ;

        CPPUNIT_ASSERT(c->getDependentNotifiables().find(dt_root) != c->getDependentNotifiables().end()) ;

        child->changeParent(other_root) ;

        HasChildTrait1* dt_other_root = other_root->getTrait<HasChildTrait1>() ;
        CPPUNIT_ASSERT(dt_other_root) ;

        CPPUNIT_ASSERT(c->getDependentNotifiables().find(dt_root) == c->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(c->getDependentNotifiables().find(dt_other_root) != c->getDependentNotifiables().end()) ;
      }

      void TestTrait::recursiveChangeParentChangeHasChildDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Object* grand_child = child->createObject() ;
        Child* gc = new Child() ;
        grand_child->addTrait(gc) ;

        Object* other_root = model->createObject() ;

        HasChildTrait1* dt_root = root->getTrait<HasChildTrait1>() ;
        CPPUNIT_ASSERT(dt_root) ;

        CPPUNIT_ASSERT(gc->getDependentNotifiables().find(dt_root) != gc->getDependentNotifiables().end()) ;

        child->changeParent(other_root) ;

        HasChildTrait1* dt_other_root = other_root->getTrait<HasChildTrait1>() ;
        CPPUNIT_ASSERT(dt_other_root) ;

        CPPUNIT_ASSERT(gc->getDependentNotifiables().find(dt_root) == gc->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(gc->getDependentNotifiables().find(dt_other_root) != gc->getDependentNotifiables().end()) ;
      }

      void TestTrait::changeParentToAnAlreadyValidParentChangeHasChildDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root1 = model->createObject() ;

        Object* child1 = root1->createObject() ;
        Child* c1 = new Child() ;
        child1->addTrait(c1) ;

        Object* child2 = root1->createObject() ;
        Child* c2 = new Child() ;
        child2->addTrait(c2) ;

        Object* root2 = model->createObject() ;

        Object* child3 = root2->createObject() ;
        Child* c3 = new Child() ;
        child3->addTrait(c3) ;

        child1->changeParent(root2) ;

        HasChildTrait1* dt_root1 = root1->getTrait<HasChildTrait1>() ;
        CPPUNIT_ASSERT(dt_root1) ;

        HasChildTrait1* dt_root2 = root2->getTrait<HasChildTrait1>() ;
        CPPUNIT_ASSERT(dt_root2) ;

        CPPUNIT_ASSERT(c1->getDependentNotifiables().find(dt_root1) == c1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(c1->getDependentNotifiables().find(dt_root2) != c1->getDependentNotifiables().end()) ;
      }


      namespace TestTraitLocal5
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

      using namespace TestTraitLocal5 ;

      void TestTrait::destroyChildObjectShouldNotCrash()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Object* grand_child = child->createObject() ;
        grand_child->addTrait(new Active()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(DisplayedSolid)) ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,root->getNumberOfTrueChildFormulae(formula)) ;

        grand_child->destroyObject() ;
      }

      namespace TestTraitLocal6
      {
        class R : public Relation
        {};

        class TR : public Trait
        {};

        class LinkedToTR : public DeducedTrait
        {};

        DeclareDeducedTrait(LinkedToTR,IsRelated(R,HasTrait(TR))) ;
      }

      using namespace TestTraitLocal6 ;

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

      namespace TestTraitLocal7
      {
        class TRi : public Trait
        {};

        class LinkedToTRi : public DeducedTrait
        {};

        DeclareDeducedTrait(LinkedToTRi,IsRelated(Inverse<R>,HasTrait(TRi))) ;
      }

      using namespace TestTraitLocal7 ;

      void TestTrait::isInverseRelatedHasDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination = model->createObject() ;

        Trait* tr = destination->addTrait(new TRi()) ;

        Link<Inverse<R> >(source,destination) ;

        DeducedTrait* dt = source->getTrait<LinkedToTRi>() ;

        CPPUNIT_ASSERT(tr->getDependentNotifiables().find(dt) != tr->getDependentNotifiables().end()) ;
      }

      void TestTrait::addInverseRelatedChangeDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination1 = model->createObject() ;

        Trait* tr1 = destination1->addTrait(new TRi()) ;

        Link<Inverse<R> >(source,destination1) ;

        Object* destination2 = model->createObject() ;
        Trait* tr2 = destination2->addTrait(new TRi()) ;

        Link<Inverse<R> >(source,destination2) ;

        DeducedTrait* dt = source->getTrait<LinkedToTRi>() ;

        CPPUNIT_ASSERT(tr1->getDependentNotifiables().find(dt) != tr1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(tr2->getDependentNotifiables().find(dt) != tr2->getDependentNotifiables().end()) ;
      }

      void TestTrait::removeInverseRelatedChangeDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination1 = model->createObject() ;

        Trait* tr1 = destination1->addTrait(new TRi()) ;

        Link<Inverse<R> >(source,destination1) ;

        Object* destination2 = model->createObject() ;
        Trait* tr2 = destination2->addTrait(new TRi()) ;

        Link<Inverse<R> >(source,destination2) ;

        UnLink<Inverse<R> >(source,destination1) ;

        DeducedTrait* dt = source->getTrait<LinkedToTRi>() ;

        CPPUNIT_ASSERT(tr1->getDependentNotifiables().find(dt) == tr1->getDependentNotifiables().end()) ;
        CPPUNIT_ASSERT(tr2->getDependentNotifiables().find(dt) != tr2->getDependentNotifiables().end()) ;
      }

      namespace TestTraitLocal8
      {
        class ROnly : public Relation
        {};

        class TROnly : public Trait
        {};

        class LinkedToTROnly : public DeducedTrait
        {};

        DeclareDeducedTrait(LinkedToTROnly,IsOnlyRelated(ROnly,HasTrait(TROnly))) ;
      }

      using namespace TestTraitLocal8 ;
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

      namespace TestTraitLocal9
      {
        class R2 : public Relation
        {};

        class From : public Trait
        {};

        class R2From : public DeducedRelation
        {};

        DeclareDeducedRelation(R2From,R2,IsFrom(HasTrait(From))) ;
      }

      using namespace TestTraitLocal9 ;

      void TestTrait::isFromHasDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination = model->createObject() ;

        Trait* from = source->addTrait(new From()) ;

        Link<R2>(source,destination) ;
        Relation* deduced(Relation::getRelation(getClassTypeIdentifier(R2From),source,destination)) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,from->getDependentNotifiables().size()) ;
        CPPUNIT_ASSERT(from->getDependentNotifiables().find(deduced) != from->getDependentNotifiables().end()) ;
      }

      void TestTrait::addRelationChangeIsFromDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination1 = model->createObject() ;
        Object* destination2 = model->createObject() ;
        Trait* from = source->addTrait(new From()) ;

        Link<R2>(source,destination1) ;

        Relation* deduced1(Relation::getRelation(getClassTypeIdentifier(R2From),source,destination1)) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,from->getDependentNotifiables().size()) ;
        CPPUNIT_ASSERT(from->getDependentNotifiables().find(deduced1) != from->getDependentNotifiables().end()) ;

        Link<R2>(source,destination2) ;

        Relation* deduced2(Relation::getRelation(getClassTypeIdentifier(R2From),source,destination2)) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)2,from->getDependentNotifiables().size()) ;
        CPPUNIT_ASSERT(from->getDependentNotifiables().find(deduced2) != from->getDependentNotifiables().end()) ;
      }

      void TestTrait::removeRelationChangeIsFromDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination1 = model->createObject() ;
        Object* destination2 = model->createObject() ;
        Trait* from = source->addTrait(new From()) ;

        Link<R2>(source,destination1) ;
        Link<R2>(source,destination2) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,from->getDependentNotifiables().size()) ;

        UnLink<R2>(source,destination1) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,from->getDependentNotifiables().size()) ;

        UnLink<R2>(source,destination2) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)0,from->getDependentNotifiables().size()) ;
      }

      namespace TestTraitLocal10
      {
        class R3 : public Relation
        {};

        class To : public Trait
        {};

        class R3To : public DeducedRelation
        {};

        DeclareDeducedRelation(R3To,R3,IsTo(HasTrait(To))) ;
      }

      using namespace TestTraitLocal10 ;

      void TestTrait::isToHasDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination = model->createObject() ;

        Trait* to = destination->addTrait(new To()) ;

        Link<R3>(source,destination) ;

        Relation* deduced(Relation::getRelation(getClassTypeIdentifier(R3To),source,destination)) ;
        CPPUNIT_ASSERT(Relation::areLinked<R3To>(source,destination)) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,to->getDependentNotifiables().size()) ;
        CPPUNIT_ASSERT(to->getDependentNotifiables().find(deduced) != to->getDependentNotifiables().end()) ;
      }

      void TestTrait::addRelationChangeIsToDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source1 = model->createObject() ;
        Object* source2 = model->createObject() ;
        Object* destination = model->createObject() ;
        Trait* to = destination->addTrait(new To()) ;

        Link<R3>(source1,destination) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,to->getDependentNotifiables().size()) ;

        Link<R3>(source2,destination) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,to->getDependentNotifiables().size()) ;
      }

      void TestTrait::removeRelationChangeIsToDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source1 = model->createObject() ;
        Object* source2 = model->createObject() ;
        Object* destination = model->createObject() ;
        Trait* to = destination->addTrait(new To()) ;

        Link<R3>(source1,destination) ;
        Link<R3>(source2,destination) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)2,to->getDependentNotifiables().size()) ;

        UnLink<R3>(source1,destination) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,to->getDependentNotifiables().size()) ;

        UnLink<R3>(source2,destination) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)0,to->getDependentNotifiables().size()) ;
      }

      void TestTrait::isToHasOnlyDestinationDependencies()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* source = model->createObject() ;
        Object* destination = model->createObject() ;

        Trait* to = destination->addTrait(new To()) ;
        Trait* to_source = source->addTrait(new To()) ;

        Link<R3>(source,destination) ;

        CPPUNIT_ASSERT(Relation::areLinked<R3To>(source,destination)) ;
        Relation* deduced(Relation::getRelation(getClassTypeIdentifier(R3To),source,destination)) ;
        CPPUNIT_ASSERT(deduced->getDependencies().find(to) != deduced->getDependencies().end()) ;
        CPPUNIT_ASSERT(deduced->getDependencies().find(to_source) == deduced->getDependencies().end()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,deduced->getDependencies().size()) ;
      }

      namespace TestTraitLocal11
      {
        class Starter : public Trait
        {};

        class Reflexive : public DeducedTrait
        {};

        DeclareDeducedTrait(Reflexive,
                            Or(HasTrait(Starter),
                               HasParent(HasTrait(Reflexive)))) ;
      }

      using namespace TestTraitLocal11 ;

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

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root->getNumberOfTrueChildFormulae(formula)) ;

        child->addTrait(new Ancestor()) ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;

        root->addTrait(new Ancestor()) ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,grand_child->getNumberOfTrueChildFormulae(formula)) ;
      }

      void TestTrait::addingParentChangeNumberOfTrueChildFormulae()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(HasParentTrait1)) ;

        Object* root = model->createObject() ;
        Object* child = root->createObject() ;
        Object* grand_child = child->createObject() ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root->getNumberOfTrueChildFormulae(formula)) ;

        child->addTrait(new Parent()) ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;

        root->addTrait(new Parent()) ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,root->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,grand_child->getNumberOfTrueChildFormulae(formula)) ;
      }

      void TestTrait::addingChildChangeNumberOfTrueChildFormulae()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Formula* formula = DeducedTrait::getFormula(getClassTypeIdentifier(HasChildTrait1)) ;
        {
          Object* root = model->createObject() ;
          Object* child = root->createObject() ;
          Object* grand_child = child->createObject() ;

          CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root->getNumberOfTrueChildFormulae(formula)) ;

          child->addTrait(new Child()) ;

          CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,root->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,child->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,grand_child->getNumberOfTrueChildFormulae(formula)) ;

          root->addTrait(new Child()) ;

          CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,root->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,child->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,grand_child->getNumberOfTrueChildFormulae(formula)) ;
        }
        {
          Object* root = model->createObject() ;
          Object* child = root->createObject() ;
          Object* grand_child = child->createObject() ;

          CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root->getNumberOfTrueChildFormulae(formula)) ;

          child->addTrait(new Child()) ;

          CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,root->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,child->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,grand_child->getNumberOfTrueChildFormulae(formula)) ;

          grand_child->addTrait(new Child()) ;

          CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,root->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,child->getNumberOfTrueChildFormulae(formula)) ;
          CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;
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

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root2->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,grand_child->getNumberOfTrueChildFormulae(formula)) ;

        child->changeParent(root2) ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root2->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;
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

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root2->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,grand_child->getNumberOfTrueChildFormulae(formula)) ;

        // induces a memory lost of WithAncestor created on child
        child->changeParent(root2) ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root2->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,child->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,grand_child->getNumberOfTrueChildFormulae(formula)) ;
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

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root2->getNumberOfTrueChildFormulae(formula)) ;

        child->changeParent(root2) ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)0,root1->getNumberOfTrueChildFormulae(formula)) ;
        CPPUNIT_ASSERT_EQUAL((Implementation::Number)2,root2->getNumberOfTrueChildFormulae(formula)) ;
      }

      namespace Complex
      {
        class R1 : public Relation
        {};
        class T1 : public Trait
        {};
        class T2 : public Trait
        {};

        class DT1 : public DeducedTrait
        {};

        DeclareDeducedTrait(DT1,IsRelated(Inverse<R1>,And(HasTrait(T1),IsRelated(Inverse<R1>,HasTrait(T2))))) ;

      }

      void TestTrait::severalLinkToTheSameShouldNotIncreaseTrueChildOfIsRelated()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* o1 = model->createObject() ;

        o1->addTrait(new Complex::T1()) ;
        o1->addTrait(new Complex::T2()) ;

        Link<Complex::R1>(o1,o1) ;
        Link<Complex::R1>(o1,o1) ;

        CPPUNIT_ASSERT(o1->getTrait<Complex::DT1>()) ;

        Formula* formula = o1->getTrait<Complex::DT1>()->getFormula() ;

        CPPUNIT_ASSERT_EQUAL((Implementation::Number)1,o1->getNumberOfTrueChildFormulae(formula)) ;
      }

      void TestTrait::removingRelationShouldNotCleanOtherRelationValidities()
      {
        std::auto_ptr<Model> model(new Model()) ;

        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Trait* t1 = o1->addTrait(new OrFrom()) ;

        Link<ROr>(o1,o2) ;

        CPPUNIT_ASSERT(Relation::areLinked<DeducedOr>(o1,o2)) ;

        Link<R2>(o1,o2) ;
        UnLink<R2>(o1,o2) ;

        o1->destroyTrait(t1) ;

        CPPUNIT_ASSERT(!Relation::areLinked<DeducedOr>(o1,o2)) ;
      }

    }
  }
}
