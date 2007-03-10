/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#include <typeinfo>
#include <kernel/error.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/exception_kernel.h>

#include <kernel/trait.h>
#include <kernel/model.h>
#include <kernel/view_point.h>
#include <kernel/object.h>


namespace ProjetUnivers {
  namespace Kernel {

 
    std::string Object::getName() const
    {
      return name ;
    }

    Object* Object::getParent() const
    {
      return parent ;
    }

    /// Get top most ancestor.
    Object* Object::getRoot() const
    {
    
    }

  // @}  
  /*!
    @name Construction
  */
  // @{
  

    Object::Object(Model* i_model,const std::string& i_name)
    : name(i_name),
      parent(NULL),
      model(i_model)
    {
    }

    void Object::_add(Trait* i_trait)
    {
      check(i_trait,ExceptionKernel("Kernel::_add(Trait*) no trait")) ;
      
      Kernel::Log::InternalMessage("Kernel::Object::_add(Trait)#1") ;

      /// erreur si l'objet a déjà une facette de ce type là
      check(traits.find(typeid(*i_trait).name())==traits.end(), 
            ExceptionKernel("trait already exists")) ;

      Kernel::Log::InternalMessage("Registering :") ;
      Kernel::Log::InternalMessage(typeid(*i_trait).name()) ;
      Kernel::Log::InternalMessage("with value :") ;
      Kernel::Log::InternalMessage(toString((int)i_trait).c_str()) ;

      i_trait->object = this ;

      /// on range les facettes en fonction de leur classe
      traits[typeid(*i_trait).name()] = i_trait ;

#ifdef _DEBUG          
      std::map<std::string, Trait*>::const_iterator it = traits.find(typeid(*i_trait).name()) ;
      if (it != traits.end())
      {
        Kernel::Log::InternalMessage("trait found") ;
        std::pair<std::string, Trait*> temp = *it ;
        Kernel::Log::InternalMessage("trait name = ") ;
        Kernel::Log::InternalMessage(temp.first.c_str()) ;
        Kernel::Log::InternalMessage("trait value = ") ;
        Kernel::Log::InternalMessage(toString((int)temp.second).c_str()) ;
      }
#endif      
      i_trait->_create_views() ;
      i_trait->_init() ;

      Kernel::Log::InternalMessage("traits number = ") ;
      Kernel::Log::InternalMessage(toString(traits.size()).c_str()) ;
      Kernel::Log::InternalMessage("Kernel::Object::add(facette)#3") ;
    }

    Object* Object::_add(Object* i_child)
    {
      check(i_child,
            ExceptionKernel("Object::add(Object*) : _object is NULL")) ;

      /// on met à jour le lien contenu/contenant
      i_child->parent = this ;
      children.insert(i_child) ;

      /// useless
      i_child->_init() ;

      return i_child ;
    }

    void Object::_remove(Object* i_child)
    {
      delete _release(i_child) ;
    }

    Object* Object::_release(Object* i_child)
    {
      i_child->_close() ;
      this->children.erase(i_child) ;
      return i_child ;
    }

    void Object::_remove(Trait* i_trait)
    {
      i_trait->_close() ;
      
      this->traits.erase(typeid(*i_trait).name()) ;
      delete i_trait ;
    }

    Object::~Object()
    {
      //_close() ;
      
      for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        delete trait->second ;
      }
      
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        delete *child ;
      }
    }

    void Object::_init()
    {
      for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        trait->second->_init() ;
      }
      
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->_init() ;
      }
    }
    
    void Object::_init(ViewPoint* i_viewpoint)
    {
      if (i_viewpoint->isVisible(this))
      {
        for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
            trait != traits.end() ;
            ++trait)
        {
          trait->second->_init(i_viewpoint) ;
        }
        
        for(std::set<Object*>::iterator child = children.begin() ;
            child != children.end() ;
            ++child)
        {
          (*child)->_init(i_viewpoint) ;
        }
      }
    }
    
    void Object::_close() 
    {
      
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->_close() ;
      }

      for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        trait->second->_close() ;
      }
      
    }

    void Object::_close(ViewPoint* i_viewpoint)
    {
      if (i_viewpoint->isVisible(this))
      {
        
        for(std::set<Object*>::iterator child = children.begin() ;
            child != children.end() ;
            ++child)
        {
          (*child)->_close(i_viewpoint) ;
        }

        for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
            trait != traits.end() ;
            ++trait)
        {
          trait->second->_close(i_viewpoint) ;
        }

      }
    }

    void Object::_create_views(ViewPoint* i_viewpoint)
    {
      Log::InternalMessage(
        (std::string("Object::_create_views ") + typeid(*i_viewpoint).name()).c_str()) ;

      if (i_viewpoint->isVisible(this))
      {
      
        for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
            trait != traits.end() ;
            ++trait)
        {
          trait->second->_create_views(i_viewpoint) ;
        }
        
        for(std::set<Object*>::iterator child = children.begin() ;
            child != children.end() ;
            ++child)
        {
          (*child)->_create_views(i_viewpoint) ;
        }
      }
    }
    
    void Object::_changed_parent(Object* i_old_parent)
    {
      for(std::map<std::string, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        trait->second->_changed_parent(i_old_parent) ;
      }
    }


  }
}
