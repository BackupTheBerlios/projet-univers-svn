/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

#include <kernel/notifiable.h>
#include <kernel/exception_kernel.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    Notifiable::~Notifiable()
    {
      for(std::set<Notifiable*>::iterator dependency = m_reverse_dependencies.begin() ; dependency != m_reverse_dependencies.end() ; ++dependency)
      {
        (*dependency)->_removeDependency(this) ;
      }

      for(std::set<Notifiable*>::iterator dependent = m_direct_dependent_notifiables.begin() ; dependent != m_direct_dependent_notifiables.end() ; ++dependent)
      {
        (*dependent)->removeReverseDependency(this) ;
      }
    }

    Notifiable::Notifiable()
    {}

    void Notifiable::addReverseDependency(Notifiable* notifiable)
    {
      m_reverse_dependencies.insert(notifiable) ;
    }

    void Notifiable::removeReverseDependency(Notifiable* notifiable)
    {
      m_reverse_dependencies.erase(notifiable) ;
    }

    const std::set<Notifiable*>& Notifiable::getDependentNotifiables() const
    {
      return m_direct_dependent_notifiables ;
    }

    const std::set<Notifiable*>& Notifiable::getDependencies() const
    {
      return m_reverse_dependencies ;
    }

    void Notifiable::addDependency(Notifiable* notifiable)
    {
      if (!notifiable)
        throw ExceptionKernel("Notifiable::addDependency") ;

      if (this == notifiable)
        return ;

      m_direct_dependent_notifiables.insert(notifiable) ;
      notifiable->addReverseDependency(this) ;
    }

    void Notifiable::removeDependency(Notifiable* notifiable)
    {
      if (this == notifiable)
        return ;

      _removeDependency(notifiable) ;
      notifiable->removeReverseDependency(this) ;
    }

    void Notifiable::_removeDependency(Notifiable* notifiable)
    {
      if (!notifiable)
        throw ExceptionKernel("Notifiable::removeDependency") ;
      m_direct_dependent_notifiables.erase(notifiable) ;
    }

    void Notifiable::updateDependents() const
    {
      for(std::set<Notifiable*>::const_iterator notifiable = m_direct_dependent_notifiables.begin() ;
          notifiable != m_direct_dependent_notifiables.end() ;
          ++notifiable)
      {
        (*notifiable)->notify() ;
      }
    }

    void Notifiable::closeDependents() const
    {
      for(std::set<Notifiable*>::const_iterator notifiable = m_direct_dependent_notifiables.begin() ;
          notifiable != m_direct_dependent_notifiables.end() ;
          ++notifiable)
      {
        (*notifiable)->_close() ;
      }
    }

  }
}
