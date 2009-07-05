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

#include <kernel/trait_view.h>

#include <sound/implementation/shot.h>
#include <sound/implementation/openal/sound_emitter.h>
#include <sound/implementation/openal/real_world_view_point.h>

namespace ProjetUnivers 
{
  namespace Sound 
  {
    namespace Implementation 
    {
      namespace OpenAL 
      {
    
        /// Sound produced by an engine
        class Shot : public Kernel::TraitView<Implementation::Shot,
                                              RealWorldViewPoint>,
                       public SoundEmitter
        {
        protected:
        
        /*!
          @name Access methods
          
          Redefinition of some properties of the sound to emit.
          
        */
        // @{
                    
          /// Get the sound's filename
          virtual std::string getSoundFileName() const ;
          
          /// Indicate if the sound is looping
          virtual bool isEvent() const ;
          
          ///Acces to the object with the trait
          virtual Kernel::Object* getObject() const ;
          
        // @}
        
        /*!
          @name Updates.
        */
        // @{
                  
          void onInit() ;
                      
          void onClose() ;
                      
          void onUpdate() ;
          
          void onChangeParent(Kernel::Object* old_parent) ;

        // @}      
        };
      }
    }
  }
}
