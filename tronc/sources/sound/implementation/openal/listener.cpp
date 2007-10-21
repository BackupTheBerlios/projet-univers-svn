/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD                                    *
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

#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/listener.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        
        RegisterView(OpenAL::Listener, 
                     Model::Listener, 
                     OpenAL::RealWorldViewPoint) ;
        
        Listener::Listener(Model::Listener*    i_observer,
                           RealWorldViewPoint* i_viewpoint) 
        : Kernel::TraitView<Model::Listener,RealWorldViewPoint>(i_observer,i_viewpoint),
          SoundListener()
        {
          InternalMessage("Building OpenAL::Listener") ;
        }
        
        float Listener::getGain() const
        {
          return 1.0f;
        }
                             
        Model::Position Listener::getPosition() const
        {  
          Model::Positionned* positionned = getObject()->getTrait<Model::Positionned>();
          if(positionned)
          {
            return positionned->getPosition(getManager()->getReference());
          }
          else
          {
          	//default value
            return Model::Position();
          }
        }
                                 
        Model::Orientation Listener::getOrientation() const
        {
          Model::Oriented* oriented = getObject()->getTrait<Model::Oriented>();
          if(oriented)
          {
            return oriented->getOrientation(getManager()->getReference());
          }
          else
          {
          	//default value
            return Model::Orientation();
          }
        }
                                 
        Model::Speed Listener::getSpeed() const
        {
          Model::Mobile* mobile = getObject()->getTrait<Model::Mobile>();
          if(mobile)
          {
            return mobile->getSpeed();
          }
          else
          {
          	//default value
            return Model::Speed();
          }
        }
        
        void Listener::onInit()
        {
          InternalMessage("OpenAL::Listener::onInit Entering") ;

          this->updateListener();
                      
          InternalMessage("OpenAL::Listener::onInit Leaving") ;
        }
          
        void Listener::onClose()
        {
          InternalMessage("OpenAL::Listener::onClose Entering") ;

          //Just one listener by context in openal , it's destroy with openal context
          
          InternalMessage("OpenAL::Listener::onClose Leaving") ;
        }
        
        void Listener::onUpdate()
        {
          this->updateListener();
        }
        
      }
    }
  }
}

