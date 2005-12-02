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

#ifndef _PU_MODELE_OBJET_H_
#define _PU_MODELE_OBJET_H_

#include <base/association.h>
#include <base/modele.h>

#include <modele/position.h>
#include <modele/orientation.h>

namespace ProjetUnivers {

  namespace Modele {


    /// Classe des objets du monde.
    
    /*!
      Chaque objet poss�de une position. 

      @par Containtes
      
      Un Objet peut �tre sa propre origine mais cela ne doit pas arriver 
      indirectement : si o1 est l'origine de p1, si o2 a p1 comme position, o2 
      ne peut �tre l'origine de la position de p1.
      
    */
    class Objet : public Base::Modele 
    {
    public:
    
      /// Position de l'objet.
      Position AccesPosition() const ;

      /// Orientation de l'objet
      Orientation AccessOrientation() const ;

      /// 
      Base::Association<Objet> AccesReferentiel() const ;


      /// Vrai si les deux objets font partie d'un m�me ref�rentiel.
      Base::Booleen MemeReferentiel(const Base::Association<Objet>&) const ;
      
      

      /// @name Constructeur/Destructeur

      /// Classe abstraite donc destructeur virtuel.
      virtual ~Objet() ;
    
      
    
    protected:
    
      /// Classe abstraite donc constructeur prot�g�.
      Objet(const Position&) ;
      Objet() ;

      /// Position de l'objet.
      /*!
        Si cela n'a pas r��lement de sens alors la position est la 
        position nulle par rapport � lui m�me.
      */
      Position position ;

      /// Orientation dans l'espace
      /*!
        C'est un vecteur norm�.
      */
      Orientation orientation ;
      
    };
  }
}
#endif
