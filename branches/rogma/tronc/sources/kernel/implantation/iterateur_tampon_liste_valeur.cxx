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

#include <base/implantation/noeud_valeur.h>

namespace ProjetUnivers {

  namespace Base {

    namespace Implantation {
      
      ///////////////
      // Renvoie l'élément courant en association.
      template <typename VALEUR> 
      IterateurTamponListeValeur<VALEUR>::operator VALEUR()
      {
        return noeudCourant()->element ;
      
      }
      
      ///////////////
      // Renvoie l'élément courant en référence.
      //template <typename VALEUR> 
      //IterateurTamponListeValeur<VALEUR>::operator const OBJET&()
      //{
      //  return *noeudCourant()->element ;
      //
      //}
      
      
      template <typename VALEUR> 
      IterateurTamponListeValeur<VALEUR>::IterateurTamponListeValeur
      (const TamponListeValeur<VALEUR> &_l)
        : IterateurListe(_l)
      {}
      
      
      template <typename VALEUR> void 
      IterateurTamponListeValeur<VALEUR>::AjouterApres(const VALEUR& _n) {
      
        Composition< NoeudValeur<VALEUR> > n(new NoeudValeur<VALEUR>(_n)) ;
      
        IterateurListe::AjouterApres(n.Liberer()) ;
      
      }
      
      template <typename VALEUR> void 
      IterateurTamponListeValeur<VALEUR>::AjouterAvant(const VALEUR& _n) {
      
        Composition< NoeudValeur<VALEUR> > n(new NoeudValeur<VALEUR>(_n)) ;
      
        IterateurListe::AjouterAvant(n.Liberer()) ;
      
      }
      
      
      //template <typename VALEUR> VALEUR* 
      //IterateurTamponListeValeur<VALEUR>::operator ->() const {
      //
      //  OBJET* resultat = (OBJET*)(noeudCourant()->element) ;
      //
      //  if (resultat == NULL)
      //
      //    throw ExceptionBase("IterateurTamponListeValeur<OBJET>::operator ->") ;
      //
      //  return resultat ;
      //
      //}
      
      //template <typename VALEUR> VALEUR& 
      //IterateurTamponListeValeur<VALEUR>::operator *() const {
      //
      //  return *(noeudCourant()->element) ;
      //}
    }
  }
}

