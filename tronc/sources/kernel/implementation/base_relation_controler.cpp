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
#include <kernel/controler_set.h>
#include <kernel/base_relation_controler.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    void BaseRelationControler::realInit()
    {
      if (m_controler_set)
      {
        if (! m_really_initialised && m_controler_set->isInitialised())
        {
          onInit() ;
          m_really_initialised = true ;
        }
      }
    }

    BaseRelationControler::~BaseRelationControler()
    {
      close() ;
    }

    BaseRelationControler::BaseRelationControler()
    : m_controler_set(NULL)
    {}

    void BaseRelationControler::_setControlerSet(ControlerSet* controler_set)
    {
      m_controler_set = controler_set ;
    }

    ControlerSet* BaseRelationControler::getControlerSet() const
    {
      return m_controler_set ;
    }
  }
}

