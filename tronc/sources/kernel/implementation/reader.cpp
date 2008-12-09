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
#include <iostream>
#include <kernel/string.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/model.h>
#include <kernel/object_reference.h>

#include <kernel/reader.h>

namespace ProjetUnivers {
  namespace Kernel {

    Object* Reader::readObject(Model* model,Object* parent)
    {
      if (!isObjectNode() || !isBeginNode())
      {
        std::cerr << "expected object node" << std::endl ; 
        return NULL ;
      }
      Object* result ;
      
      if (parent)
      {
        result = model->createObject(parent) ;
      }
      else
      {
        result = model->createObject() ;
      }
      
      // internal to normal id
      m_local_id_to_real_id[getObjectIdentifier()] = result->getIdentifier() ;
      
      while (!isEndNode() && processNode())
      {
        if (isObjectNode())
        {
          readObject(model,result) ;
        }
        else if (isTraitNode())
        {
          Trait* trait = Trait::read(this) ;
          if (trait)
          {
            model->addTrait(result,trait) ;
          }
        }
      }

      processNode() ;

      return result ;
    }
    
    Object* Reader::internalReadModel(Model* model,Object* parent)
    {
      m_local_id_to_real_id.clear() ;
      m_references.clear() ;
            
      if (! isModelNode())
      {
        std::cerr << "first node is not a model" << std::endl ; 
        return NULL ;
      }
      
      int depth = getNodeDepth() ;
      
      std::set<Object*> roots ;
      
      // reading
      while (moveToTraitOrChild(depth) && isObjectNode())
      {
        roots.insert(readObject(model,parent)) ;
      }
      
      // local reference resolution 
      try
      {      
        for(std::set<ObjectReference*>::const_iterator reference = m_references.begin() ;
            reference != m_references.end() ;
            ++reference)
        {
          std::map<int,int>::const_iterator finder 
            = m_local_id_to_real_id.find((*reference)->m_object_identifier) ;
          if (finder != m_local_id_to_real_id.end())
          {
          
            (*reference)->m_object_identifier = finder->second ;
            (*reference)->m_reader = NULL ;
            (*reference)->_setModel(model) ;
          }
          else
          {
            ErrorMessage("Kernel::Reader::read undefined identifier") ;
            throw std::exception() ;
          }
        }
      }
      catch(std::exception)
      {
        for(std::set<Object*>::const_iterator object = roots.begin() ;
            object != roots.end() ;
            ++object)
        {
          model->destroyObject(*object) ;
        }
      }
      
      if (roots.size() > 0)
      {
        return *roots.begin() ;
      }
      else
      {
        return NULL ;
      }
    }
    
    void Reader::read(Model* model)
    {
      internalReadModel(model,NULL) ;
    }

    Object* Reader::read(Object* parent)
    {
      return internalReadModel(parent->getModel(),parent) ;
    }
    
    bool Reader::moveToTraitOrChild(const int& depth)
    {
      while (!isTraitNode() && (!isObjectNode() && getNodeDepth() >= depth) 
             && processNode())
      {
//        std::cout << print() << std::endl ;
      }
      
      return hasNode() ;
    }

    std::string Reader::getName() const
    {
      std::map<std::string,std::string>::const_iterator finder ; 
  
      finder = getAttributes().find("name") ;
      if (finder != getAttributes().end())
      {
        return finder->second ;
      }
      
      return "" ;
    }
    
    std::string Reader::print() const
    {
      std::string result("<node name=") ;
      
      result = result + getTraitName() 
               + " isbegin=" + (const char*)(isBeginNode()?"true":"false")
               + " isend=" + (const char*)(isEndNode()?"true":"false")
               + " isobject=" + (const char*)(isObjectNode()?"true":"false")
               + " istrait=" + (const char*)(isTraitNode()?"true":"false")
               + " depth=" + toString(getNodeDepth())
               + "/>" ;
      
      return result ;
    }    

    void Reader::_registerReference(ObjectReference* reference)
    {
      m_references.insert(reference) ;
    }
      
    void Reader::_unregisterReference(ObjectReference* reference)
    {
      m_references.erase(reference) ;
    }
  }
}
    
