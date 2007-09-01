/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD                                      *
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

#include <sound/implementation/openal.h>

namespace ProjetUnivers {
  namespace Sound {
  	namespace Implementation {
      namespace OpenAL {
    
      	void init() 
      	{
      	  InternalMessage("Sound::OpenAL::init entering") ;
      	  ALCdevice *device = alcOpenDevice(NULL);
      	  if(device == NULL)
      	  {
      		throw OpenAL::Exception("[OpenAL] No sound device found");
      	  }

      	  ALCcontext *context = alcCreateContext(device, NULL);
      	  if(context == NULL)
      	  {
      		throw OpenAL::Exception("[OpenAL] Can't create contexte");
      	  }

      	  alcMakeContextCurrent(context);
      	  
      	  if((error = alGetError()) != AL_NO_ERROR)
      	  {
      		throw OpenAL::Exception("[OpenAL] init error:" + error);
      	  }
      			
      	  InternalMessage("Sound::OpenAL::init leaving") ;
	    }
    
	    void close()
	    {
	      InternalMessage("Sound::OpenAL::close entering") ;
	      
	      // Désactivation du contexte
	      alcMakeContextCurrent(NULL);

	      // Destruction du contexte
	      alcDestroyContext(this->context);

	      // Fermeture du device
	      alcCloseDevice(this->device);
	      
	      InternalMessage("Sound::OpenAL::close leaving") ;
	    }
	
	    void update()
	    {
	      //TODO voir les besoins pour les streams
	    }
      }
  	}
  }
}

