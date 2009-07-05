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
#include <model/computer.h>
#include <model/shooting_helper.h>
#include <model/implementation/logic/shooting_helper_viewpoint.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {

        ShootingHelperViewPoint::ShootingHelperViewPoint(Kernel::Object* shooting_helper)
        : Kernel::ViewPoint(NULL),
          m_shooting_helper(shooting_helper)
        {
          update() ;
        }
        
        void ShootingHelperViewPoint::update()
        {
          InternalMessage("Model","Entering ShootingHelperViewPoint::update") ;
          if (!m_shooting_helper)
            return ;
          
          InternalMessage("Model","ShootingHelperViewPoint::update#1") ;
          ShootingHelper* sh = m_shooting_helper->getTrait<ShootingHelper>() ;
          if (!sh)
            return ;
          
          InternalMessage("Model","ShootingHelperViewPoint::update#2") ;
          Kernel::Object* computer = sh->getComputer() ;
          
          if(!computer)
            return ;

          InternalMessage("Model","ShootingHelperViewPoint::update#3") ;
          
          Computer* trait = computer->getTrait<Computer>() ;
          if (trait)
          {
            setModel(trait->getMemoryModel()) ;
          }
          InternalMessage("Model","Leaving ShootingHelperViewPoint::update#2") ;
        
        }

        Kernel::Object* ShootingHelperViewPoint::getLaser() const 
        {
          if (!m_shooting_helper)
            return NULL ;
          ShootingHelper* sh = m_shooting_helper->getTrait<ShootingHelper>() ;
          if (!sh)
            return NULL ;
          
          return sh->getLaser() ;
          
        }
        
      }
    }
  }
}
