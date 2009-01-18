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
#pragma once

#include <AL/al.h>

#include <kernel/view_point.h>
#include <model/position.h>
#include <model/orientation.h>
#include <model/speed.h>

#include <sound/implementation/openal/openal.h>

namespace ProjetUnivers 
{
  namespace Sound 
  {
    namespace Test
    {
      class TestMovingObject ;
    }
    
    namespace Implementation 
    {
      namespace OpenAL 
      {
        class Reader ;
    
        /// Common part of object's views that emit sound.
        /*! 
          Object's views that can emit a sound must extends this class.
          
          For example : engine...
        */
        class SoundEmitter 
        {
        public:
        
        /*!
          @name Main methods
        */
        // @{

          /// Initialise an openAL source for the sound
          void initSound(Kernel::ViewPoint*) ;
          
          /// Launch the source
          void startSound(Kernel::ViewPoint*) ;
          
          /// Update the source informations
          void updateSource(Kernel::ViewPoint*) ;
          
          /// Update the source environnement
          void changeParentSource(Kernel::ViewPoint*) ;
          
          /// Stop the source
          void stopSound() ;
          
          /// Delete the source
          void deleteSound() ;
        
        // @}
        
        protected:
        
        /*!
          @name Access methods
          
          These can be redefined by sub classes. They globally describe the 
          sound to emit. 
        */
        // @{

          /// Get the sound's filename
          virtual std::string getSoundFileName() const = 0 ;
          
          /// Indicate if the sound is an event.
          /*!
            An event triggers a sound that continues event when event is 
            destroyed. For example Collision sound, Shot sound...
          */
          virtual bool isEvent() const = 0 ;
          
          /// Is the source active now considering damages or other elements.
          virtual bool isActive() const;
          
          ///Acces to the object with the trait
          virtual Kernel::Object* getObject() const = 0 ;
          
          /// Get the object's position relative to the world or the listener
          Model::Position getPosition() const;
              
          /// Get the object's orientation relative to the world or the listener
          Model::Orientation getOrientation() const;
              
          /// Get the object's speed relative to the world or listener
          Model::Speed getSpeed() const;
          
          /// Get the gain. 
          /*!
            @return value between 1 and 0 
                    1 indicates the sound is not attenuated
          */
          virtual float getGain() const;
          
          /// Get the gain after the outerCone limit.
          /*!
            @return value between 1 and 0 
                    1 indicates the sound is not attenuated
          */
          virtual float getOuterGain() const;
          
          /// Change the frequency. 
          /*!
             add 100% or reduce by 50% is equivalent to an octave variation
          */
          virtual float getPitch() const;
          
          /*! 
            @todo: study min/max gain usage with a priority system on sounds
          */
          
          /// Get the cone's inner angle
          virtual float getInnerAngle() const;
          
          /// Get the cone's outer angle
          virtual float getOuterAngle() const;
          
          /// Get the reference distance where the gain equal the value of getGain
          virtual float getRefDistance() const;
          
          /// Get the limit distance
          virtual float getMaxDistance() const;
          
          /// Indicate the factor of attenuation
          virtual float getRolloffFactor() const;
          
          
        // @}

          /// Default constructor.
          SoundEmitter() ;
            
        private:
          
          /// OpenAL source
          ALuint m_source ;
          /// Container of an effect
          ALuint m_auxEffectSlot ;
          
          /// Update the buffers in the stream
          Reader* m_reader ;
          
          /// Position before closing reader.
          /*!
            usefull in the changeParent case to restart at the same point
            --> I do not see why ???
          */
          int m_posInFile ;
          int m_posInBuffer ;
          
          friend class ::ProjetUnivers::Sound::Test::TestMovingObject ; 
        };
      
      }
    }
  }
}
