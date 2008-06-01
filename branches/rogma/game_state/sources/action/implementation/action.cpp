/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
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

#include <OgreVector3.h>

#include <list>
#include <kernel/error.h>
#include <kernel/log.h>
#include <kernel/object.h>

#include <model/model.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/solid.h>
#include <model/stellar_system.h>
#include <model/mobile.h>

#include <action/action.h>

using namespace ProjetUnivers::Model ;
using namespace ::Ogre ;
using namespace ProjetUnivers::Kernel ;

namespace ProjetUnivers {
  namespace Action {

    bool is_finished ;

    struct Action
    {
      std::string name ;
      
    };

    std::list<Action> actions ;
    
    
    void perfom(const Action& _action)
    {
      if (_action.name == "Sortie")
      {
        is_finished = true ;
      }
    }
    
    
    void init()
    {
      actions.clear() ;
      is_finished = false ;
    }

    void close()
    {
      actions.clear() ;
    }

    void update()
    {
      for(std::list<Action>::iterator action = actions.begin() ;
          action != actions.end() ;
          ++action)
      {
        perfom(*action) ;
      }
      
      actions.clear() ;
    }

    void add(const std::string& _name)
    {
      Action temp ;
      temp.name = _name ;
      actions.push_back(temp) ;
    }

    bool finished()
    {
      return is_finished ;
    }


  }
}

