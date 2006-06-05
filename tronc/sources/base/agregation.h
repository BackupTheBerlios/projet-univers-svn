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

#ifndef _PU_BASE_AGREGATION_H_
#define _PU_BASE_AGREGATION_H_

#include <base/exception_base.h>
#include <boost/shared_ptr.hpp>

namespace ProjetUnivers {

  namespace Base {

   
    /// Une agrégation, ou composition faible.
    /*!
    Une agrégation est une relation entre un tout et ses parties mais qui, 
    contrairement à la composition, permet de partager ses parties.

    @par Utilisation
    
      A utiliser en remplacement du couple Composition/Association lorsqu'on 
      souhaite que l'objet soit partagé par plusieurs propriétaires. Dès que 
      l'objet en question n'est plus agrégé, alors il est automatiquement 
      détruit. 
    @warning
      On ne doit utiliser que des agregations.
      
    @par Implantation
      Réalisé avec boost::shared_ptr.
    @par Test
      Testé le 13/05/2006 avec TestAgregation :
      - Conversion implicite
      - Destruction automatique
    
    */
    template <typename OBJET> class Agregation {
    public:
    
      // *************************
      /// @name Constructeurs
      // *************************      
      // @{  
    
    
      /// Constructeur.
      Agregation(OBJET* _pointeur = NULL) ;

      /// Constructeur de copie.
      Agregation(const Agregation<OBJET>&) ;
      
      /// Conversion depuis un autre type.
      template <typename OBJET2> 
      Agregation(const Agregation<OBJET2>& _agregation) 
      : pointeur(_agregation.pointeur)
      {}

    
      // @}
      // *************************
      /// @name Opérateurs de déréférenciation
      // *************************      
      // @{  
    
    
      /// Vérifie que le pointeur est non NULL avant d'appeler.
      OBJET* operator ->() const ;
    
      /// Accès à l'objet pointé.
      OBJET& operator *() const ;

    
      // @}
      // *************************
      /// @name Affectations
      // *************************      
      // @{  
    
    
      /// Affectation avec un pointeur d'agregation.
      Agregation<OBJET>& operator=(const Agregation<OBJET>&) ;

      template <typename OBJET2> 
      Agregation<OBJET>& operator=(const Agregation<OBJET2>& _agregation)
      {
        pointeur = _agregation.pointeur ;
        return *this ;
      }
     
      
      // @}
      // *************************
      /// @name Comparaisons
      // *************************      
      // @{  
    

      /// Comparaison avec une agrégation.
      Booleen operator == (const Agregation<OBJET>&) const ;

      /// Différence avec une autre agrégation.
      template <class OBJET2> 
      Booleen operator!=(const Agregation<OBJET2>& _agregation) const
      {
        return ! (this->pointeur == _agregation.operator->())  ;
      }

      /// Comparaison avec une agrégation.
      Booleen operator != (const Agregation<OBJET>&) const ;
    
      // @}
    private:
    
    
      /// pointeur sur l'objet en association.
      boost::shared_ptr<OBJET> pointeur ;
      template<class OBJET2> friend class Agregation ;

    };
  }
}

#include <base/implantation/agregation.cxx>

#endif

  
