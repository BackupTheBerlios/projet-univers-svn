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
#ifndef PU_SOUND_IMPLEMENTATION_OPENAL_FILTER_H_
#define PU_SOUND_IMPLEMENTATION_OPENAL_FILTER_H_

#include <kernel/trait.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
    
        /// Describe attenuation filter for occlusion and obstruction
        class Filter
        {
        public:
    
          /// Constructor
          Filter(const float& p_gain, const float& p_gainHF) ;
      
          /// Add two filters
          friend Filter operator+(const Filter& p_f1, const Filter& p_f1) ;
          /// Sub the second to the first filter
          // No meaning? When we sub a 0.0 gain we can't know the gain before...
          // @TODO see if usefull
          friend Filter operator-(const Filter& p_f1, const Filter& p_f1) ;
          
        /*!
          @name Access methods
        */
        // @{
          
          float getGain() const ;
          void setGain(const float& p_gain) ;
          float getGainHF() const ;
          void setGainHF(const float& p_gainHF) ;
        
        // @}
        private:
    
          /// @todo describe
          float m_gain ;
          
          /// @todo describe
          float m_gainHF ;
    
        // @}
       
        };
            
    
      }
    }
  }
}

#endif /*PU_SOUND_IMPLEMENTATION_OPENAL_FILTER_H_*/
