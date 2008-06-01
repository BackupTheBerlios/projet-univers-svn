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
#include <map>

#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/parameters.h>

#include <sound/implementation/openal/extension.h>
#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/real_world_view_point.h>

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
        
        Manager* manager;
        RealWorldViewPoint*  sound_system ;
        
        namespace 
        {
          // Allowto have only one context at a time
          struct Context
          {
            ALCcontext* context ;
          
            Context()
            : context(NULL)
            {}
            
            ~Context()
            {
              if (context)
                alcDestroyContext(context) ;
            }
          };
        
          Context context ; 
        }
      // @}
        
        
        void init() 
        {
          InternalMessage("Sound","Sound::OpenAL::init entering") ;
          
          //Open a device
          std::string deviceType;
          try
          {
            deviceType = Kernel::Parameters::getValue<std::string>("Sound","SoundDevice") ;
          }
          catch (Kernel::ExceptionKernel e)
          {
            deviceType = "Generic Software" ;
          }
          device = alcOpenDevice(deviceType.c_str());
          if (!device)
          {
            initialised = false ;
            ErrorMessage("[OpenAL] No sound device found") ;
            return ;
          }
          
          /// access to special extensions...
          ALint* extension = EFX::getParameters() ; 
          
          // create only one context
          if (!context.context)
            context.context = alcCreateContext(device,extension) ;
          
          if (!context.context)
          {
            initialised = false ;
            ErrorMessage("[OpenAL] Can't create context") ;
            return ;
          }

          alcMakeContextCurrent(context.context);

          EFX::init(device) ;
          
          //Configure attenuation model
          std::string attenuationModel;
          try
          {
            attenuationModel = Kernel::Parameters::getValue<std::string>("Sound","AttenuationModel") ;
          }
          catch (Kernel::ExceptionKernel e)
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
  
          EFX::close() ;
          
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

