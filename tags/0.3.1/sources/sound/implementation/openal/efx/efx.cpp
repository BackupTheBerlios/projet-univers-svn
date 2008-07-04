/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Morgan GRIGNARD Mathieu ROGER                      *
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
#include <kernel/log.h>
#include <model/sound_environnement.h>
#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/efx/efx.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        namespace EFX {
          
          // Effect objects
          LPALGENEFFECTS alGenEffects = NULL;
          LPALDELETEEFFECTS alDeleteEffects = NULL;
          LPALISEFFECT alIsEffect = NULL;
          LPALEFFECTI alEffecti = NULL;
          LPALEFFECTIV alEffectiv = NULL;
          LPALEFFECTF alEffectf = NULL;
          LPALEFFECTFV alEffectfv = NULL;
          LPALGETEFFECTI alGetEffecti = NULL;
          LPALGETEFFECTIV alGetEffectiv = NULL;
          LPALGETEFFECTF alGetEffectf = NULL;
          LPALGETEFFECTFV alGetEffectfv = NULL;

          //Filter objects
          LPALGENFILTERS alGenFilters = NULL;
          LPALDELETEFILTERS alDeleteFilters = NULL;
          LPALISFILTER alIsFilter = NULL;
          LPALFILTERI alFilteri = NULL;
          LPALFILTERIV alFilteriv = NULL;
          LPALFILTERF alFilterf = NULL;
          LPALFILTERFV alFilterfv = NULL;
          LPALGETFILTERI alGetFilteri = NULL;
          LPALGETFILTERIV alGetFilteriv = NULL;
          LPALGETFILTERF alGetFilterf = NULL;
          LPALGETFILTERFV alGetFilterfv = NULL;

          // Auxiliary slot object
          LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots = NULL;
          LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots = NULL;
          LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot = NULL;
          LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti = NULL;
          LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv = NULL;
          LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf = NULL;
          LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv = NULL;
          LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti = NULL;
          LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv = NULL;
          LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf = NULL;
          LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv = NULL;
          
          ALint attributs[4] = { 0 };
          
          ALint* getParameters()
          {
            //Context creation with a request of 4 auxiliary slot for effect
            //but it  isn't possible without a sound card, just 1 will be create
            attributs[0] = ALC_MAX_AUXILIARY_SENDS;
            attributs[1] = 4;
            
            return attributs ;
          }
          
          /// Init and return parameters.
          void init(ALCdevice* device)
          {
            //Search for effect extension
            if (alcIsExtensionPresent(device, "ALC_EXT_EFX") == AL_FALSE)
            {
              ErrorMessage("[OpenAL] No effect extension found") ;
              return ;
            }

            //See if the EFX version follow the requirement
            ALint minVersion;
            ALint maxVersion;
            alcGetIntegerv(device, ALC_EFX_MINOR_VERSION, 1, &minVersion);
            alcGetIntegerv(device, ALC_EFX_MAJOR_VERSION, 1, &maxVersion);
            
            /// @todo test EFX requirement when we will have some
            if (false)
            {
              InformationMessage("Sound","[OpenAL] Context don't support the required EFX version") ;
              return ;
            } 
                  
            //Get functions pointer, must be done after making context current
            alGenEffects = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");
            alDeleteEffects = (LPALDELETEEFFECTS )alGetProcAddress("alDeleteEffects");
            alIsEffect = (LPALISEFFECT )alGetProcAddress("alIsEffect");
            alEffecti = (LPALEFFECTI)alGetProcAddress("alEffecti");
            alEffectiv = (LPALEFFECTIV)alGetProcAddress("alEffectiv");
            alEffectf = (LPALEFFECTF)alGetProcAddress("alEffectf");
            alEffectfv = (LPALEFFECTFV)alGetProcAddress("alEffectfv");
            alGetEffecti = (LPALGETEFFECTI)alGetProcAddress("alGetEffecti");
            alGetEffectiv = (LPALGETEFFECTIV)alGetProcAddress("alGetEffectiv");
            alGetEffectf = (LPALGETEFFECTF)alGetProcAddress("alGetEffectf");
            alGetEffectfv = (LPALGETEFFECTFV)alGetProcAddress("alGetEffectfv");
            alGenFilters = (LPALGENFILTERS)alGetProcAddress("alGenFilters");
            alDeleteFilters = (LPALDELETEFILTERS)alGetProcAddress("alDeleteFilters");
            alIsFilter = (LPALISFILTER)alGetProcAddress("alIsFilter");
            alFilteri = (LPALFILTERI)alGetProcAddress("alFilteri");
            alFilteriv = (LPALFILTERIV)alGetProcAddress("alFilteriv");
            alFilterf = (LPALFILTERF)alGetProcAddress("alFilterf");
            alFilterfv = (LPALFILTERFV)alGetProcAddress("alFilterfv");
            alGetFilteri = (LPALGETFILTERI )alGetProcAddress("alGetFilteri");
            alGetFilteriv = (LPALGETFILTERIV )alGetProcAddress("alGetFilteriv");
            alGetFilterf = (LPALGETFILTERF )alGetProcAddress("alGetFilterf");
            alGetFilterfv = (LPALGETFILTERFV )alGetProcAddress("alGetFilterfv");
            alGenAuxiliaryEffectSlots = (LPALGENAUXILIARYEFFECTSLOTS)alGetProcAddress("alGenAuxiliaryEffectSlots");
            alDeleteAuxiliaryEffectSlots = (LPALDELETEAUXILIARYEFFECTSLOTS)alGetProcAddress("alDeleteAuxiliaryEffectSlots");
            alIsAuxiliaryEffectSlot = (LPALISAUXILIARYEFFECTSLOT)alGetProcAddress("alIsAuxiliaryEffectSlot");
            alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI)alGetProcAddress("alAuxiliaryEffectSloti");
            alAuxiliaryEffectSlotiv = (LPALAUXILIARYEFFECTSLOTIV)alGetProcAddress("alAuxiliaryEffectSlotiv");
            alAuxiliaryEffectSlotf = (LPALAUXILIARYEFFECTSLOTF)alGetProcAddress("alAuxiliaryEffectSlotf");
            alAuxiliaryEffectSlotfv = (LPALAUXILIARYEFFECTSLOTFV)alGetProcAddress("alAuxiliaryEffectSlotfv");
            alGetAuxiliaryEffectSloti = (LPALGETAUXILIARYEFFECTSLOTI)alGetProcAddress("alGetAuxiliaryEffectSloti");
            alGetAuxiliaryEffectSlotiv = (LPALGETAUXILIARYEFFECTSLOTIV)alGetProcAddress("alGetAuxiliaryEffectSlotiv");
            alGetAuxiliaryEffectSlotf = (LPALGETAUXILIARYEFFECTSLOTF)alGetProcAddress("alGetAuxiliaryEffectSlotf");
            alGetAuxiliaryEffectSlotfv = (LPALGETAUXILIARYEFFECTSLOTFV)alGetProcAddress("alGetAuxiliaryEffectSlotfv");

            if (!(alGenEffects && alDeleteEffects && alIsEffect && alEffecti && alEffectiv && alEffectf &&
              alEffectfv && alGetEffecti && alGetEffectiv && alGetEffectf && alGetEffectfv && alGenFilters &&
              alDeleteFilters && alIsFilter && alFilteri && alFilteriv && alFilterf && alFilterfv &&
              alGetFilteri && alGetFilteriv && alGetFilterf && alGetFilterfv && alGenAuxiliaryEffectSlots &&
              alDeleteAuxiliaryEffectSlots && alIsAuxiliaryEffectSlot && alAuxiliaryEffectSloti &&
              alAuxiliaryEffectSlotiv && alAuxiliaryEffectSlotf && alAuxiliaryEffectSlotfv &&
              alGetAuxiliaryEffectSloti && alGetAuxiliaryEffectSlotiv && alGetAuxiliaryEffectSlotf &&
              alGetAuxiliaryEffectSlotfv))
            {
              InformationMessage("Sound","[OpenAL] Device doesn't support all EFX functions") ;           
            }
            
            //Get the real number of auxiliary slot available
            ALint auxSlotNumber;
            alcGetIntegerv(device, ALC_MAX_AUXILIARY_SENDS, 1, &auxSlotNumber);
            if(auxSlotNumber < 1)
            {
              InformationMessage("Sound","[OpenAL] Context hasn't enough effect slot") ;
              return ;
            }
            
          }
          
          /// close the module.
          void close()
          {
            
          }
          void createEffect(ALuint* effect,ALuint* auxEffectSlot)
          {
            InformationMessage("Sound","OpenAL::EFX::createEffect enter") ; 
            alGenAuxiliaryEffectSlots(1,auxEffectSlot) ;
            InformationMessage("Sound","OpenAL::SoundEmitter::gen slot: " + getErrorString(alGetError())) ; 
            alGenEffects(1,effect) ;
            InformationMessage("Sound","OpenAL::EFX::createEffect leave") ; 
          }
          
          void destroyEffect(ALuint* effect,ALuint* auxEffectSlot)
          {
            alDeleteEffects(1,effect) ;
            alDeleteAuxiliaryEffectSlots(1,auxEffectSlot) ;
          }
          
          void changeEffect(ALuint effect,ALuint auxEffectSlot,Model::SoundEnvironnement* env)
          {
            if (!env)
              return ;
            
            alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB) ;
            alEffectf(effect, AL_REVERB_DENSITY, env->getDensity()) ;
            alEffectf(effect, AL_REVERB_DIFFUSION, env->getDiffusion()) ;
            alEffectf(effect, AL_REVERB_GAIN, env->getGain()) ;
            alEffectf(effect, AL_REVERB_GAINHF, env->getGainHF()) ;
            alEffectf(effect, AL_REVERB_DECAY_TIME, env->getDecayTime()) ;
            alEffectf(effect, AL_REVERB_DECAY_HFRATIO, env->getDecayHFRatio()) ;
            alEffectf(effect, AL_REVERB_REFLECTIONS_GAIN, env->getReflexionsGain()) ;
            alEffectf(effect, AL_REVERB_REFLECTIONS_DELAY, env->getReflexionsDelay()) ;
            alEffectf(effect, AL_REVERB_LATE_REVERB_GAIN, env->getLateReverbGain()) ;
            alEffectf(effect, AL_REVERB_LATE_REVERB_DELAY, env->getLateReverbDelay()) ;
            alEffectf(effect, AL_REVERB_ROOM_ROLLOFF_FACTOR, env->getRoomRollofFactor()) ;
            alEffectf(effect, AL_REVERB_AIR_ABSORPTION_GAINHF, env->getAirAbsorptionGainHF()) ;
            alEffectf(effect, AL_REVERB_DECAY_HFLIMIT, env->getDecayHFLimit()) ;
            alAuxiliaryEffectSloti(auxEffectSlot, AL_EFFECTSLOT_EFFECT, effect) ;
          }
          
          void applyEffectToSource(ALuint source,ALuint auxEffectSlot)
          {
            alSource3i(source, AL_AUXILIARY_SEND_FILTER, auxEffectSlot, 0, 0) ;
          }
          
        }
      }
    }
  }
}
