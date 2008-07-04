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
#include <model/throttle.h>

namespace ProjetUnivers {
  namespace Model {

    RegisterTrait(Throttle) ;
      
    namespace
    {
      /// local data
      const int max = 100 ;
    }

    Throttle::Throttle()
    : Oriented(),
      m_y(-100)
    {}

    Kernel::Trait* Throttle::read(Kernel::Reader* reader)
    {
      Throttle* result = new Throttle() ;
      
      std::map<std::string,std::string>::const_iterator finder ; 

      finder = reader->getAttributes().find("y") ;
      if (finder != reader->getAttributes().end())
      {
        result->m_y = atoi(finder->second.c_str()) ;
      }
      
      // move out of node
      while (!reader->isEndNode() && reader->processNode())
      {}
      
      reader->processNode() ;

      return result ;
    }
    
    void Throttle::modify(const int& i_delta)
    {
      m_y += i_delta ;
      set(m_y) ;
    }

    void Throttle::set(const int& throttle)
    {
      m_y = throttle ;
      if (m_y > max)
      {
        m_y = max ;
      }
      if (m_y < -max)
      {
        m_y = -max ;
      }
      Ogre::Quaternion orientation(Ogre::Degree(0.9*(m_y/2+50)),Ogre::Vector3::UNIT_X) ;
      m_orientation = Model::Orientation(orientation) ;
      notify() ;
    }

    RegisterAxis("Throttle",Throttle,set) ;
    /// @todo should be private
    RegisterAxis("Change Throttle",Throttle,modify) ;
  }
}
