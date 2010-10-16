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

#include <model/head_up_display.h>
#include <model/whole.h>
#include <model/selection.h>
#include <model/transponder.h>
#include <display/implementation/observer.h>

#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/targeted_indicator.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {

      DeclareDeducedRelation(TargetedIndicator,
                             Model::Selection,
                             And(IsTo(And(HasTrait(Model::HeadUpDisplay),
                                          HasChild(HasTrait(Model::Transponder)))),
                                 /// @todo correct because transponder could be on a component sub object
                                 IsFrom(And(HasTrait(Model::Whole),
                                            HasTrait(Model::Transponder))))) ;
      namespace Ogre
      {

        RegisterRelationView(Ogre::TargetedIndicator,
                             Implementation::TargetedIndicator,
                             Ogre::RealWorldViewPoint) ;


        unsigned int TargetedIndicator::m_count = 0 ;
        ::Ogre::Overlay* TargetedIndicator::m_overlay = NULL ;

        void TargetedIndicator::onInit()
        {
          InternalMessage("Display","Display::TargetedIndicator::onInit Entering") ;

          // enemies if they are in different teams
          m_is_enemy_target = getObjectTo()->getChild<Model::Transponder>()->getTeam() != getObjectFrom()->getChild<Model::Transponder>()->getTeam() ;

          if (m_is_enemy_target)
          {
            ++m_count ;
            if (m_count == 1)
              createIndicator() ;
          }
          InternalMessage("Display","Display::TargetedIndicator::onInit Leaving") ;
        }

        void TargetedIndicator::createIndicator()
        {
          m_overlay = getOverlay("PU/base/HUD/TargetedIndicator") ;
          m_overlay->show() ;
        }

        void TargetedIndicator::onClose()
        {
          if (m_is_enemy_target)
          {
            InternalMessage("Display","Display::TargetedIndicator::onClose Entering") ;
            --m_count ;

            // the last one turn of the light
            if (m_count == 0)
              removeIndicator() ;

            InternalMessage("Display","Display::TargetedIndicator::onClose Leaving") ;
          }
        }

        void TargetedIndicator::removeIndicator()
        {
          InternalMessage("Display","Display::TargetedIndicator::removeIndicator Entering") ;
          if (m_overlay)
          {
            m_overlay->hide() ;
          }
          InternalMessage("Display","Display::TargetedIndicator::removeIndicator Leaving") ;
        }

      }
    }
  }
}


