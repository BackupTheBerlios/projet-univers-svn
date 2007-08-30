/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#ifndef PU_SOUND_EMITTER_H_
#define PU_SOUND_EMITTER_H_

#include <kernel/trait.h>

#include <model/name.h>
#include <model/position.h>
#include <model/orientation.h>
#include <model/speed.h>

namespace ProjetUnivers {
  namespace Model {
    
    /// An objects that can emit a sound must extends this trait
    /*!
      For example : engine...
    */
    class SoundEmitter : public Kernel::Trait 
    {
    public:
      
      /// Constructor by default.
      SoundEmitter() ;
      
      //TODO constructor if we didn't authorized the three setters
      /// Constructor with the options that must not be change after initialisation
      SoundEmitter(const Name& sound, const bool& loop, const bool& listenerRelative)
      
      /// Copy constructor
      SoundEmitter(const SoundEmitter&) ;
      
      //TODO Authorized or not, in openal it's possible to change if its a looping sound, we just add the new sound at the buffer's end
      /// Set the sound's filename
      void setSoundFileName(const Name& sound) ;
      
      /// Get the sound's filename
      Name getSoundFileName() const ;
      
      //TODO Authorized or not to change in activity, openal support this
      /// Specify if the sound must loop or is an event
      void setLooping(const bool& loop);
      
      /// Indicate if the sound is looping
      bool isLooping() const ;
      
      /// Indicate if the source is active now considering damages or other elements
      virtual bool isActive() const ;
      
      //TODO Authorized or not to change in activity, openal support this
      // but the implementation of getPosition is specific to one relative point
      /// Specify if the source is relative to the world or the listener
      void setListenerRelative(const bool& listenerRelative)
      
      /// Indicate if the source is relative to the world or the listener
      bool isListenerRelative() const;
      
      /// Get the object's position relative to the world or the listener
      virtual Position getPosition() const ;
      
      /// Get the object's orientation relative to the world or the listener
      virtual Orientation getOrientation() const ;
      
      /// Get the object's speed relative to the world or listener
      virtual Speed getSpeed() const ;
      
      /// Set the cone's outer angle base
      void setOuterAngle(const float& sound) ;

      /// Get the calculate cone's outer angle
      virtual float getOuterAngle() const ;
      
      /// Set the cone's inner angle base
      void setInnerAngle(const float& sound) ;
      
      /// Get the calculate cone's inner angle
      virtual float getInnerAngle() const ;
      
      /// Set the base distance where there is no more sound
      void setMaxDistance(const float& sound) ;
      
      /// Get the calculate max distance
      virtual float getMaxDistance() const;
 
    private:
    
    // TODO add const for the tree if no setters
      Name soundFileName ;
      bool looping;
      bool listenerRelative;
      float outerAngle ;
      float innerAngle ;
      float maxDistance ;
      
    };
    
    
  }
}

#endif /*PU_SOUND_EMITTER_H_*/
