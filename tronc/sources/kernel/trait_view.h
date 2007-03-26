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
#ifndef PU_KERNEL_VUE_H_
#define PU_KERNEL_VUE_H_


#include <kernel/base_trait_view.h>


namespace ProjetUnivers {
  namespace Kernel {
    
    class ViewPoint ;
    
    
    /// A specialised trait view.
    /*!
    @par Usage

      Inherit from this class and implement :
      - init, called at creation
      - close, called before destruction
      - update, called when the _Trait model object has changed

      If one to have initialisation sequencement between trait views of an 
      object, call the init of another trait view (calling twice init does 
      only one). 
    
    @pre
      _Trait must be a subclass of ProjetUnivers::Kernel::Trait
    
    */
    template <class _Trait,class _ViewPoint> class TraitView : public BaseTraitView
    {
    protected:
    
    /*!
      @name To be redefined methods
      
      Default implementation is a empty stub.
      Each specific view should override some of these methods.
    */
    // @{
    
      /// Called after the view is created on a initialised viewpoint.
      virtual void onInit() ;
      
      /// Called just before the view is destroyed.
      virtual void onClose() ;

      /// Called when parent changed.
      virtual void onChangeParent(Object* i_old_parent) ;
      
      /// Called when the model trait has changed.
      virtual void onUpdate() ;

    // @}
    public:
    
      /// To have typed model.     
      virtual _Trait* getModel() const ;

      /// Abstract class means virtual destructor.
      virtual ~TraitView() ;
    
      /// Access to specialised viewpoint.
      _ViewPoint* getViewPoint() const ;
      
    protected:    
      /// Abstract class means protected constructor.
      TraitView(_Trait* i_model,_ViewPoint* i_viewpoint) ;
      
    };
    
  }
}

#include <kernel/implementation/trait_view.cxx>


#endif

