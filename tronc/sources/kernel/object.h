/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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

#include <list>
#include <set>
#include <map>
#include <vector>
#include <typeinfo>

#include <kernel/meta.h>
#include <kernel/exception_kernel.h>
#include <kernel/error.h>
#include <kernel/string.h>
#include <kernel/log.h>
#include <kernel/inherits.h>
#include <kernel/object_reference.h>
#include <kernel/trait.h>
#include <kernel/implementation/number.h>


namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {
      class Operation ;
      class Interpretor ;
    }
    namespace Test
    {
      class TestModelView ;
      class TestTrait ;
    }
    class Trait ;
    class Model ;
    class ViewPoint ;
    class ControlerSet ;
    class Formula ;
    class FormulaAnd ;
    class FormulaOr ;
    class TraitFormula ;
    class FormulaNot ;
    class Reader ;
    class CommandDelegator ;
    class HasParentFormula ;
    class HasAncestorFormula ;
    class HasChildFormula ;
    class Reader ;
    class Writer ;
    class BaseTraitView ;
    class BaseControler ;
    class IsRelatedFormula ;
    class IsOnlyRelatedFormula ;
    class WithRelationFormula ;

    /// A model object.
    /*!
      An object has traits and eventually sub-objects. When an object is
      destroyed, his traits and sub objects are also destroyed.

      Trait can be added. Only one trait having class T can be added on
      the same object.
    */
    class Object
    {
    public:

    /*!
      @name Construction
    */
    //@{

      /// Creates a child Object.
      Object* createObject() ;

      /// Destroy this object.
      void destroyObject() ;

      /// Changes parent of this object.
      void changeParent(Object* new_parent) ;

      /// Adds a new trait to object.
      /*!
        @return the trait added
      */
      Trait* addTrait(Trait* trait) ;

      /// Destroy an object's trait.
      void destroyTrait(Trait* trait) ;

      /// Set the object name (optional).
      void setName(const std::string& name) ;

    //@}
    /*!
      @name Access methods
    */
    //@{

      /// Access to an object by name.
      static Object* get(const std::string& name) ;

      /// Get object's identifier.
      int getIdentifier() const ;

      // Access to parent.
      Object* getParent() const ;

      /// Get top most ancestor.
      const Object* getRoot() const ;

      /// A common ancestor iff exists.
      const Object* getCommonAncestor(const Object*) const ;

      /// True iff @c this is ancestor of @c object
      bool isAncestor(const Object* object) const ;

      /// Access to model.
      Model* getModel() const ;

      /// Access to trait of type T if exists.
      template <class T> T* getTrait() const ;

      /// Retrieve the trait named @c trait_name.
      Trait* getPrimitiveTrait(const TypeIdentifier& trait_name) const ;

      /// Access to trait's view of type _View if exists.
      /*!
        @remark
          It may exist several @c _View on that object (mainly because
          the view may be attached to a base trait whose several sub traits are
          attached to this object) : in that case, it returns one of the view
          in an unspecified manner.
          Note that in that case one can obtain exactly the desired view through
          Trait::getView after choosing the correct trait.
      */
      template <class _View> _View* getView(ViewPoint* i_viewpoint) ;

      /// Top most ancestor with T trait.
      template <class T> T* getRoot() const ;

      /// First ancestor (including @c this) with trait T.
      template <class T> T* getParent() const ;

      /// First ancestor (excluding @c this) with trait T.
      template <class T> T* getAncestor() const ;

      /// First ancestor (including @c this) with trait T and not up to @c i_object.
      /*!
        @returns NULL
          if no object has T trait between this and @c i_object
          or @c i_object is not ancestor of this.
      */
      template <class T> T* getParentUpTo(const Object* i_object) const ;

      /// Get all the descendant (excluding @c this) with trait T.
      template <class T> std::set<T*> getDescendants() const ;

      /// Get all the descendant (including @c this) with trait T.
      template <class T> std::set<T*> getChildren() const ;

      /// Get all the descendant (including @c this) with trait T.
      template <class T> std::set<Object*> getChildrenObjects() const ;

      /// Get the descendant (including @c this) with trait T.
      /*!
        Return NULL iff severals.
      */
      template <class T> T* getChild() const ;

      /// Call a void command.
      /*!
        Try first on object traits then on sub-objects...??
        @return true iff succeeded.
      */
      bool call(const std::string& i_command) ;

      /// Call an int command.
      /*!
        @return true iff succeeded.
      */
      bool call(const std::string& i_command, const int&) ;

      /// Call a function on object.
      /*!
        @exception boost::bad_any_cast
                   function exists but ReturnType cast is incorrect

        @exception std::exception
                   function does not exist
      */
      template <typename ReturnType>
      ReturnType callFunction(const std::string& function_name) const
      throw (boost::bad_any_cast,std::exception) ;

      /// Access to all commands understood be the object.
      std::set<std::string> getCommands() const ;

      /// Access to all children.
      const std::set<Object*>& getChildren() const ;

      /// True when object is deleting.
      bool isDeleting() const ;

    //@}
    /*!
      @name Apply methods
    */
    //@{

      /// Apply @c i_operation on all _View.
      /*!
        @deprecated
      */
      template <class _View>
      void apply(const TypeIdentifier& i_trait_name,
                 ViewPoint* i_viewpoint,
                 boost::function1<void,_View*> i_operation) ;

      /// Apply @c i_operation on all controllers of @c i_controler_set.
      void applyTopDown
                (ControlerSet*                         i_controler_set,
                 boost::function1<void,BaseControler*> i_operation) ;

      /// Apply @c i_operation on all controllers of @c i_controler_set.
      void applyBottomUp
                (ControlerSet*                         i_controler_set,
                 boost::function1<void,BaseControler*> i_operation) ;

    //@}

      /// Returns a dot language representation of the object.
      std::string toGraphviz() const ;

      /// Returns a dot language representation of the model relative to @c controller_set.
      std::string toGraphviz(ControlerSet* controller_set) const ;

      /// Returns a dot language representation of the model relative to @c viewpoint.
      std::string toGraphviz(ViewPoint* viewpoint) const ;

    private:

      /// Constructor.
      Object(Model* i_model) ;

      /// Destroy the objects and the traits.
      ~Object() ;

      /// Returns the name of the object.
      std::string graphvizName() const ;

      /// Build the graphviz object ranks.
      void buildGraphvizRanks(const int& current_rank,std::map<int,std::string>& ranks) const ;

      /// Returns a dot language representation of the object.
      std::string toGraphviz(boost::function1<bool,Trait*> trait_condition) const ;

    /*!
      @name Internal construction

      @see Model for public construction methods.
    */
    //@{

      /// Add a sub-object
      Object* _add(Object* i_child) ;

      /// Remove a sub-object.
      void _remove(Object* i_child) ;

      /// Detach and close a sub-object.
      Object* _release(Object* i_child) ;

      /// Detach a sub-object.
      Object* _detach(Object* i_child) ;

      /// Attach a sub-object.
      Object* _attach(Object* i_child) ;

      /// Add a trait.
      void _addPrimitiveTrait(Trait* trait) ;
      void _addDeducedTrait(DeducedTrait* trait) ;
      /// Remove a trait.
      void _removePrimitiveTrait(Trait* trait) ;
      /// Remove a trait by trait name.
      void _removeDeducedTrait(const TypeIdentifier& trait_name) ;

      /// Detach a trait.
      void _detach(Trait* trait) ;

      /// Retrieve the trait named @c trait_name.
      DeducedTrait* _getDeducedTrait(const TypeIdentifier& trait_name) const ;

      /// update the views for a change_parent.
      void _changed_parent(Object* i_old_parent) ;

      /// update the views.
      void _updated() ;

      /// True iff we can initialize views, controllers.
      bool mayInit() const ;

      /// Initialize after construction.
      void _init() ;

      /// Initialize the views after construction.
      void _init(ViewPoint* i_viewpoint) ;

      /// Initialize the controllers after construction.
      void _init(ControlerSet* i_controler_set) ;

      /// closes before destruction.
      void _close() ;

      /// close the views before viewpoint closing.
      void _close(ViewPoint* i_viewpoint) ;

      /// close the controllers before controller set closing.
      void _close(ControlerSet* i_controler_set) ;

      /// Recursively create views for a viewpoint.
      void _create_views(ViewPoint* i_viewpoint) ;

      /// Recursively create controllers for a controller set.
      void _create_controlers(ControlerSet* i_controler_set) ;

      /// Internal call a void command.
      /*!
        @return true iff succeeded.
      */
      bool _call(const std::string& i_command) ;

      /// Internal call an int command.
      /*!
        @return true iff succeeded.
      */
      bool _call(const std::string& i_command, const int&) ;

      /// Internal access to all commands understood be the object.
      std::set<std::string> _getCommands() const ;

    /*!
      @name Deduction access
    */
    //@{


      /// Access to the validity of a formula for @c this
      bool getValidity(const Formula* i_formula) const ;

      /// Change the validity of a formula for @c this
      void setValidity(const Formula* i_formula,bool i_validity) ;

      /// Access to the number of true child formulae for @c this
      Implementation::Number getNumberOfTrueChildFormulae(const Formula* i_formula) const ;

      /// Change the number of true child formulae for @c this
      void setNumberOfTrueChildFormulae(const Formula* i_formula,
                                        Implementation::Number i_number) ;

      /// Access to a trait by name.
      Trait* getTrait(const TypeIdentifier&) const ;
      std::set<Trait*> getDirectChildren(const TypeIdentifier&) const ;
      std::set<Trait*> getDirectDescendants(const TypeIdentifier&) const ;
      Trait* getParent(const TypeIdentifier&) const ;
      Trait* getAncestor(const TypeIdentifier&) const ;

      /// Access to number of parents with trait @c name.
      unsigned int getNumberOfParent(const TypeIdentifier& name) const ;

      /// Access to number of ancestors with trait @c name.
      unsigned int getNumberOfAncestor(const TypeIdentifier& name) const ;

      /// Access to number of children with trait @c name.
      unsigned int getNumberOfChildren(const TypeIdentifier& name) const ;

      /// Access to number of children with c formula.
      unsigned int getNumberOfChildren(const Formula* formula) const ;

      /// Access to number of parents with @c formula.
      unsigned int getNumberOfParent(const Formula* formula) const ;

      /// Access to number of ancestors with @c formula.
      unsigned int getNumberOfAncestor(const Formula* formula) const ;

    // @}

      /// Returns the path from root to this.
      std::list<Object*> getAncestorPath() const ;


    /*!
      @name attributes
    */
    // @{

      /// Is the current object is deleting
      bool                             m_deleting ;

      /// Unique identifier.
      int                              m_identifier ;

      /// internal access.
      std::set<Trait*>& _getTraits() ;
      const std::set<Trait*>& _getTraits() const ;

      /// @composite
      std::set<Trait*> m_traits ;

      /// Access speed
      std::map<TypeIdentifier,Trait*>        m_primitive_traits ;
      std::map<TypeIdentifier,DeducedTrait*> m_deduced_traits ;

      Object*                          m_parent ;
      /// @composite
      std::set<Object*>                children ;

      /// Model of the object.
      Model*                           m_model ;

      /// Validities for each formula
      std::vector<bool>                m_validities ;

      /// Number of true child formulae indexed by formulae.
      std::vector<Implementation::Number>      m_number_of_true_child_formulae ;

      /// Object name
      std::string                      m_name ;

      std::set<Trait*> lockTraits() ;
      void unlockTraits(const std::set<Trait*>&) ;

      void addLock() ;
      void removeLock() ;
      bool isLocked() const ;
      int m_locks ;

      /// Record the objects on which we have already try calling a function
      /*!
        Avoid infinite loops when the structure of CommandDelegator contains a
        cycle.
      */
      static std::set<const Kernel::Object*> m_already_called_objects ;

      /// Objects with a name.
      static std::map<std::string,ObjectReference> m_named_objects ;

      static void startReading() ;
      static void stopReading() ;

      /// True when we are in a Reader::read call.
      static bool m_is_reading ;

    // @}

      friend class Trait ;
      friend class Model ;
      friend class Formula ;
      friend class FormulaAnd ;
      friend class FormulaOr ;
      friend class FormulaNot ;
      friend class TraitFormula ;
      friend class HasParentFormula ;
      friend class HasAncestorFormula ;
      friend class HasChildFormula ;
      friend class DeducedTrait ;
      friend class CommandDelegator ;
      friend class Reader ;
      friend class Writer ;
      friend class ::ProjetUnivers::Kernel::Implementation::Operation ;
      friend class ::ProjetUnivers::Kernel::Implementation::Interpretor ;
      friend class ::ProjetUnivers::Kernel::Test::TestModelView ;
      friend class ::ProjetUnivers::Kernel::Test::TestTrait ;
      friend class BaseTraitView ;
      friend class BaseControler ;
      friend class IsRelatedFormula ;
      friend class IsOnlyRelatedFormula ;
      friend class WithRelationFormula ;
    };
  }
}

#include <kernel/implementation/object.cxx>
