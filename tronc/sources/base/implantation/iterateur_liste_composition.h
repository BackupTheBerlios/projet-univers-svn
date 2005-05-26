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

#ifndef _PU_BASE_ITERATEUR_LISTE_COMPOSITION_H_
#define _PU_BASE_ITERATEUR_LISTE_COMPOSITION_H_

#include <base/association_virtuelle.h>
#include <base/implantation/iterateur_liste.h>
#include <base/implantation/noeud_composition.h>


namespace ProjetUnivers {

  namespace Base {


    namespace Implantation {
  

      template <class OBJET> class ListeComposition ;
      
      ///	Classe générique fournissant un itérateur sur les listes 
      ///	ListeComposition.
      
      /*!
        Sert à itérer sur une ListeComposition.
      */
      template <class OBJET> class IterateurListeComposition 
      : public IterateurListe {
      
      public: 
      
      	// **********************************************
      	/// @name Constructeur, méthodes de modifications
      	// **********************************************
        // @{     
      
      	/// Constructeur, prenant la liste sur laquelle on va itérer.
      	IterateurListeComposition(const ListeComposition<OBJET>& _l);
      
      	/// Constructeur de copie.
      	IterateurListeComposition(const IterateurListeComposition<OBJET>& _i) ;
      
      	/// Libère l'élément courant.
      	OBJET* Liberer() ;
      
      	/// Ajoute un élément après.
      	void AjouterApres(OBJET* _n) ;
      
      	/// Ajoute un élément avant.
      	void AjouterAvant(OBJET* _n) ;
      
      	/// Ajoute une liste.
      	void Ajouter(const ListeComposition<OBJET>& _nouveaux) ;
      
      	/// Enlève le noeud courant.
      	void Enlever() ;
  
        // @}
      	// ***********************
      	/// @name Méthodes d'accès
      	// ***********************
        // @{
  
        /// Renvoie l'élément courant en association.
        operator Association<OBJET>() ;
  
    
        /// Renvoie l'élément courant en référence.
        operator const OBJET&() ;
      
      	/// Opérateur de déréférenciation.
      	OBJET* operator ->() const ;
      
        // @}
      private:
      
      	/// Conversion dynamique de liste
      	/// en un ListeComposition<OBJET>.
      	UTILISATION_ASSOCIATION_VIRTUELLE(ListeComposition<OBJET>,liste)
  
  
      
      	/// Conversion dynamique de current_node qui est un ObAbstractNode 
      	/// en un NoeudComposition<OBJET>.
      	UTILISATION_ASSOCIATION_VIRTUELLE(NoeudComposition<OBJET>,noeudCourant)
      
      
      
      
      };
      
      
      
    }
  }
}

#include <base/implantation/iterateur_liste_composition.cxx>
#endif 


