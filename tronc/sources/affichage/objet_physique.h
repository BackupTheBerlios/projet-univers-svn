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

#ifndef _PU_AFFICHAGE_OBJET_PHYSIQUE_H_
#define _PU_AFFICHAGE_OBJET_PHYSIQUE_H_


#include <base/association_virtuelle.h>


namespace ProjetUnivers {


  class Univers::ObjetPhysique ;


  namespace Affichage {


    

  
    /// Classe de l'affichage des objets physiques du monde.
    
    /*!  
    Explication
    
      C'est la classe de base de l'affichage des objets r�els de Univers, comme 
      par exemple : un vaisseau, un ast�ro�de, une �toile. 
      
        
    Type de classe
    
      Objet
    
      Abstrait
    */
    class ObjetPhysique {
    public:
    


      // ***************************
      /// @name M�thodes principales
      // ***************************
      // @{


      /// Pr�pare l'affichage
      virtual void Afficher() = 0 ;


      // @}
      // *******************************
      /// @name Constructeur Destructeur
      // *******************************
      // @{


      /// Classe abstraite donc destructeur virtuel.
      virtual ~ObjetPhysique() ;
    
    protected:
    

      
      /// Classe abstraite donc constructeur prot�g�.
      ObjetPhysique(
      	const Base::Association< Univers::ObjetPhysique>& _modele) ;

      // @}
      // **********************************
      /// @name Lien vers la partie univers
      // **********************************
      // @{
      
      //// R�f�rence � la partie "mod�le" de l'�l�ment.
      DECLARATION_ASSOCIATION_VIRTUELLE(Univers::ObjetPhysique, modele) ;
      
      // @}
  
    };
  }
}
#endif
