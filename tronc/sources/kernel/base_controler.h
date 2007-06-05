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
#ifndef PU_KERNEL_BASE_CONTROLER_H_
#define PU_KERNEL_BASE_CONTROLER_H_

namespace ProjetUnivers {
  namespace Kernel {
  
    class Trait ;
    class ControlerSet ;
    class Object ;
    
    /// A controler on a trait.
    class BaseControler
    {
    public:
      
      /// Any controler does a simulation. 
      virtual void simulate(const float& i_seconds) ;

      /// Some controlers does a preparation. 
      virtual void prepare() ;
      
      /// init the controler after construction.
      void _init() ;

      /// closes the controler before destruction.
      void _close() ;

      /// abstract class means virtual destructor.
      virtual ~BaseControler() ;
      
      /// Access to object.
      Object* getObject() const ;
      
      /// Acces to controler set.
      ControlerSet* getControlerSet() const ;
      
    protected:

      /// update the controler for a change_parent. 
      void _changed_parent(Object* i_old_parent) ;
      
      /// update the controler.
      void _updated() ;

      /// Called after the controler is created.
      virtual void onInit() = 0 ;
      
      /// Called just before the controler is destroyed.
      virtual void onClose() = 0 ;

      /// Called when parent changed.
      virtual void onChangeParent(Object* i_old_parent) = 0 ;
      
      /// Called when the model trait has changed.
      virtual void onUpdate() = 0 ;

      /// abstract class means protected constructor.
      BaseControler(Trait* i_trait,ControlerSet* i_controler_set) ;
      

      bool          m_initialised ;
      Trait*        m_trait ;
      ControlerSet* m_controler_set ;

      friend class Trait ;

    };
    
  }
}
#endif /*PU_KERNEL_BASE_CONTROLER_H_*/
