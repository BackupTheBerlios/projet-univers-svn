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

#include <string>
#include <kernel/trait.h>
#include <model/duration.h>

namespace ProjetUnivers
{
  namespace Model
  {

    /// Indicate that the object is a network client.
    /*!
    @see Model::Connecting, Model::Connected, Model::Server
    */
    class Client : public Kernel::Trait
    {
    public:

      Client(const std::string&,const Duration&) ;

      /// Connection address
      const std::string& getAddress() const ;

      /// Timeout duration.
      const Duration& getTimeout() const ;

    private:

      /// Connection address
      std::string m_address ;

      /// The time we can wait before considering that we have a timeout
      Duration m_timout_duration ;
    };

  }
}
