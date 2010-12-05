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
#include <kernel/text_serialiser.h>
#include <kernel/string.h>
#include <network/implementation/enet/packet.h>

namespace ProjetUnivers
{
  namespace Network
  {
    namespace Implementation
    {
      namespace Enet
      {

        ENetPacket* messageCreateObject(const ObjectIdentifier& parent,const ObjectIdentifier& object)
        {
          std::string content("c") ;
          content += Kernel::toString(parent) ;
          content += "," ;
          content += Kernel::toString(object) ;

          return enet_packet_create(content.c_str(),content.length(),ENET_PACKET_FLAG_RELIABLE) ;
        }

        bool isMessageCreate(ENetPacket* packet)
        {
          return packet->data[0] == 'c' ;
        }

        ObjectIdentifier decodeParentIdentifier(ENetPacket* packet)
        {
          return decodeObjectIdentifier(packet) ;
        }

        ObjectIdentifier decodeNewObjectIdentifier(ENetPacket* packet)
        {
          std::string content ;
          content.assign((const char*)packet->data,packet->dataLength) ;
          std::string::size_type begin = content.find(',') + 1 ;
          std::string::size_type end = content.find_first_not_of("0123456789",begin) ;
          std::string value = content.substr(begin,end-begin) ;

          return atoi(value.c_str()) ;
        }

        ENetPacket* messageAddTrait(const ObjectIdentifier& object,Kernel::Trait* trait)
        {
          Kernel::TextSerialiser serialiser ;
          std::string content("a") ;
          content += Kernel::toString(object) ;
          content += serialiser.serialiseTrait(*trait) ;
          return enet_packet_create(content.c_str(),content.length(),ENET_PACKET_FLAG_RELIABLE) ;
        }

        bool isMessageAddTrait(ENetPacket* packet)
        {
          return packet->data[0] == 'a' ;
        }

        ObjectIdentifier decodeObjectIdentifier(ENetPacket* packet)
        {
          std::string content ;
          content.assign((const char*)packet->data,packet->dataLength) ;

          std::string::size_type temp = content.find_first_not_of("0123456789",1) ;
          std::string value = content.substr(1,temp-1) ;

          return atoi(value.c_str()) ;
        }

        Kernel::Trait* decodeTrait(ENetPacket* packet,Kernel::Model* model)
        {
          std::string content ;
          content.assign((const char*)packet->data,packet->dataLength) ;
          std::string::size_type temp = content.find_first_not_of("0123456789",1) ;
          content = content.substr(temp) ;

          Kernel::TextSerialiser serialiser ;
          Kernel::Trait* result = serialiser.deserialiseTrait(content,model) ;

          return result ;
        }

        ENetPacket* messageDestroyObject(const ObjectIdentifier& object)
        {
          std::string content("d") ;
          content += Kernel::toString(object) ;

          return enet_packet_create(content.c_str(),content.length(),ENET_PACKET_FLAG_RELIABLE) ;
        }

        bool isMessageDestroyObject(ENetPacket* packet)
        {
          return packet->data[0] == 'd' ;
        }

        ENetPacket* messageDestroyTrait(const ObjectIdentifier& object,Kernel::Trait* trait)
        {
          std::string content("t") ;
          content += Kernel::toString(object) ;
          content += "ProjetUnivers::" ;
          content += getObjectTypeIdentifier(trait).fullName() ;

          return enet_packet_create(content.c_str(),content.length(),ENET_PACKET_FLAG_RELIABLE) ;
        }

        bool isMessageDestroyTrait(ENetPacket* packet)
        {
          return packet->data[0] == 't' ;
        }

        Kernel::TypeIdentifier getTraitToBeDestroyed(ENetPacket* packet)
        {
          std::string content ;
          content.assign((const char*)packet->data,packet->dataLength) ;

          std::string::size_type begin = content.find_first_not_of("0123456789",1) ;

          const std::string& trait_name = content.substr(begin) ;

          return Kernel::TypeIdentifier(trait_name) ;
        }

        ENetPacket* messageUpdateTrait(const ObjectIdentifier& object,Kernel::Trait* trait)
        {
          Kernel::TextSerialiser serialiser ;
          std::string content("u") ;
          content += Kernel::toString(object) ;
          content += serialiser.serialiseTrait(*trait) ;
          return enet_packet_create(content.c_str(),content.length(),ENET_PACKET_FLAG_RELIABLE) ;
        }

        bool isMessageUpdateTrait(ENetPacket* packet)
        {
          return packet->data[0] == 'u' ;
        }

        void updateTrait(ENetPacket* packet,Kernel::Trait* trait)
        {
          std::string content ;
          content.assign((const char*)packet->data,packet->dataLength) ;
          std::string::size_type temp = content.find_first_not_of("0123456789",1) ;
          content = content.substr(temp) ;

          Kernel::TextSerialiser serialiser ;
          serialiser.deserialiseTrait(content,trait) ;
        }

        Kernel::TypeIdentifier getTraitToBeUpdated(ENetPacket* packet)
        {
          std::string content ;
          content.assign((const char*)packet->data,packet->dataLength) ;

          std::string::size_type begin = content.find_first_not_of("0123456789",1) ;
          std::string::size_type end = content.find('(',begin) ;

          const std::string& trait_name = content.substr(begin,end-begin) ;

          return Kernel::TypeIdentifier(trait_name) ;
        }

        ENetPacket* messageAddRelation(const Kernel::Relation& relation,NetworkMapper* mapper)
        {
          Kernel::TextSerialiser serialiser(mapper) ;
          std::string content("r") ;
          content += serialiser.serialiseRelation(relation) ;
          return enet_packet_create(content.c_str(),content.length(),ENET_PACKET_FLAG_RELIABLE) ;
        }

        bool isMessageAddRelation(ENetPacket* packet)
        {
          return packet->data[0] == 'r' ;
        }

        void addRelation(ENetPacket* packet,NetworkMapper* mapper,Kernel::Model* model)
        {
          std::string content ;
          content.assign((const char*)packet->data,packet->dataLength) ;

          Kernel::TextSerialiser serialiser(mapper) ;
          serialiser.addRelation(content.substr(1),model) ;
        }

        ENetPacket* messageDestroyRelation(const Kernel::Relation& relation,NetworkMapper* mapper)
        {
          Kernel::TextSerialiser serialiser(mapper) ;
          std::string content("s") ;
          content += serialiser.serialiseRelation(relation) ;
          return enet_packet_create(content.c_str(),content.length(),ENET_PACKET_FLAG_RELIABLE) ;
        }

        bool isMessageDestroyRelation(ENetPacket* packet)
        {
          return packet->data[0] == 's' ;
        }

        void destroyRelation(ENetPacket* packet,NetworkMapper* mapper,Kernel::Model* model)
        {
          std::string content ;
          content.assign((const char*)packet->data,packet->dataLength) ;

          Kernel::TextSerialiser serialiser(mapper) ;
          serialiser.removeRelation(content.substr(1),model) ;
        }

      }
    }
  }
}
