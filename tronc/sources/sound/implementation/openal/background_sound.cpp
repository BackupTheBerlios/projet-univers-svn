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

#include <sound/implementation/openal/background_sound.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        RegisterView(OpenAL::BackgroundSound, 
                     Model::BackgroundSound, 
                     OpenAL::RealWorldViewPoint) ;
             
        BackgroundSound::BackgroundSound(
          Model::BackgroundSound* i_observer,
          RealWorldViewPoint*     i_viewpoint) 
        : Kernel::TraitView<Model::BackgroundSound,RealWorldViewPoint>(i_observer,i_viewpoint),
        SoundEmitter()
        {
          InternalMessage("Building OpenAL::BackgroundSound") ;
        }
                    
        std::string BackgroundSound::getSoundFileName() const
        {
          return this->getModel()->getFileName();
        }
          
        bool BackgroundSound::isEvent() const
        {
          return false;
        }
          
        bool BackgroundSound::isActive() const
        {
          return true;
        }
          
        bool BackgroundSound::isListenerRelative() const
        {
          return true;
        }
        
        Kernel::Object* BackgroundSound::getObject() const
        {
          getModel()->getObject() ;
        }
        
        float BackgroundSound::getOuterAngle() const
        {
          return 360 ;
        }
        
        float BackgroundSound::getInnerAngle() const
        {
          return 360;
        }
       
        float BackgroundSound::getMaxDistance() const
        {
          return 1000;
        }
          
        void BackgroundSound::onInit()
        {
          this->initSound();
        }
                    
        void BackgroundSound::onClose()
        {
          this->deleteSound();
        }
                    
        void BackgroundSound::onUpdate()
        {
          this->updateSource();
        } 
      
      }
    }
  }
}
