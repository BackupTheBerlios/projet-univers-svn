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

#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include "exception_base.h"

namespace ProjetUnivers {

  namespace Base {

    template <class OBJET> class Composition ;
    template <class OBJET> class NoeudAssociation ;

    /*
    CLASS
      Association
    
      Classe g�n�rique d�signant une association d'un �l�ment d'une classe 
      d'objets.
    
    UTILISATION
      Cette classe sert � d�signer des objets en lecture et comme retours 
      de fonctions d'acc�s. Ainsi, lorsqu'on a besoin de d�signer 
      un objet existant on utilise cette classe.
    */
    template <class OBJET> class Association {
    public:
    
      // ********************
      // GROUP: Constructeurs
      // ********************
    
    
      /////////////////
      // Constructeur par d�faut.
      Association()
        : pt(NULL)
      {}
    
    
      ///////////////////
      // Constructeur, prends une r�f�rence � l'objet.
      Association(OBJET &_x)
        : pt(&_x)
      {}
    
      ///////////////////
      // Constructeur, prends une r�f�rence � l'objet.
      Association(const OBJET &_x)
        : pt((OBJET*)&_x)
      {}
    
      /////////////////////
      // Constructeur de copie.
      Association(const Association<OBJET>& _x)
        :pt(_x.pt)
      {}
    	
      /////////////////////
      // Conversion de Composition en Association
      Association(const Composition<OBJET>& _x) ;
    
    
      // *************************************
      // GROUP: Op�rateurs de d�r�f�renciation
      // *************************************
    
    
      /////////////////////////
      // V�rifie que le pointeur est non NULL avant d'appeler.
      OBJET* operator ->() const ;
    
    
    
      // *******************
      // GROUP: Affectations
      // *******************
    
    
    
      ////////////////////////////
      // Affectation d'une autre association.
      Association<OBJET>& operator =(Association<OBJET> _r)
      {
    
        pt = _r.pt ;
        return *this ;
      }
    
      ///////////////////////////
      // Affectation avec un pointeur d'agregation.
      Association<OBJET>& operator =(const Composition<OBJET>& _x) ;
    	
    
      // *******************
      // GROUP: Comparaisons
      // *******************
    
    
      //////////////////
      // Egalit� avec une autre association.
      Booleen operator == (const Association<OBJET>& _x) const
      {
        return pt == _x.pt ;
      }
    
      /////////////////////
      // Comparaison avec une agr�gation.
      Booleen operator == (const Composition<OBJET>& _x) const ;
    
      /////////////////////
      // Comparaison avec un pointeur.
      Booleen operator ==(const OBJET* _x) const {
    		
        return pt == _x ;
      }
    	
      /////////////////
      // Diff�rence avec une autre association.
      Booleen operator !=(const  Association<OBJET>& _x) const 
      {
        return pt != _x.pt ;
      }
    
      /////////////////////
      // Diff�rence avec un pointeur.
      Booleen operator !=(const OBJET* _x) const {
    		
        return pt != _x ;
      }
      
      /////////////////////
      // Comparaison avec une agr�gation.
      Booleen operator != (const Composition<OBJET>& _x) const ;
    
    private:
    
    
      /////////////////
      // pointeur sur l'jet en association.
      OBJET*	pt ;
    
      // *******************
      // GROUP: Interdictions
      // *******************
    
    
      /////////////////////////
      // Affectation d'un pointeur. 
      // Cette m�thode est INTERDITE donc on la d�clare en priv�.
      Association<OBJET>& operator =(OBJET* _p) ;
    
    
      friend class NoeudAssociation<OBJET> ;
    };
    
    #include "implantation/association.cxx"

  }
}

#endif

	
