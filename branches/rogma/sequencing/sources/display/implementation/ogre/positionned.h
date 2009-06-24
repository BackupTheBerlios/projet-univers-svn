/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#pragma once

#include <Ogre.h>

#include <kernel/trait_view.h>
#include <model/distance.h>
#include <display/implementation/positionned.h>
#include <display/implementation/ogre/real_world_view_point.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {
        /// Convert position to Ogre position
        ::Ogre::Vector3 convert(const Model::Position& _position) ;

        /// Convert a distance to an Ogre distance.
        ::Ogre::Real convert(const Model::Distance& distance) ;

        /// View on object that have a position in space.
        class Positionned : public Kernel::TraitView<Implementation::Positionned,
                                                     RealWorldViewPoint>
        {
        public:

          /// Construct.
          Positionned(Implementation::Positionned* object,
                      RealWorldViewPoint*          viewpoint) ;

          /// get scene node.
          /*!
            Init the view if necessary.
          */
          ::Ogre::SceneNode* getNode() ;

        protected:

          /// Build a scene node.
          virtual void onInit() ;

          /// Destroy the node.
          virtual void onClose() ;

          /// Position update.
          virtual void onUpdate() ;

          /// must detach/reattach node.
          virtual void onChangeParent(Kernel::Object* i_old_parent) ;

        private:

          void setPosition() ;
          void setOrientation() ;

          /// Scene node.
          ::Ogre::SceneNode* m_node ;

        };

      }
    }
  }
}
