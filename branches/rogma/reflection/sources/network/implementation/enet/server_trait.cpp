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
#include <network/implementation/enet/server_trait.h>
#include <network/implementation/enet/server_object.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Implementation
    {

      namespace Enet
      {

        RegisterControler(ServerTrait,
                          Kernel::Trait,
                          NetworkSystem) ;

        void ServerTrait::onInit()
        {
          m_trait = NULL ;

          // not an error
          if (!getTrait()->isPrimitive())
            return ;

          Implementation::ActiveServer* server = getAncestor<Implementation::ActiveServer>() ;

          // not an error
          if (!server)
            return ;

          Implementation::ServerObject* object = getTrait<Implementation::ServerObject>() ;

          if (!object)
          {
            ErrorMessage("no server object !!") ;
            return ;
          }

          Enet::ServerObject* server_object = object->getControler<Enet::ServerObject>(getControlerSet()) ;

          if (!server_object)
          {
            ErrorMessage("no server object controler !!") ;
            return ;
          }

          m_trait = getTrait() ;

          ObjectIdentifier identifier = server_object->getNetworkIdentifier() ;

          ENetHost* host = server->getControler<Server>(getControlerSet())->getHost() ;

          ENetPacket* packet = messageAddTrait(identifier,m_trait) ;
          enet_host_broadcast(host,0,packet) ;
        }

        void ServerTrait::onClose()
        {
          if (!m_trait)
            return ;
        }

      }
    }
  }
}
