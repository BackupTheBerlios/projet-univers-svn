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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_SHIP_CONTROL_DEBUG_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_SHIP_CONTROL_DEBUG_H_

#include <Ogre.h>

#include <kernel/trait_view.h>
#include <model/ship_control.h>
#include <display/implementation/ogre/real_world_view_point.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// display a stick as 3D line.
        /*!
        */
        class ShipControl : public Kernel::TraitView<Model::ShipControl,
                                                     RealWorldViewPoint>
        {
        public:
        
        // **********************
        /// @name Constructeur/Destructeur
        // **********************
        // @{

          /// Constructeur.
          ShipControl(Model::ShipControl* i_object,
                      RealWorldViewPoint* i_viewpoint) ;

        protected:
        //@}
        /*!
          @name Mise à jour
        */
        // @{
        
          /// Crée une entité.
          void onInit() ;
          
          /// Détruit l'entité.
          void onClose() ;
        
          /// 
          /*!
          @par Etat
            stub vide
          */
          void onUpdate() ;

        // @}
        private:
          
          /// Modèle 3D.
          ::Ogre::Entity* m_object ;
      
        };
      }
    }
  }
}
#endif
