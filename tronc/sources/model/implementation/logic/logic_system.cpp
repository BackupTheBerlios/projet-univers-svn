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
#include <boost/function.hpp>

#include <kernel/log.h>
#include <kernel/base_controler.h>

#include <model/model.h>
#include <model/implementation/logic/logic_system.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {

        RegisterControlerSet(LogicSystem) ;
        
        LogicSystem::LogicSystem(Kernel::Model* model)
        : Kernel::ControlerSet(model)
        {}
  
        void LogicSystem::simulate(const float& i_seconds)
        {
          InternalMessage("Model","Model::LogicSystem::simulate entering") ;
          boost::function2<void,
                           Kernel::BaseControler*,
                           float> f 
                              = &Kernel::BaseControler::simulate ;
          
          applyBottomUp(std::bind2nd(f,i_seconds)) ;
          
          for(std::set<Kernel::ObjectReference>::iterator object = m_objects_to_destroy.begin() ;
              object != m_objects_to_destroy.end() ;
              ++object)
          {
            if (*object)
            {
              InternalMessage("Model","Model::LogicSystem::simulate destroying object") ;
              (*object)->getModel()->destroyObject(*object) ;
            }
          }
          
          m_objects_to_destroy.clear() ;
          InternalMessage("Model","Model::LogicSystem::simulate leaving") ;
        }
        
        void LogicSystem::addObjectToDestroy(Kernel::Object* object)
        {
          m_objects_to_destroy.insert(object) ;
        }
      }
    }
  }
}

