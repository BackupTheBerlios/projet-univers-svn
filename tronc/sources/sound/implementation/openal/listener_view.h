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
#ifndef PU_SOUND_IMPLEMENTATION_OPENAL_LISTENER_VIEW_H_
#define PU_SOUND_IMPLEMENTATION_OPENAL_LISTENER_VIEW_H_

#include <kernel/trait_view.h>

#include <sound/implementation/openal/sound_listener.h>
#include <sound/implementation/openal/real_world_view_point.h>
#include <sound/implementation/openal/listener.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        
        
        /// Sound Observer view.
        /*!
        */
        class ListenerView : public Kernel::TraitView<Listener,
                                                  RealWorldViewPoint>, 
                         public SoundListener
        {
        public:
        
        /*!
          @name Construction 
        */
        // @{


          /// Constructor.
          ListenerView(Listener*,RealWorldViewPoint*) ;


        // @}
          
          /// @Implements
          virtual float getGain() const ;
                        
          /// @Implements
          virtual Model::Position getPosition() const ;
                            
          /// @Implements
          virtual Model::Orientation getOrientation() const ;
                            
          /// @Implements
          virtual Model::Speed getSpeed() const ; 
          
          
        protected:

        /*!
          @name Updates.
        */
        // @{
        
          /// TODO
          void onInit() ;
          
          /// TODO
          void onClose() ;
          
          /// TODO
          void onUpdate() ;

        // @}
        };
      }
    }
  }
}


#endif /*PU_SOUND_IMPLEMENTATION_OPENAL_LISTENER_VIEW_H_*/
