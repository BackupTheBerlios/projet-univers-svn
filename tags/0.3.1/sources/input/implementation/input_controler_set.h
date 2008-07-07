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
#ifndef PU_INPUT_IMPLEMENTATION_INPUT_CONTROLER_SET_H_
#define PU_INPUT_IMPLEMENTATION_INPUT_CONTROLER_SET_H_

#include <kernel/controler_set.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
    
      /// Send input events to model
      class InputControlerSet : public Kernel::ControlerSet
      {
      public:
      
        /// Constructor.
        InputControlerSet(Kernel::Model*) ;
        
        /// Capture inputs and send them to objects.
        virtual void simulate(const float& seconds) ;
        
      protected:

        /// Initialise input system.
        virtual void onInit() ;

        /// Close input system.
        virtual void onClose() ;
      };
      
    }
  }
}

#endif /*PU_INPUT_IMPLEMENTATION_INPUT_CONTROLER_SET_H_*/
