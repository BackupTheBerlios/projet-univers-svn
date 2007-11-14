/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#ifndef PU_MODEL_IMPLEMENTATION_LOGIC_DETECTOR_H_
#define PU_MODEL_IMPLEMENTATION_LOGIC_DETECTOR_H_

#include <kernel/controler.h>
#include <model/detector.h>
#include <model/implementation/logic/logic_system.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {

        /// Perform detection.
        class Detector : public Kernel::Controler<Model::Detector,
                                                  LogicSystem>
        {
        public:
          
          /// Construct.
          Detector(Model::Detector* i_object,
                   LogicSystem*     i_system) ;
        
          /// Calculate new objects.
          void simulate(const float& i_seconds) ;
        
        protected:
    
          /// Called after the controler is created on a initialised controler set.
          virtual void onInit() ;
        
        };
      }
    }
  }
}


#endif
