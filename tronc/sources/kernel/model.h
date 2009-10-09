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
#pragma once

#include <boost/function.hpp>
#include <set>
#include <map>
#include <string>

#include <kernel/implementation/interpretor.h>
#include <kernel/object.h>
#include <kernel/relation.h>
#include <kernel/statistics.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {
      class Operation ;
      template <class Relation> class GetLink ;
    }

    class ObjectPair ;
    class Observer ;
    class RelationObserver ;
    class ViewPoint ;
    class Trait ;
    class ControlerSet ;
    class ObjectReference ;
    class BaseTraitView ;
    class Reader ;
    class WithRelationFormula ;
    class IsRelatedFormula ;
    class IsOnlyRelatedFormula ;
    class DeducedRelation ;

    /// A set of Objects.
    class Model : public Implementation::Interpretor
    {
    public:

      /// Builds a new model.
      Model(const std::string& name = "") ;

      /// Destroy all objects, views and controlers.
      ~Model() ;

      /// Creates a new Object.
      Object* createObject() ;

      /// Destroy a given Object.
      void destroyObject(Object* object) ;

      /// Manually add a view.
      void addManualView(Trait*,BaseTraitView*,ViewPoint*) ;

      /// Build all registered viewpoints and controler sets.
      void init() ;

      /// Closes all registered viewpoints and controler sets.
      void close() ;

      /// Update the model during @c seconds
      void update(const float& seconds) ;

      /// Globally set the time step of simulation.
      void setTimeStep(const float& seconds) ;

      /// Add a viewpoint.
      ViewPoint* addViewPoint(ViewPoint*) ;

      /// Add a controler set.
      ControlerSet* addControlerSet(ControlerSet*) ;

      /// Get an object by identifier.
      Object* getObject(const int& identifier) const ;

      /// Access to root objects.
      const std::set<Object*>& getRoots() const ;
      /// return a controler set of type @c T.
      template <class T> T* getControlerSet() const ;

      /// return a viewpoint of type @c T.
      template <class T> T* getViewPoint() const ;

      /// Reset the recorded performance statistics.
      void resetStatistics() ;

      /// Prints statistics to log.
      void printStatistics() const ;

      const Statistics& getStatistics() const ;

      /// Returns a dot language representation of the model.
      std::string toGraphviz() const ;

      /// Returns a dot language representation of the model relative to @c controller_set.
      std::string toGraphviz(ControlerSet* controller_set) const ;

      /// Returns a dot language representation of the model relative to @c viewpoint.
      std::string toGraphviz(ViewPoint* viewpoint) const ;

    private:

      /// Creates a new Object with given parent.
      Object* createObject(Object* parent) ;

      /// Changes parent of a given Object.
      void changeParent(Object* object,Object* new_parent) ;

      /// Adds a new trait to an Object.
      Trait* addTrait(Object* object,Trait* new_trait) ;

      /// Destroy an Object's trait.
      void destroyTrait(Object* object,Trait* trait) ;

      /// Access to viewpoints.
      const std::set<ViewPoint*>& getViewPoints() const ;

      /// Access to controler sets.
      const std::set<ControlerSet*>& getControlerSets() const ;

      std::string                   m_name ;

      /// root objects @composite
      std::set<Object*>             m_objects ;

      /// Remove the mapping between an identifier and an object.
      /*!
        Used during object destruction.
      */
      void _removeObjectIdentifier(const int& identifier) ;

      /// Identify objects.
      std::map<int,Object*>         m_objects_by_identifier ;

      /// Register a view point.
      void _register(ViewPoint* viewpoint) ;

      /// Unregister a view point.
      void _unregister(ViewPoint* viewpoint) ;

      /// Register a controler set.
      void _register(ControlerSet* controler_set) ;

      /// Unregister a controler set.
      void _unregister(ControlerSet* controler_set) ;

      /// Init objects according to a viewpoint
      void _init(ViewPoint* viewpoint) ;

      /// Close objects according to a viewpoint
      void _close(ViewPoint* viewpoint) ;

      /// Init objects according to a controler set
      void _init(ControlerSet* controler_set) ;

      /// Close objects according to a controler set
      void _close(ControlerSet* controler_set) ;

      std::set<ViewPoint*>        m_viewpoints ;
      std::set<ControlerSet*>     m_controler_sets ;

      Statistics m_statistics ;

    // @}
    /*!
      @name Back reference handling

      Reference to object need to be "cleared" when model is destroyed.
    */
    // @{

      void _registerReference(ObjectReference*) ;

      void _unregisterReference(ObjectReference*) ;

      std::set<ObjectReference*>  m_references ;

    // @}
    /*!
      @name Handling of modifications during controlers update

      When a controler set is updated, the structure should not be modified
    */
    // @{

      /// True iff we are in a simulation
      bool m_is_simulating_controler_set ;

      void beginSimulation() ;
      void endSimulation() ;

      void initObserver(Observer*) ;
      void closeObserver(Observer*) ;
      void updateObserver(Observer*) ;
      void changeParentObserver(Observer*,Object*) ;

      void initObserver(RelationObserver*) ;
      void closeObserver(RelationObserver*) ;
      void updateObserver(RelationObserver*) ;

    // @}
    /*!
      @name Relation handling
    */
    // @{

      /// Return the 'canonical' element of a relation.
      Relation* getCanonical(const Relation&) ;

      std::map<Relation,Relation> m_canonical_relations ;

      /// All the links
      std::set<Relation> m_relations ;

      /// Functional operations
      void addRelation(const Relation&) ;
      void removeRelation(const Relation&) ;

      /// Really destroy a relation.
      void _internalDestroyRelation(const Relation&) ;

      /// The objects related to an object though a particular relation type.
      std::set<Object*> getRelations(const TypeIdentifier&,Object*) const ;

      /// The objects related to an object though any relation type.
      std::set<Object*> getRelations(Object*) const ;

      /// The objects related to an object though a particular relation type.
      std::set<Object*> getInverseRelations(const TypeIdentifier&,Object*) const ;

      /// The objects related to an object though any relation type.
      std::set<Object*> getInverseRelations(Object*) const ;

      /// Remove all relation involving the object.
      void removeRelations(Object*) ;

      /// Reference counting on pairs
      std::map<ObjectPair,int> m_pair_reference_counting ;

      bool getValidity(const ObjectPair& relation,const Formula* formula) ;
      void setValidity(const ObjectPair& relation,const Formula* formula,const bool&) ;

      std::map<ObjectPair,std::vector<bool> > m_relation_validities ;

      /// Access to the number of true child formulae for @c this
      short getNumberOfTrueChildFormulae(const ObjectPair& relation,const Formula* formula) ;

      /// Change the number of true child formulae for @c this
      void setNumberOfTrueChildFormulae(const ObjectPair& relation,
                                        const Formula* formula,
                                        short number) ;

      std::map<ObjectPair,std::vector<short> > m_number_of_true_child_formulae ;

      /// Storage for relation views.
      std::map<Relation,std::set<BaseRelationView*> > m_relation_views ;

      /// Add a relation view
      void addRelationView(const Relation&,BaseRelationView*,ViewPoint*) ;

      /// Destroy the relation's views
      void destroyRelationView(const Relation&) ;

      bool hasObserver(const Relation&) ;

      /// Storage for relation controlers.
      std::map<Relation,std::set<BaseRelationControler*> > m_relation_controlers ;

      /// Get a relation view.
      template <class _View> _View* getView(const Relation&) const ;

      /// Add a relation controler.
      void addRelationControler(const Relation&,BaseRelationControler*,ControlerSet*) ;

      /// Destroy the relation's controlers
      void destroyRelationControler(const Relation&) ;

      /// Initialize the observers of the relation
      void init(const Relation&) ;

      /// Terminate the observers of the relation
      void close(const Relation&) ;

      /// Update the observers of the relation
      void update(const Relation&) ;

    // @}

      std::string beginGraphviz() const ;
      std::string printGraphvizRank() const ;

      /// The next identifier to assign
      int m_next_identifier ;

      friend class ViewPoint ;
      friend class Trait ;
      friend class Object ;
      friend class ControlerSet ;
      friend class Reader ;
      friend class Observer ;
      friend class RelationObserver ;
      friend class Relation ;
      friend class ObjectPair ;
      friend class ::ProjetUnivers::Kernel::Implementation::Interpretor ;
      template <class Relation> friend class Link ;
      template <class Relation> friend class UnLink ;
      template <class Relation> friend class ::ProjetUnivers::Kernel::Implementation::GetLink ;
      friend class IsRelatedFormula ;
      friend class IsOnlyRelatedFormula ;
      friend class WithRelationFormula ;
      friend class DeducedRelation ;

      template <class _View>
      friend void forAll(ViewPoint*                    viewpoint,
                         boost::function1<void,_View*> operation) ;

      friend class ObjectReference ;
      friend class ::ProjetUnivers::Kernel::Implementation::Operation ;
    };

  }
}

#include <kernel/implementation/model.cxx>

