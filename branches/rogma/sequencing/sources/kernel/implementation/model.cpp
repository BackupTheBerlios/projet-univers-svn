/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#include <kernel/log.h>
#include <kernel/error.h>
#include <kernel/exception_kernel.h>

#include <kernel/implementation/transaction.h>
#include <kernel/implementation/operation.h>
#include <kernel/deduced_trait.h>
#include <kernel/object.h>
#include <kernel/object_reference.h>
#include <kernel/base_trait_view.h>
#include <kernel/trait.h>
#include <kernel/view_point.h>
#include <kernel/controler_set.h>
#include <kernel/model.h>

#include <typeinfo>


namespace ProjetUnivers
{
  namespace Kernel
  {

    namespace
    {
      int next_number = 0 ;
    }

    /// create a unique object name.
    std::string getUniqueName()
    {
      return "PU::Kernel::Name" + toString(next_number++) ;
    }

    Object* Model::getObject(const int& identifier) const
    {
      std::map<int,Object*>::const_iterator finder
        = m_objects_by_identifier.find(identifier) ;
      if (finder != m_objects_by_identifier.end())
      {
        return finder->second ;
      }
      else
      {
        return NULL ;
      }
    }

    Object* Model::createObject()
    {
      Log::Block temp("Structure","createObject (root)") ;
      m_statistics.addObject() ;
      Object* result = new Object(this) ;
      m_objects.insert(result) ;
      m_objects_by_identifier[result->getIdentifier()] = result ;
      startTransaction() ;
      DeducedTrait::evaluateInitial(result) ;
      endTransaction() ;
      return result ;
    }

    Object* Model::createObject(Object* parent)
    {
      Log::Block temp("Structure","createObject(child)") ;
      m_statistics.addObject() ;
      Object* result = new Object(this) ;
      if (parent->m_deleting)
      {
        result->m_deleting = true ;
        addObjectToDestroy(result) ;
      }
      else
      {
        parent->_add(result) ;
      }
      m_objects_by_identifier[result->getIdentifier()] = result ;
      startTransaction() ;
      DeducedTrait::evaluateInitial(result) ;
      endTransaction() ;
      return result ;
    }

    void Model::destroyObject(Object* object)
    {
      Log::Block temp("Structure","destroyObject") ;
      m_statistics.removeObject() ;

      object->m_deleting = true ;

      if (m_destroying)
        return ;

      startTransaction() ;

      object->_close() ;
      addObjectToDestroy(object) ;

      endTransaction() ;
    }

    void Model::_removeObjectIdentifier(const int& identifier)
    {
      m_objects_by_identifier.erase(identifier) ;
    }

    void Model::changeParent(Object* object,
                             Object* new_parent)
    {
      Log::Block temp("Structure","changeParent") ;

      Object* old_parent = object->getParent() ;

      if (object->getParent() == NULL)
      {
        /// a top object
        m_objects.erase(object) ;
      }
      else
      {
        object->getParent()->_detach(object) ;
      }

      new_parent->_add(object) ;
      object->_changed_parent(old_parent) ;

    }

    void Model::addTrait(Object* object,
                         Trait* new_trait)
    {
      Log::Block temp("Structure","addTrait") ;

      if (object->m_deleting)
        return ;

      bool deduced = ! new_trait->isPrimitive() ;

      startTransaction() ;
      object->_add(new_trait) ;
      endTransaction() ;

      if (deduced)
        m_statistics.addDeducedTrait() ;
      else
        m_statistics.addPrimitiveTrait() ;
    }

    void Model::destroyTrait(Object* object,
                            Trait* trait)
    {
      Log::Block temp("Structure","destroyTrait") ;

      DeducedTrait* deduced = dynamic_cast<DeducedTrait*>(trait) ;
      if (deduced)
        m_statistics.removeDeducedTrait() ;
      else
        m_statistics.removePrimitiveTrait() ;

      startTransaction() ;
      object->_remove(trait) ;
      endTransaction() ;
    }

