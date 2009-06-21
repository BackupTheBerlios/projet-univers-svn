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
#include <model/targeting_system.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/head_up_display/target.h>
#include <display/implementation/ogre/head_up_display/target_with_selection.h>

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

          RegisterView(TargetWithSelection,
                       Implementation::TargetWithSelection,
                       HeadUpDisplayViewPoint) ;

          TargetWithSelection::TargetWithSelection(
              Implementation::TargetWithSelection* object,
              HeadUpDisplayViewPoint* viewpoint)
          : Kernel::TraitView<Implementation::TargetWithSelection,HeadUpDisplayViewPoint>(object,viewpoint),
            m_target(NULL)
          {}

          void TargetWithSelection::onInit()
          {
            InternalMessage("Display","Entering TargetWithSelection::onInit") ;
            m_target = getView<Target>() ;
            onUpdate() ;
            InternalMessage("Display","Leaving TargetWithSelection::onInit") ;
          }

          void TargetWithSelection::onClose()
          {
            InternalMessage("Display","Entering TargetWithSelection::onClose") ;
            m_target = getView<Target>() ;
            if (m_target)
            {
              m_target->setTargetIdentification("") ;
            }
            InternalMessage("Display","Leaving TargetWithSelection::onClose") ;
          }

          void TargetWithSelection::onUpdate()
          {
            InternalMessage("Display","Entering TargetWithSelection::onUpdate") ;

            // display transponder code of the selected target
            Model::TargetingSystem* system = getObject()->getTrait<Model::TargetingSystem>() ;

            if (!system || !system->getTarget())
              return ;

            Model::Transponder* transponder = system->getTarget()->getTrait<Model::Transponder>() ;
            if (transponder)
            {
              m_target->setTargetIdentification(transponder->getCode()) ;
            }
            InternalMessage("Display","Leaving TargetWithSelection::onUpdate") ;
          }

        }
      }
    }
  }
}
