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

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/engine.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        RegisterView(OpenAL::Engine, 
                     Implementation::Engine, 
                     OpenAL::RealWorldViewPoint) ;
             
        Engine::Engine(
          Implementation::Engine*      object,
          OpenAL::RealWorldViewPoint*  viewpoint) 
        : Kernel::TraitView<Implementation::Engine,
                            OpenAL::RealWorldViewPoint>(object,viewpoint),
          SoundEmitter()
        {
          InternalMessage("Sound","Building OpenAL::EngineSound") ;
        }
                    
        std::string Engine::getSoundFileName() const
        {
          return "pu_moteur_2.ogg" ;
        }
          
        bool Engine::isEvent() const
        {
          return false;
        }
        
        Kernel::Object* Engine::getObject() const
        {
          getTrait()->getObject() ;
        }
        
        float Engine::getOuterGain() const
        {
          return 0.25;  
        }
        
        float Engine::getOuterAngle() const
        {
          return 170;
        }
        
        float Engine::getInnerAngle() const
        {
          return 45;
        }
                  
        void Engine::onInit()
        {
          this->initSound(getViewPoint());
        }
                    
        void Engine::onClose()
        {
          this->deleteSound();
        }
                    
        void Engine::onUpdate()
        {
          this->updateSource(getViewPoint());
        }
        
        void Engine::onChangeParent(Kernel::Object* i_old_parent)
        {
          InformationMessage("Sound","call onChangeParent") ;
          this->changeParentSource(getViewPoint()) ;
        }
      
      }
    }
  }
}
