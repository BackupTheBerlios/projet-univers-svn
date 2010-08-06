/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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
#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/timer.h>

#include <kernel/test/performance/model.h>
#include <kernel/test/performance/test_performance_model.h>
#include <kernel/view_point.h>
#include <kernel/trait_view.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Kernel::Test::Performance::TestPerformanceModel) ;

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {
      namespace Performance
      {
        void TestPerformanceModel::getUnexistingTraitOnEmptyObject()
        {
          const unsigned int number = 1000000 ;
          std::auto_ptr<Model> model(new Model()) ;
          Kernel::Object* root = model->createObject() ;
          
          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            root->getTrait<AB>() ;
          }
        }
        
        void TestPerformanceModel::getExistingTrait()
        {
          std::auto_ptr<Model> model(new Model()) ;
          Kernel::Object* root = model->createObject() ;
          root->addTrait(new A()) ;
          root->addTrait(new B()) ;
          root->addTrait(new C()) ;
          root->addTrait(new D()) ;
          root->addTrait(new E()) ;
          root->addTrait(new F()) ;
          root->addTrait(new G()) ;
          root->addTrait(new H()) ;
          
          const unsigned int number = 1000000 ;
          
          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            root->getTrait<AB>() ;
          }
        }
        
        void TestPerformanceModel::getUnexistingTraitOnFullObject()
        {
          std::auto_ptr<Model> model(new Model()) ;
          Kernel::Object* root = model->createObject() ;
          root->addTrait(new A()) ;
          root->addTrait(new C()) ;
          root->addTrait(new D()) ;
          root->addTrait(new E()) ;
          root->addTrait(new F()) ;
          root->addTrait(new G()) ;
          root->addTrait(new H()) ;
          
          const unsigned int number = 1000000 ;
          
          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            root->getTrait<AB>() ;
          }
        }
        
        void TestPerformanceModel::updateFullObject()
        {
          std::auto_ptr<Model> model(new Model()) ;
          Kernel::Object* root = model->createObject() ;
          A* a = new A() ;
          root->addTrait(a) ;
          root->addTrait(new C()) ;
          root->addTrait(new D()) ;
          root->addTrait(new E()) ;
          root->addTrait(new F()) ;
          root->addTrait(new G()) ;
          root->addTrait(new H()) ;
          
          const unsigned int number = 1000000 ;
          
          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            a->change() ;
          }
        }
        
        void TestPerformanceModel::updateDeducedTrait()
        {
          std::auto_ptr<Model> model(new Model()) ;
          Kernel::Object* root = model->createObject() ;
          root->addTrait(new A()) ;
          root->addTrait(new C()) ;
          root->addTrait(new D()) ;
          root->addTrait(new E()) ;
          root->addTrait(new F()) ;
          root->addTrait(new G()) ;
          root->addTrait(new H()) ;

          AEG* aeg = root->getTrait<AEG>() ;
          const unsigned int number = 1000000 ;
          
          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            aeg->change() ;
          }
        }
        
        void TestPerformanceModel::createDestroyObject()
        {
          std::auto_ptr<Model> model(new Model()) ;
          Kernel::Object* root = model->createObject() ;
          const unsigned int number = 1000000 ;
          
          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            Kernel::Object* temp = root->createObject() ;
            temp->destroyObject() ;
          }
        }

        void TestPerformanceModel::addRemoveTrait()
        {
          std::auto_ptr<Model> model(new Model()) ;
          Kernel::Object* root = model->createObject() ;
          const unsigned int number = 1000000 ;
          
          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            A* a = new A() ;
            root->addTrait(a) ;
            root->destroyTrait(a) ;
          }
        }

        namespace Display
        {

          class DisplayViewPoint : public ViewPoint
          {
          public:

            DisplayViewPoint(Model* model)
            : ViewPoint(model)
            {}
          };

          class DisplaySolid : public TraitView<DisplayedSolid,DisplayViewPoint>
          {
          public:

            virtual void onUpdate()
            {
              ++m_number_of_update ;
            }

            static unsigned int m_number_of_update ;
          };

          unsigned int DisplaySolid::m_number_of_update = 0 ;

          RegisterView(DisplaySolid,DisplayedSolid,DisplayViewPoint) ;
        }

        void TestPerformanceModel::updateSimpleTrait()
        {
          std::auto_ptr<Model> model(new Model()) ;

          Kernel::Object* root = model->createObject() ;
          Positioned* trait = (Positioned*)root->addTrait(new Positioned()) ;

          const unsigned int number = 1000000 ;

          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            trait->change() ;
          }
          CPPUNIT_ASSERT_EQUAL(0,trait->getNumberOfImpactedObservers()) ;
        }

        void TestPerformanceModel::updateTraitWithNoView()
        {
          std::auto_ptr<Model> model(new Model()) ;
          ViewPoint* viewpoint = model->addViewPoint(new Display::DisplayViewPoint(model.get())) ;
          viewpoint->init() ;

          Kernel::Object* root = model->createObject() ;
          Positioned* trait = (Positioned*)root->addTrait(new Positioned()) ;
          Kernel::Object* child = root->createObject() ;
          child->addTrait(new Positioned()) ;
          Kernel::Object* grand_child = child->createObject() ;
          grand_child->addTrait(new Positioned()) ;

          const unsigned int number = 1000000 ;

          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            trait->change() ;
          }
          CPPUNIT_ASSERT_EQUAL(0,trait->getNumberOfImpactedObservers()) ;
          std::ofstream out("updateTraitWithNoView.txt") ;
          out << model->toGraphviz() << std::endl ;
        }

        void TestPerformanceModel::updateTraitWithView()
        {
          std::auto_ptr<Model> model(new Model()) ;
          ViewPoint* viewpoint = model->addViewPoint(new Display::DisplayViewPoint(model.get())) ;
          viewpoint->init() ;

          /*
          Positioned    <-- update
            ^
            |
          Positioned
            ^
            |
          Positioned & Solid    <--- view

          */

          Kernel::Object* root = model->createObject() ;
          Positioned* trait = (Positioned*)root->addTrait(new Positioned()) ;

          Kernel::Object* child = root->createObject() ;
          child->addTrait(new Positioned()) ;
          Kernel::Object* grand_child = child->createObject() ;
          grand_child->addTrait(new Solid()) ;
          grand_child->addTrait(new Positioned()) ;

          CPPUNIT_ASSERT(grand_child->getTrait<DisplayedSolid>()) ;
          CPPUNIT_ASSERT(grand_child->getTrait<DisplayedSolid>()->getView<Display::DisplaySolid>(viewpoint)) ;


          Display::DisplaySolid::m_number_of_update = 0 ;

          // update will update all intermediate traits ?
          const unsigned int number = 1000000 ;

          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            trait->change() ;
          }

          std::ofstream out("updateTraitWithView.txt") ;
          out << model->toGraphviz() << std::endl ;

          CPPUNIT_ASSERT_EQUAL(number,Display::DisplaySolid::m_number_of_update) ;
//          CPPUNIT_ASSERT_EQUAL(1,trait->getNumberOfImpactedObservers()) ;
        }

        void TestPerformanceModel::getChildren()
        {
          std::auto_ptr<Model> model(new Model()) ;
          Kernel::Object* root = model->createObject() ;

          Kernel::Object* child1 = root->createObject() ;
          child1->addTrait(new Positioned()) ;
          Kernel::Object* grand_child1 = child1->createObject() ;

          Kernel::Object* child2 = root->createObject() ;
          child2->addTrait(new Positioned()) ;
          Kernel::Object* grand_child2 = child2->createObject() ;
          grand_child2->addTrait(new Positioned()) ;

          const unsigned int number = 1000000 ;

          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            root->getChildren<Positioned>() ;
          }

        }
        
      }
    }
  }
}
