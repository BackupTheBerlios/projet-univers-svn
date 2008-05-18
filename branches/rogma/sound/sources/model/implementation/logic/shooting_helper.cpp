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
#include <kernel/log.h>
#include <model/implementation/logic/shooting_helper.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {

        RegisterControler(Logic::ShootingHelper,
                          Model::ShootingHelper,
                          Logic::LogicSystem) ;
        
        ShootingHelper::ShootingHelper(
            Model::ShootingHelper* object,
            LogicSystem* system)
        : Kernel::Controler<Model::ShootingHelper,LogicSystem>(object,system)
        {}
            
        void ShootingHelper::onInit()
        {
          InternalMessage("Model","Entering ShootingHelper::onInit") ;
          m_implementation.reset(new ShootingHelperViewPoint(getObject())) ;
          m_implementation->init() ;
          InternalMessage("Model","Leaving ShootingHelper::onInit") ;
        }
        
        void ShootingHelper::onClose() 
        {
          InternalMessage("Model","ShootingHelper::onClose") ;
          if (m_implementation.get())
          {
            m_implementation->close() ;
            m_implementation.reset(NULL) ;
          }
        }
          
        void ShootingHelper::onUpdate()
        {
          InternalMessage("Model","Entering ShootingHelper::onUpdate") ;
          m_implementation->update() ;
        }
      }
    }
  }
}
