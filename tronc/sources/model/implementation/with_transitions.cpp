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
#include <kernel/object.h>
#include <model/displayed.h>
#include <model/with_transitions.h>

namespace ProjetUnivers {
  namespace Model {
    
    WithTransitions::WithTransitions()
    {}

    void WithTransitions::addTransition(const std::string& name,Kernel::Object* object)
    {
      m_transitions[name] = object ; 
    }
   
    void WithTransitions::setNext(Kernel::Object* object)
    {
      m_transitions[""] = object ;
    }
    
    void WithTransitions::trigger(const std::string& name)
    {
      std::map<std::string,Kernel::ObjectReference>::const_iterator 
        finder = m_transitions.find(name) ;
      
      if (finder != m_transitions.end())
      {
        Displayed* displayed = getObject()->getTrait<Displayed>() ;
        if (displayed)
        {
          getObject()->destroyTrait(displayed) ;
        }
        
        if (finder->second)
        {
          finder->second->addTrait(new Displayed()) ;
        }
      }
    }

    bool WithTransitions::call(const Kernel::TypeIdentifier& trait_type,
                               const std::string&            command)
    {
      std::map<std::string,Kernel::ObjectReference>::const_iterator 
        finder = m_transitions.find(command) ;
      
      if (finder != m_transitions.end())
      {
        trigger(command) ;
        return true ;
      }
      return false ;
    }
    
  }
}

