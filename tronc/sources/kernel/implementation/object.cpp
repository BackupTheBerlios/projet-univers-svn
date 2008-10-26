/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <iostream>
#include <kernel/error.h>
#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/exception_kernel.h>

#include <kernel/controler_set.h>
#include <kernel/trait.h>
#include <kernel/model.h>
#include <kernel/view_point.h>
#include <kernel/deduced_trait.h>
#include <kernel/reader.h>
#include <kernel/object.h>


namespace ProjetUnivers {
  namespace Kernel {

    std::set<const Kernel::Object*> Object::m_already_called_objects ;
    
    std::map<std::string,Kernel::ObjectReference> Object::m_named_objects ;
    namespace 
    {
      int next_identifier = 1 ;
    }

    Object* Object::createObject()
    {
      if (getModel())
        return getModel()->createObject(this) ;
      else
        return NULL ;
    }

    void Object::destroyObject()
    {
      if (getModel())
        getModel()->destroyObject(this) ;
    }

    void Object::changeParent(Object* new_parent)
    {
      if (getModel())
        getModel()->changeParent(this,new_parent) ;
    }
    
    void Object::addTrait(Trait* trait)
    {
      if (getModel())
        getModel()->addTrait(this,trait) ;
      else
        delete trait ;
    }

    void Object::destroyTrait(Trait* trait)
    {
      if (getModel())
        getModel()->destroyTrait(this,trait) ;
    }
    
    void Object::setName(const std::string& name)
    {
      m_named_objects[name] = this ;
    }
    
    Object* Object::get(const std::string& name)
    {
      std::map<std::string,ObjectReference>::const_iterator finder =
        m_named_objects.find(name) ;
      
      if (finder != m_named_objects.end())
      {
        return finder->second ;
      }
      
      return NULL ;
    }
    
    int Object::getIdentifier() const
    {
      return m_identifier ;
    }

    Object* Object::getParent() const
    {
      return m_parent ;
    }

    const Object* Object::getRoot() const
    {
      if (m_parent)
      {
        return m_parent->getRoot() ;
      }
      else
      {
        return this ;
      }
    }

    const Object* Object::getCommonAncestor(const Object* object) const
    {
      if (m_model == object->m_model)
      {
        std::list<Object*> ancestors(getAncestorPath()) ;
        std::list<Object*> object_ancestors(object->getAncestorPath()) ;
        
        const Object* result = NULL ;
        
        std::list<Object*>::const_iterator i = ancestors.begin() ;
        std::list<Object*>::const_iterator j = object_ancestors.begin() ;
        
        while (i != ancestors.end() && j != object_ancestors.end() &&
               *i == *j)
        {
          result = *i ;
          ++i ;
          ++j ;
        } 
        
        return result ;
      }

      return NULL ;
    }

    Model* Object::getModel() const
    {
      return m_model ;
    }

    bool Object::getValidity(const Formula* i_formula) const
    {
      CHECK(Formula::getNumberOfFormulae() <= m_validities.size(),
            "Object::getValidity not enought place") ;

      if (i_formula->getIdentifier() < 0)
      {
        InternalMessage("Kernel","getting validity of a trait formula") ;
      }
      
      return m_validities[i_formula->getIdentifier()] ; 
    }
    
    void Object::setValidity(const Formula* i_formula,bool i_validity)
    {
      CHECK(Formula::getNumberOfFormulae() <= m_validities.size(),
            "Object::setValidity not enought place") ;

      if (i_formula->getIdentifier() >= m_validities.size())
      {
        // error
        std::cout << "error" << std::endl << i_formula->print() ;
      }
      
      m_validities[i_formula->getIdentifier()] = i_validity ;
    }

    unsigned short Object::getNumberOfTrueChildFormulae(const Formula* i_formula) const
    {
      CHECK(i_formula,"Object::getNumberOfTrueChildFormulae no formula") ;
      CHECK(Formula::getNumberOfFormulae() <= m_number_of_true_child_formulae.size(),
            "Object::getNumberOfTrueChildFormulae not enought place") ;

      return m_number_of_true_child_formulae[i_formula->getIdentifier()] ;
    }
    
