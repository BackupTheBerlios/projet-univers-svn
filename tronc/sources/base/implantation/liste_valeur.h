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

#ifndef _PU_BASE_LISTE_VALEUR_H_
#define _PU_BASE_LISTE_VALEUR_H_

#include <base/types.h>

namespace ProjetUnivers {

  namespace Base {
  
    
    namespace Implantation {    
      
      
      template <typename VALEUR> class TamponListeValeur ;
      
      /// Une liste d'objets d'une classe de valeur.
      
      template <typename VALEUR> class ListeValeur 
      {
      public:
      
      
        
        // ********************
        /// @name Construction
        // ********************
      
        
        /// Constructeur par défaut.
        ListeValeur() ;
      
        /// Destructeur.
        ~ListeValeur() ;
      
        /// Constructeur de copie, _liste est vide après cela.
        ListeValeur(const ListeValeur<VALEUR>& _liste);
      
        /// Ajoute un élément à la liste en première position.
        void AjouterEnTete(const VALEUR& _element);
      
        /// Ajoute des éléments à la liste en première position.
        void AjouterEnTete(const ListeValeur<VALEUR>& _liste) ;
      
        /// Ajoute un élément à la liste en dernière position.
        void AjouterEnQueue(const VALEUR& _elt);
      
        /// Enlève l'élément à la position _position.
        void Enlever(const EntierPositif& _position) ;
      
        /// Affectation, àprès ça,@ _l est vide.
        ListeValeur<VALEUR>& operator = (const ListeValeur<VALEUR> &_l);
      
        /// Vide la liste
        void Vider() ;
      
        // @}
        // ********************
        /// @name Consultation
        // ********************
        // @{
        
      
        /// Determine si @_el fait partie de la liste.
        Booleen Contient(const VALEUR& _el) const ;
  
        /// Determine si @_el fait partie de la liste, et renvoie la position, 
        /// du premier trouvé.
        /// \return 
        ///   renvoie 0 si l'élément ne fait pas partie de la liste
        EntierPositif Position(const VALEUR& _el) const ;
  
        /// Renvoie l'élément à la position _position.
        VALEUR Element(const EntierPositif& _position) const ;
      
        /// Accès au nombre d'éléments.
        EntierPositif NombreDElements() const ;

      
        //@}
  
      private:
      
        /// Vrai liste proprement dite
        /// elle va être partagée par toutes les copies
        TamponListeValeur< VALEUR >* liste ;
      
      };

    }
  }
}

#include <base/implantation/liste_valeur.cxx>

#endif 


