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

#include <base/composition.h>

#include <affichage/implantation/ogre/planetoide.h>

using namespace ProjetUnivers::Base ;

namespace ProjetUnivers {
   
  namespace Affichage 
  {

    namespace Implantation 
    {

      namespace Ogre 
      {
      
       
        Planetoide::Planetoide(
          const Association< Modele::Planetoide>& _planetoide)
        : Implantation::Planetoide(_planetoide)
        {}
  
        Planetoide* Construire(
          const Association< Modele::Planetoide>& _planetoide)
        {
          Composition< Planetoide > resultat(new Planetoide(_planetoide)) ;
          
          // si on trouve une donnée de ce planetoide alors c'est bon
          
          
          
          // sinon on en construit une par défaut
          // ... on choppe les caracs et on construit une boule de la bonne 
          // taille
          // avec une atmo de la bonne couleur...
          
          return resultat.Liberer() ;
        }
        
        /// Construction par défaut
        Planetoide* ConstruireParDefaut(
          const Association< Modele::Planetoide>& _planetoide)
        {
          Composition< Planetoide > resultat(new Planetoide(_planetoide)) ;
        
          /// un mesh en forme de boule de la bonne taille :
          
          
          /// une texture au hasard
          
          
          return resultat.Liberer() ;
  
      }
    }    

  }
}

