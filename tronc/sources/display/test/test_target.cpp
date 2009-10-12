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

#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/command_delegator.h>
#include <kernel/timer.h>

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
#include <model/model.h>
#include <model/positioned.h>
#include <model/solid.h>
#include <model/selection.h>
#include <model/transponder.h>

#include <display/implementation/target.h>
#include <display/implementation/target_with_selection.h>
#include <display/implementation/ogre/head_up_display.h>
#include <display/implementation/ogre/head_up_display/target.h>
#include <display/implementation/ogre/head_up_display/target_with_selection.h>
#include <display/test/test_target.h>
#include <display/implementation/positioned.h>
#include <display/implementation/observer.h>

using ProjetUnivers::Display::Implementation::Ogre::HUD::Target;

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Display::
                                Test::
                                TestTarget) ;

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Test
    {

      namespace
      {
        /// Acceptable variable for comparison
        const float delta = 1e-4 ;

        bool equal(float i1,float i2)
        {
          return (fabs(i1 - i2) <= delta) ;
        }

      }

      void TestTarget::testCalculateRotation()
      {
        using namespace Implementation::Ogre::HUD ;

        CPPUNIT_ASSERT(equal(Target::calculateRotation(0,1).valueDegrees(),0)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(1,1).valueDegrees(),45)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(1,0).valueDegrees(),90)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(1,-1).valueDegrees(),135)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(0,-1).valueDegrees(),180)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(-1,-1).valueDegrees(),225)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(-1,0).valueDegrees(),270)) ;
        CPPUNIT_ASSERT(equal(Target::calculateRotation(-1,1).valueDegrees(),315) ||
                       equal(Target::calculateRotation(-1,1).valueDegrees(),-45)) ;

      }

      void TestTarget::simulate(Kernel::Model* model,const float& time)
      {
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < time)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
            model->update(seconds) ;
          }
        }
      }

      void TestTarget::rotateObserverLeft(Kernel::Object* ship)
      {
        ship->getTrait<Model::Oriented>()
        ->setOrientation(ship->getTrait<Model::Oriented>()->getOrientation()*
                         Model::Orientation(::Ogre::Quaternion(::Ogre::Degree(45),::Ogre::Vector3::UNIT_Y))) ;

        simulate(ship->getModel(),0.3) ;
      }

      void TestTarget::selectedTarget()
      {
        InternalMessage("Display","Display::TestTarget::selectedTarget entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTarget::selectedTarget")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::ObjectReference target ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
          target = ship ;
        }

        Kernel::Object* ship = Model::createShip(system) ;

        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;

        Kernel::Object* observer = ship->createObject() ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Kernel::CommandDelegator()) ;
        observer->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

        observer->call(Model::TargetingSystem::SelectNextTarget) ;

        CPPUNIT_ASSERT(Kernel::Relation::areLinked<Model::Selection>(ship,target)) ;
        CPPUNIT_ASSERT(Kernel::Relation::areLinked<Display::Implementation::Target>(ship,target)) ;

        Implementation::Ogre::HUD::Target* target_view =
        Kernel::Relation::getRelation(getClassTypeIdentifier(Display::Implementation::Target),ship,target)
        ->getView<Implementation::Ogre::HUD::Target>() ;

        CPPUNIT_ASSERT(!target_view->m_arrow_is_shown) ;
        CPPUNIT_ASSERT(target_view->m_target_is_shown) ;
        CPPUNIT_ASSERT_EQUAL(Ogre::Real(0),target_view->m_target_container->getLeft()) ;
        CPPUNIT_ASSERT_EQUAL(Ogre::Real(0),target_view->m_target_container->getTop()) ;

