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
#include <CEGUI.h>

#include <display/implementation/ogre/menu.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        
        RegisterView(Ogre::Menu, 
                     Model::Menu, 
                     Ogre::RealWorldViewPoint) ;
        
        Menu::Menu(Model::Menu* object,RealWorldViewPoint* viewpoint)
        : Kernel::TraitView<Model::Menu,RealWorldViewPoint>(object,viewpoint), 
          m_window(NULL)
        {
          InternalMessage("Display","Building Ogre::Menu::Menu") ;
        }

        void Menu::onInit()
        {
          InternalMessage("Display","Building Ogre::Menu::onInit entering") ;
          CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLook.scheme");
          CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", "MouseArrow");        
          CEGUI::MouseCursor::getSingleton().show() ;
          
          m_window = CEGUI::WindowManager::getSingleton().loadWindowLayout(
            getTrait()->getFileName()) ;
          
          InternalMessage("Display","Building Ogre::Menu::onInit #1") ;

          CEGUI::System::getSingleton().setGUISheet(m_window) ;
          m_window->setMouseCursor("TaharezLook", "MouseArrow");        
          InternalMessage("Display","Building Ogre::Menu::onInit leaving") ;
        }
        
        void Menu::onClose()
        {
          if (m_window)
          {
             CEGUI::WindowManager::getSingleton().destroyWindow(m_window) ;
             m_window = NULL ;
          }
        }
        
      }
    }
  }
}
