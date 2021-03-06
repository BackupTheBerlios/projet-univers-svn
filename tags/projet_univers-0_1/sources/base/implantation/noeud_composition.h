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

#ifndef _PU_BASE_IMPLANTATION_NOEUD_COMPOSITION_H_
#define _PU_BASE_IMPLANTATION_NOEUD_COMPOSITION_H_

#include <base/implantation/noeud_abstrait.h>

namespace ProjetUnivers {

  namespace Base {
    
    namespace Implantation {
        
      template <class OBJET> class IterateurListeComposition ;
      
      
      
      ///  Classe des noeuds de ListeComposition.
      template <class OBJET> class NoeudComposition : public NoeudAbstrait {
      public:
      
        /// Constructeur.
        NoeudComposition(OBJET* _elt) ;
      
        /// Lib�re l'�l�ment .
        OBJET* Liberer() ;
      
      
      private:
      
        /// El�ment.
        Composition<OBJET>	element ;
      
        friend class IterateurListeComposition<OBJET> ;
      
      };
      
      
    }
  }
}

#include <base/implantation/noeud_composition.cxx>

#endif 


