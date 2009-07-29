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

        class Stream ;
        
        /// Read a sound stream
        class Reader
        {
        public:
          
          virtual ~Reader() ;

          Reader(const ALuint& source,Stream*,const bool& is_event) ;
          
          /// Open the file, create and load the 2 buffers to link to the source
          virtual void onInit(const int& position_in_file,const int& position_in_buffer) ;
          
          /// Look for empty buffer which are already heard and load them.
          virtual void update() ;
          
          /// Stop reading.
          virtual void onClose() ;

          bool isFinished() const ;
          
        private:
          
          ALuint  m_source ;
          Stream* m_stream ;
          bool    m_is_event ;
          bool    m_is_finished ;
          bool    m_is_initialised ;
          
        };
      }
    }
  }
}
