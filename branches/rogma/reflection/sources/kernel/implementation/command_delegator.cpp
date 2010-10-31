/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#include <kernel/object.h>
#include <kernel/command_delegator.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {

    CommandDelegator::CommandDelegator()
    : Trait(),
      m_delegates()
    {}

    void CommandDelegator::addDelegate(Object* delegate)
    {
      m_delegates.insert(delegate) ;
      notify() ;
    }

    bool CommandDelegator::call(const TypeIdentifier&,const std::string& command)
    {
      bool found = false ;

      for(std::set<ObjectReference>::iterator delegate = m_delegates.begin() ;
          delegate != m_delegates.end() && !found ;
          ++delegate)
      {
        if (*delegate)
        {
          found = (*delegate)->_call(command) ;
        }
      }

      return found ;
    }

    bool CommandDelegator::call(const TypeIdentifier&,
                                const std::string&    command,
                                const int&            parameter)
    {
      bool found = false ;

      for(std::set<ObjectReference>::iterator delegate = m_delegates.begin() ;
          delegate != m_delegates.end() && !found ;
          ++delegate)
      {
        if (*delegate)
        {
          found = (*delegate)->_call(command,parameter) ;
        }
      }

      return found ;
    }

    std::set<std::string> CommandDelegator::getCommands() const
    {
      std::set<std::string> result ;
      for(std::set<ObjectReference>::const_iterator delegate = m_delegates.begin() ;
          delegate != m_delegates.end();
          ++delegate)
      {
        if (*delegate)
        {
          std::set<std::string> temp((*delegate)->_getCommands()) ;
          result.insert(temp.begin(),temp.end()) ;
        }
      }

      return result ;
    }
  
    const std::set<ObjectReference>& CommandDelegator::getDelegates() const
    {
      return m_delegates ;
    }
    
  }
}
