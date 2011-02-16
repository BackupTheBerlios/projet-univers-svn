/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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


namespace ProjetUnivers
{
  namespace Kernel
  {

    std::set<const Kernel::Object*> Object::m_already_called_objects ;

    std::map<std::string,Kernel::ObjectReference> Object::m_named_objects ;

    bool Object::m_is_reading = false ;

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

    Trait* Object::addTrait(Trait* trait)
    {
      if (getModel())
        return getModel()->addTrait(this,trait) ;
      else
      {
        delete trait ;
        return NULL ;
      }
    }

    void Object::destroyTrait(Trait* trait)
    {
      if (getModel())
        getModel()->destroyTrait(this,trait) ;
    }

    void Object::setName(const std::string& name)
    {
      m_named_objects[name] = this ;
      m_name = name ;
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
      }

      return m_validities[i_formula->getIdentifier()] ;
    }

    void Object::setValidity(const Formula* i_formula,bool i_validity)
    {
      CHECK(Formula::getNumberOfFormulae() <= m_validities.size(),
            "Object::setValidity not enought place") ;

      if (i_formula->getIdentifier() >= (int)m_validities.size())
      {
        // error
        std::cout << "error" << std::endl << i_formula->print() ;
      }

      m_validities[i_formula->getIdentifier()] = i_validity ;
    }

    Implementation::Number Object::getNumberOfTrueChildFormulae(const Formula* formula) const
    {
      CHECK(formula,"Object::getNumberOfTrueChildFormulae no formula") ;
      CHECK(Formula::getNumberOfFormulae() <= m_number_of_true_child_formulae.size(),
            "Object::getNumberOfTrueChildFormulae not enought place") ;

      Implementation::Number result = m_number_of_true_child_formulae[formula->getIdentifier()] ;

      if (result < 0 && !isDeleting())
        throw ExceptionKernel("Object::getNumberOfTrueChildFormulae getting a negative value for "
                              + formula->print()) ;

      return result ;
    }

    void Object::setNumberOfTrueChildFormulae(const Formula* formula,
                                              Implementation::Number          number)
    {
      CHECK(formula,"Object::setNumberOfTrueChildFormulae no formula") ;
      CHECK(Formula::getNumberOfFormulae() <= m_number_of_true_child_formulae.size(),
            "Object::setNumberOfTrueChildFormulae not enough place") ;

      if (number < 0)
        /*
          temporary hack, the issue comes from destroying an object
          in some cases we start by destroying a deduced trait... and after
          we destroy the underlying trait causing a double removal...
        */
        return ;

      if (number < 0 && !isDeleting())
        throw ExceptionKernel("Object::setNumberOfTrueChildFormulae setting a negative value for "
                              + formula->print()) ;

      m_number_of_true_child_formulae[formula->getIdentifier()] = number ;
    }

  // @}
  /*!
    @name Construction
  */
  // @{


    Object::Object(Model* model)
    : m_deleting(false),
      m_identifier(model->m_next_identifier++),
      m_parent(NULL),
      m_model(model),
      m_validities(Formula::getNumberOfFormulae(),false),
      m_number_of_true_child_formulae(Formula::getNumberOfFormulae(),0),
      m_locks(0)
    {
    }

    void Object::_addPrimitiveTrait(Trait* trait)
    {
      const TypeIdentifier& trait_name(getObjectTypeIdentifier(trait)) ;

      if (getPrimitiveTrait(trait_name))
      {
        // already have
        delete trait ;

        if (!isDeleting())
          // if we have marked the trait for destruction, undo it
          getModel()->removeTraitToDestroy(this,trait_name) ;
        return ;
      }

      trait->m_object = this ;

      _getTraits().insert(trait) ;
      m_primitive_traits[trait_name] = trait ;

      // hope deleting objects wont need it
      if (isDeleting())
      {
        getModel()->recordTraitToDestroy(trait) ;
      }
      else
      {
        trait->_create_views() ;
        trait->_create_controlers() ;
        trait->_init() ;
        DeducedTrait::addTrait(this,trait) ;
      }
    }

