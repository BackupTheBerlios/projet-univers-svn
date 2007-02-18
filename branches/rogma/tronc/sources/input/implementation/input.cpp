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

#include <sstream>
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>
#include <OISInputManager.h>


#include <display/display.h>
#include <input/implementation/keyboard.h>
#include <input/input.h>

namespace ProjetUnivers {
  namespace Input {

    namespace {
      
      /// Detruit les objets locaux
      class OISSystem
      {  
      public:
        /// Gestionnaire OIS d'entr�es
        OIS::InputManager* manager ;
   
        /// Clavier
        OIS::Keyboard* keyboard ;
    
        OISSystem()
        : manager(), keyboard()
        {}
        
        ~OISSystem()
        {
          if (keyboard) 
          {
            manager->destroyInputObject(keyboard);
            keyboard = NULL ;
          }
          if (manager)
          {
            manager->destroyInputSystem() ;
          }
        }  
          
      };
    }

    /// Les �l�ment de OIS
    std::ato_ptr<SystemeOIS*> ois ;
   
    /// Notre �couteur de clavier
    std::ato_ptr<Implementation::Keyboard*> keyboard ;
   
    void init()
    {
      
      if (ois != NULL)
      {
        return ;
      }
      
      ois = new SystemeOIS() ;
      
      OIS::ParamList parameters ;    
      size_t window_hanlde = 0;
      std::ostringstream window_hanlde_name ;

      window_hanlde = Display::getWindowHandle() ;
      window_hanlde_name << (unsigned int) window_hanlde;
      parameters.insert(std::make_pair(
                          std::string("WINDOW"), 
                          window_hanlde_name.str())) ;

      // cr�ation du gestionnaire
      ois->manager = OIS::InputManager::createInputSystem(parameters) ;

      // cr�ation d'un clavier, avec son �couteur
      ois->keyboard = static_cast<OIS::Keyboard*>(
                  ois->manager->createInputObject(OIS::OISKeyboard,true)) ;
    
      keyboard = new Implementation::Keyboard() ;
      
      ois->keyboard->setEventCallback(keyboard.operator->()) ;

    }       
    
    void close()
    {
      ois = NULL ;
     
    }
    
    void Traiter()
    {
      /// capture sur tous les syst�mes d'entr�e
      ois->clavier->capture() ;
    }
    
  }
}



