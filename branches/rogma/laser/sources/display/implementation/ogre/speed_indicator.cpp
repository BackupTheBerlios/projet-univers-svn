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

#include <model/observer.h>
#include <model/positioned.h>
#include <model/mobile.h>

#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/speed_indicator.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {
        
        RegisterView(Ogre::SpeedIndicator, 
                     Implementation::SpeedIndicator, 
                     Ogre::RealWorldViewPoint) ;
        
        
        void SpeedIndicator::onInit()
        {
          InternalMessage("Display","Display::SpeedIndicator::onInit Entering") ;

          m_speed_container = static_cast< ::Ogre::OverlayContainer* >(
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", Utility::getUniqueName())) ;
          getOverlay()->add2D(m_speed_container) ;
          
          m_speed_container->setPosition(0,0) ;
          m_speed_container->setWidth(1) ;
          m_speed_container->setHeight(1) ;
          
          m_speed = 
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "TextArea", Utility::getUniqueName()) ;
          
          m_speed->setHorizontalAlignment(::Ogre::GHA_CENTER) ;
          m_speed->setVerticalAlignment(::Ogre::GVA_CENTER) ;
          m_speed->setMetricsMode(::Ogre::GMM_PIXELS) ;
          m_speed->setParameter("font_name", "BlueHighway") ;
          m_speed->setParameter("char_height", "16") ;
          m_speed->setParameter("horz_align", "center") ;
          ::Ogre::MaterialPtr material = m_speed->getMaterial() ; 
          material = material->clone(Utility::getUniqueName()) ;
          m_speed->setMaterialName(material->getName()) ; 
          Utility::setColour(m_speed,::Ogre::ColourValue(1.0, 1.0, 1.0)) ;            
          m_speed_container->_addChild(m_speed) ;
          m_speed_container->setPosition(0.2,0.2) ;

          m_speed->setCaption("speed : " + Kernel::toString(getTrait<Model::Mobile>()->getSpeed().MeterPerSecond().length()) + " m/s") ;
          
          InternalMessage("Display","Display::SpeedIndicator::onInit Leaving") ;
        }
          
        void SpeedIndicator::onClose()
        {
          InternalMessage("Display","Display::SpeedIndicator::onClose Entering") ;
          if (m_speed_container)
          {
            getOverlay()->remove2D(m_speed_container) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_speed) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_speed_container) ;
            m_speed_container = NULL ;
            m_speed = NULL ;
          }
          InternalMessage("Display","Display::SpeedIndicator::onClose Leaving") ;
        }
        
        void SpeedIndicator::onUpdate()
        {
          m_speed->setCaption("speed : " + Kernel::toString(getTrait<Model::Mobile>()->getSpeed().MeterPerSecond().length()) + " m/s") ;
        }
        
      }
    }
  }
}

