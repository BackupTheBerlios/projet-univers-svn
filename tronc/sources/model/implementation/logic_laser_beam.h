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
#ifndef PU_MODEL_IMPLEMENTATION_LOGIC_LASER_BEAM_H_
#define PU_MODEL_IMPLEMENTATION_LOGIC_LASER_BEAM_H_

#include <kernel/controler.h>
#include <model/laser_beam.h>
#include <model/implementation/logic_system.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
        
      /// Makes laser beam disappear after a certain amount of time.
      class LogicLaserBeam : public Kernel::Controler<Model::LaserBeam,
                                                     LogicSystem>
      {
      public:
        
        /// Construct.
        LogicLaserBeam(Model::LaserBeam* i_object,
                       LogicSystem*      i_system) ;
      
        /// Simulate world during a certain duration and notify positions.
        void simulate(const float& i_seconds) ;
      
      private:
        
        /// Time remaining before disappearing in seconds)
        float m_seconds_remaining ;
      };
    }
  }
}


#endif
