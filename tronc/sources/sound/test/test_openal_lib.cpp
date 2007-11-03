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
#include <AL/alut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <kernel/string.h>
#include <kernel/log.h>

#include <kernel/timer.h>
#include <sound/test/test_openal_lib.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Sound::Test::TestOpenALLib) ;

namespace ProjetUnivers {
  namespace Sound {
    namespace Test {

      void TestOpenALLib::basicTest()
      {
      	/*!
          - init openal directly to see if the lib work
        */
        
        ALCdevice* device ;
        ALCcontext* context ;
        device = alcOpenDevice(NULL);
        if(device == NULL)
        {
          ErrorMessage("[OpenAL] No sound device found");
          return ;
        }

        context = alcCreateContext(device, NULL);
        if(context == NULL)
        {
          ErrorMessage("[OpenAL] Can't create contexte");
          return ;
        }

        alcMakeContextCurrent(context);
        ALenum error ;
        
        if((error = alGetError()) != AL_NO_ERROR)
        {
          ErrorMessage("[OpenAL] init error:" + error);
          return ;
        }
        
        InformationMessage("Al status " + Kernel::toString(alGetError())) ;
        
        ALboolean alut_error = alutInitWithoutContext(NULL,NULL) ;
        if (alut_error ==AL_FALSE)
        {
          ErrorMessage("[ALUT] init error:" + std::string(alutGetErrorString(alutGetError())));
          return ;
         
        }
        
        ALuint source ;
        alGenSources(1,&source) ;
        ALuint buffer = alutCreateBufferFromFile("sound.wav");
        if(buffer == AL_NONE)
        {
          ErrorMessage("[OpenAL] Can't generate a buffer" 
                       + std::string(alutGetErrorString(alutGetError())));
          return ;
        }
        
        alSourcei(source, AL_BUFFER, buffer);
        
        alSourcePlay(source) ;

        Kernel::Timer timer ;
        int i = 0 ;
        while(timer.getSecond() <= 2.0)
        {
          ++i ;
        }          
        std::cout << i << std::endl  ;
        
      }

      void TestOpenALLib::setUp() 
      {
      }
      
      void TestOpenALLib::tearDown() 
      {
      }
      

    }
  }
}

