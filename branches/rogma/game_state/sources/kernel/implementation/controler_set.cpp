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
#include <kernel/model.h>
#include <kernel/base_controler.h>
#include <kernel/object.h>

#include <kernel/controler_set.h>

namespace ProjetUnivers {
  namespace Kernel {
  
    ControlerSet::StaticStorage* ControlerSet::StaticStorage::get()
    {
      static StaticStorage temp ;
      return &temp ;
    }

    
    void ControlerSet::simulate(const float& i_seconds)
    {
      boost::function2<void,
                       BaseControler*,
                       float> f 
                          = &BaseControler::simulate ;
      
      applyTopDown(std::bind2nd(f,i_seconds)) ;
      
    }
    
    void ControlerSet::applyTopDown(boost::function1<void,BaseControler*> i_procedure)
    {
      /// down to top recursive simulation on controlers.
      for(std::set<Object*>::const_iterator object = m_model->m_objects.begin() ;
          object != m_model->m_objects.end() ;
          ++object)
      {
        (*object)->applyTopDown(this,i_procedure) ;
      }
    }

    void ControlerSet::applyBottomUp(boost::function1<void,BaseControler*> i_procedure)
    {
      /// down to top recursive simulation on controlers.
      for(std::set<Object*>::const_iterator object = m_model->m_objects.begin() ;
          object != m_model->m_objects.end() ;
          ++object)
      {
        (*object)->applyBottomUp(this,i_procedure) ;
      }
    }
    
    void ControlerSet::init()
    {
      if (! m_initialised)
      {
        if (m_model)
        {
          m_model->_register(this) ;
        }
        
        m_initialised = true ;
        
        /// must init all the objects according to current viewpoint
        if (m_model)
        {
          m_model->_init(this) ;
        }
      }
    }

    void ControlerSet::close()
    {
      if (m_initialised && m_model)
      {
        /// must init all the objects according to current controler set
        m_model->_close(this) ;
        m_model->_unregister(this) ;
        m_initialised = false ;
      }
    }
    
    ControlerSet::~ControlerSet()
    {
      InternalMessage("Kernel","ControlerSet::~ControlerSet destroying") ;
      close() ;
      InternalMessage("Kernel","ControlerSet::~ControlerSet destroyed") ;
    }
      
    ControlerSet::ControlerSet(Model* model)
    : m_model(model),
      m_initialised(false)
    {}
    
    bool ControlerSet::isVisible(Object* i_object) const
    {
      return true ;
    }

    bool ControlerSet::isInitialised() const
    {
      return m_initialised ;
    }      

    void ControlerSet::setModel(Model* model)
    {
      InternalMessage("Kernel","ViewPoint::setModel Entering") ;
      if (m_initialised && m_model)
      {
        /// must close all the objects according to current viewpoint
        m_model->_close(this) ;
        m_model->_unregister(this) ;
      }
      
      m_model = model ;
      
      if (m_model)
      {
        m_model->_register(this) ;
        m_model->_init(this) ;
      }
      InternalMessage("Kernel","ViewPoint::setModel Entering") ;
    }

    void ControlerSet::registerBuilder(ControlerSet::ControlerSetBuilder builder)
    {
      StaticStorage::get()->m_controler_set_builders.push_back(builder) ;
    }
    
    void ControlerSet::buildRegistered(Model* model)
    {
      for(std::list<ControlerSetBuilder>::const_iterator 
            builder = StaticStorage::get()->m_controler_set_builders.begin() ;
          builder != StaticStorage::get()->m_controler_set_builders.end() ;
          ++builder)
      {
        (*builder)(model) ;
      }
    }
    
  }
}
