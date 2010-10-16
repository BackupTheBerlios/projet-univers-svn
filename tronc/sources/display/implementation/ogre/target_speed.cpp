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

#include <model/mobile.h>
#include <model/selection.h>
#include <display/implementation/head_up_display.h>

#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/target_speed.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      DeclareDeducedTrait(TargetSpeed,And(HasTrait(Implementation::HeadUpDisplay),
                                          IsRelated(Model::Selection,HasTrait(Model::Mobile)))) ;

      namespace Ogre
      {

        RegisterView(Ogre::TargetSpeed,
                     Implementation::TargetSpeed,
                     Ogre::RealWorldViewPoint) ;


        void TargetSpeed::onInit()
        {
          InternalMessage("Display","Display::TargetSpeed::onInit Entering") ;

          m_overlay = getOverlay("PU/base/HUD/TargetSpeed") ;

          m_speed_container = m_overlay->getChild("TargetSpeed") ;
          m_speed = m_speed_container->getChild("TargetSpeed/Speed") ;
          ::Ogre::MaterialPtr material = m_speed->getMaterial() ;
          material = material->clone(Utility::getUniqueName()) ;
          m_speed->setMaterialName(material->getName()) ;
          Utility::setColour(m_speed,::Ogre::ColourValue(1.0, 1.0, 1.0)) ;

          onUpdate() ;

          m_overlay->show() ;

          InternalMessage("Display","Display::TargetSpeed::onInit Leaving") ;
        }

        void TargetSpeed::onClose()
        {
          InternalMessage("Display","Display::TargetSpeed::onClose Entering") ;
          if (m_overlay)
          {
            m_overlay->hide() ;
          }
          InternalMessage("Display","Display::TargetSpeed::onClose Leaving") ;
        }

        void TargetSpeed::onUpdate()
        {
          Model::Mobile* mobile = Kernel::Relation::getUniqueLinked<Model::Selection>(getObject())->getTrait<Model::Mobile>() ;
          m_speed->setCaption("Target speed : " + Kernel::toString(mobile->getSpeed().MeterPerSecond().length()) + " m/s") ;
        }

      }
    }
  }
}


