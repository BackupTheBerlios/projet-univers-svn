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
    template <class OBJET, typename VALEUR> class FonctionObjetValeur ;
    
   
    /// Association d'un �l�ment d'une classe d'objets.  
    /*!
    Utilisation
    
      Cette classe sert � d�signer des objets en lecture et comme retours 
      de fonctions d'acc�s. Ainsi, lorsqu'on a besoin de d�signer 
      un objet existant on utilise cette classe.
    */
    template <class OBJET> class Association {
    public:
    
      // *************************
      /// @name Constructeurs
      // *************************      
      // @{  
    
    
      /// Constructeur par d�faut.
      Association()
        : pt(NULL)
      {}

      /// Constructeur, prends une r�f�rence � l'objet.
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
      : pt((OBJET*)_x.pt)
      {}

      /// Conversion depuis un autre type.
      template <class OBJET2> Association(const Composition<OBJET2>& _x)
      : pt(_x.pt)
      {}

    
      // @}
      // *************************
      /// @name Op�rateurs de d�r�f�renciation
      // *************************      
      // @{  
    
    
      /// V�rifie que le pointeur est non NULL avant d'appeler.
      OBJET* operator ->() const ;
    
      /// Acc�s � l'objet point�.
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
    

      /// Egalit� avec une autre association.
      template <class OBJET2> 
      Booleen operator == (const Association<OBJET2>& _x) const
      {
        return pt == _x.pt ;
      }

      /// Egalit� avec une autre association.
      Booleen operator == (const Association<OBJET>& _x) const
      {
        return pt == _x.pt ;
      }
    
      /// Comparaison avec une agr�gation.
      Booleen operator == (const Composition<OBJET>& _x) const ;
    
      /// Comparaison avec un pointeur.
      template <class OBJET2> Booleen operator ==(const OBJET2* _x) const {
    		
        return pt == _x ;
      }

      /// Diff�rence avec une autre association.
      template <class OBJET2> 
      Booleen operator !=(const  Association<OBJET2>& _x) const 
      {
        return pt != _x.pt ;
      }

      /// Diff�rence avec une autre association.
      Booleen operator !=(const  Association<OBJET>& _x) const 
      {
        return pt != _x.pt ;
      }

    
      /// Diff�rence avec un pointeur.
      template <class OBJET2> Booleen operator !=(const OBJET2* _x) const {
    		
        return pt != _x ;
      }

      /// Comparaison avec une agr�gation.
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
        Cette m�thode est interdite, donc on la d�clare explicitement en priv�.
      */
      template <typename OBJET2> Association<OBJET>& operator =(OBJET2* _p) ;
    
    
      // @}
      
      template<class ANY> friend class Association ;
      template<class ANY> friend class Composition ;
      template <class ANY,typename VALEUR> friend class FonctionObjetValeur ;
    };
  }
}

#include <base/implantation/association.cxx>

#endif

	
