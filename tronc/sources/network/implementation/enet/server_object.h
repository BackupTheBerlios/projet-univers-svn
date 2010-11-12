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
    namespace Implementation
    {

      class ServerObject : public Kernel::DeducedTrait
      {};

      namespace Enet
      {

        /// The channel for objetc replication
        extern const enet_uint8 ReplicationChannel ;

        /// An object server side that need replication on clients
        class ServerObject : public Kernel::Controler<Implementation::ServerObject,
                                                      NetworkSystem>
        {
        public:

          /// Send create message to all clients
          virtual void onInit() ;

          /// Send destroy message to all clients
          virtual void onClose() ;

          /// The object network identifier
          const ObjectIdentifier& getNetworkIdentifier() const ;

        private:

          /// object global identifier
          ObjectIdentifier m_object_identifier ;
        };
      }
    }
  }
}
