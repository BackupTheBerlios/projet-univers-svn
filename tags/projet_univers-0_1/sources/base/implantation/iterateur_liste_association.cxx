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

#include <base/association.h>

namespace ProjetUnivers {

  namespace Base {

    
    namespace Implantation {
            
      template <class OBJET> 
      IterateurListeAssociation<OBJET>::operator Association<OBJET>()
      {
        return noeudCourant()->element ;
      
      }
      
      ///////////////
      // Renvoie l'�l�ment courant en r�f�rence.
      template <class OBJET> 
      IterateurListeAssociation<OBJET>::operator const OBJET&()
      {
        return *noeudCourant()->element ;
      
      }
      
      
      template <class OBJET> 
      IterateurListeAssociation<OBJET>::IterateurListeAssociation
      (const ListeAssociation<OBJET>& _liste)
      : IterateurListe(*_liste.liste),
      liste((TamponListeAssociation<OBJET>*)_liste.liste)
      {
        liste->Prendre() ;
      
      }
      
      
      ///////////////////
      // Destructeur.
      template <class OBJET> 
      IterateurListeAssociation<OBJET>::~IterateurListeAssociation()
      {
        if (liste->Laisser())
      
          delete liste ;
      }
      
      
      
      template <class OBJET> OBJET* 
      IterateurListeAssociation<OBJET>::operator ->() const {
      
        return (noeudCourant()->element).operator->() ;
      
      }
      

    }
  }
}
