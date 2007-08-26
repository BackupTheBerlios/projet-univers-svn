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
#ifndef PU_MODEL_ORIENTED_H_
#define PU_MODEL_ORIENTED_H_

#include <kernel/trait.h>
#include <model/position.h>
#include <model/orientation.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that have an orientation in space.
    /*!
      The orientation of the object is relative to its first oriented 
      ancestor parent or to nothing if it has none. 
    */
    class Oriented : public Kernel::Trait
    {
    public:

    /*!
      @name Constructors
    */
    // @{
    
      /// Constructor.
      Oriented() ;

      /// Constructor.
      Oriented(const Orientation&) ;
  

    // @}
    /*!
      @name Access
    */
    // @{

      /// Access to orientation relative to its parent.
      virtual const Orientation& getOrientation() const ;

      /// Access to orientation relative to @c i_ancestor.
      /*!
        Skipps any non positionned intermediate object.
      */
      Orientation getOrientation(Kernel::Object* i_ancestor) const ;

    // @}
    /*!
      @name Update
    */
    // @{

      /// Change the current orientation.
      void setOrientation(const Orientation& i_orientation) ;

      /// Change the current orientation.
      /*!
        @param[in] 
          i_orientation 
          the new orientation relativelly to i_reference
        @post 
          getOrientation(i_reference) == i_orientation
      */
      void setOrientation(const Orientation& i_orientation,
                          Kernel::Object*    i_reference) ;

    //@}
    
    protected:

      mutable Orientation m_orientation ;

    };
  }
}

#endif /*PU_MODEL_ORIENTED_H_*/
