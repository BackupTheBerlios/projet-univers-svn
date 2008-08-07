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
#include <model/implementation/logic/end_of_simulation.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {


        RegisterControler(EndOfSimulation, 
                          ActivatedEndOfSimulation, 
                          LogicSystem) ;

        EndOfSimulation::EndOfSimulation(ActivatedEndOfSimulation* object,
                                         LogicSystem*              system)
        : Kernel::Controler<ActivatedEndOfSimulation,
                            LogicSystem>(object,system)
        {}
      
        
        void EndOfSimulation::onInit()
        {
          const std::set<Kernel::Object*>& roots = getTrait()->getObject()
                                                   ->getModel()->getRoots() ;
          for(std::set<Kernel::Object*>::const_iterator root = roots.begin() ; 
              root != roots.end() ;
              ++root)
            
            getControlerSet()->addObjectToDestroy(*root) ;
        }
      }
    }
  }
}

