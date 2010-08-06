/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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

    /// For objects that are a throttle.
    /*!
      Throttle have exactly one axis. Value ranges in [-100,100].  
      usage : 
        getOrientation().getPitch()
      @invariant getOrientation().getPitch() in [0,90°].
    */
    class Throttle : public Oriented
    {
    public:
    /*!
      @name Operations Names

      Meant to be called on Object, @see Object::call().
    */
    // @{

      static std::string ChangeThrottle ;
      static std::string SetThrottle ;

    // @}
    
      /// Constructor.
      Throttle() ;

      /// Read a Throttle trait.
      /*!
        stored as <Throttle [y="..."]/>
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;

      /// Modify the pitch.
      void modify(const int& delta) ;

      /// Set the throttle.
      /*!
        Passed value is in [-100,100].
      */
      void set(const int& throttle) ;
    
    private:

      /// Current value in [-100,100].
      int m_y ;
    };
  }
}
