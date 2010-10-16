/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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
#include <model/team.h>
#include <model/transponder.h>
#include <model/targeting_system.h>
#include <model/positioned.h>
#include <model/selection.h>
#include <model/destroyable.h>
#include <model/whole.h>
#include <model/head_up_display.h>

#include <display/display.h>
#include <display/implementation/ogre/targeted_indicator.h>
#include <display/test/test_hud.h>
#include <display/implementation/observer.h>
#include <display/implementation/displayed_solid.h>
#include <display/implementation/ogre/ogre.h>

using ProjetUnivers::Display::Implementation::Ogre::getOverlay;


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Test
    {
      CPPUNIT_TEST_SUITE_REGISTRATION(TestHUD) ;

      void TestHUD::targetedIndicatorIndicatesEnemyTargetting()
      {
        InternalMessage("Display","Display::TestHUD::targetedIndicatorIndicatesEnemyTargetting entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        Implementation::Ogre::RealWorldViewPoint* viewpoint =
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        /*
        Two ships in different teams
        one selecting other as target
        other has player inside

        We should have the indicator
        */
        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;

        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* ship = Model::createShip(system) ;
        ship->addTrait(new Model::Transponder(team1)) ;
        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;

        Kernel::Object* observer = createObserver(ship) ;

        Kernel::Object* enemy = Model::createShip(system) ;
        enemy->addTrait(new Model::Transponder(team2)) ;
        enemy->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        CPPUNIT_ASSERT(ship->getChild<Implementation::Observer>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Whole>()) ;
        CPPUNIT_ASSERT(!ship->getTrait<Implementation::DisplayedSolid>()) ;

        simulate(model.get(),0.1) ;

        ::Ogre::Overlay* overlay = getOverlay("PU/base/HUD/TargetedIndicator") ;
        CPPUNIT_ASSERT(overlay) ;
        CPPUNIT_ASSERT(!overlay->isVisible()) ;

        enemy->call(Model::TargetingSystem::SelectNearestEnemy) ;

        float test_duration = 0 ;
        test_duration = Kernel::Parameters::getValue<float>("Display","Test.Targeted.Duration",0.1) ;

        simulate(model.get(),test_duration) ;

        CPPUNIT_ASSERT(overlay->isVisible()) ;

        InternalMessage("Display","Display::TestHUD::targetedIndicatorIndicatesEnemyTargetting leaving") ;
      }

      void TestHUD::targetedIndicatorIndicatesSeveralEnemyTargetting()
      {
        InternalMessage("Display","Display::TestHUD::targetedIndicatorIndicatesSeveralEnemyTargetting entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        Implementation::Ogre::RealWorldViewPoint* viewpoint =
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        /*
        Two ships in different teams
        one selecting other as target
        other has player inside

        We should have the indicator
        */
        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;

        Kernel::Object* team2 = model->createObject() ;
        team2->addTrait(new Model::Team("team2")) ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* ship = Model::createShip(system) ;
        ship->addTrait(new Model::Transponder(team1)) ;
        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;

        Kernel::Object* observer = createObserver(ship) ;

        Kernel::Object* enemy1 = Model::createShip(system) ;
        enemy1->addTrait(new Model::Transponder(team2)) ;
        enemy1->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        Kernel::Object* enemy2 = Model::createShip(system) ;
        enemy2->addTrait(new Model::Transponder(team2)) ;
        enemy2->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        CPPUNIT_ASSERT(ship->getChild<Implementation::Observer>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Whole>()) ;
        CPPUNIT_ASSERT(!ship->getTrait<Implementation::DisplayedSolid>()) ;

        simulate(model.get(),0.1) ;

        // no enemy targeting
        ::Ogre::Overlay* overlay = getOverlay("PU/base/HUD/TargetedIndicator") ;
        CPPUNIT_ASSERT(overlay) ;
        CPPUNIT_ASSERT(!overlay->isVisible()) ;

        enemy1->call(Model::TargetingSystem::SelectNearestEnemy) ;
        simulate(model.get(),0.1) ;
        CPPUNIT_ASSERT(overlay->isVisible()) ;

        enemy2->call(Model::TargetingSystem::SelectNearestEnemy) ;
        simulate(model.get(),0.1) ;
        CPPUNIT_ASSERT(overlay->isVisible()) ;

        enemy1->call(Model::TargetingSystem::UnselectTarget) ;
        simulate(model.get(),0.1) ;

        CPPUNIT_ASSERT(!Model::Selection::isSelected(enemy1,ship)) ;
        CPPUNIT_ASSERT(overlay->isVisible()) ;

        enemy2->call(Model::TargetingSystem::UnselectTarget) ;
        simulate(model.get(),0.1) ;

        CPPUNIT_ASSERT(!Model::Selection::isSelected(enemy2,ship)) ;
        CPPUNIT_ASSERT(!overlay->isVisible()) ;

        InternalMessage("Display","Display::TestHUD::targetedIndicatorIndicatesSeveralEnemyTargetting leaving") ;
      }

      void TestHUD::targetedIndicatorDoesNotIndicateFriendTargetting()
      {
        InternalMessage("Display","Display::TestHUD::targetedIndicatorDoesNotIndicateFriendTargetting entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        Implementation::Ogre::RealWorldViewPoint* viewpoint =
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        /*
        Two ships in same teams
        one selecting other as target
        other has player inside

        We should have the indicator
        */
        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* ship = Model::createShip(system) ;
        ship->addTrait(new Model::Transponder(team1)) ;
        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;

        Kernel::Object* observer = createObserver(ship) ;

        Kernel::Object* friend_ship = Model::createShip(system) ;
        friend_ship->addTrait(new Model::Transponder(team1)) ;
        friend_ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        CPPUNIT_ASSERT(ship->getChild<Implementation::Observer>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Whole>()) ;
        CPPUNIT_ASSERT(!ship->getTrait<Implementation::DisplayedSolid>()) ;

        simulate(model.get(),0.1) ;

        CPPUNIT_ASSERT(!hasOverlay("TargetedIndicator")) ;

        friend_ship->call(Model::TargetingSystem::SelectNextTarget) ;
        simulate(model.get(),0.1) ;

        CPPUNIT_ASSERT(Model::Selection::isSelected(friend_ship,ship)) ;
        ::Ogre::Overlay* overlay = getOverlay("PU/base/HUD/TargetedIndicator") ;
        CPPUNIT_ASSERT(overlay) ;
        CPPUNIT_ASSERT(!overlay->isVisible()) ;

        InternalMessage("Display","Display::TestHUD::targetedIndicatorDoesNotIndicateFriendTargetting leaving") ;
      }

      void TestHUD::displayHullLifePoint()
      {
        InternalMessage("Display","Display::TestHUD::displayHullLifePoint entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        Implementation::Ogre::RealWorldViewPoint* viewpoint =
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* ship = Model::createShip(system) ;
        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;

        Kernel::Object* observer = createObserver(ship) ;

        CPPUNIT_ASSERT(ship->getChild<Implementation::Observer>()) ;
        CPPUNIT_ASSERT(ship->getTrait<Model::Whole>()) ;
        CPPUNIT_ASSERT(!ship->getTrait<Implementation::DisplayedSolid>()) ;
        CPPUNIT_ASSERT(ship->getChild<Model::Destroyable>()) ;

        ship->getChild<Model::Destroyable>()->setMaximumHitPoint(Model::Energy::Joule(10)) ;
        for (int i = 1 ; i <= 10 ; ++i)
        {
          ship->getChild<Model::Destroyable>()->damage(Model::Energy::Joule(1)) ;
          simulate(model.get(),0.1) ;
        }

        ::Ogre::Overlay* overlay = getOverlay("PU/base/HUD/HullLifePoint") ;
        CPPUNIT_ASSERT(overlay) ;
        CPPUNIT_ASSERT(overlay->isVisible()) ;

        InternalMessage("Display","Display::TestHUD::displayHullLifePoint leaving") ;
      }

      void TestHUD::displayShipData()
      {
        InternalMessage("Display","Display::TestHUD::displayShipData entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        Implementation::Ogre::RealWorldViewPoint* viewpoint =
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* ship = Model::createShip(system) ;
        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;
        ship->addTrait(new Model::Transponder(team1)) ;

        Kernel::Object* observer = createObserver(ship) ;

        float test_duration = 0 ;
        test_duration = Kernel::Parameters::getValue<float>("Display","Test.ShipData.Duration",0.1) ;

        simulate(model.get(),test_duration) ;

        // check name
        {
          ::Ogre::Overlay* overlay = getOverlay("PU/base/HUD/ShipName") ;
          CPPUNIT_ASSERT(overlay) ;
          CPPUNIT_ASSERT(overlay->isVisible()) ;
        }
        // check speed
        {
          ::Ogre::Overlay* overlay = getOverlay("PU/base/HUD/ShipSpeed") ;
          CPPUNIT_ASSERT(overlay) ;
          CPPUNIT_ASSERT(overlay->isVisible()) ;
        }
        InternalMessage("Display","Display::TestHUD::displayShipData leaving") ;
      }

      void TestHUD::displayTargetSpeed()
      {
        InternalMessage("Display","Display::TestHUD::displayShipData entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        Implementation::Ogre::RealWorldViewPoint* viewpoint =
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        Kernel::Object* team1 = model->createObject() ;
        team1->addTrait(new Model::Team("team1")) ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* ship = Model::createShip(system) ;
        ship->addTrait(new Model::HeadUpDisplay()) ;
        Model::HeadUpDisplay::connect(ship,ship) ;
        ship->addTrait(new Model::Transponder(team1)) ;

        Kernel::Object* observer = createObserver(ship) ;

        Kernel::Object* ship2 = Model::createShip(system) ;

        ship->call(Model::TargetingSystem::SelectNextTarget) ;
        CPPUNIT_ASSERT(Kernel::Relation::areLinked<Model::Selection>(ship,ship2)) ;

        float test_duration = 0 ;
        test_duration = Kernel::Parameters::getValue<float>("Display","Test.TargetSpeed.Duration",0.1) ;

        simulate(model.get(),test_duration) ;

        ::Ogre::Overlay* overlay = getOverlay("PU/base/HUD/TargetSpeed") ;
        CPPUNIT_ASSERT(overlay) ;
        CPPUNIT_ASSERT(overlay->isVisible()) ;
      }

    }
  }
}

