/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
      
    /*!
      @name View managment
    */
    // @{

      /// Views on the trait 
      /*!
        @composite
      */
      std::multimap<ViewPoint*,BaseTraitView*> m_views ;

      typedef 
      boost::function2<BaseTraitView*, Trait*, ViewPoint*> 
        ViewBuilder ;

      /// ViewPoint -> Trait X ViewBuilder (in term of classes names)
      static std::multimap<
        TypeIdentifier,
        std::pair<TypeIdentifier,ViewBuilder> > m_view_builders ;
      
      /// View X ViewPoint -> Trait (in term of classes names)
      static std::map<
        std::pair<TypeIdentifier,TypeIdentifier>,
        TypeIdentifier>                         m_trait_of_view ;
      
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
          ClassTrait* temp(static_cast<ClassTrait*>( _model)) ;              \
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
          ClassTrait* temp(static_cast<ClassTrait*>(_model)) ;               \
          ClassControlerSet* temp2(static_cast<ClassControlerSet*>( _set)) ; \
          return new ClassControler(temp,temp2) ;                            \
        }                                                                    \
        static                                                               \
        ProjetUnivers::Kernel::ControlerRegistration<                        \
            ClassTrait,ClassControlerSet,ClassControler> temp(&build) ;      \
      }                                                                
    
      
    template <class _Trait,class _ViewPoint,class _View> 
    class ViewRegistration
    {
    public:
      
      /// Constructor.
      /*!
        This constructor is called at the module init because of the variable 
        declaration in macro RegisterView. 
        
        The internal C++ classes names is used as a registering key for 
        builder.
        
        It also register mapping from ViewXViewPoint to Trait
      */
      ViewRegistration(Trait::ViewBuilder builder)
      {
        
        Kernel::Trait::registerBuilder(getClassTypeIdentifier(_Trait),
                                       getClassTypeIdentifier(_ViewPoint),
                                       builder) ;
        Kernel::Trait::registerMapping(getClassTypeIdentifier(_View),
                                       getClassTypeIdentifier(_ViewPoint),
                                       getClassTypeIdentifier(_Trait)) ;
                                        
      }
    };
    
    template <class _Trait, class _ControlerSet, class _Controler> 
    class ControlerRegistration
    {
    public:
      
      /// Constructor.
      /*!
        This constructor is called at the module init because of the variable 
        declaration in macro RegisterControler. 
        
        The internal C++ classes names is used as a registering key for 
        builder.
        
        It also register mapping from ControlerXControlerSet to Trait
      */
      ControlerRegistration(Trait::ControlerBuilder builder)
      {
        
        Kernel::Trait::registerControler(getClassTypeIdentifier(_Trait),
                                         getClassTypeIdentifier(_ControlerSet),
                                         builder) ;

        Kernel::Trait::registerControlerMapping(
                                       getClassTypeIdentifier(_Controler),
                                       getClassTypeIdentifier(_ControlerSet),
                                       getClassTypeIdentifier(_Trait)) ;
                                        
      }
    };
    
    
    
    
    template<class View> View* Trait::getView(ViewPoint* i_viewpoint)
    {
      InternalMessage(
        (std::string("Trait::getView for ") + toString((int)i_viewpoint)).c_str()) ;
      
      std::multimap<ViewPoint*,BaseTraitView*>::const_iterator
        finder = m_views.lower_bound(i_viewpoint) ;
      
      if (finder != m_views.end() && finder->first == i_viewpoint) 
      {
        std::multimap<ViewPoint*,BaseTraitView*>::const_iterator
          last = m_views.upper_bound(i_viewpoint) ;
        
        while(finder != last)
        {
          View* candidate = dynamic_cast<View*>(finder->second) ;
          if (candidate)
          {
            InternalMessage("found view") ;
            return candidate ;
          }
          ++finder ;
        }
      }
      InternalMessage("not found view") ;
      return NULL ;
    }

    template<class _Controler> 
    _Controler* Trait::getControler(ControlerSet* i_controler_set)
    {
      InternalMessage(
        (std::string("Trait::getControler for ") + toString((int)i_controler_set)).c_str()) ;
      
      std::multimap<ControlerSet*,BaseControler*>::const_iterator 
        finder = m_controlers.find(i_controler_set) ;
      
      if (finder != m_controlers.end()) 
      {
        InternalMessage("found controler") ;
        
        return dynamic_cast<_Controler*>(finder->second) ;
      }
      else
      {
        InternalMessage("no controler found") ;
        return NULL ;
      }
      
    }
    

  }
}

#endif /*PU_KERNEL_TRAIT_VIEW_H_*/
