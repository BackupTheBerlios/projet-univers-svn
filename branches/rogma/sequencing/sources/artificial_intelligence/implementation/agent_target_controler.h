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

#include <kernel/relation_controler.h>
#include <artificial_intelligence/implementation/ai_system.h>
#include <artificial_intelligence/implementation/agent_target.h>
#include <artificial_intelligence/implementation/agent.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {
      /// Something we will associate with a vehicle.
      class AgentTargetControler : public Kernel::RelationControler<AISystem>
      {
      protected:

        /// Set the target for the agent
        void onInit() ;

        /// Remove the target for the agent.
        void onClose() ;

      private:

        /// Access to the targeting agent
        Agent* getAgent() const ;

        /// Access to the target
        Vehicle* getTarget() const ;
      };
    }
  }
}

