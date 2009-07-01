/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

#include <memory>
#include <kernel/controler.h>
#include <artificial_intelligence/implementation/ai_system.h>
#include <artificial_intelligence/implementation/with_vehicle.h>
#include <artificial_intelligence/implementation/vehicle.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {
      /// Something we will associate with a vehicle.
      class WithVehicleControler : public Kernel::Controler<WithVehicle,
                                                            AISystem>
      {
      public:

        /// Access to vehicle.
        Vehicle* getVehicle() const ;

      protected:

        /// Create a vehicle
        void onInit() ;

        /// Destroy the vehicle.
        void onClose() ;

        /// Update position etc...
        void onUpdate() ;

      private:

        /// Simplified access functions.
        Ogre::Vector3 getPosition() const ;
        Ogre::Vector3 getSpeed() const ;
        Ogre::Quaternion getOrientation() const ;
        float getSize() const ;

        std::auto_ptr<Vehicle> m_vehicle ;

      };
    }
  }
}
