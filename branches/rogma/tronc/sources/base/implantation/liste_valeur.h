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
      template <typename VALEUR> class IterateurListeValeur ;
      
      /// Une liste d'objets d'une classe de valeur.
      /*!
        @todo 
          remplacer l'implantation
      */
      template <typename VALEUR> class ListeValeur 
      {
      public:
      
      
        
        // ********************
        /// @name Construction
        // ********************
      
        
        /// Constructeur par d�faut.
        ListeValeur() ;
      
        /// Destructeur.
        ~ListeValeur() ;
      
        /// Constructeur de copie, _liste est vide apr�s cela.
        ListeValeur(const ListeValeur<VALEUR>& _liste);
      
        /// Ajoute un �l�ment � la liste en premi�re position.
        void AjouterEnTete(const VALEUR& _element);
      
        /// Ajoute des �l�ments � la liste en premi�re position.
        void AjouterEnTete(const ListeValeur<VALEUR>& _liste) ;
      
        /// Ajoute un �l�ment � la liste en derni�re position.
        void AjouterEnQueue(const VALEUR& _elt);
      
        /// Enl�ve l'�l�ment � la position _position.
        void Enlever(const EntierPositif& _position) ;
      
        /// Affectation, �pr�s �a,@ _l est vide.
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
        /// du premier trouv�.
        /// \return 
        ///   renvoie 0 si l'�l�ment ne fait pas partie de la liste
        EntierPositif Position(const VALEUR& _el) const ;
  
        /// Renvoie l'�l�ment � la position _position.
        VALEUR Element(const EntierPositif& _position) const ;
      
        /// Acc�s au nombre d'�l�ments.
        EntierPositif NombreDElements() const ;

      
        //@}
  
      private:
      
        /// Vrai liste proprement dite
        /// elle va �tre partag�e par toutes les copies
        TamponListeValeur< VALEUR >* liste ;

        friend class IterateurListeValeur<VALEUR> ;      

      };

    }
  }
}

#include <base/implantation/liste_valeur.cxx>

#endif 


