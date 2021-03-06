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

#ifndef _PU_BASE_DERIVE_DE_H_
#define _PU_BASE_DERIVE_DE_H_


namespace ProjetUnivers {

  namespace Base {


    /// V�rifie statiquement si Enfant d�rive de Parent
    /*!
      Code propos� par Stroustrup pour v�rifier statiquement si un type d�rive 
      d'un autre.
      
      Utilisation
      
        Mettre :
        @code 
          DeriveDe<A,B>() ; 
        @endcode
        aux endroits o� on d�sire v�rifier que A d�rive de B.
        
        @see
          Vue

    */
    template<class Enfant, class Parent> struct DeriveDe 
    {
      static void Contrainte(Enfant* _enfant) 
      { 
        Parent* parent = _enfant ; 
      }
      
      DeriveDe() 
      { 
        void(*p)(Enfant*) = Contrainte ; 
      }
      
     };
  }
}

#endif
