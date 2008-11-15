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
#include <model/player_configuration.h>
#include <input/implementation/input_internal.h>
#include <input/implementation/ois/keyboard.h>
#include <input/implementation/ois/ois.h>
#include <input/implementation/ois/player_configuration.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
      namespace OIS {
      
        RegisterControler(PlayerConfiguration,
                          EditedPlayerConfiguration,
                          InputControlerSet) ;
   
        PlayerConfiguration::PlayerConfiguration(EditedPlayerConfiguration* menu,
                                                 InputControlerSet* system)
        : Kernel::Controler<EditedPlayerConfiguration,InputControlerSet>(menu,system),
          m_recording_mode(false)
        {}
        
        void PlayerConfiguration::simulate(const float& seconds)
        {
          if (getObject()->getTrait<Model::PlayerConfiguration>()->isEventRecordingMode())
          {
            const std::set<Model::PlayerConfiguration::InputEvent>& events = getEvents() ;
            if (events.size() > 0)
            {
              getObject()->getTrait<Model::PlayerConfiguration>()
                         ->recordEvent(*events.begin()) ;
            }
          }
          else
          {
            simulateInputMenu(seconds) ;
          }
        }

        void PlayerConfiguration::update()
        {
          if (getObject()->getTrait<Model::PlayerConfiguration>()->isEventRecordingMode() &&
              !m_recording_mode)
          {
            m_recording_mode = true ;
            Input::clear() ;
          }
          else if (!getObject()->getTrait<Model::PlayerConfiguration>()->isEventRecordingMode() &&
                   m_recording_mode)
          {
            m_recording_mode = false ;
          }
        }
        
      }
    }
  }
}
