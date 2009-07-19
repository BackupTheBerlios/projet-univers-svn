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
#pragma once

/*!
  @file trait.h

*/

#include <map>
#include <stack>
#include <boost/function.hpp>
#include <boost/any.hpp>

#include <kernel/meta.h>
#include <kernel/helper_macros.h>
#include <kernel/log.h>
#include <kernel/string.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    namespace Test
    {
      class TestTrait ;
    }
    namespace Implementation
    {
      class Operation ;
    }

    class Object ;
    class BaseTraitView ;
    class ViewPoint ;
    class DeducedTrait ;
    class ControlerSet ;
    class BaseControler ;
    class BaseTraitReference ;
    class Reader ;
    class Writer ;
    class TraitFormula ;
    class FormulaOr ;
    class IsRelatedFormula ;
    class IsOnlyRelatedFormula ;

    /// Abstract class for object traits.
    class Trait
    {
    public:

      /// Build a trait from a reader.
      static Trait* read(Reader*) ;

      /// Access to object.
      Object* getObject() const ;

      /// Access to a specific view.
      template<class View>
      View* getView(ViewPoint* viewpoint) ;

      /// Access to a specific controler.
      template<class _Controler>
      _Controler* getControler(ControlerSet* controler_set) ;

      /// Access to the trait class's name associated with view, viewpoint.
      static const TypeIdentifier& getTraitName(const TypeIdentifier& view,
                                                const TypeIdentifier& viewpoint) ;

      /// Apply @c operation on all controlers of @c controler_set.
      /*!
        @deprecated
      */
      void apply(ControlerSet*                         controler_set,
                 boost::function1<void,BaseControler*> operation) ;

      /// Abstract class means virtual destructor.
      virtual ~Trait() ;

      /// Register a command for that trait.
      template <class SpecializedTrait> static void addCommand(
          const std::string&                       command_name,
          boost::function1<void,SpecializedTrait*> operation) ;

      /// Register an axis update for that trait.
      template <class SpecializedTrait> static void addAxis(
          const std::string&                           axis_name,
          const std::string&                           axis_group_name,
          boost::function2<void,SpecializedTrait*,int> axis_update) ;

      /// Add a definition for that function on this trait.
      template <class SpecializedTrait> static void addFunction(
          const std::string&                             function_name,
          boost::function1<boost::any,SpecializedTrait*> function) ;

      /// Manual adding of a view.
      void addView(ViewPoint*,BaseTraitView*) ;

      /// Manual removing of the viewpoint's views .
      void removeView(ViewPoint*) ;

      /// Access to all registered commands.
      static std::set<std::string> getRegisteredCommands() ;

      /// Access to all registered *not internal* axes groups.
      /*!
        An axis may be registered as internal.
      */
      static std::set<std::string> getRegisteredAxesGroups() ;

      /// Access to all registered axes of a group.
      static std::set<std::string> getRegisteredAxes(const std::string&) ;

      /// Access to all registered *not internal* axes..
      static std::set<std::string> getRegisteredAxes() ;

      /// Write trait
      virtual void write(Writer*) ;

      /// True if the trait is not deduced
      virtual bool isPrimitive() const ;

    protected:

      /// Abstract class means protected constructor.
      Trait() ;

      /// Trait's contener.
      Object* m_object ;

      /// Tells the views the trait has changed.
      virtual void notify() ;

      /// The latest updated trait type.
      static std::stack<TypeIdentifier> m_latest_updated_trait ;

    private:

    /*!
      @name Update notifications.
    */
    // @{

      /// update the views for a change_parent.
      void _changed_parent(Object* old_parent) ;

      /// update the views.
      void _updated() ;

      /// init after construction.
      void _init() ;

      /// init the views after construction.
      void _init(ViewPoint* viewpoint) ;

      /// init the controlers after construction.
      void _init(ControlerSet* controler_set) ;

      /// closes before destruction.
      void _close() ;

      /// close the views.
      void _close(ViewPoint* viewpoint) ;

      /// close the controlers before controler set closing.
      void _close(ControlerSet* controler_set) ;

    // @}
    /*!
      @name System construction.
    */
    // @{

      /// create the views.
      void _create_views() ;

      /// create views for a viewpoint.
      void _create_views(ViewPoint* viewpoint) ;

      /// create the controlers for a controler set
      void _create_controlers(ControlerSet* controler_set) ;

      /// create the controlers.
      void _create_controlers() ;

      /// Remove a view, used in ~BaseTraitVue.
      void _remove_view(ViewPoint* viewpoint,BaseTraitView* view) ;

      /// Remove a controler, used in ~BaseControler.
      void _remove_controler(ControlerSet* controler_set,BaseControler* controler) ;

      /// To avoid removing view while destroying object
      bool m_destroying ;

      /// Get the trait's type identifier that is associated with @c view_type @c viewpoint_type.
      static TypeIdentifier getTraitTypeOfView(const TypeIdentifier& view_type,
                                               const TypeIdentifier& viewpoint_type) ;

      /// Get the trait's type identifier that is associated with @c controler_type @c controler_set_type.
      static TypeIdentifier getTraitTypeOfControler(const TypeIdentifier& controler_type,
                                                    const TypeIdentifier& controler_set_type) ;

    // @}
    /*!
      @name View management
    */
    // @{

      /// Views on the trait
      /*!
        @composite
      */
      std::multimap<ViewPoint*,BaseTraitView*>             m_views ;

      /// Type for function that build views from a trait and viewpoint.
      typedef
      boost::function2<BaseTraitView*, Trait*, ViewPoint*> ViewBuilder ;


      /// Register @c _builder as the builder for @c _trait in @c _viewpoint
      /*!
        Whenever a trait is built, the corresponding trait views will be
        automatically built in each viewpoints.
      */
      static void registerBuilder(const TypeIdentifier& _trait,
                                  const TypeIdentifier& _viewpoint,
                                  ViewBuilder _builder) ;

      /// Register @c trait as the trait for @c view and @c viewpoint.
      static void registerMapping(const TypeIdentifier& view,
                                  const TypeIdentifier& viewpoint,
                                  const TypeIdentifier& trait) ;

      template <class _Trait,class _ViewPoint,class _View>
        friend class ViewRegistration ;

    // @}
    /*!
      @name Trait Controler managment
    */
    // @{


      /// Controlers that apply on the trait, organized by controler sets.
      std::multimap<ControlerSet*,BaseControler*> m_controlers ;

      // The type for Trait X ControlerSet -> BaseControler
      typedef
      boost::function2<BaseControler*, Trait*, ControlerSet*>
        ControlerBuilder ;


      /// Register @c builder as the builder for @c trait_class in
      /// @c controler_set_class
      /*!
        Whenever a trait is build, the corresponding trait controler will be
        automatically built in each controler set.
      */
      static void registerControler(
            const TypeIdentifier& trait_class,
            const TypeIdentifier& controler_set_class,
            ControlerBuilder      builder) ;

      /// Register @c trait_class as the trait for @c controler_class
      /// and @c controler_set_class.
      static void registerControlerMapping(
              const TypeIdentifier& controler_class,
              const TypeIdentifier& controler_set_class,
              const TypeIdentifier& trait_class) ;


      template <class _Trait,class _ControlerSet,class _Controler>
        friend class ControlerRegistration ;

    // @}
    /*!
      @name Command management

      Preliminary version.
    */
    // @{

    protected:

      /// call a void command returns true iff succeeded.
      virtual bool call(const TypeIdentifier& trait_type,
                        const std::string&    command) ;

      /// call an int command returns true iff succeeded.
      virtual bool call(const TypeIdentifier& trait_type,
                        const std::string&    command,
                        const int&            parameter) ;

      /// Function call return <true,result> if succeeded <false,..> otherwise.
      virtual std::pair<bool,boost::any> callFunction(
          const TypeIdentifier& trait_type,
          const std::string&    function) ;

      /// Access to all commands understood be the trait.
      virtual std::set<std::string> getCommands() const ;

      /// Add a lock the trait, it will be removed when unlocked
      void lock() ;

      /// Remove a lock on the trait
      void unlock() ;

      /// Has it locks ?
      bool isLocked() const ;

    private:

    // @}
    /*!
      @name Reference management
    */
    // @{

      void _registerReference(BaseTraitReference*) ;
      void _unregisterReference(BaseTraitReference*) ;

      /// Trait references pointing on this.
      std::set<BaseTraitReference*> m_references ;

      template <class Trait> friend class TraitReference ;

    // @}

      /// Number of active locks
      int m_locks ;

    /*!
      @name Dependency management
    */
    // @{

      /// True during notify().
      bool m_is_updating ;

      /// Add a dependent trait.
      void addDependency(DeducedTrait*) ;
      /// Remove a dependent trait.
      void removeDependency(DeducedTrait*) ;
      /// Remove a dependent trait.
      void _removeDependency(DeducedTrait*) ;

      /// Access to direct dependent deduced traits.
      /*!
        @todo change to multivalued redundant collection (because the same
        trait update twice ;) ) + add a test showing the bug

        Gives the traits to update if we update @c this (non recursive).

        This value is stored and maintained during structure changes. So access
        if fast at cost of structural changes and memory.

        In case of DeducedTrait, this value is equivalent to
        getDependentDeducedTraits(@c this) on the formula defining the deduced trait.
      */
      const std::set<DeducedTrait*>& getDependentDeducedTraits() const ;
      /// Traits that directly depends on @c this
      std::set<DeducedTrait*> m_direct_dependent_traits ;

      /// Propagate update on dependent traits.
      /*!
        @todo use it instead of formula update propagation.
      */
      void updateDepedentTraits() const ;

    // @}

      typedef boost::function1<Trait*, Reader*> ReaderFunction ;

      /// Register a reader function.
      static void _registerReader(const std::string& name,ReaderFunction reader) ;

      /// Static storage
      /*!
        Because static variable dynamic initialization occurs in an undefined
        order, we use this hook. By calling :
        <code>
          StaticStorage::get()->variable...
        </code>
        we are assured that map are dynamically initialized on demand.
      */
      class StaticStorage
      {
      public:

        /// Access to singleton.
        static StaticStorage* get() ;

        /// ViewPoint -> Trait X ViewBuilder (in term of classes names)
        std::multimap<TypeIdentifier,
                      std::pair<TypeIdentifier,
                                ViewBuilder> >            m_view_builders ;

        /// View X ViewPoint -> Trait (in term of classes names)
        std::map<std::pair<TypeIdentifier,TypeIdentifier>,
                 TypeIdentifier>                           m_trait_of_view ;

        /// ControlerSet -> Trait X ControlerBuilder (in term of classes names)
        std::multimap<TypeIdentifier,
                      std::pair<TypeIdentifier,
                                Trait::ControlerBuilder> > m_controler_builders ;

        /// Controler X ControlerSet -> Trait (in term of classes names)
        std::map<std::pair<TypeIdentifier,TypeIdentifier>,
                 TypeIdentifier>                          m_trait_of_controler ;

        /// Commands that traits understand.
        /*!
          These are void commands, mainly triggered by buttons and keys.
        */
        std::map<TypeIdentifier,
                 std::map<std::string,
                          boost::function1<void,Trait*> > > m_void_commands ;

        /// Axes that traits understand.
        /*!
          These are commands taking an integer parameter, mainly obtained by
          mouse and joystick axes.
        */
        std::map<TypeIdentifier,
                 std::map<std::string,
                          boost::function2<void,Trait*,int> > > m_int_commands ;

        /// Axes are grouped into groups.
        std::multimap<std::string,std::string> m_axes_group_to_axes ;

        /// Custom parameter less functions.
        std::map<TypeIdentifier,
                 std::map<std::string,
                          boost::function1<boost::any,Trait*> > > m_functions ;

        /// xml tag name -> reader functions
        std::map<std::string,ReaderFunction> m_readers ;

      private:

        StaticStorage()
        {}

      };

      const std::set<TraitFormula*>& getImpactedTraitFormulae() ;
      const std::set<TraitFormula*>* m_impacted_trait_formulae ;


      friend class Object ;
      friend class BaseTraitView ;
      friend class BaseControler ;
      friend class DeducedTrait ;
      friend class TraitReaderRegistration ;
      friend class TraitFormula ;
      friend class FormulaOr ;
      friend class HasParentFormula ;
      friend class HasAncestorFormula ;
      friend class HasChildFormula ;
      friend class IsRelatedFormula ;
      friend class IsOnlyRelatedFormula ;
      friend class ::ProjetUnivers::Kernel::Test::TestTrait ;
      friend class ::ProjetUnivers::Kernel::Implementation::Operation ;
    };

    /// Tells that @c TraitClass is a trait class.
    #define RegisterTrait(TraitClass)                                        \
      namespace PU_MAKE_UNIQUE_NAME(register_trait) {                        \
        static                                                               \
        ProjetUnivers::Kernel::TraitReaderRegistration                       \
          temp(#TraitClass,&TraitClass::read) ;                              \
      }

    /// @c ClassView is the view for @c ClassTrait in @c ClassViewPoint.
    /*!
    @par Usage
    @c ClassView must inherit from
    @code
      Kernel::TraitView<ClassTrait,ClassViewPoint>
    @endcode
    In the .cpp of a view class :
    @code
      RegisterView(ClassView,ClassTrait,ClassViewPoint) ;
    @endcode

    @par Example
    @code
      RegisterView(Display::Mobile,Model::Mobile,Ogre::ViewPoint) ;
    @endcode

    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterView(ClassView,ClassTrait,ClassViewPoint)                \
      namespace PU_MAKE_UNIQUE_NAME(register_view) {                         \
        static                                                               \
        ProjetUnivers::Kernel::BaseTraitView* build(                         \
          ProjetUnivers::Kernel::Trait* _model,                              \
          ProjetUnivers::Kernel::ViewPoint* _viewpoint)                      \
        {                                                                    \
          return new ClassView() ;                                           \
        }                                                                    \
        static                                                               \
        ProjetUnivers::Kernel::ViewRegistration<                             \
            ClassTrait,ClassViewPoint,ClassView> temp(&build) ;              \
      }

    /// @c ClassControler is the controler for @c ClassTrait in @c ClassControlerSet.
    /*!
    @par Usage
    @c ClassControler must inherit from
    @code
      Kernel::Controler<ClassTrait,ClassControlerSet>
    @endcode
    In the .cpp of a controler class :
    @code
        RegisterControler(ClassControler,ClassTrait,ClassControlerSet) ;
    @endcode

    @par Example
    @code
      RegisterView(Logic::Stabilizer,Model::Stabilizer,Logic) ;
    @endcode

    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterControler(ClassControler,ClassTrait,ClassControlerSet)   \
      namespace PU_MAKE_UNIQUE_NAME(register_controler) {                    \
        static                                                               \
        ProjetUnivers::Kernel::BaseControler* build(                         \
          ProjetUnivers::Kernel::Trait* _model,                              \
          ProjetUnivers::Kernel::ControlerSet* _set)                         \
        {                                                                    \
          return new ClassControler() ;                                      \
        }                                                                    \
        static                                                               \
        ProjetUnivers::Kernel::ControlerRegistration<                        \
            ClassTrait,ClassControlerSet,ClassControler> temp(&build) ;      \
      }

    /// Register @c ClassTrait::MethodName as a command named @c CommandName .
    /*!
    @par Usage
      In the .cpp of a trait clas :

        RegisterCommand(CommandName,ClassTrait,MethodName) ;

    Example
    @code
      RegisterCommand("fire",Model::Canon,fire) ;
    @endcode

    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterCommand(CommandName,ClassTrait,MethodName)               \
      namespace PU_MAKE_UNIQUE_NAME(register_command) {                      \
        static                                                               \
        ProjetUnivers::Kernel::CommandRegistration<ClassTrait>               \
          temp(CommandName,&ClassTrait::MethodName) ;                        \
      }

    /// Special axis group name for the internal use axes.
    const std::string InternalGroup = "_internal_" ;

    /// Register @c ClassTrait::MethodName as an axis named @c AxisName .
    /*!
    @par Usage
      In the .cpp of a trait clas :

        RegisterAxis(AxisName,AxisGroupName,ClassTrait,MethodName) ;

    Example
    @code
      RegisterCommand("fire","attack",Model::Throttle,setThrottle) ;
    @endcode

    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterAxis(AxisName,AxisGroupName,ClassTrait,MethodName) \
      namespace PU_MAKE_UNIQUE_NAME(register_axis) {                   \
        static                                                         \
        ProjetUnivers::Kernel::AxisRegistration<ClassTrait>            \
          temp(AxisName,AxisGroupName,&ClassTrait::MethodName) ;       \
      }

    /// Register @c ClassTrait::MethodName as a function named @c FunctionName.
    /*!
    @par Usage
      In the .cpp of a trait clas :

        RegisterFunction(FunctionName,ClassTrait,MethodName) ;

    Example
    @code
      RegisterFunction("getPosition",Model::Positionned,getPosition) ;
    @endcode

    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterFunction(FunctionName,ClassTrait,MethodName)       \
      namespace PU_MAKE_UNIQUE_NAME(register_function) {               \
        boost::any localFunction(ClassTrait* trait)                    \
        {                                                              \
          return trait->MethodName() ;                                 \
        }                                                              \
        static                                                         \
        ProjetUnivers::Kernel::FunctionRegistration<ClassTrait>        \
          temp(FunctionName,&localFunction) ;                          \
      }


  }
}

#include <kernel/implementation/trait.cxx>
