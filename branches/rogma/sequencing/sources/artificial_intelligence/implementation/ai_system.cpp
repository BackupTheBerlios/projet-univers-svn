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
#include <kernel/base_controler.h>
#include <kernel/log.h>
#include <kernel/controler_set.h>

#include <artificial_intelligence/implementation/ai_system.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Implementation
    {

      RegisterControlerSet(AISystem) ;
      
      AISystem::AISystem(Kernel::Model* model)
      : Kernel::ControlerSet(model)
      {}
      
      void AISystem::simulate(const float& seconds)
      {
        boost::function2<void,Kernel::BaseControler*,float> f 
          = &Kernel::BaseControler::simulate ;

        InternalMessage("AI","AISystem::simulate simulation") ;
        
        applyTopDown(std::bind2nd(f,seconds)) ;
      }
      
    }    
  }
}

