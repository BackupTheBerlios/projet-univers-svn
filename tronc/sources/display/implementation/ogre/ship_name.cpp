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

          m_overlay = getOverlay("PU/base/HUD/ShipName") ;

          m_name_container = m_overlay->getChild("ShipData") ;
          m_name = m_name_container->getChild("ShipData/Name") ;

          ::Ogre::MaterialPtr material = m_name->getMaterial() ;
          material = material->clone(Utility::getUniqueName()) ;
          m_name->setMaterialName(material->getName()) ;
          Utility::setColour(m_name,::Ogre::ColourValue(1.0, 1.0, 1.0)) ;

          onUpdate() ;

          m_overlay->show() ;

          InternalMessage("Display","Display::ShipName::onInit Leaving") ;
        }

        void ShipName::onClose()
        {
          InternalMessage("Display","Display::ShipName::onClose Entering") ;
          if (m_overlay)
          {
            m_overlay->hide() ;
          }
          InternalMessage("Display","Display::ShipName::onClose Leaving") ;
        }

        void ShipName::onUpdate()
        {
          m_name->setCaption(getChild<Model::Transponder>()->getCode()) ;
        }

      }
    }
  }
}

