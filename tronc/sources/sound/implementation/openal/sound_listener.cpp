/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD                                 *
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

#include <sound/implementation/sound_listener.h>

#include <OgreVector3.h>
#include <OgreQuaternion.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

      	SoundListener::SoundListener(){}
  	  	
  	  	void SoundListener::updateListener()
  	  	{ 	  		  	  	    
  	  		Ogre::Vector3 position = this->getPosition()->Meter()
  	  		alListener3f(AL_POSITION, (float)position->x, (float)position->y, (float)position->z);
  	  		  	  	    
  	  		Ogre::Quaternion orientation = this->getOrientation()->getQuaternion();
  	  		alListener3f(AL_DIRECTION, (float)orientation->x, (float)orientation->y, (float)orientation->z)
  	  		  	  	    
  	  		Ogre::Vector3 speed = this->getSpeed()->MeterPerSecond();
  	  		alListener3f(AL_VELOCITY, (float)speed->x, (float)speed->y, (float)speed->z)
  	  		
  	  		alListenerf(AL_GAIN,)
  	  	}
      
      }
    }
  }
}
