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

    template <typename OBJET> class EnsembleAssociation ;
    namespace Implantation
    {
      template <typename OBJET> class TamponEnsembleAssociation ;
    }
    
    
    /// It�rateur sur les ensemble en association.
    template <typename OBJET> class IterateurEnsembleAssociation 
    {
    public:
    
      /// Constructeur.
      IterateurEnsembleAssociation(const EnsembleAssociation<OBJET>&) ;

      /// Passe � l'�l�ment suivant.
      void operator ++() ;
    
      /// Passe � l'�l�ment pr�c�dent.
      void operator --() ;
    

    // @}
    // ***********************
    /// @name M�thodes d'acc�s
    // ***********************
    // @{

      /// Dit si l'it�rateur est valide.
      Booleen Valide() const ;      
      
      /// Renvoie l'�l�ment courant en association.
      operator Association<OBJET>() ;
    
      /// Renvoie l'�l�ment courant en r�f�rence.
      operator const OBJET&() ;
     
      /// Op�rateur de d�r�f�renciation.
      OBJET* operator ->() const ;
    
      /// Op�rateur de d�r�f�renciation.
      Association<OBJET> operator *() const ;

    
    // @}

    private:
    
      Implantation::TamponEnsembleAssociation<OBJET>* tampon ;
      typename std::set<OBJET*>::iterator iterateur ;            
      
    };

  }
}

#include <base/implantation/iterateur_ensemble_association.cxx>


#endif 


