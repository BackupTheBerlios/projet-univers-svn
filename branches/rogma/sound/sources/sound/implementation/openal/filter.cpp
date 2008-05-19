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
#include <sound/implementation/openal/filter.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        Filter::Filter(const float& gain, const float& gainHF)
        : m_gain(gain), m_gainHF(gainHF)
        {}
        
        Filter operator+(const Filter& p_f1, const Filter& p_f2)
        {
          return Filter(p_f1.m_gain * p_f2.m_gain, p_f1.m_gainHF * p_f2.m_gainHF);
        }
        Filter operator-(const Filter& p_f1, const Filter& p_f2)
        {
          float r_gain ;
          float r_gainHF ;
          if(p_f2.m_gain != 0)
          {
          	r_gain = p_f1.m_gain / p_f2.m_gain ;
          }
          else
          {
          	r_gain = 0 ;
          }
          if(p_f2.m_gainHF != 0)
          {
          	r_gainHF = p_f1.m_gainHF / p_f2.m_gainHF ;
          }
          else
          {
          	r_gainHF = 0 ;
          }
          return Filter(r_gain , r_gainHF);	
        } 

		float Filter::getGain() const
		{
		  return m_gain ;	
		}
		
        void Filter::setGain(const float& p_gain)
        {
          m_gain = p_gain ;
        }
        
        float Filter::getGainHF() const
        {
          return m_gainHF ;	
        }
        
        void Filter::setGainHF(const float& p_gainHF)
        {
          m_gainHF = p_gainHF ;
        }   
             
      }
    }
  }
}
