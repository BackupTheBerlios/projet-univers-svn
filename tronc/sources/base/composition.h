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


#ifndef COMPOSITION_H
#define COMPOSITION_H




#include <base/exception_base.h>

namespace ProjetUnivers {

  namespace Base {
  
    template <class OBJET> class Association ;    
    
    ///  Classe g�n�rique r�alisant la composition d'un �l�ment d'une classe 
    ///  d'objets.
    
    /*!
    UTILISATIONS
    	
      Utilisez cette classe partout ! Mais surtout dans les trois cas suivants:
    
      1. Pour pointer sur le r�sultat d'une fonction fabriquante. La cr�ation 
      se fait avec un new, il n'y a pas de destruction � g�rer. Cette 
      utilisation peut se r�veler pratique si vous utilisez des exceptions, 
      en effet, lorsqu'une exception est lev�e, on sort du block et il faut 
      d�truire les jets allou�s dans le tas. Un simple pointeur est insuffisant 
      pour une bonne gestion des exceptions.
    
    
    \code
      Classe1* fabriquant() {
    
      // r�sultat :
      Composition<Classe1>	res = new Classe1(...)
    
      // traitements 
      // N.B. Si une exception est lev�e ici, l'jet sera d�truit.
      .....
    
      // on se s�pare de l'jet point� :
      return res.release() ;
      }
    \endcode

    
      2. Pour pointer sur les attributs agr�g�s � une classe. Cela �vite 
      d'�crire un destructeur, car celui g�n�r� par defaut par les compilateurs 
      app�le le destructeur de tous les attributs.
    
    Exemple
    
    \code
      class A {
    
      ....
      };
    
      class B {
    
      Composition<A>	attribut_agr�g�_classe_A ;
    
      };
    \endcode
    END
    
      3. Pour g�rer une variable locale.
    
    Exemple
    \code    
    
      <i>type</i> <b>fonction</b>( ... ) {
    
      Composition<A> temp(new A(...)) ;
    
      temp->....
      ....
    		
      }
    \endcode
    
    Fin de l'exemple
    
      En effet, si surviens une exception pendant la "manipulation" de temp ou 
      d'un autre jet, l'jet d�sign� par temp sera detruit.
    
    */
    template <class OBJET> class Composition {
    public:
    
    
      /// Le destructeur d�truit l'objet point�.

      /// C'est l� tout l'int�r�t de cette classe.
      ~Composition()
      {
        delete pt ;
      }
    
      /// Acc�s � un membre de l'onjet point�.
      
      /// V�rifie que le pointeur est non NULL. 
      OBJET* operator ->() const
      {
        if (pt == NULL) 
    
          throw ExceptionBase("Composition::->") ;
    
        return pt ;
      }
    

      // *************************
      /// @name Op�rateurs de conversion
      // *************************      
      // @{  
      

      /// Acc�s � l'objet point�.
      const OBJET& operator *() const
      {
        return *pt ;
      }
    
      /// Acc�s � l'objet point�.
      OBJET& operator *() 
      {
        return *pt ;
      }
    
      // @}
          
      // *************************
      /// @name Adoption/Abandon
      // *************************      
      // @{  
      
      /// Constructeur, l'objet point� est adopt�. Par d�faut, 
      /// le pointeur pointe sur NULL.
      Composition(OBJET* _pt = NULL)
        : pt(_pt)
      {}
    
      /// Affectation entre un pointeur et un pointeur d'agr�gation, 
      /// l'objet est adopt�.
      Composition<OBJET>& operator =(OBJET* _pt) {
    
        if (pt != _pt) {
    
          delete pt ;
          pt = _pt ;
        }
    
        return *this ;
    	
      }
    
      /// Affectation entre pointeurs d'agr�gation, cette 
      /// affectation transf�re la responsabilit� de l'objet.
      Composition<OBJET>& operator =(Composition<OBJET>& _x) {
    
        if (*this != _x) {
    
          delete pt ;
          pt = _x.pt ;
          _x.pt = NULL ;
        }
    
        return *this ;
      }
      
      /// Lib�re l'objet point�.
      
      /// L'objet composant ne l'est plus 
      /// Cette fonction permet de transferer la 
      /// responsabilit� de l'objet point� � une autre composition.
      OBJET* Liberer() {
    
        OBJET* rc = pt ;
        pt = NULL ;
        return rc ;
      }
    
      // @}

    
      // *************************
      /// @name Op�rateurs de comparaison
      // *************************      
      // @{  
      
      /// Comparaison avec une Association.
      Booleen operator == (const Association<OBJET>& _p) ;
    
      /// Comparaison avec une Association.
      Booleen operator !=(const  Association<OBJET>& _p) ;
    	
      // @}
          
    private:
    
      /// Pointeur sur l'objet agr�g�.
      OBJET* pt ;
    
    

      // *************************
      /// @name M�thodes Interdites
      // *************************      
      // @{  
      
      /// M�thode Interdite
      
      /// Cette m�thode n'est pas impl�ment�e, pour qu'elle ne soit 
      /// pas utilis�e.
      void operator [](size_t) ;
    
      /// M�thode Interdite

      /// Cette m�thode n'est pas impl�ment�e, pour qu'elle ne soit pas 
      /// utilis�e.
      Composition(const Composition< OBJET >&) ;
    
      // @}
      
      friend class Association<OBJET> ;
    };
    
    #include <base/implantation/composition.cxx>
  }
}

#endif
