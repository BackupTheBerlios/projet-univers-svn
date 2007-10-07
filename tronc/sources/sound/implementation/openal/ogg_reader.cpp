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
#include <sound/implementation/openal/ogg_reader.h>

#include <vector>
#include <iostream>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        
        OggReader::OggReader()
        :Reader(), m_stream(0), m_file(0)
        {}
        
        OggReader::OggReader(ALuint p_source, std::string p_fileName, bool p_isEvent)
        :Reader(p_source, p_fileName, p_isEvent), m_stream(0), m_file(0)
        {}
        
        void OggReader::onInit()
        {
          InternalMessage("enter oggreader Init") ;  
          // Open File
          m_file = fopen(m_fileName.c_str(), "rb");
          if (!m_file)
          {
              ErrorMessage("[OpenAL::OggReader] Can't read the file: " + m_fileName);
          }

          // Create Ogg Stream on the file
          m_stream = new OggVorbis_File();
          int error = ov_open(m_file, m_stream, NULL, 0);
          if (error < 0)
          {
              ErrorMessage("[OpenAL::OggReader] Can't read the samples");
          }

          // Récupération des informations du son
          vorbis_info* Infos = ov_info(m_stream, -1);

          //TODO voir l'utilité des cast vu coté wav
          m_sampleRate = Infos->rate;
          m_samplesByBuffer  = Infos->channels * Infos->rate; 
          switch (Infos->channels)
          {
            case 1 : m_format = AL_FORMAT_MONO16;   break;
            case 2 : m_format = AL_FORMAT_STEREO16; break;
            default :
              ErrorMessage("[OpenAL::OggReader] Audio Format audio not supported (more than 2 channel)");
          }

          
          //Load the buffers and link with the source
          loadBuffer(m_buffers[0]);
          loadBuffer(m_buffers[1]);
          alSourceQueueBuffers(m_source, 2, m_buffers);
          if (alGetError() != AL_NO_ERROR)
          {
            InformationMessage("[OpenAL::OggReader] Impossible to queue the buffers");
          }
          
          InternalMessage("leave oggreader Init") ;  
        }
          
        void OggReader::onClose()
        {
          ov_clear(m_stream);
          delete m_stream;
          fclose(m_file);
        }
          
        void OggReader::loadBuffer(ALuint buffer)
        {
          //get the samples
          std::vector<ALshort> samples(m_samplesByBuffer);
          ALsizei totalSize  = m_samplesByBuffer * sizeof(ALshort);
          ALsizei totalRead  = 0;
          char*   samplesPtr = reinterpret_cast<char*>(&samples[0]);

          while (totalRead < totalSize)
          {
              ALsizei read = ov_read(m_stream, samplesPtr + totalRead, totalSize - totalRead, 0, 2, 1, NULL);
              if (read > 0)
              {
                  totalRead += read;
              }
              else
              {
                //End of file
                if(m_isEvent)
                {
                  //mark  for event the reader ready for destruction
                  m_finish = true;
                  break ;
                }
                else
                {
                  //loop for over sound
                  ov_pcm_seek(m_stream,0);
                }
              }
          }
          
          // load the buffer
          alBufferData(buffer, m_format, &samples[0], totalRead, m_sampleRate);
          if (alGetError() != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::OggReader] Impossible to load the buffer with the samples");
          }
        }     
        
      }
    }
  }
}
