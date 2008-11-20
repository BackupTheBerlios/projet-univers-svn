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
#include <list>
#include <kernel/percentage.h>
#include <model/player_configuration.h>

namespace ProjetUnivers 
{
  namespace Input 
  {
    namespace Implementation 
    {

      /// Abstraction of an input system.
      class InputObject
      {
      public:
        
        /// Access to the latest key/button events.
        const std::set<Model::PlayerConfiguration::InputEvent>& getEvents() const ;
        
        /// Access to current key axes.
        const std::map<Model::PlayerConfiguration::InputAxis,
                       Kernel::Percentage>& getAxes() const ;

        /// Access to key/button pressed 
        const std::list<int>& getKeyButtonPressed() const ;

        /// Access to key/button released 
        const std::list<int>& getKeyButtonReleased() const ;
        
        /// Base classes have virtual destructor.
        virtual ~InputObject() ;
        
        /// Initialise axes.
        void initAxes() ;
        
        /// Update the time.
        virtual void update(const float& time) ;
        
        /// Build an event from a code 
        virtual Model::PlayerConfiguration::InputEvent buildEvent(const int&) const = 0 ;
        
        /// Indicate the presence of a peripheral to the player configuration.
        virtual void indicatePresence(Model::PlayerConfiguration*) const ;
        
        /// Clear the button pressed/released.
        virtual void clear() ;
        
      protected:
        
        InputObject() ;
        
        /// Current pressed keys/buttons.
        std::set<Model::PlayerConfiguration::InputEvent> m_events ;
        
        /// Current axis values.
        std::map<Model::PlayerConfiguration::InputAxis,Kernel::Percentage> m_axes ;
        
        // User event triggering
        void addInterpretedKeyButtonPressed(const int&,const Model::PlayerConfiguration::InputEvent&) ;
        void addInterpretedKeyButtonReleased(const int&,const Model::PlayerConfiguration::InputEvent&) ;
        
        /// button/key pressed/released (with auto repeat)
        std::list<int> m_interpreted_key_button_pressed ;
        std::list<int> m_interpreted_key_button_released ;
        
        // User event triggering
        void addRealKeyButtonPressed(const int&) ;
        void addRealKeyButtonReleased(const int&) ;
        
        /// real button/key pressed/released
        std::list<int> m_key_button_pressed ;
        std::list<int> m_key_button_released ;
        
        /// Time remaining to next press for each button/key
        /*!
          For auto repeat.
        */
        std::map<int,float> m_time_remaining_to_next_press ;
        
      };
    }
  }
}

#endif /*PU_INPUT_IMPLEMENTATION_INPUT_OBJECT_H_*/
