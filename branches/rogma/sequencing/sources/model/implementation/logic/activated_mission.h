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
#ifndef PU_MODEL_IMPLEMENTATION_LOGIC_ACTIVATED_MISSION_H_
#define PU_MODEL_IMPLEMENTATION_LOGIC_ACTIVATED_MISSION_H_

#include <kernel/controler.h>
#include <model/duration.h>
#include <model/implementation/activated_mission.h>
#include <model/implementation/logic/logic_system.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
    namespace Implementation 
    {
      namespace Logic 
      {

        /// Load the mission.
        class ActivatedMission : public Kernel::Controler<Implementation::ActivatedMission,
                                                          LogicSystem>
        {
        public:
          
          /// Construct.
          ActivatedMission(Implementation::ActivatedMission* mission,
                           LogicSystem*                      system) ;

          void indicateGroupHasNoMoreSpawn(Kernel::Object*) ;
        
        protected:
          
          /// Load the mission.
          virtual void onInit() ;

          /// Destroy the mission.
          virtual void onClose() ;

        private:
          
          Duration m_remaining_time ;
          
        };
      }
    }
  }
}


#endif /*PU_MODEL_IMPLEMENTATION_LOGIC_ACTIVATED_MISSION_H_*/
