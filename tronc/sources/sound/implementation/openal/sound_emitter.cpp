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
#include <AL/alut.h>

#include <kernel/string.h>
#include <kernel/log.h>

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/sound_emitter.h>


#include <OgreVector3.h>
#include <OgreQuaternion.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        SoundEmitter::SoundEmitter()
        : source(0)
        {}
              
        void SoundEmitter::initSound()
        {
          InternalMessage("SoundEmitter::initSound") ;
          if(!this->source)
          {
            std::string name = getSoundFileName() ;

            //TODO catch les problèmes mémoires pour récupérer un buffer ou une source
            alGenSources((ALsizei)1,&source) ;
            //TODO lecture format audio divers , pour l'instant test wav
            //TODO conversion filename de logique vers physique, pour l'instant on test avec
            //directement name = physique
            
            InformationMessage("Al status " + getErrorString(alGetError())) ;
            InformationMessage("SoundEmitter::initSound Alut status " + std::string(alutGetErrorString(alutGetError()))) ;
            InformationMessage("SoundEmitter::initSound " + name) ;
            m_buffer = alutCreateBufferFromFile(name.c_str());
            if(m_buffer == AL_NONE)
            {
              ErrorMessage("[OpenAL] Can't generate a buffer" 
                           + std::string(alutGetErrorString(alutGetError())));
              return ;
            }
            
            alSourcei(this->source, AL_BUFFER, m_buffer);
            
            //TODO vérifier la conversion brutale de bool vers AL_TRUE et AL_FALSE de type ALuint
            alSourcei(this->source, AL_LOOPING, this->isLooping()) ;
            alSourcei(this->source, AL_SOURCE_RELATIVE, this->isListenerRelative()) ;
            
            this->updateSource();      
          }  
        }
        
        void SoundEmitter::startSound()
        {
          if(!this->source)
          {
            this->initSound() ;
          }
          // TODO ajouter dans un gestionnaire pour les events
          alSourcePlay(this->source);
        }
        
        void SoundEmitter::updateSource()
        {                     
          Ogre::Vector3 position = this->getPosition().Meter() ;
          alSource3f(this->source,
                     AL_POSITION, 
                     (float)position.x, 
                     (float)position.y, 
                     (float)position.z);
                      
          Ogre::Quaternion orientation = this->getOrientation().getQuaternion();

          ALfloat openal_orientation[6] ;
          openal_orientation[0] = orientation.zAxis().x ;
          openal_orientation[1] = orientation.zAxis().y ;
          openal_orientation[2] = orientation.zAxis().z ;
          openal_orientation[3] = orientation.yAxis().x ;
          openal_orientation[4] = orientation.yAxis().y ;
          openal_orientation[5] = orientation.yAxis().z ;
          
          alSourcefv(this->source, 
                     AL_DIRECTION, 
                     openal_orientation) ;
                      
          Ogre::Vector3 speed = this->getSpeed().MeterPerSecond();
          alSource3f(this->source, AL_VELOCITY, (float)speed.x, (float)speed.y, (float)speed.z) ;
                      
          alSourcef(this->source, AL_CONE_OUTER_ANGLE, this->getOuterAngle());
          alSourcef(this->source, AL_CONE_INNER_ANGLE, this->getInnerAngle());
          alSourcef(this->source, AL_MAX_DISTANCE, this->getMaxDistance());
          
          ALint state;
          alGetSourcei(this->source, AL_SOURCE_STATE, &state);
          
//          std::cout << "state =" << state << std::endl ;
//          std::cout << "AL_STOPPED= " << AL_STOPPED << std::endl ; 
//          std::cout << "AL_PLAYING= " << AL_PLAYING << std::endl ; 
          
          if(this->isActive() && (state == AL_STOPPED || state == AL_INITIAL)) 
          {
            this->startSound();
          }

          if(!this->isActive() && state == AL_PLAYING) 
          {
            this->stopSound();
          }
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
            alDeleteSources(1,&this->source);
            alDeleteBuffers(1,&m_buffer);
            
          }
        }
      
      }
    }
  }
}
