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
        /*!
          When an event sound reader has finished, destroy it.
        */
        class Manager
        {
        public:
        /*!
         @name Construction 
         */
        // @{

          /// Constructor 
          Manager();

          /// Add a resource to the cache
          void cacheRessource(const std::string&) ;
          
          ~Manager();

        // @}
        /*!
         @name Reader management
        */
        // @{

          /// Create a reader which match the soundFile type
          Reader* createReader(const std::string& fileName,const bool& isEvent,
                               const int& posInFile,const int& posInBuffer) ;

          /// Close the files of finish sounds, delete the finished readers
          void update();

        // @}
        private:

          /// Get a stream by name.
          Stream* getStream(const std::string&) ;
          void releaseStream(Stream*) ;
          
          /// Active readers
          std::vector<Reader*> m_readers ;
          Kernel::Timer m_timer ;
          float m_updateTime ;

          /// Resource caching
          std::map<std::string,Stream*> m_cached_streams ;
          std::set<Stream*> m_streams ;
        };
      }
    }
  }
}
