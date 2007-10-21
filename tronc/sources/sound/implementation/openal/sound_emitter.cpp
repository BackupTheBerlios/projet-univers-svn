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
#include <kernel/string.h>
#include <kernel/log.h>

#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/sound_emitter.h>


#include <OgreVector3.h>
#include <OgreQuaternion.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        SoundEmitter::SoundEmitter()
        : m_source(0)
        {}
              
        void SoundEmitter::initSound()
        {
          InternalMessage("SoundEmitter::initSound entering") ;
          if(!m_source)
          {
            alGenSources(1,&m_source) ;
            m_reader = getManager()->createReader(m_source, getSoundFileName().c_str(), isEvent()) ;
            alSourcei(m_source, AL_SOURCE_RELATIVE, AL_FALSE) ;
            updateSource();   
          } 
          InternalMessage("SoundEmitter::initSound leaving") ; 
        }
        
        void SoundEmitter::startSound()
        {
          if(!m_source)
          {
            initSound() ;
          }
          alSourcePlay(m_source);
        }
        
        void SoundEmitter::updateSource()
        {
          InternalMessage("SoundEmitter::updateSource entering") ;
          
		  ALint state;
          alGetSourcei(m_source, AL_SOURCE_STATE, &state);
          
          if(!isActive() && state == AL_PLAYING) 
          {
            stopSound();
          }
          else
          {         
            //TODO voir à l'usage si certains paramètres ne sont jamais changés et transférer vers init()
            alSourcef(m_source, AL_GAIN, getGain()) ;
            alSourcef(m_source, AL_CONE_OUTER_GAIN, getOuterGain()) ;   
            alSourcef(m_source, AL_PITCH, getPitch()) ; 
            alSourcef(m_source, AL_CONE_OUTER_ANGLE, getOuterAngle());
            alSourcef(m_source, AL_CONE_INNER_ANGLE, getInnerAngle());
            alSourcef(m_source, AL_REFERENCE_DISTANCE, getRefDistance());
            alSourcef(m_source, AL_MAX_DISTANCE, getMaxDistance());
            alSourcef(m_source, AL_ROLLOFF_FACTOR, getRolloffFactor());
                            
            Ogre::Vector3 position = getPosition().Meter() ;
            alSource3f(m_source,
                       AL_POSITION, 
                       (float)position.x, 
                       (float)position.y, 
                       (float)position.z);
                   
            Ogre::Quaternion orientation = getOrientation().getQuaternion();

            ALfloat openal_orientation[6] ;
            openal_orientation[0] = orientation.zAxis().x ;
            openal_orientation[1] = orientation.zAxis().y ;
            openal_orientation[2] = orientation.zAxis().z ;
            openal_orientation[3] = orientation.yAxis().x ;
            openal_orientation[4] = orientation.yAxis().y ;
            openal_orientation[5] = orientation.yAxis().z ;
          
            alSourcefv(m_source, 
                       AL_DIRECTION, 
                       openal_orientation) ;
                      
            Ogre::Vector3 speed = getSpeed().MeterPerSecond();
            alSource3f(m_source, AL_VELOCITY, (float)speed.x, (float)speed.y, (float)speed.z) ;        
          }
          
          if(isActive() && (state == AL_STOPPED || state == AL_INITIAL)) 
          {
            startSound();
          }

          InternalMessage("SoundEmitter::updateSource leaving") ; 
        }
        
        void SoundEmitter::stopSound()
        {
          if(m_source)
          {
            alSourceStop(m_source);
          }
        }
            
        void SoundEmitter::deleteSound()
        {
          if(!isEvent())
          {
            stopSound();
            m_reader->setFinish(true);
          }
        }
        
        Model::Position SoundEmitter::getPosition() const
        {
          Model::Positionned* positionned = getObject()->getTrait<Model::Positionned>();
          if(positionned)
          {
            return positionned->getPosition(getManager()->getReference());
          }
          else
          {
          	//default value
            return Model::Position();
          }
        }
              
        Model::Orientation SoundEmitter::getOrientation() const
        {
          Model::Oriented* oriented = getObject()->getTrait<Model::Oriented>();
          if(oriented)
          {
            return oriented->getOrientation(getManager()->getReference());
          }
          else
          {
          	//default value
            return Model::Orientation();
          }
        }
              
        Model::Speed SoundEmitter::getSpeed() const
        {
          Model::Mobile* mobile = getObject()->getTrait<Model::Mobile>();
          if(mobile)
          {
            return mobile->getSpeed();
          }
          else
          {
          	//default value
            return Model::Speed();
          }
        }
        
        bool SoundEmitter::isActive() const
        {
          return true;
        }
        
        float SoundEmitter::getGain() const
        {
        	return 1.0;	
        }
          
        float SoundEmitter::getOuterGain() const
        {
        	return 1.0;	
        }
          
        float SoundEmitter::getPitch() const
        {
        	return 1.0;	
        }
        
        float SoundEmitter::getOuterAngle() const
        {
          return 360 ;
        }
        
        float SoundEmitter::getInnerAngle() const
        {
          return 360;
        }
       
        float SoundEmitter::getRefDistance() const
        {
          return 5.0;
        }
        
        float SoundEmitter::getMaxDistance() const
        {
          return 500.0;
        }
        
        float SoundEmitter::getRolloffFactor() const
        {
          return 1.0;	
        }
      
      }
    }
  }
}
