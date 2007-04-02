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
#ifndef PU_KERNEL_BASE_TRAIT_VIEW_H_
#define PU_KERNEL_BASE_TRAIT_VIEW_H_

#include <kernel/object.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Kernel {
  
    class ViewPoint ;
    class Trait ;
    
    /// A view on a trait.
    class BaseTraitView
    {
    public:
      
      /// init the view after construction.
      void _init() ;

      /// closes the view before destruction.
      void _close() ;

      /// abstract class means virtual destructor.
      virtual ~BaseTraitView() ;
      
      /// Access to a view of the same object.
      template <class _View> _View* getView() const ;
      
      /// Access to object.
      Object* getObject() const ;
    
    protected:

      /// abstract class means protected constructor.
      BaseTraitView(Trait* i_trait,ViewPoint* i_viewpoint) ;

      /// Called after the view is created on a initialised viewpoint.
      virtual void onInit() = 0 ;
      
      /// Called just before the view is destroyed.
      virtual void onClose() = 0 ;

      /// Called when parent changed.
      virtual void onChangeParent(Object* i_old_parent) = 0 ;
      
      /// Called when the model trait has changed.
      virtual void onUpdate() = 0 ;

      /// update the view for a change_parent. 
      void _changed_parent(Object* i_old_parent) ;
      
      /// update the view.
      void _updated() ;

      bool initialised ;
      Trait* trait ;
      ViewPoint* viewpoint ;

      friend class Trait ;

    };
    
    template <class _View> _View* BaseTraitView::getView() const
    {
      return trait->object->getView<_View>(viewpoint) ;
    }
  }
}

#endif /*PU_KERNEL_BASE_TRAIT_VIEW_H_*/
