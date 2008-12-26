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
#include <OgreVector3.h>
#include <OgreMath.h>
#include <kernel/log.h>
#include <model/orientation.h>

namespace ProjetUnivers {
  namespace Model {

    Orientation::Orientation()
    : m_orientation()
    {}

    Orientation::Orientation(const Orientation& _orientation)
    : m_orientation(_orientation.m_orientation)
    {}

    Orientation::Orientation(const Ogre::Quaternion& _orientation)
    : m_orientation(_orientation)
    {}

    Orientation Orientation::random()
    {
      Ogre::Quaternion quaternion(Ogre::Math::UnitRandom(),
                                  Ogre::Math::UnitRandom(),
                                  Ogre::Math::UnitRandom(),
                                  Ogre::Math::UnitRandom()) ;
      
      quaternion.normalise() ;
      
      return Orientation(quaternion) ;
    }
    
    Orientation Orientation::read(Kernel::Reader* reader)
    {
      std::map<std::string,std::string>::const_iterator finder ; 
      Ogre::Degree degree ; 

      finder = reader->getAttributes().find("angle_degree") ;
      if (finder != reader->getAttributes().end())
      {
        degree = atof(finder->second.c_str()) ;
      }
      
      Ogre::Vector3 axis ;

      finder = reader->getAttributes().find("axis_x") ;
      if (finder != reader->getAttributes().end())
      {
        axis.x = atof(finder->second.c_str()) ;
      }
      
      finder = reader->getAttributes().find("axis_y") ;
      if (finder != reader->getAttributes().end())
      {
        axis.y = atof(finder->second.c_str()) ;
      }

      finder = reader->getAttributes().find("axis_z") ;
      if (finder != reader->getAttributes().end())
      {
        axis.z = atof(finder->second.c_str()) ;
      }
      
      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}
      
      reader->processNode() ;
      
      return Orientation(Ogre::Quaternion(degree,axis)) ;            
    }   

    const Ogre::Quaternion& Orientation::getQuaternion() const 
    {
      return m_orientation ;
    }
    
    Orientation Orientation::operator*(const Orientation& i_orientation) const
    {
      return m_orientation * i_orientation.m_orientation ; 
    }

    Orientation Orientation::inverse() const
    {
      return m_orientation.Inverse() ;
    }

  }
}
