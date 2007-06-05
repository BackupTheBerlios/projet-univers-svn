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
#include <kernel/trait.h>
#include <kernel/controler_set.h>

#include <kernel/controler.h>

namespace ProjetUnivers {
  namespace Kernel {

    Object* BaseControler::getObject() const
    {
      return m_trait->getObject() ; 
    }
  
    BaseControler::~BaseControler()
    {
      _close() ;
      if (m_trait)
      {
        m_trait->_remove_controler(m_controler_set,this) ;
      }
    }

    BaseControler::BaseControler(Trait* i_trait,ControlerSet* i_controler_set)
    : m_initialised(false),
      m_trait(i_trait),
      m_controler_set(i_controler_set)
    {}

    void BaseControler::_init()
    {
      /*!
        We initialise only if the controler set has been initialised.
      */
      if (m_controler_set)
      {
        if (! m_initialised && m_controler_set->isInitialised())
        {
          onInit() ;
          m_initialised = true ;        
        }
      }
    }

    void BaseControler::_close()
    {
      if (m_initialised)
      {
        onClose() ;
        m_initialised = false ;        
      }
    }

    void BaseControler::_changed_parent(Object* i_old_parent)
    {
      if (m_initialised)
      {
        onChangeParent(i_old_parent) ;
      }
    }
    
    void BaseControler::_updated()
    {
      if (m_initialised)
      {
        onUpdate() ;
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
