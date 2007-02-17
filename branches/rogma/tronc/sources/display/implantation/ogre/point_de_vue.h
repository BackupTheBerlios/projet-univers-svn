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

#ifndef _PU_AFFICHAGE_IMPLANTATION_OGRE_POINT_DE_VUE_H_
#define _PU_AFFICHAGE_IMPLANTATION_OGRE_POINT_DE_VUE_H_

#include <Ogre.h>

#include <base/association.h>
#include <base/agregation.h>

#include <affichage/objet.h>
#include <affichage/point_de_vue.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implantation {
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
          ViewPoint(const Base::Association<Model::Object>& _observateur) ;

          /// Le point de vue est celui affich�.
          virtual void Activer() ;

          /// Le point de vue n'est plus affich�.
          virtual void Desactiver() ;
          
          /// Initialise le point de vue
          virtual void init() ;
          
          /// termine le point de vue
          virtual void close() ;
          
          /// Change l'observateur de la vue.
          virtual void ChangerObservateur
            (const Base::Association<Model::Object>& _observateur) ;
          
        // @}
        /*!
          @name acc�s 
        */
        // @{

          /// Acc�s au gestionnaire Ogre.
          ::Ogre::SceneManager* AccesGestionnaire() const ;

        // @}
        
        private:
        
          /// Vrai si l'objet est interessant pour le point de vue
          virtual Base::Booleen EstVisible
              (const Base::Association<Model::Object>& _modele) const ;
        /*!
          @name Attributs
        */
        // @{
          
          /// Object repr�sentant l'univers affich�
          Base::Association<Object> univers ;
        
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
          ::Ogre::SceneManager* gestionnaire ;
          
        // @}
          
        };
      }
    }
  }
}


#endif
