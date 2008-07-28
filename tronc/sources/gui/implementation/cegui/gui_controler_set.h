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
#ifndef PU_GUI_IMPLEMENTATION_CEGUI_GUI_CONTROLER_SET_H_
#define PU_GUI_IMPLEMENTATION_CEGUI_GUI_CONTROLER_SET_H_

#include <kernel/controler_set.h>

namespace ProjetUnivers {
  namespace GUI {
    namespace Implementation {
      namespace CEGUI {
      
        /// Controler set for all GUIs.
        class GUIControlerSet : public Kernel::ControlerSet
        {
        public:
          
          /// Construction.
          GUIControlerSet(Kernel::Model*) ;
        
          /// Init the module on demand.
          virtual void onInit() ;
  
          /// Simulate all controlers.
          virtual void simulate(const float& seconds) ;
          
        };
      }      
    }
  }
}

#endif /*PU_GUI_IMPLEMENTATION_CEGUI_GUI_CONTROLER_SET_H_*/
