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


#ifndef _PU_DISPLAY_IMPLEMENTATION_OGRE_OGRE_H_
#define _PU_DISPLAY_IMPLEMENTATION_OGRE_OGRE_H_

#include <Ogre.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      
      /// Implementation du module affichage avec Ogre3d.
      
      /*!
        Voir www.ogre3d.org     
      */ 
      namespace Ogre {  
  
        /// Initialisation de l'affichage
        /*!
        */
        bool init() ;
        
        /// Termine l'affichage
        void close() ;

        /// Accès aux descripteur de la fenetre d'affichage
        /*!
          Utilisé pour initialiser le module Input
        */
        size_t getWindowHandle() ;

        /// Accès à la taille de la fenêtre
        void getWindowSize(unsigned int& width,
                           unsigned int& height,
                           unsigned int& depth,
                           int& left,
                           int& top );

        
        /// Rafraichissement de l'affichage.
        /*!
          Met à jour tout ce qui doit être affiché

          @todo
            Changer le nom en "Afficher"
        */
        void update() ;
        
        /*!
          @name Variables Locales
        */
        // @{

        
        /// le système ogre      
        ::Ogre::Root* getRoot() ;
        
        /// la fenetre d'affichage
        /*!
          @remark
            C'est un pointeur, Ogre gère lui même sa mémoire et détruira 
            l'objet lorsqu'on n'en aura plus besoin. 
            Ce pointeur doit être considéré comme une association.
        */
        ::Ogre::RenderWindow* getWindow() ;
        
        ::Ogre::SceneManager* getManager() ;

        // @}
        
        
      }
    
    }
    
  }
  
}



#endif 
