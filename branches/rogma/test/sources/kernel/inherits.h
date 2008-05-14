/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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

    /// Statically checks that @c Child inherits from @c Parent
    /*!
      Stroustrup's code.
      
      Usage :
        Put 
        @code 
          Inherits<A,B>() ; 
        @endcode
        where we whant to ensure that A inherits from B.
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
