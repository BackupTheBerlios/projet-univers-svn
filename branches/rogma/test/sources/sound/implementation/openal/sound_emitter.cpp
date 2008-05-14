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

#include <sound/sound.h>
#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/sound_environnement_view.h>
#include <sound/implementation/openal/sound_emitter.h>


#include <OgreVector3.h>
#include <OgreQuaternion.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        SoundEmitter::SoundEmitter()
        : m_source(0), m_auxEffectSlot(0), m_reader(0), m_posInFile(0), m_posInBuffer(0)
        {}
              
        void SoundEmitter::initSound()
        {
          InformationMessage("Sound","SoundEmitter::initSound entering") ;
          if(!m_source)
          {
          	InformationMessage("Sound","SoundEmitter::init real") ;
            alGenSources(1,&m_source) ;
            m_reader = getManager()->createReader(m_source, getSoundFileName().c_str(), isEvent(), m_posInFile, m_posInBuffer) ;
            alSourcei(m_source, AL_SOURCE_RELATIVE, AL_FALSE) ;
            updateSource();   
          } 
          InformationMessage("Sound","SoundEmitter::initSound leaving") ; 
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
            
            
            //update Environnement Effect
            
            Model::SoundEnvironnement* env  = getObject()->getParent<Model::SoundEnvironnement>() ;
            if(env)
            {
              SoundEnvironnementView* envView  = env->getView<SoundEnvironnementView>(getViewPoint()) ;
              if(envView)
              {
                ALuint auxEffectSlot = envView->getAuxEffectSlot() ; 
                //SoundEnvironnement has changed
                if(auxEffectSlot != m_auxEffectSlot)
                {
                  m_auxEffectSlot = auxEffectSlot ;
              	  alSource3i(m_source, AL_AUXILIARY_SEND_FILTER, m_auxEffectSlot, 0, 0) ;
              	  InformationMessage("Sound","update add reverb") ;	
                }
              }
              else
              {
                InformationMessage("Sound","no envView") ;	
              }
            }
            else
            {
              InformationMessage("Sound","no env") ;	
            }
            
          }
          
          if(isActive() && (state == AL_STOPPED || state == AL_INITIAL)) 
          {
            startSound();
          }
        }
        
        void SoundEmitter::changeParentSource()
        {
          
          InformationMessage("Sound","SoundEmitter::changeParent : enter") ;
          	
          Model::SoundEnvironnement* env  = getObject()->getParent<Model::SoundEnvironnement>() ;
            if(env)
            {
              SoundEnvironnementView* envView  = env->getView<SoundEnvironnementView>(getViewPoint()) ;
              if(envView)
              {
                ALuint auxEffectSlot = envView->getAuxEffectSlot() ; 
                //SoundEnvironnement has changed
                if(auxEffectSlot != m_auxEffectSlot)
                {
                  m_auxEffectSlot = auxEffectSlot ;
              	  //TODO see filter parameter for occlusion , exclusion case
              	  alSource3i(m_source, AL_AUXILIARY_SEND_FILTER, m_auxEffectSlot, 0, 0) ;
              	  InformationMessage("Sound","update add reverb") ;	
                }
                else
                {
                  InformationMessage("Sound","same reverb") ;	
                }
              }
              else
              {
                InformationMessage("Sound","no envView") ;	
              }
            }
            else
            {
              InformationMessage("Sound","no env") ;	
            }
            
          InformationMessage("Sound","SoundEmitter::changeParent : leaving") ;
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
          InformationMessage("Sound","SoundEmitter::deleteSound : enter") ;
          if(!isEvent())
          {
              alGetSourcei(m_source, AL_SAMPLE_OFFSET, &m_posInBuffer) ;
              stopSound();
              m_posInFile = m_reader->getPos() ;
              m_reader->setFinish(true) ; 
          }
          m_auxEffectSlot = 0 ;
          m_source = 0 ;
          InformationMessage("Sound","SoundEmitter::deleteSound : leaving") ;
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
