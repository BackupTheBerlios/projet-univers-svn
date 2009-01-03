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
#ifndef PU_KERNEL_TRAIT_H_
#define PU_KERNEL_TRAIT_H_

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
  
    class Object ;
    class BaseTraitView ;
    class ViewPoint ;
    class DeducedTrait ;
    class ControlerSet ;
    class BaseControler ;
    class BaseTraitReference ;
    class Reader ;
    
    /// Abstract class for object traits.
    class Trait
    {
    public:

      /// Build a trait from a reader.
      static Trait* read(Reader*) ;
    
      /// Access to object.      
      Object* getObject() const ;

      /// Access to a specific view.
      template<class View> View* getView(ViewPoint* i_viewpoint) ;

      /// Access to a specific controler.
      template<class _Controler> 
      _Controler* getControler(ControlerSet* i_controler_set) ;

      /// Access to the trait class's name associated with i_view, i_viewpoint.
      static const TypeIdentifier& getTraitName(const TypeIdentifier& i_view,
                                                const TypeIdentifier& i_viewpoint) ;

      /// Apply @c i_operation on all controlers of @c i_controler_set.
      /*!
        @deprecated
      */
      void apply(ControlerSet*                         i_controler_set,
                 boost::function1<void,BaseControler*> i_operation) ;

      /// Abstract class means virtual destructor.
      virtual ~Trait() ;
      
      /// Register a command for that trait.
      template <class SpecializedTrait> static void addCommand(
          const std::string&                       i_command_name,
          boost::function1<void,SpecializedTrait*> i_operation) ;

      /// Register an axis update for that trait.
      template <class SpecializedTrait> static void addAxis(
          const std::string&                           axis_name,
          const std::string&                           axis_group_name,
          boost::function2<void,SpecializedTrait*,int> axis_update) ;
      
      /// Add a definition for that funciton on this trait.
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
      void _changed_parent(Object* i_old_parent) ;
      
      /// update the views.
      void _updated() ;
      
      /// init after construction.
      void _init() ;

      /// init the views after construction.
      void _init(ViewPoint* i_viewpoint) ;

      /// init the controlers after construction.
      void _init(ControlerSet* i_controler_set) ;

      /// closes before destruction.
      void _close() ;

      /// close the views.
      void _close(ViewPoint* i_viewpoint) ;

      /// close the controlers before controler set closing.
      void _close(ControlerSet* i_controler_set) ;

    // @}
    /*!
      @name System construction.
    */
    // @{

      /// create the views.
      void _create_views() ;

      /// create views for a viewpoint.
      void _create_views(ViewPoint* i_viewpoint) ;
      
      /// create the controlers for a controler set
      void _create_controlers(ControlerSet* i_controler_set) ;
      
      /// create the controlers.
      void _create_controlers() ;

      /// Remove a view, used in ~BaseTraitVue.
      void _remove_view(ViewPoint* i_viewpoint,BaseTraitView* i_view) ;

      /// Remove a controler, used in ~BaseControler.
      void _remove_controler(ControlerSet* i_controler_set,BaseControler* i_controler) ;

      /// To avoid removing view while destroying object  
      bool m_destroying ;
      
      /// Get the trait's type identifier that is associated with @c i_view_type @c i_viewpoint_type.
      static TypeIdentifier getTraitTypeOfView(const TypeIdentifier& i_view_type,
                                               const TypeIdentifier& i_viewpoint_type) ;
      
    // @}
    /*!
      @name View managment
    */
    // @{

      /// Views on the trait 
      /*!
        @composite
      */
      std::multimap<ViewPoint*,BaseTraitView*>             m_views ;

      typedef 
      boost::function2<BaseTraitView*, Trait*, ViewPoint*> ViewBuilder ;

      
      /// Register @c _builder as the builder for @c _trait in @c _viewpoint
      /*!
        Whenever a trait is build, the corresponding trait views will be 
        automatically built in each viewpoints.
      */
      static void registerBuilder(const TypeIdentifier& _trait,
                                  const TypeIdentifier& _viewpoint,
                                  ViewBuilder _builder) ;

      /// Register @c i_trait as the trait for @c i_view and @c i_viewpoint.
      static void registerMapping(const TypeIdentifier& i_view,
                                  const TypeIdentifier& i_viewpoint,
                                  const TypeIdentifier& i_trait) ;
      
      template <class _Trait,class _ViewPoint,class _View> 
        friend class ViewRegistration ;

    // @}
    /*!
      @name Trait Controler managment
    */
    // @{


      /// Controlers that apply on the trait, organised by controler sets.
      std::multimap<ControlerSet*,BaseControler*> m_controlers ;
      
      // The type for Trait X ControlerSet -> BaseControler
      typedef 
      boost::function2<BaseControler*, Trait*, ControlerSet*> 
        ControlerBuilder ;

      
      /// Register @c i_builder as the builder for @c i_trait_class in 
      /// @c i_controler_set_class
      /*!
        Whenever a trait is build, the corresponding trait controler will be 
        automatically built in each controler set.
      */
      static void registerControler(
            const TypeIdentifier& i_trait_class,
            const TypeIdentifier& i_controler_set_class,
            ControlerBuilder      i_builder) ;

      /// Register @c i_trait_class as the trait for @c i_controler_class 
      /// and @c i_controler_set_class.
      static void registerControlerMapping(
              const TypeIdentifier& i_controler_class,
              const TypeIdentifier& i_controler_set_class,
              const TypeIdentifier& i_trait_class) ;


      template <class _Trait,class _ControlerSet,class _Controler> 
        friend class ControlerRegistration ;

    // @}
    /*!
      @name Command managment
      
      Preliminary version.
    */
    // @{

    protected:

      /// call a void command returns true iff succedeed.
      virtual bool call(const TypeIdentifier& i_trait_type,
                        const std::string&    i_command) ;

      /// call an int command returns true iff succedeed.
      virtual bool call(const TypeIdentifier& i_trait_type,
                        const std::string&    i_command, 
                        const int&            i_parameter) ;
      
      /// Function call return <true,result> if succeeded <false,..> otherwise.
      virtual std::pair<bool,boost::any> callFunction(
          const TypeIdentifier& trait_type,
          const std::string&    function) ; 

      /// Access to all commands understood be the trait.
      virtual std::set<std::string> getCommands() const ;
    

    private:
        
    // @}
    /*!
      @name Reference managment
    */
    // @{
      
      void _registerReference(BaseTraitReference*) ;
      void _unregisterReference(BaseTraitReference*) ;
      
      /// Trait references pointing on this.
      std::set<BaseTraitReference*> m_references ;
      
      template <class Trait> friend class TraitReference ;  
      
    // @}
      
      typedef boost::function1<Trait*, Reader*> ReaderFunction ;  
      
      /// Register a reader function.
      static void _registerReader(const std::string& name,ReaderFunction reader) ;
      
      /// Static storage
      /*!
        Because static variable dynamic initialisation occurs in an undefined 
        order, we use this hook. By calling : 
        <code>
          StaticStorage::get()->variable...
        </code>
        we are assured that map are dynamically initialised on demand.
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
          These are commands taking an int parameter, mainly obtained by 
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
      
      friend class Object ;
      friend class BaseTraitView ;
      friend class BaseControler ;
      friend class DeducedTrait ;
      friend class TraitReaderRegistration ;
    };
    
    /// Tells that @c TraitClass is a trait class.
    #define RegisterTrait(TraitClass)                                        \
      namespace PU_MAKE_UNIQUE_NAME(register_trait) {                        \
        static                                                               \
        ProjetUnivers::Kernel::TraitReaderRegistration                       \
          temp(#TraitClass,&TraitClass::read) ;                              \
      }

    /// Tells that ClassView is the view for ClassTrait in ClassViewPoint.
    /*!
    @par Usage
      In the .cpp of a view class : 
        RegisterView(ClassView,ClassTrait,ClassViewPoint) ;
        
    Example
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
          ClassTrait* temp(dynamic_cast<ClassTrait*>( _model)) ;             \
          ClassViewPoint* temp2(static_cast<ClassViewPoint*>( _viewpoint)) ; \
          return new ClassView(temp,temp2) ;                                 \
        }                                                                    \
        static                                                               \
        ProjetUnivers::Kernel::ViewRegistration<                             \
            ClassTrait,ClassViewPoint,ClassView> temp(&build) ;              \
      }                                                                

    /// Tells that ClassControler is the controler for ClassTrait in ClassControlerSet.
    /*!
    @par Usage
      In the .cpp of a controler class : 
      
        RegisterControler(ClassControler,ClassTrait,ClassControlerSet) ;
        
    Example
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
          ClassTrait* temp(dynamic_cast<ClassTrait*>(_model)) ;              \
          ClassControlerSet* temp2(static_cast<ClassControlerSet*>( _set)) ; \
          return new ClassControler(temp,temp2) ;                            \
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

#endif /*PU_KERNEL_TRAIT_VIEW_H_*/
