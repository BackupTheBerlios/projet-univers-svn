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

#ifndef _PU_BASE_LISTE_ASSOCIATION_H_
#define _PU_BASE_LISTE_ASSOCIATION_H_


#include "types.h"
#include "tampon_liste_association.h"
#include "iterateur_liste_association.h"
#include "iterateur_liste_composition.h"
#include "liste_composition.h"


namespace ProjetUnivers {

  namespace Base {

    template <class OBJET> class Association ;
      
    
    template <class OBJET> class TamponListeAssociation ;
    template <class OBJET> class IterateurListeAssociation ;
    template <class OBJET> class ListeComposition ;
    
    
    
      
    /*
    CLASS
      ListeAssociation
    
      Classe générique des listes d'association.
    
    UTILISATION
      La même que pour Association
    */
    
    template <class OBJET> class ListeAssociation {
    	
    public:
    
    
      // ********************
      // GROUP: Constructeurs
      // ********************
    
      //////////////
      // Constructeur.
      ListeAssociation() ;
    
      //////////////
      //Destructeur.
      ~ListeAssociation() ;
    
      //////////////
      // Constructeur de copie.
      ListeAssociation(const ListeAssociation< OBJET >& _l) ;
    
      //////////////
      // Constructeur.
      ListeAssociation(const ListeComposition< OBJET >& _l) ;
    
      ////////////////
      // Opérateur d'affectation.
      ListeAssociation< OBJET >& operator=(const ListeComposition< OBJET >& _l) ;
    
    
      ////////////////
      // Opérateur d'affectation.
      ListeAssociation< OBJET >& operator=(const ListeAssociation< OBJET >& _l) ;
    
      ///////////////
      // Ajoute un nouvel élément en début de liste.
      void AjouterEnTete(const Association< OBJET > _elt) ;
    
      ///////////////
      // Ajoute un nouvel élément en fin de liste.
      void AjouterEnQueue(const Association< OBJET > _elt) ;
    
      ///////////////
      // Ajoute des nouveaux éléments en fin de liste.
      void AjouterEnQueue(const ListeAssociation< OBJET > _elt) ;
    
    
      // ***********************
      // GROUP: Méthodes d'accès
      // ***********************
    
      ////////////////
      // Accès au nombre d'éléments.
      unsigned int NombreDElements() const ;
    
    
      /////////////////
      // Determine si l'élément _elt fait parti de la liste.
      Booleen Contient(const Association< OBJET >& _elt) const ;
    
      ///////////////////
      // Determine si _el fait partie de la liste et renvoie sa position.
      unsigned int Position(const Association< OBJET >& _el) const ;
    
      //////////////////
      // Enlève l'élément à la position _pos;
      void Enlever(unsigned int _pos) ;
    
      ////////////////
      // Accès au dernier élément.
      Association< OBJET > Dernier() const ;
    
    
    private:
    
      ///////////////////
      // Vrai liste proprement dite
      // elle va être partagée par toutes les copies
      TamponListeAssociation< OBJET >* liste ;
    
      friend class IterateurListeAssociation<OBJET> ;
    
    };
    
    
    
    
    ///////////////////
    // Intersection des éléments des listes, considérées comme des ensembles.
    template <class OBJET > 
    ListeAssociation< OBJET > Intersection
        ( const ListeAssociation< OBJET >& _l1,
          const ListeAssociation< OBJET >& _l2) ;
  
  
  
  
    #ifdef _INC_TEMP_CODE_
    #include "liste_association.cxx"
    #endif
      
  
  }
}
#endif 


