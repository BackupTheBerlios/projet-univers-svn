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
#ifndef PU_MODEL_PLAYER_CONFIGURATION_H_
#define PU_MODEL_PLAYER_CONFIGURATION_H_

#include <map>
#include <OISKeyboard.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {
  
    /// Contains the player configuration. 
    class PlayerConfiguration : public Kernel::Trait
    {
    public:
      
      /// Abstraction of an input event
      /*!
        May be for example a key combining...
      */
      class InputEvent
      {
      public:
        
        static InputEvent joystickButton(int button) ; 
        static InputEvent mouseButton(int button) ;
        static InputEvent key(int key) ;
        
        /// 'null' value.
        InputEvent() ;
        
        /// For sets.
        bool operator < (const InputEvent&) const ;
      
        bool operator==(const InputEvent&) const ;
        
        /// Prints the event.
        std::string toString(OIS::Keyboard* keyboard) const ;
        
      private:
        
        enum Type
        {
          joystick,
          mouse,
          keyboard,
          
          /// for 'null' value
          none
        };
        
        int type ; 
        int key_or_bouton ;
      };
      
      /// Abstraction of an input axis
      /*!
        May be a mouse axis or a joystick axis.
      */
      class InputAxis
      {
      public:

        /// Negative value indicates axis inversion.
        static InputAxis joystickAxis(int axis) ; 

        /// Negative value indicates axis inversion.
        static InputAxis mouseAxis(int axis) ;

        /// 'null' value.
        InputAxis() ;
        
        /// Return an inverted axis.
        InputAxis operator-() const ;
        
        /// For sets.
        bool operator < (const InputAxis&) const ;

        bool operator==(const InputAxis&) const ;
        
        /// Prints the axis.
        std::string toString(OIS::Keyboard* keyboard) const ;
        
        /// True if the axis is inversed.
        bool isInversed() const ;

      private:

        enum Type
        {
          joystick,
          mouse,
          /// for 'null' value
          none
        };
        
        int type ; 
        int axis ;
      };
      
      /// Construction.
      PlayerConfiguration() ;
      
      void addMapping(const InputEvent&,const std::string&) ;
      void addMapping(const InputAxis&,const std::string&) ;
      
    /*!
      @name Recording
    */
    // @{
    
      /// Set the configuration in recording mode.
      void setEventRecordingMode() ;
      
      bool isEventRecordingMode() const ;
      
      /// Record the event.
      void recordEvent(const InputEvent& event) ;
      
      bool isEventRecorded() const ;
      
      /// Access to the latest recorded event.
      const InputEvent& getRecordedEvent() const ;
      
      /// Stop the sequence of recording.
      void stopRecording() ;
      
    // @}
      
      /// Returns the command associated with event.
      /*!
        @returns "" if not assigned
      */
      std::string getCommand(const InputEvent&) const ;

      /// Returns the axis associated with axis.
      /*!
        @returns "" if not assigned
      */
      std::string getAxis(const InputAxis&) const ;
      
      /// Return the event associated with a command.
      const InputEvent& getInputEvent(const std::string& command) const ;
      
      /// Return the input axis associated with an axis.
      const InputAxis& getInputAxis(const std::string& axis) const ;
      
    private:
      
      /// Commands
      std::map<InputEvent,std::string> m_input_event_to_commands ;
      /// Commands
      std::map<std::string,InputEvent> m_command_to_input_events ;
      
      /// Axes
      std::map<InputAxis,std::string> m_input_axis_to_axes ;
      /// Axes
      std::map<std::string,InputAxis> m_axis_to_input_axes ;
      
      bool m_event_recording_mode ;
      
      bool m_event_recorded ;
      
      InputEvent m_recorded_event ;
      
    };
        
  }
}
#endif /*PU_MODEL_PLAYER_CONFIGURATION_H_*/
