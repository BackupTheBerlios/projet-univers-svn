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
#include <model/disconnected.h>
#include <model/connected.h>
#include <model/connecting.h>
#include <model/client.h>
#include <network/implementation/enet/packet.h>
#include <network/implementation/enet/client.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Implementation
    {

      DeclareDeducedTrait(Client,And(HasTrait(Model::Client),
                                     Not(HasTrait(Model::Disconnected)))) ;

      namespace Enet
      {

        RegisterControler(Client,Implementation::Client,NetworkSystem) ;

        const unsigned int numberOfChannels = 2 ;
        /// number of milliseconds to wait for network events, corresponding to time between frames
        const unsigned int waitTime = 5 ;

        void Client::onInit()
        {
          m_host = enet_host_create(0,1,0,0) ;
          enet_address_set_host(&m_address,getTrait<Model::Client>()->getAddress().c_str()) ;
          m_address.port = 3490 ;
          m_peer = enet_host_connect(m_host,&m_address,numberOfChannels) ;

          // by convention
          m_objects[0] = getObject() ;

          // @todo m_peer == NULL
        }

        void Client::onClose()
        {
          enet_peer_disconnect(m_peer,0) ;

          ENetEvent event ;

          // give a chance to notify server
          while (enet_host_service(m_host,&event,waitTime) > 0)
          {}
        }

        void Client::simulate(const float& seconds)
        {
          ENetEvent event ;

          while (enet_host_service(m_host,&event,waitTime) > 0)
          {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
              {
                getObject()->addTrait(new Model::Connected()) ;
                Model::Connecting* connecting = getObject()->getTrait<Model::Connecting>() ;
                if (connecting)
                  getObject()->destroyTrait(connecting) ;
              }
              break ;
            case ENET_EVENT_TYPE_DISCONNECT:
              {
                Model::Connecting* connecting = getObject()->getTrait<Model::Connecting>() ;
                if (connecting)
                  getObject()->destroyTrait(connecting) ;
                Model::Connected* connected = getObject()->getTrait<Model::Connected>() ;
                if (connected)
                  getObject()->destroyTrait(connected) ;
              }
              break ;
            case ENET_EVENT_TYPE_RECEIVE:
              {
                ENetPacket* packet = event.packet ;
                if (isMessageCreate(packet))
                {
                  ObjectIdentifier parent = decodeParentIdentifier(packet) ;
                  ObjectIdentifier object = decodeNewObjectIdentifier(packet) ;
                  Kernel::Object* new_object = getNetworkObject(parent)->createObject() ;
                  m_objects[object] = new_object ;
                }
                else if (isMessageAddTrait(packet))
                {
                  getNetworkObject(decodeObjectIdentifier(packet))->addTrait(decodeTrait(packet)) ;
                }
              }
              break ;
            }
          }
        }

        Kernel::Object* Client::getNetworkObject(const ObjectIdentifier& identifier) const
        {
          std::map<ObjectIdentifier,Kernel::ObjectReference>::const_iterator finder = m_objects.find(identifier) ;

          CHECK(finder != m_objects.end(),"unexisting identifier") ;

          return finder->second ;
        }
      }
    }
  }
}
