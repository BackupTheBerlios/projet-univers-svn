/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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


#ifndef _PU_AFFICHAGE_IMPLANTATION_OGRE_OGRE_H_
#define _PU_AFFICHAGE_IMPLANTATION_OGRE_OGRE_H_

#include <Ogre.h>

#include <base/types.h>
#include <base/association.h>

namespace ProjetUnivers {
  
 
  namespace Affichage 
  {


    namespace Implantation {
      
      /// Implantation du module affichage avec Ogre3d.
      
      /*!
        Voir www.ogre3d.org     
      */ 
      namespace Ogre {  
  
        /// Initialisation de l'affichage
        /*!
        */
        Base::Booleen Initialiser() ;
        
        /// Termine l'affichage
        void Terminer() ;

        /// Acc�s aux descripteur de la fenetre d'affichage
        /*!
          Utilis� pour initialiser le module Entrees
        */
        size_t DescripteurFenetre() ;

        /// Acc�s � la taille de la fen�tre
        void TailleFenetre(unsigned int& width,
                           unsigned int& height,
                           unsigned int& depth,
                           int& left,
                           int& top );

        
        /// Rafraichissement de l'affichage.
        /*!
          Met � jour tout ce qui doit �tre affich�

          @todo
            Changer le nom en "Afficher"
        */
        void Rafraichir() ;
        
        /*!
          @name Variables Locales
        */
        // @{

        
        /// le syst�me ogre      
        Base::Association< ::Ogre::Root> Racine() ;
        
        /// la fenetre d'affichage
        /*!
          @remark
            C'est un pointeur, Ogre g�re lui m�me sa m�moire et d�truira 
            l'objet lorsqu'on n'en aura plus besoin. 
            Ce pointeur doit �tre consid�r� comme une association.
        */
        ::Ogre::RenderWindow* Fenetre() ;
        
        ::Ogre::SceneManager* Gestionnaire() ;

        // @}
        
        
      }
    
    }
    
  }
  
}



#endif 
