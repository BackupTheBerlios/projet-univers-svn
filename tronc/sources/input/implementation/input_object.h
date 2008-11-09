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
#ifndef PU_INPUT_IMPLEMENTATION_INPUT_OBJECT_H_
#define PU_INPUT_IMPLEMENTATION_INPUT_OBJECT_H_

#include <set>
#include <map>
#include <kernel/percentage.h>
#include <model/player_configuration.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      /// Abstraction of an input system.
      class InputObject
      {
      public:
        
        /// Access to current key events.
        const std::set<Model::PlayerConfiguration::InputEvent>& getEvents() const ;
        
        /// Access to current key axes.
        const std::map<Model::PlayerConfiguration::InputAxis,
                       Kernel::Percentage>& getAxes() const ;

        /// Base classes have virtual destructor.
        virtual ~InputObject() ;
        
        /// Initialise axes.
        void initAxes() ;
        
      protected:
        
        InputObject() ;
        
        /// Current pressed buttons.
        std::set<Model::PlayerConfiguration::InputEvent> m_events ;
        
        /// Current axis values.
        std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage> m_axes ;
        
        
      };
    }
  }
}

#endif /*PU_INPUT_IMPLEMENTATION_INPUT_OBJECT_H_*/
