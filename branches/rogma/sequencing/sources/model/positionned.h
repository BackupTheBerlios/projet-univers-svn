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
#include <model/position.h>

namespace ProjetUnivers 
{
  namespace Model 
  {

    /// Calculate the position of o1 relative to o2.
    Position getRelativePosition(const Kernel::Object* o1,const Kernel::Object* o2) ;

    /// For objects that have a position in space.
    /*!
      The position of the object is relative to its first positionned 
      ancestor parent or to nothing if it has none.
      
      @todo
        setPosition may change Object parentship to keep the following 
        invariant : 
        
        isInside(child,parent) <=> isDescendent(child,parent) 
       
    */
    class Positionned : public Kernel::Trait
    {
    public:

    /*!
      @name Constructors
    */
    // @{
    
      /// Constructor.
      Positionned(const Position&) ;

      /// Origin position.
      Positionned() ;
  
      /// Read a Positionned trait.
      /*!
        stored as 
        @code
          <Positionned>
            [<Positionn .../>]
          </Positionned>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;

    // @}
    /*!
      @name Access
    */
    // @{

      /// Access to position relative to its parent.
      const Position& getPosition() const ;

      /// Access to position relative to another object.
      Position getPosition(const Kernel::Object* object) const ;

    // @}
    /*!
      @name Update
    */
    // @{

      /// Change the current position.
      /*!
        @param[in] 
          i_position 
          the new position relativelly to the positionned parent 
      */
      void setPosition(const Position& i_position) ;
      
      /// Change the current position.
      /*!
        @param[in] 
          position 
          the new position relativelly to reference 
        @param[in] 
          reference 
          the reference to set the position to 
        @pre 
          reference is an ancestor of this
        @post 
          getPosition(reference) == position
      */
      void setPosition(const Position& position,
                       Kernel::Object* reference) ;


    // @}
        
    private:
      
      /// Access to position relative to an ancestor.
      /*!
        Skips any non positionned intermediate object.
      */
      Position getPositionRelativeToAncestor(const Kernel::Object* ancestor) const ;

      /// Position relative to the parent object.
      Position    m_position ;  
    
    };
  }
}
