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
#include <ode/ode.h>

#include <kernel/log.h>

#include <model/model.h>

#include <physic/implementation/ode/real_world_view_point.h>

namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {
        
        RealWorldViewPoint::RealWorldViewPoint(Kernel::Object* i_observer)
        : Kernel::ViewPoint(Model::getRealWorlModel())
        {}
        
        void RealWorldViewPoint::onInit()
        {
        }
        
        void RealWorldViewPoint::onClose()
        {
          Kernel::Log::InternalMessage("RealWorldViewPoint::onClose") ;
        }
        
        /*!
          To be visible an object needs :
          - being positionned and (mobile or solid) 
          - ??? 
          not too far from the observer....
        */
        bool RealWorldViewPoint::isVisible(Kernel::Object* i_object) const
        {
          /// @temp
          return true ;          
        }
      }
    }
  }
}
