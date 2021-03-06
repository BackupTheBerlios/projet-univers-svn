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
#include <AL/alc.h>

#include <sound/implementation/openal/manager.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      
      /// Sound implementation through OpenAL.
      namespace OpenAL 
      {
        
        /// Initialization of OpenAL specific.
        void init() ;
        
        /// Termination of OpenAL specific.
        void close() ;
        
        /// Update OpenAL
        void update() ;
      
        /// Humanly readable OpenAL error code. 
        std::string getErrorString(const ALenum&) ;
        
        Manager* getManager();
        
        /// Indicate that a new source has been created
        void addSource() ;
        /// Indicate that a source has been destroyed
        void removeSource() ;

        /// Get the max number of simultaneous sources.
        int getMaximumNumberOfSources() ;
      }
    }
  }
}