    Model::~Model()
    {
      m_destroying = true ;

      for(std::set<ObjectReference*>::iterator reference = m_references.begin() ;
          reference != m_references.end() ;
          ++reference)
      {
        (*reference)->_setModel(NULL) ;
      }

      /// 1. close all controler sets
      for(std::set<ControlerSet*>::iterator controler_set = m_controler_sets.begin() ;
          controler_set != m_controler_sets.end() ;
          ++controler_set)
      {
        (*controler_set)->close() ;
        delete (*controler_set) ;
      }

      /// 1. close all view points
      for(std::set<ViewPoint*>::iterator viewpoint = m_viewpoints.begin() ;
          viewpoint != m_viewpoints.end() ;
          ++viewpoint)
      {
        (*viewpoint)->close() ;
        delete *viewpoint ;
      }

      /// 2. destroy m_objects
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        delete *object ;
      }
    }

    Model::Model(const std::string& name)
    : m_name(name),
      m_is_simulating_controler_set(false),
      m_next_identifier(0)
    {}

    void Model::_register(ViewPoint* viewpoint)
    {
      m_viewpoints.insert(viewpoint) ;

      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_create_views(viewpoint) ;
      }
    }

    void Model::_unregister(ViewPoint* viewpoint)
    {
      if (m_destroying)
        return ;
      m_viewpoints.erase(viewpoint) ;
    }

    void Model::_register(ControlerSet* controler_set)
    {
      m_controler_sets.insert(controler_set) ;

      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_create_controlers(controler_set) ;
      }
    }

    void Model::_unregister(ControlerSet* controler_set)
    {
      if (m_destroying)
        return ;

      m_controler_sets.erase(controler_set) ;
    }

    void Model::_init(ViewPoint* viewpoint)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_init(viewpoint) ;
      }
    }

    void Model::_close(ViewPoint* viewpoint)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_close(viewpoint) ;
      }
    }

    void Model::_init(ControlerSet* controler_set)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_init(controler_set) ;
      }
    }

    void Model::_close(ControlerSet* controler_set)
    {
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_close(controler_set) ;
      }
    }

    const std::set<Object*>& Model::getRoots() const
    {
      return m_objects ;
    }

    void Model::_registerReference(ObjectReference* reference)
    {
      m_references.insert(reference) ;
    }

    void Model::_unregisterReference(ObjectReference* reference)
    {
      m_references.erase(reference) ;
    }

    void Model::addManualView(BaseTraitView* view)
    {
      view->getTrait()->addView(view->m_viewpoint,view) ;
      if (!view->getObject()->m_deleting && view->m_viewpoint->isInitialised())
      {
        view->_init() ;
      }
    }

    const std::set<ViewPoint*>& Model::getViewPoints() const
    {
      return m_viewpoints ;
    }

    const std::set<ControlerSet*>& Model::getControlerSets() const
    {
      return m_controler_sets ;
    }

    ViewPoint* Model::addViewPoint(ViewPoint* viewpoint)
    {
      // nothing to do, viewpoints are already registered
      return viewpoint ;
    }

    ControlerSet* Model::addControlerSet(ControlerSet* controlerset)
    {
      // nothing to do, controler sets are already registered
      return controlerset ;
    }

    void Model::init()
    {
      ViewPoint::buildRegistered(this) ;
      const std::set<Kernel::ViewPoint*>& viewpoints = getViewPoints() ;
      for(std::set<Kernel::ViewPoint*>::const_iterator viewpoint = viewpoints.begin() ;
          viewpoint != viewpoints.end() ;
          ++viewpoint)
      {
        (*viewpoint)->init() ;
      }

      ControlerSet::buildRegistered(this) ;
      const std::set<Kernel::ControlerSet*>& controlersets = getControlerSets() ;
      for(std::set<Kernel::ControlerSet*>::const_iterator controlerset = controlersets.begin() ;
          controlerset != controlersets.end() ;
          ++controlerset)
      {
        (*controlerset)->init() ;
      }
    }

    void Model::close()
    {
      std::set<Kernel::ControlerSet*> controlersets = getControlerSets() ;
      for(std::set<Kernel::ControlerSet*>::const_iterator controlerset = controlersets.begin() ;
          controlerset != controlersets.end() ;
          ++controlerset)
      {
        (*controlerset)->close() ;
      }

      std::set<Kernel::ViewPoint*> viewpoints = getViewPoints() ;
      for(std::set<Kernel::ViewPoint*>::const_iterator viewpoint = viewpoints.begin() ;
          viewpoint != viewpoints.end() ;
          ++viewpoint)
      {
        (*viewpoint)->close() ;
      }
    }

    void Model::update(const float& seconds)
    {
      // first update controler sets then viewpoints
      const std::set<Kernel::ControlerSet*>& controlersets = getControlerSets() ;
      for(std::set<Kernel::ControlerSet*>::const_iterator controlerset = controlersets.begin() ;
          controlerset != controlersets.end() ;
          ++controlerset)
      {
        beginSimulation() ;
        (*controlerset)->update(seconds) ;
        endSimulation() ;
      }

      const std::set<Kernel::ViewPoint*>& viewpoints = getViewPoints() ;
      for(std::set<Kernel::ViewPoint*>::const_iterator viewpoint = viewpoints.begin() ;
          viewpoint != viewpoints.end() ;
          ++viewpoint)
      {
        (*viewpoint)->update(seconds) ;
      }
    }

    void Model::beginSimulation()
    {
      m_is_simulating_controler_set = true ;
      startTransaction() ;
    }

    void Model::endSimulation()
    {
      m_is_simulating_controler_set = false ;
      endTransaction() ;
    }

    void Model::resetStatistics()
    {
      for(std::set<Kernel::ControlerSet*>::const_iterator controlerset = getControlerSets().begin() ;
          controlerset != getControlerSets().end() ;
          ++controlerset)
      {
        (*controlerset)->resetStatistics() ;
      }
    }

    void Model::printStatistics() const
    {
      float total = 0 ;
      for(std::set<Kernel::ControlerSet*>::const_iterator controlerset = getControlerSets().begin() ;
          controlerset != getControlerSets().end() ;
          ++controlerset)
      {
        total += (*controlerset)->getStatistics() ;
        InternalMessage("Statistics",getObjectTypeIdentifier(*controlerset).toString() +
                                    "=" + Kernel::toString((*controlerset)->getStatistics())) ;
      }

      InternalMessage("Statistics","total =" + Kernel::toString(total)) ;

      InternalMessage("Statistics","number of deduced traits per objects = " + Kernel::toString(m_statistics.maximumNumberOfDeducedTraitsPerObject())) ;
      InternalMessage("Statistics","number of primitive traits per objects = " + Kernel::toString(m_statistics.maximumNumberOfPrimitiveTraitsPerObject())) ;

    }

    void Model::setTimeStep(const float& seconds)
    {
      for(std::set<Kernel::ControlerSet*>::const_iterator controlerset = getControlerSets().begin() ;
          controlerset != getControlerSets().end() ;
          ++controlerset)
      {
        (*controlerset)->setTimeStep(seconds) ;
      }
    }

    void Model::initObserver(Observer* observer)
    {
      addOperation(Implementation::Operation::init(observer)) ;
    }

    void Model::closeObserver(Observer* observer)
    {
      addOperation(Implementation::Operation::close(observer)) ;
    }

    void Model::updateObserver(Observer* observer)
    {
      addOperation(Implementation::Operation::update(observer)) ;
    }

    void Model::changeParentObserver(Observer*,Object*)
    {

    }

  }
}


