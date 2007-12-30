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

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {

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
        Object* object = model->createObject("object") ;

        model->addTrait(object,new Trait1()) ;
        /// Check that object has no DeducedTrait1
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait1>()) ;

        model->addTrait(object,new Trait2()) ;
        /// Check that object has no DeducedTrait1
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait1>()) ;

        model->addTrait(object,new Trait3()) ;
        /// Check that object has automatically gained DeducedTrait1
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait1>()) ;
        
        model->destroyTrait(object,object->getTrait<Trait2>()) ;
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
        Object* object = model->createObject("object") ;

        /// Check that object has no DeducedTrait2
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait2>()) ;

        model->addTrait(object,new Trait1()) ;
        /// Check that object has automatically gained DeducedTrait2
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait2>()) ;


        model->addTrait(object,new Trait2()) ;
        /// Check that object still has DeducedTrait2
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait2>()) ;

        model->destroyTrait(object,object->getTrait<Trait2>()) ;
        /// Check that object still has DeducedTrait2
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait2>()) ;

        model->destroyTrait(object,object->getTrait<Trait1>()) ;
        /// Check that object has lost DeducedTrait2
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait2>()) ;

        model->addTrait(object,new Trait3()) ;
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
        Object* object = model->createObject("object") ;

        /// Check that object has DeducedTrait3
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait3>()) ;

        model->addTrait(object,new Trait1()) ;
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
        Object* object = model->createObject("object") ;

        /// Check that object has DeducedTrait4
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait4>()) ;
        
        model->addTrait(object,new Trait1()) ;
        model->addTrait(object,new Trait3()) ;
        /// Check that object has automatically lost DeducedTrait4
        CPPUNIT_ASSERT(! object->getTrait<DeducedTrait4>()) ;

        model->addTrait(object,new Trait2()) ;
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
        Object* object = model->createObject("object") ;

        /// Check that object has DeducedTrait5 but not DeducedTrait6
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait5>()) ;
        CPPUNIT_ASSERT(!object->getTrait<DeducedTrait6>()) ;

        model->addTrait(object,new Trait3()) ;
        /// Check that object has DeducedTrait5 but not DeducedTrait6
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait5>()) ;
        CPPUNIT_ASSERT(!object->getTrait<DeducedTrait6>()) ;

        model->addTrait(object,new Trait2()) ;
        /// Check that object has DeducedTrait5 and DeducedTrait6
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait5>()) ;
        CPPUNIT_ASSERT(object->getTrait<DeducedTrait6>()) ;

        model->addTrait(object,new Trait1()) ;
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
        Object* object = model->createObject("object") ;

        model->addTrait(object,new Trait1()) ;
        model->addTrait(object,new Trait2()) ;

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
      
      void TestDeducedTrait::setUp()
      {
      }

      void TestDeducedTrait::tearDown()
      {
      }

 
       
       
    }
  }
}
