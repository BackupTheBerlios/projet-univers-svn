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

#include <base/implantation/iterateur_liste_composition.h>
#include <base/implantation/noeud_composition.h>


namespace ProjetUnivers {

  namespace Base {

    namespace Implantation {
      
      template <class OBJET> 
      ListeComposition<OBJET>::ListeComposition()
        : ListeAbstraite()
      {}
      
      //////////////
      // Destructeur par défaut.
      template <class OBJET> 
      ListeComposition<OBJET>::~ListeComposition() {
      
        Vider() ;
      }
      
      template <class OBJET> void 
      ListeComposition<OBJET>::AjouterEnTete(OBJET* _elt) {
      
        Composition<NoeudComposition<OBJET> > n(new NoeudComposition<OBJET>(_elt)) ;
      
        ListeAbstraite::AjouterEnTete(n.Liberer()) ;
      }
      
      template <class OBJET> void 
      ListeComposition<OBJET>::AjouterEnTete(const ListeComposition< OBJET >& _l) {
      
        if (this != &_l) {
      
          for(IterateurListeComposition<OBJET> i(_l) ; i.Valide() ;) {
      
            AjouterEnTete(i.Liberer()) ;
            i.Enlever() ;
          }
        }
      
      }
      
      
      template <class OBJET> void 
      ListeComposition<OBJET>::AjouterEnQueue(OBJET* _elt) {
      
        Composition<NoeudComposition<OBJET> > n(new NoeudComposition<OBJET>(_elt)) ;
      
        ListeAbstraite::AjouterEnQueue(n.Liberer()) ;
      }
      
      
      template <class OBJET> ListeComposition<OBJET>& 
      ListeComposition<OBJET>::operator = (const ListeComposition<OBJET> &_l) {
      
        if (this != &_l) {
      
          for(IterateurListeComposition<OBJET> i(_l) ; i.Valide() ;) {
      
            AjouterEnQueue(i.Liberer()) ;
            i.remove() ;
          }
        }
      
        return *this ;
      }
      
      template <class OBJET> 
      ListeComposition<OBJET>::ListeComposition(const ListeComposition<OBJET>& _l)
        : ListeAbstraite() {
      
        operator =(_l) ;
      }
      
      
      template <class OBJET> Booleen 
      ListeComposition<OBJET>::Contient(const Association< OBJET >& _el) const {
      
        for(IterateurListeComposition<OBJET> i(*this) ; i.Valide() ; ++i)
      
          if (_el == i)
      
            return VRAI ;
      
        return FAUX ;
      }
      
      template <class OBJET> Association< OBJET > 
      ListeComposition<OBJET>::Element(unsigned int _pos) const {
      
        unsigned int compteur = 0 ;
      
        for(IterateurListeComposition<OBJET> i(*this) ; i.Valide() ; ++i) {
      
          ++ compteur ;
      
          if (_pos == compteur) {
      
            return i ;
      	
          }
        }
      
        return NULL ;
      					
      }
      
      
      template <class OBJET> void 
      ListeComposition<OBJET>::Enlever(unsigned int _pos) {
      
        unsigned int compteur = 0 ;
      
        for(IterateurListeComposition<OBJET> i(*this) ; i.Valide() ; ++i) {
      
          ++ compteur ;
      
          if (_pos == compteur) {
      
            i.Enlever() ;
            return ;
      	
          }
        }
      					
      }
      
      template <class OBJET> unsigned int 
      ListeComposition<OBJET>::Position(const Association< OBJET >& _el) const {
      
        unsigned int compteur = 0 ;
      
        for(IterateurListeComposition<OBJET> i(*this) ; i.Valide() ; ++i) {
      
          ++compteur ;
      
          if (_el == i)
      
            return compteur ;
        }
      
        return 0 ;
      
      }
    }
  }
}

