/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007-2008 Morgan GRIGNARD Mathieu ROGER                 *
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
#ifndef PU_SOUND_IMPLEMENTATION_OPENAL_MANAGER_H_
#define PU_SOUND_IMPLEMENTATION_OPENAL_MANAGER_H_


#include <kernel/timer.h>
#include <kernel/object.h>

#include <sound/implementation/openal/reader.h>

#include <vector>
#include <string>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        
        /// Update the buffers and create/delete the reader during their life.
        class Manager
        {
        public:
        /*!
          @name Construction 
        */
        // @{
        
          /// Constructor 
          Manager() ;

          ~Manager() ;

        // @}
        
          /// Create a reader which match the soundFile type
          Reader* createReader(const ALuint& p_source, 
                               const std::string& p_fileName,
                               const bool& p_isEvent, const int& m_posInFile, 
                               const int& m_posInBuffer) ;
          
          /// Close the files of finish sounds, delete the  buffers
          void update() ;
            
        private:
          
          std::vector<Reader*> m_readers ;
          Kernel::Timer m_timer ;
          float m_updateTime ;
             
        };
      }
    }
  }
}


#endif /*PU_SOUND_IMPLEMENTATION_OPENAL_MANAGER_H_*/
