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
#ifndef PU_SOUND_IMPLEMENTATION_OPENAL_READER_H_
#define PU_SOUND_IMPLEMENTATION_OPENAL_READER_H_

#include <AL/al.h>

#include <string>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        /// Interface  of a soundfile reader use for streaming
        /*!
        */
        class Reader
        {
        
        public:
        
          virtual ~Reader() ;
          
          
          /// @Implements
          /// Open the file, create and load the 2 buffers to link to the source
          virtual void onInit() = 0 ;
          
          ///Look for empty buffer which are already heard and load them with content
          void update() ;
          
          /// @Implements
          /// Close the file, delete the  buffers
          virtual void onClose() = 0 ;
          
          ///Indicate the sound life end and that the manager can delete this reader
          bool m_finish ;
          
        protected:
        
          /*!
        name Construction 
        */
        // @{
          
          /// Constructor in use
          Reader(const ALuint& p_source, const std::string& p_fileName, const bool& p_isEvent) ;
        // @}
          
          /// OpenAL source
          ALuint m_source ;
          /// OpenAL buffers 
          ALuint m_buffers[2] ;
          /// SoundFile name
          //TODO voir le format qu'on donne en paramètre, plutot travailler sur une copie
          std::string m_fileName ;
          
          /// Indicate if the sound is an event and don't must loop
          bool m_isEvent ;
          
          ///Sound format
          ALenum m_format ;
          ///Sound rate
          ALsizei m_sampleRate ;
          ///Sample which must be read for a buffer 
          ALsizei m_samplesByBuffer ; 
        
        private:
          /// @Implements
          /// Read the sound file to load the buffer with content
          virtual void loadBuffer(ALuint buffer) = 0 ;
          
        };
      }
    }
  }
}


#endif /*PU_SOUND_IMPLEMENTATION_OPENAL_READER_H_*/
