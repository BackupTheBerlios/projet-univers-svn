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
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/observer.h>
#include <model/background_sound.h>

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
          - build a background sound object 
          - a listener
        */

        // we construct a complete system
        Model::init() ;
        
        Kernel::Object* system = Model::createObject("system") ;

        Kernel::Object* listener = Model::createObject(system) ;
        Model::addTrait(listener,new Model::Observer()) ;
        Model::addTrait(listener,new Model::Positionned()) ;
        Model::addTrait(listener,new Model::Oriented()) ;

        Kernel::Object* emmiter = Model::createObject(system) ;
        Model::addTrait(emmiter,new Model::BackgroundSound("sound.wav")) ;
        Model::addTrait(emmiter,new Model::Positionned()) ;
        Model::addTrait(emmiter,new Model::Oriented()) ;
        
        /// build a physical viewpoint        
        Sound::init() ;
        Kernel::ViewPoint* sound = Sound::build(listener) ;
        
        Kernel::Timer timer ;
        int i = 0 ;
        while(timer.getSecond() <= 2.0)
        {
          ++i ;
        }          
        InternalMessage("i=" + Kernel::toString(i)) ;
        
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

