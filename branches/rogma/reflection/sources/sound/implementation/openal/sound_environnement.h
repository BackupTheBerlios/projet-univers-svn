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
#pragma once

#include <kernel/trait_view.h>

#include <model/sound_environnement.h>

#include <sound/implementation/openal/real_world_view_point.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {
    
        /// View on a soundEnvironnement, create the corresponding reverb effect
        class SoundEnvironnement : 
                        public Kernel::TraitView<Model::SoundEnvironnement,
                                                 RealWorldViewPoint>
        {
        public:

          /// Accessor to the effect slot
          ALuint getAuxEffectSlot() ;
      
        protected:
        /*!
          @name Updates.
        */
        // @{
                  
          void onInit() ;
                      
          void onClose() ;
                      
          void onUpdate() ;

        // @}      
      
        private:
    
          /// Container of an effect
          ALuint m_auxEffectSlot ;
          /// Effect
          ALuint m_effect ;
       
        };
    
      }
    }
  }
}
