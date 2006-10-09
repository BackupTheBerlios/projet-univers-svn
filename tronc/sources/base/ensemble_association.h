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

#ifndef _PU_BASE_ENSEMBLE_ASSOCIATION_H_
#define _PU_BASE_ENSEMBLE_ASSOCIATION_H_


#include <set>
#include <base/association.h>
#include <base/implantation/liste_association.h>
#include <base/implantation/iterateur_liste_association.h>

namespace ProjetUnivers {

  namespace Base {


    namespace Implantation
    {
      template <typename OBJET> class TamponEnsembleAssociation ;
    }
    
    template <typename OBJET> class IterateurEnsembleAssociation ;
    template <typename OBJET> class EnsembleComposition ;
    
    ///  Représente un ensemble d'élément d'une classe d'objets en association.
    
    /*!
      Utilisation
      
      Même utilisations que pour Association, en ce qui concerne les ensembles.
    */
    template <typename OBJET> class EnsembleAssociation 
    {
    public:
    
    
      
      // *************************
      /// @name Construction
      // *************************      
      // @{      
      

      /// Constructeur par défaut.
      
      /// Construit un ensemble vide.
      EnsembleAssociation() ; 
    
      /// Constructeur de copie.
      EnsembleAssociation(const EnsembleAssociation<OBJET>& _e);
    
      /// Ajoute un élément à l'ensemble.
      void Ajouter(const Association<OBJET>& _elt);

      /// Ajoute des éléments à l'ensemble.
      void Ajouter(const EnsembleAssociation<OBJET>& _elt);
    
      /// Enlève l'élément _el, s'il n'y est pas ne fait rien.
      void Enlever(const Association<OBJET>& _el) ;
    
      /// Enlève tous les éléments.
      void Vider() ;
    
      // @}
      // *************************
      /// @name Consultation
      // *************************      
      // @{      

      /// Accès au nombre d'éléments.
      EntierPositif NombreDElements() const ;
    
      /// Determine si _el fait partie de l'ensemble.
      Booleen Contient(const Association<OBJET>& _el) const ;
    
      /// Egalité de deux ensembles.
      Booleen operator==(const EnsembleAssociation<OBJET>& _r) const ;

      // @}      
      
    private:
    
      Implantation::TamponEnsembleAssociation<OBJET>* tampon ;

      friend class IterateurEnsembleAssociation<OBJET> ;
      friend class EnsembleComposition<OBJET> ;
    };
    
    
  }
}

#include <base/implantation/ensemble_association.cxx>



#endif
