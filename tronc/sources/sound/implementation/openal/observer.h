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
#ifndef PU_SOUND_IMPLEMENTATION_OPENAL_OBSERVATEUR_H_
#define PU_SOUND_IMPLEMENTATION_OPENAL_OBSERVATEUR_H_

#include <kernel/trait_view.h>

#include <model/observer.h>

#include <sound/implementation/openal/sound_listener.h>
#include <sound/implementation/openal/real_world_view_point.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {
        
        
        /// Sound Observer view.
        /*!
        */
        class Observer : public Kernel::TraitView<Model::Observer,
                                                  RealWorldViewPoint>, 
                         public SoundListener
        {
        public:
        
        /*!
          @name Construction 
        */
        // @{


          /// Constructor.
          Observer(Model::Observer*,RealWorldViewPoint*) ;


        // @}
          
          /// @Implements
          /// TODO voir sur quelles facettes on pourra gérer le cas
          /// où la personne n'étend plus ou de manière déformée
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


#endif /*PU_SOUND_IMPLEMENTATION_OPENAL_OBSERVATEUR_H_*/
