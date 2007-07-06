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
#ifndef PU_MODEL_GUIDANCE_SYSTEM_H_
#define PU_MODEL_GUIDANCE_SYSTEM_H_

#include <model/torque_generator.h>

namespace ProjetUnivers {
  namespace Model {
    
    class GuidanceControl ;
    
    /// Change direction of a ship.
    /*!
      It is a set of propellers that change an object orientation. 
        
    */
    class GuidanceSystem : public TorqueGenerator
    {
    public:

      /// Constructor.
      GuidanceSystem() ;
 
      /// get the torque in newton.meter.
      virtual Ogre::Vector3 NewtonMeter() const ;
      
      /// Update the control.
      void setControler(GuidanceControl*) ;
      
    private:
      
      /// Computer that control this system
      GuidanceControl* m_control ;
      
    };
    
    
  }
}

#endif /*PU_MODEL_GUIDANCE_SYSTEM_H_*/
