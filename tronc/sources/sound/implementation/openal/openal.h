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
#ifndef PU_SOUND_IMPLEMENTATION_OPENAL_OPENAL_H_
#define PU_SOUND_IMPLEMENTATION_OPENAL_OPENAL_H_

#include <AL/al.h>
#include <AL/alc.h>

#include <sound/implementation/openal/manager.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      
      /// Sound implementation throught OpenAL.
      /*!                  
                */
      namespace OpenAL {
        
        /// Initialisation of OpenAL specific.
        void init() ;
        
        /// Termination of OpenAL specific.
        void close() ;
        
        /// Update OpenAL
        void update() ;
        
        /// Create the manager
        void build(Kernel::Object* listener, Kernel::Object* reference) ;
        
        /// Humanly readable OpenAL error code. 
        std::string getErrorString(const ALenum&) ;
        
        Manager* getManager();
      }
    }
  }
}

#endif /*PU_SOUND_IMPLEMENTATION_OPENAL_OPENAL_H*/
