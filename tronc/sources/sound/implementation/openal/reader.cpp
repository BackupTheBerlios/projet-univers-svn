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
        {}

        Reader::Reader(const ALuint& source,Stream* stream,const bool& is_event)
        : m_source(source),
          m_stream(stream),
          m_is_event(is_event),
          m_is_finished(false),
          m_is_initialised(false)
        {}

        void Reader::onInit(const int& position_in_file,const int& position_in_buffer)
        {
          m_stream->init(m_source,position_in_file,position_in_buffer,m_is_event) ;
          m_is_initialised = true ;
        }

        void Reader::update()
        {
          m_is_finished = !m_stream->update(m_source,m_is_event) ;
        }
        
        void Reader::onClose()
        {
          if(! m_is_initialised)
            return ;
          stopSourceAndUnQueueBuffers(m_source) ;
          alDeleteSources(1,&m_source) ;
          ALenum error = alGetError() ; 
          if (error != AL_NO_ERROR)
          {
            ErrorMessage("[OpenAL::OggReader] " + getErrorString(error)) ;
          }
          m_is_initialised = false ;
        }

        bool Reader::isFinished() const
        {
          return m_is_finished ;
        }
        
      }
    }
  }
}
