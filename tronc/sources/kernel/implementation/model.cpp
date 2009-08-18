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
#include <typeinfo>
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
#include <kernel/base_relation_view.h>
#include <kernel/base_relation_controler.h>
#include <kernel/model.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

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

      removeRelations(object) ;

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

      // there is no change !
      if (old_parent == new_parent)
      {
        return ;
      }

      startTransaction() ;

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

      endTransaction() ;
    }

    Trait* Model::addTrait(Object* object,
                           Trait* new_trait)
    {
      Log::Block temp("Structure","addTrait") ;

      if (object->m_deleting)
      {
        delete new_trait ;
        return NULL ;
      }

      bool deduced = ! new_trait->isPrimitive() ;

      startTransaction() ;
      object->_add(new_trait) ;
      endTransaction() ;

      if (deduced)
        m_statistics.addDeducedTrait() ;
      else
        m_statistics.addPrimitiveTrait() ;

      return new_trait ;
    }

    void Model::destroyTrait(Object* object,
                            Trait* trait)
    {
      std::string trait_name(getObjectTypeIdentifier(trait).fullName()) ;

      Log::Block temp("Structure","destroyTrait" + trait_name) ;

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
      InternalMessage("Kernel",Kernel::toString(m_controler_sets.size())) ;
      m_destroying = true ;

      /// 1. close all controller sets
      for(std::set<ControlerSet*>::iterator controler_set = m_controler_sets.begin() ;
          controler_set != m_controler_sets.end() ;
          ++controler_set)
      {
        (*controler_set)->close() ;
      }

      /// 1. close all view points
      for(std::set<ViewPoint*>::iterator viewpoint = m_viewpoints.begin() ;
          viewpoint != m_viewpoints.end() ;
          ++viewpoint)
      {
        (*viewpoint)->close() ;
      }

      m_relations.clear() ;

      for(std::set<ObjectReference*>::iterator reference = m_references.begin() ;
          reference != m_references.end() ;
          ++reference)
      {
        (*reference)->_setModel(NULL) ;
      }

      /// 2. destroy m_objects
      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        delete *object ;
      }
      for(std::set<ControlerSet*>::iterator controler_set = m_controler_sets.begin() ;
          controler_set != m_controler_sets.end() ;
          ++controler_set)
      {
        delete (*controler_set) ;
      }

      /// 1. close all view points
      for(std::set<ViewPoint*>::iterator viewpoint = m_viewpoints.begin() ;
          viewpoint != m_viewpoints.end() ;
          ++viewpoint)
      {
        delete *viewpoint ;
      }

      // delete view and controlers on relations
      for(std::map<Relation,std::set<BaseRelationView*> >::iterator relation = m_relation_views.begin() ; relation != m_relation_views.end() ; ++ relation)
      {
        for(std::set<BaseRelationView*>::iterator view = relation->second.begin() ; view != relation->second.end() ; ++view)
        {
          delete *view ;
        }
      }

      for(std::map<Relation,std::set<BaseRelationControler*> >::iterator relation = m_relation_controlers.begin() ; relation != m_relation_controlers.end() ; ++ relation)
      {
        for(std::set<BaseRelationControler*>::iterator controller = relation->second.begin() ; controller != relation->second.end() ; ++controller)
        {
          delete *controller ;
        }
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
      startTransaction() ;

      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_close(viewpoint) ;
      }

      for(std::map<Relation,std::set<BaseRelationView*> >::iterator relation_view = m_relation_views.begin() ; relation_view != m_relation_views.end() ; ++relation_view)
      {
        for(std::set<BaseRelationView*>::iterator view = relation_view->second.begin() ; view != relation_view->second.end() ; ++view)
        {
          if ((*view)->m_viewpoint == viewpoint)
          {
            (*view)->realClose() ;
          }
        }
      }

      endTransaction() ;
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
      startTransaction() ;

      for(std::map<Relation,std::set<BaseRelationControler*> >::iterator relation_controler = m_relation_controlers.begin() ; relation_controler != m_relation_controlers.end() ; ++relation_controler)
      {
        for(std::set<BaseRelationControler*>::iterator controler = relation_controler->second.begin() ; controler != relation_controler->second.end() ; ++controler)
        {
          if ((*controler)->m_controler_set == controler_set)
          {
            (*controler)->close() ;
          }
        }
      }

      for(std::set<Object*>::iterator object = m_objects.begin() ;
          object != m_objects.end() ;
          ++object)
      {
        (*object)->_close(controler_set) ;
      }

      endTransaction() ;
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

    void Model::addManualView(Trait* trait,BaseTraitView* view,ViewPoint* viewpoint)
    {
      view->setObserved(trait) ;
      view->setViewPoint(viewpoint) ;
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

      for(std::set<Relation>::iterator relation = m_relations.begin() ; relation != m_relations.end() ; ++relation)
      {
        close(*relation) ;
      }
    }

    void Model::update(const float& seconds)
    {
      // first update controller sets then viewpoints
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

    void Model::changeParentObserver(Observer* observer,Object* old_parent)
    {
      addOperation(Implementation::Operation::changeParent(observer,old_parent)) ;
    }

    void Model::initObserver(RelationObserver* observer)
    {
      addOperation(Implementation::Operation::init(observer)) ;
    }

    void Model::closeObserver(RelationObserver* observer)
    {
      addOperation(Implementation::Operation::close(observer)) ;
    }

    void Model::updateObserver(RelationObserver* observer)
    {
      addOperation(Implementation::Operation::update(observer)) ;
    }

    Relation* Model::getCanonical(const Relation& relation)
    {
      return &(m_canonical_relations.find(relation)->second) ;
    }

    void Model::addRelation(const Relation& relation)
    {
      startTransaction() ;

      if (m_pair_reference_counting.find(relation) == m_pair_reference_counting.end())
        m_pair_reference_counting[relation] = 0 ;

      ++m_pair_reference_counting[relation] ;

      m_relations.insert(relation) ;

      /*
       handle the case where during a transaction we add, remove and re-add the
       the same relation @see TestRelationView::severalInitCloseInTheSameFrame
      */
      if (isToDestroy(relation))
      {
        unRecordRelationToDestroy(relation) ;
      }
      else
      {
        m_canonical_relations.insert(std::make_pair(relation,relation)) ;
        m_relation_validities.insert(std::make_pair(relation,std::vector<bool>(Formula::getNumberOfFormulae(),false))) ;
        m_number_of_true_child_formulae.insert(std::make_pair(relation,std::vector<short>(Formula::getNumberOfFormulae(),0))) ;
        relation.createViews() ;
        relation.createControlers() ;
      }
      init(relation) ;
      DeducedTrait::addRelation(relation) ;
      endTransaction() ;
    }

    void Model::removeRelation(const Relation& relation)
    {
      startTransaction() ;

      close(relation) ;
      DeducedTrait::removeRelation(relation) ;
      m_relations.erase(relation) ;
      recordRelationToDestroy(relation) ;

      endTransaction() ;
    }

    void Model::_internalDestroyRelation(const Relation& relation)
    {
      m_canonical_relations.erase(relation) ;

      int& counting = m_pair_reference_counting[relation] ;
      --counting ;

      if (counting == 0)
      {
        m_relation_validities.erase(relation) ;
        m_number_of_true_child_formulae.erase(relation) ;
      }
      destroyRelationView(relation) ;
      destroyRelationControler(relation) ;
    }

    void Model::removeRelations(Object* object)
    {
      std::list<Relation> to_remove ;

      for(std::set<Relation>::const_iterator relation = m_relations.begin() ; relation != m_relations.end() ; ++relation)
      {
        if (relation->getObjectFrom() == object || relation->getObjectTo() == object)
          to_remove.push_back(*relation) ;
      }

      for(std::list<Relation>::const_iterator relation = to_remove.begin() ; relation != to_remove.end() ; ++relation)
      {
        removeRelation(*relation) ;
      }
    }

    std::set<Object*> Model::getRelations(const TypeIdentifier& type,Object* object) const
    {
      std::set<Object*> result ;
      /*
        @todo we could use the < on relation by finding all the elements between Relation(type,object,-1) and Relation(type,object,+inf)
      */
      for(std::set<Relation>::const_iterator relation = m_relations.begin() ; relation != m_relations.end() ; ++relation)
      {
        if (relation->getType() == type && relation->getObjectFrom() == object)
          result.insert(relation->getObjectTo()) ;
      }

      return result ;
    }

    std::set<Object*> Model::getRelations(Object* object) const
    {
      std::set<Object*> result ;
      for(std::set<Relation>::const_iterator relation = m_relations.begin() ; relation != m_relations.end() ; ++relation)
      {
        if (relation->getObjectFrom() == object)
          result.insert(relation->getObjectTo()) ;
      }

      return result ;
    }

    std::set<Object*> Model::getInverseRelations(const TypeIdentifier& type,Object* object) const
    {
      std::set<Object*> result ;
      for(std::set<Relation>::const_iterator relation = m_relations.begin() ; relation != m_relations.end() ; ++relation)
      {
        if (relation->getType() == type && relation->getObjectTo() == object)
          result.insert(relation->getObjectFrom()) ;
      }

      return result ;
    }

    std::set<Object*> Model::getInverseRelations(Object* object) const
    {
      std::set<Object*> result ;
      for(std::set<Relation>::const_iterator relation = m_relations.begin() ; relation != m_relations.end() ; ++relation)
      {
        if (relation->getObjectTo() == object)
          result.insert(relation->getObjectFrom()) ;
      }

      return result ;
    }

    bool Model::getValidity(const ObjectPair& relation,const Formula* formula)
    {
      if (formula->getIdentifier() > (int)m_relation_validities[relation].capacity() ||
          formula->getIdentifier() < 0)
      {
        throw ExceptionKernel("Model::getValidity " + formula->print()) ;
      }

      return m_relation_validities[relation][formula->getIdentifier()] ;
    }

    void Model::setValidity(const ObjectPair& relation,const Formula* formula,const bool& validity)
    {
      if (formula->getIdentifier() > (int)m_relation_validities[relation].capacity() ||
          formula->getIdentifier() < 0)
      {
        throw ExceptionKernel("Model::setValidity " + formula->print() + " identifier=" +
                              Kernel::toString(formula->getIdentifier()) + " capacity=" +
                              Kernel::toString(m_relation_validities[relation].capacity())) ;
      }
      m_relation_validities[relation][formula->getIdentifier()] = validity ;
    }

    short Model::getNumberOfTrueChildFormulae(const ObjectPair& relation,
                                              const Formula* formula)
    {
      if (formula->getIdentifier() > (int)m_number_of_true_child_formulae[relation].capacity() ||
          formula->getIdentifier() < 0)
      {
        throw ExceptionKernel("Model::getNumberOfTrueChildFormulae") ;
      }
      return m_number_of_true_child_formulae[relation][formula->getIdentifier()] ;
    }

    void Model::setNumberOfTrueChildFormulae(const ObjectPair& relation,
                                             const Formula* formula,
                                             short number)
    {
      if (formula->getIdentifier() > (int)m_number_of_true_child_formulae[relation].capacity() ||
          formula->getIdentifier() < 0)
      {
        throw ExceptionKernel("Model::setNumberOfTrueChildFormulae") ;
      }
      m_number_of_true_child_formulae[relation][formula->getIdentifier()] = number ;
    }

    void Model::addRelationView(const Relation& relation,BaseRelationView* view,ViewPoint* viewpoint)
    {
      m_relation_views[relation].insert(view) ;
      view->_setRelation(relation) ;
      view->_setViewPoint(viewpoint) ;
    }

    void Model::destroyRelationView(const Relation& relation)
    {
      for(std::set<BaseRelationView*>::iterator view = m_relation_views[relation].begin() ; view != m_relation_views[relation].end() ; ++view)
      {
        delete *view ;
      }
      m_relation_views.erase(relation) ;
    }

    void Model::addRelationControler(const Relation& relation,
                                     BaseRelationControler* controler,
                                     ControlerSet* controler_set)
    {
      m_relation_controlers[relation].insert(controler) ;
      controler->_setRelation(relation) ;
      controler->_setControlerSet(controler_set) ;
    }

    void Model::destroyRelationControler(const Relation& relation)
    {
      for(std::set<BaseRelationControler*>::iterator controler = m_relation_controlers[relation].begin() ; controler != m_relation_controlers[relation].end() ; ++controler)
      {
        delete *controler ;
      }
      m_relation_controlers.erase(relation) ;
    }

    void Model::init(const Relation& relation)
    {
      for(std::set<BaseRelationView*>::iterator view = m_relation_views[relation].begin() ; view != m_relation_views[relation].end() ; ++view)
      {
        (*view)->init() ;
      }
      for(std::set<BaseRelationControler*>::iterator controler = m_relation_controlers[relation].begin() ; controler != m_relation_controlers[relation].end() ; ++controler)
      {
        (*controler)->init() ;
      }
    }

    void Model::close(const Relation& relation)
    {
      for(std::set<BaseRelationView*>::iterator view = m_relation_views[relation].begin() ; view != m_relation_views[relation].end() ; ++view)
      {
        (*view)->close() ;
      }
      for(std::set<BaseRelationControler*>::iterator controler = m_relation_controlers[relation].begin() ; controler != m_relation_controlers[relation].end() ; ++controler)
      {
        (*controler)->close() ;
      }
    }

    void Model::update(const Relation& relation)
    {
      for(std::set<BaseRelationView*>::iterator view = m_relation_views[relation].begin() ; view != m_relation_views[relation].end() ; ++view)
      {
        (*view)->update() ;
      }
      for(std::set<BaseRelationControler*>::iterator controler = m_relation_controlers[relation].begin() ; controler != m_relation_controlers[relation].end() ; ++controler)
      {
        (*controler)->update() ;
      }
    }
  }
}


