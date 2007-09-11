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
#ifndef PU_MODEL_IMPLEMENTATION_LOGIC_LOGIC_H_
#define PU_MODEL_IMPLEMENTATION_LOGIC_LOGIC_H_

#include <kernel/model.h>
#include <model/duration.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      
      /// Gameplay control system.
      /*!
        This sub-module of model is responsible for gameplay mecanism.
      */ 
      namespace Logic {

        /// Initialised module.
        void init() ; 
        
        /// Terminate module.
        void close() ;
    
        /// Creates the standard representation for the world 
        Kernel::ControlerSet* build(Kernel::Model*) ; 
        
        /// simulate model during a given time.
        void update(const Model::Duration& i_duration) ;

      }
    }
  }
}


#endif
