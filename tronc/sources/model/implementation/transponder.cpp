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
#include <kernel/trait.h>
#include <kernel/object.h>
#include <model/team.h>
#include <model/transponder.h>

namespace ProjetUnivers
{
  namespace Model
  {
    
    Transponder::Transponder(Kernel::Object* team)
    : m_team(team)
    {
      if (team && team->getTrait<Team>())
      {  
        m_team_name = team->getTrait<Team>()->getName() ;
      }
    }

    Transponder::Transponder(const Transponder& transponder)
    : m_team_name(transponder.m_team_name)
    {}
    
    void Transponder::setCode(const Transponder* transponder)
    {
      m_team_name = transponder->m_team_name ;
    }
    
    std::string Transponder::getCode() const
    {
      return m_team_name + "-" + Kernel::toString(getObject()->getIdentifier()) ;
    }

    Kernel::Object* Transponder::getTeam() const
    {
      return m_team ;
    }

    bool Transponder::areFoe(Kernel::Object* object1,Kernel::Object* object2)
    {
      if (!object1 || !object2)
        return false ;
      
      Transponder* identification1 = object1->getParent<Transponder>() ;
      Transponder* identification2 = object2->getParent<Transponder>() ;
      
      if (!identification1 || !identification2)
        return false ;
      
      return identification1->m_team_name != identification2->m_team_name ;  
    }

    bool Transponder::areFriend(Kernel::Object* object1,Kernel::Object* object2)
    {
      if (!object1 || !object2)
        return false ;
      
      Transponder* identification1 = object1->getParent<Transponder>() ;
      Transponder* identification2 = object2->getParent<Transponder>() ;
      
      if (!identification1 || !identification2)
        return false ;
      
      return identification1->m_team_name == identification2->m_team_name ;  
    }
    
  }
}
