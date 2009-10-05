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
#include <iostream>
#include <algorithm>
#include <kernel/model.h>
#include <kernel/base_controler.h>
#include <kernel/object.h>
#include <kernel/timer.h>
#include <kernel/parameters.h>

#include <kernel/controler_set.h>
#include <kernel/implementation/profiler.h>

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

      // timestep == 0 means no fixed timestep
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

    void ControlerSet::beforeSimulation(const float&)
    {}


    struct Equivalence
    {
      bool operator()(BaseControler* const & x,BaseControler* const & y) const
      {
        BaseControler::DependencyOrder local ;
        return !local(x,y) && !local(y,x) ;
      }
    };

    void ControlerSet::checkOrder(const std::list<BaseControler*>& controllers)
    {

      if (!Parameters::getValue<bool>("Kernel","ActivateCoherencyChecks",false))
        return ;

      BaseControler::DependencyOrder order ;
      bool error = false ;

      // check Irreflexivity
      for(std::list<BaseControler*>::const_iterator controller = controllers.begin() ; controller != controllers.end() ; ++controller)
      {
        if (order(*controller,*controller))
          error = true ;
      }

      // check Antisymmetry
      for(std::list<BaseControler*>::const_iterator controller1 = controllers.begin() ; controller1 != controllers.end() ; ++controller1)
      {
        for(std::list<BaseControler*>::const_iterator controller2 = controllers.begin() ; controller2 != controllers.end() ; ++controller2)
        {
          if (order(*controller1,*controller2) && order(*controller2,*controller1))
          {
            error = true ;
          }
        }
      }

      Equivalence equivalent ;

      // check Transitivity of equivalence
      for(std::list<BaseControler*>::const_iterator controller1 = controllers.begin() ; controller1 != controllers.end() ; ++controller1)
      {
        for(std::list<BaseControler*>::const_iterator controller2 = controllers.begin() ; controller2 != controllers.end() ; ++controller2)
        {
          for(std::list<BaseControler*>::const_iterator controller3 = controllers.begin() ; controller3 != controllers.end() ; ++controller3)
          {
            if (equivalent(*controller1,*controller2) && equivalent(*controller2,*controller3) && !equivalent(*controller1,*controller3))
            {
              error = true ;
            }
          }
        }
      }

      // check Transitivity
      for(std::list<BaseControler*>::const_iterator controller1 = controllers.begin() ; controller1 != controllers.end() ; ++controller1)
      {
        for(std::list<BaseControler*>::const_iterator controller2 = controllers.begin() ; controller2 != controllers.end() ; ++controller2)
        {
          for(std::list<BaseControler*>::const_iterator controller3 = controllers.begin() ; controller3 != controllers.end() ; ++controller3)
          {
            if ( order(*controller1,*controller2) && order(*controller2,*controller3) && !order(*controller1,*controller3))
            {
              error = true ;
              std::cout << std::endl << "order does not satisfy Transitivity : "
                        << (*controller1)->toString() << " < "
                        << (*controller2)->toString() << " and "
                        << (*controller2)->toString() << " < "
                        << (*controller3)->toString() << " but "
                        << (*controller1)->toString() << " is not < "
                        << (*controller3)->toString() << std::endl ;
            }
          }
        }
      }

      if (error)
        Log::logToFile(m_model->toGraphviz(this)) ;
    }

    void ControlerSet::orderControlers()
    {
      BaseControler::DependencyOrder order ;

      m_controllers.sort(order) ;

      checkOrder(m_controllers) ;
    }

    void ControlerSet::simulate(const float& seconds)
    {
      m_model->startTransaction() ;

      beforeSimulation(seconds) ;

      for(std::list<BaseControler*>::iterator controller = m_controllers.begin() ; controller != m_controllers.end() ; ++controller)
      {
        Implementation::Profiler::startBlock(getObjectTypeIdentifier(*controller).fullName() + "::prepare()") ;
        (*controller)->prepare() ;
        Implementation::Profiler::endBlock() ;
      }

      for(std::list<BaseControler*>::iterator controller = m_controllers.begin() ; controller != m_controllers.end() ; ++controller)
      {
        Implementation::Profiler::startBlock(getObjectTypeIdentifier(*controller).fullName() + "::simulate()") ;
        (*controller)->simulate(seconds) ;
        Implementation::Profiler::endBlock() ;
      }

      afterSimulation(seconds) ;

      m_model->endTransaction() ;
    }

    void ControlerSet::afterSimulation(const float&)
    {}

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
        /// must init all the objects according to current controller set
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
      m_elapsed(0),
      m_timestep(0.1),
      m_consumed_time(0),
      m_simulation_time(0)
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

    void ControlerSet::addControler(BaseControler* controler)
    {
      std::string debug = " " + getObjectTypeIdentifier(controler).fullName() ;

      m_controllers.push_back(controler) ;
    }

    void ControlerSet::removeControler(BaseControler* controler)
    {
      m_controllers.remove(controler) ;
    }

    void ControlerSet::destroyController(BaseControler* controler)
    {
      if (std::find(m_controllers.begin(),m_controllers.end(),controler) != m_controllers.end())
        throw ExceptionKernel("ControlerSet::destroyController") ;
    }

  }
}
