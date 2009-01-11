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
#ifndef PU_KERNEL_OBJECT_H_
#define PU_KERNEL_OBJECT_H_

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


namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Implementation
    {
      class Operation ;
      class Interpretor ;
      class Transaction ;
      class ConcurrentBlock ;
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
    class HasChildFormula ;
    class Reader ;
    
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
      void addTrait(Trait* trait) ;
  
      /// Destroy an object's trait.
      void destroyTrait(Trait* trait) ;
      
      /// Set the object name (optionnal).
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
      
      /// Acces to model.
      Model* getModel() const ;

      /// Access to trait of type T if exists.
      template <class T> T* getTrait() const ;

      /// Access to trait's view of type _View if exists.
      /*!
        @remark 
          It may exist several @c _View on that object (mainly because 
          the view may be attached to a base trait whose several subtraits are
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
      
      /// Call a void command.
      /*!
        Try first on object traits then on sub-objects...??
        @return true iff succedeed.
      */
      bool call(const std::string& i_command) ;

      /// Call an int command.
      /*!
        @return true iff succedeed.
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

      /// Apply @c i_operation on all controlers of @c i_controler_set.
      void applyTopDown
                (ControlerSet*                         i_controler_set,
                 boost::function1<void,BaseControler*> i_operation) ;

      /// Apply @c i_operation on all controlers of @c i_controler_set.
      void applyBottomUp
                (ControlerSet*                         i_controler_set,
                 boost::function1<void,BaseControler*> i_operation) ;

    //@}

    private:

      /// Constructor.
      Object(Model* i_model) ;

      /// Destructs the objects and the traits.
      ~Object() ;
      
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
      void _add(Trait* i_trait) ;

      /// Remove a trait.
      void _remove(Trait* i_trait) ;

      /// Remove a trait by trait name.
      void _remove(const TypeIdentifier& i_trait_name) ;

      /// Detach a trait.
      Object* _detach(const TypeIdentifier& trait_name) ;
      
      /// Retreive the trait named @c i_trait_name.
      Trait* _get(const TypeIdentifier& i_trait_name) const ;

      /// update the views for a change_parent. 
      void _changed_parent(Object* i_old_parent) ;
      
      /// update the views.
      void _updated() ;

      /// True iff we can init views, controlers.
      bool mayInit() const ;
      
      /// init after construction.
      void _init() ;

      /// init the views after construction.
      void _init(ViewPoint* i_viewpoint) ;

      /// init the controlers after construction.
      void _init(ControlerSet* i_controler_set) ;

      /// closes before destruction.
      void _close() ;

      /// close the views before viewpoint closing.
      void _close(ViewPoint* i_viewpoint) ;

      /// close the controlers before controler set closing.
      void _close(ControlerSet* i_controler_set) ;

      /// recursivelly create views for a viewpoint.
      void _create_views(ViewPoint* i_viewpoint) ;

      /// recursivelly create controlers for a controler set.
      void _create_controlers(ControlerSet* i_controler_set) ;

      /// Internal call a void command.
      /*!
        @return true iff succedeed.
      */
      bool _call(const std::string& i_command) ;

      /// Internal call an int command.
      /*!
        @return true iff succedeed.
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
      unsigned short getNumberOfTrueChildFormulae(const Formula* i_formula) const ;
      
      /// Change the number of true child formulae for @c this
      void setNumberOfTrueChildFormulae(const Formula* i_formula,
                                        unsigned short i_number) ;

      /// Access to a trait by name.
      Trait* getTrait(const TypeIdentifier&) const ;

      /// Access to number of parents with trait @c name.
      unsigned int getNumberOfParent(const TypeIdentifier& name) const ;

      /// Access to number of children with trait @c name.
      unsigned int getNumberOfChildren(const TypeIdentifier& name) const ;
      
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
      
      /// @composite
      std::map<TypeIdentifier, Trait*> traits ;
      Object*                          m_parent ;
      /// @composite
      std::set<Object*>                children ;
      
      /// Model of the object.
      Model*                           m_model ;
      
      /// Validities for each formula
      std::vector<bool>                m_validities ;

      /// Number of true chid formulae indexed by formulae.       
      std::vector<unsigned short>      m_number_of_true_child_formulae ;

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
      friend class HasChildFormula ;
      friend class DeducedTrait ;
      friend class CommandDelegator ;
      friend class Reader ;
      friend class ::ProjetUnivers::Kernel::Implementation::Operation ;
      friend class ::ProjetUnivers::Kernel::Implementation::Transaction ;
      friend class ::ProjetUnivers::Kernel::Implementation::Interpretor ;
      friend class ::ProjetUnivers::Kernel::Implementation::ConcurrentBlock ;
    };
  }
}      

#include <kernel/implementation/object.cxx>

#endif /*PU_KERNEL_OBJECT_H_*/
