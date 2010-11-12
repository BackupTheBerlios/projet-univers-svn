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
#include <network/implementation/enet/server_relation.h>
#include <network/implementation/enet/server_object.h>
#include <network/implementation/enet/packet.h>
#include <network/implementation/enet/server.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Implementation
    {

      DeclareDeducedRelation(ServerRelation,
                             Kernel::Relation,
                             And(IsFrom(HasTrait(ServerObject)),
                                 IsTo(HasTrait(ServerObject)))) ;

      namespace Enet
      {

        RegisterRelationControler(ServerRelation,
                                  Implementation::ServerRelation,
                                  NetworkSystem) ;

        void ServerRelation::onInit()
        {
          m_relation = NULL ;
          if (!getRelation()->isPrimitive())
          {
            std::cout << "not primitive" ;
            return ;
          }

          std::cout << "sending add relation" ;

          ENetHost* host = getObjectFrom()
                           ->getAncestor<Implementation::ActiveServer>()
                           ->getControler<Server>(getControlerSet())
                           ->getHost() ;

          ENetPacket* packet = messageAddRelation(*getRelation()) ;
          enet_host_broadcast(host,ReplicationChannel,packet) ;
        }

        void ServerRelation::onClose()
        {
          if (!m_relation)
            return ;

        }
      }
    }
  }
}
