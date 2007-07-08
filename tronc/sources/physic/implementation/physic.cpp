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
#include <memory>
#include <set>

#include <ode/ode.h>

#include <kernel/log.h>
#include <kernel/error.h>
#include <kernel/view_point.h>

#include <model/duration.h>

#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/physic_system.h>

#include <physic/physic.h>

namespace ProjetUnivers {
  namespace Physic {

  /*!
    @name Attributes
  */
  // @{
    
    /// active viewpoint.
    std::auto_ptr<Implementation::Ode::PhysicSystem> m_system ;

    bool initialised = false ;

  // @}
    
    void init() 
    {
      if (! initialised)
      {
        initialised = true ;
        
        if (m_system.get())
        {
          m_system->init() ;
        }      
      }
    }
    
    void close()
    {
      InternalMessage("Physic::close entering") ;
      if (m_system.get())
      {
        m_system->close() ;
      }
      
      m_system.reset(NULL) ;
      InternalMessage("Physic::close leaving") ;
    }

    Kernel::ControlerSet* build(Kernel::Object* i_observer)
    {
      m_system.reset( 
        new Implementation::Ode::PhysicSystem(i_observer)) ;
      m_system->init() ;
      return m_system.get() ;
    }

    void update()
    {
      update(Model::Duration::Second(1)) ;
    }

    void update(const Model::Duration& i_duration)    
    {
      float seconds = i_duration.Second() ;
//      std::cout << "initialised=" << initialised
//                << " m_system.get()=" << m_system.get()
//                << " seconds=" << seconds
//                << std::endl ;
      if (initialised && m_system.get() && seconds != 0)
      {
//        std::cout << "Physic::update" << std::endl ;
        m_system->simulate(seconds) ;
      }
    }

  }
}

