/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#ifndef PU_KERNEL_INHERITS_H_
#define PU_KERNEL_INHERITS_H_


namespace ProjetUnivers {
  namespace Kernel {

    /// Vérifie statiquement si Enfant dérive de Parent
    /*!
      Code proposé par Stroustrup pour vérifier statiquement si un type dérive 
      d'un autre.
      
      Utilisation
      
        Mettre :
        @code 
          Inherits<A,B>() ; 
        @endcode
        aux endroits où on désire vérifier que A dérive de B.
        
        @see
          View

    */
    template<class Child, class Parent> struct Inherits 
    {
      static void constraint(Child* _child) 
      { 
        Parent* parent = _child ;
        parent = NULL ; 
      }
      
      Inherits() 
      { 
        void(*p)(Child*) = constraint ;
        p = NULL ; 
      }
      
     };
  }
}

#endif
