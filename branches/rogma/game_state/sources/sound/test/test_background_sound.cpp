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
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/timer.h>
#include <kernel/log.h>
#include <kernel/string.h>

#include <model/model.h>
#include <model/listener.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/background_sound.h>
#include <model/collision.h>

#include <sound/sound.h>
#include <sound/test/test_background_sound.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Sound::Test::TestBackgroundSound) ;

namespace ProjetUnivers {
  namespace Sound {
    namespace Test {

      void TestBackgroundSound::basicTest()
      {
        /*!
          - build a background sound object wih a ogg
          - build an event colision with a wav (default sound.wav in OpenAL::colision.cpp code) 
          - build a listener
          - destroy the event  before the end of the sound
          - update the module for streaming during 10secondes
          -destroy all and clean sound module
        */

        // we construct a complete system
        Model::init() ;
        
        Kernel::Object* system = Model::createObject("system") ;
        Model::addTrait(system, new Model::Positionned()) ;
        Model::addTrait(system, new Model::Oriented()) ;

        Kernel::Object* listener = Model::createObject(system) ;
        Model::addTrait(listener,new Model::Listener()) ;
        Model::addTrait(listener,new Model::Positionned()) ;
        Model::addTrait(listener,new Model::Oriented()) ;
        Model::addTrait(listener,new Model::Mobile());

        Kernel::Object* emmiter = Model::createObject(system) ;
        Model::addTrait(emmiter,new Model::BackgroundSound("pu_comm_essai_1.ogg")) ;
        Model::addTrait(emmiter,new Model::Positionned()) ;
        Model::addTrait(emmiter,new Model::Oriented()) ;
        
        
        Kernel::Object* elm1 = Model::createObject(system) ;
        Kernel::Object* elm2 = Model::createObject(system) ;
        Kernel::Object* collision = Model::createObject(system) ;
        const Model::Position& posRef = Model::Position();
        Model::addTrait(collision,new Model::Collision(elm1, elm2, posRef)) ;
        InternalMessage("Sound","fin definition world") ;
        /// build a sound viewpoint        
        Sound::init() ;
        InternalMessage("Sound","after sound init") ;
        Sound::build(listener, system) ;
        InternalMessage("Sound","after sound build") ;
        
        Model::destroyObject(collision) ;
        
        InternalMessage("Sound","after destroy colision") ;
        
        Kernel::Timer timer ;
        int i = 0 ;
        while(timer.getSecond() <= 10.0)
        {
          ++i ;
          Sound::update() ;
        }          
        InternalMessage("Sound","i=" + Kernel::toString(i)) ;
        
       
        Sound::close();
        Model::close();
        
        InternalMessage("Sound","after all close") ;
        
      }

      void TestBackgroundSound::setUp() 
      {
      }
      
      void TestBackgroundSound::tearDown() 
      {
      }
      

    }
  }
}

