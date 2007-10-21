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

#include <sound/implementation/openal/engine_sound.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        RegisterView(OpenAL::EngineSound, 
                     Model::EngineSound, 
                     OpenAL::RealWorldViewPoint) ;
             
        EngineSound::EngineSound(
          Model::EngineSound* i_observer,
          RealWorldViewPoint*     i_viewpoint) 
        : Kernel::TraitView<Model::EngineSound,RealWorldViewPoint>(i_observer,i_viewpoint),
        SoundEmitter()
        {
          InternalMessage("Building OpenAL::EngineSound") ;
        }
                    
        std::string EngineSound::getSoundFileName() const
        {
          return "engine.ogg";
        }
          
        bool EngineSound::isEvent() const
        {
          return false;
        }
        
        Kernel::Object* EngineSound::getObject() const
        {
          getModel()->getObject() ;
        }
        
        float EngineSound::getOuterGain() const
        {
        	return 0.5;	
        }
        
        float EngineSound::getOuterAngle() const
        {
          return 170;
        }
        
        float EngineSound::getInnerAngle() const
        {
          return 45;
        }
                  
        void EngineSound::onInit()
        {
          this->initSound();
        }
                    
        void EngineSound::onClose()
        {
          this->deleteSound();
        }
                    
        void EngineSound::onUpdate()
        {
          this->updateSource();
        } 
      
      }
    }
  }
}
