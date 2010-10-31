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

#include <OgreMath.h>
#include <kernel/trait.h>
#include <kernel/reader.h>

namespace ProjetUnivers
{
  namespace Model
  {

    /// Trait of object that can observe.
    class Observer : public Kernel::Trait
    {
    public:

      /// Construct.
      Observer() ;

      /// Construct.
      void setFieldOfView(const ::Ogre::Degree&) ;

      /// Read an Observer trait.
      /*!
        stored as 
        @code
          <Observer>
            [<Angle value="50" unit="Degree"/>]
          </Observer>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;

      ::Ogre::Degree getFieldOfView() const ;

    private:

      ::Ogre::Degree m_field_of_view ;

    };
  }
}
