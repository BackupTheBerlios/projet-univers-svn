/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/implementation/operation.h>
#include <kernel/implementation/concurrent_block.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Implementation
    {
      ConcurrentBlock::ConcurrentBlock(Model* model)
      : m_model(model)
      {}
      
      void ConcurrentBlock::addOperation(Operation* operation)
      {
        m_operations.push_back(operation) ;
      }
      
      void ConcurrentBlock::execute()
      {
        for(std::list<Operation*>::const_iterator operation = m_operations.begin() ;
            operation != m_operations.end() ;
            ++operation)
        {
          (*operation)->execute() ;
        }
      }
      
      
      Trait* ConcurrentBlock::getTrait(Object* object,const TypeIdentifier& trait) const
      {
        for(std::list<Operation*>::const_reverse_iterator operation = m_operations.rbegin() ;
            operation != m_operations.rend() ;
            ++operation)
        {
          Operation* local = *operation ;
          
          if (local->m_type == Operation::DestroyTrait && 
              object == local->m_object && 
              trait == local->m_trait_identifier)
          {
            return NULL ;
          }
          else if (local->m_type == Operation::AddTrait && 
                   object == local->m_object && 
                   trait == local->m_trait_identifier)
          {
            return local->m_trait ;
          }
        }
        
        return object->getTrait(trait) ;
      }
      
      std::set<Object*> ConcurrentBlock::getChildren(Object* object) const
      {
        std::set<Object*> result(object->getChildren()) ;
        
        for(std::list<Operation*>::const_reverse_iterator operation = m_operations.rbegin() ;
            operation != m_operations.rend() ;
            ++operation)
        {
          Operation* local = *operation ;
          
          if (local->m_type == Operation::DestroyObject && 
              object == local->m_object->getParent())
          {
            result.erase(local->m_object) ;
          }
        }
        
        return result ;
      }
      
      
    }
  }
}
