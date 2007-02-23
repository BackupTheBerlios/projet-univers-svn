/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#include <input/implementation/keyboard.h>

namespace ProjetUnivers {
  namespace Input {
   
    namespace Implementation {
      
      Keyboard::Keyboard()
      {} 
      
      Keyboard::~Keyboard()
      {}
  
      bool Keyboard::keyPressed(const OIS::KeyEvent &e)    
      {
        
        /// log
        Kernel::Log::InternalMessage(
              (std::string("bouton presse timestamp = ") + 
              toString(e.timeStamp)).c_str() ) ;

        /// pour l'instant : on sort si c'est entrée
        switch(e.key)
        {
        case OIS::KC_RETURN:
          Action::add("Sortie") ;
          break ;
          
        case OIS::KC_UP:
          Action::add("Haut") ;
          break ;

        case OIS::KC_DOWN:
          Action::add("Bas") ;
          break ;

        case OIS::KC_LEFT:
          Action::add("Gauche") ;
          break ;
          
        case OIS::KC_RIGHT:
          Action::add("Droite") ;
          break ;

        case OIS::KC_C:
           Kernel::Log::InternalMessage("Input : added create object") ;
           Action::add("CreerObject") ;
          break ;

        case OIS::KC_D:
           Kernel::Log::InternalMessage("Input : added destroy object") ;
          Action::add("destroyObject") ;
          break ;



        default:
          break ;
        }
        return true ;
      }
      
      bool Keyboard::keyReleased(const OIS::KeyEvent &e)
      {
        return true ;
      }
    }
  }
}

