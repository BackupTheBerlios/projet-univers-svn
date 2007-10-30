/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Morgan GRIGNARD                                    *
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
        /// Reader manager, update the buffers and create/delete the reader during their life
        /*!
        */
        class Manager
        {
        
        public:
        /*!
          @name Construction 
        */
        // @{
        
          /// Constructor 
          Manager(Kernel::Object* listener, Kernel::Object* reference) ;
        // @}
        
          ~Manager() ;
          
          
          /// Create a reader which match the soundFile type
          Reader* createReader(ALuint p_source,std::string p_fileName, bool p_isEvent) ;
          
          /// Give a pointer to the listener
          Kernel::Object* getListener() ;
          
          /// Give a pointer to the reference object of the world/soundWorld if it isn't the same
          Kernel::Object* getReference() ;
          
          /// Close the files of finish sounds, delete the  buffers
          void update() ;
            
        private:
          
          std::vector<Reader*> m_readers ;
          Kernel::Timer m_timer ;
          float m_updateTime ;
          Kernel::Object* m_listener ;
          Kernel::Object* m_reference ;
             
        };
      }
    }
  }
}


#endif /*PU_SOUND_IMPLEMENTATION_OPENAL_MANAGER_H_*/
