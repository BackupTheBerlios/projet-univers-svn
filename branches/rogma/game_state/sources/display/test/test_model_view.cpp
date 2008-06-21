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
#include <model/universe.h>
#include <model/mobile.h>
#include <model/player.h>
#include <model/target_displayer.h>
#include <model/targeting_system.h>
#include <model/computer.h>
#include <model/ideal_target.h>

#include <display/display.h>
#include <display/implementation/space_dust.h>
#include <display/test/test_model_view.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Display::
                                Test::
                                TestModelView) ;

namespace ProjetUnivers {
  namespace Display {
    namespace Test {

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

        ship->addTrait(new Model::TargetDisplayer()) ;
        Model::TargetDisplayer::connect(ship,ship) ;
        
        Kernel::Object* observer = ship->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
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
        observer->addTrait(new Model::Positionned(Model::Position::Meter(0,0,200))) ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Kernel::Object* computer = observer->createObject() ;
        computer->addTrait(new Model::Computer()) ;
        computer->addTrait(new Model::TargetDisplayer()) ;
        computer->addTrait(new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(computer,computer) ;
        Model::TargetDisplayer::connect(computer,computer) ;
        
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
      
      void TestModelView::setUp() 
      {
      }
      
      void TestModelView::tearDown() 
      {
      }

    }
  }
}

