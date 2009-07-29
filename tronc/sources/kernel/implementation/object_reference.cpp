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
#include <kernel/reader.h>
#include <kernel/writer.h>
#include <kernel/object_reference.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    
    ObjectReference::ObjectReference(Object* object)
    : m_model(object?object->getModel():NULL),
      m_object_identifier(object?object->getIdentifier():-1),
      m_reader(NULL)
    {
      if (m_model)
      {
        m_model->_registerReference(this) ;
      }
    }
    
    ObjectReference::ObjectReference()
    : m_model(NULL),
      m_object_identifier(-1),
      m_reader(NULL)
    {}

    ObjectReference::~ObjectReference()
    {
      if (m_model)
      {
        m_model->_unregisterReference(this) ;
      }
      
      if (m_reader)
      {
        m_reader->_unregisterReference(this) ;
      }
    }
    
    ObjectReference ObjectReference::read(Reader* reader)
    {
      ObjectReference result ;
      
      std::map<std::string,std::string>::const_iterator finder ; 

      finder = reader->getAttributes().find("id") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_object_identifier = atoi(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Kernel::ObjectReference::read required attribute : id") ;
      }

      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}
      
      reader->processNode() ;
      
      reader->_registerReference(&result) ;
      result.m_reader = reader ;
      
      return result ;            
    }
    
    ObjectReference& ObjectReference::operator=(const ObjectReference& reference)
    {
      if (&reference != this)
      {
        if (m_model)
        {
          m_model->_unregisterReference(this) ;
        }
        if (m_reader)
        {
          m_reader->_unregisterReference(this) ;
        }
        m_model = reference.m_model ;
        m_object_identifier = reference.m_object_identifier ;
        m_reader = reference.m_reader ;
        if (m_model)
        {
          m_model->_registerReference(this) ;
        }
        if (m_reader)
        {
          m_reader->_registerReference(this) ;
        }
      }
      return *this ;
    }

    ObjectReference& ObjectReference::operator=(Object* object)
    {
      if (m_model)
      {
        m_model->_unregisterReference(this) ;
      }

      if (m_reader)
      {
        m_reader->_unregisterReference(this) ;
      }
      
      m_model = object?object->getModel():NULL ;
      m_object_identifier = object?object->getIdentifier():-1 ;
      m_reader = NULL ;
      if (m_model)
      {
        m_model->_registerReference(this) ;
      }
      return *this ;
    }

    ObjectReference::ObjectReference(const ObjectReference& reference)
    : m_model(reference.m_model),
      m_object_identifier(reference.m_object_identifier),
      m_reader(reference.m_reader)
    {
      if (m_model)
      {
        m_model->_registerReference(this) ;
      }
      
      if (m_reader)
      {
        m_reader->_registerReference(this) ;
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
    
    Object* ObjectReference::operator->() const
    {
      return ((Object*)*this) ;
    }

    bool ObjectReference::operator==(const ObjectReference& reference) const 
    {
      return (m_model == reference.m_model) &&  
             (m_object_identifier == reference.m_object_identifier) ;
    }

    bool ObjectReference::operator<(const ObjectReference& reference) const 
    {
      return m_object_identifier < reference.m_object_identifier ;
    }

    void ObjectReference::_setModel(Model* model)
    {
      m_model = model ;
    }
    
    void ObjectReference::write(Writer* writer,const std::string& name)
    {
      writer->startTrait("ObjectReference") ;
      writer->addAttribute("id",toString(m_object_identifier)) ;
      if (name != "")
        writer->addAttribute("name",name) ;
        
      writer->endTrait() ;
    }
    
  }
}