    void Object::_addDeducedTrait(DeducedTrait* trait)
    {
      const TypeIdentifier& trait_name(getObjectTypeIdentifier(trait)) ;

      if (_getDeducedTrait(trait_name))
      {
        // already have
        delete trait ;

        if (!isDeleting())
          // if we have marked the trait for destruction, undo it
          getModel()->removeTraitToDestroy(this,trait_name) ;
        return ;
      }

      trait->m_object = this ;

      _getTraits().insert(trait) ;
      m_deduced_traits[trait_name] = trait ;

      // hope deleting objects wont need it
      if (isDeleting())
      {
        getModel()->recordTraitToDestroy(trait) ;
      }
      else
      {
        trait->_create_views() ;
        trait->_create_controlers() ;
        trait->_init() ;
        DeducedTrait::addTrait(this,trait) ;
      }
    }

    Object* Object::_add(Object* child)
    {
      CHECK(child,
            "Object::add(Object*) : _object is NULL") ;

      child->m_parent = this ;
      children.insert(child) ;

      /// useless ?
      child->_init() ;

      return child ;
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

    void Object::_removePrimitiveTrait(Trait* trait)
    {
      /*
      should be before closing because closing local views/controlers
      because views/controlers on deduced trait including the current trait
      would depend on local views.
      */
      DeducedTrait::removeTrait(this,trait) ;
      trait->_close() ;
      getModel()->recordTraitToDestroy(trait) ;
    }

    void Object::_removeDeducedTrait(const TypeIdentifier& trait_name)
    {
      Trait* trait = _getDeducedTrait(trait_name) ;
      /*
      should be before closing because closing local views/controlers
      because views/controlers on deduced trait including the current trait
      would depend on local views.
      */
      DeducedTrait::removeTrait(this,trait) ;
      trait->_close() ;
      getModel()->recordTraitToDestroy(trait) ;
    }

    void Object::_detach(Trait* trait)
    {
      if (!_getTraits().empty())
      {
        const TypeIdentifier& trait_name = getObjectTypeIdentifier(trait) ;
        m_primitive_traits.erase(trait_name) ;
        m_deduced_traits.erase(trait_name) ;
        _getTraits().erase(trait) ;
      }
    }

    Object::~Object()
    {
      m_deleting = true ;
      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {
        delete *trait ;
      }

      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        delete *child ;
      }

      if (m_model)
        m_model->_removeObjectIdentifier(m_identifier) ;
    }

    void Object::_init()
    {
      if (!mayInit())
        return ;

      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {
        (*trait)->_init() ;
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
      if (!mayInit())
        return ;

      if (i_viewpoint->isVisible(this))
      {
        for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
            trait != _getTraits().end() ;
            ++trait)
        {
          (*trait)->_init(i_viewpoint) ;
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
      if (!mayInit())
        return ;

      if (i_controler_set->isVisible(this))
      {
        for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
            trait != _getTraits().end() ;
            ++trait)
        {
          (*trait)->_init(i_controler_set) ;
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
      m_deleting = true ;

      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->_close() ;
      }

      // @todo switch between deduced and ...
      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {
        destroyTrait(*trait) ;
      }

      getModel()->removeRelations(this) ;
    }

    void Object::_close(ViewPoint* i_viewpoint)
    {
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->_close(i_viewpoint) ;
      }

      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {

        (*trait)->_close(i_viewpoint) ;
      }

    }

    void Object::_close(ControlerSet* i_controler_set)
    {
      if (i_controler_set->isVisible(this))
      {
        for(std::set<Object*>::iterator child = children.begin() ;
            child != children.end() ;
            ++child)
        {
          (*child)->_close(i_controler_set) ;
        }

        for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
            trait != _getTraits().end() ;
            ++trait)
        {
          (*trait)->_close(i_controler_set) ;
        }

      }
    }

