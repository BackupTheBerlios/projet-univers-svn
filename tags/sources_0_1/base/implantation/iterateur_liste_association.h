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

#ifndef _PU_BASE_ITERATEUR_LISTE_ASSOCIATION_H_
#define _PU_BASE_ITERATEUR_LISTE_ASSOCIATION_H_

#include "association_virtuelle.h"
#include "noeud_association.h"
#include "iterateur_liste.h"




namespace ProjetUnivers {

  namespace Base {
      
    template <class OBJET> class ListeAssociation ;
    template <class OBJET> class TamponListeAssociation ;
    
    
    /*
    CLASS
      IterateurListeAssociation
    
      Classe générique fournissant un itérateur sur les listes ListeAssociation.
    
    UTILISATION
      Itérer sur les éléments d'une ListeAssociation.
    
    */
    template <class OBJET> class IterateurListeAssociation 
    : public IterateurListe {
    public: 
    
      // **********************************************
      // GROUP: Constructeur, méthodes de modifications
      // **********************************************
    
    
      //////////////////
      // Constructeur, prenant la liste sur laquelle on va itérer.
      IterateurListeAssociation(const ListeAssociation<OBJET> &_l);
    
      ///////////////////
      // Destructeur.
      ~IterateurListeAssociation() ;
    
    
    
      // ***********************
      // GROUP: Méthodes d'accès
      // ***********************
    
      ///////////////
      // Renvoie l'élément courant en association.
      operator Association< OBJET >() ;
    
      ///////////////
      // Renvoie l'élément courant en référence.
      operator const OBJET&() ;
     
      /////////////
      // Opérateur de déréférenciation.
      OBJET* operator ->() const ;
    
    
    
    private:
    
      /////////////
      // Conversion dynamique de noeudCourant qui est un Node 
      // en un NoeudAssociation<OBJET>.
      UTILISATION_ASSOCIATION_VIRTUELLE(NoeudAssociation<OBJET>,noeudCourant)
    
    
      //////////////////
      // Une référence pour pouvoir la lacher
      TamponListeAssociation< OBJET >* liste ;
    
    };
    
    #include "iterateur_liste_association.cxx"

  }
}
#endif 


