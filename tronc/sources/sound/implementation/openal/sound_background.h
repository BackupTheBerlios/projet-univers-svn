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
#ifndef PU_SOUND_IMPLEMENTATION_SOUND_BACKGROUND_H_
#define PU_SOUND_IMPLEMENTATION_SOUND_BACKGROUND_H_

#include <kernel/trait_view.h>

#include <model/sound_background.h>

#include <sound/implementation/openal/sound_emitter.h>
#include <sound/implementation/openal/real_world_view_point.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

    
        /// Sound background observer
      	class BackgroundSound : public Kernel::TraitView<Model::BackgroundSound,RealWorldViewPoint>,
             				 public SoundEmitter
        {
        public:
        	
        	/*!
        	  @name Construction 
        	 */
        	 // @{


        		/// Constructor.
        		BackgroundSound(Model::BackgroundSound*,RealWorldViewPoint*) ;


        	// @}
        	          
            /// Get the sound's filename
  	        virtual Name getSoundFileName() const;
  	      
  	        /// Indicate if the sound is looping
  	        virtual bool isLooping() const;
  	      
  	        /// Indicate if the source is active now considering damages or other elements
  	        virtual bool isActive() const ;
  	      
  	        /// Indicate if the source is relative to the world or the listener
  	        virtual bool isListenerRelative() const;
  	      
  	        /// Get the object's position relative to the world or the listener
  	        virtual Position getPosition() const ;
  	      
  	        /// Get the object's orientation relative to the world or the listener
  	        virtual Orientation getOrientation() const ;
  	      
  	        /// Get the object's speed relative to the world or listener
  	        virtual Speed getSpeed() const ;
  	
  	        /// Get the cone's outer angle
  	        virtual float getOuterAngle() const ;
  	      
  	        /// Get the cone's inner angle
  	        virtual float getInnerAngle() const ;
  	      
  	        /// Get the calculate max distance
  	        virtual float getMaxDistance() const;
        	
        protected:
        /*!
        	@name Updates.
        */
        // @{
        	        
        /// TODO
        void onInit() ;
        	          
        /// TODO
        void onClose() ;
        	          
        /// TODO
        void onUpdate() ;
      
        };
        
        
      
      }
    }
  }
}

#endif /*PU_SOUND_IMPLEMENTATION_SOUND_BACKGROUND_H_*/