    void Object::setNumberOfTrueChildFormulae(const Formula*     i_formula,
                                              unsigned short i_number)
    {
      CHECK(i_formula,"Object::setNumberOfTrueChildFormulae no formula") ;
      CHECK(Formula::getNumberOfFormulae() <= m_number_of_true_child_formulae.size(),
            "Object::setNumberOfTrueChildFormulae not enought place") ;

      m_number_of_true_child_formulae[i_formula->getIdentifier()]
        = i_number ;
    }

  // @}  
  /*!
    @name Construction
  */
  // @{
  

    Object::Object(Model* i_model)
    : m_deleting(false),
      m_identifier(next_identifier++),
      m_parent(NULL),
      m_model(i_model),
      m_validities(Formula::getNumberOfFormulae()),
      m_number_of_true_child_formulae(Formula::getNumberOfFormulae())
    {
      InternalMessage("Kernel","Formula::getNumberOfFormulae()=" + toString(Formula::getNumberOfFormulae())) ;
    }

    void Object::_add(Trait* i_trait)
    {
      if (m_deleting)
      {
        delete i_trait ;
        return ;
      }
      
      CHECK(i_trait,"Kernel::_add(Trait*) no trait") ;
      InternalMessage("Kernel","added trait " + getObjectTypeIdentifier(i_trait).toString()
                               + " to objectid=" + toString(getIdentifier())) ;

      TypeIdentifier trait_name(getObjectTypeIdentifier(i_trait)) ;

      CHECK(traits.find(trait_name)==traits.end(), 
            "trait " + trait_name.toString() + " already exists on object " + toString(getIdentifier())) ;

//      InternalMessage("Kernel","Registering :") ;
//      InternalMessage("Kernel",trait_name.toString()) ;
//      InternalMessage("Kernel","with value :") ;
//      InternalMessage("Kernel",toString((int)i_trait).c_str()) ;

      i_trait->m_object = this ;


      /// on range les facettes en fonction de leur classe
      traits[trait_name] = i_trait ;

      i_trait->_create_views() ;
      i_trait->_create_controlers() ;
      i_trait->_init() ;

      TraitFormula::addTrait(this,trait_name) ;
      HasParentFormula::addTrait(this,trait_name) ;
      HasChildFormula::addTrait(this,trait_name) ;
      
//      InternalMessage("Kernel","traits number = ") ;
//      InternalMessage("Kernel",toString(traits.size()).c_str()) ;
//      InternalMessage("Kernel","Kernel::Object::add(facette)#3") ;
    }

    Object* Object::_add(Object* i_child)
    {
      CHECK(i_child,
            "Object::add(Object*) : _object is NULL") ;

      i_child->m_parent = this ;
      children.insert(i_child) ;

      /// useless
      i_child->_init() ;

      return i_child ;
    }

    Object* Object::_attach(Object* i_child)
    {
      i_child->m_parent = this ;
      children.insert(i_child) ;
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

    Object* Object::_detach(Object* i_child)
    {
      this->children.erase(i_child) ;
      return i_child ;
    }

    void Object::_remove(const TypeIdentifier& i_trait_name)
    {
      if (m_deleting)
      {
        return ;
      }

      InternalMessage("Kernel","removed trait " + i_trait_name.toString()
                               + " to objectid=" + toString(getIdentifier())) ;

      Trait* trait = traits[i_trait_name] ;
      trait->_close() ;
      TraitFormula::removeTrait(this,i_trait_name) ;
      
      this->traits.erase(i_trait_name) ;
      delete trait ;
    }
    
    void Object::_remove(Trait* i_trait)
    {
      if (m_deleting)
      {
        return ;
      }
      
      CHECK(i_trait,"Kernel::_remove(Trait*) no trait") ;
      TypeIdentifier trait_name(getObjectTypeIdentifier(i_trait)) ;

      i_trait->_close() ;
      TraitFormula::removeTrait(this,trait_name) ;
      HasParentFormula::removeTrait(this,trait_name) ;
      HasChildFormula::removeTrait(this,trait_name) ;
      
      this->traits.erase(trait_name) ;
      delete i_trait ;
    }

    Object::~Object()
    {
      //_close() ;
      m_deleting = true ;
      InternalMessage("Kernel","Destroying object" + toString(m_identifier)) ;
      for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
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
      
      if (m_model)
        m_model->_removeObjectIdentifier(m_identifier) ;
      
      InternalMessage("Kernel","Destroyed object" + toString(m_identifier)) ;
    }

    void Object::_init()
    {
      for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
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
        for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
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

    void Object::_init(ControlerSet* i_controler_set)
    {
      if (i_controler_set->isVisible(this))
      {
        for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
            trait != traits.end() ;
            ++trait)
        {
          trait->second->_init(i_controler_set) ;
        }
        
        for(std::set<Object*>::iterator child = children.begin() ;
            child != children.end() ;
            ++child)
        {
          (*child)->_init(i_controler_set) ;
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

      for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        trait->second->_close() ;
      }
      
    }

    void Object::_close(ViewPoint* i_viewpoint)
    {
      InternalMessage("Kernel","Object::_close(ViewPoint*) closing childs") ;

      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->_close(i_viewpoint) ;
      }

      for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        
        trait->second->_close(i_viewpoint) ;
      }

    }