//        {
//          // check the dependencies
//          Kernel::Notifiable* positioned = observer->getTrait<Implementation::Positioned>() ;
//          Kernel::Notifiable* camera = observer->getTrait<Implementation::Observer>() ;
//          Kernel::Notifiable* selected = Kernel::Relation::getRelation(getClassTypeIdentifier(Display::Implementation::Target),ship,target) ;
//          Kernel::Notifiable* oriented = observer->getTrait<Model::Oriented>() ;
//          Kernel::Notifiable* recursively_oriented = observer->getTrait<Model::RecursivelyOriented>() ;
//
//          CPPUNIT_ASSERT(positioned) ;
//          CPPUNIT_ASSERT(camera) ;
//          CPPUNIT_ASSERT(selected) ;
//
//          CPPUNIT_ASSERT(camera->dependsOn(positioned)) ;
//          CPPUNIT_ASSERT(selected->dependsOn(camera)) ;
//          CPPUNIT_ASSERT(selected->dependsOn(oriented)) ;
//          CPPUNIT_ASSERT(camera->dependsOn(oriented)) ;
//          CPPUNIT_ASSERT(positioned->dependsOn(oriented)) ;
//
//          CPPUNIT_ASSERT(oriented->getDependentNotifiables().find(recursively_oriented) != oriented->getDependentNotifiables().end()) ;
//          CPPUNIT_ASSERT(oriented->getDependentNotifiables().find(positioned) != oriented->getDependentNotifiables().end()) ;
//
//          CPPUNIT_ASSERT(recursively_oriented->getDependentNotifiables().find(selected) != recursively_oriented->getDependentNotifiables().end()) ;
//
//          CPPUNIT_ASSERT(positioned->getDependentNotifiables().find(camera) != positioned->getDependentNotifiables().end()) ;
//
//          CPPUNIT_ASSERT(camera->getDependentNotifiables().find(selected) != camera->getDependentNotifiables().end()) ;
//        }


        InternalMessage("Display","***************************") ;

        model->toGraphviz() ;

        rotateObserverLeft(ship) ;

        Kernel::Log::logToFile(model->toGraphviz(target_view->getViewPoint())) ;

        CPPUNIT_ASSERT(!target_view->m_arrow_is_shown) ;
        CPPUNIT_ASSERT(target_view->m_target_is_shown) ;
        CPPUNIT_ASSERT_MESSAGE(Kernel::toString(target_view->m_target_container->getLeft()),
                               target_view->m_target_container->getLeft()>0.4) ;
        CPPUNIT_ASSERT_EQUAL(Ogre::Real(0),target_view->m_target_container->getTop()) ;

        rotateObserverLeft(ship) ;

        CPPUNIT_ASSERT(!target_view->m_target_is_shown) ;
        CPPUNIT_ASSERT(target_view->m_arrow_is_shown) ;
        CPPUNIT_ASSERT_MESSAGE(Kernel::toString(target_view->m_arrow_container->getLeft()),
                               target_view->m_arrow_container->getLeft()>0.4) ;
        CPPUNIT_ASSERT_EQUAL(Ogre::Real(0),target_view->m_arrow_container->getTop()) ;

        rotateObserverLeft(ship) ;
        rotateObserverLeft(ship) ;
        rotateObserverLeft(ship) ;
        // 180+45°
        CPPUNIT_ASSERT(!target_view->m_target_is_shown) ;
        CPPUNIT_ASSERT(target_view->m_arrow_is_shown) ;
        CPPUNIT_ASSERT_MESSAGE(Kernel::toString(target_view->m_arrow_container->getLeft()),
                               target_view->m_arrow_container->getLeft()<-0.4) ;
        CPPUNIT_ASSERT_EQUAL(Ogre::Real(0),target_view->m_arrow_container->getTop()) ;

        rotateObserverLeft(ship) ;
        rotateObserverLeft(ship) ;

        CPPUNIT_ASSERT(!target_view->m_arrow_is_shown) ;
        CPPUNIT_ASSERT(target_view->m_target_is_shown) ;
        CPPUNIT_ASSERT_MESSAGE(Kernel::toString(target_view->m_target_container->getLeft()),
                               target_view->m_target_container->getLeft()<-0.4) ;
        CPPUNIT_ASSERT_EQUAL(Ogre::Real(0),target_view->m_target_container->getTop()) ;

        rotateObserverLeft(ship) ;

        // one complete turn
        CPPUNIT_ASSERT(!target_view->m_arrow_is_shown) ;
        CPPUNIT_ASSERT(target_view->m_target_is_shown) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(Ogre::Real(0),target_view->m_target_container->getLeft(),delta) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(Ogre::Real(0),target_view->m_target_container->getTop(),delta) ;

        InternalMessage("Display","Display::TestTarget::selectedTarget leaving") ;
      }

      void TestTarget::changeTargetDisplayer()
      {
        InternalMessage("Display","Display::TestTarget::changeTargetDisplayer entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTarget::changeTargetDisplayer")) ;
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
        target->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        Kernel::Object* ship1 = system->createObject() ;
        ship1->addTrait(new Model::Detector(Model::Distance(Model::Distance::_Meter,2000))) ;
        Model::Detector::connect(ship1,ship1) ;
        ship1->addTrait(new Model::TargetingSystem()) ;
        ship1->addTrait(new Model::Computer()) ;
        Model::TargetingSystem::connect(ship1,ship1) ;
        ship1->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship1,ship1) ;

        Kernel::Object* observer = ship1->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;

        Kernel::Object* ship2 = system->createObject() ;
        ship2->addTrait(new Model::Detector(Model::Distance(Model::Distance::_Meter,2000))) ;
        Model::Detector::connect(ship2,ship2) ;
        ship2->addTrait(new Model::TargetingSystem()) ;
        ship2->addTrait(new Model::Computer()) ;
        Model::TargetingSystem::connect(ship2,ship2) ;

        Kernel::Object* observer2 = ship2->createObject() ;
        observer2->addTrait(new Model::Observer()) ;
        observer2->addTrait(new Model::Positioned(Model::Position::Meter(0,0,500))) ;
        observer2->addTrait(new Model::Oriented()) ;

        model->update(0.1) ;
        ship1->call(Model::TargetingSystem::SelectNextTarget) ;

        ship2->call(Model::TargetingSystem::SelectNextTarget) ;
        Model::Computer* computer2 = ship2->getTrait<Model::Computer>() ;
        CPPUNIT_ASSERT(computer2) ;
        CPPUNIT_ASSERT(computer2->getMemoryModel()) ;

        CPPUNIT_ASSERT_EQUAL(Model::Position::Meter(0,0,0),
                             Model::getRelativePosition(viewpoint->getObserver(),universe)) ;

        simulate(model.get(),0.5) ;

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

        // @todo still some checks to perform...

        observer2->addTrait(new Model::Active()) ;
        CPPUNIT_ASSERT(viewpoint->getObserver()) ;
        CPPUNIT_ASSERT_EQUAL(Model::Position::Meter(0,0,500),
                             Model::getRelativePosition(viewpoint->getObserver(),universe)) ;


        simulate(model.get(),0.5) ;

        InternalMessage("Display","Display::TestTarget::changeTargetDisplayer leaving") ;
      }

      void TestTarget::selectedTargetHasSelection()
      {
        InternalMessage("Display","Display::TestTarget::selectedTargetHasSelection entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTarget::selectedTargetHasSelection")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* team = model->createObject() ;
        team->addTrait(new Model::Team("team")) ;

        Kernel::ObjectReference target ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
          target = ship ;
        }

        Kernel::Object* ship = Model::createShip(system) ;
        Model::Transponder* transponder = (Model::Transponder*)ship->addTrait(new Model::Transponder(team)) ;
        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;

        Kernel::Object* observer = ship->createObject() ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Kernel::CommandDelegator()) ;
        observer->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

        observer->call(Model::TargetingSystem::SelectNextTarget) ;

        target->call(Model::TargetingSystem::SelectNextTarget) ;

        Implementation::Ogre::HUD::Target* target_view =
        Kernel::Relation::getRelation(getClassTypeIdentifier(Display::Implementation::Target),ship,target)
        ->getView<Implementation::Ogre::HUD::Target>() ;

        CPPUNIT_ASSERT_EQUAL(Ogre::UTFString("target : " + transponder->getCode()),target_view->m_target_text->getCaption()) ;
      }

      void TestTarget::identifiedTarget()
      {
        InternalMessage("Display","Display::TestTarget::identifiedTarget entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTarget::identifiedTarget")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* team = model->createObject() ;
        team->addTrait(new Model::Team("team")) ;
        Model::Transponder* transponder ;
        Kernel::ObjectReference target ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
          transponder = (Model::Transponder*)ship->addTrait(new Model::Transponder(team)) ;
          target = ship ;
        }

        Kernel::Object* ship = Model::createShip(system) ;
        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;

        Kernel::Object* observer = ship->createObject() ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Kernel::CommandDelegator()) ;
        observer->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

        observer->call(Model::TargetingSystem::SelectNextTarget) ;

        Implementation::Ogre::HUD::Target* target_view =
        Kernel::Relation::getRelation(getClassTypeIdentifier(Display::Implementation::Target),ship,target)
        ->getView<Implementation::Ogre::HUD::Target>() ;

        CPPUNIT_ASSERT_EQUAL(Ogre::UTFString(transponder->getCode()),target_view->m_identification->getCaption()) ;
      }

      void TestTarget::changeTarget()
      {
        InternalMessage("Display","Display::TestTarget::identifiedTarget entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestTarget::identifiedTarget")) ;
        model->init() ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Model::Transponder* transponder ;
        Kernel::ObjectReference target1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
          transponder = (Model::Transponder*)ship->addTrait(new Model::Transponder(team1)) ;
          target1 = ship ;
        }
        Kernel::ObjectReference target2 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,+500)) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          target2 = ship ;
        }

        // player ship
        Kernel::Object* ship = Model::createShip(system) ;
        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;
        ship->addTrait(new Model::Transponder(team2)) ;

        Kernel::Object* observer = ship->createObject() ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Kernel::CommandDelegator()) ;
        observer->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

        target1->call(Model::TargetingSystem::SelectNextTarget) ;
        target2->call(Model::TargetingSystem::SelectNextTarget) ;

        model->startTransaction() ;
        observer->call(Model::TargetingSystem::SelectNearestEnemy) ;
        observer->call(Model::TargetingSystem::SelectNearestEnemy) ;
        model->endTransaction() ;
      }


    }
  }
}

