/***************************************************************************
 *   Copyright (C) 2007 by Equipe Projet Univers                           *
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
#include <model/throttle.h>

namespace ProjetUnivers {
  namespace Model {
      
    namespace
    {
      /// local data
      const int max = 100 ;
    }

    Throttle::Throttle()
    : Oriented(),
      m_y(0)
    {}
    
    void Throttle::modify(const int& i_delta)
    {
      m_y += i_delta ;
      if (m_y > max)
      {
        m_y = max ;
      }
      if (m_y < -max)
      {
        m_y = -max ;
      }
//      std::cout << "throttle::m_y =" << m_y << std::endl ;
      
      Ogre::Quaternion orientation(Ogre::Degree(0.9*m_y),Ogre::Vector3::UNIT_X) ;
      m_orientation = Model::Orientation(orientation) ;
    }

    void Throttle::set(const int& i_y)
    {
      m_y = i_y ;
      if (m_y > max)
      {
        m_y = max ;
      }
      if (m_y < -max)
      {
        m_y = -max ;
      }
//      std::cout << "throttle::m_y =" << m_y << std::endl ;
      
      Ogre::Quaternion orientation(Ogre::Degree(0.9*m_y),Ogre::Vector3::UNIT_X) ;
      m_orientation = Model::Orientation(orientation) ;
    }

    RegisterAxis("set_throttle",Throttle,set) ;

  }
}
