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
#ifndef PU_KERNEL_CONTROLER_H_
#define PU_KERNEL_CONTROLER_H_

#include <kernel/base_controler.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
   
    /// Abstract class for object that perform modifications. 
    /*!
      Controlers : 
      - are grouped into ControlerSet.
      - are registered onto Trait and automatically created when 
        the corresponding trait appears (like a view).
      - have a simulate method 
    */
    template <class _Trait,class _ControlerSet>  
    class Controler : public BaseControler
    {
    public:

      /// Access to object's trait viewed.     
      _Trait* getTrait() const ;
      
      /// Access to trait of type T if exists.
      template <class T> T* getTrait() const ;
      
      /// Abstract class means virtual destructor.
      virtual ~Controler() ;

      /// Access to specialised controler set.
      _ControlerSet* getControlerSet() const ;
      
    protected:

    /*!
      @name To be redefined methods
      
      Default implementation is a empty stub.
      Each specific controler should override some of these methods.
    */
    // @{
    
      /// Called after the controler is created on a initialised controler set.
      virtual void onInit() ;
      
      /// Called just before the controler is destroyed.
      virtual void onClose() ;

      /// Called when parent changed.
      virtual void onChangeParent(Object* i_old_parent) ;
      
      /// Called when the model trait has changed.
      virtual void onUpdate() ;

    // @}
      
      /// Abstract class means protected constructor.
      Controler(_Trait* i_trait,_ControlerSet* i_controler_set) ;
      
      
    };
  }
}

#include <kernel/implementation/controler.cxx>

#endif /*PU_KERNEL_CONTROLER_H_*/
