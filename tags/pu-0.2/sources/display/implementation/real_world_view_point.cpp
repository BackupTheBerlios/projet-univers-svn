/***************************************************************************
 *   Copyright (C) 2006 by Equipe Projet Univers                           *
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

#include <kernel/log.h>
#include <kernel/error.h>
#include <kernel/object.h>

#include <model/model.h>

#include <display/exception.h>
#include <display/implementation/real_world_view_point.h>
#include <display/implementation/ogre/real_world_view_point.h>


namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {

      /*!
        Common part for all real worl viepoint implementations.
        For now we use Ogre as renderer.
      */
  
      RealWorldViewPoint::RealWorldViewPoint(Kernel::Object* i_observer)
      : Kernel::ViewPoint(Model::getRealWorlModel()), 
        observer(i_observer)
      {}
  
      RealWorldViewPoint::~RealWorldViewPoint()
      {}
  
      Kernel::Object* RealWorldViewPoint::getObserverView() const
      {
        return observer ;
      }
    
    }  
  }
}

