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
#ifndef PU_SOUND_IMPLEMENTATION_SOUND_EMITTER_H_
#define PU_SOUND_IMPLEMENTATION_SOUND_EMITTER_H_

#include <model/name.h>
#include <model/position.h>
#include <model/orientation.h>
#include <model/speed.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

    
        /// An objects that can emit a sound must have an observer which extends this trait
        /*! TODO regarder si openal est en mètre aussi
          For example : engine...
        */
        class SoundEmitter 
        {
        public:
            /// Get the sound's filename
  	        virtual Name getSoundFileName() const = 0
  	      
  	        /// Indicate if the sound is looping
  	        virtual bool isLooping() const = 0
  	      
  	        /// Indicate if the source is active now considering damages or other elements
  	        virtual bool isActive() const = 0
  	      
  	        /// Indicate if the source is relative to the world or the listener
  	        virtual bool isListenerRelative() const = 0
  	        
  	        /// Get the object's position relative to the world or the listener
  	        virtual Position getPosition() const = 0;
  	            
  	        /// Get the object's orientation relative to the world or the listener
  	        virtual Orientation getOrientation() const = 0;
  	            
  	        /// Get the object's speed relative to the world or listener
  	        virtual Speed getSpeed() const = 0;
  	
  	        /// Get the cone's outer angle
  	        virtual float getOuterAngle() const = 0
  	      
  	        /// Get the cone's inner angle
  	        virtual float getInnerAngle() const = 0
  	      
  	        /// Get the calculate max distance
  	        virtual float getMaxDistance() const = 0
  	        
  	        /// Initialise an openAL source for the sound
  	        void initSound();
  	        
  	        /// Launch the source
  	        void startSound();
  	        
  	        /// Update the source informations
  	        void updateSource();
  	        
  	        /// Stop the source
  	        void stopSound();
  	        
  	        /// Delete the source
  	        void deleteSound();
        	
        protected:
            /// Constructor by default.
            SoundEmitter() ;
            
        private:
        	/// OpenAL source
        	ALuint source;
      
        };
      
      }
    }
  }
}

#endif /*PU_SOUND_IMPLEMENTATION_SOUND_EMITTER_H_*/
