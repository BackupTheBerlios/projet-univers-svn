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

#include <sound/implementation/openal/wav_reader.h>

#include <vector>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        
        WavReader::WavReader(const ALuint& p_source, const std::string& p_fileName, const bool& p_isEvent)
        :Reader(p_source, p_fileName, p_isEvent), m_file(0)
        {}
        
        void WavReader::onInit()
        {
          InternalMessage("enter wavreader Init") ;   
          // Open the file
          SF_INFO fileInfos;
          m_file = sf_open(m_fileName.c_str(), SFM_READ, &fileInfos);
          if (!m_file)
          {
            //TODO paufiner erreur sur location ou format non reconnu
            ErrorMessage("[OpenAL::WavReader] Can't read the file: " + m_fileName);
          }
          //Get file information
          m_sampleRate = fileInfos.samplerate;
          m_samplesByBuffer  = fileInfos.channels * fileInfos.samplerate;
          switch (fileInfos.channels)
          {
            case 1 : m_format = AL_FORMAT_MONO16;   break;
            case 2 : m_format = AL_FORMAT_STEREO16; break;
            default :
              ErrorMessage("[OpenAL::WavReader] Audio Format audio not supported (more than 2 channel)");
          }
          
          //Load the buffers and link with the source
          loadBuffer(m_buffers[0]);
          loadBuffer(m_buffers[1]);
          alSourceQueueBuffers(m_source, 2, m_buffers);
          if (alGetError() != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::WavReader] Impossible to queue the buffers");
          }
          
          InternalMessage("leave wavreader Init") ;   
        }
          
        void WavReader::onClose()
        {
          sf_close(m_file);
        }
          
        void WavReader::loadBuffer(ALuint buffer)
        {
          //get the samples
          std::vector<ALshort> samples(m_samplesByBuffer);
          ALsizei totalRead = sf_read_short(m_file, &samples[0], m_samplesByBuffer);
          if (totalRead < m_samplesByBuffer)
          {
            if(m_isEvent)
            {
              m_finish = true;
            }
            else
            {
              sf_seek(m_file, 0, SEEK_SET);
            }
          }
          
          // load the buffer
          alBufferData(buffer, m_format, &samples[0], totalRead * sizeof(ALushort), m_sampleRate);
          if (alGetError() != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::WavReader] Impossible to load the buffer with the samples");
          }
        }
        
      }
    }
  }
}
