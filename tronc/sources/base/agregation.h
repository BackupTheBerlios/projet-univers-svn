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

   
    /// Une agr�gation, ou composition faible.
    /*!
    Une agr�gation est une relation entre un tout et ses parties mais qui, 
    contrairement � la composition, permet de partager ses parties.

    Utilisation
    
      A utiliser en remplacement du couple Composition/Association lorsqu'on 
      souhaite que l'objet soit partag� par plusieurs propri�taires. D�s que 
      l'objet en question n'est plus agr�g�, alors il est automatiquement 
      d�truit. 
    @warning
      On ne doit utiliser que des agregations.
      
    Implantation
      R�alis� avec boost::shared_ptr.
    
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
      /// @name Op�rateurs de d�r�f�renciation
      // *************************      
      // @{  
    
    
      /// V�rifie que le pointeur est non NULL avant d'appeler.
      OBJET* operator ->() const ;
    
      /// Acc�s � l'objet point�.
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
    

      /// Comparaison avec une agr�gation.
      Booleen operator == (const Agregation<OBJET>&) const ;

      /// Diff�rence avec une autre agr�gation.
      template <class OBJET2> 
      Booleen operator!=(const Agregation<OBJET2>& _agregation) const
      {
        return ! (this->pointeur == _agregation.operator->())  ;
      }

      /// Comparaison avec une agr�gation.
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

  
