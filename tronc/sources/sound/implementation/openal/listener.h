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

#include <sound/implementation/openal/sound_listener.h>
#include <sound/implementation/openal/real_world_view_point.h>
#include <sound/implementation/listener.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Implementation
    {
      namespace OpenAL
      {

        /// Sound Observer view.
        class Listener : public Kernel::TraitView<Implementation::Listener,
                                                  RealWorldViewPoint>, 
                         public SoundListener
        {
        protected:
        /*!
         @name Access methods
         
         Redefinition of some properties of the listener.
         
         */
        // @{

          /// @Implements
          virtual float getGain() const;

          /// Access to the object with the trait
          Kernel::Object* getObject() const;

        // @}
        /*!
         @name Updates.
         */
        // @{

          void onInit();

          void onClose();

          void onUpdate();

        // @}
        };
      }
    }
  }
}
