/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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

#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_REAL_WORLD_VIEW_POINT_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_REAL_WORLD_VIEW_POINT_H_

#include <Ogre.h>

#include <kernel/object.h>
#include <display/implementation/real_world_view_point.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        
        /// Le point de vue subjectif d'un personnage réalisé avec Ogre3d.
        /*!
          C'est la vue à la première personne d'un observateur.
          
          @par Type de classe :
          - Object
          - Concret
        */
        class RealWorldViewPoint : public Display::Implementation::RealWorldViewPoint {
        public:
        
        /*!
          @name Construction 
        */
        // @{
          
          
          /// Constructeur.
          /*!
            @param[in] _observateur 
              l'objet qui voie (par exemple un personnage, une caméra,...)
          */
          RealWorldViewPoint(Kernel::Object* _observer) ;
          
          /// Initialise le point de vue
          virtual void onInit() ;
          
          /// termine le point de vue
          virtual void onClose() ;
          
          /// Change l'observateur de la vue.
          virtual void onChangeObserver(Kernel::Object* _observer) ;

          /// Make this as the displayed viewpoint. 
          virtual void activate() ;
          
        // @}
        /*
          @name accès 
        */
        // @{

          /// Accès au gestionnaire Ogre.
          ::Ogre::SceneManager* getManager() const ;

        // @}
        
        private:
        
          /// Vrai si l'objet est interessant pour le point de vue
          virtual bool isVisible(Kernel::Object* _model) const ;
        /*!
          @name Attributs
        */
        // @{
          
          /// Object représentant l'univers affiché
          Kernel::Object* universe ;
        
        // @}
        /*!
          @name Attributs Ogre
        */
        // @{
          
          /// Une surface d'écran
          /*!
            @remark
              si on le met ailleur alors, on peut éventuellement changer la 
              surface (lorsque elle n'est pas effectivement affichée ou si la 
              surface est reduite/agrandie)
          */
          ::Ogre::RenderTarget* surface ;

          /// Ce qui va gérer tous les objets à afficher.          
          ::Ogre::SceneManager* manager ;
          
        // @}
          
        };
      }
    }
  }
}


#endif
