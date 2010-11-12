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
#include <kernel/relation.h>
#include <kernel/serialiser.h>
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

        /// True if the message is a destroy object message
        bool isMessageDestroyObject(ENetPacket* packet) ;

        /// Create a message indicating a trait addition
        ENetPacket* messageAddTrait(const ObjectIdentifier& object,Kernel::Trait*) ;

        /// True if the message is an addTrait
        bool isMessageAddTrait(ENetPacket* packet) ;

        /// Get the object identifier contained in a packet
        ObjectIdentifier decodeObjectIdentifier(ENetPacket* packet) ;

        /// Return the trait contained in the packet
        Kernel::Trait* decodeTrait(ENetPacket* packet) ;

        /// Create a message indicating a trait destruction
        ENetPacket* messageDestroyTrait(const ObjectIdentifier& object,Kernel::Trait*) ;

        /// True if the message is a destroyTrait
        bool isMessageDestroyTrait(ENetPacket* packet) ;

        /// Return the trait to be destroyed contained in the packet
        Kernel::TypeIdentifier getTraitToBeDestroyed(ENetPacket* packet) ;

        /// Create a message indicating a trait update
        ENetPacket* messageUpdateTrait(const ObjectIdentifier& object,Kernel::Trait*) ;

        /// True if the message is an update Trait
        bool isMessageUpdateTrait(ENetPacket* packet) ;

        /// Return the trait to be updated contained in the packet
        Kernel::TypeIdentifier getTraitToBeUpdated(ENetPacket* packet) ;

        /// Apply the update of a trait.
        void updateTrait(ENetPacket* packet,Kernel::Trait*) ;

        /// Create a message indicating a trait update
        ENetPacket* messageAddRelation(const Kernel::Relation&) ;

        /// True if the message is an add relation
        bool isMessageAddRelation(ENetPacket* packet) ;

        /// Apply the adding of a relation.
        void addRelation(ENetPacket* packet,Kernel::ObjectMapper*,Kernel::Model*) ;

      }
    }
  }
}
