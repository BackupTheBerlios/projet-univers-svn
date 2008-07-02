/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#ifndef PU_INPUT_IMPLEMENTATION_JOYSTICK_H_
#define PU_INPUT_IMPLEMENTATION_JOYSTICK_H_

#include <OIS/OISJoyStick.h>
#include <kernel/object.h>
#include <input/implementation/input_object.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      /// Handle joystick.
      class Joystick : public OIS::JoyStickListener, public InputObject
      {
      public:
      
        /// Constructor.
        Joystick(const float& sensibility = 0.1) ;  
        
      /*!
        @name Interface implementation
      */
      // @{
      
        virtual bool buttonPressed(const OIS::JoyStickEvent&,int) ;
        
        virtual bool buttonReleased(const OIS::JoyStickEvent&,int) ;
        
        virtual bool axisMoved(const OIS::JoyStickEvent&,int) ;
        
        virtual bool sliderMoved(const OIS::JoyStickEvent&,int) ;
        
        virtual bool povMoved(const OIS::JoyStickEvent&,int) ;

      // @}
      private:
        
        /// sensibility.
        float m_sensibility ;

      };
    }
  }
}



#endif /*PU_INPUT_IMPLEMENTATION_JOYSTICK_H_*/
