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
#include <kernel/log.h>

#include <model/implementation/logic/logic_system.h>
#include <model/implementation/logic/logic.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {

        /// active controler set.
        std::auto_ptr<LogicSystem> m_system ;
    
        bool initialised = false ;

        void init()
        {
          if (! initialised)
          {
            initialised = true ;
            
            if (m_system.get())
            {
              m_system->init() ;
            }      
          }
        }
        
        void close()
        {
          if (m_system.get())
          {
            m_system->close() ;
          }
          initialised = false ;
          m_system.reset(NULL) ;
        }
    
        Kernel::ControlerSet* build(Kernel::Model* model)
        {
          close() ;
          m_system.reset(new LogicSystem(model)) ;
          init() ;
          return m_system.get() ;
        } 
        
        void update(const Model::Duration& i_duration)
        {
          float seconds = i_duration.Second() ;

          InternalMessage("Model::Logic::simulate entering") ;
  
          if (initialised && m_system.get() && seconds != 0)
          {
            m_system->simulate(seconds) ;
          }

          InternalMessage("Model::Logic::simulate leaving") ;
          
        }

      }
    }
  }
}

