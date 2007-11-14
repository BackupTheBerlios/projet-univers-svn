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
#include <kernel/model.h>
#include <kernel/object_reference.h>

namespace ProjetUnivers {
  namespace Kernel {
    
    ObjectReference::ObjectReference(Object* object)
    : m_model(object?object->getModel():NULL),
      m_object_identifier(object?object->getIdentifier():-1)
    {
      if (m_model)
      {
        m_model->_registerReference(this) ;
      }
    }
    
    ObjectReference::ObjectReference()
    : m_model(NULL),
      m_object_identifier(-1)
    {}

    ObjectReference::~ObjectReference()
    {
      if (m_model)
      {
        m_model->_unregisterReference(this) ;
      }
    }
    
    ObjectReference& ObjectReference::operator=(const ObjectReference& reference)
    {
      if (&reference != this)
      {
        if (m_model)
        {
          m_model->_unregisterReference(this) ;
        }
        m_model = reference.m_model ;
        m_object_identifier = reference.m_object_identifier ;
        if (m_model)
        {
          m_model->_registerReference(this) ;
        }
      }
    }

    ObjectReference::ObjectReference(const ObjectReference& reference)
    : m_model(reference.m_model),
      m_object_identifier(reference.m_object_identifier)
    {
      if (m_model)
      {
        m_model->_registerReference(this) ;
      }
    }
    
    ObjectReference::operator Object*() const
    {
      if (m_model)
      {
        return m_model->getObject(m_object_identifier) ;
      }
      else
      {
        return NULL ;
      } 
    }

    bool ObjectReference::operator!() const
    {
      return ((Object*)*this) == NULL ;
    }
    
    ObjectReference::operator bool() const
    {
      return ((Object*)*this) != NULL ;
    }
    
    Object* ObjectReference::operator->()
    {
      return ((Object*)*this) ;
    }

    bool ObjectReference::operator==(const ObjectReference& reference) const 
    {
      return (m_model == reference.m_model) &&  
             (m_object_identifier == reference.m_object_identifier) ;
    }

    void ObjectReference::_setModel(Model* model)
    {
      m_model = model ;
    }
    
  }
}

