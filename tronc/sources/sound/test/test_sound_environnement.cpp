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
#include <model/positioned.h>
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
#include <model/engine_controler.h>
#include <model/throttle.h>

#include <sound/sound.h>
#include <sound/test/test_sound_environnement.h>

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Sound::Test::TestSoundEnvironnement) ;

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Test
    {

      void TestSoundEnvironnement::basicTest()
      {
        std::cerr << "TestSoundEnvironnement::basicTest"  ;
        std::cerr.flush() ;
        
        /*!
         - build a SoundEnvironnement
         - build an Engine in this environnement
         - build a listener in the same environnement   
         - change a parent and listen the sound continue with just a little artefact between the close and init
         */

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestSoundEnvironnement::basicTest"));
        model->init() ;

        Kernel::Object* system = model->createObject() ;
        system->addTrait(new Model::Positioned()) ;
        system->addTrait(new Model::Oriented()) ;

        Kernel::Object* listener = system->createObject() ;
        listener->addTrait(new Model::Listener()) ;
        listener->addTrait(new Model::Positioned()) ;
        listener->addTrait(new Model::Oriented(Model::Orientation(Ogre::Quaternion(1.0, 0.0, 10.0, 0.0)))) ;
        listener->addTrait(new Model::Mobile());

        Kernel::Object* ship = Model::createShip(system) ;

        ship->getChild<Model::Throttle>()->set(100) ;

        Kernel::Timer timer;
        Kernel::Timer global_timer;

        std::cerr << " normal... " ;
        std::cerr.flush() ;

        while (global_timer.getSecond() <= 3)
        {
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }

        Kernel::Object* env = system->createObject() ;
        Model::SoundEnvironnement* soundEnv = new Model::SoundEnvironnement();
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
        env->addTrait(soundEnv) ;
        ship->changeParent(env) ;

        std::cerr << " switching environement... " << std::endl ;
        std::cerr.flush() ;

        while (global_timer.getSecond() <= 6)
        {
          float seconds = timer.getSecond() ;
          timer.reset() ;
          model->update(seconds) ;
        }
      }

    }
  }
}

