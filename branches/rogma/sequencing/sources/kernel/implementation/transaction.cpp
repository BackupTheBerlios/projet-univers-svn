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
#include <kernel/implementation/transaction.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Implementation
    {
      Transaction::Transaction(Model* model)
      : m_model(model)
      {}

      void Transaction::startConcurrentBlock()
      {
        m_blocks.push_back(new ConcurrentBlock(m_model)) ;
      }
      
      void Transaction::addOperation(Operation* operation)
      {
        if (!m_blocks.empty())
        {
          m_blocks.back()->addOperation(operation) ;
        }
        else
        {
          ErrorMessage("No concurrent block") ;
          throw std::exception() ;
        }
      }
      
      void Transaction::endConcurrentBlock()
      {
        if (m_blocks.empty())
        {
          ErrorMessage("Closing an openned concurrent block") ;
          throw std::exception() ;
        }
      }
      
      void Transaction::execute()
      {
        for(std::list<ConcurrentBlock*>::const_iterator block = m_blocks.begin() ;
            block != m_blocks.end() ;
            ++block)
        {
          (*block)->execute() ;
        }
      }
      
      Transaction::~Transaction()
      {
        
      }
      
      Trait* Transaction::getTrait(Object* object,const TypeIdentifier& trait) const
      {
        if (! m_blocks.empty())
        {
          return m_blocks.back()->getTrait(object,trait) ;
        }
        else
        {
          return object->getTrait(trait) ;
        }
      }

      std::set<Object*> Transaction::getChildren(Object* object) const
      {
        if (! m_blocks.empty())
        {
          return m_blocks.back()->getChildren(object) ;
        }
        else
        {
          return object->getChildren() ;
        }
      }
      
    }
  }
}
