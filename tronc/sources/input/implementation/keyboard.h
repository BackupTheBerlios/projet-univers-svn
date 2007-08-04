/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
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
#ifndef PU_INPUT_IMPLEMENTATION_KEYBOARD_H_
#define PU_INPUT_IMPLEMENTATION_KEYBOARD_H_

#include <OIS/OISKeyboard.h>
#include <kernel/object.h>

namespace ProjetUnivers {
  namespace Input {

    namespace Implementation {

      /// Keyboard event handler.
      /*!
  
      */
      class Keyboard : public OIS::KeyListener
      {
      public:
      
        /// Contructor.
        Keyboard() ;  
        
        /// Change the model object that receive the commands.         
        void setControledObject(Kernel::Object*) ;

        /// Called when a key is pressed.
        virtual bool keyPressed(const OIS::KeyEvent &e) ;    
  
        /// Called when a key is released.
        virtual bool keyReleased(const OIS::KeyEvent &e) ;

        /// Destruct.
        virtual ~Keyboard() ;
      
      private:

        Kernel::Object* m_controled_object ;

      };
    }
  }
}



#endif /*PU_INPUT_IMPLEMENTATION_KEYBOARD_H_*/
