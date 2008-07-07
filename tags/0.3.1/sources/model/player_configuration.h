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

#include <OIS/OIS.h>
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
        
        /// For sets.
        bool operator < (const InputEvent&) const ;
      
      private:
        
        enum Type
        {
          joystick,
          mouse,
          keyboard
        };

        InputEvent() ;
        
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

        /// Return an inverted axis.
        InputAxis operator-() const ;
        
        /// For sets.
        bool operator < (const InputAxis&) const ;

      private:

        InputAxis() ;
        
        enum Type
        {
          joystick,
          mouse
        };
        
        int type ; 
        int axis ;
      };
      
      /// Construction.
      PlayerConfiguration() ;
      
      void addMapping(const InputEvent&,const std::string&) ;
      void addMapping(const InputAxis&,const std::string&) ;
      
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
      
      
    private:
      
      /// Commands
      std::map<InputEvent,std::string> m_commands ;
      
      /// Axes
      std::map<InputAxis,std::string> m_axes ;
    };
        
  }
}
#endif /*PU_MODEL_PLAYER_CONFIGURATION_H_*/
