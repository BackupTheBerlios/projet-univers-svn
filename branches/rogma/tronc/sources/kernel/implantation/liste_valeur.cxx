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

#include <base/implantation/iterateur_liste_valeur.h>
#include <base/implantation/tampon_liste_valeur.h>

namespace ProjetUnivers {

  namespace Base {

    namespace Implantation {

      
      template <typename VALEUR>
      ListeValeur<VALEUR>::ListeValeur()
      : liste(new TamponListeValeur<VALEUR>())
      {}
          
      template <typename VALEUR>
      ListeValeur<VALEUR>::~ListeValeur()
      {
      
        if(liste->Laisser())
      
          delete liste ;
        
      }
      
      template <typename VALEUR>    
      ListeValeur<VALEUR>::ListeValeur(const ListeValeur<VALEUR>& _liste)
      : liste(_liste.liste->Prendre()) 
      {}
      
      template <typename VALEUR>
      void ListeValeur<VALEUR>::AjouterEnTete(const VALEUR& _element)
      {
        // deux cas : 
        // la liste n'est pas partagée, on peut lui ajouter directement 
        // la liste est partagée, on copie puis on ajoute 
      
        if (liste->NombreDeReferences() > 1)
        {
      
      
          TamponListeValeur<VALEUR>* temp 
            = new TamponListeValeur<VALEUR>(*liste) ;
      
          // pas besoin de tester, il ya d'autres références
          liste->Laisser() ;
      
          liste = temp ;
      
        }
      
        // dans tous les cas on ajoute
        liste->AjouterEnTete(_element) ;
      
      
      }
      
      template <typename VALEUR>
      void ListeValeur<VALEUR>::AjouterEnTete(const ListeValeur<VALEUR>& _liste)
      {
        // deux cas : 
        // la liste n'est pas partagée, on peut lui ajouter directement 
        // la liste est partagée, on copie puis on ajoute 
      
        if (liste->NombreDeReferences() > 1)
        {
      
      
          TamponListeValeur<VALEUR>* temp 
            = new TamponListeValeur<VALEUR>(*liste) ;
      
          // pas besoin de tester, il ya d'autres références
          liste->Laisser() ;
      
          liste = temp ;
      
        }
      
        // dans tous les cas on ajoute
        liste->AjouterEnTete(_liste) ;
      
      
      
      
      }
      
      template <typename VALEUR>
      void ListeValeur<VALEUR>::AjouterEnQueue(const VALEUR& _elt)
      {
        // deux cas : 
        // la liste n'est pas partagée, on peut lui ajouter directement 
        // la liste est partagée, on copie puis on ajoute 
      
        if (liste->NombreDeReferences() > 1)
        {
      
      
          TamponListeValeur<VALEUR>* temp 
            = new TamponListeValeur<VALEUR>(*liste) ;
      
          // pas besoin de tester, il ya d'autres références
          liste->Laisser() ;
      
          liste = temp ;
      
        }
      
        // dans tous les cas on ajoute
        liste->AjouterEnQueue(_elt) ;
      
      
      
      }
      
      template <typename VALEUR>
      void ListeValeur<VALEUR>::Enlever(const EntierPositif& _position)
      {
      
        if (liste->NombreDeReferences() > 1)
        {
      
          TamponListeValeur<VALEUR>* temp 
            = new TamponListeValeur<VALEUR>(*liste) ;
      
          // pas besoin de tester, il ya d'autres références
          liste->Laisser() ;
      
          liste = temp ;
      
        }
      
        // dans tous les cas on enlève
        liste->Enlever(_position) ;          
      
      }
      
      template <typename VALEUR>
      ListeValeur<VALEUR>& ListeValeur<VALEUR>::
      operator = (const ListeValeur<VALEUR> &_l)
      {
      
      
        if (liste)
        {
      
          if (liste->Laisser())
      
            delete liste ;
        }
        
        
        liste = _l.liste->Prendre() ;
      
      
        return *this ;
      
      
      }
      
      
      
      template <typename VALEUR>
      Booleen ListeValeur<VALEUR>::Contient(const VALEUR& _el) const
      {
      
      }
      
      template <typename VALEUR>
      EntierPositif ListeValeur<VALEUR>::Position(const VALEUR& _el) const
      {
         return liste->Position(_el) ;
      }
      
      
      template <typename VALEUR>
      void ListeValeur<VALEUR>::Vider()
      {
        
        // on laisse la liste courante
        if (liste->Laisser())
        
          delete liste ;
        
        // et on s'en choppe une vide
        liste = new TamponListeValeur<VALEUR>() ;
        
      }
      
      /// Accès au nombre d'éléments.
      template <typename VALEUR>
      EntierPositif ListeValeur<VALEUR>::NombreDElements() const
      {
        return liste->NombreDElements() ;
      }
      
      
    }
  }
}

          
          