    void Object::_close(ControlerSet* i_controler_set)
    {
//      InternalMessage("Kernel","Object::_close entering " + name) ;
      if (i_controler_set->isVisible(this))
      {
        
//        InternalMessage("Kernel","Object::_close closing childs") ;

        for(std::set<Object*>::iterator child = children.begin() ;
            child != children.end() ;
            ++child)
        {
          (*child)->_close(i_controler_set) ;
        }

//        InternalMessage("Kernel","Object::_close closing traits") ;
        
        for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
            trait != traits.end() ;
            ++trait)
        {
//          InternalMessage("Kernel","traits=" + toString((int)trait->second)) ;
          
          trait->second->_close(i_controler_set) ;
        }

      }
//      InternalMessage("Kernel","Object::_close leaving " + name) ;
    }

    void Object::_create_views(ViewPoint* i_viewpoint)
    {
//      InternalMessage("Kernel",
//        (std::string("Object::_create_views ") + typeid(*i_viewpoint).name()).c_str()) ;

      if (i_viewpoint->isVisible(this))
      {
      
        for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
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

    void Object::_create_controlers(ControlerSet* i_controler_set)
    {
//      InternalMessage("Kernel",
//        (std::string("Object::_create_controlers ") + typeid(*i_controler_set).name()).c_str()) ;

      if (i_controler_set->isVisible(this))
      {

        for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
            trait != traits.end() ;
            ++trait)
        {
          trait->second->_create_controlers(i_controler_set) ;
        }
        
        for(std::set<Object*>::iterator child = children.begin() ;
            child != children.end() ;
            ++child)
        {
          (*child)->_create_controlers(i_controler_set) ;
        }
      }
    }
    
    void Object::_changed_parent(Object* i_old_parent)
    {
      for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        trait->second->_changed_parent(i_old_parent) ;
      }
      HasParentFormula::changeParent(this,i_old_parent) ;
      HasChildFormula::changeParent(this,i_old_parent) ;
      
    }
    
    Trait* Object::_get(const TypeIdentifier& i_trait_name) const
    {
//      InternalMessage("Kernel","Object::_get searching " + i_trait_name.toString()) ;
      std::map<TypeIdentifier, Trait*>::const_iterator trait = traits.find(i_trait_name) ;
      if (trait != traits.end()) 
      {
//        InternalMessage("Kernel","Object::_get found") ;
        return trait->second ;
      }
      
      for(std::map<TypeIdentifier, Trait*>::const_iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        if (i_trait_name.isInstance(trait->second))
        {
          return trait->second ;
        }
      }
      
//      InternalMessage("Kernel","Object::_get not found") ;

      return NULL ;
    }    

    void Object::applyTopDown(
      ControlerSet*                         i_controler_set,
      boost::function1<void,BaseControler*> i_operation)
    {
      // the set of trait may vary during apply so we store it once for all 
      std::set<TypeIdentifier> saved_traits ;

      for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        saved_traits.insert(trait->first) ;
      }

