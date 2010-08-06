/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Morgan GRIGNARD                               *
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
#include <iostream>

#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/parameters.h>

#include <sound/implementation/openal/extension.h>
#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/real_world_view_point.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {
        
      /*!
        @name Attributes
       */
      // @{
        
        bool initialised = false ;
        
        std::auto_ptr<Manager> manager;
        
        namespace 
        {
          
          /// Allow a one time initialization.
          /*!
            several initialization tends to cause problem with
            alcMakeContextCurrent
          */
          struct SoundSystem
          {
            
            ALCdevice* device ;
            
            ALCcontext* context ;
            
            SoundSystem()
            {
              if (!manager.get())
                manager.reset(new Manager()) ;

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
              device = alcOpenDevice(NULL);
              if (!device)
              {
                initialised = false ;
                ErrorMessage("[OpenAL] No sound device found") ;
                return ;
              }
              
              /// access to special extensions...
              ALint* extension = EFX::getParameters() ; 
              
              // create only one context
              context = alcCreateContext(device,extension) ;
              
              if (!context)
              {
                initialised = false ;
                ErrorMessage("[OpenAL] Can't create context") ;
                return ;
              }

              alcMakeContextCurrent(context);

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
              
              //Verification of initialization without error
              initialised = true ;
              
              // @todo configure
              manager->cacheRessource("pu_choc.ogg") ;
              manager->cacheRessource("pu_moteur_2.ogg") ;
              manager->cacheRessource("laser.ogg") ;
              manager->cacheRessource("pu_impact_coque.ogg") ;
            }
            
            ~SoundSystem()
            {
              manager.reset(NULL) ;

              // De-activate context
              alcMakeContextCurrent(NULL) ;
      
              EFX::close() ;

              if (context)
                alcDestroyContext(context) ;
              
              // Device closing
              if(!alcCloseDevice(device))
              {
                InformationMessage("Sound","Sound::OpenAL::close can't close device, some device or buffer remain") ;
              }

              initialised = false ;
            }
            
          };
        
        }
        
        std::auto_ptr<SoundSystem> system ;
        
      // @}
        
        
        void init() 
        {
          InternalMessage("Sound","Sound::OpenAL::init entering") ;

          if (!system.get())
            system.reset(new SoundSystem()) ;

          InternalMessage("Sound","Sound::OpenAL::init leaving with status: " + getErrorString(alGetError())) ;
      }
    
        void close()
        {
          InternalMessage("Sound","Sound::OpenAL::close entering") ;
          system.reset(NULL) ;
          InternalMessage("Sound","Sound::OpenAL::close leaving with " + Kernel::toString(getMaximumNumberOfSources())) ;
          InternalMessage("Statistics","Maximum number of sources " + Kernel::toString(getMaximumNumberOfSources())) ;
        }
    
        void update()
        {
          manager->update() ;
        }
        
        void stopSourceAndUnQueueBuffers(const ALuint& source)
        {
          ALint state;
          alGetSourcei(source,AL_SOURCE_STATE,&state) ;
          if (state == AL_PLAYING)
          {
            alSourceStop(source) ;
            ALenum error = alGetError() ; 
            if (error != AL_NO_ERROR)
            {
              ErrorMessage("[OpenAL::OggReader] " + getErrorString(error)) ;
            }
          }
          
          ALint queue_size = 0 ;
          alGetSourcei(source,AL_BUFFERS_QUEUED,&queue_size) ;
          ALenum error = alGetError() ; 
          if (error != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::OggReader] " + getErrorString(error)) ;
          }
          else
          {
            ALuint* buffers = new ALuint[std::max(0,queue_size)];
            alSourceUnqueueBuffers(source,queue_size,buffers) ;
            error = alGetError() ; 
            if (error != AL_NO_ERROR)
            {
              ErrorMessage("[OpenAL::OggReader] " + getErrorString(error)) ;
            }
            delete[] buffers ;
          }
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
          default:
            return "Unknown error" ;
          }
        }

        Manager* getManager()
        {
          return manager.get() ;
        }

        namespace
        {
          int number_of_sources = 0 ;
          int max_number_of_sources = 0 ;
        }

        void addSource()
        {
          ++number_of_sources ;
          if (number_of_sources > max_number_of_sources)
            max_number_of_sources = number_of_sources ;
        }

        void removeSource()
        {
          --number_of_sources ;
        }

        int getMaximumNumberOfSources()
        {
          return max_number_of_sources ;
        }
        
      }
    }
  }
}

