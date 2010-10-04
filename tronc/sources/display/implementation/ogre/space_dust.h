/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008 Mathieu ROGER                                      *
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

#include <Ogre.h>

#include <kernel/trait_view.h>
#include <display/implementation/space_dust.h>
#include <display/implementation/ogre/real_world_view_point.h>

namespace ProjetUnivers
{
  namespace Display
  {
    namespace Implementation
    {
      namespace Ogre
      {
        
        
        /// Space dust to show speed.
        class SpaceDust : public Kernel::TraitView<Implementation::SpaceDust,
                                                   RealWorldViewPoint>
        {
        protected:
        /*!
          @name Updates.
        */
        // @{
        
          /// Build a paticle emiter.
          void onInit() ;
          
          /// Destroy the particule emiter.
          void onClose() ;
          
          /// Update  
          void onUpdate() ;

        // @}
        private:

          /// Set emission rate according to speed
          void setEmissionRate() ;
          
          /// Space dust effect
          ::Ogre::SceneNode*      m_space_dust_node ;
          ::Ogre::ParticleSystem* m_space_dusts ;

          float m_maximum_emission_rate ;
        };
      }
    }
  }
}
