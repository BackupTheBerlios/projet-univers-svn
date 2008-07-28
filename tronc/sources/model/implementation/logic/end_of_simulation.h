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
#ifndef PU_MODEL_IMPLEMENTATION_LOGIC_END_OF_SIMULATION_H_
#define PU_MODEL_IMPLEMENTATION_LOGIC_END_OF_SIMULATION_H_

#include <kernel/controler.h>
#include <model/implementation/logic/activated_end_of_simulation.h>
#include <model/implementation/logic/logic_system.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {

        /// Delete all objects od the model.
        class EndOfSimulation : public Kernel::Controler<ActivatedEndOfSimulation,
                                                         LogicSystem>
        {
        public:
          
          /// Construct.
          EndOfSimulation(ActivatedEndOfSimulation* object,
                          LogicSystem*              system) ;
        
        
        protected:
          
          /// Destroy all model roots.
          virtual void onInit() ;
        
        };
      }
    }
  }
}


#endif /*PU_MODEL_IMPLEMENTATION_LOGIC_END_OF_SIMULATION_H_*/
