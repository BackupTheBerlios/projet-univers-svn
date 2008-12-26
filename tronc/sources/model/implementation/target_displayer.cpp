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
#include <kernel/object.h>
#include <kernel/log.h>

#include <model/targeting_system.h>
#include <model/target_displayer.h>

namespace ProjetUnivers {
  namespace Model {
      

    TargetDisplayer::TargetDisplayer()
    {}

    void TargetDisplayer::connect(
                        Kernel::Object* target_displayer,
                        Kernel::Object* targeting_system)
    {
      if (target_displayer)
      {
        TargetDisplayer* displayer = target_displayer->getTrait<TargetDisplayer>() ;
        TargetingSystem* system = targeting_system->getTrait<TargetingSystem>() ;
        if (displayer && system)
        {
          displayer->m_targeting_system = targeting_system ;
          displayer->notify() ;
        }
        else
        {
          ErrorMessage("TargetDisplayer::connect") ;
        }
      }
    }

    Kernel::Object* TargetDisplayer::getTargetingSystem() const
    {
      return m_targeting_system ;
    }      
    
    Kernel::Model* TargetDisplayer::getComputerModel() const
    {
      if(! m_targeting_system)
        return NULL ;
      
      return m_targeting_system->getTrait<TargetingSystem>()->getComputerModel() ;
    }
  }
}
