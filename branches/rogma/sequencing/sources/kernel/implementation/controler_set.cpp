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
#include <kernel/timer.h>

#include <kernel/controler_set.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    ControlerSet::StaticStorage* ControlerSet::StaticStorage::get()
    {
      static StaticStorage temp ;
      return &temp ;
    }

    void ControlerSet::setTimeStep(const float& timestep)
    {
      m_timestep = timestep ;
    }

    void ControlerSet::update(const float& seconds)
    {
      Kernel::Timer timer ;

      if (m_timestep==0)
      {
        this->simulate(seconds) ;
      }
      else
      {
        m_elapsed += seconds ;

        while (m_elapsed >= m_timestep)
        {
          this->simulate(m_timestep) ;
          m_elapsed -= m_timestep ;
        }
      }

      float elapsed = timer.getSecond() ;
      m_consumed_time += elapsed ;
      m_simulation_time += seconds ;
    }

    void ControlerSet::simulate(const float& seconds)
    {

      boost::function2<void,
                       BaseControler*,
                       float> f
                          = &BaseControler::simulate ;

      applyTopDown(std::bind2nd(f,seconds)) ;
    }

    float ControlerSet::getStatistics() const
    {
      return 100*m_consumed_time/m_simulation_time ;
    }

    void ControlerSet::applyTopDown(boost::function1<void,BaseControler*> procedure)
    {
      m_model->startTransaction() ;
      /// top to down recursive simulation on controlers.
      for(std::set<Object*>::const_iterator object = m_model->m_objects.begin() ;
          object != m_model->m_objects.end() ;
          ++object)
      {
        (*object)->applyTopDown(this,procedure) ;
      }
      m_model->endTransaction() ;
    }

    void ControlerSet::applyBottomUp(boost::function1<void,BaseControler*> procedure)
    {
      m_model->startTransaction() ;
      /// down to top recursive simulation on controlers.
      for(std::set<Object*>::const_iterator object = m_model->m_objects.begin() ;
          object != m_model->m_objects.end() ;
          ++object)
      {
        (*object)->applyBottomUp(this,procedure) ;
      }
      m_model->endTransaction() ;
    }

    void ControlerSet::init()
    {
      if (! m_initialised)
      {
        if (m_model)
        {
          m_model->_register(this) ;
        }

        onInit() ;

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
        onClose() ;
        m_model->_unregister(this) ;
        m_initialised = false ;
      }
    }

    ControlerSet::~ControlerSet()
    {
      close() ;
    }

    ControlerSet::ControlerSet(Model* model)
    : m_model(model),
      m_initialised(false),
      m_consumed_time(0),
      m_simulation_time(0),
      m_elapsed(0),
      m_timestep(0.1)
    {}

    void ControlerSet::resetStatistics()
    {
      m_consumed_time = 0 ;
      m_simulation_time = 0 ;
    }

    bool ControlerSet::isVisible(Object*) const
    {
      return true ;
    }

    bool ControlerSet::isInitialised() const
    {
      return m_initialised ;
    }

    void ControlerSet::onInit()
    {
    }

    void ControlerSet::onClose()
    {
    }

    void ControlerSet::setModel(Model* model)
    {
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
        ControlerSet* controlerset = (*builder)(model) ;
        model->_register(controlerset) ;
      }
    }

  }
}
