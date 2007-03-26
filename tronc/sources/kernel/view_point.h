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
#ifndef PU_KERNEL_VIEW_POINT_H_
#define PU_KERNEL_VIEW_POINT_H_


namespace ProjetUnivers {
  namespace Kernel {
    
    class Model ;
    class Trait ;
    class Object ;
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

      /// Constructor.
      ViewPoint(Model* i_model) ;
    
      bool initialised ;
      Model* model ;

      friend class Model ;
      friend class BaseTraitView ;
      friend class Object ;
    };

    
  }
}


#endif

