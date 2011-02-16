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
#pragma once

#include <OIS/OISMouse.h>
#include <input/implementation/input_object.h>

namespace ProjetUnivers
{
  namespace Input
  {
    namespace Implementation
    {
      namespace OIS
      {

        /// Handle mouse.
        class Mouse : public ::OIS::MouseListener, public InputObject
        {
        public:
        
          /// Constructor.
          Mouse() ;  
          
          /// Change sensibility.
          void setInGameSensibility() ;
          void setMenuSensibility() ;
          
        /*!
          @name OIS Interface implementation
        */
        // @{
        
          virtual bool mouseMoved(const ::OIS::MouseEvent&) ;
          virtual bool mousePressed(const ::OIS::MouseEvent&,::OIS::MouseButtonID) ;
          virtual bool mouseReleased(const ::OIS::MouseEvent&,::OIS::MouseButtonID) ;
  
        // @}
          
          /// Build an event from a code 
          virtual Model::PlayerConfiguration::InputEvent buildEvent(const int&) const ;

          /// Indicate the presence of a peripheral to the player configuration.
          virtual void indicatePresence(Model::PlayerConfiguration*) const ;
          
        private:
  
          /// Mouse sensibility.
          float m_sensibility ;
        };
        
      }
    }
  }
}
