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
#ifndef PU_MODEL_PLAYER_H_
#define PU_MODEL_PLAYER_H_

#include <kernel/object.h>
#include <kernel/object_reference.h>
#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {
  
    /// Indicate that the object is the player.
    class Player : public Kernel::Trait
    {
    public:
      
      /// Construction.
      Player() ;
      
      /// Relate a player to its configuration.
      static void connect(Kernel::Object* player,Kernel::Object* configuration) ;
      
      /// Access to configuration.
      Kernel::Object* getConfiguration() const ;
    
    private:
      
      /// Player configuration.
      Kernel::ObjectReference m_configuration ;
      
    };
        
  }
}
#endif /*PU_MODEL_PLAYER_H_*/
