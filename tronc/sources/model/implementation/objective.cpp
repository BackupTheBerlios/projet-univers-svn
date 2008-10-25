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
#include <model/objective.h>

namespace ProjetUnivers {
  namespace Model {

    Objective::Objective(const Objective& objective) 
    : m_objective_kind(objective.m_objective_kind),
      m_parameters(objective.m_parameters)
    {}
      
    Objective& Objective::operator=(const Objective& objective)
    {
      if (&objective != this)
      {
        m_objective_kind = objective.m_objective_kind ;
        m_parameters = objective.m_parameters ;
      }
      return *this ;
    }
    
    Objective Objective::wait()
    {
      return Objective(Wait) ;
    }
    
    Objective Objective::patrol(Kernel::Object* zone)
    {
      Objective result(Patrol) ;
      result.m_parameters.insert(zone) ;
      return result ;
    }
    
    Objective Objective::attackAllEnemies()
    {
      return Objective(AttackAllEnemies) ;
    }
    
    Objective Objective::goTo(Kernel::Object* position)
    {
      Objective result(GoTo) ;
      result.m_parameters.insert(position) ;
      return result ;
    }
    
    bool Objective::operator==(const Objective& objective) const
    {
      return m_objective_kind == objective.m_objective_kind && 
             m_parameters == objective.m_parameters ;
    }
    
    Objective::Objective(const Kind& kind) 
    : m_objective_kind(kind)
    {}
  
    Objective::Kind Objective::getKind() const 
    {
      return m_objective_kind ;
    }
    
    Kernel::ObjectReference Objective::getPatrolZone() const 
    {
      if (m_parameters.size()>0)
      {
        return *(m_parameters.begin()) ;
      }
      else
      {
        return NULL ;
      }
    }
  
    Kernel::ObjectReference Objective::getDestination() const
    {
      return getPatrolZone() ;
    }
    
    bool Objective::operator<(const Objective& objective) const
    {
      return m_objective_kind < objective.m_objective_kind ||  
             (   m_objective_kind == objective.m_objective_kind && 
                 m_parameters < objective.m_parameters) ;
    }
    
  }
}
