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
#include <sound/implementation/openal/ogg_file_stream.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        OggFileStream::OggFileStream(const std::string& file_name)
        : FileStream(file_name), 
          m_stream(NULL)
        {}

        void OggFileStream::init(const ALuint& source,
                                 const int& position_in_file,
                                 const int& position_in_buffer,
                                 const bool& is_event)
        {
          // create buffers for reading in flip mode
          alGenBuffers(2,m_buffers) ;
          
          InternalMessage("Sound", "enter oggreader Init") ;

          // Create Ogg Stream on the file
          m_stream = new OggVorbis_File() ;
          int error = ov_fopen((char*)m_file_name.c_str(),m_stream) ;
          if (error < 0)
          {
            ErrorMessage("[OpenAL::OggReader] Can't read the samples") ;
            return ;
          }

          // Get sound information
          vorbis_info* Infos = ov_info(m_stream,-1) ;

          m_sample_rate = Infos->rate ;
          m_samples_by_buffer = (ALsizei)(Infos->channels * Infos->rate * m_update_time) ;
          switch (Infos->channels)
          {
          case 1:
            m_format = AL_FORMAT_MONO16 ;
            break;
          case 2:
            m_format = AL_FORMAT_STEREO16 ;
            break;
          default:
            ErrorMessage("[OpenAL::OggReader] Audio Format audio not supported (more than 2 channel)") ;
            return ;
          }

          int pos = 0 ;
          if (position_in_file > 0)
          {
            pos = position_in_file-m_samples_by_buffer+position_in_buffer+1 ;
          }
          ov_pcm_seek(m_stream,pos) ;

          // Load the buffers
          loadBuffer(m_buffers[0],is_event) ;
          loadBuffer(m_buffers[1],is_event) ;
          alSourceQueueBuffers(source,2,m_buffers) ;
          if (alGetError() != AL_NO_ERROR)
          {
            InformationMessage("Sound",
                "[OpenAL::OggReader] Impossible to queue the buffers") ;
            return ;
          }

          InternalMessage("Sound", "leave oggreader Init") ;
        }

        void OggFileStream::close(const ALuint& source)
        {
          ov_clear(m_stream) ;
          delete m_stream ;
          alSourceStop(source) ;
          alDeleteBuffers(2,m_buffers) ;
        }
        
        bool OggFileStream::loadBuffer(ALuint buffer,const bool& is_event)
        {
          //get the samples
          std::vector<ALshort> samples(m_samples_by_buffer) ;
          ALsizei totalSize = m_samples_by_buffer * sizeof(ALshort) ;
          ALsizei totalRead = 0 ;
          char* samplesPtr = reinterpret_cast<char*>(&samples[0]) ;

          while (totalRead < totalSize)
          {
            ALsizei read = ov_read(m_stream,samplesPtr+totalRead,totalSize-totalRead,0,2,1,NULL) ;
            if (read > 0)
            {
              totalRead += read ;
            }
            else
            {
              //End of file
              if (is_event)
              {
                // mark  for event the reader ready for destruction
                return true ;
              }
              else
              {
                //loop for over sound
                ov_pcm_seek(m_stream,0) ;
              }
            }
          }

          // load the buffer
          alBufferData(buffer,m_format,&samples[0],totalRead,m_sample_rate) ;
          if (alGetError() != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::OggReader]" + m_file_name + " Impossible to load the buffer with the samples") ;
            return true ;
          }
          
          return false ;
        }


      }
    }
  }
}
