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
        
        RegisterView(Ogre::Stick, 
                     Implementation::DisplayedStick, 
                     Ogre::RealWorldViewPoint) ;
        
        Stick::Stick(Implementation::DisplayedStick* stick,
                     RealWorldViewPoint*             viewpoint) 
        : Kernel::TraitView<Implementation::DisplayedStick,
                            RealWorldViewPoint>(stick,viewpoint),
          m_cross_container(NULL),
          m_cross(NULL)
        {
          InternalMessage("Display","Building Ogre::Stick::Stick") ;
        }
        
        
        void Stick::onInit()
        {
          InternalMessage("Display","Display::Stick::onInit Entering") ;

          m_cross_container = static_cast< ::Ogre::OverlayContainer* >(
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", Utility::getUniqueName())) ;
          getOverlay()->add2D(m_cross_container) ;
          
          m_cross_container->setPosition(0,0) ;
          m_cross_container->setWidth(1) ;
          m_cross_container->setHeight(1) ;
          
          m_cross = 
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", Utility::getUniqueName()) ;
          
          m_cross->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
          m_cross->setVerticalAlignment(::Ogre::GVA_CENTER) ;
          m_cross->setMaterialName("PU/material/reticule") ;
          
          const float size = 0.05 ;
          
          m_cross->setLeft(-size/2) ;
          m_cross->setTop(-size/2) ;
          m_cross->setDimensions(size,size) ;
          
          m_cross_container->_addChild(m_cross) ;
          onUpdate() ;
          
          InternalMessage("Display","Display::Stick::onInit Leaving") ;
        }
          
        void Stick::onClose()
        {
          InternalMessage("Display","Display::Stick::onClose Entering") ;
          if (m_cross_container)
          {
            getOverlay()->remove2D(m_cross_container) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_cross) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_cross_container) ;
            m_cross_container = NULL ;
            m_cross = NULL ;
          }
          InternalMessage("Display","Display::Stick::onClose Leaving") ;
        }
        
        void Stick::onUpdate()
        {
          float x_position = (float)(getTrait<Model::Stick>()->getX())*0.5 ;
          float y_position = (float)(getTrait<Model::Stick>()->getY())*0.5 ;
          m_cross_container->setPosition(x_position,y_position) ;
        }
        
      }
    }
  }
}

