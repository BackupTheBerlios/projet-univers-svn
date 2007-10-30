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
#include <kernel/timer.h>
#include <kernel/log.h>

#include <sound/sound.h>
#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/ogg_reader.h>
#include <sound/implementation/openal/wav_reader.h>
#include <sound/test/test_effect.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Sound::Test::TestEffect) ;

namespace ProjetUnivers {
  namespace Sound {
    namespace Test {

      void TestEffect::basicTest()
      {
        /*!
          - create a source and try different effect on it
        */
 
        Sound::init() ;
        
        ALuint source;
        alGenSources(1,&source) ;
        Implementation::OpenAL::Reader* reader = new Implementation::OpenAL::WavReader(source, "hit.wav", false, 1.1) ;
        reader->onInit() ;
        alSourcePlay(source);
        Kernel::Timer timer ;
        Kernel::Timer bip ;
        
        //build effect slot
        ALuint auxEffectSlot;
        Implementation::OpenAL::alGenAuxiliaryEffectSlots(1, &auxEffectSlot);
        if(alGetError() != AL_NO_ERROR)
        {
            ErrorMessage("[TestEffect] can't build an auxEffectSlot") ;
        }
        
        //build effect
        ALuint effect;
        Implementation::OpenAL::alGenEffects(1, &effect);
        if(alGetError() != AL_NO_ERROR)
        {
            ErrorMessage("[TestEffect] can't build an effect") ;
        }
        
        //configure effect
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
        if (alGetError() != AL_NO_ERROR)
        {
           ErrorMessage("[TestEffect] Reverb Effect not supported");
        }
        else
        {
          Implementation::OpenAL::alEffectf(effect, AL_REVERB_DECAY_TIME, 2.0f);
        }
        
        //link effect to slot effect
        Implementation::OpenAL::alAuxiliaryEffectSloti(auxEffectSlot, AL_EFFECTSLOT_EFFECT, effect);
        if(alGetError() != AL_NO_ERROR)
        {
            ErrorMessage("[TestEffect] can't link an effect to a slot") ;
        }
        
        //create filter
        ALuint filter;
        Implementation::OpenAL::alGenFilters(1, &filter);
        if(alGetError() != AL_NO_ERROR)
        {
            ErrorMessage("[TestEffect] can't build a filter") ;
        }
        Implementation::OpenAL::alFilteri(filter,AL_FILTER_TYPE,AL_FILTER_LOWPASS);
        Implementation::OpenAL::alFilterf(filter, AL_LOWPASS_GAIN, 0.5f);
		Implementation::OpenAL::alFilterf(filter, AL_LOWPASS_GAINHF, 0.5f);
        if(alGetError() != AL_NO_ERROR)
        {
            ErrorMessage("[TestEffect] lowpass filter not supported") ;
        }
        
        
        if (alGetError() == AL_NO_ERROR)
        {
           InformationMessage("[TestEffect] No ERROR");
        }
        
        
        //Normal sound
        while (timer.getSecond() <= 2)
        {
          if(bip.getSecond() > 1)
          {
          	reader->update();
          	bip.reset();
          }
        }
        
         //link source output 0 to effect slot without more filter
        alSource3i(source, AL_AUXILIARY_SEND_FILTER, auxEffectSlot, 0, 0);
        if(alGetError() != AL_NO_ERROR)
        {
            ErrorMessage("[TestEffect] can't link slot to source output") ;
        }
        
        timer.reset();
        //Sound with reverb effect
        while (timer.getSecond() <= 2)
        {
          if(bip.getSecond() > 1)
          {
          	reader->update();
          	bip.reset();
          }
        }
        
        //unlink effect
        alSource3i(source,AL_AUXILIARY_SEND_FILTER,AL_EFFECTSLOT_NULL, 0, 0);
        //link filter
        alSourcei(source, AL_DIRECT_FILTER, filter);
        
        timer.reset();
        //Sound with low pass filter on main output
        while (timer.getSecond() <= 2)
        {
          if(bip.getSecond() > 1)
          {
          	reader->update();
          	bip.reset();
          }
        }
        
        alSource3i(source, AL_AUXILIARY_SEND_FILTER, auxEffectSlot, 0, 0);
        timer.reset();
        //Sound with low pass filter and reverb effect
        while (timer.getSecond() <= 2)
        {
          if(bip.getSecond() > 1)
          {
          	reader->update();
          	bip.reset();
          }
        }
        
      }

      void TestEffect::setUp() 
      {
      }
      
      void TestEffect::tearDown() 
      {
      }
      

    }
  }
}

