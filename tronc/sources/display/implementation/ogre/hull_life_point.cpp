/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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
#include <kernel/log.h>

#include <model/destroyable.h>
#include <display/implementation/head_up_display.h>

#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/hull_life_point.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {

      DeclareDeducedTrait(HullLifePoint,
                          And(HasTrait(Model::Destroyable),
                              HasTrait(Implementation::HeadUpDisplay))) ;
      namespace Ogre
      {

        RegisterView(Ogre::HullLifePoint,
                     Implementation::HullLifePoint,
                     Ogre::RealWorldViewPoint) ;


        namespace
        {
          const float width = 0.24/10 ;
          const float height = 1.04/10 ;
        }

        void HullLifePoint::onInit()
        {
          InternalMessage("Display","Display::HullLifePoint::onInit Entering") ;

          m_hull_container = static_cast< ::Ogre::OverlayContainer* >(
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel","HullLifePoint")) ;
          getOverlay()->add2D(m_hull_container) ;

          m_hull_container->setPosition(0,0) ;
          m_hull_container->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
          m_hull_container->setVerticalAlignment(::Ogre::GVA_CENTER) ;
          m_hull_container->setWidth(1) ;
          m_hull_container->setHeight(1) ;
          m_hull_container->setLeft(-0.1) ;
          m_hull_container->setTop(-height/2) ;

          m_hull =
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", Utility::getUniqueName()) ;

          m_hull->setMaterialName("PU/base/hud/hull_life_point") ;
          m_hull->setDimensions(width,height) ;
          m_hull_container->_addChild(m_hull) ;

          m_hull_interior =
              ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                    "Panel", Utility::getUniqueName()) ;

          m_hull_interior->setMaterialName("PU/base/hud/hull_life_point_interior") ;
          m_hull_container->setDimensions(width,height) ;
          m_hull_container->_addChild(m_hull_interior) ;

          onUpdate() ;

          getOverlay()->show() ;

          InternalMessage("Display","Display::HullLifePoint::onInit Leaving") ;
        }

        void HullLifePoint::onClose()
        {
          InternalMessage("Display","Display::HullLifePoint::removeIndicator Entering") ;
          if (m_hull_container)
          {
            getOverlay()->remove2D(m_hull_container) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_hull) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_hull_container) ;
            m_hull_container = NULL ;
            m_hull = NULL ;
          }
          InternalMessage("Display","Display::HullLifePoint::removeIndicator Leaving") ;
        }

        void HullLifePoint::onUpdate()
        {
          float life = getTrait<Model::Destroyable>()->getLife() ;

          float local_height = height * life ;

          m_hull_interior->setHeight(local_height) ;
          m_hull_interior->setWidth(width) ;
          m_hull_interior->setTop(height-local_height) ;
          Utility::setColour(m_hull_interior,life*::Ogre::ColourValue::Green + (1-life)* ::Ogre::ColourValue::Red) ;
        }

      }
    }
  }
}


