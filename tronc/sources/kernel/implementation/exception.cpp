/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <kernel/implementation/debugger.h>
#include <kernel/exception.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    Exception::Exception(const std::string& message)
    : m_message(message),numeroErreur(0)
    {
      m_message = Implementation::Debugger::getDebugger().getStack() + m_message ;
    }

    Exception::Exception(const std::string& message,const unsigned int& numero)
    : m_message(message),numeroErreur(numero)
    {
      m_message = Implementation::Debugger::getDebugger().getStack() + m_message ;
    }

    Exception::~Exception() throw()
    {}

    Exception::Exception(const Exception& x)
    : std::exception(*this),
    m_message(x.m_message),numeroErreur(x.numeroErreur)
    {}

    std::string Exception::Message() const
    {

      return std::string("ERREUR") + std::string(" : ") + m_message;
    }

    const char* Exception::what() const throw()
    {
      return m_message.c_str() ;
    }

  }
}
