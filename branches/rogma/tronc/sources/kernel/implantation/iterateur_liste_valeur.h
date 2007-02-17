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


#ifndef _PU_BASE_IMPLANTATION_ITERATEUR_LISTE_VALEUR_H_
#define _PU_BASE_IMPLANTATION_ITERATEUR_LISTE_VALEUR_H_

#include <base/association_virtuelle.h>
#include <base/implantation/iterateur_liste.h>


namespace ProjetUnivers {

  namespace Base {
      
    namespace Implantation {
        
      template <typename VALEUR> class TamponListeValeur ;
      template <typename VALEUR> class ListeValeur ;
      template <typename VALEUR> class NoeudValeur ;


      ///Itérateur sur les listes TamponListeValeur.
      template <typename VALEUR> class IterateurListeValeur
      : public IterateurListe {
      public: 
      
        // *******************************
        /// @name Constructeur Destructeur
        // *******************************
        // @{
        
      
        /// Constructeur.      
        /*!
          @param[_liste] liste sur laquelle on va itérer.
        */
        IterateurListeValeur(
          const ListeValeur<VALEUR>& _liste) ;

        /// Ajoute un élément après.
        void addApres(const VALEUR& _n) ;
      
        /// Ajoute un élément avant.
        void addAvant(const VALEUR& _n) ; 
  
        /// Destructeur.
        ~IterateurListeValeur() ;
  
  
      
        // @}
        // ***********************
        /// @name Méthodes d'accès
        // ***********************
        // @{

      
        /// Renvoie l'élément courant.
        operator VALEUR() ;
      
      
        // @}  
      private:

      
        // Conversion dynamique de noeudCourant.
        UTILISATION_ASSOCIATION_VIRTUELLE(NoeudValeur<VALEUR>,noeudCourant)
      
        /// La liste gérée en copie partagée.
        TamponListeValeur<VALEUR>* liste ;
      
      
      
      };
      
      

    }
  }
}



#include <base/implantation/iterateur_liste_valeur.cxx>

#endif 
