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
#include <kernel/log.h>

#include <sound/implementation/openal/file_stream.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        FileStream::FileStream(const std::string& file_name)
        : Stream(file_name)
        {}

        bool FileStream::update(const ALuint& source,const bool& is_event)
        {
          InformationMessage("Sound", "Enter FileStream::update") ;
          // Get the empty buffers
          ALint NbProcessed ;
          alGetSourcei(source,AL_BUFFERS_PROCESSED,&NbProcessed) ;
          // Load this buffers with content
          bool is_finished = false ;
          for (ALint i = 0; i < NbProcessed && !is_finished; ++i)
          {
            InformationMessage("Sound", "call load") ;
            ALuint buffer;
            alSourceUnqueueBuffers(source,1,&buffer) ;
            is_finished = loadBuffer(buffer,is_event) ;
            alSourceQueueBuffers(source,1,&buffer) ;
          }
          InformationMessage("Sound", "leave FileStream::update") ;
          
          return !is_finished ;
        }
        
      }
    }
  }
}
