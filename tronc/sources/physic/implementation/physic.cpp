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

#include <boost/function.hpp>

#include <ode/ode.h>

#include <kernel/log.h>
#include <kernel/error.h>
#include <kernel/view_point.h>

#include <model/duration.h>

#include <physic/implementation/ode/physical_world.h>
#include <physic/implementation/ode/real_world_view_point.h>

#include <physic/physic.h>

namespace ProjetUnivers {
  namespace Physic {

  /*!
    @name Attributes
  */
  // @{
    
    /// active viewpoint.
    std::auto_ptr<Implementation::Ode::RealWorldViewPoint> viewpoint ;

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
      Kernel::Log::InternalMessage("Physic::close leaving") ;
    }

    Kernel::ViewPoint* buildRealWorldViewPoint(Kernel::Object* i_observer)
    {
      viewpoint.reset( 
        new Implementation::Ode::RealWorldViewPoint(i_observer)) ;
      viewpoint->init() ;
      return viewpoint.get() ;
    }

    void update()
    {
      update(Model::Duration::Second(1)) ;
    }

    void update(const Model::Duration& i_duration)    
    {
      boost::function2<void,
                       Implementation::Ode::PhysicalWorld*,
                       Model::Duration> f 
                          = &Implementation::Ode::PhysicalWorld::update ;
      
      /// update for all physical worlds  
      Kernel::forAll<Implementation::Ode::PhysicalWorld>(
        viewpoint.get(),
        std::bind2nd(f,i_duration)) ;
      
    }

  }
}

