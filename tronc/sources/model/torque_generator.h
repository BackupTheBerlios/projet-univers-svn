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
#ifndef PU_MODEL_TORQUE_GENERATOR_H_
#define PU_MODEL_TORQUE_GENERATOR_H_
#include <OgreVector3.h>

#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {
    
    /// For objects that generate momentum.
    /*!
      Generates a torque.
      
      @todo 
        make torque a value class with conversion.
        make a single virtal function that returns this torque class.
    */
    class TorqueGenerator : public Kernel::Trait 
    {
    public:

      /// Constructor.
      TorqueGenerator() ;

      /// get the torque in newton.meter.
      virtual Ogre::Vector3 NewtonMeter() const ;
      
      /// Set the torque.
      void setNewtonMeter(const float& i_x,  
                          const float& i_y,
                          const float& i_z) ;

      /// Destructor.
      virtual ~TorqueGenerator() ;

    private:
      
      Ogre::Vector3 m_torque ; 
    };
  }
}

#endif /*PU_MODEL_TORQUE_GENERATOR_H_*/
