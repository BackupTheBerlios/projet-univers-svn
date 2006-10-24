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
      
      ///////////////
      // Renvoie l'�l�ment courant en r�f�rence.
      template <class OBJET> 
      IterateurListeComposition<OBJET>::operator const OBJET&() 
      {
        return *noeudCourant()->element ;
      }
      
      
      ///////////////
      // Renvoie l'�l�ment courant en association.
      template <class OBJET> 
      IterateurListeComposition<OBJET>::operator Association< OBJET >() 
      {
        return noeudCourant()->element ;
      
      }
      
      
      
      template <class OBJET> OBJET* 
      IterateurListeComposition<OBJET>::operator ->() const {
      
      //  OBJET* resultat = (OBJET*)(noeudCourant()->element) ;
      //
      //  if (resultat == NULL)
      //
      //    throw ExceptionBase("IterateurListeComposition<OBJET>::operator ->");
      
        return (noeudCourant()->element).operator->() ;
      }
      
      template <class OBJET> OBJET* 
      IterateurListeComposition<OBJET>::Liberer() {
      
        return noeudCourant()->Liberer() ;
      }
      
      template <class OBJET> 
      IterateurListeComposition<OBJET>::IterateurListeComposition
      (const ListeComposition<OBJET>& _l)
        : IterateurListe(_l)
      {}
      
      template <class OBJET> 
      IterateurListeComposition<OBJET>::IterateurListeComposition
      (const IterateurListeComposition<OBJET>& _i)
        : IterateurListe(*_i.liste())
      {}
      
      
      template <class OBJET> void 
      IterateurListeComposition<OBJET>::AjouterApres(OBJET* _elt) {
      	
        Composition<NoeudComposition<OBJET> > n_node(
            new NoeudComposition<OBJET>(_elt)) ;
      
        IterateurListe::AjouterApres(n_node.Liberer()) ;
      }
      
      template <class OBJET> void 
      IterateurListeComposition<OBJET>::AjouterAvant(OBJET* _elt) {
      
        Composition<NoeudComposition<OBJET> > n_node(
            new NoeudComposition<OBJET>(_elt)) ;
      
        IterateurListe::AjouterAvant(n_node.Liberer()) ;
      
      }
      
      ///////////////////
      // Ajoute une liste.
      template <class OBJET> void 
      IterateurListeComposition<OBJET>::Ajouter
      (const ListeComposition< OBJET >& _nouveaux) {
      
        liste()->AjouterEnTete(_nouveaux) ;
      
      }
      
      
      template <class OBJET> void 
      IterateurListeComposition<OBJET>::Enlever() {
      
        Composition< OBJET > temp(Liberer()) ;
      
        IterateurListe::Enlever() ;
      
      }
    }
  }
}
