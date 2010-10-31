/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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
#ifndef PU_MODEL_SIZED_H_
#define PU_MODEL_SIZED_H_

#include <kernel/trait.h>
#include <kernel/reader.h>
#include <model/distance.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that have a size.
    /*!
      Used in conjunction with Positioned to determine isInside.
      @todo StellarSystem inherit from it...
    */
    class Sized : public Kernel::Trait
    {
    public:

    /*!
      @name Constructors
    */
    // @{
    
      /// Constructor.
      Sized(const Distance&) ;

    // @}
    /*!
      @name Access
    */
    // @{

      /// Access to object radius.
      const Distance& getRadius() const ;

    // @}
        
    private:
      
      Distance m_radius ;  
    
    };
  }
}

#endif 
