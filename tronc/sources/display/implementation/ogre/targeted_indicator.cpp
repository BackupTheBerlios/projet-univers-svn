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
        ::Ogre::OverlayContainer* TargetedIndicator::m_indicator_container = NULL ;
        ::Ogre::OverlayElement*   TargetedIndicator::m_indicator = NULL ;

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
          m_indicator_container = static_cast< ::Ogre::OverlayContainer* >(
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel","TargetedIndicator")) ;
          getOverlay()->add2D(m_indicator_container) ;

          m_indicator_container->setPosition(0,0) ;
          m_indicator_container->setWidth(1) ;
          m_indicator_container->setHeight(1) ;

          m_indicator =
            ::Ogre::OverlayManager::getSingleton().createOverlayElement(
                  "Panel", Utility::getUniqueName()) ;

          // top left
          m_indicator->setHorizontalAlignment(::Ogre::GHA_LEFT) ;
          m_indicator->setVerticalAlignment(::Ogre::GVA_TOP) ;
          m_indicator->setMaterialName("PU/base/hud/warning") ;

          const float size = 0.1 ;

          m_indicator->setDimensions(size,size) ;

          m_indicator_container->_addChild(m_indicator) ;

          getOverlay()->show() ;
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
          if (m_indicator_container)
          {
            getOverlay()->remove2D(m_indicator_container) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_indicator) ;
            ::Ogre::OverlayManager::getSingleton().destroyOverlayElement(m_indicator_container) ;
            m_indicator_container = NULL ;
            m_indicator = NULL ;
          }
          InternalMessage("Display","Display::TargetedIndicator::removeIndicator Leaving") ;
        }

      }
    }
  }
}


