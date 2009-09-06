/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Morgan GRIGNARD Mathieu ROGER                 *
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
#include <OgreStringConverter.h>
#include <kernel/string.h>
#include <kernel/log.h>

#include <model/positioned.h>
#include <model/oriented.h>
#include <model/mobile.h>

#include <sound/sound.h>
#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/extension.h>
#include <sound/implementation/openal/reader.h>
#include <sound/implementation/openal/sound_environnement.h>
#include <sound/implementation/openal/sound_emitter.h>

#include <OgreVector3.h>
#include <OgreQuaternion.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        SoundEmitter::SoundEmitter()
        : m_auxEffectSlot(0),
          m_reader(0),
          m_posInFile(0),
          m_posInBuffer(0)
        {}

        void SoundEmitter::initSound(Kernel::ViewPoint* viewpoint)
        {
          InformationMessage("Sound", "SoundEmitter::initSound entering") ;
          if (!m_reader)
          {
            InformationMessage("Sound", "SoundEmitter::initSound real") ;
            m_reader = getManager()->createReader(getSoundFileName(),
                                                  isEvent(),
                                                  m_posInFile,
                                                  m_posInBuffer) ;

            alSourcei(getSource(),AL_SOURCE_RELATIVE,AL_FALSE) ;
            updateSource(viewpoint) ;
          }
          InformationMessage("Sound", "SoundEmitter::initSound leaving") ;
        }

        void SoundEmitter::startSound(Kernel::ViewPoint* viewpoint)
        {
          if (!getSource())
          {
            initSound(viewpoint) ;
          }
          alSourcePlay(getSource());
        }

        void SoundEmitter::updateSource(Kernel::ViewPoint* viewpoint)
        {
          ALint state;
          alGetSourcei(getSource(),AL_SOURCE_STATE,&state) ;

          if (!isActive() && state == AL_PLAYING)
          {
            stopSound();
          }
          else
          {
            /// @todo If parameters are never changed move them to init
            alSourcef(getSource(), AL_GAIN, getGain()) ;
            alSourcef(getSource(), AL_REFERENCE_DISTANCE, getRefDistance());
            alSourcef(getSource(), AL_MAX_DISTANCE, getMaxDistance());
            alSourcef(getSource(), AL_ROLLOFF_FACTOR, getRolloffFactor());

            Ogre::Vector3 position = getPosition().Meter() ;

            InternalMessage("Sound","SoundEmitter::updateSource position=" + ::Ogre::StringConverter::toString(position)) ;

            alSource3f(getSource(),AL_POSITION,(float)position.x,(float)position.y,(float)position.z) ;

            Ogre::Vector3 speed = getSpeed().MeterPerSecond();
            InternalMessage("Sound","SoundEmitter::updateSource speed=" + ::Ogre::StringConverter::toString(position)) ;
            alSource3f(getSource(),AL_VELOCITY,(float)speed.x,(float)speed.y,(float)speed.z) ;

            // update Environment Effect

            Model::SoundEnvironnement* env = getObject()->getParent<Model::SoundEnvironnement>() ;
            if (env)
            {
              SoundEnvironnement* envView =
                  env->getView<SoundEnvironnement>(viewpoint) ;
              if (envView)
              {
                ALuint auxEffectSlot = envView->getAuxEffectSlot() ;
                //SoundEnvironnement has changed
                if (auxEffectSlot != m_auxEffectSlot)
                {
                  m_auxEffectSlot = auxEffectSlot;
                  EFX::applyEffectToSource(getSource(), m_auxEffectSlot) ;
                  InformationMessage("Sound", "update add reverb") ;
                }
              }
              else
              {
                InformationMessage("Sound", "no envView") ;
              }
            }
            else
            {
              InformationMessage("Sound", "no env") ;
            }

          }

          if (isActive() && (state == AL_STOPPED || state == AL_INITIAL))
          {
            startSound(viewpoint);
          }
        }

        void SoundEmitter::changeParentSource(Kernel::ViewPoint* viewpoint)
        {

          InformationMessage("Sound", "SoundEmitter::changeParent : enter") ;

          Model::SoundEnvironnement* env = getObject()->getParent<Model::SoundEnvironnement>() ;
          if (env)
          {
            SoundEnvironnement* envView =
                env->getView<SoundEnvironnement>(viewpoint) ;
            if (envView)
            {
              ALuint auxEffectSlot = envView->getAuxEffectSlot() ;
              //SoundEnvironnement has changed
              if (auxEffectSlot != m_auxEffectSlot)
              {
                m_auxEffectSlot = auxEffectSlot;
                // @todo see filter parameter for occlusion , exclusion case
                EFX::applyEffectToSource(getSource(), m_auxEffectSlot) ;
                InformationMessage("Sound", "update add reverb") ;
              }
              else
              {
                InformationMessage("Sound", "same reverb") ;
              }
            }
            else
            {
              InformationMessage("Sound", "no envView") ;
            }
          }
          else
          {
            InformationMessage("Sound", "no environment") ;
          }

          InformationMessage("Sound", "SoundEmitter::changeParent : leaving") ;
        }

        void SoundEmitter::stopSound()
        {
          if (getSource())
          {
            stopSourceAndUnQueueBuffers(getSource()) ;
          }
        }

        void SoundEmitter::deleteSound()
        {
          InformationMessage("Sound", "SoundEmitter::deleteSound : enter") ;
          if (!isEvent())
          {
            alGetSourcei(getSource(), AL_SAMPLE_OFFSET, &m_posInBuffer) ;
            stopSound() ;
          }
          m_auxEffectSlot = 0;
          InformationMessage("Sound", "SoundEmitter::deleteSound : leaving") ;
        }

        Model::Position SoundEmitter::getPosition() const
        {
          return Model::getRelativePosition(getObject(),getObject()->getRoot()) ;
        }

        Model::Orientation SoundEmitter::getOrientation() const
        {
          return Model::getRelativeOrientation(getObject(),getObject()->getRoot()) ;
        }

        Model::Speed SoundEmitter::getSpeed() const
        {
          Model::Mobile* mobile = getObject()->getParent<Model::Mobile>();
          if (mobile)
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
          return 360;
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

        ALuint SoundEmitter::getSource() const
        {
          return m_reader->getSource() ;
        }

      }
    }
  }
}
