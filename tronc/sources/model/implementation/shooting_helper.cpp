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
#include <model/data_connection.h>
#include <model/shooting_helper.h>

namespace ProjetUnivers 
{
  namespace Model 
  {

    RegisterTrait(ShootingHelper) ;
    
    ShootingHelper::ShootingHelper()
    {}

    void ShootingHelper::connect(
        Kernel::Object* shooting_helper,
        Kernel::Object* computer,
        Kernel::Object* laser)
    {
      ShootingHelper* trait = shooting_helper->getTrait<ShootingHelper>() ;
      
      if (trait)
      {
        trait->m_laser = laser ;

        Kernel::Link<DataConnection>(computer,shooting_helper) ;

        trait->notify() ;

      }
    }

    Kernel::Trait* ShootingHelper::read(Kernel::Reader* reader)
    {
      ShootingHelper* result = new ShootingHelper() ;
      
      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && 
            reader->getTraitName() == "ObjectReference")
        {
          std::map<std::string,std::string>::const_iterator finder ; 

          finder = reader->getAttributes().find("name") ;
          if (finder != reader->getAttributes().end())
          {
            if (finder->second == "laser")
            {
              result->m_laser = Kernel::ObjectReference::read(reader) ;
            }
          }
        }
        else 
        {
          Trait::read(reader) ;
        }
      }
      
      reader->processNode() ;
      
      return result ;
    }
    
    Kernel::Object* ShootingHelper::getComputer() const
    {
      std::set<Kernel::ObjectReference> computers(Kernel::Relation::getLinked<Kernel::Inverse<DataConnection> >(getObject())) ;

      if (computers.size() != 1)
        return NULL ;

      return *(computers.begin()) ;
    }
    
    Kernel::Object* ShootingHelper::getLaser() const
    {
      return m_laser ;
    }
    
  }
}
