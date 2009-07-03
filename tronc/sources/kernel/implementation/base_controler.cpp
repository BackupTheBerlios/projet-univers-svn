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
#include <kernel/trait.h>
#include <kernel/controler_set.h>

#include <kernel/controler.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    BaseControler::~BaseControler()
    {
      _close() ;
      if (m_trait)
      {
        m_trait->_remove_controler(m_controler_set,this) ;
      }
    }

    BaseControler::BaseControler()
    : m_controler_set(NULL)
    {}

    void BaseControler::setControlerSet(ControlerSet* controler_set)
    {
      m_controler_set = controler_set ;
    }

    void BaseControler::realInit()
    {
      /*!
        We initialise only if the controler set has been initialised.
      */
      if (m_controler_set)
      {
        if (! m_really_initialised && m_controler_set->isInitialised())
        {
          onInit() ;
          m_really_initialised = true ;
        }
      }
    }

    ControlerSet* BaseControler::getControlerSet() const
    {
      return m_controler_set ;
    }

    void BaseControler::prepare()
    {
    }

    void BaseControler::simulate(const float&)
    {
    }
  }
}
