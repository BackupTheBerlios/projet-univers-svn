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
#include <iostream>
#include <kernel/string.h>
#include <kernel/log.h>
#include <display/display_input.h>
#include <input/implementation/ois/keyboard.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
      namespace OIS {
      
        Keyboard::Keyboard()
        {} 
        
        bool Keyboard::keyPressed(const ::OIS::KeyEvent &e)    
        {
          addRealKeyButtonPressed(e.key) ;
          m_keycode_to_text[e.key] = e.text ;
          return true ;
        }
        
        bool Keyboard::keyReleased(const ::OIS::KeyEvent &e)
        {
          addRealKeyButtonReleased(e.key) ;
          return true ;
        }
       
        
        Model::PlayerConfiguration::InputEvent Keyboard::buildEvent(const int& code) const
        {
          return Model::PlayerConfiguration::InputEvent::key(code) ;
        }
        
        unsigned int Keyboard::getText(const ::OIS::KeyCode& code) const
        {
          return m_keycode_to_text.find(code)->second ;
        }
        
      }
    }
  }
}

