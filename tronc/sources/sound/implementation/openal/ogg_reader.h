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
#ifndef PU_SOUND_IMPLEMENTATION_OPENAL_OGG_READER_H_
#define PU_SOUND_IMPLEMENTATION_OPENAL_OGG_READER_H_

#include <vorbis/vorbisfile.h>
#include <sound/implementation/openal/reader.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        /// Interface  of a soundfile reader use for streaming
        /*!
                      */
        class OggReader : public Reader
        {
        
        public:
        /*!
                     @name Construction 
                    */
        // @{
        
          /// Constructor by default for container like vector
          OggReader() ;
          
          /// Constructor in use
          OggReader(ALuint p_source, std::string p_fileName, bool p_isEvent) ;
        // @}
          
          
          /// @Implements
          /// Open the file, create and load the 2 buffers to link to the source
          virtual void onInit();
          
          /// @Implements
          /// Close the file, delete the  buffers
          virtual void onClose();
          
          
          
        private:
          
          /// @Implements
          /// Read the sound file to load the buffer with content
          virtual void loadBuffer(ALuint buffer);
          
          ///File
          OggVorbis_File* m_stream;
          FILE* m_file;        
        };
      }
    }
  }
}


#endif /*PU_SOUND_IMPLEMENTATION_OPENAL_OGG_READER_H_*/
