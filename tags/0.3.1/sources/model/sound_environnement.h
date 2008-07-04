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
#ifndef PU_MODEL_SOUND_ENVIRONNEMENT_H_
#define PU_SOUND_SOUND_ENVIRONNEMENT_H_

#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Model {
    
    /// Describe the reverb effect of the source in this environnement
    class SoundEnvironnement : public Kernel::Trait
    {
    public:

    /*!
      @name Construction
    */
    //@{
    
      /// Default constructor with default OpenAL parameters
      SoundEnvironnement() ;
      
      /// Constructor
      SoundEnvironnement(const float& p_density, const float& p_diffusion,
        const float& p_gain, const float& p_gainHF, const float& p_decayTime,
        const float& p_decayHFRatio, const float& p_reflexionsGain,
        const float& p_reflexionsDelay, const float& p_lateReverbGain,
        const float& p_lateReverbDelay, const float& p_roomRollofFactor,
        const float& p_airAbsorptionGainHF, const bool& p_decayHFLimit) ;
      
     // @}
     
     /*!
       @name Access methods
     */
     //@{

       float getDensity() const;
       void setDensity(const float& p_density) ;
       float getDiffusion() const;
       void setDiffusion(const float& p_diffusion) ;
       float getGain() const;
       void setGain(const float& p_gain) ;
       float getGainHF() const;
       void setGainHF(const float& p_gainHF) ;
       float getDecayTime() const;
       void setDecayTime(const float& p_decayTime) ;
       float getDecayHFRatio() const;
       void setDecayHFRatio(const float& p_decayHFRatio) ;
       float getReflexionsGain() const;
       void setReflexionsGain(const float& p_reflexionsGain) ;
       float getReflexionsDelay() const;
       void setReflexionsDelay(const float& p_reflexionsDelay) ;
       float getLateReverbGain() const;
       void setLateReverbGain(const float& p_lateReverbGain) ;
       float getLateReverbDelay() const;
       void setLateReverbDelay(const float& p_lateReverbDelay) ;
       float getRoomRollofFactor() const;
       void setRoomRollofFactor(const float& p_roomRollofFactor) ;
       float getAirAbsorptionGainHF() const;
       void setAirAbsorptionGainHF(const float& p_airAbsorptionGainHF) ;
       bool getDecayHFLimit() const;
       void setDecayHFLimit(const bool& p_decayHFLimit) ;

     //@}
      
     private:
    
       /// See OpenAl doc for more information on parameters
       float m_density ;
       float m_diffusion ;
       float m_gain ;
       float m_gainHF ; 
       float m_decayTime ;
       float m_decayHFRatio ;
       float m_reflexionsGain ;
       float m_reflexionsDelay ;
       float m_lateReverbGain ;
       float m_lateReverbDelay ;
       float m_roomRollofFactor ;
       float m_airAbsorptionGainHF ;
       bool  m_decayHFLimit ;
       
    };
  }
}

#endif /*PU_MODEL_SOUND_ENVIRONNEMENT_H_*/
