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
#include <kernel/string.h>
#include <kernel/log.h>
#include <action/action.h>
#include <display/display_input.h>
#include <input/implementation/keyboard.h>

namespace ProjetUnivers {
  namespace Input {
   
    namespace Implementation {
      
      Keyboard::Keyboard()
      : m_controled_object(NULL)
      {} 
      
      Keyboard::~Keyboard()
      {}
  
      bool Keyboard::keyPressed(const OIS::KeyEvent &e)    
      {

        switch(e.key)
        {
        case OIS::KC_RETURN:
          Action::add("Sortie") ;
          break ;
        case OIS::KC_F:
          
          if (m_controled_object)
          {
            m_controled_object->call("fire") ;
          }
          break ;
        default:
          
          Display::injectKey(e.key) ;
          break ;
          
//        case OIS::KC_UP:
//          Action::add("Haut") ;
//          break ;
//
//        case OIS::KC_DOWN:
//          Action::add("Bas") ;
//          break ;
//
//        case OIS::KC_LEFT:
//          Action::add("Gauche") ;
//          break ;
//          
//        case OIS::KC_RIGHT:
//          Action::add("Droite") ;
//          break ;
//
//        case OIS::KC_C:
//           InternalMessage("Input","Input : added create object") ;
//           Action::add("CreerObject") ;
//          break ;
//
//        case OIS::KC_D:
//          InternalMessage("Input","Input : added destroy object") ;
//          Action::add("destroyObject") ;
//          break ;
//
//        case OIS::KC_M:
//          InternalMessage("Input","Input : added move object") ;
//          Action::add("moveObject") ;
//          break ;
//
//
//        default:
//          break ;
        }
        return true ;
      }
      
      bool Keyboard::keyReleased(const OIS::KeyEvent &e)
      {
        return true ;
      }

      void Keyboard::setControledObject(Kernel::Object* i_object)
      {
        m_controled_object = i_object ;
      }

    }
  }
}

