/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

namespace ProjetUnivers {
  namespace Kernel {

    CommandDelegator::CommandDelegator()
    : Trait(),
      m_delegates()
    {}

    void CommandDelegator::addDelegate(Object* i_delegate)
    {
      m_delegates.insert(i_delegate) ;
    }

    bool CommandDelegator::call(
      const TypeIdentifier& i_trait_type,
      const std::string&    i_command)
    {
      bool found = false ;

      for(std::set<Object*>::iterator delegate = m_delegates.begin() ;
          delegate != m_delegates.end() && !found ;
          ++delegate)
      {
        found = (*delegate)->call(i_command) ;
      }

      return found ;

    }

    bool CommandDelegator::call(
      const TypeIdentifier& i_trait_type,
      const std::string&    i_command,
      const int&            i_parameter)
    {
      bool found = false ;

      for(std::set<Object*>::iterator delegate = m_delegates.begin() ;
          delegate != m_delegates.end() && !found ;
          ++delegate)
      {
        found = (*delegate)->call(i_command,i_parameter) ;
      }

      return found ;
    }

    std::set<std::string> CommandDelegator::getCommands() const
    {
      std::set<std::string> result ;
      for(std::set<Object*>::const_iterator delegate = m_delegates.begin() ;
          delegate != m_delegates.end();
          ++delegate)
      {
        std::set<std::string> temp((*delegate)->getCommands()) ;
        result.insert(temp.begin(),temp.end()) ;
      }

      return result ;
    }
  }
}
