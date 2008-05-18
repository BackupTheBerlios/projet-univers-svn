/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#ifndef PU_DISPLAY_DISPLAY_H_
#define PU_DISPLAY_DISPLAY_H_

#include <kernel/object.h>
#include <kernel/view_point.h>

namespace ProjetUnivers {
 
  /// 3D display of Model objects.
  /*!
    It is the Model's view responsible for graphic display. This module :
    - has the screen and the ogre Root
    - has view points having scene manager
    - some are displayed (the active ones) others are maintained but not 
      displayed. 
  */ 
  namespace Display {
    
    /// Module initialisation.
    bool init(bool choose_display = true) ;
    
    /// Module closing.
    void close() ;
  
    /// Creates the standard representation for the world 
    Kernel::ViewPoint* buildRealWorldViewPoint(Kernel::Object* i_observer) ; 
    
    /// Update display
    void update() ;
    
  }
  
}



#endif //PU_DISPLAY_DISPLAY_H_
