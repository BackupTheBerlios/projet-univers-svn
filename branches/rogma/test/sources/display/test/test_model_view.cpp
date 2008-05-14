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
#include <model/target_displayer.h>
#include <model/targeting_system.h>
#include <model/computer.h>
#include <model/ideal_target.h>

#include <display/display.h>
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
        
        Model::init() ;
        Display::init(false) ;

        Kernel::Object* universe = Model::createObject() ;
        Model::addTrait(universe,new Model::Universe()) ;
        Model::addTrait(universe,new Model::Positionned()) ;

        Kernel::Object* system = Model::createObject(universe) ;
        Model::addTrait(system,new Model::StellarSystem()) ;
        Model::addTrait(system,new Model::Positionned()) ;
        
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        
        Kernel::Object* observer = Model::createObject(system) ;
        Model::addTrait(observer,new Model::Observer()) ;
        Model::addTrait(observer,new Model::Positionned()) ;
        Model::addTrait(observer,new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Display::buildRealWorldViewPoint(observer) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;

          if (seconds != 0)
          {
            timer.reset() ;
          }
          Model::update(elapsed) ;
          Display::update() ;
        }        
        
        Display::close() ;
        Model::close() ;
        
        InternalMessage("Display","Display::TestModelView::testConstruct leaving") ;
      }

      void TestModelView::destroyObserver()
      {
        InternalMessage("Display","Display::TestModelView::destroyObserver entering") ;
        
        Model::init() ;
        Display::init(false) ;

        Kernel::Object* universe = Model::createObject() ;
        Model::addTrait(universe,new Model::Universe()) ;
        Model::addTrait(universe,new Model::Positionned()) ;

        Kernel::Object* system = Model::createObject(universe) ;
        Model::addTrait(system,new Model::StellarSystem()) ;
        Model::addTrait(system,new Model::Positionned()) ;
        
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        
        Kernel::Object* observer = Model::createObject(system) ;
        Model::addTrait(observer,new Model::Observer()) ;
        Model::addTrait(observer,new Model::Positionned()) ;
        Model::addTrait(observer,new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Display::buildRealWorldViewPoint(observer) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        bool destroyed = false ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;

          if (!destroyed && global_timer.getSecond() > 1.5)
          {
            Model::destroyObject(observer) ;
            destroyed = true ;
          }
          
          if (seconds != 0)
          {
            timer.reset() ;
          }
          Model::update(elapsed) ;
          Display::update() ;
        }        
        
        Display::close() ;
        Model::close() ;
        
        InternalMessage("Display","Display::TestModelView::destroyObserver leaving") ;
      }
      
      void TestModelView::selectedTarget()
      {
        InternalMessage("Display","Display::TestModelView::selectedTarget entering") ;
        
        Model::init() ;
        Display::init(false) ;

        Kernel::Object* universe = Model::createObject() ;
        Model::addTrait(universe,new Model::Universe()) ;
        Model::addTrait(universe,new Model::Positionned()) ;

        Kernel::Object* system = Model::createObject(universe) ;
        Model::addTrait(system,new Model::StellarSystem()) ;
        Model::addTrait(system,new Model::Positionned()) ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        }
        
        Kernel::Object* ship = Model::createShip(system) ;

        Model::addTrait(ship,new Model::TargetDisplayer()) ;
        Model::TargetDisplayer::connect(ship,ship) ;
        
        Kernel::Object* observer = Model::createObject(ship) ;
        Model::addTrait(observer,new Model::Observer()) ;
        Model::addTrait(observer,new Model::Positionned()) ;
        Model::addTrait(observer,new Model::Oriented()) ;
        Model::addTrait(observer,new Kernel::CommandDelegator()) ;
        observer->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

        ship->getTrait<Model::Oriented>()
        ->setOrientation(ship->getTrait<Model::Oriented>()->getOrientation()*
                         Model::Orientation(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
//        ship->getTrait<Model::Oriented>()
//        ->setOrientation(ship->getTrait<Model::Oriented>()->getOrientation()*
//                         Model::Orientation(::Ogre::Quaternion(::Ogre::Degree(45),::Ogre::Vector3::UNIT_X))) ;

        Display::buildRealWorldViewPoint(observer) ;

        Model::update(Model::Duration::Second(0.1)) ;
        observer->call("Select Next Target") ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        Kernel::Timer rotation_timer ;
        
        
        while (global_timer.getSecond() < 10)
        {
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;

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
            Model::update(elapsed) ;
            Display::update() ;
          }
          
        }        
        
        Display::close() ;
        Model::close() ;
        
        InternalMessage("Display","Display::TestModelView::selectedTarget leaving") ;
      }
      
      void TestModelView::displayIdealTarget()
      {
        InternalMessage("Display","Display::TestModelView::displayIdealTarget entering") ;
        
        Model::init() ;
        Display::init(false) ;

        Kernel::Object* universe = Model::createObject() ;
        Model::addTrait(universe,new Model::Universe()) ;
        Model::addTrait(universe,new Model::Positionned()) ;

        Kernel::Object* system = Model::createObject(universe) ;
        Model::addTrait(system,new Model::StellarSystem()) ;
        Model::addTrait(system,new Model::Positionned()) ;
        
        Kernel::Object* observer = Model::createObject(system) ;
        Model::addTrait(observer,new Model::Observer()) ;
        Model::addTrait(observer,new Model::Positionned(Model::Position::Meter(0,0,200))) ;
        Model::addTrait(observer,new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;
        
        Kernel::Object* computer = Model::createObject(observer) ;
        Model::addTrait(computer,new Model::Computer()) ;
        Model::addTrait(computer,new Model::TargetDisplayer()) ;
        Model::addTrait(computer,new Model::TargetingSystem()) ;
        Model::TargetDisplayer::connect(computer,computer) ;
        Model::TargetingSystem::connect(computer,computer) ;
        
        Kernel::Model* model = computer->getTrait<Model::Computer>()->getMemoryModel() ;
        Kernel::Object* target = model->createObject() ;
        model->addTrait(target,new Model::Positionned(Model::Position::Meter(50,-100,200))) ;
        model->addTrait(target,new Model::IdealTarget(computer)) ;
        
        Display::buildRealWorldViewPoint(observer) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 3)
        {
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;
          if (seconds != 0)
          {
            timer.reset() ;
            Model::update(elapsed) ;
            Display::update() ;
          }
        }        
        
        Display::close() ;
        Model::close() ;
        
        InternalMessage("Display","Display::TestModelView::displayIdealTarget leaving") ;
        
      }
      
      void TestModelView::setUp() 
      {
        Model::closeRessources() ;
      }
      
      void TestModelView::tearDown() 
      {
      }

    }
  }
}

