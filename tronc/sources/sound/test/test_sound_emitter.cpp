/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/timer.h>
#include <kernel/log.h>

#include <model/model.h>
#include <model/universe.h>
#include <model/positioned.h>
#include <model/stellar_system.h>
#include <model/listener.h>
#include <model/oriented.h>
#include <model/observer.h>
#include <model/active.h>
#include <model/player.h>
#include <model/mobile.h>
#include <model/throttle.h>
#include <model/engine.h>

#include <sound/implementation/openal/real_world_view_point.h>
#include <sound/implementation/openal/engine.h>
#include <sound/test/test_sound_emitter.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Sound::Test::TestSoundEmitter);

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Test
    {

      void TestSoundEmitter::createListenerAfterSource()
      {
        InternalMessage("Sound","entering TestSoundEmitter::createListenerAfterSource") ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model());
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positioned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* ship = Model::createShip(system) ;

        Implementation::Engine* engine = ship->getChild<Implementation::Engine>() ;
        CPPUNIT_ASSERT(engine) ;
        Implementation::OpenAL::Engine* engine_view = engine->getView<Implementation::OpenAL::Engine>(model->getViewPoint<Implementation::OpenAL::RealWorldViewPoint>()) ;
        CPPUNIT_ASSERT(engine_view) ;

        // because listener is created after
        CPPUNIT_ASSERT(!engine_view->isActive()) ;

        CPPUNIT_ASSERT(!engine_view->getSource()) ;

        Kernel::Object* listener = createObserver(ship) ;

        // now active
        CPPUNIT_ASSERT(engine_view->isActive()) ;

        ship->getChild<Model::Throttle>()->set(100) ;
        // hacky : setting throttle does not update engine so we force update
        CPPUNIT_ASSERT(ship->getChild<Model::Engine>()) ;
        ship->getChild<Model::Engine>()->getAppliedForce() ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(10,0,0)) ;

        ALint state;
        alGetSourcei(engine_view->getSource(),AL_SOURCE_STATE,&state) ;
        CPPUNIT_ASSERT_EQUAL(AL_PLAYING,state) ;

        ALfloat gain ;
        alGetSourcef(engine_view->getSource(),AL_GAIN,&gain) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1,gain,0.1) ;
      }

      void TestSoundEmitter::makeSourceActive()
      {
        InternalMessage("Sound","entering TestSoundEmitter::makeSourceActive") ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model());
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positioned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* ship = Model::createShip(system) ;

        Implementation::Engine* engine = ship->getChild<Implementation::Engine>() ;
        CPPUNIT_ASSERT(engine) ;
        Implementation::OpenAL::Engine* engine_view = engine->getView<Implementation::OpenAL::Engine>(model->getViewPoint<Implementation::OpenAL::RealWorldViewPoint>()) ;
        CPPUNIT_ASSERT(engine_view) ;

        // make ship far away
        float distance_in_meter = engine_view->getMaxDistance() ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(2*distance_in_meter,0,0)) ;

        // because listener is created after
        CPPUNIT_ASSERT(!engine_view->isActive()) ;

        CPPUNIT_ASSERT(!engine_view->getSource()) ;

        Kernel::Object* listener = createObserver(system) ;

        // still inactive
        CPPUNIT_ASSERT(!engine_view->isActive()) ;

        ship->getChild<Model::Throttle>()->set(100) ;
        // hacky : setting throttle does not update engine so we force update
        CPPUNIT_ASSERT(ship->getChild<Model::Engine>()) ;
        ship->getChild<Model::Engine>()->getAppliedForce() ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(2*distance_in_meter,0,0)) ;

        // still inactive
        CPPUNIT_ASSERT(!engine_view->isActive()) ;

        // make active
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,0)) ;

        CPPUNIT_ASSERT(engine_view->isActive()) ;

        ALint state;
        alGetSourcei(engine_view->getSource(),AL_SOURCE_STATE,&state) ;
        CPPUNIT_ASSERT_EQUAL(AL_PLAYING,state) ;

        ALfloat gain ;
        alGetSourcef(engine_view->getSource(),AL_GAIN,&gain) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1,gain,0.1) ;
      }

      void TestSoundEmitter::makeSourceInactive()
      {
        InternalMessage("Sound","entering TestSoundEmitter::makeSourceInactive") ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model());
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positioned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = createObserver(system) ;

        Kernel::Object* ship = Model::createShip(system) ;
        ship->getChild<Model::Throttle>()->set(100) ;
        CPPUNIT_ASSERT(ship->getChild<Model::Engine>()) ;
        ship->getChild<Model::Engine>()->getAppliedForce() ;

        Implementation::Engine* engine = ship->getChild<Implementation::Engine>() ;
        CPPUNIT_ASSERT(engine) ;
        Implementation::OpenAL::Engine* engine_view = engine->getView<Implementation::OpenAL::Engine>(model->getViewPoint<Implementation::OpenAL::RealWorldViewPoint>()) ;
        CPPUNIT_ASSERT(engine_view) ;

        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(10,0,0)) ;

        // active
        CPPUNIT_ASSERT(engine_view->isActive()) ;
        CPPUNIT_ASSERT(engine_view->getSource()) ;
        ALint state;
        alGetSourcei(engine_view->getSource(),AL_SOURCE_STATE,&state) ;
        CPPUNIT_ASSERT_EQUAL(AL_PLAYING,state) ;
        ALfloat gain ;
        alGetSourcef(engine_view->getSource(),AL_GAIN,&gain) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1,gain,0.1) ;

        // becomes inactive
        ship->getChild<Model::Throttle>()->set(100) ;
        // hacky : setting throttle does not update engine so we force update
        float distance_in_meter = engine_view->getMaxDistance() ;
        ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(2*distance_in_meter,0,0)) ;
        CPPUNIT_ASSERT(ship->getChild<Model::Engine>()) ;
        ship->getChild<Model::Engine>()->getAppliedForce() ;

        CPPUNIT_ASSERT(!engine_view->isActive()) ;
        CPPUNIT_ASSERT(!engine_view->getSource()) ;
      }

    }
  }
}
