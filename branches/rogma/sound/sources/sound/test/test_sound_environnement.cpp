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

#include <OgreQuaternion.h>

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
#include <model/orientation.h>
#include <model/listener.h>
#include <model/mobile.h>
#include <model/engine.h>
#include <model/force.h>
#include <model/background_sound.h>
#include <model/sound_environnement.h>
#include <model/collision.h>

#include <sound/sound.h>
#include <sound/test/test_sound_environnement.h>

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Sound::Test::TestSoundEnvironnement) ;

namespace ProjetUnivers {
  namespace Sound {
    namespace Test {

      void TestSoundEnvironnement::basicTest()
      {
        /*!
          - build a SoundEnvironnement
          - build an Engine in this environnement
          - build a listener in the same environnement   
          - change a parent and listen the sound continue with just a little artefact between the close and init
        */
      
        Model::init() ;
        
        Kernel::Object* system = Model::createObject("system") ;
        Model::addTrait(system, new Model::Positionned()) ;
        Model::addTrait(system, new Model::Oriented()) ;

        Kernel::Object* listener = Model::createObject(system) ;
        Model::addTrait(listener,new Model::Listener()) ;
        Model::addTrait(listener,new Model::Positionned()) ;
        Model::addTrait(listener,new Model::Oriented(Model::Orientation(Ogre::Quaternion(1.0, 0.0, 10.0, 0.0)))) ;
        Model::addTrait(listener,new Model::Mobile());
        
        Kernel::Object* engine = Model::createObject(system) ;
        Model::addTrait(engine,new Model::Engine(Model::Force::Newton(10,10,10))) ;
        Model::addTrait(engine,new Model::Positionned()) ;
        Model::addTrait(engine,new Model::Oriented(Model::Orientation(Ogre::Quaternion(1.0, 0.0, -10.0, 0.0)))) ;
        Model::addTrait(engine,new Model::Mobile());
        
        /// build a sound viewpoint        
        Sound::init() ;
        Sound::build(listener, system) ;
        
        
        Kernel::Timer timer ;
        
        while (timer.getSecond() <= 3)
        {
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;
          Model::update(elapsed) ;
          Sound::update() ;
        }
        
        Kernel::Object* env = Model::createObject(system) ;
        Model::SoundEnvironnement* soundEnv = new Model::SoundEnvironnement() ;
//        soundEnv->setDensity(0.5) ;
//        soundEnv->setDiffusion(1.0) ;
//        soundEnv->setGain(0.5) ;
//        soundEnv->setGainHF(1.0) ;
//        soundEnv->setDecayTime(2.0) ;
//        soundEnv->setDecayHFRatio(1.1) ;
//        soundEnv->setReflexionsGain(1.0) ;
//        soundEnv->setReflexionsDelay(2.0) ;
//        soundEnv->setLateReverbGain(1.0) ;
//        soundEnv->setLateReverbDelay(2.5) ;
        Model::addTrait(env, soundEnv) ;
        Model::changeParent(engine,env) ;
        
        while (timer.getSecond() <= 6)
        {
          float seconds = timer.getSecond() ;
          Model::Duration elapsed(Model::Duration::Second(seconds)) ;
          Model::update(elapsed) ;
          Sound::update() ;
        } 

        Sound::close();
        Model::close();
        
      }

      void TestSoundEnvironnement::setUp() 
      {
      }
      
      void TestSoundEnvironnement::tearDown() 
      {
      }
      

    }
  }
}

