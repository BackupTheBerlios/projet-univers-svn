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

#include <sound/implementation/sound_emitter.h>

#include <openal/alut.h>

#include <OgreVector3.h>
#include <OgreQuaternion.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

      	SoundEmitter::SoundEmitter()
      	:source(NULL)
      	{}
      				
  	  	void SoundEmitter::initSound()
  	  	{
  	  		if(!this->source)
  	  		{
  	  			//TODO catch les problèmes mémoires pour récupérer un buffer ou une source
  	  			alGenSources(1,&this->source)
	  	  		//TODO lecture format audio divers , pour l'instant test wav
  	  			//TODO conversion filename de logique vers physique, pour l'instant on test avec
  	  			//directement name = physique
  	  			const char* name = const_cast<char*>(this->getFileName().c_str())
	  	  		ALuint buffer = alutCreateBufferFromFile(name);
	  	  	    if(buffer == AL_NONE)
	  	  	    {
	  	  	    	throw OpenAL::Exception("[OpenAL] Can't generate a buffer");   
	  	  	    }
	  	  	    
	  	  	    alSourcei(this->source, AL_BUFFER, buffer);
	  	  	    
	  	  	    //TODO vérifier la conversion brutale de bool vers AL_TRUE et AL_FALSE de type ALuint
	  	  	    alSourcei(this->source, AL_LOOPING, this->isLooping())
	  	  	    alSourcei(this->source, AL_SOURCE_RELATIVE, this->isListenerRelative())
	  	  	    
	  	  	    this->updateSource();	    
  	  		}	
  	  	}
  	  	
  	  	void SoundEmitter::startSound()
  	  	{
  	  		if(!this->source)
  	  		{
  	  			this->initSound()
  	  		}
  	  		// TODO ajouter dans un gestionnaire pour les events
  	  		alSourcePlay(this->source);
  	  	}
  	  	
  	  	void SoundEmitter::updateSource()
  	  	{ 	  		  	  	    
  	  		Ogre::Vector3 position = this->getPosition()->Meter()
  	  		alSource3f(this->source, AL_POSITION, (float)position->x, (float)position->y, (float)position->z);
  	  		  	  	    
  	  		Ogre::Quaternion orientation = this->getOrientation()->getQuaternion();
  	  		alSource3f(this->source, AL_DIRECTION, (float)orientation->x, (float)orientation->y, (float)orientation->z)
  	  		  	  	    
  	  		Ogre::Vector3 speed = this->getSpeed()->MeterPerSecond();
  	  		alSource3f(this->source, AL_VELOCITY, (float)speed->x, (float)speed->y, (float)speed->z)
  	  		  	  	    
  	  		alSourcef(this->source, AL_CONE_OUTER_ANGLE, this->getOuterAngle());
  	  		alSourcef(this->source, AL_CONE_INNER_ANGLE, this->getInnerAngle());
  	  		alSourcef(this->source, AL_MAX_DISTANCE, this->getMaxDistance());
  	  		
	  		ALuint state;
	  		alGetSourcei(this->source, AL_SOURCE_STATE, state);
  	  		
  	  		if(this->isActive && state == AL_STOPPED) this->startSound();
  	  		if(!this->isActive && state == AL_PLAYING) this->stopSound();
  	  	}
  	  	
  	  	void SoundEmitter::stopSound()
  	  	{
  	  		if(this->source)
  	  		{
  	  			alSourceStop(this->source);
  	  		}
  	  		//TODO voir si on libère dès l'arrêt car on peut relancer ( suivant le rapport consommation mémoire/ perf)
  	  	}
  	        
  	    void SoundEmitter::deleteSound()
  	    {
  	    	if(this->source)
  	    	{
  	    		ALuint buffer;
  	    		alGetSourcei(this->source, AL_BUFFER, &buffer);
  	    		alDeleteSources(1,&this->source);
  	    		alDeleteBuffers(1,&buffer);
  	    		
  	    	}
  	    }
      
      }
    }
  }
}