    void Object::_create_views(ViewPoint* i_viewpoint)
    {
      if (i_viewpoint->isVisible(this))
      {

        for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
            trait != _getTraits().end() ;
            ++trait)
        {
          (*trait)->_create_views(i_viewpoint) ;
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
      if (i_controler_set->isVisible(this))
      {

        for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
            trait != _getTraits().end() ;
            ++trait)
        {
          (*trait)->_create_controlers(i_controler_set) ;
        }

        for(std::set<Object*>::iterator child = children.begin() ;
            child != children.end() ;
            ++child)
        {
          (*child)->_create_controlers(i_controler_set) ;
        }
      }
    }

    void Object::_changed_parent(Object* old_parent)
    {
      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {
        (*trait)->_changed_parent(old_parent) ;
      }

      DeducedTrait::changeParent(this,old_parent) ;
    }

    Trait* Object::getTrait(const TypeIdentifier& trait_type) const
    {
      Trait* result = _getDeducedTrait(trait_type) ;
      if (result)
        return result ;

      return getPrimitiveTrait(trait_type) ;
    }

    Trait* Object::getPrimitiveTrait(const TypeIdentifier& trait_type) const
    {
      // @todo try with searching if trait_type is a deduced trait or not
      std::map<TypeIdentifier,Trait*>::const_iterator finder = m_primitive_traits.find(trait_type) ;
      if (finder != m_primitive_traits.end())
      {
        return finder->second ;
      }

      for(std::map<TypeIdentifier,Trait*>::const_iterator trait = m_primitive_traits.begin() ;
          trait != m_primitive_traits.end() ;
          ++trait)
      {
        if (trait_type.isInstance(trait->second))
        {
          return trait->second ;
        }
      }

      return NULL ;

    }

    DeducedTrait* Object::_getDeducedTrait(const TypeIdentifier& trait_name) const
    {
      /// simpler/faster : no inheritance is taken into account
      std::map<TypeIdentifier,DeducedTrait*>::const_iterator trait = m_deduced_traits.find(trait_name) ;
      if (trait != m_deduced_traits.end())
      {
        return trait->second ;
      }
      return NULL ;
    }

    void Object::applyTopDown(
      ControlerSet*                         controler_set,
      boost::function1<void,BaseControler*> operation)
    {
      // the set of trait may vary during apply so we store it once for all
      std::set<TypeIdentifier> saved_traits ;

      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {
        saved_traits.insert(getObjectTypeIdentifier(*trait)) ;
      }

      for(std::set<TypeIdentifier>::const_iterator trait = saved_traits.begin() ;
          trait != saved_traits.end() ;
          ++trait)
      {
        // if object still has the trait apply
        Trait* local_trait = getTrait(*trait) ;
        if (local_trait)
          local_trait->apply(controler_set,operation) ;
      }

      /// the set of child may vary...
      std::set<Object*> saved_children(children) ;

      for(std::set<Object*>::iterator child = saved_children.begin() ;
          child != saved_children.end() ;
          ++child)
      {
        (*child)->applyTopDown(controler_set,operation) ; ;
      }
    }

    void Object::applyBottomUp(
      ControlerSet*                         i_controler_set,
      boost::function1<void,BaseControler*> i_operation)
    {
      std::set<Trait*> locked_traits(lockTraits()) ;
      /// the set of child may vary...
      std::set<Object*> saved_children(children) ;

      for(std::set<Object*>::iterator child = saved_children.begin() ;
          child != saved_children.end() ;
          ++child)
      {
        (*child)->applyBottomUp(i_controler_set,i_operation) ; ;
      }

      std::set<TypeIdentifier> saved_traits ;

      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {
        saved_traits.insert(getObjectTypeIdentifier(*trait)) ;
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
      unlockTraits(locked_traits) ;
    }

    bool Object::call(const std::string& i_command)
    {
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

    bool Object::_call(const std::string& command)
    {
      if (m_already_called_objects.find(this) != m_already_called_objects.end())
        return false ;

      m_already_called_objects.insert(this) ;
      bool found = false ;

      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() && !found ;
          ++trait)
      {
        found = (*trait)->call(getObjectTypeIdentifier(*trait),command) ;
      }

      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() && !found ;
          ++child)
      {
        found = (*child)->_call(command) ;
      }

      return found ;
    }

