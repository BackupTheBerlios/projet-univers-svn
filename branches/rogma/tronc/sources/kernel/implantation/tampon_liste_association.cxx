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

#include <base/implantation/iterateur_tampon_liste_association.h>

namespace ProjetUnivers {

  namespace Base {

    namespace Implantation {
      
      
      
      template <class OBJET> 
      TamponListeAssociation<OBJET>::TamponListeAssociation()
       : ListeAbstraite(),nombreDeReferences(1)
      {}
      
      template <class OBJET> 
      TamponListeAssociation<OBJET>::~TamponListeAssociation() {
      
        Vider() ;
      }
      
      template <class OBJET> 
      TamponListeAssociation<OBJET>::TamponListeAssociation
      (const TamponListeAssociation< OBJET >& _l)
       : ListeAbstraite(),nombreDeReferences(1) {
      
        for(IterateurTamponListeAssociation<OBJET> i(_l) ; i.Valide() ; ++i)
      
          AjouterEnQueue(i) ;
      }
      
      template <class OBJET> void 
      TamponListeAssociation<OBJET>::AjouterEnTete(const Association<OBJET> _n) {
      
        Composition< NoeudAssociation<OBJET> > 
          nouveau_noeud(new NoeudAssociation<OBJET>(_n)) ;
      
        ListeAbstraite::AjouterEnTete(nouveau_noeud.Liberer()) ;
      
      }
      
      template <class OBJET> void 
      TamponListeAssociation<OBJET>::AjouterEnQueue(const Association<OBJET> _n) {
      
        Composition< NoeudAssociation<OBJET> > 
          nouveau_noeud(new NoeudAssociation<OBJET>(_n)) ;
      
        ListeAbstraite::AjouterEnQueue(nouveau_noeud.Liberer()) ;
      
      }
      
      template <class OBJET> void 
      TamponListeAssociation<OBJET>::Enlever(const EntierPositif& _pos) {
      
        EntierPositif compteur = 0 ;
      
        for(IterateurTamponListeAssociation<OBJET> i(*this) ; i.Valide() ; ++i) {
      
          ++ compteur ;
      
          if (_pos == compteur) {
      
            i.Enlever() ;
            return ;
      	
          }
        }
      					
      }
      
      template <class OBJET> EntierPositif 
      TamponListeAssociation<OBJET>::Position
      (const Association< OBJET >& _el) const {
      
        EntierPositif compteur = 0 ;
      
        for(IterateurTamponListeAssociation<OBJET> i(*this) ; i.Valide() ; ++i) {
      
          ++compteur ;
      
          if (_el == i)
      
            return compteur ;
        }
      
        return 0 ;
      
      }
      
      // Accès à une "copie", augmente la référence
      template <class OBJET> 
      TamponListeAssociation< OBJET >* 
      TamponListeAssociation<OBJET>::Prendre()
      {
        ++nombreDeReferences ;
        return this ;
      }
      
      ////////////////
      // Relache une "copie", diminue la référence et renvoie 
      // le nombre de références restantes.
      template <class OBJET> 
      Booleen
      TamponListeAssociation<OBJET>::Laisser()
      {
        --nombreDeReferences ;
        return nombreDeReferences == 0 ;
      }
      
      
      ////////////////////
      // renvoie le nombre de références.
      template <class OBJET> 
      EntierPositif 
      TamponListeAssociation<OBJET>::NombreDeReferences() const 
      {
        return nombreDeReferences ;
      }
    }
  }
}

