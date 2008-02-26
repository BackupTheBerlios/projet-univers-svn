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
#ifndef PU_MODEL_IMPLEMENTATION_LOGIC_TARGET_H_
#define PU_MODEL_IMPLEMENTATION_LOGIC_TARGET_H_

#include <Ogre.h>
#include <kernel/trait_view.h>
#include <model/implementation/target.h>
#include <model/implementation/logic/shooting_helper_viewpoint.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {

        /// Generates the associated ideal target with the selectioned target. 
        class Target : public Kernel::TraitView<Implementation::Target,
                                                ShootingHelperViewPoint>
        {
        public:
        
        /*! 
          @name Construct
        */ 
        // @{

          /// Constructor.
          Target(Implementation::Target* object,
              ShootingHelperViewPoint* viewpoint) ;
        // @}
      protected:
        /*!
          @name Updates
        */
        // @{
        
          /// Create the IdealTarget if exist.
          void onInit() ;
          
          /// Destroy the IdealTarget.
          void onClose() ;
        
          /// Update/create the IdealTarget.
          void onUpdate() ;

        // @}
        private:
          
          /// The associated ideal target.
          /*!
            It is child of the target object in the computer.
          */
          Kernel::ObjectReference m_ideal_target ;
        };
      }
    }
  }
}

#endif /*PU_MODEL_IMPLEMENTATION_LOGIC_TARGET_H_*/
