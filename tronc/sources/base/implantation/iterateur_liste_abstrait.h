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

#ifndef _PU_BASE_ITERATEUR_LISTE_ABSTRAIT_H_
#define _PU_BASE_ITERATEUR_LISTE_ABSTRAIT_H_

#include <base/implantation/liste_abstraite.h>
#include <base/implantation/noeud_abstrait.h>
#include <base/association_virtuelle.h>
#include <base/association.h>

namespace ProjetUnivers {

  namespace Base {
  
    
    
    /// Classe de base des itérateurs sur les listes.

    class IterateurListeAbstrait {
    public:
    
    

      /// Constructeur.
      IterateurListeAbstrait(
          const Association< NoeudAbstrait >& n, 
    			const Association< ListeAbstraite >& l) ;
    
      /// Destructeur.
      ~IterateurListeAbstrait() ;
    
      /// Passe à l'élément suivant.
      void operator ++() ;
    
      /// Passe à l'élément précédent.
      void operator --() ;
    
      /// Dit si l'itérateur est valide.
      Booleen Valide() const ;
    
      /// renvoie le nombre d'éléments de la liste.
      unsigned int NombreDElements() const ;
    
    
    protected:
    
      /// Noeud courant.
      DECLARATION_ASSOCIATION_VIRTUELLE(NoeudAbstrait,noeudCourant)
    
      /// Liste parcourue.
      DECLARATION_ASSOCIATION_VIRTUELLE(ListeAbstraite,liste)
    
    
    };
  }
}
#endif


