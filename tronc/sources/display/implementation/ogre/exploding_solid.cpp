/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2010 Mathieu ROGER                                 *
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
#include <OgreVector3.h>

#include <kernel/log.h>

#include <model/solid.h>
#include <model/explosion.h>

#include <display/implementation/displayed_solid.h>
#include <display/implementation/ogre/utility.h>
#include <display/implementation/ogre/positioned.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/ogre/solid.h>
#include <display/implementation/ogre/exploding_solid.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {

      DeclareDeducedTrait(ExplodingSolid,And(HasTrait(Model::Explosion),
                                             HasTrait(DisplayedSolid))) ;

      namespace Ogre
      {

        RegisterView(Ogre::ExplodingSolid,Implementation::ExplodingSolid,Ogre::RealWorldViewPoint) ;

        /// Updates an animation
        class AnimationUpdate : public ::Ogre::FrameListener
        {
        public:

          AnimationUpdate(::Ogre::AnimationState* state,::Ogre::Entity* mesh)
          : m_state(state),m_mesh(mesh),m_active(true)
          {
            m_state->setLoop(false) ;
            m_state->setEnabled(true) ;
          }

          ~AnimationUpdate()
          {
            if (m_active)
              m_state->setEnabled(false) ;
          }

          bool frameStarted(const ::Ogre::FrameEvent& evt)
          {
            // @todo fade mesh to transparent... ?

            if (!m_active)
              return true ;

            if (m_state->hasEnded())
            {
              m_mesh->setVisible(false) ;
              m_active = false ;
            }
            else
              m_state->addTime(evt.timeSinceLastFrame) ;

            return true ;
          }

          ::Ogre::AnimationState* m_state ;
          ::Ogre::Entity* m_mesh ;
          bool m_active ;
        };

        void ExplodingSolid::onInit()
        {
          m_animation = NULL ;

          ::Ogre::Entity* mesh = getView<Solid>()->getEntity() ;

          if (mesh->hasVertexAnimation())
          {
            ::Ogre::AnimationState* explosion = mesh->getAnimationState("explosion") ;
            if (explosion)
            {
              m_animation = new AnimationUpdate(explosion,mesh) ;
              getRoot()->addFrameListener(m_animation) ;
            }
          }
          else
          {
            // hide
            mesh->setVisible(false) ;
          }
        }

        void ExplodingSolid::onClose()
        {
          if (m_animation)
          {
            // removing animation
            getRoot()->removeFrameListener(m_animation) ;
            delete m_animation ;
            m_animation = NULL ;
          }
        }


      }
    }
  }
}
