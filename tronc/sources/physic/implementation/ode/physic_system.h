/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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
#ifndef PU_PHYSIC_IMPLEMENTATION_REAL_WORLD_VIEW_POINT_H_
#define PU_PHYSIC_IMPLEMENTATION_REAL_WORLD_VIEW_POINT_H_

#include <kernel/controler_set.h>


namespace ProjetUnivers {
  namespace Physic {
    namespace Implementation {
      namespace Ode {

        /// Physic implementation 
        /*!
        */
        class PhysicSystem : public Kernel::ControlerSet
        {
        public:
        
          /// Contructs.
          PhysicSystem(Kernel::Object* i_observer) ;
          
          /// Create a ODE world.
          virtual void onInit() ;

          /// Destroy the ODE world.
          virtual void onClose() ;
          
          /// Simulate the systeme during @c i_seconds seconds.
          virtual void simulate(const float& i_seconds) ;

        protected:
          
          /// True iff object is taken into account.
          virtual bool isVisible(Kernel::Object* i_object) const ;  
          
        };
      }
    }
  }
}

#endif /*PU_PHYSIC_IMPLEMENTATION_REAL_WORLD_VIEW_POINT_H_*/
