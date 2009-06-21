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

#include <map>
#include <string>
#include <vector>
#include <AL/al.h>
#include <kernel/timer.h>
#include <kernel/object.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        class Reader ;
        class Stream ;
        
        /// Update the buffers and create/delete the reader during their life.
        class Manager
        {
        public:
        /*!
         @name Construction 
         */
        // @{

          /// Constructor 
          Manager();

          /// Add a ressource to the cache
          void cacheRessource(const std::string&) ;
          
          ~Manager();

        // @}

          /// Create a reader which match the soundFile type
          Reader* createReader(
              const ALuint& p_source,
              const std::string& p_fileName, const bool& p_isEvent,
              const int& m_posInFile, const int& m_posInBuffer);

          /// Close the files of finish sounds, delete the  buffers
          void update();

        private:

          Stream* getStream(const std::string&) ;
          
          std::vector<Reader*> m_readers;
          Kernel::Timer m_timer;
          float m_updateTime;

          std::map<std::string,Stream*> m_cached_streams ;
          std::set<Stream*> m_streams ;
          
        };
      }
    }
  }
}
