/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Morgan GRIGNARD Mathieu ROGER                 *
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
#include <vector>
#include <iostream>

#include <kernel/log.h>

#include <sound/implementation/openal/openal.h>
#include <sound/implementation/openal/wav_file_stream.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {
        WavFileStream::WavFileStream(const std::string& file_name)
        : FileStream(file_name),
          m_file(0)
        {}
        
        void WavFileStream::init(const ALuint& source,
                                 const int& position_in_file,
                                 const int& position_in_buffer,
                                 const bool& is_event)
        {
          InternalMessage("Sound", "enter WavFileStream::init") ;
          // Open the file
          SF_INFO fileInfos;
          m_file = sf_open(m_file_name.c_str(), SFM_READ, &fileInfos);
          if (!m_file)
          {
            //TODO paufiner erreur sur location ou format non reconnu
            ErrorMessage("[OpenAL::WavFileStream] Can't read the file: " + m_file_name);
            return;
          }
          //Get file information
          m_sample_rate = fileInfos.samplerate;
          m_samples_by_buffer = (ALsizei)(fileInfos.channels*fileInfos.samplerate*m_update_time) ;
          switch (fileInfos.channels)
          {
          case 1:
            m_format = AL_FORMAT_MONO16;
            break;
          case 2:
            m_format = AL_FORMAT_STEREO16;
            break;
          default:
            ErrorMessage("[OpenAL::WavFileStream] Audio Format audio not supported (more than 2 channel)");
            return;
          }

          int pos = 0;
          if (position_in_file > 0)
          {
            pos = position_in_file - m_samples_by_buffer + position_in_buffer + 1;
          }
          sf_seek(m_file, pos, SEEK_SET);

          //Load the buffers and link with the source
          alGenBuffers(2,m_buffers) ;
          loadBuffer(m_buffers[0],is_event);
          loadBuffer(m_buffers[1],is_event);
          alSourceQueueBuffers(source, 2, m_buffers);
          if (alGetError() != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::WavFileStream] Impossible to queue the buffers");
            return;
          }

          InternalMessage("Sound", "leave WavFileStream::init") ;   
          
        }

        
        void WavFileStream::close(const ALuint& source)
        {
          sf_close(m_file);
        }

        bool WavFileStream::loadBuffer(ALuint buffer,const bool& is_event)
        {
          InternalMessage("Sound", "enter WavFileStream::loadBuffer") ;   
          //get the samples
          std::vector<ALshort> samples(m_samples_by_buffer);
          ALsizei totalRead = 0 ;
          while (totalRead < m_samples_by_buffer)
          {
            ALsizei read = sf_read_short(m_file, &samples[totalRead], m_samples_by_buffer-totalRead);
            if (read > 0)
            {
              totalRead += read;
            }
            else
            {
              //End of file
              if(is_event)
              {
                //mark  for event the reader ready for destruction
                return true;
              }
              else
              {
                //loop for over sound
                sf_seek(m_file, 0, SEEK_SET) ;
              }
            }
          }
          
          // load the buffer
          alBufferData(buffer, m_format, &samples[0], totalRead * sizeof(ALushort), m_sample_rate);
          if (alGetError() != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::WavReader] " + m_file_name + " Impossible to load the buffer with the samples");
            return true ;
          }
          InternalMessage("Sound", "leave WavFileStream::loadBuffer") ;   
          return false ;
        }
        
      }
    }
  }
}
