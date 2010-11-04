/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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

#include <enet/enet.h>
#include <kernel/trait.h>
#include <network/implementation/enet/server_object.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Implementation
    {
      namespace Enet
      {
        /// Create a message indicating an object creation
        ENetPacket* messageCreateObject(const ObjectIdentifier& parent,const ObjectIdentifier& object) ;

        /// True if the message is a create object message
        bool isMessageCreate(ENetPacket* packet) ;

        /// Get the parent identifier contained in a packet
        ObjectIdentifier decodeParentIdentifier(ENetPacket* packet) ;

        /// Get the parent identifier contained in a packet
        ObjectIdentifier decodeNewObjectIdentifier(ENetPacket* packet) ;

        /// Create a message indicating an object destruction
        ENetPacket* messageDestroyObject(const ObjectIdentifier& object) ;

        /// Create a message indicating a trait addition
        ENetPacket* messageAddTrait(const ObjectIdentifier& object,Kernel::Trait*) ;

        /// True if the message is an addTrait
        bool isMessageAddTrait(ENetPacket* packet) ;

        /// Get the object identifier contained in a packet
        ObjectIdentifier decodeObjectIdentifier(ENetPacket* packet) ;

        /// Return the trait contained in the packet
        Kernel::Trait* decodeTrait(ENetPacket* packet) ;
      }
    }
  }
}
