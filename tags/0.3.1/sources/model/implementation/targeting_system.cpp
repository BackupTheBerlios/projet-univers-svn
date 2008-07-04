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

#include <model/model.h>
#include <model/selected.h>
#include <model/computer.h>
#include <model/transponder.h>
#include <model/positionned.h>
#include <model/computer_data.h>
#include <model/targeting_system.h>

namespace ProjetUnivers {
  namespace Model {

    RegisterCommand("Select Next Target",TargetingSystem,selectNextTarget) ;
    RegisterCommand("Select Previous Target",TargetingSystem,selectPreviousTarget) ;
    RegisterCommand("Select Nearest Target",TargetingSystem,selectNearestTarget) ;
    RegisterCommand("Select Nearest Enemy",TargetingSystem,selectNearestEnemy) ;

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
      InternalMessage("Model","TargetingSystem::selectNextTarget entering") ;
      
      if (!m_computer)
        return ;

      InternalMessage("Model","TargetingSystem::selectNextTarget has computer") ;

      Computer* computer = m_computer->getTrait<Computer>() ;
      if (!computer)
        return ;
      
      InternalMessage("Model","TargetingSystem::selectNextTarget computer is correct") ;
      /*!
        1 if no target take the first one 
        2 if a target take the next one
      */
      const std::set<Kernel::Object*>& roots = computer->getMemoryModel()->getRoots() ;

      if (roots.size() > 0)
      {
        InternalMessage("Model","TargetingSystem::selectNextTarget selected") ;
        if (!m_target)
        {
          selectTarget(*(roots.begin())) ;
        }
        else
        {
          selectTarget(Kernel::Algorithm::findAfter<Kernel::Object*>(roots,m_target)) ;
        }
      }
      else
      {
        InternalMessage("Model","TargetingSystem::selectNextTarget nothing to select") ;
        unSelectTarget(m_target) ;
      }
      notify() ;

      InternalMessage("Model","TargetingSystem::selectNextTarget leaving") ;
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
          selectTarget(*(roots.rbegin())) ;
        }
        else
        {
          selectTarget(Kernel::Algorithm::findBefore<Kernel::Object*>(roots,m_target)) ;
        }
      }
      else
      {
        unSelectTarget(m_target) ;
      }
      
      notify() ;
      InternalMessage("Model","TargetingSystem::selectPreviousTarget leaving") ;
    }
    
    void TargetingSystem::selectNearestTarget()
    {
      InternalMessage("Model","TargetingSystem::selectNearestTarget entering") ;
      
      if (!m_computer)
        return ;

      InternalMessage("Model","TargetingSystem::selectNearestTarget has computer") ;

      Computer* computer = m_computer->getTrait<Computer>() ;
      if (!computer)
        return ;
      
      InternalMessage("Model","TargetingSystem::selectNearestTarget computer is correct") ;
      const std::set<Kernel::Object*>& roots = computer->getMemoryModel()->getRoots() ;

      Distance shortest_distance ;
      Kernel::Object* target = NULL ; 
        
        
      for(std::set<Kernel::Object*>::const_iterator object = roots.begin() ;
          object != roots.end() ;
          ++object)
      {
        Distance distance = (*object)->getTrait<Positionned>()
                      ->getPosition().calculateDistance(Position()) ;
        
        if (!target || distance <= shortest_distance)
        {
          shortest_distance = distance ;
          target = *object ;
        }
      }
      
      if (target)
      {  
        selectTarget(target) ;
        notify() ;
      }
      InternalMessage("Model","TargetingSystem::selectNearestTarget leaving") ;
    }
    
    void TargetingSystem::selectNearestEnemy()
    {
      InternalMessage("Model","TargetingSystem::selectNearestEnemy entering") ;
      
      if (!m_computer)
        return ;

      InternalMessage("Model","TargetingSystem::selectNearestEnemy has computer") ;

      Computer* computer = m_computer->getTrait<Computer>() ;
      if (!computer)
        return ;
      
      InternalMessage("Model","TargetingSystem::selectNearestEnemy computer is correct") ;
      const std::set<Kernel::Object*>& roots = computer->getMemoryModel()->getRoots() ;

      Distance shortest_distance ;
      Kernel::Object* target = NULL ; 
        
      Transponder* detecting_identification = getObject()->getParent<Transponder>() ;
      if (!detecting_identification)
        return ;
      
      for(std::set<Kernel::Object*>::const_iterator object = roots.begin() ;
          object != roots.end() ;
          ++object)
      {
        Distance distance = (*object)->getTrait<Positionned>()
                      ->getPosition().calculateDistance(Position()) ;
        
        Transponder* detected_identification = (*object)->getTrait<Transponder>() ;
        
        InternalMessage("Model","TargetingSystem::selectNearestEnemy testing") ;
        if (detected_identification && 
            Transponder::areFoe(detecting_identification->getObject(),*object) && 
            (!target || distance <= shortest_distance))
        {
          shortest_distance = distance ;
          target = *object ;
        }
      }
      
      if (target)
      {  
        selectTarget(target) ;
        notify() ;
      }
      InternalMessage("Model","TargetingSystem::selectNearestEnemy leaving") ;
    }
    
    Kernel::Object* TargetingSystem::getTarget() const
    {
      return m_target ;
    }
    
    void TargetingSystem::selectTarget(Kernel::Object* object)
    {
      InternalMessage("Model","TargetingSystem::selectTarget entering") ;
      
      unSelectTarget(m_target) ;
      
      m_target = object ;
      Selected* selected = object->getTrait<Selected>() ;
      
      if (! selected)
      {
        InternalMessage("Model","TargetingSystem::selectTarget#0") ;
        object->addTrait(new Selected()) ;
        InternalMessage("Model","TargetingSystem::selectTarget#1") ;
        selected = object->getTrait<Selected>() ;
        InternalMessage("Model","TargetingSystem::selectTarget#2") ;
      }
      
      InternalMessage("Model","TargetingSystem::selectTarget#3") ;
      selected->select(getObject()) ;
      InternalMessage("Model","TargetingSystem::selectTarget leaving") ;
    }
    
    void TargetingSystem::unSelectTarget(Kernel::Object* object)
    {
      if (! object)
      {
        m_target = NULL ;
        return ;
      }
      
      Selected* selected = object->getTrait<Selected>() ;
      
      if (selected)
      {
        selected->unSelect(getObject()) ;
        if (! selected->isSelected())
        {
          selected->getObject()->destroyTrait(selected) ;
        }
      }
      m_target = NULL ;
    }

    Kernel::Model* TargetingSystem::getComputerModel() const
    {
      if(!m_computer)
        return NULL ;
      
      return m_computer->getTrait<Computer>()->getMemoryModel() ;
    
    }

    Kernel::Object* TargetingSystem::getComputer() const
    {
      return m_computer ;
    }
  }
}
