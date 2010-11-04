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
#include <kernel/controler.h>
#include <kernel/deduced_trait.h>
#include <network/implementation/enet/network_system.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Test
    {
      class TestConnection ;
    }

    namespace Implementation
    {

      class ActiveServer : public Kernel::DeducedTrait
      {};

      namespace Enet
      {
        /// An active server
        class Server : public Kernel::Controler<Implementation::ActiveServer,NetworkSystem>
        {
        public:

          /// Create an enet server
          virtual void onInit() ;

          /// Destroy the enet server
          virtual void onClose() ;

          /// Send data to the clients
          virtual void simulate(const float& seconds) ;

          ENetHost* getHost() const ;

        private:

          ENetHost* m_host ;
          ENetAddress m_address ;
          std::list<ENetPeer*> m_clients ;

          friend class ::ProjetUnivers::Network::Test::TestConnection ;
        };
      }
    }
  }
}
