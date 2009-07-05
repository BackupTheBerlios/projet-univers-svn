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
#include <string>
#include <sound/implementation/openal/stream.h>

namespace ProjetUnivers 
{
  namespace Sound 
  {
    namespace Implementation 
    {
      namespace OpenAL 
      {
        
        /// File stream
        class FileStream : public Stream
        {
        public:
          
          virtual bool update(const ALuint& source,const bool& is_event) ;
          
        protected:
        /*!
         @name Construction 
         */
        // @{

          /// Constructor.
          FileStream(const std::string& file_name);
          
        // @}

        private:
          
          /// Read the sound file to load the buffer with content
          virtual bool loadBuffer(ALuint buffer,const bool& is_event) = 0 ;
          
        };
          
      }
    }
  }
}
