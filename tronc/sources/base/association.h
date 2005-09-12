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

#ifndef _PU_BASE_ASSOCIATION_H_
#define _PU_BASE_ASSOCIATION_H_


#include <base/exception_base.h>

namespace ProjetUnivers {

  namespace Base {

    template <class OBJET> class Composition ;
    
   
    /// Association d'un élément d'une classe d'objets.  
    /*!
    Utilisation
    
      Cette classe sert à désigner des objets en lecture et comme retours 
      de fonctions d'accès. Ainsi, lorsqu'on a besoin de désigner 
      un objet existant on utilise cette classe.
    */
    template <class OBJET> class Association {
    public:
    
      // *************************
      /// @name Constructeurs
      // *************************      
      // @{  
    
    
      /// Constructeur par défaut.
      Association()
        : pt(NULL)
      {}

      /// Constructeur, prends une référence à l'objet.
      Association(const OBJET& _x)
        : pt((OBJET*)&_x)
      {}
    
      /// Constructeur de copie.
      Association(const Association<OBJET>& _x)
      : pt(_x.pt)
      {}
    	
      /// Conversion de Composition en Association
      Association(const Composition<OBJET>& _x) ;
 
      /// Conversion depuis un autre type.
      template <class OBJET2> Association(const Association<OBJET2>& _x)
      : pt(_x.pt)
      {}

      /// Conversion depuis un autre type.
      template <class OBJET2> Association(const Composition<OBJET2>& _x)
      : pt(_x.pt)
      {}

    
      // @}
      // *************************
      /// @name Opérateurs de déréférenciation
      // *************************      
      // @{  
    
    
      /// Vérifie que le pointeur est non NULL avant d'appeler.
      OBJET* operator ->() const ;
    
      /// Accès à l'objet pointé.
      OBJET& operator *() const 
      {
        return *pt ;
      }

    
      // @}
      // *************************
      /// @name Affectations
      // *************************      
      // @{  
    
    
      /// Affectation d'une autre association.
      Association<OBJET>& operator =(const Association<OBJET>& _r)
      {
        pt = _r.pt ;
        return *this ;
      }
    
      /// Affectation avec un pointeur d'agregation.
      Association<OBJET>& operator =(const Composition<OBJET>& _x) ;
     
      
      // @}
      // *************************
      /// @name Comparaisons
      // *************************      
      // @{  
    

      /// Egalité avec une autre association.
      template <class OBJET2> 
      Booleen operator == (const Association<OBJET2>& _x) const
      {
        return pt == _x.pt ;
      }

      /// Egalité avec une autre association.
      Booleen operator == (const Association<OBJET>& _x) const
      {
        return pt == _x.pt ;
      }
    
      /// Comparaison avec une agrégation.
      Booleen operator == (const Composition<OBJET>& _x) const ;
    
      /// Comparaison avec un pointeur.
      template <class OBJET2> Booleen operator ==(const OBJET2* _x) const {
    		
        return pt == _x ;
      }

      /// Différence avec une autre association.
      template <class OBJET2> 
      Booleen operator !=(const  Association<OBJET2>& _x) const 
      {
        return pt != _x.pt ;
      }

      /// Différence avec une autre association.
      Booleen operator !=(const  Association<OBJET>& _x) const 
      {
        return pt != _x.pt ;
      }

    
      /// Différence avec un pointeur.
      template <class OBJET2> Booleen operator !=(const OBJET2* _x) const {
    		
        return pt != _x ;
      }

      /// Comparaison avec une agrégation.
      Booleen operator != (const Composition<OBJET>& _x) const ;
    
      // @}
    private:
    
    
      /// pointeur sur l'ojet en association.
      OBJET*	pt ;
    

      // *************************
      /// @name Interdictions
      // *************************      
      // @{  
    
    
      /// Affectation d'un pointeur. 
      /*!
        Cette méthode est interdite, donc on la déclare explicitement en privé.
      */
      template <typename OBJET2> Association<OBJET>& operator =(OBJET2* _p) ;
    
    
      // @}
      
      template<class Y> friend class Association ;
      template<class Y> friend class Composition ;
      
    };
  }
}

#include <base/implantation/association.cxx>

#endif

	
