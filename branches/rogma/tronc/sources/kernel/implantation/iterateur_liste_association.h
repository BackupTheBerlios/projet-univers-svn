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

#include <base/association_virtuelle.h>
#include <base/implantation/iterateur_liste.h>




namespace ProjetUnivers {

  namespace Base {

    template <class OBJET> class Association ;
    
    namespace Implantation {
          
      template <class OBJET> class ListeAssociation ;
      template <class OBJET> class TamponListeAssociation ;
      template <class OBJET> class NoeudAssociation ;
      
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
        /// @name Constructeur, méthodes de modifications
        // **********************************************
        // @{
      
      
        /// Constructeur.
        
        /*
         @param[_liste] liste sur laquelle on va itérer.
        */
        IterateurListeAssociation(const ListeAssociation<OBJET> &_liste) ;
      
        /// Destructeur.
        ~IterateurListeAssociation() ;
      
      
        // @}
        // ***********************
        /// @name Méthodes d'accès
        // ***********************
        // @{
        
        
        /// Renvoie l'élément courant en association.
        operator Association< OBJET >() ;
      
        /// Renvoie l'élément courant en référence.
        operator const OBJET&() ;
       
        /// Opérateur de déréférenciation.
        OBJET* operator ->() const ;
      
      
        // @}
      private:
      
        /// Une référence pour pouvoir la lacher
        TamponListeAssociation< OBJET >* liste ;

        /// Conversion dynamique de noeudCourant.
        UTILISATION_ASSOCIATION_VIRTUELLE(NoeudAssociation<OBJET>,noeudCourant)
      };
    }
  }
}


#include <base/implantation/iterateur_liste_association.cxx>

#endif 


