/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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

namespace ProjetUnivers 
{
  namespace Input 
  {
    namespace Implementation 
    {
      namespace OIS 
      {
      
        class Keyboard ;
        class Joystick ;
        class Mouse ;
        
        /// Start all OIS related stuff.
        void start() ;
        
        /// Terminate all OIS related stuff.
        void terminate() ;
        
        /// Intitialize.
        void init() ;
       
        /// Terminate.
        void close() ;

        /// Capture input and update. 
        void update() ;
        
        /// Access to keyboard.
        ::OIS::Keyboard* getOISKeyboard() ;

        /// Access to keyboard.
        Keyboard* getKeyboard() ;

        /// Access to mouse.
        Mouse* getMouse() ;

        /// Access to joystick.
        Joystick* getJoystick() ;

      }
    }
  }
}
