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
#include <OgreVector3.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    
    /// Utility algorithms
    namespace Algorithm 
    {

      /// Get the next @c s element after @c object
      /*!
        @param s an non-empty set
        @param object a "possible" element of s

        @return
          @c r minimum element of @c s such that @c r > @c object if exists
          first @c s element otherwise  
      */ 
      template <typename T> T findAfter(const std::set<T>& s,const T& object) ;
      
      /// Get the previous @c s element after @c object
      /*!
        @param s an non-empty set
        @param object a "possible" element of s
        
        T must be a type with <= operator
        
        @return
          @c r maximum element of @c s such that @c r < @c object if exists
          last @c s element otherwise  
      */ 
      template <typename T> T findBefore(const std::set<T>& s,const T& object) ;

      
      /// Calculate interception time between two moving elements.
      /*!
        Hypothesis : 
        - all units must be consistent
        - time is calculated considering target keeps actual speed and interceptor 
          goes at interceptor_speed
        
        @param [in] target_positon target position
        @param [in] target_speed target actual speed
        @param [in] interceptor_speed interceptor speed
        
        @return boolean says if target is reachable, float gives time
      */
      std::pair<bool,float> calculateInterceptionTime(
          const Ogre::Vector3& target_positon,
          const Ogre::Vector3& target_speed,
          const float& interceptor_speed) ;    
      
    }
  }
}

#include <kernel/implementation/algorithm.cxx>

#endif /*PU_KERNEL_ALGORITHM_H_*/
