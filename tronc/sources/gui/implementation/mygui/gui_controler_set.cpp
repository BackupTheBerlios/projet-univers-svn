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
#include <MyGUI.h>
#include <gui/implementation/mygui/mygui.h>
#include <gui/implementation/mygui/gui_controler_set.h>

namespace ProjetUnivers 
{
  namespace GUI 
  {
    namespace Implementation 
    {
      namespace MyGUI 
      {
    
        RegisterControlerSet(GUIControlerSet) ;
        
        GUIControlerSet::GUIControlerSet(Kernel::Model* model)
        : Kernel::ControlerSet(model)
        {}
        
        void GUIControlerSet::onInit()
        {
          start() ;
          ::Ogre::Root::getSingleton().addFrameListener(this) ;
        }

        void GUIControlerSet::onClose()
        {
          ::Ogre::Root::getSingleton().removeFrameListener(this) ;
        }
        
        void GUIControlerSet::simulate(const float& seconds)
        {
          ControlerSet::simulate(seconds) ;
        }
        
        bool GUIControlerSet::frameStarted(const ::Ogre::FrameEvent& evt)
        {
          getWindowManager()->injectFrameEntered(evt.timeSinceLastFrame) ;
          return true ;
        }
      }      
    }
  }
}
