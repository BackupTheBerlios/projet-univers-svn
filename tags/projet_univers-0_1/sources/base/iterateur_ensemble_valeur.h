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

#ifndef _PU_BASE_ITERATEUR_ENSEMBLE_ASSOCIATION_H_
#define _PU_BASE_ITERATEUR_ENSEMBLE_ASSOCIATION_H_

#include <set>
#include <iterator>
#include <base/association.h>

namespace ProjetUnivers {

  namespace Base {

    template <typename Valeur> class EnsembleValeur ;
    
    
    /// Itérateur sur les ensemble de valeur.
    template <typename Valeur> class IterateurEnsembleValeur 
    {
    public:
    
      /// Constructeur.
      IterateurEnsembleAssociation(const EnsembleValeur<Valeur>&) ;

      /// Passe à l'élément suivant.
      void operator ++() ;
    
      /// Passe à l'élément précédent.
      void operator --() ;
    

      // @}
      // ***********************
      /// @name Méthodes d'accès
      // ***********************
      // @{

      /// Dit si l'itérateur est valide.
      Booleen Valide() const ;      
     
      /// Opérateur de déréférenciation.
      Valeur* operator ->() const ;
    
      /// Opérateur de déréférenciation.
      Valeur& operator*() const ;
    
      // @}

    private:
    
      Implantation::TamponEnsembleValeur<Valeur>* tampon ;
      typename std::set<Valeur>::iterator iterateur ;            
      
    };

  }
}

#include <base/implantation/iterateur_ensemble_valeur.cxx>


#endif 


