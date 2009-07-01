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
#pragma once

#include <kernel/trait_view.h>
#include <artificial_intelligence/implementation/selected_target.h>
#include <artificial_intelligence/implementation/vehicle.h>
#include <artificial_intelligence/implementation/agent_view_point.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {

      /// The selected vehicle.
      class SelectedVehicle : public Kernel::TraitView<SelectedTarget,AgentViewPoint>
      {
      public:
        
        /// Build the associated vehicle.
        virtual void onInit() ;
        
        /// Destroy the associated vehicle.
        virtual void onClose() ;
        
        /// Update the associated vehicle.
        virtual void onUpdate() ;
        
      private:

        /// True iff the target is selected            
        bool isSelected() const ;
      };
    }
  }
}
