/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2008 Mathieu ROGER                                 *
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
#ifndef PU_INPUT_IMPLEMENTATION_OIS_MOUSE_H_
#define PU_INPUT_IMPLEMENTATION_OIS_MOUSE_H_

#include <OIS/OISMouse.h>
#include <input/implementation/input_object.h>

namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {
      namespace OIS {

        /// Handle mouse.
        class Mouse : public ::OIS::MouseListener, public InputObject
        {
        public:
        
          /// Numbering for mouse axes.
          enum MouseAxis
          {
            X = 0,
            Y = 1,
            Z = 2 
          };
          
          /// Constructor.
          Mouse() ;  
          
        /*!
          @name Interface implementation
        */
        // @{
        
          virtual bool mouseMoved(const ::OIS::MouseEvent&) ;
          virtual bool mousePressed(const ::OIS::MouseEvent&,::OIS::MouseButtonID) ;
          virtual bool mouseReleased(const ::OIS::MouseEvent&,::OIS::MouseButtonID) ;
  
        // @}
          
          const std::set< ::OIS::MouseButtonID>& getButtonPressed() const ;
          const std::set< ::OIS::MouseButtonID>& getButtonReleased() const ;
          
          void clear() ;
          
        private:
  
          
          /// Mouse sensibility.
          float m_sensibility ;
          
          std::set< ::OIS::MouseButtonID> m_button_pressed ;
          std::set< ::OIS::MouseButtonID> m_button_released ;
          
        };
        
      }
    }
  }
}



#endif /*PU_INPUT_IMPLEMENTATION_MOUSE_H_*/
