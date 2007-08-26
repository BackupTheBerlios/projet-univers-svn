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
#ifndef PU_KERNEL_VIEW_POINT_H_
#define PU_KERNEL_VIEW_POINT_H_

#include <boost/function.hpp>

#include <kernel/meta.h>
#include <kernel/object.h>
#include <kernel/model.h>

namespace ProjetUnivers {
  namespace Kernel {
    
    class Trait ;
    class BaseTraitView ;
    
    /// Coherent set of views.
    /*!
      A view point is a set of views. Generally speaking, all these views 
      looks on model that are related to each other. These views must all 
      be updated in order to have a coherent view point.       
      
      @par Examples 
      - what a character looks
      - what a detector detects
    
      @par Usage
      -# create a ViewPoint
      -# register views by ViewPoint::add
      -# updates periodically the view point by ViewPoint::update
        
    */
    class ViewPoint 
    {
    public:
    
      /// Destructor, destroys all the views.
      virtual ~ViewPoint() ;

      /// initialise the viewpoint.
      void init() ;

      /// terminate the viewpoint.
      void close() ;
      
      /// Acces to model.
      Model* getModel() const ;
      
      /// True iff the viewpoint has been initialised
      bool isInitialised() const ;
      
    protected:

      /// called during initialisation before views initialisation.
      /*!
        Default implementation does nothing. Specific viewpoint should 
        probably redefine this.
      */
      virtual void onInit() ;

      /// called during closing after views closing.
      /*!
        Default implementation does nothing. Specific viewpoint should 
        probably redefine this.
      */
      virtual void onClose() ;

      /// called when changing viewpoint observer.
      /*!
        Default implementation does nothing. Specific viewpoint should 
        probably redefine this.
      */
      virtual void onChangeObserver() ;

      /// Should i_object should have views in the viewpoint.
      /*!
        Must be redefined for specialised viewpoints. Default implementation 
        returns true.
        
        @constraint
          if !isVisible(object) 
          then 
            whatever child of object !isVisible(child)
      */
      virtual bool isVisible(Object* i_object) const ;

      /// Change model.
      void setModel(Model* i_model) ;

      /// Constructor.
      ViewPoint(Model* i_model) ;
    
      bool   m_initialised ;
      Model* m_model ;

      friend class Model ;
      friend class BaseTraitView ;
      friend class Object ;

      template <class _View> friend
      void forAll(ViewPoint*                    i_viewpoint,
                  boost::function1<void,_View*> i_operation) ;

    };


    /// Top down execution of @c i_operation on all @ _View of @c i_viewpoint.
    /*!
      i_operation is a _View -> void function
      _View is a trait view. 
    */ 
    template <class _View>
    void forAll(ViewPoint*                    i_viewpoint,
                boost::function1<void,_View*> i_operation)
    {                   
      
      TypeIdentifier         view_name(getClassTypeIdentifier(_View)) ;
      const TypeIdentifier&  trait_name(
                            Trait::getTraitName(
                              view_name,
                              getObjectTypeIdentifier(i_viewpoint))) ;

      for(std::set<Object*>::iterator object = i_viewpoint->getModel()->m_objects.begin() ;
          object != i_viewpoint->getModel()->m_objects.end() ;
          ++object)
      {
        (*object)->apply(trait_name,i_viewpoint,i_operation) ;
      }
    }
    
  }
}


#endif

