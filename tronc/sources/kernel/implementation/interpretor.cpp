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
#include <kernel/log.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/implementation/operation.h>
#include <kernel/implementation/transaction.h>
#include <kernel/implementation/interpretor.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Implementation
    {
      Interpretor::Interpretor(Model* model)
      : m_model(model)
      {}
      
      void Interpretor::startTransaction() 
      {
        m_transactions.push_back(new Transaction(m_model)) ;
      }
      
      void Interpretor::endTransaction() 
      {
        if (! m_transactions.empty())
        {
          m_transactions.back()->execute() ;
          m_transactions.pop_back() ;
        }
        else
        {
          ErrorMessage("Closing an openned transaction") ;
          throw std::exception() ;
        }
      }
      void Interpretor::startConcurrentBlock() 
      {
        if (! m_transactions.empty())
        {
          m_transactions.back()->startConcurrentBlock() ;
        }
        else
        {
          ErrorMessage("No transaction") ;
          throw std::exception() ;
        }
      }
      void Interpretor::endConcurrentBlock() 
      {
        if (! m_transactions.empty())
        {
          m_transactions.back()->endConcurrentBlock() ;
        }
        else
        {
          ErrorMessage("No transaction") ;
          throw std::exception() ;
        }
      }
      
      void Interpretor::destroyObject(Object* object) 
      {
        if (! m_transactions.empty())
        {
          m_transactions.back()->addOperation(Operation::destroyObject(object)) ;
        }
        else
        {
          ErrorMessage("No transaction") ;
          throw std::exception() ;
        }
        
      }
      void Interpretor::addTrait(Object* object,Trait* trait) 
      {
        if (! m_transactions.empty())
        {
          m_transactions.back()->addOperation(Operation::addTrait(object,trait)) ;
        }
        else
        {
          ErrorMessage("No transaction") ;
          throw std::exception() ;
        }
      }
      void Interpretor::destroyTrait(Object*,Trait* trait) 
      {
        if (! m_transactions.empty())
        {
          m_transactions.back()->addOperation(Operation::destroyTrait(trait)) ;
        }
        else
        {
          ErrorMessage("No transaction") ;
          throw std::exception() ;
        }
      }
      
      Object* Interpretor::getParent(Object*) const
      {
        return NULL ;
      }
      
      Trait* Interpretor::getTrait(Object* object,const TypeIdentifier& trait) const
      {
        if (! m_transactions.empty())
        {
          return m_transactions.back()->getTrait(object,trait) ;
        }
        else
        {
          return object->getTrait(trait) ;
        }
      }
      
      std::set<Object*> Interpretor::getChildren(Object* object) const
      {
        if (! m_transactions.empty())
        {
          return m_transactions.back()->getChildren(object) ;
        }
        else
        {
          return object->getChildren() ;
        }
      }
      
    }
  }
}
