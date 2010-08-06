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

#include <kernel/reader.h>

#include <model/force_generator.h>

namespace ProjetUnivers
{
  namespace Model
  {
    
    /// Resist movement.
    /*!
      Same as Stabilizer but for linear movement.
    */
    class Dragger : public ForceGenerator
    {
    public:

      /// Constructor.
      Dragger(const float & i_dragg) ;

      /// Read a Dragger trait.
      /*!
        stored as 
        @code
          <Dragger dragg_factor=".."/>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
 
      /// Get the force.
      virtual Force getAppliedForce() const ;
    
    private:
      
      float m_dragg_factor ;
    };
    
    
  }
}
