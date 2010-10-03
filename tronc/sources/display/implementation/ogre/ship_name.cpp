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

#include <model/transponder.h>
#include <display/implementation/head_up_display.h>

#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/ship_name.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {

      DeclareDeducedTrait(ShipName,And(HasTrait(HeadUpDisplay),
                                       HasTrait(Model::Transponder))) ;

      namespace Ogre
      {

        RegisterView(Ogre::ShipName,
                     Implementation::ShipName,
                     Ogre::RealWorldViewPoint) ;


        void ShipName::onInit()
        {
          InternalMessage("Display","Display::ShipName::onInit Entering") ;

          m_name_container = static_cast< ::Ogre::OverlayContainer* >(
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel","ShipData")) ;
          getOverlay()->add2D(m_name_container) ;

          m_name_container->setPosition(0,0) ;
          m_name_container->setWidth(1) ;
          m_name_container->setHeight(1) ;

          m_name =
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "TextArea",
                  Utility::getUniqueName()) ;

          m_name->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
          m_name->setVerticalAlignment(::Ogre::GVA_CENTER) ;
          m_name->setMetricsMode(::Ogre::GMM_PIXELS) ;
          m_name->setParameter("font_name", "BlueHighway") ;
          m_name->setParameter("char_height", "16") ;
          m_name->setParameter("horz_align", "center") ;
          m_name_container->_addChild(m_name) ;
          m_name->setPosition(0,-0.48) ;

          onUpdate() ;

          InternalMessage("Display","Display::ShipName::onInit Leaving") ;
        }

        void ShipName::onClose()
        {
          InternalMessage("Display","Display::ShipName::onClose Entering") ;
          if (m_name_container)
          {
            getOverlay()->remove2D(m_name_container) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_name) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_name_container) ;
            m_name_container = NULL ;
            m_name = NULL ;
          }
          InternalMessage("Display","Display::ShipName::onClose Leaving") ;
        }

        void ShipName::onUpdate()
        {
          m_name->setCaption("Name " + getChild<Model::Transponder>()->getCode()) ;
        }

      }
    }
  }
}

