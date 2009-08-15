/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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

#include <kernel/object_reference.h>
#include <kernel/trait.h>
#include <kernel/reader.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
      
    /// Calculate where one should fire.
    class ShootingHelper : public Kernel::Trait
    {
    public:
    
    /*!
      @name Construction
    */
    // @{
    
      /// Constructs.
      ShootingHelper() ;

      /// Connect a shooting helper to a computer.
      static void connect(Kernel::Object* shooting_helper,
                          Kernel::Object* computer,
                          Kernel::Object* laser) ;

      /// Read a ShootingHelper trait.
      /*!
        stored as 
        @code
          <ShootingHelper>
            [<ObjectReference ... name="computer"/>]
            [<ObjectReference ... name="laser"/>]
          </ShootingHelper>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
    // @}  
      
      /// Access to Computer.
      Kernel::Object* getComputer() const ;

      /// Access to Laser.
      Kernel::Object* getLaser() const ;
      
    private:
      
      /// The laser.
      Kernel::ObjectReference m_laser ;
      
    };
  }
}
