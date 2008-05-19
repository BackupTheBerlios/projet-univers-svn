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
#include <kernel/string.h>
#include <kernel/log.h>

#include <sound/implementation/openal/extension.h>
#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/sound_environnement_view.h>


namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        RegisterView(OpenAL::SoundEnvironnementView, 
                     Model::SoundEnvironnement, 
                     OpenAL::RealWorldViewPoint) ;
                     
        SoundEnvironnementView::SoundEnvironnementView(
          Model::SoundEnvironnement* i_observer,
          RealWorldViewPoint*     i_viewpoint)
        : Kernel::TraitView<Model::SoundEnvironnement,RealWorldViewPoint>(i_observer,i_viewpoint),
          m_auxEffectSlot(0), m_effect(0)
        {
          InformationMessage("Sound","Building OpenAL::SoundEnvironnementView") ;
        }
        
        ALuint SoundEnvironnementView::getAuxEffectSlot()
        {
        	return m_auxEffectSlot ;	
        }
        
        void SoundEnvironnementView::onInit()
        {
          InformationMessage("Sound","OpenAL::SoundEnvironnementView::init enter") ;
          EFX::createEffect(&m_effect,&m_auxEffectSlot) ;
          update();
          InformationMessage("Sound","OpenAL::SoundEnvironnementView::init leaving with status: " + getErrorString(alGetError())) ;
          InformationMessage("Sound","OpenAL::SoundEnvironnementView::init leaving") ;
        }


        void SoundEnvironnementView::onClose()
        {
          EFX::destroyEffect(&m_effect,&m_auxEffectSlot) ;
        }
                      
        void SoundEnvironnementView::onUpdate()
        {
          InformationMessage("Sound","OpenAL::SoundEnvironnementView::update enter") ;
          Model::SoundEnvironnement* env = getTrait()->getObject()->getTrait<Model::SoundEnvironnement>() ;
          EFX::changeEffect(m_effect,m_auxEffectSlot,env) ;
          InformationMessage("Sound","OpenAL::SoundEnvironnementView::update leave") ;
        }
              
        
      
      }
    }
  }
}