    bool Object::_call(const std::string& command,const int& parameter)
    {
      if (m_already_called_objects.find(this) != m_already_called_objects.end())
        return false ;

      m_already_called_objects.insert(this) ;
      bool found = false ;

      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() && !found ;
          ++trait)
      {
        found = (*trait)->call(getObjectTypeIdentifier(*trait),command,parameter) ;
      }

      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() && !found ;
          ++child)
      {
        found = (*child)->_call(command,parameter) ;
      }

      return found ;
    }

    std::set<std::string> Object::_getCommands() const
    {
      std::set<std::string> result ;

      if (m_already_called_objects.find(this) != m_already_called_objects.end())
        return result ;

      m_already_called_objects.insert(this) ;

      for(std::set<Trait*>::const_iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {
        std::set<std::string> temp((*trait)->getCommands()) ;
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

    bool Object::isDeleting() const
    {
      return m_deleting ;
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

    std::set<Trait*> Object::getDirectChildren(const TypeIdentifier& identifier) const
    {
      std::set<Trait*> result ;
      Trait* local = getTrait(identifier) ;
      if (local)
      {
        result.insert(local) ;
        return result ;
      }

      return getDirectDescendants(identifier) ;
    }

    std::set<Trait*> Object::getDirectDescendants(const TypeIdentifier& identifier) const
    {
      std::set<Trait*> result ;

      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        std::set<Trait*> temp = (*child)->getDirectChildren(identifier) ;
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
    }

    Trait* Object::getParent(const TypeIdentifier& identifier) const
    {
      Object* iterator(const_cast<Object*>(this)) ;
      Trait* trait(iterator->getTrait(identifier)) ;

      while((! trait) && iterator)
      {
        iterator = iterator->getParent() ;
        if (iterator)
        {
          trait = iterator->getTrait(identifier) ;
        }
      }

      return trait ;
    }

    Trait* Object::getAncestor(const TypeIdentifier& identifier) const
    {
      Object* iterator(getParent()) ;
      Trait* trait = NULL ;

      while((! trait) && iterator)
      {
        trait = iterator->getTrait(identifier) ;
        iterator = iterator->getParent() ;
      }

      return trait ;
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

    unsigned int Object::getNumberOfParent(const Formula* formula) const
    {
      unsigned int result = 0 ;

      Object* iterator(const_cast<Object*>(this)) ;
      while(iterator)
      {
        if (formula->isValid(iterator))
          ++result ;
        iterator = iterator->getParent() ;
      }
      return result ;
    }

    unsigned int Object::getNumberOfAncestor(const Formula* formula) const
    {
      if (getParent())
        return getNumberOfParent(formula) ;

      return 0 ;
    }

    unsigned int Object::getNumberOfAncestor(const TypeIdentifier& name) const
    {
      unsigned int result = 0 ;

      Object* iterator(getParent()) ;
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

    unsigned int Object::getNumberOfChildren(const Formula* formula) const
    {
      unsigned int result = 0 ;

      // recurse
      for(std::set<Object*>::const_iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        result += (*child)->getNumberOfChildren(formula) ;
      }

      // local
      if (formula->isValid(const_cast<Object*>(this)))
        ++result ;

      return result ;
    }

    void Object::startReading()
    {
      m_is_reading = true ;
    }

    void Object::stopReading()
    {
      m_is_reading = false ;
    }

    std::set<Trait*> Object::lockTraits()
    {
      std::set<Trait*> result ;
      for(std::set<Trait*>::iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {
        (*trait)->lock() ;
        result.insert(*trait) ;
      }
      return result ;
    }

    void Object::unlockTraits(const std::set<Trait*>& traits)
    {

      for(std::set<Trait*>::const_iterator trait = traits.begin() ;
          trait != traits.end() ;
          ++trait)
      {
        (*trait)->unlock() ;
      }
    }

    void Object::addLock()
    {
      ++m_locks ;
      if (getParent())
        getParent()->addLock() ;
    }

    void Object::removeLock()
    {
      if (m_locks==0)
      {
        ErrorMessage("should not remove locks") ;
        return ;
      }

      --m_locks ;
      if (getParent())
        getParent()->removeLock() ;
    }

    bool Object::isLocked() const
    {
      return m_locks>0 ;
    }

    bool Object::mayInit() const
    {
      return !m_deleting ;
    }

    std::set<Trait*>& Object::_getTraits()
    {
      return m_traits ;
    }

    const std::set<Trait*>& Object::_getTraits() const
    {
      return m_traits ;
    }

    std::string Object::toGraphviz(boost::function1<bool,Trait*> trait_condition) const
    {
      std::string object(graphvizName()) ;

      // print the object it self
      std::string result(object) ;

      result += " [label=<<TABLE>" ;
      result += "<TR><TD>" ;
      result += Kernel::toString(getIdentifier()) ;
      result += "</TD></TR>" ;

      // print the traits we use HTML array grouping
      if (!_getTraits().empty())
      {
        std::string traits ;

        for(std::set<Trait*>::const_iterator trait = _getTraits().begin() ;
            trait != _getTraits().end() ;
            ++trait)
        {
          traits = traits + "<TR><TD TOOLTIP=\"" + getObjectTypeIdentifier(*trait).fullName() + "\" " +
                                    "PORT=\"" + (*trait)->getGraphvizPortName() + "\"" ;


          // color indicate status :
          //  red for primitive trait to be destroyed
          //  yellow for deduced trait
          //  orange for primitive trait to be destroyed
          if (trait_condition((*trait)))
          {
            traits += " BGCOLOR=\"green\"" ;
          }
          else if (!(*trait)->isPrimitive())
          {
            if (getModel()->isToBeDestroyed((*trait)))
            {
              traits += " BGCOLOR=\"orange\"" ;
            }
            else
            {
              traits += " BGCOLOR=\"yellow\"" ;
            }
          }
          else if (getModel()->isToBeDestroyed((*trait)))
          {
            traits += " BGCOLOR=\"red\"" ;
          }

          traits += + ">" ;
          traits += getObjectTypeIdentifier(*trait).className() ;
          traits += "</TD></TR>\n" ;
        }

        result += traits ;
      }

      result += "</TABLE>>" ;

      result += "]" ;
      result += " ;\n" ;

      // dependencies
      for(std::set<Trait*>::const_iterator trait = _getTraits().begin() ;
          trait != _getTraits().end() ;
          ++trait)
      {
        if (trait_condition((*trait)))
        {
          const std::set<Notifiable*>& dependencies = (*trait)->getDependencies() ;

          for(std::set<Notifiable*>::const_iterator dependency = dependencies.begin() ; dependency != dependencies.end() ; ++dependency)
          {
            result += (*trait)->graphvizName() ;
            result += " -> " ;
            result += (*dependency)->graphvizName() ;
            result += " [style=dashed];\n" ;
          }
        }
      }

      // print its children + link parent/child
      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        result += (*child)->toGraphviz(trait_condition) ;

        std::string object_child((*child)->graphvizName()) ;

        result = result + object + " -> " + object_child + " ;\n" ;
      }

      return result ;

    }

    namespace
    {
      bool alwaysTrue(Trait*)
      {
        return true ;
      }
    }

    std::string Object::toGraphviz() const
    {

      return toGraphviz(&alwaysTrue) ;
    }

    std::string Object::toGraphviz(ViewPoint* viewpoint) const
    {
      return toGraphviz(boost::bind(&Trait::hasViewPoint,_1,viewpoint)) ;
    }

    std::string Object::toGraphviz(ControlerSet* controller_set) const
    {

      return toGraphviz(boost::bind(&Trait::hasController,_1,controller_set)) ;
    }

    std::string Object::graphvizName() const
    {
      return "Object_" + Kernel::toString(getIdentifier()) ;
    }

    void Object::buildGraphvizRanks(const int& current_rank,std::map<int,std::string>& ranks) const
    {
      ranks[current_rank] += graphvizName() ;
      ranks[current_rank] += " ; " ;

      for(std::set<Object*>::iterator child = children.begin() ;
          child != children.end() ;
          ++child)
      {
        (*child)->buildGraphvizRanks(current_rank+1,ranks) ;
      }
    }
  }
}
