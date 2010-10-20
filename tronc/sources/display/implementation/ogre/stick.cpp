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
#include <algorithm>
#include <kernel/log.h>

#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/stick.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {
        
//        RegisterView(Ogre::Stick,
//                     Implementation::DisplayedStick,
//                     Ogre::RealWorldViewPoint) ;
        
        
        void Stick::onInit()
        {
          InternalMessage("Display","Display::Stick::onInit Entering") ;

          m_overlay = getOverlay("PU/base/HUD/Stick") ;

          m_cross = m_overlay->getChild("PU/base/HUD/Stick/Cross") ;
          
          onUpdate() ;
          
          m_overlay->show() ;

          InternalMessage("Display","Display::Stick::onInit Leaving") ;
        }
          
        void Stick::onClose()
        {
          InternalMessage("Display","Display::Stick::onClose Entering") ;
          if (m_overlay)
          {
            m_overlay->hide() ;
          }
          InternalMessage("Display","Display::Stick::onClose Leaving") ;
        }
        
        void Stick::onUpdate()
        {
          const float width = m_cross->getWidth() ;
          const float height = m_cross->getHeight() ;
          float x_position = (float)(getTrait<Model::Stick>()->getX())*0.5 ;
          x_position -= width/2 ;
          float y_position = (float)(getTrait<Model::Stick>()->getY())*0.5 ;
          y_position -= height/2 ;
          m_cross->setPosition(x_position,y_position) ;
        }
        
      }
    }
  }
}

