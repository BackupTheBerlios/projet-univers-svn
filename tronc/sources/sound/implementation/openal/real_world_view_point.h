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
#ifndef PU_SOUND_IMPLEMENTATION_OPENAL_REAL_WORLD_VIEW_POINT_H_
#define PU_SOUND_IMPLEMENTATION_OPENAL_REAL_WORLD_VIEW_POINT_H_

#include <kernel/object.h>
#include <kernel/view_point.h>

namespace ProjetUnivers {
  namespace Sound {
    namespace Implementation {
      namespace OpenAL {

        /// Standard sound viewpoint.
        class RealWorldViewPoint : public Kernel::ViewPoint 
        {
        public:
        
        /*!
          @name Construction 
        */
        // @{
          
          /// Constructor.
          /*!
            @param[in] _observer 
              object that sees (e.g., a character, a camera,...)
          */
          RealWorldViewPoint(Kernel::Object* observer) ;
          
        // @}
        };
      }
    }
  }
}


#endif /* PU_SOUND_IMPLEMENTATION_OPENAL_REAL_WORLD_VIEW_POINT_H_*/
