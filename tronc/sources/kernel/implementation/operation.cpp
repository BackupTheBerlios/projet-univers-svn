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

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Implementation
    {

      Operation::Operation(const Operation& operation)
      : m_type(operation.m_type),
        m_object(operation.m_object),
        m_trait_identifier(operation.m_trait_identifier),
        m_trait(operation.m_trait),
        m_model(operation.m_model)
      {}
      
      Operation::Operation()
      : m_type(None),
        m_object(),
        m_trait_identifier(),
        m_trait(NULL),
        m_model(NULL)
      {}
      
      Operation Operation::addTrait(Trait* trait)
      {
        Operation result ;
        result.m_type = AddTrait ;
        result.m_object = trait->getObject() ;
        result.m_model = result.m_object?trait->getObject()->getModel():NULL ;
        result.m_trait = trait ;
        result.m_trait_identifier = getObjectTypeIdentifier(trait) ;
        
        return result ;
      }
      
      Operation Operation::destroyTrait(Trait* trait)
      {
        Operation result ;
        result.m_type = DestroyTrait ;
        result.m_object = trait->getObject() ;
        result.m_model = result.m_object?trait->getObject()->getModel():NULL ;
        result.m_trait_identifier = getObjectTypeIdentifier(trait) ;
        result.m_trait = trait ;
        
        return result ;
      }
      
      Operation Operation::destroyObject(Object* object) 
      {
        Operation result ;
        result.m_type = DestroyObject ;
        result.m_object = object ;
        result.m_model = object->getModel() ;
        
        return result ;
      }
      
      
      void Operation::execute() 
      {
        switch(m_type)
        {
        case DestroyObject:
          if (m_model && m_object)
            m_model->destroyObject(m_object) ;
          break ;
        case DestroyTrait:
          if (m_model && m_object && m_object->getTrait(m_trait_identifier))
          {
            m_model->destroyTrait(m_object,m_trait) ;
          }
          break ;
        case AddTrait:
          if (m_model && m_object && !m_object->getTrait(m_trait_identifier))
          {
            m_model->addTrait(m_object,m_trait) ;
          }
          
          break ;
        case None:
          break ;
        }
      }
      

    }
  }
}
