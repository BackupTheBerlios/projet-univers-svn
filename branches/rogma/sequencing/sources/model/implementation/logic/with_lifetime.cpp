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
#include <model/model.h>
#include <model/implementation/logic/with_lifetime.h>

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Implementation
    {
      namespace Logic
      {
          
        RegisterControler(WithLifetime, 
                          Model::WithLifetime, 
                          LogicSystem) ;
        
        void WithLifetime::simulate(const float& i_seconds)
        {
          InternalMessage("WithLifetime","Logic::WithLifetime::simulate entering") ;
          
          getTrait()->removeLifeTime(Duration::Second(i_seconds)) ;
          
          if (getTrait()->getLifeTimeInSeconds() < 0)
          {
            InternalMessage("WithLifetime","Logic::WithLifetime::simulate destroying object") ;
  
            // mark the object for destruction
            getObject()->destroyObject() ;
          }
  
          InternalMessage("WithLifetime","Logic::WithLifetime::simulate leaving") ;
          
        }
      }      
    }
  }
}
