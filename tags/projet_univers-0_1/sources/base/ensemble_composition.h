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
#include <set>

namespace ProjetUnivers {

  namespace Base {
    
    template <typename OBJET> class EnsembleAssociation ;
    template <typename OBJET> class IterateurEnsembleComposition ;
    
    ///  Repr�sente un ensemble d'�l�ments d'une classe d'objets en composition.
    
    /*!
     M�mes utilisations que pour Composition, en ce qui concerne les ensembles.
    */
    template <typename OBJET> class EnsembleComposition 
    {
    public:
    
    
      
      // *************************
      /// @name Construction
      // *************************      
      // @{  
     
      
      // Constructeur par d�faut.
      EnsembleComposition() ;
    
      // Destructeur.
      ~EnsembleComposition() ;
    
      // Aggrege un �l�ment � l'ensemble.
      void Ajouter(OBJET* _elt);
    
      // Enl�ve l'�l�ment _el, s'il n'y est pas ne fait rien.
      void Enlever(const Association<OBJET>& _el) ;
    
      /// Conversion.
      operator EnsembleAssociation<OBJET>() const ;

      /// Enl�ve tous les �l�ments.
      void Vider() ;
    
      // @}   
    
      // *************************
      /// @name Consultation
      // *************************      
      // @{  
     

      /// Acc�s au nombre d'�l�ments.
      EntierPositif NombreDElements() const ;
    
      /// Determine si _el fait partie de l'ensemble.
      Booleen Contient(const Association<OBJET>& _el) const ;
    
 
      // @}


    private:
    
      std::set<OBJET*> ensemble ;
      
      friend class IterateurEnsembleComposition<OBJET> ;

      
    };
    

  }
}

#include <base/implantation/ensemble_composition.cxx>


#endif
