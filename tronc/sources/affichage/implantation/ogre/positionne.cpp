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

#include <base/traceur.h>

#include <affichage/point_de_vue.h>
#include <affichage/implantation/ogre/point_de_vue.h>

#include <affichage/implantation/ogre/positionne.h>

namespace ProjetUnivers {
  namespace Affichage {
    namespace Implantation {
      namespace Ogre {

        /// Indique que la cette vue s'applique au modèle dans ce point de vue
        EnregistreVue(Ogre::Positionne,Modele::Positionne, Ogre::PointDeVue) ;
      
      
      /*!
        @name Méthodes locales
      */  
      // @{
      
        /// Convertit une position en position Ogre
        ::Ogre::Vector3 Conversion(const Modele::Position& _position)
        {
          Modele::Distance x(_position.AccesCoordonneeX()) ;
          Modele::Distance y(_position.AccesCoordonneeY()) ;
          Modele::Distance z(_position.AccesCoordonneeZ()) ;
          
          /*!
            Les coordonnées ogre sont codées sur 32 bits. 
            
            Il faut être capable d'ajuster l'échèle par un facteur de 
            conversion, ici on pose : 1 unité Ogre = 1000 mètres.
            
            De plus on pourrait changer de système de coordonnées, Ogre utilise 
            le système suivant : 
            +X = right
            -X = left
            +Y = up
            -Y = down
            +Z = going into the screen
            -Z = going away from the screen
            
            On pourrait par exemple, inverser des axes etc...
            
          */
          
          const Base::Reel facteurDeConversion = 1000 ;
          
          Base::Reel XEnMetres = x.Metre() ;
          Base::Reel YEnMetres = y.Metre() ;
          Base::Reel ZEnMetres = z.Metre() ;
          
          return ::Ogre::Vector3(XEnMetres/facteurDeConversion,
                                  YEnMetres/facteurDeConversion,
                                  ZEnMetres/facteurDeConversion) ;
          
          
          
        }
      
      // @}
      
        /// Constructeur.
        Positionne::Positionne(
          const Base::Association<Modele::Positionne>& _objet)
        : Vue<Modele::Positionne>(_objet), noeud(NULL)
        {
          Base::Traceur::MessageInterne("Entering Ogre::Positionne::Positionne") ;
          Base::Traceur::MessageInterne("Leaving Ogre::Positionne::Positionne") ;
        }
      
        /// Initialise la vue.
        /*!
        @pre
          La vue correspondant au conteneur à déjà été initialisée.
        */
        void Positionne::Initialiser()
        {
          Base::Traceur::MessageInterne("Entering Positionne::Initialiser") ;
          
          /*! 
            on crée un noeud qu'on rattache en dessous du conteneur
          */
          if (! this->initialise)
          {
            
            /// On récupère le connteneur et son noeud
            Base::Association<Objet> conteneur(this->AccesObjet()->AccesConteneur()) ;
            
            if (conteneur)
            {
              Base::Association<Positionne> parent(*conteneur) ;
              noeud = this->AccesPointDeVue()->AccesGestionnaire()->createSceneNode() ;
              parent->noeud->addChild(noeud) ;
            }
            else
            {
              Base::Traceur::MessageInterne("root node") ;
              
              /// on est à la racine.
              noeud = this->AccesPointDeVue()->AccesGestionnaire()->getRootSceneNode() ;
            }
            
            this->initialise = Base::VRAI ;
          }

          Base::Traceur::MessageInterne("Leaving Positionne::Initialiser") ;

        }

        /// Termine la vue.
        void Positionne::Terminer()
        {
          /*! 
            rien n'a faire, le manager détruira les noeuds.
          */
        }
        
        /// La position à changé
        /*!
        @par Etat actuel
          terminé
        */
        void Positionne::Raffraichir()
        {
          /// on le replace par rapport à son parent
          noeud->setPosition(Conversion(observe->AccesPosition())) ;
        }

        ::Ogre::SceneNode* Positionne::AccesNoeud()
        {
          if (noeud == NULL)
          {
            this->Initialiser() ;
          }
          
          return noeud ;
        }


      }      
    }
  }
}
