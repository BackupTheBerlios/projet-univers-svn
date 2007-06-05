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
#ifndef PU_KERNEL_CONTROLER_SET_H_
#define PU_KERNEL_CONTROLER_SET_H_

#include <boost/function.hpp>

namespace ProjetUnivers {
  namespace Kernel {
  
    class Model ;
    class Object ;
    class BaseControler ;
    
    /// A set of coherent controlers.
    class ControlerSet
    {
    public:

      /// Initialise the controler set.
      void init() ;

      /// Close the controler set.
      void close() ;

      /// Simulate all controlers.
      void simulate(const float& i_seconds) ;
      
      /// True iff the controler set has been initialised
      bool isInitialised() const ; 
      
      /// Abstract class means virtual destructor.
      virtual ~ControlerSet() ;

    protected:
      
      /// Should @c i_object should have controlers for that controler set.
      /*!
        Must be redefined for specialised viewpoints. Default implementation 
        returns true.
        
        @constraint
          if !isVisible(object) 
          then 
            whatever child of object !isVisible(child)
      */
      virtual bool isVisible(Object* i_object) const ;
 
      /// Apply a procedure on all controlers.
      void applyTopDown(boost::function1<void,BaseControler*> i_procedure) ;
 
      /// Apply a procedure on all controlers.
      void applyBottomUp(boost::function1<void,BaseControler*> i_procedure) ;
      
      /// Change the model.
      void setModel(Model* i_model) ;
      
      /// Abstract class means protected constructor.
      ControlerSet(Model* i_model) ;
      
      Model* m_model ;
      bool   m_initialised ;
      
      friend class Object ;
      friend class Model ;
      
    };
  }
}

#endif /*PU_KERNEL_CONTROLER_SET_H_*/
