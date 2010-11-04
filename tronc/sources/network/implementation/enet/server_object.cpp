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
#include <iostream>
#include <enet/enet.h>
#include <network/implementation/enet/packet.h>
#include <network/implementation/enet/server.h>
#include <network/implementation/enet/server_object.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Implementation
    {

      DeclareDeducedTrait(ServerObject,
                          HasAncestor(HasTrait(Implementation::ActiveServer))) ;

      namespace Enet
      {

        RegisterControler(ServerObject,
                          Implementation::ServerObject,
                          NetworkSystem) ;

        ObjectIdentifier ServerObject::m_next_identifier = 1 ;

        const ObjectIdentifier& ServerObject::getNetworkIdentifier() const
        {
          return m_object_identifier ;
        }

        void ServerObject::onInit()
        {
          m_object_identifier = m_next_identifier ;
          ++m_next_identifier ;

          ENetHost* host = getAncestor<Implementation::ActiveServer>()
                           ->getControler<Server>(getControlerSet())
                           ->getHost() ;

          Implementation::ServerObject* parent = getAncestor<Implementation::ServerObject>() ;
          ObjectIdentifier parent_identifier = 0 ;
          if (parent)
            parent_identifier = parent->getControler<ServerObject>(getControlerSet())->getNetworkIdentifier() ;

          ENetPacket* packet = messageCreateObject(parent_identifier,m_object_identifier) ;
          enet_host_broadcast(host,0,packet) ;
        }

        void ServerObject::onClose()
        {
        }

      }
    }
  }
}
