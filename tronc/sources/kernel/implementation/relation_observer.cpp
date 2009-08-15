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
#include <kernel/object.h>
#include <kernel/relation_observer.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    void RelationObserver::init()
    {
      if (!m_initialised)
      {
        getObjectFrom()->getModel()->initObserver(this) ;
        m_initialised = true ;
      }
    }

    void RelationObserver::close()
    {
      if (m_initialised)
      {
        getObjectFrom()->getModel()->closeObserver(this) ;
        m_initialised = false ;
      }
    }

    void RelationObserver::update()
    {
      if (m_initialised)
      {
        getObjectFrom()->getModel()->updateObserver(this) ;
      }
    }

    Object* RelationObserver::getObjectFrom() const
    {
      return m_relation.getObjectFrom() ;
    }

    Object* RelationObserver::getObjectTo() const
    {
      return m_relation.getObjectTo() ;
    }

    RelationObserver::~RelationObserver()
    {}

    RelationObserver::RelationObserver()
    : m_initialised(false),
      m_really_initialised(false),
      m_relation()
    {}

    void RelationObserver::_setRelation(const Relation& relation)
    {
      m_relation = relation ;
    }

    bool RelationObserver::isInitialised() const
    {
      return m_really_initialised ;
    }

    void RelationObserver::realClose()
    {
      if (m_really_initialised)
      {
        m_initialised = false ;
        m_really_initialised = false ;
        onClose() ;
      }
    }

    void RelationObserver::realUpdate()
    {
      if (m_really_initialised)
      {
        onUpdate() ;
      }
    }

  }
}
