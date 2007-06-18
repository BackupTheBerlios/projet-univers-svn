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
#ifndef PU_INPUT_INPUT_H_
#define PU_INPUT_INPUT_H_

#include <kernel/object.h>

namespace ProjetUnivers {

  /// Input management
  /*!
  */
  namespace Input {
   
    /// Intitialize.
    void init() ;
   
    /// Terminate.
    void close() ;
    
    /// Build an input system relative to @c i_object.
    void build(Kernel::Object* i_object) ;
    
    
    /// Capture input and update. 
    /*!
      @param[in] i_seconds time in seconds since last frame. 
    */
    void update(const float& i_seconds) ;
   
    
  }
}

#endif
