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
#include <iostream>
#include <CEGUI.h>
#include <display/display_input.h>
#include <input/implementation/ois/keyboard.h>
#include <input/implementation/ois/mouse.h>
#include <input/implementation/ois/ois.h>
#include <input/implementation/ois/input_menu.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
      namespace OIS {

        CEGUI::MouseButton convertOgreButtonToCegui(const int& buttonID)
        {
            switch (buttonID)
            {
            case ::OIS::MB_Left:
                return CEGUI::LeftButton;
            case ::OIS::MB_Right:
                return CEGUI::RightButton;
            case ::OIS::MB_Middle:
                return CEGUI::MiddleButton;
            default:
                return CEGUI::LeftButton;
            }
        }      
        
        void InputMenu::simulateInputMenu(const float& seconds)
        {
          CEGUI::System* system = CEGUI::System::getSingletonPtr() ;
          
          if (!system)
            return ;

          if (getKeyboard())
          {
            std::list<int> buttons = getKeyboard()->getKeyButtonPressed() ;
            
            // inject events to cegui...
            for(std::list<int>::const_iterator event = buttons.begin() ;
                event != buttons.end() ;
                ++event)
            {
              system->injectKeyDown(*event) ;
              system->injectChar(getKeyboard()->getText((::OIS::KeyCode)*event)) ;
            }
    
            buttons = getKeyboard()->getKeyButtonReleased() ;
            
            for(std::list<int>::const_iterator event = buttons.begin() ;
                event != buttons.end() ;
                ++event)
            {
              system->injectKeyUp(*event) ;
            }
          }
          if (getMouse())
          {
            
            std::list<int> buttons = getMouse()->getKeyButtonPressed() ;
            for(std::list<int>::const_iterator event = buttons.begin() ;
                event != buttons.end() ;
                ++event)
            {
              system->injectMouseButtonDown(convertOgreButtonToCegui(*event)) ;
            }
    
            buttons = getMouse()->getKeyButtonReleased() ;
            
            for(std::list<int>::const_iterator event = buttons.begin() ;
                event != buttons.end() ;
                ++event)
            {
              system->injectMouseButtonUp(convertOgreButtonToCegui(*event)) ;
            }
            
            Kernel::Percentage mouse_x ;
            Kernel::Percentage mouse_y ;
            
            std::map<Model::PlayerConfiguration::InputAxis,
                     Kernel::Percentage>::const_iterator finder ;
    
            finder = getMouse()->getAxes().find(Model::PlayerConfiguration::InputAxis::mouseAxis(Mouse::X)) ;
            
            if (finder != getMouse()->getAxes().end())
              mouse_x = finder->second ;
    
            finder = getMouse()->getAxes().find(Model::PlayerConfiguration::InputAxis::mouseAxis(Mouse::Y)) ;
            
            if (finder != getMouse()->getAxes().end())
              mouse_y = finder->second ;
            
            unsigned int width ;
            unsigned int height ;
            unsigned int depth ;
            int left ;        
            int top ;
            
            Display::getWindowSize(width,height,depth,left,top) ;
            CEGUI::Point position(width*(float(mouse_x)+0.5),height*(float(mouse_y)+0.5)) ;
            CEGUI::MouseCursor::getSingleton().setPosition(position) ;
          }
        }
      }      
    }
  }
}
