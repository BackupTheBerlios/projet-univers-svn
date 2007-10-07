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

#include <sound/implementation/openal/collision.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        RegisterView(OpenAL::Collision, 
                     Model::Collision, 
                     OpenAL::RealWorldViewPoint) ;
             
        Collision::Collision(
          Model::Collision* i_observer,
          RealWorldViewPoint*     i_viewpoint) 
        : Kernel::TraitView<Model::Collision,RealWorldViewPoint>(i_observer,i_viewpoint),
        SoundEmitter()
        {
          InternalMessage("Building OpenAL::Collision") ;
        }
                    
        std::string Collision::getSoundFileName() const
        {
          return "sound.wav";
        }
          
        bool Collision::isEvent() const
        {
          return true;
        }
          
        bool Collision::isActive() const
        {
          return true;
        }
          
        bool Collision::isListenerRelative() const
        {
          return true;
        }
          
        Model::Position Collision::getPosition() const
        {
          return Model::Position();
        }
          
        Model::Orientation Collision::getOrientation() const
        {
          return Model::Orientation();
        }
          
        Model::Speed Collision::getSpeed() const
        {
          return Model::Speed();
        }
    
        float Collision::getOuterAngle() const
        {
          return 360 ;
        }
        
        float Collision::getInnerAngle() const
        {
          return 360;
        }
       
        float Collision::getMaxDistance() const
        {
          return 1000;
        }
          
        void Collision::onInit()
        {
          this->initSound();
        }
                    
        void Collision::onClose()
        {
          this->deleteSound();
        }
                    
        void Collision::onUpdate()
        {
          this->updateSource();
        } 
      
      }
    }
  }
}
