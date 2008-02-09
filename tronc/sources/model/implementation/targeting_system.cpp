/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <kernel/object.h>
#include <kernel/log.h>
#include <kernel/algorithm.h>

#include <model/computer.h>
#include <model/computer_data.h>
#include <model/targeting_system.h>

namespace ProjetUnivers {
  namespace Model {

    RegisterCommand("Select Next Target",TargetingSystem,selectNextTarget) ;
    RegisterCommand("Select Previous Target",TargetingSystem,selectPreviousTarget) ;

    TargetingSystem::TargetingSystem()
    {}

    void TargetingSystem::connect(
        Kernel::Object* targeting_system,
        Kernel::Object* computer)
    {
      if (targeting_system)
      {
        TargetingSystem* system = targeting_system->getTrait<TargetingSystem>() ;
        if (system)
        {
          system->m_computer = computer ;
        }
      }
    }

    /// Get the next @s element after @c i
    /*!
      @param s an non-empty set
      @param i a "possible" element of s
      
      @return
        @c r minimum element of @c s such that @c r > @c i if exists
        first @c s element otherwise  
    */ 
    Kernel::Object* find_after(const std::set<Kernel::Object*>& s,Kernel::Object* i)
    {
      std::set<Kernel::Object*>::const_iterator up = s.upper_bound(i) ;
      
      if (up == s.end())
      {
        return *(s.begin()) ;
      }
      else
      {
        return *up ;
      }
    }
    
    void TargetingSystem::selectNextTarget()
    {
      InternalMessage("Model","TargetingSystem::selectNextTarget entering") ;
      
      if (!m_computer)
        return ;

      /*!
        1 if no target take the first one 
        2 if a target take the next one
      */
      const std::set<Kernel::Object*>& roots =
        m_computer->getTrait<Computer>()->getMemoryModel()->getRoots() ;
      if (roots.size() > 0)
      {
        InternalMessage("Model","TargetingSystem::selectNextTarget selected") ;
        if (!m_target)
        {
          m_target = *(roots.begin()) ;
        }
        else
        {
          m_target = Kernel::Algorithm::findAfter<Kernel::Object*>(roots,m_target) ;
        }
      }
      else
      {
        m_target = NULL ;
      }

      InternalMessage("Model","TargetingSystem::selectNextTarget leaving") ;
    }

    /// Get the previous @s element after @c i
    /*!
      @param s an non-empty set
      @param i a "possible" element of s
      
      @return
        @c r maximum element of @c s such that @c r < @c i if exists
        last @c s element otherwise  
    */ 
    Kernel::Object* find_before(const std::set<Kernel::Object*>& s,
                                Kernel::Object* object)
    {
      std::set<Kernel::Object*>::const_iterator up = s.lower_bound(object) ;
      
      if (up == s.end())
      {
        return *(s.rbegin()) ;
      }
      else
      {
        if (object <= *up)
        {
          if (up == s.begin())
            return *(s.rbegin()) ;
          else
          {
            --up ;
            return *up ;
          }
        }
        return *up ;
      }
    }

    void TargetingSystem::selectPreviousTarget()
    {
      InternalMessage("Model","TargetingSystem::selectPreviousTarget entering") ;
      
      if (!m_computer)
        return ;

      /*!
        1 if no target take the first one 
        2 if a target take the previous one
      */
      const std::set<Kernel::Object*>& roots =
        m_computer->getTrait<Computer>()->getMemoryModel()->getRoots() ;
      if (roots.size() > 0)
      {
        InternalMessage("Model","TargetingSystem::selectPreviousTarget selected") ;
        if (!m_target)
        {
          m_target = *(roots.rbegin()) ;
        }
        else
        {
          m_target = Kernel::Algorithm::findBefore<Kernel::Object*>(roots,m_target) ;
        }
      }
      else
      {
        m_target = NULL ;
      }

      InternalMessage("Model","TargetingSystem::selectPreviousTarget leaving") ;
    }
    
    void TargetingSystem::selectNearestTarget()
    {
      /// @todo
    }
    
    Kernel::Object* TargetingSystem::getTarget() const
    {
      return m_target ;
    }
      
  }
}
