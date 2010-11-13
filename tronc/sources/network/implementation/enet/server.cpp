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
#include <model/active.h>
#include <model/server.h>
#include <network/implementation/enet/server.h>
#include <network/implementation/enet/server_object.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Implementation
    {

      DeclareDeducedTrait(ActiveServer,And(HasTrait(Model::Server),
                                           HasTrait(Model::Active))) ;

      namespace Enet
      {

        RegisterControler(Server,Implementation::ActiveServer,NetworkSystem) ;

        /// number of milliseconds to wait for network events, corresponding to time between frames
        const unsigned int waitTime = 5 ;

        void Server::onInit()
        {
          m_address.host = ENET_HOST_ANY ;
          m_address.port = 3490 ;
          m_host = enet_host_create(&m_address,32,0,0) ;

          // @todo gracefully failure

        }

        void Server::onClose()
        {
          // number of milliseconds to wait for network events, corresponding to time between frames
          const unsigned int waitTime = 5 ;
          for(std::list<ENetPeer*>::iterator client = m_clients.begin() ; client != m_clients.end() ; ++client)
          {
            enet_peer_disconnect(*client,0) ;
            ENetEvent event ;

            // give a chance to notify clients
            while (enet_host_service(m_host,&event,waitTime) > 0)
            {}
          }

          if (m_host)
          {
            enet_host_destroy(m_host) ;
            m_host = NULL ;
          }
        }

        void Server::simulate(const float& seconds)
        {
          ENetEvent event ;

          while (enet_host_service(m_host,&event,waitTime) > 0)
          {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
              {
                m_clients.push_back(event.peer) ;
              }
              break ;
            case ENET_EVENT_TYPE_DISCONNECT:
              {
                m_clients.remove(event.peer) ;
              }
              break ;
            }
          }
        }

        ENetHost* Server::getHost() const
        {
          return m_host ;
        }

        int Server::getMappedIdentifier(Kernel::Object* object)
        {
          Implementation::ServerObject* server_object = object->getTrait<Implementation::ServerObject>() ;

          return server_object->getControler<Enet::ServerObject>(getControlerSet())->getNetworkIdentifier() ;
        }

        Kernel::ObjectReference Server::getMappedObject(Kernel::Model*,const int& identifier)
        {
          return Kernel::ObjectReference() ;
        }

      }
    }
  }
}
