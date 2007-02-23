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

#ifndef _PU_DISPLAY_IMPLEMENTATION_OGRE_VIEW_POINT_H_
#define _PU_DISPLAY_IMPLEMENTATION_OGRE_VIEW_POINT_H_

#include <Ogre.h>

#include <display/object.h>
#include <display/view_point.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {
        
        class Univers ;
        
        /// Le point de vue subjectif d'un personnage r�alis� avec Ogre3d.
        /*!
          C'est la vue � la premi�re personne d'un observateur.
          
          @par Type de classe :
          - Object
          - Concret
        */
        class ViewPoint : public Display::ViewPoint {
        public:
        
        /*!
          @name Construction 
        */
        // @{
          
          
          /// Constructeur.
          /*!
            @param[in] _observateur 
              l'objet qui voie (par exemple un personnage, une cam�ra,...)
          */
          ViewPoint(Model::Object* _observer) ;

          /// Le point de vue est celui affich�.
          virtual void activate() ;

          /// Le point de vue n'est plus affich�.
          virtual void desactivate() ;
          
          /// Initialise le point de vue
          virtual void init() ;
          
          /// termine le point de vue
          virtual void close() ;
          
          /// Change l'observateur de la vue.
          virtual void changeObserver(Model::Object* _observer) ;
          
        // @}
        /*!_PU_DISPLAY_IMPLEMENTATION_OGRE_POINT_DE_VUE_H_
          @name acc�s 
        */
        // @{

          /// Acc�s au gestionnaire Ogre.
          ::Ogre::SceneManager* getManager() const ;

        // @}
        
        private:
        
          /// Vrai si l'objet est interessant pour le point de vue
          virtual bool isVisible(Model::Object* _model) const ;
        /*!
          @name Attributs
        */
        // @{
          
          /// Object repr�sentant l'univers affich�
          Object* universe ;
        
        // @}
        /*!
          @name Attributs Ogre
        */
        // @{
          
          /// Une surface d'�cran
          /*!
            @remark
              si on le met ailleur alors, on peut �ventuellement changer la 
              surface (lorsque elle n'est pas effectivement affich�e ou si la 
              surface est reduite/agrandie)
          */
          ::Ogre::RenderTarget* surface ;

          /// Ce qui va g�rer tous les objets � afficher.          
          ::Ogre::SceneManager* manager ;
          
        // @}
          
        };
      }
    }
  }
}


#endif
