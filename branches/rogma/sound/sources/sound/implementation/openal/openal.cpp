/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD                                    *
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
#include <kernel/string.h>
#include <kernel/parameters.h>

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/real_world_view_point.h>

#include <AL/efx.h>

#include <map>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        
      /*!
        @name Attributes
       */
      // @{
        bool initialised = false ;
        ALCdevice* device ;
        ALCcontext* context ;
        Manager* manager;
        RealWorldViewPoint*  sound_system ;
      // @}
        
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
        
        void init() 
        {
          InternalMessage("Sound","Sound::OpenAL::init entering") ;
          
          //Open a device
          std::string deviceType;
          try
          {
            deviceType = Kernel::Parameters::getValue<std::string>("Sound","SoundDevice") ;
          }
          catch(Kernel::ExceptionKernel e)
          {
          	deviceType = "Generic Software" ;
          }
          device = alcOpenDevice(deviceType.c_str());
          if(device == NULL)
          {
            initialised = false ;
            ErrorMessage("[OpenAL] No sound device found") ;
            return ;
          }
          
          //Search for effect extension
          if (alcIsExtensionPresent(device, "ALC_EXT_EFX") == AL_FALSE)
          {
          	initialised = false ;
            ErrorMessage("[OpenAL] No effect extension found") ;
            return ;
          }
          
          //Context creation with a request of 4 auxiliary slot for effect
          //but it  isn't possible without a sound card, just 1 will be create
          ALint attributs[4] = { 0 };
          attributs[0] = ALC_MAX_AUXILIARY_SENDS;
          attributs[1] = 4;
          
          context = alcCreateContext(device, attributs);
          if(context == NULL)
          {
            initialised = false ;
            ErrorMessage("[OpenAL] Can't create context") ;
            return ;
          }

          alcMakeContextCurrent(context);
          
          //See if the EFX version follow the requirement
          ALint minVersion;
          ALint maxVersion;
          alcGetIntegerv(device, ALC_EFX_MINOR_VERSION, 1, &minVersion);
          alcGetIntegerv(device, ALC_EFX_MAJOR_VERSION, 1, &maxVersion);
          if(false)//TODO test EFX requirement when we will have some
          {
          	initialised = false ;
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

		  if (!(alGenEffects &&	alDeleteEffects && alIsEffect && alEffecti && alEffectiv &&	alEffectf &&
			alEffectfv && alGetEffecti && alGetEffectiv && alGetEffectf && alGetEffectfv &&	alGenFilters &&
			alDeleteFilters && alIsFilter && alFilteri && alFilteriv &&	alFilterf && alFilterfv &&
			alGetFilteri &&	alGetFilteriv && alGetFilterf && alGetFilterfv && alGenAuxiliaryEffectSlots &&
			alDeleteAuxiliaryEffectSlots &&	alIsAuxiliaryEffectSlot && alAuxiliaryEffectSloti &&
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
          	initialised = false ;
            InformationMessage("Sound","[OpenAL] Context hasn't enough effect slot") ;
            return ;
          }

          //Configure attenuation model
          std::string attenuationModel;
          try
          {
            attenuationModel = Kernel::Parameters::getValue<std::string>("Sound","AttenuationModel") ;
          }
          catch(Kernel::ExceptionKernel e)
          {
          	attenuationModel = "INVERSE_DISTANCE_CLAMPED" ;
          }
          std::map<std::string, ALenum> stringToEnum;
          stringToEnum["NONE"] = AL_NONE;
          stringToEnum["INVERSE_DISTANCE"] = AL_INVERSE_DISTANCE;
          stringToEnum["INVERSE_DISTANCE_CLAMPED"] = AL_INVERSE_DISTANCE_CLAMPED;
          stringToEnum["LINEAR_DISTANCE"] = AL_LINEAR_DISTANCE;
          stringToEnum["LINEAR_DISTANCE_CLAMPED"] = AL_LINEAR_DISTANCE_CLAMPED;
          stringToEnum["EXPONENT_DISTANCE"] = AL_EXPONENT_DISTANCE;
          stringToEnum["EXPONENT_DISTANCE_CLAMPED"] = AL_EXPONENT_DISTANCE_CLAMPED;

          alDistanceModel(stringToEnum[attenuationModel]) ;
          
          
          //Verification of initialisation without error  
          initialised = true ;
          
          InternalMessage("Sound","Sound::OpenAL::init leaving with status: " + getErrorString(alGetError())) ;
      }
    
        void close()
        {
          InternalMessage("Sound","Sound::OpenAL::close entering") ;
          
          delete sound_system ;
          delete manager;

          // Désactivation du contexte
          alcMakeContextCurrent(NULL) ;
  
          // Destruction du contexte
          alcDestroyContext(context) ;
  
          // Fermeture du device
          if(!alcCloseDevice(device))
          {
          	InformationMessage("Sound","Sound::OpenAL::close can't close device, some device or buffer remain") ;
          }
          initialised = false ;
          InternalMessage("Sound","Sound::OpenAL::close leaving") ;
        }
    
        void update()
        {
          manager->update() ;
        }
        
        Kernel::ViewPoint* build(Kernel::Object* listener, Kernel::Object* reference)
        {
        	manager = new Manager(listener, reference) ;
        	sound_system = new Implementation::OpenAL::RealWorldViewPoint(listener) ;
        	sound_system->init() ;
        	return sound_system ;
        }
        
        std::string getErrorString(const ALenum& error)
        {
          switch (error)
          {
          case AL_NO_ERROR:
            return "No error" ;
          case AL_INVALID_NAME:
            return "Invalid Name parameter" ;
          case AL_INVALID_ENUM:
            return "Invalid parameter" ;
          case AL_INVALID_VALUE:
            return "Invalid enum parameter value" ;
          case AL_INVALID_OPERATION:
            return "Illegal call" ;
          case AL_OUT_OF_MEMORY:
            return "Unable to allocate memory" ;
          }
        }
        
        Kernel::ViewPoint* getViewPoint()
        {
          return sound_system ;	
        }
        
        Manager* getManager()
        {
          return manager ;
        }
        
      }
    }
  }
}

