/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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

#ifndef _PU_BASE_IMPLANTATION_TAMPON_ENSEMBLE_VALEUR_H_
#define _PU_BASE_IMPLANTATION_TAMPON_ENSEMBLE_VALEUR_H_

#include <vector>

namespace ProjetUnivers {
  namespace Base {

    template <typename Valeur> class IterateurEnsembleValeur ;
    template <typename Valeur> class EnsembleValeur ;

    namespace Implantation {

      template <typename Valeur> class TamponEnsembleValeur 
      {
      public:


        /// Obtient une référence, et donc augmente le nombre de référencants.
        TamponEnsembleValeur<Valeur>* Prendre()
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

        TamponEnsembleValeur()
        : nombreDeReferences(1)
        {}

        TamponEnsembleValeur(const TamponEnsembleValeur& _tampon)
        : nombreDeReferences(1), ensemble(_tampon.ensemble) 
        {}

        
        /// Lorsque ce nombre tombe à zéro, il y a destruction.
        EntierPositif nombreDeReferences ;
        
        std::vector<Valeur> ensemble ;
        
        friend class IterateurEnsembleValeur<Valeur> ;
        friend class EnsembleValeur<Valeur> ;        
      };
    }
  }
}
#endif
