/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _PU_BASE_LISTE_COMPOSITION_H_
#define _PU_BASE_LISTE_COMPOSITION_H_

#include "liste_abstraite.h"
#include "noeud_composition.h"
#include "iterateur_liste_composition.h"

namespace ProjetUnivers {

  namespace Base {
  
    
    template <class OBJET> class ListeAssociation ;
    
    
    /*
    CLASS
      ListeComposition
    
      Classe générique réalisant l'agrégation d'une liste d'objets.
    
    UTILISATION
      Même utilisations que pour ObComposition, en ce qui concerne les listes.
    */
    template <class OBJET> class ListeComposition 
      : public ListeAbstraite {
    
    public:
    
    
      
      // ********************
      // GROUP: Construction
      // ********************
    
      
      //////////////
      // Constructeur par défaut.
      ListeComposition() ;
    
      //////////////
      // Destructeur par défaut.
      ~ListeComposition() ;
    
      /////////////////
      // Constructeur de copie, _l est vide après cela.
      ListeComposition(const ListeComposition<OBJET> &_l);
    
      /////////////////
      // Aggrege un élément à la liste en première position.
      void AjouterEnTete(OBJET* _elt);
    
      /////////////////
      // Aggrege des éléments à la liste en première position.
      void AjouterEnTete(const ListeComposition< OBJET >& _l) ;
    
      /////////////////
      // Aggrege un élément à la liste en dernière position.
      void AjouterEnQueue(OBJET* _elt);
    
      //////////////////
      // Enlève l'élément à la position _pos;
      void Enlever(unsigned int _pos) ;
    
      /////////////////
      // Méthode linéaireAprès ça, _l est vide.
      ListeComposition< OBJET >& operator = (const ListeComposition<OBJET> &_l);
    
    
      // ********************
      // GROUP: Consultation
      // ********************
    
    
      ///////////////////
      // Determine si _el fait partie de la liste.
      Booleen Contient(const Association< OBJET >& _el) const ;
    
      ///////////////////
      // Determine si _el fait partie de la liste et renvoie sa position.
      unsigned int Position(const Association< OBJET >& _el) const ;
    
    
      /////////////////
      // Renvoie l'élément à la position _pos.
      Association< OBJET > Element(unsigned int _pos) const ;
    
    
    };
    
    #ifdef _INC_TEMP_CODE_
    #include "liste_composition.cxx"
    #endif
  }
}
#endif 


