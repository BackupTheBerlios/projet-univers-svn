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
#include <sound/sound.h>
#include <sound/implementation/openal/openal.h>
#include <sound/test/test_openal_init.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Sound::Test::TestOpenALInit);

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Test
    {

      void TestOpenALInit::basicTest()
      {
        std::cerr << "TestOpenALInit::basicTest" << std::endl;
        std::cerr.flush() ;
        /*!
         - just init sound module and show the platform possibilities
         */

        Sound::init() ;

        ALCdevice* device;
        ALCcontext* contexte;
        ALint auxSlotNumber;
        ALint minVersion;
        ALint maxVersion;

        contexte = alcGetCurrentContext();
        device = alcGetContextsDevice(contexte);
        alcGetIntegerv(device, ALC_MAX_AUXILIARY_SENDS, 1, &auxSlotNumber);
        alcGetIntegerv(device, ALC_EFX_MINOR_VERSION, 1, &minVersion);
        alcGetIntegerv(device, ALC_EFX_MAJOR_VERSION, 1, &maxVersion);
        printf(
            "Your system can support :\n -%d aux. effect slot\n -an EFX version between %d and %d\n",
            auxSlotNumber, minVersion, maxVersion);
        printf("Effect supported:\n");

        ALuint effect;
        Implementation::OpenAL::alGenEffects(1, &effect);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Can't build effect\n");
          return;
        }

        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_EAXREVERB);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("EAXReverb: no\n");
        }
        else
        {
          printf("EAXReverb: yes\n");
        }

        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_REVERB);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Reverb: no\n");
        }
        else
        {
          printf("Reverb: yes\n");
        }

        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_CHORUS);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Chorus: no\n");
        }
        else
        {
          printf("Chorus: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_DISTORTION);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Distortion: no\n");
        }
        else
        {
          printf("Distortion: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_ECHO);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Echo: no\n");
        }
        else
        {
          printf("Echo: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_FLANGER);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Flanger: no\n");
        }
        else
        {
          printf("Flanger: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_FREQUENCY_SHIFTER);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Frequency shifter: no\n");
        }
        else
        {
          printf("Frequency shifter: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_VOCAL_MORPHER);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Vocal Morpher: no\n");
        }
        else
        {
          printf("Vocal Morpher: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_PITCH_SHIFTER);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Pitch shifter: no\n");
        }
        else
        {
          printf("Pitch shifter: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_RING_MODULATOR);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Ring modulator: no\n");
        }
        else
        {
          printf("Ring modulator: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_AUTOWAH);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Autowah: no\n");
        }
        else
        {
          printf("Autowah: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_COMPRESSOR);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Comprossor: no\n");
        }
        else
        {
          printf("Comprossor: yes\n");
        }
        Implementation::OpenAL::alEffecti(effect, AL_EFFECT_TYPE,
            AL_EFFECT_EQUALIZER);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Equalizer: no\n");
        }
        else
        {
          printf("Equalizer: yes\n");
        }

        printf("Filter supported:\n");
        ALuint filter;
        Implementation::OpenAL::alGenFilters(1, &filter);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("can't build a filter") ;
        }
        Implementation::OpenAL::alFilteri(filter, AL_FILTER_TYPE,
            AL_FILTER_LOWPASS);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Lowpass: no\n");
        }
        else
        {
          printf("Lowpass: yes\n");
        }
        Implementation::OpenAL::alFilteri(filter, AL_FILTER_TYPE,
            AL_FILTER_HIGHPASS);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Highpass: no\n");
        }
        else
        {
          printf("Highpass: yes\n");
        }
        Implementation::OpenAL::alFilteri(filter, AL_FILTER_TYPE,
            AL_FILTER_BANDPASS);
        if (alGetError() != AL_NO_ERROR)
        {
          printf("Bandpass: no\n");
        }
        else
        {
          printf("Bandpass: yes\n");
        }

        Sound::close();

      }

      void TestOpenALInit::setUp()
      {
      }

      void TestOpenALInit::tearDown()
      {
      }

    }
  }
}

