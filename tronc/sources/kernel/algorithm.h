/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#ifndef PU_KERNEL_ALGORITHM_H_
#define PU_KERNEL_ALGORITHM_H_

#include <set>
#include <iterator>

namespace ProjetUnivers {
  namespace Kernel {
    
    /// Utility algorithms
    namespace Algorithm {

      /// Get the next @s element after @c i
      /*!
        @param s an non-empty set
        @param i a "possible" element of s

        @return
          @c r minimum element of @c s such that @c r > @c i if exists
          first @c s element otherwise  
      */ 
      template <typename T> T findAfter(const std::set<T>& s,const T& object) ;
      
      /// Get the previous @s element after @c i
      /*!
        @param s an non-empty set
        @param i a "possible" element of s
        @param T must be a type with <= operator
        
        @return
          @c r maximum element of @c s such that @c r < @c i if exists
          last @c s element otherwise  
      */ 
      template <typename T> T findBefore(const std::set<T>& s,const T& object) ;

    }
  }
}

#include <kernel/implementation/algorithm.cxx>

#endif /*PU_KERNEL_ALGORITHM_H_*/
