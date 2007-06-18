/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#ifndef PU_MODEL_SHIP_CONTROL_H_
#define PU_MODEL_SHIP_CONTROL_H_

#include <model/torque_generator.h>
#include <model/oriented.h>

namespace ProjetUnivers {
  namespace Model {
    
    /// Change direction of a ship.
    /*!
    */
    class ShipControl : public TorqueGenerator
    {
    public:

      /// Constructor.
      ShipControl(Oriented* i_stick) ;
 
      /// get the torque in newton.meter.
      virtual Ogre::Vector3 NewtonMeter() const ;
      
    private:
      
      /// the stick 
      /*!
        it is a normalised orientation of a stick.
      */ 
      Oriented* m_stick ;
      
    };
    
    
  }
}

#endif /*PU_MODEL_SHIP_CONTROL_H_*/
