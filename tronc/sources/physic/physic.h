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
#ifndef PU_PHYSIC_PHYSIC_H_
#define PU_PHYSIC_PHYSIC_H_

namespace ProjetUnivers {
  namespace Kernel
  {
    class Object ;
    class ControlerSet ;
  }
  namespace Model
  {
    class Duration ;
  }
  
  /// Physic module.
  /*!
    Handle position, forces and movements of objects. 
  */
  namespace Physic {

    /// Initialise module.
    void init() ; 
    
    /// Terminate module.
    void close() ;

    /// Creates the standard representation for the world 
    Kernel::ControlerSet* build(Kernel::Object* i_observer) ; 
    
    /// simulate physics.
    /*!
      @deprecated
    */
    void update() ;

    /// simulate physics on a certain duration.
    void update(const Model::Duration& i_duration) ;

  }
}

#endif /*PU_PHYSIC_PHYSIC_H_*/
