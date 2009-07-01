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
#include <kernel/log.h>
#include <model/selected.h>
#include <artificial_intelligence/implementation/detected_vehicle.h>
#include <artificial_intelligence/implementation/selected_vehicle.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {

      RegisterView(SelectedVehicle,SelectedTarget,AgentViewPoint) ;
      
      void SelectedVehicle::onInit() 
      {
        InternalMessage("AI","entering SelectedVehicle::onInit") ;
        onUpdate() ;
        InternalMessage("AI","leaving SelectedVehicle::onInit") ;
      }
      
      void SelectedVehicle::onClose()
      {
      }
      
      void SelectedVehicle::onUpdate()
      {
        InternalMessage("AI","entering SelectedVehicle::onUpdate") ;
        if (isSelected())
        {
          DetectedVehicle* detected = getView<DetectedVehicle>() ;
          if (detected)
          {
            InternalMessage("AI","SelectedVehicle::onUpdate#1") ;
            getViewPoint()->setTarget(detected->getVehicle()) ;
          }
        }
        InternalMessage("AI","leaving SelectedVehicle::onUpdate") ;
      }

      bool SelectedVehicle::isSelected() const
      {
        return getObject()->getTrait<Model::Selected>()
                          ->isSelected(getViewPoint()->getTargetingSystem()) ;
      }          
      
    }
  }
}
