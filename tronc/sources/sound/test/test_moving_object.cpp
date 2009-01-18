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
#include <AL/al.h>
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/timer.h>
#include <kernel/log.h>
#include <kernel/string.h>

#include <model/model.h>
#include <model/duration.h>
#include <model/positionned.h>
#include <model/position.h>
#include <model/oriented.h>
#include <model/listener.h>
#include <model/mobile.h>
#include <model/engine.h>
#include <model/force.h>

#include <sound/sound.h>
#include <sound/implementation/engine.h>
#include <sound/implementation/openal/engine.h>
#include <sound/test/test_moving_object.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Sound::Test::TestMovingObject) ;

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Test
    {

      namespace 
      {
        const float delta = 0.001 ;
        
        void checkSourcePosition(ALuint source,
                                 const float& expected_position_x,
                                 const float& expected_position_y,
                                 const float& expected_position_z)
        {
          float position_x ;
          float position_y ;
          float position_z ;
          
          alGetSource3f(source,AL_POSITION,&position_x,&position_y,&position_z) ;
          CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_position_x,position_x,delta) ;
          CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_position_y,position_y,delta) ;
          CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_position_z,position_z,delta) ;
        }
      }
      
      void TestMovingObject::basicTest()
      {
        std::cerr << "TestMovingObject::basicTest" << std::endl ;
        std::cerr.flush() ;
        /*!
          - build a engine
          - build a listener
          - move the engine position
          - update the module for streaming during 10secondes
          -destroy all and clean sound module
        */

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestMovingObject::basicTest")) ;
        model->init() ;
        
        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positionned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        Model::Positionned* listenerPos = new Model::Positionned();
        listener->addTrait(listenerPos) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());

        Kernel::Object* engine = system->createObject() ;
        engine->addTrait(new Model::Engine(Model::Force::Newton(10,10,10))) ;
        Model::Positionned* enginePos = new Model::Positionned(Model::Position::Meter(0,0,-50));
        engine->addTrait(enginePos);
        engine->addTrait(new Model::Oriented()) ;
        engine->addTrait(new Model::Mobile());
        
        Kernel::ViewPoint* viewpoint = model->getViewPoint<Implementation::OpenAL::RealWorldViewPoint>() ;
        
        ALuint engine_source = 
          engine->getTrait<Implementation::Engine>()
                ->getView<Implementation::OpenAL::Engine>(viewpoint)->m_source ;
        
        Kernel::Timer global_timer ;
        Kernel::Timer timer ;

        float expected_position_x = 0 ;
        float expected_position_y = 0 ;
        float expected_position_z = -50 ;

        checkSourcePosition(engine_source,
                            expected_position_x,
                            expected_position_y,
                            expected_position_z) ;
        
        /// moving on Z axis
        while (global_timer.getSecond() <= 1)
        {
          enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0,0,0.005));
          expected_position_z += 0.005 ;
          checkSourcePosition(engine_source,
                              expected_position_x,
                              expected_position_y,
                              expected_position_z) ;
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
        
        /// moving on X axis
        global_timer.reset();
        enginePos->setPosition(Model::Position::Meter(-50,0,0));
        
        expected_position_x = -50 ;
        expected_position_y = 0 ;
        expected_position_z = 0 ;
        
        checkSourcePosition(engine_source,
                            expected_position_x,
                            expected_position_y,
                            expected_position_z) ;
        
        while (global_timer.getSecond() <= 1)
        {
          enginePos->setPosition(enginePos->getPosition()+Model::Position::Meter(0.005,0,0));
          expected_position_x += 0.005 ;
          checkSourcePosition(engine_source,
                              expected_position_x,
                              expected_position_y,
                              expected_position_z) ;
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
        
        /// moving on Y axis
        global_timer.reset();
        enginePos->setPosition(Model::Position::Meter(0,-50,0));
        
        expected_position_x = 0 ;
        expected_position_y = -50 ;
        expected_position_z = 0 ;
        
        checkSourcePosition(engine_source,
                            expected_position_x,
                            expected_position_y,
                            expected_position_z) ;
        
        while (global_timer.getSecond() <= 1)
        {
          enginePos->setPosition(enginePos->getPosition()+Model::Position::Meter(0,0.005,0));
          expected_position_y += 0.005 ;
          checkSourcePosition(engine_source,
                              expected_position_x,
                              expected_position_y,
                              expected_position_z) ;
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
        
        /// moving on X axis listener and source
        global_timer.reset();
        enginePos->setPosition(Model::Position::Meter(0,0,-100));
        
        expected_position_x = 0 ;
        expected_position_y = 0 ;
        expected_position_z = -100 ;
        
        checkSourcePosition(engine_source,
                            expected_position_x,
                            expected_position_y,
                            expected_position_z) ;
        
        float listener_position_x ;
        float listener_position_y ;
        float listener_position_z ;

        float expected_listener_position_x = 0 ;
        float expected_listener_position_y = 0 ;
        float expected_listener_position_z = 0 ;
        
        while (global_timer.getSecond() <= 1)
        {
          listenerPos->setPosition(listenerPos->getPosition()+ Model::Position::Meter(0,0,-0.005));
          expected_listener_position_z -= 0.005 ;
          
          alGetListener3f(AL_POSITION,&listener_position_x,&listener_position_y,&listener_position_z) ;
          CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_listener_position_x,listener_position_x,delta) ;
          CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_listener_position_y,listener_position_y,delta) ;
          CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_listener_position_z,listener_position_z,delta) ;
          
          enginePos->setPosition(enginePos->getPosition()+ Model::Position::Meter(0,0,0.005));
          expected_position_z += 0.005 ;
          checkSourcePosition(engine_source,
                              expected_position_x,
                              expected_position_y,
                              expected_position_z) ;
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
        
        InternalMessage("Sound","after sound close") ;
      }

      void TestMovingObject::moveParentSource()
      {
        std::cerr << "TestMovingObject::moveParentSource" << std::endl ;
        std::cerr.flush() ;

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestMovingObject::basicTest")) ;
        model->init() ;
        
        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positionned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        Model::Positionned* listenerPos = new Model::Positionned();
        listener->addTrait(listenerPos) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());
        
        Kernel::Object* ship = system->createObject() ;
        Model::Positionned* ship_positionned = new Model::Positionned(Model::Position::Meter(0,0,-50));
        ship->addTrait(ship_positionned);
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile());
        
        Kernel::Object* engine = ship->createObject() ;
        engine->addTrait(new Model::Engine(Model::Force::Newton(10,10,10))) ;
        
        Kernel::ViewPoint* viewpoint = model->getViewPoint<Implementation::OpenAL::RealWorldViewPoint>() ;
        CPPUNIT_ASSERT(engine->getTrait<Implementation::Engine>()
                             ->getView<Implementation::OpenAL::Engine>(viewpoint)) ;
        
        ALuint engine_source = 
          engine->getTrait<Implementation::Engine>()
                ->getView<Implementation::OpenAL::Engine>(viewpoint)->m_source ;
        
        Kernel::Timer global_timer ;
        Kernel::Timer timer ;
        
        float expected_position_x = 0 ;
        float expected_position_y = 0 ;
        float expected_position_z = -50 ;

        checkSourcePosition(engine_source,
                            expected_position_x,
                            expected_position_y,
                            expected_position_z) ;

        ship_positionned->setPosition(ship_positionned->getPosition()+Model::Position::Meter(0,0,-0.01));
        
        expected_position_z -= 0.01 ;

        checkSourcePosition(engine_source,
                            expected_position_x,
                            expected_position_y,
                            expected_position_z) ;
        
      }

      void TestMovingObject::moveParentAndSourceHasPosition()
      {
        std::cerr << "TestMovingObject::moveParentAndSourceHasPosition" << std::endl ;
        std::cerr.flush() ;

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestMovingObject::moveParentAndSourceHasPosition")) ;
        model->init() ;
        
        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positionned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        Model::Positionned* listenerPos = new Model::Positionned();
        listener->addTrait(listenerPos) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());
        
        Kernel::Object* ship = system->createObject() ;
        Model::Positionned* ship_positionned = new Model::Positionned(Model::Position::Meter(0,0,-50));
        ship->addTrait(ship_positionned);
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile());
        
        Kernel::Object* engine = ship->createObject() ;
        engine->addTrait(new Model::Engine(Model::Force::Newton(10,10,10))) ;
        engine->addTrait(new Model::Positionned()) ;
        
        Kernel::ViewPoint* viewpoint = model->getViewPoint<Implementation::OpenAL::RealWorldViewPoint>() ;
        CPPUNIT_ASSERT(engine->getTrait<Implementation::Engine>()
                             ->getView<Implementation::OpenAL::Engine>(viewpoint)) ;
        
        ALuint engine_source = 
          engine->getTrait<Implementation::Engine>()
                ->getView<Implementation::OpenAL::Engine>(viewpoint)->m_source ;
        
        Kernel::Timer global_timer ;
        Kernel::Timer timer ;
        
        float expected_position_x = 0 ;
        float expected_position_y = 0 ;
        float expected_position_z = -50 ;

        checkSourcePosition(engine_source,
                            expected_position_x,
                            expected_position_y,
                            expected_position_z) ;

        ship_positionned->setPosition(ship_positionned->getPosition()+Model::Position::Meter(0,0,-1));
        
        expected_position_z -= 1 ;

        checkSourcePosition(engine_source,
                            expected_position_x,
                            expected_position_y,
                            expected_position_z) ;
      }

      void TestMovingObject::moveParentAndListenerHasPosition()
      {
        std::cerr << "TestMovingObject::moveParentAndListenerHasPosition" << std::endl ;
        std::cerr.flush() ;

        // we construct a complete system
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestMovingObject::moveParentAndListenerHasPosition")) ;
        model->init() ;
        
        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positionned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener_ship = system->createObject() ;
        Model::Positionned* listener_ship_positionned = new Model::Positionned();
        listener_ship->addTrait(listener_ship_positionned) ;
        
        Kernel::Object* listener = listener_ship->createObject() ;
        listener->addTrait(new Model::Positionned()) ;
        listener->addTrait(new Model::Listener()) ;
        listener->addTrait(new Model::Oriented()) ;
        listener->addTrait(new Model::Mobile());
        
        Kernel::Object* ship = system->createObject() ;
        Model::Positionned* ship_positionned = new Model::Positionned(Model::Position::Meter(0,0,-50));
        ship->addTrait(ship_positionned);
        ship->addTrait(new Model::Oriented()) ;
        ship->addTrait(new Model::Mobile());
        
        Kernel::Object* engine = ship->createObject() ;
        engine->addTrait(new Model::Engine(Model::Force::Newton(10,10,10))) ;
        engine->addTrait(new Model::Positionned()) ;
        
        Kernel::Timer global_timer ;
        Kernel::Timer timer ;
        
        float listener_position_x ;
        float listener_position_y ;
        float listener_position_z ;

        float expected_listener_position_x = 0 ;
        float expected_listener_position_y = 0 ;
        float expected_listener_position_z = 0 ;

        alGetListener3f(AL_POSITION,&listener_position_x,&listener_position_y,&listener_position_z) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_listener_position_x,listener_position_x,delta) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_listener_position_y,listener_position_y,delta) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_listener_position_z,listener_position_z,delta) ;

        listener_ship_positionned->setPosition(listener_ship_positionned->getPosition()+Model::Position::Meter(0,0,-1));
        
        expected_listener_position_z -= 1 ;

        alGetListener3f(AL_POSITION,&listener_position_x,&listener_position_y,&listener_position_z) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_listener_position_x,listener_position_x,delta) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_listener_position_y,listener_position_y,delta) ;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(expected_listener_position_z,listener_position_z,delta) ;
      }
      
    }
  }
}

