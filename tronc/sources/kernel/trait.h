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
#include <boost/function.hpp>

#include <kernel/meta.h>
#include <kernel/helper_macros.h>
#include <kernel/log.h>
#include <kernel/string.h>

namespace ProjetUnivers {
  namespace Kernel {
  
    class Object ;
    class BaseTraitView ;
    class ViewPoint ;
    class DeducedTrait ;
    class ControlerSet ;
    class BaseControler ;
    
    /// Abstract class for object traits.
    class Trait
    {
    public:
    
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
        @deprecated.
      */
      void apply(ControlerSet*                         i_controler_set,
                 boost::function1<void,BaseControler*> i_operation) ;

      /// Abstract class means virtual destructor.
      virtual ~Trait() ;
      
      /// Register a command for that trait.
      template <class SpecializedTrait>
      static
      void addCommand(const std::string&                       i_command_name,
                      boost::function1<void,SpecializedTrait*> i_operation) ;

      /// Register an axis update for that trait.
      template <class SpecializedTrait>
      static 
      void addAxis(const std::string&                           i_command_name,
                   boost::function2<void,SpecializedTrait*,int> i_axis_update) ;
      
      
    protected: 
    
      /// Abstract class means protected constructor.
      Trait() ;
      
      /// Trait's contener.
      Object* object ;

      /// Tells the views the trait has changed.
      void notify() ;

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

      /// ViewPoint -> Trait X ViewBuilder (in term of classes names)
      static std::multimap<
        TypeIdentifier,
        std::pair<TypeIdentifier,ViewBuilder> >            m_view_builders ;
      
      /// View X ViewPoint -> Trait (in term of classes names)
      static std::map<
        std::pair<TypeIdentifier,TypeIdentifier>,
        TypeIdentifier>                                    m_trait_of_view ;
      
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

      /// ControlerSet -> Trait X ControlerBuilder (in term of classes names)
      static std::multimap<
        TypeIdentifier,
        std::pair<TypeIdentifier,ControlerBuilder> > m_controler_builders ;
      
      /// Controler X ControlerSet -> Trait (in term of classes names)
      static std::map<
        std::pair<TypeIdentifier,TypeIdentifier>,
        TypeIdentifier>                        m_trait_of_controler ;
      
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

      /// Access to all commands understood be the trait.
      virtual std::set<std::string> getCommands() const ;
    
      /// Commands that the trait understand.
      /*!
        These are void commands, mainly triggered by buttons and keys.
      */
      static 
      std::map<TypeIdentifier,
               std::map<std::string,
                        boost::function1<void,Trait*> > > m_void_commands ;
    
      /// Commands that the trait understand.
      /*!
        These are commands taking an int parameter, mainly obtained by 
        mouse and joystick axes.
      */
      static 
      std::map<TypeIdentifier,
               std::map<std::string,
                        boost::function2<void,Trait*,int> > > m_int_commands ;

    
    // @}
    
    
      friend class Object ;
      friend class BaseTraitView ;
      friend class BaseControler ;
      friend class DeducedTrait ;
    };

    /// Tells that ClassView is the view for ClassTrait in ClassViewPoint.
    /*!
    @par Usage
      In the .cpp of a view class : 
        RegisterView(ClassView,ClassTrait,ClassViewPoint) ;
        
    @example
      RegisterView(Display::Mobile,Model::Mobile,Ogre::ViewPoint) ;
    
    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterView(ClassView,ClassTrait,ClassViewPoint)                \
      namespace PU_MAKE_UNIQUE_NAME(local) {                                 \
        static                                                               \
        ProjetUnivers::Kernel::BaseTraitView* build(                         \
          ProjetUnivers::Kernel::Trait* _model,                              \
          ProjetUnivers::Kernel::ViewPoint* _viewpoint)                      \
        {                                                                    \
          ClassTrait* temp(dynamic_cast<ClassTrait*>( _model)) ;              \
          ClassViewPoint* temp2(static_cast<ClassViewPoint*>( _viewpoint)) ; \
          return new ClassView(temp,temp2) ;                                 \
        }                                                                    \
        static                                                               \
        ProjetUnivers::Kernel::ViewRegistration<                             \
            ClassTrait,ClassViewPoint,ClassView> temp(&build) ;              \
      }                                                                

    /// ClassView is the view for every trait in ClassViewPoint.
    #define RegisterUniversalView(ClassView,ClassViewPoint)

    /// Tells that ClassControler is the controler for ClassTrait in ClassControlerSet.
    /*!
    @par Usage
      In the .cpp of a controler class : 
      
        RegisterControler(ClassControler,ClassTrait,ClassControlerSet) ;
        
    @example
      RegisterView(Logic::Stabilizer,Model::Stabilizer,Logic) ;
    
    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterControler(ClassControler,ClassTrait,ClassControlerSet)   \
      namespace PU_MAKE_UNIQUE_NAME(local) {                                 \
        static                                                               \
        ProjetUnivers::Kernel::BaseControler* build(                         \
          ProjetUnivers::Kernel::Trait* _model,                              \
          ProjetUnivers::Kernel::ControlerSet* _set)                         \
        {                                                                    \
          ClassTrait* temp(dynamic_cast<ClassTrait*>(_model)) ;               \
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
        
    @example
      RegisterCommand("fire",Model::Canon,fire) ;
    
    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterCommand(CommandName,ClassTrait,MethodName)               \
      namespace PU_MAKE_UNIQUE_NAME(local) {                                 \
        static                                                               \
        ProjetUnivers::Kernel::CommandRegistration<ClassTrait>               \
          temp(CommandName,&ClassTrait::MethodName) ;                        \
      }                                                                


    /// Register @c ClassTrait::MethodName as an axis named @c CommandName .
    /*!
    @par Usage
      In the .cpp of a trait clas : 
      
        RegisterCommand(CommandName,ClassTrait,MethodName) ;
        
    @example
      RegisterCommand("fire",Model::Throttle,setThrottle) ;
    
    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
    */
    #define RegisterAxis(AxisName,ClassTrait,MethodName)               \
      namespace PU_MAKE_UNIQUE_NAME(local) {                           \
        static                                                         \
        ProjetUnivers::Kernel::AxisRegistration<ClassTrait>            \
          temp(AxisName,&ClassTrait::MethodName) ;                     \
      }                                                                

  }
}

#include <kernel/implementation/trait.cxx>

#endif /*PU_KERNEL_TRAIT_VIEW_H_*/
