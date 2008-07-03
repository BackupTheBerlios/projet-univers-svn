/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2008 Mathieu ROGER                                 *
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
#ifndef PU_INPUT_IMPLEMENTATION_KEYBOARD_H_
#define PU_INPUT_IMPLEMENTATION_KEYBOARD_H_

#include <list>
#include <OIS/OISKeyboard.h>
#include <kernel/object.h>
#include <input/implementation/input_object.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      /// Keyboard event handler.
      class Keyboard : public OIS::KeyListener, public InputObject
      {
      public:
      
        /// Contructor.
        Keyboard() ;  

        /// Called when a key is pressed.
        virtual bool keyPressed(const OIS::KeyEvent &e) ;    
  
        /// Called when a key is released.
        virtual bool keyReleased(const OIS::KeyEvent &e) ;
      
        const std::list<OIS::KeyEvent>& getKeyPressed() const ;
        const std::list<OIS::KeyEvent>& getKeyReleased() const ;
        
        void clear() ;
        
      private:
        
        std::list<OIS::KeyEvent> m_key_pressed ;
        std::list<OIS::KeyEvent> m_key_released ;
        
      };
    }
  }
}



#endif /*PU_INPUT_IMPLEMENTATION_KEYBOARD_H_*/
