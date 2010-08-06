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

#include <model/sound_environnement.h>


namespace ProjetUnivers {
  namespace Model {
  	
    SoundEnvironnement::SoundEnvironnement()
    : m_density(1.0), m_diffusion(1.0), m_gain(0.32), m_gainHF(0.89), m_decayTime(1.49),
      m_decayHFRatio(0.83), m_reflexionsGain(0.05), m_reflexionsDelay(0.007), m_lateReverbGain(1.26),
      m_lateReverbDelay(0.011), m_roomRollofFactor(0.0), m_airAbsorptionGainHF(0.994), m_decayHFLimit(true)
    {}
        
    SoundEnvironnement::SoundEnvironnement(const float& p_density, const float& p_diffusion,
          const float& p_gain, const float& p_gainHF, const float& p_decayTime,
          const float& p_decayHFRatio, const float& p_reflexionsGain,
          const float& p_reflexionsDelay, const float& p_lateReverbGain,
          const float& p_lateReverbDelay, const float& p_roomRollofFactor,
          const float& p_airAbsorptionGainHF, const bool& p_decayHFLimit)
    : m_density(1.0), m_diffusion(1.0), m_gain(0.32), m_gainHF(0.89), m_decayTime(1.49),
      m_decayHFRatio(0.83), m_reflexionsGain(0.05), m_reflexionsDelay(0.007), m_lateReverbGain(1.26),
      m_lateReverbDelay(0.011), m_roomRollofFactor(0.0), m_airAbsorptionGainHF(0.994), m_decayHFLimit(true)
    {
      setDensity(p_density) ;
      setDiffusion(p_diffusion) ;
      setGain(p_gain) ;
      setGainHF(p_gainHF) ;
      setDecayTime(p_decayTime) ;
      setDecayHFRatio(p_decayHFRatio) ;
      setReflexionsGain(p_reflexionsGain) ;
      setReflexionsDelay(p_reflexionsDelay) ;
      setLateReverbGain(p_lateReverbGain) ;
      setLateReverbDelay(p_lateReverbDelay) ;
      setRoomRollofFactor(p_roomRollofFactor) ;
      setAirAbsorptionGainHF(p_airAbsorptionGainHF) ;
      setDecayHFLimit(p_decayHFLimit) ;
    }
    
    float SoundEnvironnement::getDensity() const
    {
      return m_density ;	
    }
    
    void SoundEnvironnement::setDensity(const float& p_density)
    {
      if(p_density <= 1.0 && p_density >= 0.0)
      {
        m_density = p_density ;
      }
    }
    
    float SoundEnvironnement::getDiffusion() const
    {
      return m_diffusion ;	
    }
    
    void SoundEnvironnement::setDiffusion(const float& p_diffusion)
    {
      if(p_diffusion <= 1.0 && p_diffusion >= 0.0)
      {
        m_diffusion = p_diffusion ;
      }
    }
    
    float SoundEnvironnement::getGain() const
    {
      return m_gain ;
    }
    
    void SoundEnvironnement::setGain(const float& p_gain)
    {
      if(p_gain <= 1.0 && p_gain >= 0.0)
      {
        m_gain = p_gain ;
      }
    }
       
    float SoundEnvironnement::getGainHF() const
    {
      return m_gainHF ;
    }
    
    void SoundEnvironnement::setGainHF(const float& p_gainHF)
    {
      if(p_gainHF <= 1.0 && p_gainHF >= 0.0)
      {
        m_gainHF = p_gainHF ;
      }	
    }
    
    float SoundEnvironnement::getDecayTime() const
    {
      return m_decayTime ;	
    }
    
    void SoundEnvironnement::setDecayTime(const float& p_decayTime)
    {
      if(p_decayTime <= 20.0 && p_decayTime >= 0.1)
      {
        m_decayTime = p_decayTime ;
      }	
    }
    
    float SoundEnvironnement::getDecayHFRatio() const
    {
      return m_decayHFRatio ;
    }
    
    void SoundEnvironnement::setDecayHFRatio(const float& p_decayHFRatio)
    {
      if(p_decayHFRatio <= 2.0 && p_decayHFRatio >= 0.1)
      {
        m_decayHFRatio = p_decayHFRatio ;
      }	
    }
       
    float SoundEnvironnement::getReflexionsGain() const
    {
      return m_reflexionsGain ;
    }
    
    void SoundEnvironnement::setReflexionsGain(const float& p_reflexionsGain)
    {
    	if(p_reflexionsGain <= 3.16 && p_reflexionsGain >= 0.0)
      {
        m_reflexionsGain = p_reflexionsGain ;
      }	
    }
    
    float SoundEnvironnement::getReflexionsDelay() const
    {
      return m_reflexionsDelay ;
    }
    
    void SoundEnvironnement::setReflexionsDelay(const float& p_reflexionsDelay)
    {
    	if(p_reflexionsDelay <= 0.3 && p_reflexionsDelay >= 0.0)
      {
        m_reflexionsDelay = p_reflexionsDelay ;
      }	
    }
    
    float SoundEnvironnement::getLateReverbGain() const
    {
      return m_lateReverbGain ;
    }
    
    void SoundEnvironnement::setLateReverbGain(const float& p_lateReverbGain)
    {
    	if(p_lateReverbGain <= 10.0 && p_lateReverbGain >= 0.0)
      {
        m_lateReverbGain = p_lateReverbGain ;
      }	
    }
    
    float SoundEnvironnement::getLateReverbDelay() const
    {
      return m_lateReverbDelay ;
    }
    
    void SoundEnvironnement::setLateReverbDelay(const float& p_lateReverbDelay)
    {
    	if(p_lateReverbDelay <= 0.1 && p_lateReverbDelay >= 0.0)
      {
        m_lateReverbDelay = p_lateReverbDelay ;
      }	
    }
    
    float SoundEnvironnement::getRoomRollofFactor() const
    {
      return m_roomRollofFactor ;
    }
    
    void SoundEnvironnement::setRoomRollofFactor(const float& p_roomRollofFactor)
    {
    	if(p_roomRollofFactor <= 10.0 && p_roomRollofFactor >= 0.0)
      {
        m_roomRollofFactor = p_roomRollofFactor ;
      }	
    }
    
    float SoundEnvironnement::getAirAbsorptionGainHF() const
    {
      return m_airAbsorptionGainHF ;
    }
    
    void SoundEnvironnement::setAirAbsorptionGainHF(const float& p_airAbsorptionGainHF)
    {
    	if(p_airAbsorptionGainHF <= 1.0 && p_airAbsorptionGainHF >= 0.892)
      {
        m_airAbsorptionGainHF = p_airAbsorptionGainHF ;
      }	
    }
    
    bool SoundEnvironnement::getDecayHFLimit() const
    {
      return m_decayHFLimit ;
    }
    
    void SoundEnvironnement::setDecayHFLimit(const bool& p_decayHFLimit)
    {
      m_decayHFLimit = p_decayHFLimit ;
    }

  }
}
