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
#include <kernel/controler_set.h>

namespace ProjetUnivers
{
  namespace Input
  {
    namespace Implementation
    {
      namespace OIS
      {
    
        /// Default value for autorepeat
        const float default_autorepeat_delay = 0.5 ;
        
        /// Send input events to model
        class InputControlerSet : public Kernel::ControlerSet
        {
        public:
        
          /// Constructor.
          InputControlerSet(Kernel::Model*) ;
          
          /// Called just before simulation.
          virtual void beforeSimulation(const float& seconds) ;

          /// Called just before simulation.
          virtual void afterSimulation(const float& seconds) ;
          
        protected:
  
          /// Initialize input system.
          virtual void onInit() ;
  
          /// Close input system.
          virtual void onClose() ;
        };
      }      
    }
  }
}
