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
#include <model/selection.h>
#include <model/computer.h>
#include <model/transponder.h>
#include <model/positionned.h>
#include <model/computer_data.h>
#include <model/targeting_system.h>
#include <model/whole.h>
#include <model/data_connection.h>

namespace ProjetUnivers 
{
  namespace Model 
  {

    RegisterTrait(TargetingSystem) ;
    
    std::string TargetingSystem::SelectNextTarget = "Select Next Target" ;
    std::string TargetingSystem::SelectPreviousTarget = "Select Previous Target" ;
    std::string TargetingSystem::SelectNearestTarget = "Select Nearest Target" ;
    std::string TargetingSystem::SelectNearestEnemy = "Select Nearest Enemy" ;

    RegisterCommand(TargetingSystem::SelectNextTarget,TargetingSystem,selectNextTarget) ;
    RegisterCommand(TargetingSystem::SelectPreviousTarget,TargetingSystem,selectPreviousTarget) ;
    RegisterCommand(TargetingSystem::SelectNearestTarget,TargetingSystem,selectNearestTarget) ;
    RegisterCommand(TargetingSystem::SelectNearestEnemy,TargetingSystem,selectNearestEnemy) ;

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
          Kernel::Link<DataConnection>(computer,targeting_system) ;
        }
      }
    }
    
    Kernel::Trait* TargetingSystem::read(Kernel::Reader* reader)
    {
      TargetingSystem* result = new TargetingSystem() ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode())
        {
          Trait::read(reader) ;
        }
      }
      
      reader->processNode() ;
      
      return result ;
    }
    
    void TargetingSystem::selectNextTarget()
    {
      InternalMessage("Model","TargetingSystem::selectNextTarget entering") ;
      
      if (!getComputer())
        return ;

      InternalMessage("Model","TargetingSystem::selectNextTarget has computer") ;

      Computer* computer = getComputer()->getTrait<Computer>() ;
      if (!computer)
        return ;
      
      InternalMessage("Model","TargetingSystem::selectNextTarget computer is correct") ;
      /*!
        1 if no target take the first one 
        2 if a target take the next one
      */
      const std::set<Kernel::Object*>& roots = computer->getDetectedObjects() ;

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
      
      if (!getComputer())
        return ;

      Computer* computer = getComputer()->getTrait<Computer>() ;
      if (!computer)
        return ;

      /*!
        1 if no target take the first one 
        2 if a target take the previous one
      */
      const std::set<Kernel::Object*>& roots = computer->getDetectedObjects() ;
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
      
      if (!getComputer())
        return ;

      InternalMessage("Model","TargetingSystem::selectNearestTarget has computer") ;

      Computer* computer = getComputer()->getTrait<Computer>() ;
      if (!computer)
        return ;
      
      InternalMessage("Model","TargetingSystem::selectNearestTarget computer is correct") ;
      const std::set<Kernel::Object*>& roots = computer->getDetectedObjects() ;

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
      
      if (!getComputer())
        return ;

      InternalMessage("Model","TargetingSystem::selectNearestEnemy has computer") ;

      Computer* computer = getComputer()->getTrait<Computer>() ;
      if (!computer)
        return ;
      
      InternalMessage("Model","TargetingSystem::selectNearestEnemy computer is correct") ;
      const std::set<Kernel::Object*>& roots = computer->getDetectedObjects() ;

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
      
      Selection::select(getObject()->getParent<Whole>()->getObject(),object) ;
      m_target = object ;

      InternalMessage("Model","TargetingSystem::selectTarget leaving") ;
    }
    
    void TargetingSystem::unSelectTarget(Kernel::Object* object)
    {
      if (! object)
      {
        m_target = NULL ;
        return ;
      }
      
      Selection::unSelect(getObject()->getParent<Whole>()->getObject(),object) ;
      m_target = NULL ;
    }

    Kernel::Model* TargetingSystem::getComputerModel() const
    {
      Computer* computer ;
      
      if(!getComputer() || !(computer = getComputer()->getTrait<Computer>()))
      {
        ErrorMessage("TargetingSystem::getComputerModel : no computer") ;
        return NULL ;
      }
      
      return computer->getMemoryModel() ;
    }

    Kernel::Object* TargetingSystem::getComputer() const
    {
      std::set<Kernel::Object*> computers(Kernel::Relation::getLinked<Kernel::Inverse<DataConnection> >(getObject())) ;

      if (computers.size() != 1)
        return NULL ;

      return *(computers.begin()) ;
    }
  }
}
