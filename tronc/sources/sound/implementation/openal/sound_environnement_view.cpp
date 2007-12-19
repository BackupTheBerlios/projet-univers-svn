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
          alGenAuxiliaryEffectSlots(1, &m_auxEffectSlot) ;
          InformationMessage("Sound","OpenAL::SoundEmitter::gen slot: " + getErrorString(alGetError())) ; 
          alGenEffects(1, &m_effect) ;
          update();
          InformationMessage("Sound","OpenAL::SoundEnvironnementView::init leaving with status: " + getErrorString(alGetError())) ;
          InformationMessage("Sound","OpenAL::SoundEnvironnementView::init leaving") ;
        }


        void SoundEnvironnementView::onClose()
        {
          alDeleteEffects(1, &m_effect) ;
          alDeleteAuxiliaryEffectSlots(1, &m_auxEffectSlot) ;
        }
                      
        void SoundEnvironnementView::onUpdate()
        {
          Model::SoundEnvironnement* env = getModel()->getObject()->getTrait<Model::SoundEnvironnement>() ;
          alEffecti(m_effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB) ;
          alEffectf(m_effect, AL_REVERB_DENSITY, env->getDensity()) ;
          alEffectf(m_effect, AL_REVERB_DIFFUSION, env->getDiffusion()) ;
          alEffectf(m_effect, AL_REVERB_GAIN, env->getGain()) ;
          alEffectf(m_effect, AL_REVERB_GAINHF, env->getGainHF()) ;
          alEffectf(m_effect, AL_REVERB_DECAY_TIME, env->getDecayTime()) ;
          alEffectf(m_effect, AL_REVERB_DECAY_HFRATIO, env->getDecayHFRatio()) ;
          alEffectf(m_effect, AL_REVERB_REFLECTIONS_GAIN, env->getReflexionsGain()) ;
          alEffectf(m_effect, AL_REVERB_REFLECTIONS_DELAY, env->getReflexionsDelay()) ;
          alEffectf(m_effect, AL_REVERB_LATE_REVERB_GAIN, env->getLateReverbGain()) ;
          alEffectf(m_effect, AL_REVERB_LATE_REVERB_DELAY, env->getLateReverbDelay()) ;
          alEffectf(m_effect, AL_REVERB_ROOM_ROLLOFF_FACTOR, env->getRoomRollofFactor()) ;
          alEffectf(m_effect, AL_REVERB_AIR_ABSORPTION_GAINHF, env->getAirAbsorptionGainHF()) ;
          alEffectf(m_effect, AL_REVERB_DECAY_HFLIMIT, env->getDecayHFLimit()) ;
          alAuxiliaryEffectSloti(m_auxEffectSlot, AL_EFFECTSLOT_EFFECT, m_effect) ;
        }
              
        
      
      }
    }
  }
}
