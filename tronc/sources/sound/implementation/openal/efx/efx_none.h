/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Morgan GRIGNARD Mathieu ROGER                      *
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
#ifndef PU_SOUND_IMPLEMENTATION_OPENAL_EFX_EFX_NONE_H_
#define PU_SOUND_IMPLEMENTATION_OPENAL_EFX_EFX_NONE_H_

#include <AL/al.h>
#include <AL/alc.h>

namespace ProjetUnivers {

  namespace Model {
    class SoundEnvironnement ;
  }
  
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        /// Special sound effects through efx
        /*! 
          This implementation does nothing; on purpose.
        */
        namespace EFX
        {
          /// Get extension parameters
          ALint* getParameters() ;
          
          /// Init extension.
          void init(ALCdevice* device) ;
          
          /// close the module.
          void close() ;
          
          /// Create an effect slot.
          void createEffect(ALuint* effect,ALuint* auxEffectSlot) ;
          
          /// Create an effect slot.
          void destroyEffect(ALuint* effect,ALuint* auxEffectSlot) ;
          
          /// Set effect slot parameters according to model.
          void changeEffect(ALuint effect,
                            ALuint auxEffectSlot,
                            Model::SoundEnvironnement* env) ;
          
          /// Apply an effect to a source.
          void applyEffectToSource(ALuint source,ALuint auxEffectSlot) ;
          
        }
      }
    }
  }
}

#endif /*PU_SOUND_IMPLEMENTATION_OPENAL_EFX_EFX_NONE_H_*/
