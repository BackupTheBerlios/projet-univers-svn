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

#include <kernel/helper_macros.h>
#include <kernel/log.h>
#include <kernel/string.h>

namespace ProjetUnivers {
  namespace Kernel {
  
    class Object ;
    class BaseTraitView ;
    class ViewPoint ;
    class DeducedTrait ;
    
    /// Abstract class for object traits.
    class Trait
    {
    public:
    
      /// Access to object.      
      Object* getObject() const ;

      /// Access to a specific view.
      template<class View> View* getView(ViewPoint* i_viewpoint) ;

      /// Access to the trait class's name associated with i_view, i_viewpoint.
      static const std::string& getTraitName(const std::string& i_view,
                                             const std::string& i_viewpoint) ;

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
      
      /// update the views for a change_parent. 
      void _changed_parent(Object* i_old_parent) ;
      
      /// update the views.
      void _updated() ;
      
      /// create the views.
      void _create_views() ;

      /// create views for a viewpoint.
      void _create_views(ViewPoint* i_viewpoint) ;
      
      /// init the views after construction.
      void _init() ;

      /// init the views after construction.
      void _init(ViewPoint* i_viewpoint) ;

      /// closes the views before destruction.
      void _close() ;

      /// close the views.
      void _close(ViewPoint* i_viewpoint) ;

    /*!
      @name View storage
    */
    // @{

      /// @composite
      std::map<ViewPoint*,BaseTraitView*> views ;

      typedef 
        boost::function2<BaseTraitView*, Trait*, ViewPoint*> ViewBuilder ;

      /// Each viewpoint has its own trait_view builders.
      static std::map<std::pair<std::string,std::string>,
                      ViewBuilder>                        builders ;
      
      /// View X ViewPoint -> Trait (in term of classes names)
      static std::map<std::pair<std::string,std::string>,
                      std::string>                        m_trait_of_view ;
      
      /// Register @c _builder as the builder for @c _trait in @c _viewpoint
      /*!
        Whenever a trait is build, the corresponding trait views will be 
        automatically built in each viewpoints.
      */
      static void registerBuilder(const std::string& _trait,
                                  const std::string& _viewpoint,
                                  ViewBuilder _builder) ;

      /// Register @c i_trait as the trait for @c i_view and @c i_viewpoint.
      static void registerMapping(const std::string& i_view,
                                  const std::string& i_viewpoint,
                                  const std::string& i_trait) ;
      
      template <class _Trait,class _ViewPoint,class _View> 
        friend class ViewRegistration ;

    // @}

      friend class Object ;
      friend class BaseTraitView ;
      friend class DeducedTrait ;
    };

    /// Tells that ClassView is the view for ClassModelin ClassViewPoint.
    /*!
    @par Usage
      
      In the .cpp of a view class : 
      
        RegisterView(ClasseView,ClasseModel,ClasseViewPoint) ;
        
    @example
      RegisterView(Display::Mobile,Model::Mobile,Ogre::ViewPoint) ;
      
    
    @par How does it works
      Same principle than CPPUNIT_TEST_SUITE_REGISTRATION
      
    */
    #define RegisterView(ClassView,ClassTrait,ClassViewPoint)                \
      namespace PU_MAKE_UNIQUE_NAME(local) {                                 \
        ProjetUnivers::Kernel::BaseTraitView* build(                         \
          ProjetUnivers::Kernel::Trait* _model,                              \
          ProjetUnivers::Kernel::ViewPoint* _viewpoint)                      \
        {                                                                    \
          ClassTrait* temp(static_cast<ClassTrait*>( _model)) ;              \
          ClassViewPoint* temp2(static_cast<ClassViewPoint*>( _viewpoint)) ; \
          return new ClassView(temp,temp2) ;                                 \
        }                                                                    \
        ProjetUnivers::Kernel::ViewRegistration<ClassTrait,ClassViewPoint,ClassView> \
            temp(&build) ;                                                   \
      }                                                                
      
    template <class _Trait, class _ViewPoint, class _View> class ViewRegistration
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
        
        Kernel::Trait::registerBuilder(typeid(_Trait).name(),
                                       typeid(_ViewPoint).name(),
                                       builder) ;
        Kernel::Trait::registerMapping(typeid(_View).name(),
                                       typeid(_ViewPoint).name(),
                                       typeid(_Trait).name()) ;
                                        
      }
    };
    
    template<class View> View* Trait::getView(ViewPoint* i_viewpoint)
    {
      Log::InternalMessage(
        (std::string("Trait::getView for ") + toString((int)i_viewpoint)).c_str()) ;
      
      if (views.find(i_viewpoint) != views.end()) 
      {
        Log::InternalMessage("found view") ;
        
        return dynamic_cast<View*>(views[i_viewpoint]) ;
      }
      else
      {
        Log::InternalMessage("not found view") ;
        return NULL ;
      }
    }

  }
}

#endif /*PU_KERNEL_TRAIT_VIEW_H_*/
