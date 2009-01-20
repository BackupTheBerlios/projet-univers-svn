/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 20087 Mathieu ROGER                                     *
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
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/timer.h>
#include <kernel/parameters.h>
#include <kernel/command_delegator.h>

#include <model/model.h>
#include <model/positionned.h>
#include <model/stellar_system.h>
#include <model/oriented.h>
#include <model/observer.h>
#include <model/displayed.h>
#include <model/universe.h>
#include <model/mobile.h>
#include <model/player.h>
#include <model/head_up_display.h>
#include <model/targeting_system.h>
#include <model/computer.h>
#include <model/ideal_target.h>
#include <model/image.h>
#include <model/destroyable.h>
#include <model/solid.h>
#include <model/active.h>
#include <model/detector.h>
#include <model/team.h>
#include <model/transponder.h>
#include <model/selected.h>

#include <display/display.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/head_up_display.h>
#include <display/implementation/space_dust.h>
#include <display/test/test_model_view.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Display::
                                Test::
                                TestModelView) ;

namespace ProjetUnivers 
{
  namespace Display 
  {
    namespace Test 
    {

      void TestModelView::testConstruct()
      {
        InternalMessage("Display","Display::TestModelView::testConstruct entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::testConstruct")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        
        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positionned()) ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Display","Display::TestModelView::testConstruct leaving") ;
      }

      void TestModelView::destroyObserver()
      {
        InternalMessage("Display","Display::TestModelView::destroyObserver entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::destroyObserver")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        
        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positionned()) ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        bool destroyed = false ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          if (!destroyed && global_timer.getSecond() > 1.5)
          {
            model->destroyObject(observer) ;
            destroyed = true ;
          }
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Display","Display::TestModelView::destroyObserver leaving") ;
      }
      
      void TestModelView::selectedTarget()
      {
        InternalMessage("Display","Display::TestModelView::selectedTarget entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::selectedTarget")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        }
        
        Kernel::Object* ship = Model::createShip(system) ;

        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;
        
