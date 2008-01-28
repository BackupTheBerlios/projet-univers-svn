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

#include <model/computer.h>
#include <model/computer_data.h>
#include <model/targeting_system.h>

namespace ProjetUnivers {
  namespace Model {

    RegisterCommand("selectNextTarget",TargetingSystem,selectNextTarget) ;

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
    
    void TargetingSystem::selectNextTarget()
    {
      /// @todo
      InternalMessage("Model","TargetingSystem::selectNextTarget entering") ;

      // temporary code
      if (m_computer->getTrait<Computer>()->getMemoryModel()->getRoots().size() > 0)
      {
        InternalMessage("Model","TargetingSystem::selectNextTarget selected") ;
        m_target = *(m_computer->getTrait<Computer>()->getMemoryModel()->getRoots().begin()) ;
      }

      InternalMessage("Model","TargetingSystem::selectNextTarget leaving") ;
    }

    void TargetingSystem::selectPreviousTarget()
    {
      /// @todo
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
