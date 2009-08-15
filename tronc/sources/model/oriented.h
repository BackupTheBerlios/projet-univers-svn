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
#pragma once

#include <kernel/trait.h>
#include <kernel/reader.h>
#include <kernel/deduced_trait.h>
#include <model/position.h>
#include <model/orientation.h>

namespace ProjetUnivers
{
  namespace Model
  {

    
    /// Calculate the orientation of o1 relative to o2.
    Orientation getRelativeOrientation(const Kernel::Object* o1,const Kernel::Object* o2) ;
    
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
  
      /// Read an Oriented trait.
      /*!
        stored as 
        @code
          <Oriented>
            [<Orientation .../>]
          </Oriented>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;

    // @}
    /*!
      @name Access
    */
    // @{

      /// Access to orientation relative to its parent.
      virtual const Orientation& getOrientation() const ;

      /// Access to orientation relative to @c object.
      /*!
        Skips any non positionned intermediate object.
      */
      Orientation getOrientation(const Kernel::Object* object) const ;

    // @}
    /*!
      @name Update
    */
    // @{

      /// Change the current orientation.
      void setOrientation(const Orientation& orientation) ;

      /// Change the current orientation.
      /*!
        @param[in] 
          orientation 
          the new orientation relativelly to @c reference
        @param[in] 
          reference
          the reference to which we set the orientation 
        @post 
          getOrientation(reference) == orientation
      */
      void setOrientation(const Orientation& orientation,
                          Kernel::Object*    reference) ;

    //@}
    
    protected:

      /// Access to orientation relative to an ancestor.
      /*!
        Skips any non oriented intermediate object.
        @pre @c ancestor is an ancestor of this
      */
      Orientation getOrientationRelativeToAncestor(const Kernel::Object* ancestor) const ;
      
      mutable Orientation m_orientation ;

    };

    /// For objects that have a global orientation
    class RecursivelyOriented : public Kernel::DeducedTrait
    {};

  }
}
