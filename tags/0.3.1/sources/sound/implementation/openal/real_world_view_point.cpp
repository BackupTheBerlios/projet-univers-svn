/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2008 Morgan GRIGNARD Mathieu ROGER                 *
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

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/real_world_view_point.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        RegisterViewPoint(RealWorldViewPoint) ;
        
        RealWorldViewPoint::RealWorldViewPoint(Kernel::Model* model)
        : Kernel::ViewPoint(model)
        {
           InternalMessage("Sound","Entering OpenAL::RealWorldViewPoint::RealWorldViewPoint(const Kernel::Association<Model::Object>&)") ;
           InternalMessage("Sound","Leaving OpenAL::RealWorldViewPoint::RealWorldViewPoint(const Kernel::Association<Model::Object>&)") ;
        }
        
        void RealWorldViewPoint::onInit()
        {
          Implementation::OpenAL::init() ;    
        }
        
        void RealWorldViewPoint::onClose()
        {
          Implementation::OpenAL::close() ;
        }
        
        void RealWorldViewPoint::update(const float&)
        {
          Implementation::OpenAL::update() ;
        }
        
      }
    }
  }
}
