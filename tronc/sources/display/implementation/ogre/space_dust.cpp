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

#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/ogre/space_dust.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {

        RegisterView(Ogre::SpaceDust,
                     Implementation::SpaceDust,
                     Ogre::RealWorldViewPoint) ;


        void SpaceDust::setEmmisionRate()
        {

          float speed_ms = getObject()->getParent<Model::Mobile>()
                                      ->getSpeed().MeterPerSecond().length() ;

          m_space_dusts->getEmitter(0)
                       ->setEmissionRate(std::min(speed_ms,float(200))) ;
        }

        void SpaceDust::onInit()
        {
          InternalMessage("Display","Display::SpaceDust::onInit Entering") ;

          ::Ogre::SceneManager* manager = this->getViewPoint()->getManager() ;
          Positioned* positioned(getView<Positioned>()) ;

          InternalMessage("Display","creating space dust scene node with parent " +
                                    positioned->getNode()->getName()) ;

          // add the space dust effect
          m_space_dusts = manager->createParticleSystem(Utility::getUniqueName(),
                                                        "PU/base/SpaceDust") ;

          m_space_dust_node = static_cast< ::Ogre::SceneNode* >(
                                        positioned->getNode()->createChild()) ;
          m_space_dust_node->attachObject(m_space_dusts) ;

          setEmmisionRate() ;

          InternalMessage("Display","Display::SpaceDust::onInit Leaving") ;
        }

        void SpaceDust::onClose()
        {
          InternalMessage("Display","Display::SpaceDust::onClose Entering") ;
          this->getViewPoint()->getManager()
              ->destroySceneNode(m_space_dust_node->getName()) ;
          InternalMessage("Display","Display::SpaceDust::onClose Leaving") ;
        }

        void SpaceDust::onUpdate()
        {
          setEmmisionRate() ;
        }

      }
    }
  }
}

