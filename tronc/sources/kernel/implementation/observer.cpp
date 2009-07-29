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
#include <kernel/trait.h>
#include <kernel/model.h>
#include <kernel/observer.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    Object* Observer::getObject() const
    {
      return m_trait->getObject() ;
    }

    Trait* Observer::getTrait() const
    {
      return m_trait ;
    }

    Observer::~Observer()
    {}

    Observer::Observer(Trait* trait)
    : m_initialised(false),
      m_really_initialised(false),
      m_trait(trait)
    {}

    Observer::Observer()
    : m_initialised(false),
      m_really_initialised(false),
      m_trait(NULL)
    {}

    void Observer::setObserved(Trait* trait)
    {
      m_trait = trait ;
    }

    void Observer::_init()
    {
      if (!m_initialised)
      {
        getObject()->getModel()->initObserver(this) ;
        m_initialised = true ;
      }
    }

    void Observer::_close()
    {
      if (m_initialised)
      {
        getObject()->getModel()->closeObserver(this) ;
        m_initialised = false ;
      }
    }

    void Observer::_updated()
    {
      if (m_initialised)
      {
        getObject()->getModel()->updateObserver(this) ;
      }
    }

    void Observer::_changed_parent(Object* old_parent)
    {
      getObject()->getModel()->changeParentObserver(this,old_parent) ;
    }

    void Observer::realClose()
    {
      if (m_really_initialised)
      {
        onClose() ;
        m_really_initialised = false ;
      }
    }

    void Observer::realChangeParent(Object* old_parent)
    {
      if (m_really_initialised)
      {
        onChangeParent(old_parent) ;
      }
    }

    void Observer::realUpdate()
    {
      if (m_really_initialised)
      {
        onUpdate() ;
      }
    }

    bool Observer::isInitialised() const
    {
      return m_really_initialised ;
    }

  }
}
