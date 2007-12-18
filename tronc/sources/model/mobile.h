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
#ifndef PU_MODEL_MOBILE_H_
#define PU_MODEL_MOBILE_H_

#include <kernel/trait.h>
#include <kernel/reader.h>
#include <model/speed.h>
#include <model/angular_speed.h>

namespace ProjetUnivers {
  namespace Model {

    /// For objects that move relativly to their parent.
    /*!
      Any speed is relative to the parent physical world.
      
      @todo
        change the spec because physical world is going to move to physic
    */
    class Mobile : public Kernel::Trait
    {
    public:

    /*!
      @name Construction
    */
    // @{

      /// Construct.
      Mobile() ;

      /// Construct with initial linear speed.
      Mobile(const Speed& speed) ;

      /// Read a Mobile trait.
      /*!
        stored as 
          <Mobile>
            [<Speed .../>]
            [<AngularSpeed />]
          </Mobile>
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      /// Set the linear speed.
      void setSpeed(const Speed& i_new_speed) ;
      
      /// Set the angular speed.
      void setAngularSpeed(const AngularSpeed& i_new_angular_speed) ;

    // @}
    /*!
      @name Access
    */
    // @{

      /// Acces to linear speed.
      const Speed& getSpeed() const ;
      
      /// Access to angular speed.
      const AngularSpeed& getAngularSpeed() const ;

    // @}
      
    protected:
      
      /// Linear speed
      Speed        m_speed ;
      
      /// Angular speed
      AngularSpeed m_angular_speed ;
      
    };
  }
}

#endif 
