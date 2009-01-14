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
#include <kernel/reader.h>
#include <kernel/writer.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
  
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
        friend class PlayerConfiguration ;
      };
      
      /// Abstraction of an input axis
      /*!
        May be a mouse axis or a joystick axis.
      */
      class InputAxis
      {
      public:

        /// Symbolic axes.
        enum Axis
        {
          /// When not assigned
          Unassigned,
          /// Horizontal
          JoystickX,
          /// Vertical
          JoystickY,
          /// Rudder 
          JoystickRudder,
          /// Throttle
          JoystickThrottle,
          /// Horizontal
          MouseX,
          /// Vertical
          MouseY,
          /// Wheel
          MouseWheel
        };
        
        /// Negative value indicates axis inversion.
        InputAxis(int axis) ; 
        
        /// 'null' value.
        InputAxis() ;
        
        /// Go to the next
        InputAxis& operator++() ;

        /// Go to the previous
        InputAxis& operator--() ;
        
        /// Return an inverted axis.
        InputAxis operator-() const ;
        
        /// For sets.
        bool operator < (const InputAxis&) const ;

        bool operator==(const InputAxis&) const ;
        
        /// Prints the axis.
        std::string toString() const ;
        
        /// True if the axis is inversed.
        bool isInversed() const ;

        /// Access to the symbolic axis.
        int getAxis() const ;
        
      private:

        int m_axis ;
        friend class PlayerConfiguration ;
      };
      
      /*!
        @name Construction
      */
      // @{
      
      /// Construction.
      PlayerConfiguration() ;
      
      /// Tells the configuration that we have a joystick.
      void declareJoystick() ;

      /// Tells the configuration that we have a mouse.
      void declareMouse() ;
      
      /// Add a mapping between an event and a command.
      void addMapping(const InputEvent&,const std::string&) ;
      
      /// Add a mapping between an axis and a command.
      void addMapping(const InputAxis&,const std::string&) ;
      
      /// Read an PlayerConfiguration trait.
      /*!
        stored as 
        @code
          <PlayerConfiguration>
            (<Mapping command="...">
              (<Key number=""/> | 
               <JoystickX/> |
               <JoystickY/> |
               <JoystickRudder/> |
               <JoystickThrottle/> |
               <MouseX/> |
               <MouseY/> |
               <MouseZ/> |
               <JoystickButton number=""/> |
               <MouseButton number=""/>)
            </Mapping>)*
          </PlayerConfiguration>
        @endcode
      */     
      static Kernel::Trait* read(Kernel::Reader* reader) ;
      
      virtual void write(Kernel::Writer*) ;
      
    // @}
    /*!
      @name Recording
    */
    // @{
    
      /// Set the configuration in recording mode.
      void setEventRecordingMode() ;
      
      /// True iff we are in event recording mode.
      bool isEventRecordingMode() const ;
      
      /// Record the event.
      void recordEvent(const InputEvent& event) ;
      
      /// True if an event has been recorder through recordEvent call. 
      bool isEventRecorded() const ;
      
      /// Access to the latest recorded event.
      const InputEvent& getRecordedEvent() const ;
      
      /// Stop the sequence of recording.
      void stopRecording() ;
      
    // @}
    /*!
      @name Access
    */
    // @{
      
      /// True if we have a joystick
      bool hasJoystick() const ;

      /// True if we have a mouse
      bool hasMouse() const ;
      
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

    // @}
    /*!
      @name Content validation
      
    */
    // @{
      
      /// Returns the commands that are incorrects
      std::set<std::string> getViolatingCommands() const ;

      /// Returns the commands that are incorrects
      std::set<std::string> getViolatingAxes() const ;
      
    // @}
      
    private:
      
      /// Commands
      std::map<std::string,InputEvent> m_command_to_input_events ;
      
      /// Axes
      std::map<std::string,InputAxis> m_axis_to_input_axes ;
      
      /// True iff we are in recording mode.
      bool m_event_recording_mode ;
      
      /// True iff we have recorded an event.
      bool m_event_recorded ;
      
      /// Recorded event.
      InputEvent m_recorded_event ;
      
      /// True iff we have a joystick.
      bool m_has_joystick ;
      
      /// True iff we have a mouse.
      bool m_has_mouse ;
    };
        
  }
}
#endif /*PU_MODEL_PLAYER_CONFIGURATION_H_*/
