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


#ifndef _PU_BASE_IMPLANTATION_TAMPON_LISTE_VALLEUR_H_
#define _PU_BASE_IMPLANTATION_TAMPON_LISTE_VALLEUR_H_

#include <base/implantation/liste_abstraite.h>

namespace ProjetUnivers {

  namespace Base {
    
    namespace Implantation {

      template <typename VALEUR> class ListeValeur ;
      template <typename VALEUR> class IterateurListeValeur ;

    
      ///  Classe internes des listes de valeurs. 
      
      /*!
        Cette classe ne doit 
        pas être utilisée directement. D'ailleurs tout est privé pour empécher 
        de vouloir l'utiliser. 
      
        Elle permet de partager les listes de valeur, et de construire des 
        listes temporaires qui ne sont pas détruites lorsqu'on itère dessus.
      */
      template <typename VALEUR> class TamponListeValeur 
        : public ListeAbstraite {
      
      private:
      
      
        // ********************
        /// @name Constructeurs
        // ********************
        // @{
        
      
        /// Constructeur.
        TamponListeValeur() ;
      
        /// Destructeur.
        ~TamponListeValeur() ;
      
        /// Constructeur de copie.
        TamponListeValeur(const TamponListeValeur< VALEUR >& _l) ;
      
        /// Ajoute un nouvel élément en début de liste.
        void AjouterEnTete(const VALEUR& _elt) ;
      
        /// Ajoute un nouvel élément en fin de liste.
        void AjouterEnQueue(const VALEUR& _elt) ;
      
        /// Obtient une référence, et donc augmente le nombre de référencants.
        TamponListeValeur< VALEUR >* Prendre() ;
      
        /// Relache une référence et renvoie 
        /// vrai s'il faut la détruire.
        Booleen Laisser() ;
      
        
      
        // @}
        // ***********************
        /// @name Méthodes d'accès
        // ***********************
        // @{
      
      
        /// Determine si _element fait partie de la liste et renvoie sa position.
        EntierPositif Position(const VALEUR& _element) const ;
      
        /// Enlève l'élément à la position _position
        void Enlever(const EntierPositif& _position) ;
      
        /// renvoie le nombre de références.
        EntierPositif NombreDeReferences() const ;
        
        
        // @}
        // ********************
        /// @name Attributs
        // ********************
        // @{
       
        /// Nombre de références à la liste, 
        /// lorsque ce nombre tombe à zéro, il y a destruction.
        EntierPositif nombreDeReferences ;
      
        // @}
      
        /// Ce sont les seules classes qui ont le droit d'utiliser 
        /// les fonctionnalités de ce tampon
        friend class ListeValeur<VALEUR> ;
        friend class IterateurListeValeur<VALEUR> ;
      
      };
      
    }
  }
}

#include <base/implantation/tampon_liste_valeur.cxx>


#endif
