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
#ifndef PU_MODEL_IMPLEMENTATION_LOGIC_SHOOTING_HELPER_VIEWPOINT_H_
#define PU_MODEL_IMPLEMENTATION_LOGIC_SHOOTING_HELPER_VIEWPOINT_H_

#include <kernel/view_point.h>
#include <kernel/object.h>
#include <kernel/object_reference.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {
        
        /// Views on computer data for ShootingHelper.
        class ShootingHelperViewPoint : public Kernel::ViewPoint
        {
        public:
        
          /// Contructs.
          ShootingHelperViewPoint(Kernel::Object* shooting_helper) ;
          
          /// When system may change computer or other things.
          void update() ;
          
          /// Access to the Laser.
          Kernel::Object* getLaser() const ;
          
        private:
          
          Kernel::ObjectReference m_shooting_helper ;
        };
      }
    }
  }
}


#endif /* PU_MODEL_IMPLEMENTATION_LOGIC_SHOOTING_HELPER_VIEWPOINT_H_ */
