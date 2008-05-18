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

#include <model/angular_speed.h>

namespace ProjetUnivers {
  namespace Model {

    const float pi = 3.1415926535 ;


    AngularSpeed::AngularSpeed()
    : m_value(0,0,0),
      m_unit(_TurnPerSecond)
      
    {}

    AngularSpeed AngularSpeed::TurnPerSecond(const float& i_wx,
                                             const float& i_wy,
                                             const float& i_wz)
    {
      AngularSpeed result ;
      result.m_value[0] = i_wx ;
      result.m_value[1] = i_wy ;
      result.m_value[2] = i_wz ;
      result.m_unit = _TurnPerSecond ;
      
      return result ;
      
    }

    AngularSpeed AngularSpeed::RadianPerSecond(const float& i_wx,
                                               const float& i_wy,
                                               const float& i_wz)
    {
      AngularSpeed result ;
      result.m_value[0] = i_wx ;
      result.m_value[1] = i_wy ;
      result.m_value[2] = i_wz ;
      result.m_unit = _RadianPerSecond ;
      
      return result ;
    }

    AngularSpeed::AngularSpeed(const AngularSpeed& i_speed)
    : m_value(i_speed.m_value), m_unit(i_speed.m_unit)
    {}

    Ogre::Vector3 AngularSpeed::TurnPerSecond() const
    {
      switch(m_unit)
      {
      case _TurnPerSecond:
        return m_value ;
      case _RadianPerSecond:
      { 
        Ogre::Vector3 result(m_value) ;
        result.normalise() ;
        return result * (m_value.length() / (2 * pi)) ;
      }
      default:
        return Ogre::Vector3() ;
      }
    }

    Ogre::Vector3 AngularSpeed::RadianPerSecond() const
    {
      switch(m_unit)
      {
      case _TurnPerSecond:
      { 
        Ogre::Vector3 result(m_value) ;
        result.normalise() ;
        return result * (m_value.length()* 2 * pi)  ;
      }
      case _RadianPerSecond:
        return m_value  ;

      default:
        return Ogre::Vector3() ;
      }
    }

    AngularSpeed AngularSpeed::read(Kernel::Reader* reader)
    {
      AngularSpeed result ;
      
      std::map<std::string,std::string>::const_iterator finder ; 

      finder = reader->getAttributes().find("x") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_value.x = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::AngularSpeed::read required attribute : x") ;
      }

      finder = reader->getAttributes().find("y") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_value.y = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::AngularSpeed::read required attribute : y") ;
      }

      finder = reader->getAttributes().find("z") ;
      if (finder != reader->getAttributes().end())
      {
        result.m_value.z = atof(finder->second.c_str()) ;
      }
      else
      {
        ErrorMessage("Model::AngularSpeed::read required attribute : z") ;
      }
      
      finder = reader->getAttributes().find("unit") ;
      if (finder != reader->getAttributes().end())
      {
        if (finder->second == "TurnPerSecond")
        {
          result.m_unit = _TurnPerSecond ;
        }
        else if (finder->second == "RadianPerSecond")
        {
          result.m_unit = _RadianPerSecond ;
        }
        else 
        {
          ErrorMessage("Model::AngularSpeed::read invalid unit : " + finder->second) ;
        }
      }
      else
      {
        ErrorMessage("Model::AngularSpeed::read required attribute : unit") ;
      }
      
      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}
      
      reader->processNode() ;
      
      return result ;            
    }   

  }
}
