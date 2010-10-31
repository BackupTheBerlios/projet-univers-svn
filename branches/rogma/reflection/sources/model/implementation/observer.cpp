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
#include <model/observer.h>

namespace ProjetUnivers
{
  namespace Model
  {

    RegisterTrait(Observer) ;

    Observer::Observer()
    : Kernel::Trait(),
      m_field_of_view(50)
    {}

    Kernel::Trait* Observer::read(Kernel::Reader* reader)
    {
      std::auto_ptr<Observer> result(new Observer()) ;

      while (!reader->isEndNode() && reader->processNode())
      {
        if (reader->isTraitNode() && reader->getTraitName() == "Angle")
        {
          float value = 0 ;
          std::map<std::string,std::string>::const_iterator finder ;
          finder = reader->getAttributes().find("value") ;
          if (finder != reader->getAttributes().end())
          {
            value = atof(finder->second.c_str()) ;
          }
          else
          {
            ErrorMessage("Model::Angle::read required attribute : value") ;
          }
          finder = reader->getAttributes().find("unit") ;
          if (finder != reader->getAttributes().end() && finder->second == "Degree")
          {
            result->m_field_of_view = ::Ogre::Degree(value) ;
          }
          else
          {
            ErrorMessage("Model::Angle::read required attribute : unit") ;
          }
        }
      }
      
      reader->processNode() ;
      return result.release() ;
    }

    Ogre::Degree Observer::getFieldOfView() const
    {
      return m_field_of_view ;
    }

    void Observer::setFieldOfView(const ::Ogre::Degree& field_of_view)
    {
      m_field_of_view = field_of_view ;
    }

  }
}

