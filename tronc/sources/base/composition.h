/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef COMPOSITION_H
#define COMPOSITION_H




#include "exception.h"

namespace ProjetUnivers {

  namespace Base {
    template <class T> class Association ;
    
    
    /*
    CLASS
      Composition
    
      Classe générique réalisant la composition d'un élément d'une classe 
      d'objets.
    
    UTILISATIONS
    	
      Utilisez cette classe partout ! Mais surtout dans les trois cas suivants:
    
      1. Pour pointer sur le résultat d'une fonction fabriquante. La création 
      se fait avec un new, il n'y a pas de destruction à gérer. Cette 
      utilisation peut se réveler pratique si vous utilisez des exceptions, 
      en effet, lorsqu'une exception est levée, on sort du block et il faut 
      détruire les jets alloués dans le tas. Un simple pointeur est insuffisant 
      pour une bonne gestion des exceptions.
    
    EXAMPLE
    
      Classe1* fabriquant() {
    
      // résultat :
      Composition<Classe1>	res = new Classe1(...)
    
      // traitements 
      // N.B. Si une exception est levée ici, l'jet sera détruit.
      .....
    
      // on se sépare de l'jet pointé :
      return res.release() ;
      }
    
    END
    
      2. Pour pointer sur les attributs agrégés à une classe. Cela évite 
      d'écrire un destructeur, car celui généré par defaut par les compilateurs 
      appèle le destructeur de tous les attributs.
    
    EXAMPLE
    
      class A {
    
      ....
      };
    
      class B {
    
      Composition<A>	attribut_agrégé_classe_A ;
    
      };
    END
    
      3. Pour gérer une variable locale.
    
    EXAMPLE
    
      <i>type</i> <b>fonction</b>( ... ) {
    
      Composition<A> temp(new A(...)) ;
    
      temp->....
      ....
    		
      }
    
    END
    
      En effet, si surviens une exception pendant la "manipulation" de temp ou 
      d'un autre jet, l'jet désigné par temp sera detruit.
    
    */
    template <class OBJET> class Composition {
    
    public:
    
    
      ////////////////////
      // Le destructeur détruit l'objet pointé, c'est là tout l'intérêt de 
      // cette classe.
      ~Composition()
      {
        delete pt ;
      }
    
      /////////////////
      // Vérifie que le pointeur est non NULL : 
      OBJET* operator ->() const
      {
        if (pt == NULL) 
    
          throw Exception("Composition::->") ;
    
        return pt ;
      }
    
      // *******************************
      // GROUP: Opérateurs de conversion
      // *******************************
      
      ////////////////////
      // Accès à l'objet agrégé.
      const OBJET& operator *() const
      {
        return *pt ;
      }
    
      OBJET& operator *() 
      {
        return *pt ;
      }
    
    
      // ***********************
      // GROUP: Adoption/Abandon
      // ***********************
    
      ///////////////////
      // Constructeur, l'objet pointé est adopté. Par défaut, 
      // le pointeur pointe sur NULL.
      Composition(OBJET* _pt = NULL)
        : pt(_pt)
      {}
    
      ////////////////////
      // Affectation entre un pointeur et un pointeur d'agrégation, 
      // l'objet est adopté.
      Composition<OBJET>& operator =(OBJET* _pt) {
    
        if (*this != Association<OBJET>(_pt)) {
    
          delete pt ;
          pt = _pt ;
        }
    
        return *this ;
    	
      }
    
      /////////////////////
      // Affectation entre pointeurs d'agrégation, cette 
      // affectation transfére la responsabilité de l'objet.
      Composition<OBJET>& operator =(Composition<OBJET>& _x) {
    
        if (*this != _x) {
    
          delete pt ;
          pt = _x.pt ;
          _x.pt = NULL ;
        }
    
        return *this ;
      }
    
      /////////////////
      // Renvoie un pointeur sur l'objet agrégé. Cet objet n'est plus agrégé. 
      // Cette fonction permet à l'agrégation de se libérer de la 
      // responsabilité de l'objet pointé.
      OBJET* release() {
    
        OBJET* rc = pt ;
        pt = NULL ;
        return rc ;
      }
    
      // *****************************************************
      // GROUP: Opérateurs de comparaison avec une association 
      // *****************************************************
    
      /////////////////////
      // Comparaison avec une association.
      Booleen operator == (const Association<OBJET>& _p) ;
    
      /////////////////////
      // Comparaison avec une association.
      Booleen operator !=(const  Association<OBJET>& _p) ;
    	
    
    private:
      ////////////////////
      // Pointeur sur l'objet agrégé.
      OBJET* pt ;
    
    
      // GROUP: Méthodes Interdites
    
      /////////////////
      // Cette méthode n'est pas implémentée, pour qu'elle ne soit pas utilisée.
      void operator [](size_t) ;
    
      /////////////////
      // Cette méthode n'est pas implémentée, pour qu'elle ne soit pas utilisée.
      Composition(const Composition< OBJET >&) ;
    
    };
    
    #ifdef _INC_TEMP_CODE_
    #include "implantation/composition.cxx"
    #endif
  }
}

#endif
