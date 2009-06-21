/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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

#include <kernel/log.h>
#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/trait_view.h>
#include <kernel/view_point.h>
#include <kernel/deduced_trait.h>

#include <kernel/test/test_deduced_trait.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Test::TestDeducedTrait) ;

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      /// local classes
      namespace
      {

        TypeIdentifier last_modified_trait ;

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

        class DeducedTrait2 : public Kernel::DeducedTrait
        {};

        /// A deduced trait.
        DeclareDeducedTrait(DeducedTrait2,
                            Or(HasTrait(Trait1),
                               HasTrait(Trait2))) ;

        class DeducedTrait3 : public Kernel::DeducedTrait
        {};

        /// A deduced trait.
        DeclareDeducedTrait(DeducedTrait3,
                            Not(HasTrait(Trait1))) ;

        class DeducedTrait4 : public Kernel::DeducedTrait
        {};

        /// formula is ((T1^T2)U~(T3^T1))
        DeclareDeducedTrait(DeducedTrait4,
                            Or(
                              Not(
                                And(HasTrait(Trait1),
                                    HasTrait(Trait3))),
                              And(HasTrait(Trait1),
                                  HasTrait(Trait2)))) ;

        class DeducedTrait5 : public Kernel::DeducedTrait
        {};

        DeclareDeducedTrait(DeducedTrait5,
                            Not(HasTrait(Trait1))) ;

        class DeducedTrait6 : public Kernel::DeducedTrait
        {};

        DeclareDeducedTrait(DeducedTrait6,
                            And(HasTrait(Trait2),
                                HasTrait(Trait3),
                                HasTrait(DeducedTrait5))) ;

        class TestViewPoint : public ViewPoint
        {
        public:

          TestViewPoint(Model* i_model)
          : ViewPoint(i_model)
          {}

        protected:

          virtual void onInit()
          {
          }

          virtual void onClose()
          {
          }

        };

        class DeducedTrait7 : public Kernel::DeducedTrait
        {};

        DeclareDeducedTrait(DeducedTrait7,
                            And(HasTrait(Trait1),
                                HasTrait(Trait2))) ;


        class View7 : public TraitView<DeducedTrait7,TestViewPoint>
        {
        public:

          View7(DeducedTrait7* i_trait, TestViewPoint* i_viewpoint)
          : TraitView<DeducedTrait7,TestViewPoint>(i_trait,i_viewpoint),
            m_update_number(0)
          {}

          int m_update_number ;

        protected:

          virtual void onUpdate()
          {
            last_modified_trait = getTrait()->getLatestUpdatedTrait() ;
            ++ m_update_number ;
          }
        };

        RegisterView(View7,DeducedTrait7,TestViewPoint) ;

      }

      void TestDeducedTrait::testAnd()
      {
        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testAnd entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* object = model->createObject() ;

        object->addTrait(new Trait1()) ;
        /// Check that object has no DeducedTrait1
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait1>()) ;

        object->addTrait(new Trait2()) ;
        /// Check that object has no DeducedTrait1
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait1>()) ;

        object->addTrait(new Trait3()) ;
        /// Check that object has automatically gained DeducedTrait1
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait1>()) ;

        object->destroyTrait(object->getTrait<Trait2>()) ;
        /// Check that object has lost DeducedTrait1
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait1>()) ;

        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testAnd leaving") ;
      }

      void TestDeducedTrait::testAndOnSubTrait()
      {
        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testAndOnSubTrait entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* object = model->createObject() ;

        object->addTrait(new SubTrait()) ;
        /// Check that object has no DeducedTrait1
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait1>()) ;

        object->addTrait(new Trait2()) ;
        /// Check that object has no DeducedTrait1
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait1>()) ;

        object->addTrait(new Trait3()) ;
        /// Check that object has automatically gained DeducedTrait1
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait1>()) ;

        object->destroyTrait(object->getTrait<Trait2>()) ;
        /// Check that object has lost DeducedTrait1
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait1>()) ;

        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testAnd leaving") ;
      }

      void TestDeducedTrait::testOr()
      {
        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testOr entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* object = model->createObject() ;

        /// Check that object has no DeducedTrait2
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait2>()) ;

        object->addTrait(new Trait1()) ;
        /// Check that object has automatically gained DeducedTrait2
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait2>()) ;


        object->addTrait(new Trait2()) ;
        /// Check that object still has DeducedTrait2
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait2>()) ;

        object->destroyTrait(object->getTrait<Trait2>()) ;
        /// Check that object still has DeducedTrait2
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait2>()) ;

        object->destroyTrait(object->getTrait<Trait1>()) ;
        /// Check that object has lost DeducedTrait2
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait2>()) ;

        object->addTrait(new Trait3()) ;
        /// Check that situation has not changed
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait2>()) ;


        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testOr leaving") ;
      }

      void TestDeducedTrait::testNot()
      {
        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testNot entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* object = model->createObject() ;

        /// Check that object has DeducedTrait3
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait3>()) ;

        object->addTrait(new Trait1()) ;
        /// Check that object has automatically lost DeducedTrait3
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait3>()) ;

        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testNot leaving") ;
      }

      /// formula is ((T1^T2)U~(T3^T1))
      void TestDeducedTrait::testComposite()
      {
        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testComposite entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* object = model->createObject() ;

        /// Check that object has DeducedTrait4
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait4>()) ;

        object->addTrait(new Trait1()) ;
        object->addTrait(new Trait3()) ;
        /// Check that object has automatically lost DeducedTrait4
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait4>()) ;

        object->addTrait(new Trait2()) ;
        /// Check that object has DeducedTrait4
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait4>()) ;

        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testComposite Leaving") ;
      }

      /// DeducedTrait5 <=> ~T1, DeducedTrait6 <=> T2^T3^DeducedTrait5
      void TestDeducedTrait::testCompositeWithDeduced()
      {
        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testCompositeWithDeduced entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;


        //// fill the model
        Object* object = model->createObject() ;

        /// Check that object has DeducedTrait5 but not DeducedTrait6
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait5>()) ;
        CPPUNIT_ASSERT(!object->getTrait<DeducedTrait6>()) ;

        object->addTrait(new Trait3()) ;
        /// Check that object has DeducedTrait5 but not DeducedTrait6
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait5>()) ;
        CPPUNIT_ASSERT(!object->getTrait<DeducedTrait6>()) ;

        object->addTrait(new Trait2()) ;
        /// Check that object has DeducedTrait5 and DeducedTrait6
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait5>()) ;
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait6>()) ;

        object->addTrait(new Trait1()) ;
        /// Check that object has lost both DeducedTrait5 and DeducedTrait6
        CPPUNIT_ASSERT(!object->getTrait<DeducedTrait5>()) ;
        CPPUNIT_ASSERT(!object->getTrait<DeducedTrait6>()) ;

      }

      void TestDeducedTrait::testDeducedTraitViews()
      {
        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testDeducedTraitViews entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        /// create a viewpoint
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;

        /// init the viewpoint
        viewpoint->init() ;

        //// fill the model
        Object* object = model->createObject() ;

        object->addTrait(new Trait1()) ;
        object->addTrait(new Trait2()) ;

        CPPUNIT_ASSERT(object->getView<View7>(viewpoint.get())) ;
        CPPUNIT_ASSERT(object->getView<View7>(viewpoint.get())->m_update_number == 0) ;

        last_modified_trait = TypeIdentifier() ;
        object->getTrait<Trait1>()->change(1) ;
        CPPUNIT_ASSERT(object->getView<View7>(viewpoint.get())->m_update_number == 1) ;
        CPPUNIT_ASSERT(last_modified_trait.className() == "Trait1") ;

        last_modified_trait = TypeIdentifier() ;
        object->getTrait<Trait2>()->change(1) ;
        CPPUNIT_ASSERT(object->getView<View7>(viewpoint.get())->m_update_number == 2) ;
        CPPUNIT_ASSERT(last_modified_trait.className() == "Trait2") ;

        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::testDeducedTraitViews leaving") ;

      }

      void TestDeducedTrait::notifyOnNotAssignedTrait()
      {
        Trait1* trait = new Trait1() ;
        trait->change(10) ;
      }

      namespace
      {

        class Trait11 : public Trait
        {
        public:

          Trait11()
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

        class Trait12 : public Trait
        {
        public:

          Trait12()
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

        class Trait13 : public Trait
        {
        public:

          Trait13()
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

        class Trait14 : public Trait
        {
        public:

          Trait14()
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

        class Trait15 : public Trait
        {
        public:

          Trait15()
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

        class DeducedTrait11 : public Kernel::DeducedTrait
        {};
        DeclareDeducedTrait(DeducedTrait11,
                            And(HasTrait(Trait11),
                                HasTrait(Trait12),
                                HasTrait(Trait13))) ;

        class DeducedTrait12 : public Kernel::DeducedTrait
        {};

        /// A deduced trait.
        DeclareDeducedTrait(DeducedTrait12,
                            And(HasTrait(Trait11),
                                HasTrait(Trait12))) ;

        class ViewPoint11 : public ViewPoint
        {
        public:

          ViewPoint11(Model* model)
          : ViewPoint(model)
          {}

        };

        class View11 : public TraitView<DeducedTrait11,ViewPoint11>
        {
        public:
          View11(DeducedTrait11* i_trait, ViewPoint11* i_viewpoint)
          : TraitView<DeducedTrait11,ViewPoint11>(i_trait,i_viewpoint)
          {}

          TypeIdentifier m_latest_updated_trait ;

        protected:

          virtual void onUpdate()
          {
            m_latest_updated_trait = getTrait()->getLatestUpdatedTrait() ;
            Trait15* trait = getObject()->getTrait<Trait15>() ;
            if (trait)
              trait->change(2) ;
            else
              std::cout << "ho no !!" ;
          }
        };

        RegisterView(View11,DeducedTrait11,ViewPoint11) ;

        class View12 : public TraitView<DeducedTrait12,ViewPoint11>
        {
        public:

          View12(DeducedTrait12* i_trait, ViewPoint11* i_viewpoint)
          : TraitView<DeducedTrait12,ViewPoint11>(i_trait,i_viewpoint)
          {}

          TypeIdentifier m_latest_updated_trait ;

        protected:

          virtual void onUpdate()
          {
            m_latest_updated_trait = getTrait()->getLatestUpdatedTrait() ;
            Trait14* trait = getObject()->getTrait<Trait14>() ;
            if (trait)
              trait->change(2) ;
            else
              std::cout << "ho no !!" ;
          }
        };

        RegisterView(View12,DeducedTrait12,ViewPoint11) ;

      }

      /*
        a little complicated :

        we update first trait --> trigger onUpdate on two distinct views
        each view update modify another trait

        but in each onUpdate view, the latest updatedTrait should be the inital
        one

      */
      void TestDeducedTrait::testGetLatestUpdatedTrait()
      {
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::testGetLatestUpdatedTrait")) ;

        Object* object = model->createObject() ;
        object->addTrait(new Trait11()) ;
        object->addTrait(new Trait12()) ;
        object->addTrait(new Trait13()) ;
        object->addTrait(new Trait14()) ;
        object->addTrait(new Trait15()) ;

        std::auto_ptr<ViewPoint11> viewpoint(new ViewPoint11(model.get())) ;
        viewpoint->init() ;

        object->getTrait<Trait11>()->change(2) ;
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait11>()->getView<View11>(viewpoint.get())->m_latest_updated_trait == getClassTypeIdentifier(Trait11)) ;
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait12>()->getView<View12>(viewpoint.get())->m_latest_updated_trait == getClassTypeIdentifier(Trait11)) ;

      }

      namespace
      {

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

        class ViewHasParentTrait1 : public TraitView<HasParentTrait1,TestViewPoint>
        {
        public:

          ViewHasParentTrait1(HasParentTrait1* o,TestViewPoint* v)
          : TraitView<HasParentTrait1,TestViewPoint>(o,v),
            m_update_number(0)
          {}

          int getUpdateNumber() const
          {
            return m_update_number ;
          }

        protected:

          void onUpdate()
          {
            ++m_update_number ;
          }

          int m_update_number ;
        };

        RegisterView(ViewHasParentTrait1,HasParentTrait1,TestViewPoint) ;

        class ParentAndTrait1 : public DeducedTrait
        {};

        DeclareDeducedTrait(ParentAndTrait1,
                            And(HasParent(Parent),HasTrait(Trait1))) ;

        class ViewHasParentAndTrait1 : public TraitView<ParentAndTrait1,TestViewPoint>
        {
        public:

          ViewHasParentAndTrait1(ParentAndTrait1* o,TestViewPoint* v)
          : TraitView<ParentAndTrait1,TestViewPoint>(o,v),
            m_update_number(0)
          {}

          int getUpdateNumber() const
          {
            return m_update_number ;
          }

        protected:

          void onUpdate()
          {
            ++m_update_number ;
          }

          int m_update_number ;
        };

        RegisterView(ViewHasParentAndTrait1,ParentAndTrait1,TestViewPoint) ;

      }

      void TestDeducedTrait::addParentTrait()
      {
        InternalMessage("Kernel","TestDeducedTrait::addParentTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::addParentTrait")) ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;

        object->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;
      }

      void TestDeducedTrait::addSubParentTrait()
      {
        InternalMessage("Kernel","TestDeducedTrait::addSubParentTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::addSubParentTrait")) ;
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        viewpoint->init() ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;

        object->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;

        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())) ;
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 0) ;

        child->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;

        // view has been updated because Parent parent has changed
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 1) ;
      }

      void TestDeducedTrait::removeParentTrait()
      {
        InternalMessage("Kernel","TestDeducedTrait::removeParentTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::removeParentTrait")) ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;

        object->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;

        object->destroyTrait(object->getTrait<Parent>()) ;

        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;
      }

      void TestDeducedTrait::updateAncestorTrait()
      {
        InternalMessage("Kernel","TestDeducedTrait::updateAncestorTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::updateAncestorTrait")) ;
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        viewpoint->init() ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;
        Object* grand_child = child->createObject() ;

        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! grand_child->getTrait<HasParentTrait1>()) ;

        object->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(grand_child->getTrait<HasParentTrait1>()) ;

        CPPUNIT_ASSERT(grand_child->getTrait<HasParentTrait1>()
                                  ->getView<ViewHasParentTrait1>(viewpoint.get())) ;
        CPPUNIT_ASSERT(grand_child->getTrait<HasParentTrait1>()
                                  ->getView<ViewHasParentTrait1>(viewpoint.get())
                                  ->getUpdateNumber() == 0) ;

        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 0) ;

        child->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;

        // view has been updated because Parent parent has changed
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 1) ;

        // view has been updated because Parent parent has changed
        CPPUNIT_ASSERT(grand_child->getTrait<HasParentTrait1>()
                                  ->getView<ViewHasParentTrait1>(viewpoint.get())
                                  ->getUpdateNumber() == 1) ;

        object->getTrait<Parent>()->modify() ;

        // view has not been updated because its too up
        CPPUNIT_ASSERT(grand_child->getTrait<HasParentTrait1>()
                                  ->getView<ViewHasParentTrait1>(viewpoint.get())
                                  ->getUpdateNumber() == 1) ;

        // view has not been updated because its too up
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 1) ;

        child->getTrait<Parent>()->modify() ;

        // view has been updated because parent has
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 2) ;

        // view has been updated because parent has
        CPPUNIT_ASSERT(grand_child->getTrait<HasParentTrait1>()
                                  ->getView<ViewHasParentTrait1>(viewpoint.get())
                                  ->getUpdateNumber() == 2) ;


      }

      void TestDeducedTrait::updateParentTrait()
      {
        InternalMessage("Kernel","TestDeducedTrait::updateAncestorTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::updateAncestorTrait")) ;
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        viewpoint->init() ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;

        object->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;

        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 0) ;

        object->getTrait<Parent>()->modify() ;

        // view has been updated
        CPPUNIT_ASSERT(object->getTrait<HasParentTrait1>()
                             ->getView<ViewHasParentTrait1>(viewpoint.get())
                             ->getUpdateNumber() == 1) ;

        // view has been updated
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 1) ;

      }

      void TestDeducedTrait::removeSubAncestorTrait()
      {
        InternalMessage("Kernel","TestDeducedTrait::addSubParentTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::addSubParentTrait")) ;
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        viewpoint->init() ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;
        Object* grand_child = child->createObject() ;

        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;

        object->addTrait(new Parent()) ;
        child->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(grand_child->getTrait<HasParentTrait1>()
                                  ->getView<ViewHasParentTrait1>(viewpoint.get())
                                  ->getUpdateNumber() == 1) ;

        child->destroyTrait(child->getTrait<Parent>()) ;

        CPPUNIT_ASSERT(grand_child->getTrait<HasParentTrait1>()
                                  ->getView<ViewHasParentTrait1>(viewpoint.get())
                                  ->getUpdateNumber() == 2) ;

      }

      void TestDeducedTrait::addParentTraitOnCompositeFormula()
      {
        InternalMessage("Kernel","TestDeducedTrait::addParentTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::addParentTrait")) ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        CPPUNIT_ASSERT(! child->getTrait<ParentAndTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<ParentAndTrait1>()) ;

        object->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(! child->getTrait<ParentAndTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<ParentAndTrait1>()) ;

        child->addTrait(new Trait1()) ;

        CPPUNIT_ASSERT(! object->getTrait<ParentAndTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<ParentAndTrait1>()) ;

      }

      void TestDeducedTrait::addSubParentTraitOnCompositeFormula()
      {
        InternalMessage("Kernel","TestDeducedTrait::addSubParentTraitOnCompositeFormula entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::addSubParentTraitOnCompositeFormula")) ;
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        viewpoint->init() ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        CPPUNIT_ASSERT(! child->getTrait<ParentAndTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<ParentAndTrait1>()) ;

        object->addTrait(new Parent()) ;
        child->addTrait(new Trait1()) ;

        CPPUNIT_ASSERT(child->getTrait<ParentAndTrait1>()
                            ->getView<ViewHasParentAndTrait1>(viewpoint.get())) ;
        CPPUNIT_ASSERT(child->getTrait<ParentAndTrait1>()
                            ->getView<ViewHasParentAndTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 0) ;

        child->addTrait(new Parent()) ;

        // the HasParent has changed for child : view should have been updated
        CPPUNIT_ASSERT(child->getTrait<ParentAndTrait1>()
                            ->getView<ViewHasParentAndTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 1) ;

      }

      void TestDeducedTrait::addTrueChild()
      {
        InternalMessage("Kernel","TestDeducedTrait::addTrueChild entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::addTrueChild")) ;

        Object* object = model->createObject() ;
        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;
        object->addTrait(new Parent()) ;

        // create a child after...
        Object* child = object->createObject() ;
        CPPUNIT_ASSERT(object->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;
      }

      void TestDeducedTrait::changeParentHasParentBecomeTrue()
      {
        InternalMessage("Kernel","TestDeducedTrait::changeParentHasParentBecomeTrue entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::changeParentHasParentBecomeTrue")) ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        Object* object2 = model->createObject() ;
        object2->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;

        child->changeParent(object2) ;

        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;
      }

      void TestDeducedTrait::changeAncestorHasParentBecomeTrue()
      {
        InternalMessage("Kernel","TestDeducedTrait::changeAncestorHasParentBecomeTrue entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::changeAncestorHasParentBecomeTrue")) ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;
        Object* grand_child = child->createObject() ;

        Object* object2 = model->createObject() ;
        object2->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasParentTrait1>()) ;

        child->changeParent(object2) ;

        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;
        CPPUNIT_ASSERT(grand_child->getTrait<HasParentTrait1>()) ;

      }

      void TestDeducedTrait::changeParentHasParentBecomeFalse()
      {
        InternalMessage("Kernel","TestDeducedTrait::changeParentHasParentBecomeFalse entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::changeParentHasParentBecomeFalse")) ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        Object* object2 = model->createObject() ;
        object->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;

        child->changeParent(object2) ;

        CPPUNIT_ASSERT(! child->getTrait<HasParentTrait1>()) ;
      }

      void TestDeducedTrait::changeParentHasParentUpdated()
      {
        InternalMessage("Kernel","TestDeducedTrait::changeParentHasParentUpdated entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::changeParentHasParentUpdated")) ;
        std::auto_ptr<TestViewPoint> viewpoint(new TestViewPoint(model.get())) ;
        viewpoint->init() ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        Object* object2 = model->createObject() ;
        object2->addTrait(new Parent()) ;
        object->addTrait(new Parent()) ;

        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;

        child->changeParent(object2) ;

        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()) ;

        // view has been updated
        CPPUNIT_ASSERT(child->getTrait<HasParentTrait1>()
                            ->getView<ViewHasParentTrait1>(viewpoint.get())
                            ->getUpdateNumber() == 1) ;
      }

      namespace
      {
        class NegativeDeducedTrait : public DeducedTrait
        {};

        DeclareDeducedTrait(NegativeDeducedTrait,Not(HasTrait(Trait1))) ;

        class DeducedTraitOnDeducedTrait : public DeducedTrait
        {};

        DeclareDeducedTrait(DeducedTraitOnDeducedTrait,HasTrait(NegativeDeducedTrait)) ;

      }

      void TestDeducedTrait::deducedTraitOnDeducedTrait()
      {
        InternalMessage("Kernel","Kernel::Test::TestDeducedTrait::deducedTraitOnDeducedTrait entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* object = model->createObject() ;

        CPPUNIT_ASSERT(object->getTrait<NegativeDeducedTrait>()) ;
        CPPUNIT_ASSERT(object->getTrait<DeducedTraitOnDeducedTrait>()) ;
      }


      namespace
      {
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

        class ChildAndTrait1 : public DeducedTrait
        {};

        DeclareDeducedTrait(ChildAndTrait1,And(HasChild(Child),HasTrait(Trait1))) ;

        class ViewHasChildTrait1 : public TraitView<HasChildTrait1,TestViewPoint>
        {
        public:

          ViewHasChildTrait1(HasChildTrait1* o,TestViewPoint* v)
          : TraitView<HasChildTrait1,TestViewPoint>(o,v),
            m_update_number(0)
          {}

          int getUpdateNumber() const
          {
            return m_update_number ;
          }

        protected:

          void onUpdate()
          {
            ++m_update_number ;
          }

          int m_update_number ;
        };

        RegisterView(ViewHasChildTrait1,HasChildTrait1,TestViewPoint) ;
      }

      void TestDeducedTrait::addChildTrait()
      {
        InternalMessage("Kernel","TestDeducedTrait::addChildTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::addChildTrait")) ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        CPPUNIT_ASSERT(! child->getTrait<HasChildTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasChildTrait1>()) ;

        child->addTrait(new Child()) ;

        CPPUNIT_ASSERT(child->getTrait<HasChildTrait1>()) ;
        CPPUNIT_ASSERT(object->getTrait<HasChildTrait1>()) ;
      }

      void TestDeducedTrait::removeChildTrait()
      {
        InternalMessage("Kernel","TestDeducedTrait::removeChildTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::removeChildTrait")) ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;

        CPPUNIT_ASSERT(! child->getTrait<HasChildTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasChildTrait1>()) ;

        child->addTrait(new Child()) ;

        CPPUNIT_ASSERT(object->getTrait<HasChildTrait1>()) ;
        CPPUNIT_ASSERT(child->getTrait<HasChildTrait1>()) ;

        child->destroyTrait(child->getTrait<Child>()) ;

        CPPUNIT_ASSERT(! child->getTrait<HasChildTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasChildTrait1>()) ;
      }

      void TestDeducedTrait::changeParentHasChildBecomeTrue()
      {
        InternalMessage("Kernel","TestDeducedTrait::changeParentHasChildBecomeTrue entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::changeParentHasChildBecomeTrue")) ;

        Object* object = model->createObject() ;
        Object* child = object->createObject() ;
        child->addTrait(new Child()) ;

        Object* object2 = model->createObject() ;

        CPPUNIT_ASSERT(object->getTrait<HasChildTrait1>()) ;
        CPPUNIT_ASSERT(! object2->getTrait<HasChildTrait1>()) ;

        child->changeParent(object2) ;

        CPPUNIT_ASSERT(object2->getTrait<HasChildTrait1>()) ;
        CPPUNIT_ASSERT(! object->getTrait<HasChildTrait1>()) ;

      }

      void TestDeducedTrait::getDependentTraits()
      {
        std::auto_ptr<Trait1> t1(new Trait1()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)9,DeducedTrait::getDependentTraits(t1.get()).size()) ;

        std::auto_ptr<Parent> parent(new Parent()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)2,DeducedTrait::getDependentTraits(parent.get()).size()) ;

        std::auto_ptr<Child> child(new Child()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)2,DeducedTrait::getDependentTraits(child.get()).size()) ;

      }

      namespace
      {
        class Edited : public Trait
        {};
        class Mission : public Trait
        {};
        class FlyingGroup : public Trait
        {};
        class EditedMission : public DeducedTrait
        {};
        class EditedFlyingGroup : public DeducedTrait
        {};

        DeclareDeducedTrait(EditedMission,And(HasTrait(Mission),HasTrait(Edited))) ;
        DeclareDeducedTrait(EditedFlyingGroup,And(HasTrait(FlyingGroup),HasParent(EditedMission))) ;
      }

      void TestDeducedTrait::removeParentDeducedTrait()
      {
        InternalMessage("Kernel","TestDeducedTrait::removeParentDeducedTrait entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::removeParentDeducedTrait")) ;

        Object* mission = model->createObject() ;
        mission->addTrait(new Mission()) ;
        Object* team = mission->createObject() ;
        Object* flyinggroup = team->createObject() ;
        flyinggroup->addTrait(new FlyingGroup()) ;

        CPPUNIT_ASSERT(!flyinggroup->getTrait<EditedFlyingGroup>()) ;

        mission->addTrait(new Edited()) ;

        CPPUNIT_ASSERT(flyinggroup->getTrait<EditedFlyingGroup>()) ;

        mission->destroyTrait(mission->getTrait<Edited>()) ;

        CPPUNIT_ASSERT(!mission->getTrait<EditedMission>()) ;
        CPPUNIT_ASSERT(!flyinggroup->getTrait<EditedFlyingGroup>()) ;
      }

      namespace
      {
        class Pos : public Trait
        {};
        class AncestorPos : public DeducedTrait
        {};
        DeclareDeducedTrait(AncestorPos,HasAncestor(Pos)) ;
      }

      void TestDeducedTrait::hasAncestor()
      {
        InternalMessage("Kernel","TestDeducedTrait::hasAncestor entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::hasAncestor")) ;

        Object* parent = model->createObject() ;
        Object* child = parent->createObject() ;

        CPPUNIT_ASSERT(!parent->getTrait<AncestorPos>()) ;
        CPPUNIT_ASSERT(!child->getTrait<AncestorPos>()) ;

        child->addTrait(new Pos()) ;
        CPPUNIT_ASSERT(!parent->getTrait<AncestorPos>()) ;
        CPPUNIT_ASSERT(!child->getTrait<AncestorPos>()) ;

        parent->addTrait(new Pos()) ;
        CPPUNIT_ASSERT(!parent->getTrait<AncestorPos>()) ;
        CPPUNIT_ASSERT(child->getTrait<AncestorPos>()) ;
      }

      void TestDeducedTrait::hasAncestorRemoveAncestor()
      {
        InternalMessage("Kernel","TestDeducedTrait::hasAncestorRemoveAncestor entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::hasAncestorRemoveAncestor")) ;

        Object* parent = model->createObject() ;
        Object* child = parent->createObject() ;

        CPPUNIT_ASSERT(!parent->getTrait<AncestorPos>()) ;
        CPPUNIT_ASSERT(!child->getTrait<AncestorPos>()) ;

        parent->addTrait(new Pos()) ;
        CPPUNIT_ASSERT(!parent->getTrait<AncestorPos>()) ;
        CPPUNIT_ASSERT(child->getTrait<AncestorPos>()) ;

        parent->destroyTrait(parent->getTrait<Pos>()) ;
        CPPUNIT_ASSERT(!parent->getTrait<AncestorPos>()) ;
        CPPUNIT_ASSERT(!child->getTrait<AncestorPos>()) ;
      }

      void TestDeducedTrait::hasAncestorChangeParent()
      {
        InternalMessage("Kernel","TestDeducedTrait::hasAncestorRemoveAncestor entering") ;
        std::auto_ptr<Model> model(new Model("TestDeducedTrait::hasAncestorRemoveAncestor")) ;

        Object* parent1 = model->createObject() ;
        Object* parent2 = model->createObject() ;
        Object* child = parent1->createObject() ;

        CPPUNIT_ASSERT(!parent1->getTrait<AncestorPos>()) ;
        CPPUNIT_ASSERT(!child->getTrait<AncestorPos>()) ;

        parent2->addTrait(new Pos()) ;
        CPPUNIT_ASSERT(!parent1->getTrait<AncestorPos>()) ;
        CPPUNIT_ASSERT(!child->getTrait<AncestorPos>()) ;

        child->changeParent(parent2) ;

        CPPUNIT_ASSERT(child->getTrait<AncestorPos>()) ;
      }

    }
  }
}
