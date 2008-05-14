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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_OBSERVATEUR_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_OBSERVATEUR_H_

#include <Ogre.h>

#include <kernel/trait_view.h>
#include <model/observer.h>
#include <display/implementation/ogre/real_world_view_point.h>

namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        
        
        /// Observer view.
        /*!
          Ogre inverse the camera Z axis 
          @see http://www.ogre3d.org/phpBB2/viewtopic.php?t=26839
        */
        class Observer : public Kernel::TraitView<Model::Observer,
                                                  RealWorldViewPoint>
        {
        public:
        
        /*!
          @name Construction 
        */
        // @{


          /// Constructor.
          Observer(Model::Observer*,RealWorldViewPoint*) ;

          ::Ogre::Camera* getCamera() const ;

        // @}
        protected:

        /*!
          @name Updates.
        */
        // @{
        
          /// Build a camera.
          void onInit() ;
          
          /// Destroy the camera.
          void onClose() ;
          
          /// 
          /*!
          @par state
            empty stub vide
            Model::Observer stil does not contains any changeable data. 
          */
          void onUpdate() ;

        // @}
        private:

          ::Ogre::Camera*    m_camera ;
          
          /// local node to have the camera correctly oriented
          ::Ogre::SceneNode* m_node ;

        };
      }
    }
  }
}


#endif
