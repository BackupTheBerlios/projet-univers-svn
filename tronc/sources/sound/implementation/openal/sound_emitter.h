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
#ifndef PU_SOUND_IMPLEMENTATION_SOUND_EMITTER_H_
#define PU_SOUND_IMPLEMENTATION_SOUND_EMITTER_H_

#include <AL/al.h>

#include <model/position.h>
#include <model/orientation.h>
#include <model/speed.h>

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/reader.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

    
        /// Common part of object's views that emit sound.
        /*! 
          Object's views that can emit a sound must extends this class.
          
          For example : engine...
          
          TODO regarder si openal est en mètre aussi
        */
        class SoundEmitter 
        {
        public:
        
        /*!
          @name Main methods
        */
        // @{

          /// Initialise an openAL source for the sound
          void initSound() ;
          
          /// Launch the source
          void startSound() ;
          
          /// Update the source informations
          void updateSource() ;
          
          /// Stop the source
          void stopSound() ;
          
          /// Delete the source
          void deleteSound() ;
        
        // @}
        
        protected:
        
        /*!
          @name Access methods
          
          These must be redefined by sub classes. They globally describe the 
          sound to emit. 
        */
        // @{

          /// Get the sound's filename
          virtual std::string getSoundFileName() const = 0 ;
          
          /// Indicate if the sound is an event
          virtual bool isEvent() const = 0 ;
          
          /// Indicate if the source is active now considering damages or other elements
          virtual bool isActive() const;
          
          ///Acces to the object with the trait
          virtual Kernel::Object* getObject() const = 0 ;
          
          /// Get the object's position relative to the world or the listener
          Model::Position getPosition() const;
              
          /// Get the object's orientation relative to the world or the listener
          Model::Orientation getOrientation() const;
              
          /// Get the object's speed relative to the world or listener
          Model::Speed getSpeed() const;
          
          /// Get the gain, must be between 1 and 0 , 1 indicate the sound is not attenuated
          virtual float getGain() const;
          
          /// Get the gain after the outerCone limit, must be between 1 and 0 , 1 indicate the sound is not attenuated
          virtual float getOuterGain() const;
          
          /// Change the frequency, add 100% or reduce by 50% is equivalent to an octave variation
          virtual float getPitch() const;
          
          //TODO: voir l'utilisation de Min gain et Max gain avec un système de priorités selon les sons
          
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
          
          /// Update the buffers in the stream
          Reader* m_reader ;
        };
      
      }
    }
  }
}

#endif /*PU_SOUND_IMPLEMENTATION_SOUND_EMITTER_H_*/
