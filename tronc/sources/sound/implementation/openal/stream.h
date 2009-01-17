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
#pragma once
#include <AL/al.h>
#include <string>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        /// A stream on a sound
        class Stream
        {

        public:

          /// Open the file, create and load the 2 buffers to link to the source
          virtual void init(const ALuint& source,
                            const int& position_in_file,
                            const int& position_in_buffer,
                            const bool& is_event) = 0 ;
          
          /// Return false if finished
          virtual bool update(const ALuint& source,const bool& is_event) = 0 ;
          
          /// Close the stream.
          virtual void close(const ALuint& source) = 0 ;
          
          virtual ~Stream() ;
          
        protected:

        /*!
         @name Construction 
         */
        // @{


          Stream(const std::string& file_name) ;

        // @}

          /// SoundFile name
          std::string m_file_name ;

          /// Indicate the buffer size in seconds
          float m_update_time ;

          /// Sound format
          ALenum m_format ;

          /// Sound rate
          ALsizei m_sample_rate ;

          /// Sample which must be read for a buffer 
          ALsizei m_samples_by_buffer ;

        };
      }
    }
  }
}
