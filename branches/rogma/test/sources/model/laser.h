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
#ifndef PU_MODEL_LASER_H_
#define PU_MODEL_LASER_H_

#include <kernel/trait.h>
#include <kernel/reader.h>

#include <model/position.h>
#include <model/orientation.h>
#include <model/duration.h>
#include <model/energy.h>


namespace ProjetUnivers {
  namespace Model {
    
    /// For objects that are laser weapons.
    /*!
      @todo parametrize initial speed.
    */
    class Laser : public Kernel::Trait
    {
    public:
      
      /// Constructor.
      Laser(const Position&    out_position,
            const Orientation& out_orientation,
            const Energy&      beam_energy) ;

      /// Set the time between shots.
      void setShotTimeDelay(const Duration&) ;
      
      /// Remove some time to the next shot.
      void removeTimeToNextShot(const Duration&) ;
      
      /// Change laser orientation.
      void setOrientation(const Orientation&) ;
      
      /// Read a Laser trait.
      /*!
        stored as 
        @code
          <Laser>
            <Position .../>
            <Orientation .../>
            <Energy .../>
          </Laser>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
    
      /// Fire action.
      void fire() ;
    
      /// Gives the speed of the laser "bullet".
      float getLaserSpeedMeterPerSecond() const ;
      
      /// Access to the out position of the laser.
      const Position& getOutPosition() const ;

      /// Access to the out orientation of the laser.
      const Orientation& getOutOrientation() const ;
      
      /// Acces to the life duration of the beam produced.
      Duration getLaserBeamLifeDuration() const ;
      
    private:
      
      /// the position of the "output" relative to the laser
      Position    m_out_position ;
      
      /// the orientation of the output relative to the laser
      Orientation m_out_orientation ;
      
      /// The energy of the produced laser beam.
      Energy      m_laser_beam_energy ;

      /// Time between shots.
      Duration    m_time_between_shots ;
      
      
      /// Time remaining to be able to fire.
      Duration    m_time_to_fire ;
    };
  }
}

#endif /*PU_MODEL_LASER_H_*/
