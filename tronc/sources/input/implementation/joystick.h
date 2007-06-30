/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#ifndef PU_INPUT_IMPLEMENTATION_JOYSTICK_H_
#define PU_INPUT_IMPLEMENTATION_JOYSTICK_H_

#include <OISJoyStick.h>
#include <model/oriented.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      /// Handle joystick.
      /*!
        Joystick can be attached 
        - to a Model::Oriented it will then control its orientation, usefull 
          for stick control
        
        @par Status
        
        Still very preliminary. It works with my joystick but would 
        probably do not work with other.  
        
      */
      class Joystick : public OIS::JoyStickListener
      {
      public:
      
        /// Constructor.
        Joystick(const float& i_sensibility = 0.1) ;  
        
        void setTimeDelay(const float& i_seconds) ;
        
        void setControledObject(Model::Oriented*) ;
        
      /*!
        @name Interface implementation
      */
      // @{
      
        virtual bool buttonPressed(const OIS::JoyStickEvent&,int) ;
        virtual bool buttonReleased(const OIS::JoyStickEvent&,int) ;
        
        virtual bool axisMoved(const OIS::JoyStickEvent&,int) ;
        
        virtual bool sliderMoved(const OIS::JoyStickEvent&,int) ;
        
        virtual bool povMoved(const OIS::JoyStickEvent&,int) ;


      // @}
        
        /// Destructor.
        virtual ~Joystick() ;
        
      private:
        
        /// Time (in seconds) since last frame.
        float m_time_delay ;
        
        /// This joystick control the orientation of an object.
        Model::Oriented* m_controled_object ;
        
        /// sensibility.
        float m_sensibility ;
        
        /// X/Y coordinates within [-100,100].
        int X ;
        int Y ;        
        int Z ;
        
      };
    }
  }
}



#endif /*PU_INPUT_IMPLEMENTATION_JOYSTICK_H_*/
