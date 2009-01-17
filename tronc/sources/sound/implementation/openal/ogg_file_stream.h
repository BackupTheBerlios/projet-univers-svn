/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2009 Morgan GRIGNARD Mathieu Roger                 *
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
#pragma once

#include <string>
#include <AL/al.h>
#include <vorbis/vorbisfile.h>
#include <sound/implementation/openal/file_stream.h>

namespace ProjetUnivers 
{
  namespace Sound 
  {
    namespace Implementation 
    {
      namespace OpenAL 
      {
        
        /// Ogg file stream read on the fly 
        class OggFileStream : public FileStream
        {
        public:
        /*!
         @name Construction 
         */
        // @{

          /// Constructor.
          OggFileStream(const std::string& file_name) ;
          
        // @}

          /// Open the stream
          virtual void init(const ALuint& source,
                            const int& position_in_file,
                            const int& position_in_buffer,
                            const bool& is_event) ;

          /// Close the stream.
          virtual void close(const ALuint& source) ;

        private:

          /// Read the sound file to load the buffer with content
          virtual bool loadBuffer(ALuint buffer,const bool& is_event) ;
          
          /// File read
          OggVorbis_File* m_stream ;
          
          /// Flip buffers 
          ALuint          m_buffers[2] ;
          
        };
          
      }
    }
  }
}
