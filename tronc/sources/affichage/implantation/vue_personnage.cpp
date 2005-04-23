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

#include <affichage/vue_personnage.h>
#include <modele/personnage.h>

namespace ProjetUnivers {

  namespace Affichage {

    /// Constructeur.
    VuePersonnage::VuePersonnage(
        const Base::Association< Modele::Personnage >& _personnage)
    : PointDeVue(), personnage(_personnage)
    {
      // enregistrement de la vue comme Vue sur le mod�le
      personnage->EnregistrerVue(*this) ;
    }
      
    /// Notification du changement du mod�le.
    void VuePersonnage::NotifierChangement() 
    {
      // en fonction du changement, on ne fait pas la m�me chose 
    }
 
    void VuePersonnage::Construire() 
    {
      
      // cas 1 :
      // le personnage est pilote
      
      
      // Construction de la cam�ra et des autres trucs Ogre
      
      
      
      
      // on construit 2 choses :
      // l'environnement local au vaisseau
      // le reste
      
      
      // construction de l'environnement local
      // *************************************
    
      // construction du reste
      // *********************
      
      // c'est une sph�re avec des �toiles dessus...
      
      
    
    }

  }
}

