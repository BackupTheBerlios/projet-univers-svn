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

#include <base/composition.h>
#include <base/implantation/iterateur_tampon_liste_valeur.h>
#include <base/implantation/noeud_valeur.h>


namespace ProjetUnivers {

  namespace Base {

    namespace Implantation {
      
      template <typename VALEUR> 
      TamponListeValeur<VALEUR>::TamponListeValeur()
      : ListeAbstraite(), nombreDeReferences(1)
      {}
      
          
      template <typename VALEUR> 
      TamponListeValeur<VALEUR>::~TamponListeValeur()
      {}
          
      template <typename VALEUR> 
      TamponListeValeur<VALEUR>::
      TamponListeValeur(const TamponListeValeur< VALEUR >& _liste)
      : ListeAbstraite(), nombreDeReferences(1)
      {
        for(IterateurTamponListeValeur<VALEUR> i(_liste) ; i.Valide() ; ++i)
      
          AjouterEnQueue(i) ;
        
      }
      
      
      template <typename VALEUR> 
      void TamponListeValeur<VALEUR>::AjouterEnTete(const VALEUR& _elt)
      {
        Composition< NoeudValeur<VALEUR> > 
          nouveau_noeud(new NoeudValeur<VALEUR>(_elt)) ;
      
        ListeAbstraite::AjouterEnTete(nouveau_noeud.Liberer()) ;
      
        
      }
        
      template <typename VALEUR>
      void TamponListeValeur<VALEUR>::AjouterEnQueue(const VALEUR& _elt)
      {
        
        Composition< NoeudValeur<VALEUR> > 
          nouveau_noeud(new NoeudValeur<VALEUR>(_elt)) ;
      
        ListeAbstraite::AjouterEnQueue(nouveau_noeud.Liberer()) ;
      }
        
          
      template <typename VALEUR> 
      TamponListeValeur<VALEUR>* TamponListeValeur<VALEUR>::Prendre()
      {
        ++nombreDeReferences ;
        return this ;
      
      }
        
          
          
      template <typename VALEUR> 
      Booleen TamponListeValeur<VALEUR>::Laisser()
      {
        --nombreDeReferences ;
        return nombreDeReferences == 0 ;
        
      }
      
      
      template <typename VALEUR>    
      EntierPositif TamponListeValeur<VALEUR>::
      Position(const VALEUR& _element) const 
      {
        EntierPositif compteur = 0 ;
      
        for(IterateurTamponListeValeur<VALEUR> i(*this) ; i.Valide() ; ++i) {
      
          ++compteur ;
      
          if (_element == i)
      
            return compteur ;
        }
      
        return 0 ;
        
      }
      
      template <typename VALEUR>
      void 
      TamponListeValeur<VALEUR>::Enlever(const EntierPositif& _position)
      {
        EntierPositif compteur = 0 ;
      
        for(IterateurTamponListeValeur<VALEUR> i(*this) ; i.Valide() ; ++i) {
      
          ++ compteur ;
      
          if (_position == compteur) {
      
            i.Enlever() ;
            return ;
        
          }
        }
        
      }
      
      template <typename VALEUR>
      EntierPositif 
      TamponListeValeur<VALEUR>::NombreDeReferences() const
      {
         return nombreDeReferences ;
      }
    }
  }
}
