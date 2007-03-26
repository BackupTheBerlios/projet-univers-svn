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
#include <physic/implementation/ode/real_world_view_point.h>

#include <physic/implementation/physic_internal.h>
#include <physic/physic.h>

namespace ProjetUnivers {
  namespace Physic {

  /*!
    @name Attributes
  */
  // @{
    
    /// active viewpoint.
    std::auto_ptr<Implementation::Ode::RealWorldViewPoint> viewpoint ;
    
    /// worlds to simulate.
    /*!
      Maybe in Ode::RealWorldViewPoint ???
    */
    std::set<Implementation::Ode::PhysicalWorld*> worlds ;

    bool initialised = false ;

  // @}
    
    void init() 
    {
      if (! initialised)
      {
        initialised = true ;
        
        if (viewpoint.get())
        {
          viewpoint->init() ;
        }      
      }
    }
    
    void close()
    {
      Kernel::Log::InternalMessage("Physic::close entering") ;
      if (viewpoint.get())
      {
        viewpoint->close() ;
      }
      
      viewpoint.reset(NULL) ;
      worlds.clear() ;
      Kernel::Log::InternalMessage("Physic::close leaving") ;
    }

    Kernel::ViewPoint* buildRealWorldViewPoint(Kernel::Object* i_observer)
    {
      viewpoint.reset( 
        new Implementation::Ode::RealWorldViewPoint(i_observer)) ;
      return viewpoint.get() ;
    }

    void addPhysicalWorld(Implementation::Ode::PhysicalWorld* i_world)
    {
      worlds.insert(i_world) ;
    }
    void removePhysicalWorld(Implementation::Ode::PhysicalWorld* i_world) 
    {
      worlds.erase(i_world) ;
    }

    void update()
    {
      update(Model::Duration::Second(1)) ;
    }

    void update(const Model::Duration& i_duration)    
    {
      /// simulate one frame for every worlds
      for(std::set<Implementation::Ode::PhysicalWorld*>::iterator world = worlds.begin() ;
          world != worlds.end() ;
          ++world)
      {
        dWorldStep((*world)->getWorld()->id(),i_duration.Second()) ; 
      }

      /// that's all ??? 
      
    }

  }
}

