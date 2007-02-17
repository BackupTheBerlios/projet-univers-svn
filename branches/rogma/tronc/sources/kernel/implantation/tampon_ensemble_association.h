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

#ifndef _PU_BASE_IMPLANTATION_TAMPON_ENSEMBLE_ASSOCIATION_H_
#define _PU_BASE_IMPLANTATION_TAMPON_ENSEMBLE_ASSOCIATION_H_



#include <set>
#include <base/association.h>

namespace ProjetUnivers {

  namespace Base {

    template <typename OBJET> class IterateurEnsembleAssociation ;
    template <typename OBJET> class EnsembleComposition ;

    namespace Implantation {

      template <typename OBJET> class TamponEnsembleAssociation 
      {
      public:


        /// Obtient une référence, et donc augmente le nombre de référencants.
        TamponEnsembleAssociation<OBJET>* Prendre()
        {
          ++nombreDeReferences ;
          return this ;
        }
      
        /// Relache une référence et renvoie vrai s'il faut la détruire.
        Booleen Laisser()
        {
          --nombreDeReferences ;
          
          if (nombreDeReferences == 0)

            return VRAI ;
          else
            return FAUX ;
        }

        TamponEnsembleAssociation()
        : nombreDeReferences(1)
        {}

        TamponEnsembleAssociation(const TamponEnsembleAssociation& _tampon)
        : nombreDeReferences(1), ensemble(_tampon.ensemble) 
        {}

        
        /// Lorsque ce nombre tombe à zéro, il y a destruction.
        EntierPositif nombreDeReferences ;
        
        std::set<OBJET*> ensemble ;
        
        friend class IterateurEnsembleAssociation<OBJET> ;
        friend class EnsembleComposition<OBJET> ;        
      };
    }
  }
}
#endif
