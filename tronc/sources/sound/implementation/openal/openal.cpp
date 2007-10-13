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

#include <sound/implementation/openal/openal.h>

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
        // @}
        
        void init() 
        {
          InternalMessage("Sound::OpenAL::init entering") ;
          device = alcOpenDevice(NULL);
          if(device == NULL)
          {
            initialised = false ;
            ErrorMessage("[OpenAL] No sound device found");
            return ;
          }

          context = alcCreateContext(device, NULL);
          if(context == NULL)
          {
            initialised = false ;
            ErrorMessage("[OpenAL] Can't create contexte");
            return ;
          }

          alcMakeContextCurrent(context);
          ALenum error ;
          
          if((error = alGetError()) != AL_NO_ERROR)
          {
            initialised = false ;
            ErrorMessage("[OpenAL] init error:" + error);
            return ;
          }
          
          InformationMessage("Al status end init openal " + getErrorString(alGetError())) ;

          initialised = true ;
          
          InternalMessage("Sound::OpenAL::init leaving") ;
      }
    
        void close()
        {
          InternalMessage("Sound::OpenAL::close entering") ;
          
          delete manager;
          
          // D�sactivation du contexte
          alcMakeContextCurrent(NULL);
  
          // Destruction du contexte
          alcDestroyContext(context);
  
          // Fermeture du device
          alcCloseDevice(device);
          
          InternalMessage("Sound::OpenAL::close leaving") ;
        }
    
        void update()
        {
          manager->update();
        }
        
        void build(Kernel::Object* listener, Kernel::Object* reference)
        {
        	manager = new Manager(listener, reference);
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
        
        Manager* getManager()
        {
          return manager;
        }
      }
    }
  }
}

