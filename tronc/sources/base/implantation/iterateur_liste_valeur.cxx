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

namespace ProjetUnivers {

  namespace Base {
      
    namespace Implantation {
        
      
      /// Constructeur.
      /// @param[_liste] liste sur laquelle on va itérer.
      template <typename VALEUR>
      IterateurListeValeur<VALEUR>::
      IterateurListeValeur(const ListeValeur<VALEUR>& _liste)
      : IterateurListe(*_liste.liste),
      liste((TamponListeValeur<VALEUR>*)_liste.liste)
      {
        liste->Prendre() ;
      
      }
      
      template <typename VALEUR> void 
      IterateurListeValeur<VALEUR>::AjouterApres(const VALEUR& _n) 
      {
      
        Composition< NoeudValeur<VALEUR> > n(new NoeudValeur<VALEUR>(_n)) ;
      
        IterateurListe::AjouterApres(n.Liberer()) ;
      
      }
      
      template <typename VALEUR> void 
      IterateurListeValeur<VALEUR>::AjouterAvant(const VALEUR& _n) 
      {
      
        Composition< NoeudValeur<VALEUR> > n(new NoeudValeur<VALEUR>(_n)) ;
      
        IterateurListe::AjouterAvant(n.Liberer()) ;
      
      }
      
      
      template <typename VALEUR>
      IterateurListeValeur<VALEUR>::
      ~IterateurListeValeur()
      {
        if (liste->Laisser())
      
          delete liste ;
      }
      
      
      
      
      
      // @}
      // ***********************
      /// @name Méthodes d'accès
      // ***********************
      // @{
      
      
      /// Renvoie l'élément courant.
      template <typename VALEUR>
      IterateurListeValeur<VALEUR>::operator VALEUR()
      {
        return *noeudCourant()->element ;
      }
    } 
  }
}

