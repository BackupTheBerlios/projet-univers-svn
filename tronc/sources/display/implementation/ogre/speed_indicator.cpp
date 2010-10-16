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

          m_overlay = getOverlay("PU/base/HUD/ShipSpeed") ;

          m_speed_container = m_overlay->getChild("ShipSpeed") ;
          m_speed = m_speed_container->getChild("ShipSpeed/Speed") ;
          ::Ogre::MaterialPtr material = m_speed->getMaterial() ; 
          material = material->clone(Utility::getUniqueName()) ;
          m_speed->setMaterialName(material->getName()) ; 
          Utility::setColour(m_speed,::Ogre::ColourValue(1.0, 1.0, 1.0)) ;            

          onUpdate() ;

          m_overlay->show() ;
          
          InternalMessage("Display","Display::SpeedIndicator::onInit Leaving") ;
        }
          
        void SpeedIndicator::onClose()
        {
          InternalMessage("Display","Display::SpeedIndicator::onClose Entering") ;
          if (m_overlay)
          {
            m_overlay->hide() ;
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

