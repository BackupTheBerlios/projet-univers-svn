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


#include <display/display_input.h>
#include <input/implementation/keyboard.h>
#include <input/implementation/mouse.h>
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
        
        OIS::Mouse* m_mouse ;
        
        OISSystem()
        : manager(NULL), 
          keyboard(NULL),
          m_mouse(NULL)
        {}
        
        ~OISSystem()
        {
          if (manager)
          {
            if (keyboard) 
            {
              manager->destroyInputObject(keyboard);
              keyboard = NULL ;
            }
            if (m_mouse)
            {
              manager->destroyInputObject(m_mouse);
            }
            OIS::InputManager::destroyInputSystem(manager) ;
          }
        }  
          
      };
    
      /// Les �l�ment de OIS
      std::auto_ptr<OISSystem> ois ;
     
      /// Notre �couteur de clavier
      std::auto_ptr<Implementation::Keyboard> keyboard_listener ;
      std::auto_ptr<Implementation::Mouse> mouse_listener ;
    
    }

   
    void init()
    {
      
      if (ois.get() != NULL)
      {
        return ;
      }
      
      ois.reset(new OISSystem()) ;
      
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
      keyboard_listener.reset(new Implementation::Keyboard()) ;
      ois->keyboard->setEventCallback(keyboard_listener.get()) ;
      
      ois->m_mouse = static_cast<OIS::Mouse*>(
                  ois->manager->createInputObject(OIS::OISMouse,true)) ;
      mouse_listener.reset(new Implementation::Mouse()) ;      
      ois->m_mouse->setEventCallback(mouse_listener.get()) ;

    }       
    
    void close()
    {
      ois.reset(NULL) ;
     
    }

    void build(Kernel::Object* i_object)
    {
      init() ;
      
      mouse_listener->setControledObject(i_object->getTrait<Model::Oriented>()) ;
    }
        
    void update(const float& i_seconds)
    {
      /// capture sur tous les syst�mes d'entr�e
      mouse_listener->setTimeDelay(i_seconds) ;
      ois->keyboard->capture() ;
      ois->m_mouse->capture() ;
    }
    
  }
}



