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
#include <sound/implementation/openal/ogg_cached_stream.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        OggCachedStream::OggCachedStream(const std::string& file_name)
        : Stream(file_name)
        {
          OggVorbis_File* stream ;
          InternalMessage("Sound","loading " + file_name) ;
          // Create Ogg Stream on the file
          stream = new OggVorbis_File() ;
          int error = ov_fopen((char*)m_file_name.c_str(),stream) ;
          if (error < 0)
          {
            ErrorMessage("[OpenAL::OggCachedStream] Can't read the samples") ;
            return ;
          }

          // Get sound information
          vorbis_info* Infos = ov_info(stream,-1) ;

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
            ErrorMessage("[OpenAL::OggCachedStream] Audio Format audio not supported (more than 2 channel)") ;
            return ;
          }

          int pos = 0 ;
          ov_pcm_seek(stream,pos) ;
          
          InternalMessage("Sound", "OggCachedStream loading buffers") ;
          
          // load all the buffers
          bool is_fully_read = false ;
          while (!is_fully_read)
          {
            ALuint buffer ;
            alGenBuffers(1,&buffer) ;
            is_fully_read = loadBuffer(stream,buffer) ;
            m_buffers.push_back(buffer) ;
          }
          ov_clear(stream) ;
          delete stream ;
        }

        void OggCachedStream::init(const ALuint& source,
                                 const int& position_in_file,
                                 const int& position_in_buffer,
                                 const bool& is_event)
        {
          InternalMessage("Sound", "enter OggCachedStream Init : " + Kernel::toString(m_buffers.size())) ;
          
          for(std::vector<ALuint>::iterator buffer = m_buffers.begin() ;
              buffer != m_buffers.end() ;
              ++buffer)
          {
            ALuint temp = *buffer ;
            alSourceQueueBuffers(source,1,&temp) ;
            
            if (alGetError() != AL_NO_ERROR)
            {
              InformationMessage("Sound","[OpenAL::OggCachedStream] Impossible to queue the buffers") ;
              return ;
            }
          }
          
          InternalMessage("Sound", "leave OggCachedStream Init") ;
        }

        OggCachedStream::~OggCachedStream()
        {
          for(std::vector<ALuint>::iterator buffer = m_buffers.begin() ;
              buffer != m_buffers.end() ;
              ++buffer)
          {
            alDeleteBuffers(1,&*buffer) ;
          }
        }
        
        bool OggCachedStream::update(const ALuint& source,const bool& is_event)
        {
          InformationMessage("Sound", "Enter OggCachedStream::udpate") ;
          ALint remaining ;
          alGetSourcei(source,AL_BUFFERS_QUEUED,&remaining) ;
          return remaining > 0 ;
        }
        
        bool OggCachedStream::loadBuffer(OggVorbis_File* m_stream,ALuint buffer)
        {
          //get the samples
          std::vector<ALshort> samples(m_samples_by_buffer) ;
          ALsizei totalSize = m_samples_by_buffer * sizeof(ALshort) ;
          ALsizei totalRead = 0 ;
          char* samplesPtr = reinterpret_cast<char*>(&samples[0]) ;
          bool finished = false ;
          
          while (totalRead < totalSize && !finished)
          {
            InternalMessage("Sound","OggCachedStream::loadBuffer reading") ;
            ALsizei read = ov_read(m_stream,samplesPtr+totalRead,totalSize-totalRead,0,2,1,NULL) ;
            if (read > 0)
            {
              totalRead += read ;
            }
            else
            {
              finished = true ;
            }
          }
          InternalMessage("Sound","OggCachedStream::loadBuffer copying one buffer") ;

          // load the buffer
          alBufferData(buffer,m_format,&samples[0],totalRead,m_sample_rate) ;
          if (alGetError() != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::OggCachedStream] Impossible to load the buffer with the samples") ;
          }
          
          return finished ;
        }


      }
    }
  }
}
