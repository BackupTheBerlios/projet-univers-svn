/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Mathieu ROGER                                 *
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
#include <model/positioned.h>
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
#include <model/custom_mission.h>
#include <model/flying_group.h>
#include <model/state.h>
#include <model/mission.h>
#include <model/played.h>

#include <display/display.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/head_up_display.h>
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/space_dust.h>
#include <display/implementation/positioned.h>
#include <display/test/test_model_view.h>
#include <model/selection.h>
#include <display/implementation/target.h>


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

        Implementation::Ogre::RealWorldViewPoint* viewpoint = model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        InternalMessage("Display","Display::TestModelView::testConstruct") ;
        observer->addTrait(new Model::Oriented(::Ogre::Quaternion(::Ogre::Degree(180),::Ogre::Vector3::UNIT_Y))) ;

        Implementation::Ogre::Positioned* positioned_observer = observer->getTrait<Implementation::Positioned>()->getView<Implementation::Ogre::Positioned>(viewpoint) ;
        CPPUNIT_ASSERT(positioned_observer->getNode()->_getDerivedOrientation().equals(::Ogre::Quaternion(0,0,1,0),::Ogre::Degree(5))) ;

        observer->getTrait<Model::Oriented>()->setOrientation(::Ogre::Quaternion()) ;
        CPPUNIT_ASSERT(positioned_observer->getNode()->_getDerivedOrientation().equals(::Ogre::Quaternion(1,0,0,0),::Ogre::Degree(5))) ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < 0.1)
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
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        bool destroyed = false ;

        while (global_timer.getSecond() < 0.2)
        {
          float seconds = timer.getSecond() ;
          if (!destroyed && global_timer.getSecond() > 0.1)
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

      void TestModelView::displayIdealTarget()
      {
        InternalMessage("Display","Display::TestModelView::displayIdealTarget entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::displayIdealTarget")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned(Model::Position::Meter(0,0,200))) ;
        observer->addTrait(new Model::Oriented()) ;

        Kernel::Object* computer = observer->createObject() ;
        computer->addTrait(new Model::Computer()) ;
        computer->addTrait(new Model::HeadUpDisplay()) ;
        computer->addTrait(new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(computer,computer) ;
        Model::HeadUpDisplay::connect(computer,computer) ;

        Kernel::Model* computer_model = computer->getTrait<Model::Computer>()->getMemoryModel() ;
        Kernel::Object* target = computer_model->createObject() ;
        target->addTrait(new Model::Positioned(Model::Position::Meter(50,-100,-200))) ;
        target->addTrait(new Model::IdealTarget(computer)) ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < 0.1)
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
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        ship->getTrait<Model::Mobile>()->setSpeed(Model::Speed::MeterPerSecond(0,0,-10)) ;

        Kernel::Object* observer = ship->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;

        CPPUNIT_ASSERT(observer->getParent<Model::Mobile>()) ;
        CPPUNIT_ASSERT(observer->getTrait<Implementation::SpaceDust>()) ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < 0.1)
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

        while (global_timer.getSecond() < 0.1)
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
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;

        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

          Kernel::Timer timer ;
          Kernel::Timer global_timer ;

          bool destroyed = false ;
          while (global_timer.getSecond() < 4)
          {
            if (!destroyed && global_timer.getSecond() > 1)
            {
              destroyed = true ;
              ship->getTrait<Model::Destroyable>()->damage(Model::Energy::Joule(50)) ;
            }
            float seconds = timer.getSecond() ;
            if (seconds != 0)
            {
              timer.reset() ;
            }
            model->update(seconds) ;
          }
        }
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

          Kernel::Timer timer ;
          Kernel::Timer global_timer ;

          bool destroyed = false ;
          while (global_timer.getSecond() < 4)
          {
            if (!destroyed && global_timer.getSecond() > 1)
            {
              destroyed = true ;
              ship->getTrait<Model::Destroyable>()->damage(Model::Energy::Joule(50)) ;
            }
            float seconds = timer.getSecond() ;
            if (seconds != 0)
            {
              timer.reset() ;
            }
            model->update(seconds) ;
          }
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
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        bool destroyed = false ;
        bool recreated = false ;

        while (global_timer.getSecond() < 0.3)
        {
          float seconds = timer.getSecond() ;
          if (!destroyed && global_timer.getSecond() > 0.1)
          {
            model->destroyObject(observer) ;
            destroyed = true ;
          }
          if (destroyed && !recreated && global_timer.getSecond() > 0.2)
          {
            observer = system->createObject() ;
            observer->addTrait(new Model::Observer()) ;
            observer->addTrait(new Model::Player()) ;
            observer->addTrait(new Model::Active()) ;
            observer->addTrait(new Model::Positioned()) ;
            observer->addTrait(new Model::Oriented()) ;
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
        object->addTrait(new Model::Solid(Model::Mesh("test_ship.mesh"))) ;
        CPPUNIT_ASSERT(object->getTrait<Model::Solid>()->getRadius().Meter() > 0) ;
      }

      void TestModelView::changeParent()
      {
        InternalMessage("Display","Display::TestModelView::changeParent entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::changeParent")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* database = model->createObject() ;

        Kernel::Object* ship = Model::createShip(database) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        ship->changeParent(system) ;

        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;

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
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        Kernel::Object* observer1 = system->createObject() ;
        observer1->addTrait(new Model::Observer()) ;
        observer1->addTrait(new Model::Active()) ;
        observer1->addTrait(new Model::Positioned()) ;
        observer1->addTrait(new Model::Oriented()) ;

        Kernel::Object* observer2 = system->createObject() ;
        observer2->addTrait(new Model::Observer()) ;
        observer2->addTrait(new Model::Positioned(Model::Position::Meter(0,0,500))) ;
        observer2->addTrait(new Model::Oriented()) ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < 0.1)
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
        while (global_timer.getSecond() < 0.1)
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

      void TestModelView::setOrientation()
      {
        InternalMessage("Display","Display::TestModelView::setOrientation entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestModelView::setOrientation")) ;
        model->init() ;

        Implementation::Ogre::RealWorldViewPoint* viewpoint =
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* target = Model::createShip(system) ;

        Implementation::Ogre::Positioned* positioned = target->getTrait<Implementation::Positioned>()->getView<Implementation::Ogre::Positioned>(viewpoint) ;
        CPPUNIT_ASSERT(positioned) ;

        CPPUNIT_ASSERT_EQUAL(Ogre::Vector3(0,0,0),positioned->getNode()->getPosition()) ;
        CPPUNIT_ASSERT_EQUAL(Ogre::Quaternion(),positioned->getNode()->getOrientation()) ;

        target->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        CPPUNIT_ASSERT_EQUAL(Ogre::Vector3(0,0,-500/Implementation::Ogre::conversion_factor),positioned->getNode()->getPosition()) ;
        CPPUNIT_ASSERT_EQUAL(Ogre::Quaternion(),positioned->getNode()->getOrientation()) ;

        target->getTrait<Model::Oriented>()->setOrientation(::Ogre::Quaternion(::Ogre::Degree(90),::Ogre::Vector3::UNIT_Y)) ;

        CPPUNIT_ASSERT_EQUAL(Ogre::Quaternion(::Ogre::Degree(90),::Ogre::Vector3::UNIT_Y),positioned->getNode()->getOrientation()) ;
      }

      void TestModelView::testMission()
      {
        Kernel::Log::Block temp("Physic","TestDemonstration::testMission") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* mission = model->createObject() ;
        mission->addTrait(new Model::CustomMission("",NULL,NULL)) ;
        mission->getTrait<Model::CustomMission>()->setStartingDistance(Model::Distance(Model::Distance::_Meter,4000)) ;
        mission->addTrait(new Model::State()) ;

        {
          Kernel::Object* team = mission->createObject() ;
          team->addTrait(new Model::Team("")) ;

          Kernel::Object* flying_group = team->createObject() ;
          flying_group->addTrait(new Model::FlyingGroup("")) ;

          flying_group->getTrait<Model::FlyingGroup>()->setShipName("test_ship") ;
          flying_group->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(2) ;
          flying_group->getTrait<Model::FlyingGroup>()->setHasPlayer(true) ;
        }

        {
          Kernel::Object* team = mission->createObject() ;
          team->addTrait(new Model::Team("")) ;

          Kernel::Object* flying_group = team->createObject() ;
          flying_group->addTrait(new Model::FlyingGroup("")) ;

          flying_group->getTrait<Model::FlyingGroup>()->setShipName("test_ship") ;
          flying_group->getTrait<Model::FlyingGroup>()->setInitialNumberOfShips(3) ;
          flying_group->getTrait<Model::FlyingGroup>()->setHasPlayer(false) ;
          flying_group->getTrait<Model::FlyingGroup>()->setNumberOfSpawn(2) ;

        }

        CPPUNIT_ASSERT(!mission->getTrait<Model::Mission>()->getSystem()) ;
        mission->addTrait(new Model::Played()) ;
        model->update(0.1) ;
        mission->destroyTrait(mission->getTrait<Model::Played>()) ;
        model->update(0.1) ;
      }


    }
  }
}

