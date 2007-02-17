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
        pas �tre utilis�e directement. D'ailleurs tout est priv� pour emp�cher 
        de vouloir l'utiliser. 
      
        Elle permet de partager les listes de valeur, et de construire des 
        listes temporaires qui ne sont pas d�truites lorsqu'on it�re dessus.
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
      
        /// Ajoute un nouvel �l�ment en d�but de liste.
        void AjouterEnTete(const VALEUR& _elt) ;
      
        /// Ajoute un nouvel �l�ment en fin de liste.
        void AjouterEnQueue(const VALEUR& _elt) ;
      
        /// Obtient une r�f�rence, et donc augmente le nombre de r�f�rencants.
        TamponListeValeur< VALEUR >* Prendre() ;
      
        /// Relache une r�f�rence et renvoie 
        /// vrai s'il faut la d�truire.
        Booleen Laisser() ;
      
        
      
        // @}
        // ***********************
        /// @name M�thodes d'acc�s
        // ***********************
        // @{
      
      
        /// Determine si _element fait partie de la liste et renvoie sa position.
        EntierPositif Position(const VALEUR& _element) const ;
      
        /// Enl�ve l'�l�ment � la position _position
        void Enlever(const EntierPositif& _position) ;
      
        /// renvoie le nombre de r�f�rences.
        EntierPositif NombreDeReferences() const ;
        
        
        // @}
        // ********************
        /// @name Attributs
        // ********************
        // @{
       
        /// Nombre de r�f�rences � la liste, 
        /// lorsque ce nombre tombe � z�ro, il y a destruction.
        EntierPositif nombreDeReferences ;
      
        // @}
      
        /// Ce sont les seules classes qui ont le droit d'utiliser 
        /// les fonctionnalit�s de ce tampon
        friend class ListeValeur<VALEUR> ;
        friend class IterateurListeValeur<VALEUR> ;
      
      };
      
    }
  }
}

#include <base/implantation/tampon_liste_valeur.cxx>


#endif
