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
#ifndef PU_INPUT_INPUT_LISTENER_H_
#define PU_INPUT_INPUT_LISTENER_H_

namespace ProjetUnivers 
{
  namespace Input 
  {
    
    /// Interface for objects that receive input.
    /*!
      Mainly used to register a GUI system.
    */
    class InputListener
    {
    public:
      
      /// Inject KeyPressed event.
      virtual void injectKeyPressed(int key_code) = 0 ;
      
      /// Inject KeyReleased event.
      virtual void injectKeyReleased(int key_code) = 0 ;
      
      /// Inject the char corresponding to key pressed
      virtual void injectChar(unsigned int key_char) = 0 ;
      
      /// Inject mouse position.
      virtual void injectMousePosition(int x,int y, int z) = 0 ;

      /// Inject MousePressed event.
      virtual void injectMousePressed(int button) = 0 ;

      /// Inject MouseReleased event.
      virtual void injectMouseReleased(int button) = 0 ;
      
      /// Abstract class.
      virtual ~InputListener() ;
      
    protected:
      
      /// Abstract class.
      InputListener() ;
    };
  }
}

#endif /*PU_INPUT_INPUT_LISTENER_H_*/
