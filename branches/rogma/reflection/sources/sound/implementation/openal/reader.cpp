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
#include <sound/implementation/openal/stream.h>
#include <sound/implementation/openal/reader.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        Reader::~Reader()
        {
          close() ;
        }

        Reader::Reader(Stream* stream,const bool& is_event)
        : m_source(0),
          m_stream(stream),
          m_is_event(is_event),
          m_is_finished(false),
          m_is_initialised(false)
        {}

        void Reader::init(const int& position_in_file,const int& position_in_buffer)
        {
          alGenSources(1,&m_source) ;
          m_stream->init(m_source,position_in_file,position_in_buffer,m_is_event) ;
          addSource() ;
          m_is_initialised = true ;
        }

        void Reader::update()
        {
          m_is_finished = !m_stream->update(m_source,m_is_event) ;
        }
        
        void Reader::close()
        {
          if(! m_is_initialised)
            return ;
          stopSourceAndUnQueueBuffers() ;
          alDeleteSources(1,&m_source) ;
          removeSource() ;
          m_source = 0 ;
          ALenum error = alGetError() ; 
          if (error != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::Reader::close()] " + m_stream->getFileName() + " " + getErrorString(error)) ;
          }
          m_is_initialised = false ;
        }

        bool Reader::isFinished() const
        {
          return m_is_finished ;
        }

        ALuint Reader::getSource() const
        {
          return m_source ;
        }
        
        Stream* Reader::getStream() const
        {
          return m_stream ;
        }

        void Reader::stopSourceAndUnQueueBuffers()
        {
          ALint state;
          alGetSourcei(m_source,AL_SOURCE_STATE,&state) ;
          if (state == AL_PLAYING)
          {
            alSourceStop(m_source) ;
            ALenum error = alGetError() ;
            if (error != AL_NO_ERROR)
            {
              ErrorMessage("[OpenAL::Reader::stopSourceAndUnQueueBuffers::stop] " + m_stream->getFileName() + getErrorString(error)) ;
            }
          }

          ALint queue_size = 0 ;
          alGetSourcei(m_source,AL_BUFFERS_QUEUED,&queue_size) ;
          ALenum error = alGetError() ;
          if (error != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::Reader::stopSourceAndUnQueueBuffers::get] " + m_stream->getFileName() + getErrorString(error)) ;
          }
          else if (queue_size > 0)
          {
            ALuint* buffers = new ALuint[std::max(0,queue_size)];
            alSourceUnqueueBuffers(m_source,queue_size,buffers) ;
            error = alGetError() ;
            if (error != AL_NO_ERROR)
            {
              ErrorMessage("[OpenAL::Reader::stopSourceAndUnQueueBuffers::unqueue] " + m_stream->getFileName() + getErrorString(error)) ;
            }
            delete[] buffers ;
          }
        }

      }
    }
  }
}
