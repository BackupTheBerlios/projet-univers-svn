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
#pragma once

#include <boost/function.hpp>
#include <kernel/base_trait_view.h>


namespace ProjetUnivers 
{
  namespace Kernel 
  {
    
    class ViewPoint ;
    
    
    /// A specialized trait view.
    /*!
    @par Usage

      Inherit from this class and implement :
      - onInit, called at creation
      - onClose, called before destruction
      - onUpdate, called when the _Trait model object has changed

      If one to have initialization sequencing between trait views objects,
      define views on deduced traits, initialization is performed following
      the order in formulae, i.e. if one has a view on a formula containing A,
      the view on A are initialized before.
    
    @pre
      _Trait must be a subclass of ProjetUnivers::Kernel::Trait
    
    */
    template <class _Trait,class _ViewPoint> class TraitView : public BaseTraitView
    {
    public:
    
      /// Access to object's trait viewed.     
      virtual _Trait* getTrait() const ;

      /// Access to trait of type T if exists.
      template <class T> T* getTrait() const ;
      
      /// Access to specialized viewpoint.
      _ViewPoint* getViewPoint() const ;

      /// Abstract class means virtual destructor.
      virtual ~TraitView() ;

    protected:
    
    /*!
      @name To be redefined methods
      
      Default implementation is a empty stub.
      Each specific view should override some of these methods.
    */
    // @{
    
      /// Called after the view is created on a initialized viewpoint.
      virtual void onInit() ;
      
      /// Called just before the view is destroyed.
      virtual void onClose() ;

      /// Called when parent changed.
      virtual void onChangeParent(Object* i_old_parent) ;
      
      /// Called when the model trait has changed.
      virtual void onUpdate() ;

    // @}
      
      /// Abstract class means protected constructor.
      TraitView(_Trait* i_model,_ViewPoint* i_viewpoint) ;
      TraitView() ;
      
    };
    
  }
}

#include <kernel/implementation/trait_view.cxx>

