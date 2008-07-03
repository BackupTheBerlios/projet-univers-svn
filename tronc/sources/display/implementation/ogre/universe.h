/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#ifndef PU_DISPLAY_IMPLEMENTATION_OGRE_UNIVERSE_H_
#define PU_DISPLAY_IMPLEMENTATION_OGRE_UNIVERSE_H_

#include <Ogre.h>

#include <kernel/trait_view.h>
#include <model/universe.h>
#include <display/implementation/ogre/real_world_view_point.h>



namespace ProjetUnivers {
  namespace Display {
    namespace Implementation {
      namespace Ogre {

        /// Display the Universe.
        /*!
          Display a star field.
        */
        class Universe : public Kernel::TraitView<Model::Universe,
                                                  RealWorldViewPoint>
        {
        public:
        
        /*!
          @name Construct 
        */
        // @{
          
          /// Constructor.
          Universe(Model::Universe* i_universe,
                   RealWorldViewPoint* i_viewpoint) ;

        protected:
        
        // @}
        /*!
          @name Updates
                      
        */  
        // @{
        
          /// Create the star field.
          virtual void onInit() ;

          /// remove the star field.
          virtual void onClose() ;
        
        // @}
        private:
          
          /// We only need to store ambient ligth.
          ::Ogre::Light* light ;
          
        };
      }
    }
  }
}


#endif        

