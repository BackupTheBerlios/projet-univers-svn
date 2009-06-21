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
#include <AL/al.h>

#include <kernel/log.h>

#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/sound_listener.h>

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

        SoundListener::SoundListener()
        {}
        
        float SoundListener::getGain() const
        {
          return 1.0f;
        }
                             
        Model::Position SoundListener::getPosition() const
        { 
          return Model::getRelativePosition(getObject(),getObject()->getRoot()) ;
        }
                                 
        Model::Orientation SoundListener::getOrientation() const
        {
          return Model::getRelativeOrientation(getObject(),getObject()->getRoot()) ;
        }
                                 
        Model::Speed SoundListener::getSpeed() const
        {
          Model::Mobile* mobile = getObject()->getParent<Model::Mobile>();
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
        
        void SoundListener::updateListener()
        {                           
          Ogre::Vector3 position = this->getPosition().Meter() ;
          alListener3f(AL_POSITION, (float)position.x, (float)position.y, (float)position.z);
          Ogre::Quaternion orientation = this->getOrientation().getQuaternion();

          ALfloat openal_orientation[6] ;
          openal_orientation[0] = orientation.zAxis().x ;
          openal_orientation[1] = orientation.zAxis().y ;
          openal_orientation[2] = orientation.zAxis().z ;
          openal_orientation[3] = orientation.yAxis().x ;
          openal_orientation[4] = orientation.yAxis().y ;
          openal_orientation[5] = orientation.yAxis().z ;
          
          alListenerfv(AL_ORIENTATION, openal_orientation) ; 
                      
          Ogre::Vector3 speed = this->getSpeed().MeterPerSecond();
          alListener3f(AL_VELOCITY, (float)speed.x, (float)speed.y, (float)speed.z) ;
          alListenerf(AL_GAIN,getGain()) ;
        }
      
      }
    }
  }
}