        Kernel::Object* observer = ship->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positionned()) ;
        observer->addTrait(new Model::Oriented()) ;
        observer->addTrait(new Kernel::CommandDelegator()) ;
        observer->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

        ship->getTrait<Model::Oriented>()
        ->setOrientation(ship->getTrait<Model::Oriented>()->getOrientation()*
                         Model::Orientation(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;

        model->update(0.1) ;
        observer->call("Select Next Target") ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        Kernel::Timer rotation_timer ;
        
        while (global_timer.getSecond() < 10)
        {
          float seconds = timer.getSecond() ;
          if (rotation_timer.getSecond() > 1)
          {
            ship->getTrait<Model::Oriented>()
            ->setOrientation(ship->getTrait<Model::Oriented>()->getOrientation()*
                             Model::Orientation(::Ogre::Quaternion(::Ogre::Degree(45),::Ogre::Vector3::UNIT_Y))) ;
            
            rotation_timer.reset() ;
          }
          
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Display","Display::TestModelView::selectedTarget leaving") ;
      }
      
      void TestModelView::displayIdealTarget()
      {
        InternalMessage("Display","Display::TestModelView::displayIdealTarget entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::displayIdealTarget")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        
        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positionned(Model::Position::Meter(0,0,200))) ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Kernel::Object* computer = observer->createObject() ;
        computer->addTrait(new Model::Computer()) ;
        computer->addTrait(new Model::HeadUpDisplay()) ;
        computer->addTrait(new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(computer,computer) ;
        Model::HeadUpDisplay::connect(computer,computer) ;
        
        Kernel::Model* computer_model = computer->getTrait<Model::Computer>()->getMemoryModel() ;
        Kernel::Object* target = computer_model->createObject() ;
        target->addTrait(new Model::Positionned(Model::Position::Meter(50,-100,200))) ;
        target->addTrait(new Model::IdealTarget(computer)) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Display","Display::TestModelView::displayIdealTarget leaving") ;
      }
      
      void TestModelView::spaceDust()
      {
        InternalMessage("Display","Display::TestModelView::spaceDust entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::spaceDust")) ;
        model->init() ;
        
        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        ship->getTrait<Model::Mobile>()->setSpeed(Model::Speed::MeterPerSecond(0,0,10)) ;
        
        Kernel::Object* observer = ship->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positionned()) ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;

        CPPUNIT_ASSERT(observer->getParent<Model::Mobile>()) ;
        CPPUNIT_ASSERT(observer->getTrait<Implementation::SpaceDust>()) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Display","Display::TestModelView::spaceDust leaving") ;
      }
      
      void TestModelView::displayImage()
      {
        InternalMessage("Display","Display::TestModelView::displayImage entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::displayImage")) ;
        model->init() ;
        
        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Image("intro.png")) ;
        universe->addTrait(new Model::Displayed()) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Display","Display::TestModelView::displayImage leaving") ;
        
      }
      
      void TestModelView::displayExplosion()
      {
        InternalMessage("Display","Display::TestModelView::spaceDust entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::displayExplosion")) ;
        model->init() ;
        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        ship->getTrait<Model::Destroyable>()->damage(Model::Energy::Joule(50)) ;
        
        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positionned()) ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Display","Display::TestModelView::spaceDust leaving") ;
      }
      
      void TestModelView::recreateObserver()
      {
        InternalMessage("Display","Display::TestModelView::recreateObserver entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::recreateObserver")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        
        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positionned()) ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        bool destroyed = false ;
        bool recreated = false ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          if (!destroyed && global_timer.getSecond() > 1.5)
          {
            model->destroyObject(observer) ;
            destroyed = true ;
          }
          if (destroyed && !recreated && global_timer.getSecond() > 2)
          {
            observer = system->createObject() ;
            observer->addTrait(new Model::Observer()) ;
            observer->addTrait(new Model::Player()) ;
            observer->addTrait(new Model::Active()) ;
            observer->addTrait(new Model::Positionned()) ;
            observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
            recreated = true ;
          }
          
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Display","Display::TestModelView::recreateObserver leaving") ;
      }

      void TestModelView::getMeshSize()
      {
        InternalMessage("Display","Display::TestModelView::getMeshSize entering") ;

        /// init
        Kernel::Parameters::load("demonstration.config") ;
        Kernel::Log::init() ;

        Model::start() ;
        Display::start(Display::DefaultRenderer) ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::getMeshSize")) ;

        Kernel::Object* object = model->createObject() ;
        object->addTrait(new Model::Solid(Model::Mesh("razor.mesh"))) ;
        CPPUNIT_ASSERT(object->getTrait<Model::Solid>()->getRadius().Meter() > 0) ;
      }
      
      void TestModelView::changeParent()
      {
        InternalMessage("Display","Display::TestModelView::changeParent entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::changeParent")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        
        Kernel::Object* database = model->createObject() ;
        
        Kernel::Object* ship = Model::createShip(database) ;
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        
        ship->changeParent(system) ;
        
        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positionned()) ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        model->update(1) ;
        
        InternalMessage("Display","Display::TestModelView::changeParent leaving") ;
      }
      
      void TestModelView::changeObserver()
      {
        InternalMessage("Display","Display::TestModelView::changeObserver entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::changeObserver")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        
        Kernel::Object* observer1 = system->createObject() ;
        observer1->addTrait(new Model::Observer()) ;
        observer1->addTrait(new Model::Active()) ;
        observer1->addTrait(new Model::Positionned()) ;
        observer1->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;

        Kernel::Object* observer2 = system->createObject() ;
        observer2->addTrait(new Model::Observer()) ;
        observer2->addTrait(new Model::Positionned(Model::Position::Meter(0,0,500))) ;
        observer2->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 2)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }
        
        observer1->destroyTrait(observer1->getTrait<Model::Active>()) ;
        observer2->addTrait(new Model::Active()) ;
        
        global_timer.reset() ;
        while (global_timer.getSecond() < 1)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }

        InternalMessage("Display","Display::TestModelView::changeObserver leaving") ;
      }
    
      void TestModelView::changeTargetDisplayer()
      {
        InternalMessage("Display","Display::TestModelView::changeTargetDisplayer entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::changeTargetDisplayer")) ;
        model->init() ;
        
        Implementation::Ogre::RealWorldViewPoint* viewpoint = 
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;
        
        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        
        Kernel::Object* target = Model::createShip(system) ;
        target->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        
        
        Kernel::Object* ship1 = system->createObject() ;
        ship1->addTrait(new Model::Detector(ship1,Model::Distance(Model::Distance::_Meter,2000))) ;
        ship1->addTrait(new Model::TargetingSystem()) ;
        ship1->addTrait(new Model::Computer()) ;
        Model::TargetingSystem::connect(ship1,ship1) ;
        ship1->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship1,ship1) ;
        
        Kernel::Object* observer = ship1->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positionned()) ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;


        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Model::Detector(ship2,Model::Distance(Model::Distance::_Meter,2000))) ;
        ship2->addTrait(new Model::TargetingSystem()) ;
        ship2->addTrait(new Model::Computer()) ;
        Model::TargetingSystem::connect(ship2,ship2) ;
        
        Kernel::Object* observer2 = ship2->createObject() ;
        observer2->addTrait(new Model::Observer()) ;
        observer2->addTrait(new Model::Positionned(Model::Position::Meter(0,0,500))) ;
        observer2->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;

        model->update(0.1) ;
        ship1->call("Select Next Target") ;

        ship2->call("Select Next Target") ;
        Model::Computer* computer2 = ship2->getTrait<Model::Computer>() ;
        CPPUNIT_ASSERT(computer2) ;
        CPPUNIT_ASSERT(computer2->getMemoryModel()) ;
        
        CPPUNIT_ASSERT_EQUAL(Model::Position::Meter(0,0,0),
                             Model::getRelativePosition(viewpoint->getObserver(),universe)) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 2)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        

        // *destroy* previous observer + ship
        observer->destroyObject() ;
        ship1->destroyTrait(ship1->getTrait<Model::HeadUpDisplay>()) ;

        // switch observer + add a target displayer 
        ship2->addTrait(new Model::HeadUpDisplay()) ;
        Implementation::Ogre::HeadUpDisplay* new_displayer = 
          ship2->getTrait<Model::HeadUpDisplay>()
               ->getView<Implementation::Ogre::HeadUpDisplay>(viewpoint) ;
        
        CPPUNIT_ASSERT(!new_displayer->m_implementation->getModel()) ;

        Model::HeadUpDisplay::connect(ship2,ship2) ;

        CPPUNIT_ASSERT(new_displayer->m_implementation.get()) ;
        CPPUNIT_ASSERT(new_displayer->m_implementation->getModel()) ;
        Kernel::Model* memory = computer2->getMemoryModel() ;
        CPPUNIT_ASSERT(memory == new_displayer->m_implementation->getModel()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,memory->getRoots().size()) ;

        Kernel::Object* root = *memory->getRoots().begin() ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,root->getChildren<Model::Selected>().size()) ;

        Model::Selected* selected = *root->getChildren<Model::Selected>().begin() ;

        // @todo still some checks to perform...
        
        observer2->addTrait(new Model::Active()) ;
        CPPUNIT_ASSERT(viewpoint->getObserver()) ;
        CPPUNIT_ASSERT_EQUAL(Model::Position::Meter(0,0,500),
                             Model::getRelativePosition(viewpoint->getObserver(),universe)) ;
        
        
        global_timer.reset() ;
        while (global_timer.getSecond() < 2)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Display","Display::TestModelView::changeTargetDisplayer leaving") ;
      }
      
    }
  }
}

