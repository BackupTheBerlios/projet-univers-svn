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
#include <kernel/trait_view.h>
#include <kernel/parameters.h>
#include <model/transponder.h>
#include <model/computer.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/head_up_display/ideal_target.h>
#include <display/implementation/ogre/head_up_display/target.h>
#include <display/implementation/ogre/head_up_display/identified_target.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {
        namespace HUD
        {

          RegisterView(IdentifiedTarget,
                       Implementation::IdentifiedTarget,
                       HeadUpDisplayViewPoint) ;

          void IdentifiedTarget::onInit()
          {
            InternalMessage("Display","Entering IdentifiedTarget::onInit") ;
            m_target = getView<Target>() ;
            onUpdate() ;
            InternalMessage("Display","Leaving IdentifiedTarget::onInit") ;
          }

          void IdentifiedTarget::onClose()
          {
            InternalMessage("Display","Entering IdentifiedTarget::onClose") ;
            m_target = getView<Target>() ;
            if (m_target)
            {
              m_target->setTargetColour(::Ogre::ColourValue::White) ;
            }
            InternalMessage("Display","Leaving IdentifiedTarget::onClose") ;
          }

          void IdentifiedTarget::onUpdate()
          {
            InternalMessage("Display","Entering IdentifiedTarget::onUpdate") ;
            // calculate colour
            ::Ogre::ColourValue colour ;
            if (Model::Transponder::areFriend(getObject(),getViewPoint()->getTargetingSystem()))
            {
              InternalMessage("Display","IdentifiedTarget::onUpdate friend") ;
              colour = ::Ogre::ColourValue::Green ;
            }
            else if (Model::Transponder::areFoe(getObject(),getViewPoint()->getTargetingSystem()))
            {
              InternalMessage("Display","IdentifiedTarget::onUpdate enemy") ;
              colour = ::Ogre::ColourValue::Red ;
            }
            else
            {
              InternalMessage("Display","IdentifiedTarget::onUpdate un-identified") ;
              colour = ::Ogre::ColourValue::White ;
            }

            m_target->setTargetColour(colour) ;

            std::set<Implementation::IdealTarget*> ideal_targets =
                m_target->getObject()->getDescendants<Implementation::IdealTarget>() ;
            for(std::set<Implementation::IdealTarget*>::iterator ideal_target = ideal_targets.begin() ;
                ideal_target != ideal_targets.end() ;
                ++ideal_target)
            {
              (*ideal_target)->getView<IdealTarget>(getViewPoint())->setColour(colour) ;
            }

            // display transponder code
            Model::Transponder* transponder = getObject()->getTrait<Model::Transponder>() ;
            if (transponder)
            {
              m_target->setIdentification(transponder->getCode()) ;
            }
            InternalMessage("Display","Leaving IdentifiedTarget::onUpdate") ;
          }

        }
      }
    }
  }
}
