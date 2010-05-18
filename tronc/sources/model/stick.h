/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

#include <kernel/reader.h>
#include <model/oriented.h>

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Test
    {
      class TestGuidanceControl ;
    }

    /// For objects that are a stick.
    /*!
      Right is positive X axis
      up is positive y axis
      z axis is for roll
    */
    class Stick : public Oriented
    {
    public:
    /*!
      @name Operations Names

      Meant to be called on Object, @see Object::call().
    */
    // @{

      static std::string Yaw ;
      static std::string Pitch ;
      static std::string Roll ;

    // @}

      /// Constructor.
      Stick() ;

      /// Read a Stick trait.
      /*!
        stored as
        @code
          <Stick/>
        @endcode
      */
      static Kernel::Trait* read(Kernel::Reader* reader) ;

      /// Access redefinition.
      virtual const Orientation& getOrientation() const ;

      friend class ::ProjetUnivers::Model::Test::TestGuidanceControl ;
    };
  }
}
