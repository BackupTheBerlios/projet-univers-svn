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
#ifndef PU_SOUND_IMPLEMENTATION_SOUND_LISTENER_H_
#define PU_SOUND_IMPLEMENTATION_SOUND_LISTENER_H_

#include <model/position.h>
#include <model/orientation.h>
#include <model/speed.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

    
        /// Common part of object's views that hear sound.
        /*!
          An objects that can hear a sound must have an observer which extends 
          this class. For example : the player...
        */
        class SoundListener
        {
        protected:
        
        /*!
          @name Access methods
          
          These can be redefined by sub classes. They globally describe the 
          listener. 
        */
        // @{
          
          /// Get the master gain between 0 and 1.0
          /*! 
            @todo check the limits
          */
          virtual float getGain() const ;
          
           ///Acces to the object with the trait
          virtual Kernel::Object* getObject() const = 0 ;
            
          /// Get the object's position relative to the world
          virtual Model::Position getPosition() const ;
              
          /// Get the object's orientation relative to the world
          virtual Model::Orientation getOrientation() const ;
              
          /// Get the object's speed relative to the world
          virtual Model::Speed getSpeed() const ;
          
          /// Update the listener informations
          void updateListener() ;
          
        // @}

          /// Default constructor.
          SoundListener() ;
      
        };
      
      }
    }
  }
}

#endif /*PU_SOUND_IMPLEMENTATION_SOUND_LISTENER_H_*/
