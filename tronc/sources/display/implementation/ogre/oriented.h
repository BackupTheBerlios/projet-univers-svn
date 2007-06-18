/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#ifndef _DISPLAY_IMPLEMENTATION_OGRE_ORIENTED_H_
#define _DISPLAY_IMPLEMENTATION_OGRE_ORIENTED_H_

#include <Ogre.h>

#include <kernel/trait_view.h>
#include <model/oriented.h>
#include <display/implementation/ogre/real_world_view_point.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        class ViewPoint ;
        
        /// View on element that are oriented in space.
        class Oriented : public Kernel::TraitView<Model::Oriented,
                                                     RealWorldViewPoint>
        {
        public:

          /// Construct.
          Oriented(Model::Oriented* _object,
                   RealWorldViewPoint* i_viewpoint) ;

        protected:
        
          /// Init the view.
          virtual void onInit() ;

          /// Orientation update.
          virtual void onUpdate() ;
          
        private:
          
          /// Scene node.
          ::Ogre::SceneNode* m_node ;

        };

      }      
    }
  }
}
#endif
