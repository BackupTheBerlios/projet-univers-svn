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
#include <sound/implementation/openal/reader.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        Reader::Reader(const ALuint& p_source, const std::string& p_fileName, const bool& p_isEvent) 
        : m_source(p_source), m_fileName(p_fileName), m_isEvent(p_isEvent), m_finish(false),
          m_format(0), m_sampleRate(0), m_samplesByBuffer(0)  
        {
          InformationMessage("Al status enter constructor " + getErrorString(alGetError())) ;
          alGenBuffers(2, m_buffers);
          InformationMessage("Al status leave constructor " + getErrorString(alGetError())) ;
        }
        
        Reader::~Reader()
        {
          alSourceStop(m_source) ;
          alDeleteBuffers(2, m_buffers) ;
          alDeleteSources(1,&m_source) ;
        }
          
        void Reader::update()
        {
          InformationMessage("Enter update reader") ;   
          // Get the empty buffers
          ALint NbProcessed;
          alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &NbProcessed); 
          // Load this buffers with content
          for (ALint i = 0; i < NbProcessed && !m_finish; ++i)
          {
            InformationMessage("call load") ; 
            ALuint buffer;
            alSourceUnqueueBuffers(m_source, 1, &buffer);
            loadBuffer(buffer);
            alSourceQueueBuffers(m_source, 1, &buffer);
          }
          InformationMessage("leave update reader") ;   
        }
        
      }
    }
  }
}
