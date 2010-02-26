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
#include <model/sized.h>
#include <model/selection.h>
#include <model/hit.h>

#include <display/display.h>
#include <display/implementation/target.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/space_dust.h>
#include <display/implementation/positioned.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/head_up_display.h>
#include <display/implementation/ogre/positioned.h>
#include <display/test/test_effect.h>
#include <model/laser.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Test
    {
      CPPUNIT_TEST_SUITE_REGISTRATION(TestEffect) ;

      Kernel::Object* TestEffect::createUniverseAndSystem(Kernel::Model* model) const
      {
        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positioned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positioned()) ;

        return system ;
      }

      Kernel::Object* TestEffect::createObserver(Kernel::Object* parent) const
      {
        Kernel::Object* observer = parent->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Active()) ;
        observer->addTrait(new Model::Positioned()) ;
        observer->addTrait(new Model::Oriented()) ;

        return observer ;
      }

      void TestEffect::simulate(Kernel::Model* model,const float& seconds)
      {
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < seconds)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }
      }

      ::Ogre::ParticleSystem* TestEffect::getUniqueParticleSystem() const
      {
        ::Ogre::SceneManager::MovableObjectIterator iterator = Implementation::Ogre::getManager()->getMovableObjectIterator(::Ogre::ParticleSystemFactory::FACTORY_TYPE_NAME) ;
        ::Ogre::ParticleSystem* result = NULL ;

        while (iterator.hasMoreElements())
        {
          if (!result)
          {
            result = static_cast< ::Ogre::ParticleSystem* >(iterator.getNext()) ;
            if (!result->isAttached())
              // do not 'count' if the element is not attached (because of pooling)
              result = NULL ;
          }
          else
            // several results
            return NULL ;
        }

        return result ;
      }

      void TestEffect::spaceDust()
      {
        InternalMessage("Display","Display::TestEffect::spaceDust entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestEffect::spaceDust")) ;
        model->init() ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;

        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        ship->getTrait<Model::Mobile>()->setSpeed(Model::Speed::MeterPerSecond(0,0,-10)) ;

        Kernel::Object* observer = createObserver(ship) ;

        CPPUNIT_ASSERT(observer->getParent<Model::Mobile>()) ;
        CPPUNIT_ASSERT(observer->getTrait<Implementation::SpaceDust>()) ;

        simulate(model.get(),0.1) ;

        CPPUNIT_ASSERT(getUniqueParticleSystem()) ;

        InternalMessage("Display","Display::TestEffect::spaceDust leaving") ;
      }

      void TestEffect::displayExplosion()
      {
        InternalMessage("Display","Display::TestEffect::displayExplosion entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestEffect::displayExplosion")) ;
        model->init() ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* observer = createObserver(system) ;
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

        CPPUNIT_ASSERT(!getUniqueParticleSystem()) ;

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
        CPPUNIT_ASSERT(!getUniqueParticleSystem()) ;

        InternalMessage("Display","Display::TestEffect::displayExplosion leaving") ;
      }

      void TestEffect::effect()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestEffect::displayExplosion")) ;
        model->init() ;

        Implementation::Ogre::RealWorldViewPoint* viewpoint =
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* observer = createObserver(system) ;
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        Implementation::Ogre::Positioned* positioned = ship->getTrait<Implementation::Positioned>()->getView<Implementation::Ogre::Positioned>(viewpoint) ;
        CPPUNIT_ASSERT(positioned) ;

        ::Ogre::SceneNode* effect(Implementation::Ogre::createParticleEffect("PU/Tests/Hit",
                                                                             positioned->getNode(),
                                                                             Model::Position::Meter(200,0,0))) ;

        float size = Implementation::Ogre::convert(Model::Distance(Model::Distance::_Meter,2)) ;
        effect->setScale(size,size,size) ;
        std::string name = effect->getName() ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        simulate(model.get(),0.1) ;
        CPPUNIT_ASSERT(getUniqueParticleSystem()) ;
        simulate(model.get(),3.9) ;
        CPPUNIT_ASSERT(!getUniqueParticleSystem()) ;

        try
        {
          // accessing an un-existing node raise exception
          viewpoint->getManager()->getSceneNode(name) ;
          CPPUNIT_ASSERT(false) ;
        }
        catch(std::exception&)
        {}
      }

      void TestEffect::destroyEffectParent()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Implementation::Ogre::RealWorldViewPoint* viewpoint =
          model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* observer = createObserver(system) ;
        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        Implementation::Ogre::Positioned* positioned = ship->getTrait<Implementation::Positioned>()->getView<Implementation::Ogre::Positioned>(viewpoint) ;
        CPPUNIT_ASSERT(positioned) ;

        ::Ogre::SceneNode* effect(Implementation::Ogre::createParticleEffect("PU/Tests/Hit",
                                                                             positioned->getNode(),
                                                                             Model::Position::Meter(200,0,0),
                                                                             Model::Orientation())) ;
        std::string name = effect->getName() ;

        ship->destroyObject() ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        simulate(model.get(),4) ;

        CPPUNIT_ASSERT(!getUniqueParticleSystem()) ;

        try
        {
          // accessing an un-existing node raise exception
          viewpoint->getManager()->getSceneNode(name) ;
          CPPUNIT_ASSERT(false) ;
        }
        catch(std::exception&)
        {}
      }

      void TestEffect::hit()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* observer = createObserver(system) ;

        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;

        // create a beam, a collision and watch
        Kernel::Object* hit = ship->createObject() ;
        hit->addTrait(new Model::Hit()) ;
        hit->addTrait(new Model::Positioned(Model::Position::Meter(0,50,0))) ;
        hit->addTrait(new Model::Oriented()) ;
        hit->addTrait(new Model::Sized(Model::Distance(Model::Distance::_Meter,50))) ;

        simulate(model.get(),0.1) ;

        CPPUNIT_ASSERT(getUniqueParticleSystem()) ;
      }

      void TestEffect::simulateHit()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;

        Kernel::Object* system = createUniverseAndSystem(model.get()) ;
        Kernel::Object* observer = createObserver(system) ;

        Kernel::Object* ship = Model::createShip(system) ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-500)) ;
        ship->getTrait<Model::Destroyable>()->setMaximumHitPoint(Model::Energy::Joule(5000)) ;

        Kernel::Object* ship2 = Model::createShip(system) ;
        ship2->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(-500,0,-500)) ;
        ship2->getTrait<Model::Oriented>()->setOrientation(Model::Orientation(::Ogre::Quaternion(::Ogre::Degree(-90),::Ogre::Vector3::UNIT_Y))) ;

        Kernel::Timer timer ;
        Kernel::Timer global_timer ;

        while (global_timer.getSecond() < 10)
        {
          ship2->call(Model::Laser::Fire) ;
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }
      }

    }
  }
}

