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
#include <model/selection.h>

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

          RegisterRelationView(TargetWithSelection,
                               Implementation::TargetWithSelection,
                               RealWorldViewPoint) ;

          void TargetWithSelection::onInit()
          {
            InternalMessage("Display","Entering TargetWithSelection::onInit") ;

            // @todo : sometimes it is NULL ???
            m_target = getView<HUD::Target>() ;

            if (!m_target)
            {
              Kernel::Relation* relation = Kernel::Relation::getRelation(getClassTypeIdentifier(Implementation::Target),getObjectFrom(),getObjectTo()) ;

              std::cout << "internal error" ;

            }

            onUpdate() ;
            InternalMessage("Display","Leaving TargetWithSelection::onInit") ;
          }

          void TargetWithSelection::onClose()
          {
            InternalMessage("Display","Entering TargetWithSelection::onClose") ;

            // @todo find why I put this assignment
            m_target = getView<HUD::Target>() ;
            if (m_target)
            {
              m_target->setTargetIdentification("") ;
            }
            InternalMessage("Display","Leaving TargetWithSelection::onClose") ;
          }

          void TargetWithSelection::onUpdate()
          {
            InternalMessage("Display","Entering TargetWithSelection::onUpdate") ;

            std::set<Kernel::Object*> selected(Kernel::Relation::getLinked<Model::Selection>(getObjectTo())) ;

            if (selected.size() == 1)
            {
              Model::Transponder* transponder = (*selected.begin())->getChild<Model::Transponder>() ;
              if (transponder)
              {
                m_target->setTargetIdentification(transponder->getCode()) ;
              }
            }
            InternalMessage("Display","Leaving TargetWithSelection::onUpdate") ;
          }

        }
      }
    }
  }
}
