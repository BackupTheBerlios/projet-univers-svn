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


#ifndef _PU_BASE_COMPOSITION_H_
#define _PU_BASE_COMPOSITION_H_




#include <base/exception_base.h>

namespace ProjetUnivers {

  namespace Base {
  
    template <class OBJET> class Association ;    
    
    ///  Classe générique réalisant la composition d'un élément d'une classe 
    ///  d'objets.
    
    /*!
    UTILISATIONS
    	
      Utilisez cette classe partout ! Mais surtout dans les trois cas suivants:
    
      1. Pour pointer sur le résultat d'une fonction fabriquante. La création 
      se fait avec un new, il n'y a pas de destruction à gérer. Cette 
      utilisation peut se réveler pratique si vous utilisez des exceptions, 
      en effet, lorsqu'une exception est levée, on sort du block et il faut 
      détruire les jets alloués dans le tas. Un simple pointeur est insuffisant 
      pour une bonne gestion des exceptions.
    
    
    \code
      Classe1* fabriquant() {
    
      // résultat :
      Composition<Classe1>	res = new Classe1(...)
    
      // traitements 
      // N.B. Si une exception est levée ici, l'jet sera détruit.
      .....
    
      // on se sépare de l'jet pointé :
      return res.release() ;
      }
    \endcode

    
      2. Pour pointer sur les attributs agrégés à une classe. Cela évite 
      d'écrire un destructeur, car celui généré par defaut par les compilateurs 
      appèle le destructeur de tous les attributs.
    
    Exemple
    
    \code
      class A {
    
      ....
      };
    
      class B {
    
      Composition<A>	attribut_agrégé_classe_A ;
    
      };
    \endcode
    END
    
      3. Pour gérer une variable locale.
    
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
      d'un autre jet, l'jet désigné par temp sera detruit.
    
    */
    template <class OBJET> class Composition {
    public:
    
    
      /// Le destructeur détruit l'objet pointé.

      /// C'est là tout l'intérêt de cette classe.
      ~Composition()
      {
        delete pt ;
      }
    
      /// Accès à un membre de l'onjet pointé.
      
      /// Vérifie que le pointeur est non NULL. 
      OBJET* operator ->() const
      {
        if (pt == NULL) 
    
          throw ExceptionBase("Composition::->") ;
    
        return pt ;
      }
    

      // *************************
      /// @name Opérateurs de conversion
      // *************************      
      // @{  
      

      /// Accès à l'objet pointé.
      OBJET& operator *() const
      {
        return *pt ;
      }
    
      /// Accès à l'objet pointé.
      //OBJET& operator *()
      //{
      //  return *pt ;
      //}
    
    
      // @}
      // *************************
      /// @name Adoption/Abandon
      // *************************      
      // @{  
      
      
      /// Constructeur, l'objet pointé est adopté. Par défaut, 
      /// le pointeur pointe sur NULL.
      Composition(OBJET* _pt = NULL)
        : pt(_pt)
      {}
    
      /// Affectation entre un pointeur et un pointeur d'agrégation, 
      /// l'objet est adopté.
      Composition<OBJET>& operator =(OBJET* _pt) {
    
        if (pt != _pt) {
    
          delete pt ;
          pt = _pt ;
        }
    
        return *this ;
    	
      }
    
      /// Affectation entre pointeurs d'agrégation, cette 
      /// affectation transfére la responsabilité de l'objet.
      Composition<OBJET>& operator =(Composition<OBJET>& _x) {
    
        if (*this != _x) {
    
          delete pt ;
          pt = _x.pt ;
          _x.pt = NULL ;
        }
    
        return *this ;
      }
      
      /// Libère l'objet pointé.
      
      /// L'objet composant ne l'est plus 
      /// Cette fonction permet de transferer la 
      /// responsabilité de l'objet pointé à une autre composition.
      OBJET* Liberer() {
    
        OBJET* rc = pt ;
        pt = NULL ;
        return rc ;
      }
    
    
      // @}
      // *************************
      /// @name Opérateurs de comparaison
      // *************************      
      // @{  
      
      
      /// Comparaison avec une Association.
      Booleen operator == (const Association<OBJET>& _p) const ;
    
      /// Comparaison avec une Association.
      Booleen operator !=(const  Association<OBJET>& _p) const ;
    	
      /// Comparaison avec un pointeur.
      Booleen operator == (const OBJET* _p) const ;
    
      /// Comparaison avec un pointeur.
      Booleen operator !=(const  OBJET* _p) const ;

      
      // @}    
    private:
    
      /// Pointeur sur l'objet agrégé.
      OBJET* pt ;
    
    

      // *************************
      /// @name Méthodes Interdites
      // *************************      
      // @{  
      
      
      /// Méthode Interdite
      
      /// Cette méthode n'est pas implémentée, pour qu'elle ne soit 
      /// pas utilisée.
      void operator [](size_t) ;
    
      /// Méthode Interdite

      /// Cette méthode n'est pas implémentée, pour qu'elle ne soit pas 
      /// utilisée.
      Composition(const Composition< OBJET >&) ;
    
    
      // @}  
      template <class Y> friend class Association ;
      
    };
    
  }
}

#include <base/implantation/composition.cxx>

#endif
