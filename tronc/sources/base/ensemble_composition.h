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

#ifndef _PU_BASE_ENSEMBLE_COMPOSITION_H_
#define _PU_BASE_ENSEMBLE_COMPOSITION_H_

#include <base/association.h>
#include <base/implantation/liste_composition.h>


namespace ProjetUnivers {

  namespace Base {
    
    
    ///  Représente un ensemble d'éléments d'une classe d'objets en composition.
    
    /// UTILISATION
    ///   Même utilisations que pour Composition, en ce qui concerne 
    ///   les ensembles.
    template <class OBJET> class EnsembleComposition 
        : public ListeComposition<OBJET> {

    public:
    
    
      
      // *************************
      /// @name Construction
      // *************************      
      // @{  
     
      
      // Constructeur par défaut.
      EnsembleComposition() ;
    
      // Destructeur par défaut.
      ~EnsembleComposition() ;
    
      // Aggrege un élément à l'ensemble.
      void Ajouter(OBJET* _elt);
    
      // Enlève l'élément _el, s'il n'y est pas ne fait rien.
      void Enlever(const Association< OBJET >& _el) ;
    
      // @}   
    
      // *************************
      /// @name Consultation
      // *************************      
      // @{  
     
    
      /// Determine si _el fait partie de l'ensemble.
      Booleen Contient(const Association< OBJET >& _el) const ;
    
 
      // @}   
    };
    
#include <base/implantation/ensemble_composition.cxx>

  }
}



#endif