      for(std::set<TypeIdentifier>::const_iterator trait = saved_traits.begin() ;
          trait != saved_traits.end() ;
          ++trait)
      {
        // if object still has the trait apply
        Trait* local_trait = getTrait(*trait) ;
        if (local_trait)
          local_trait->apply(i_controler_set,i_operation) ;
      }
      
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->applyTopDown(i_controler_set,i_operation) ; ;
      }
    }

    void Object::applyBottomUp(
      ControlerSet*                         i_controler_set,
      boost::function1<void,BaseControler*> i_operation)
    {
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->applyBottomUp(i_controler_set,i_operation) ; ;
      }

      for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        if (trait->second)
          trait->second->apply(i_controler_set,i_operation) ;
      }
    }

    bool Object::call(const std::string& i_command) 
    {
      InternalMessage("Kernel","entering Object::call") ;
      // clear the previous called objects
      m_already_called_objects.clear() ;

      return _call(i_command) ;
    }

    bool Object::call(const std::string& i_command,const int& i_parameter) 
    {
      // clear the previous called objects
      m_already_called_objects.clear() ;
      
      return _call(i_command,i_parameter) ;
    }
    
    std::set<std::string> Object::getCommands() const
    {
      // clear the previous called objects
      m_already_called_objects.clear() ;
      
      return _getCommands() ;
    }

    bool Object::_call(const std::string& i_command) 
    {
      if (m_already_called_objects.find(this) != m_already_called_objects.end())
        return false ;

      m_already_called_objects.insert(this) ;
      bool found = false ;
      
      for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() && !found ;
          ++trait)
      {
        found = trait->second->call(trait->first,i_command) ;
      }
      
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() && !found ;
          ++child)
      {
        found = (*child)->_call(i_command) ;
      }

      return found ;
    }

    bool Object::_call(const std::string& i_command,const int& i_parameter) 
    {
      if (m_already_called_objects.find(this) != m_already_called_objects.end())
        return false ;

      m_already_called_objects.insert(this) ;
      bool found = false ;
      
      for(std::map<TypeIdentifier, Trait*>::iterator trait = traits.begin() ;
          trait != traits.end() && !found ;
          ++trait)
      {
        found = trait->second->call(trait->first,i_command,i_parameter) ;
      }
      
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() && !found ;
          ++child)
      {
        found = (*child)->_call(i_command,i_parameter) ;
      }
      
      return found ;
    }
    
    std::set<std::string> Object::_getCommands() const
    {
      std::set<std::string> result ;

      if (m_already_called_objects.find(this) != m_already_called_objects.end())
        return result ;

      m_already_called_objects.insert(this) ;
      
      for(std::map<TypeIdentifier, Trait*>::const_iterator 
            trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        std::set<std::string> temp(trait->second->getCommands()) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      
      for(std::set<Object*>::const_iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        std::set<std::string> temp((*child)->_getCommands()) ;
        result.insert(temp.begin(),temp.end()) ;
      }
      
      return result ;
    }
    
    const std::set<Object*>& Object::getChildren() const
    {
      return children ;
    }

    std::list<Object*> Object::getAncestorPath() const
    {
      std::list<Object*> result ;
      if (m_parent)
      {
        result = m_parent->getAncestorPath() ;
      }
      
      result.push_back(const_cast<Object*>(this)) ;
      return result ;
    }
    
    bool Object::isAncestor(const Object* object) const
    {
      if (this == object)
      {
        return true ;
      }
      else if (object->getParent() == NULL)
      {
        return false ;
      }
      else
      {
        return isAncestor(object->getParent()) ;
      }
    }

    Trait* Object::getTrait(const TypeIdentifier& name) const
    {
      std::map<TypeIdentifier,Trait*>::const_iterator 
        result = traits.find(name) ;
      if (result != traits.end())
      {
        return result->second ;
      }
      return NULL ;
    }
    
    unsigned int Object::getNumberOfParent(const TypeIdentifier& name) const
    {
      unsigned int result = 0 ;
      
      Object* iterator(const_cast<Object*>(this)) ;
      while(iterator)
      {
        if (iterator->getTrait(name))
          ++result ;
        iterator = iterator->getParent() ;
      }
      return result ;
    }
  
    unsigned int Object::getNumberOfChildren(const TypeIdentifier& name) const
    {
      unsigned int result = 0 ;
      
      // recurse
      for(std::set<Object*>::const_iterator child = children.begin() ;  
          child != children.end() ;
          ++child)
      {
        result += (*child)->getNumberOfChildren(name) ;
      }

      // local
      if (getTrait(name))
        ++result ;
      
      return result ;
    }
    
  }
}
