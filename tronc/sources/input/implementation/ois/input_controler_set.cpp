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
#include <input/implementation/input_internal.h>
#include <input/implementation/ois/keyboard.h>
#include <input/implementation/ois/mouse.h>
#include <input/implementation/ois/ois.h>
#include <input/implementation/ois/input_controler_set.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
      namespace OIS {
      
        RegisterControlerSet(InputControlerSet) ;
        
        InputControlerSet::InputControlerSet(Kernel::Model* model)
        : Kernel::ControlerSet(model)
        {}
        
        void InputControlerSet::simulate(const float& seconds)
        {
          Input::update() ;
          boost::function2<void,Kernel::BaseControler*,float> 
            f = &Kernel::BaseControler::simulate ;
          
          applyTopDown(std::bind2nd(f,seconds)) ;
          
          getMouse()->clear() ;
          getKeyboard()->clear() ;
          
        }
        
        void InputControlerSet::onInit()
        {
          OIS::init() ;
        }
  
        void InputControlerSet::onClose()
        {
          OIS::close() ;
        }

      }
    }
  }
}
