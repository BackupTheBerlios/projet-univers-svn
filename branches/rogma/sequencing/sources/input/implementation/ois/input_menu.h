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
#ifndef PU_INPUT_IMPLEMENTATION_OIS_INPUT_MENU_H_
#define PU_INPUT_IMPLEMENTATION_OIS_INPUT_MENU_H_

#include <kernel/percentage.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
      namespace OIS {
      
        /// Common Menu input control.
        class InputMenu
        {
        public:
          
          /// Send commands to menu. 
          void simulateInputMenu(const float& seconds) ;
        
          void initInputMenu() ;
          void closeInputMenu() ;
          
        private:
          
          Kernel::Percentage m_mouse_x ;
          Kernel::Percentage m_mouse_y ;
          Kernel::Percentage m_mouse_z ;
          
          static int m_number_of_active_menus ;
        };
      }      
    }
  }
}


#endif /*PU_INPUT_IMPLEMENTATION_OIS_INPUT_MENU_H_*/
