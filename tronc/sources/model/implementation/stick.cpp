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
#include <model/stick.h>

namespace ProjetUnivers {
  namespace Model {
      
    namespace
    {
      /// local data
      const int max = 100 ;
    }

    Stick::Stick()
    : Oriented(),
      m_x(0),
      m_y(0),
      m_z(0),
      m_updated(true)
    {}
    
    const Orientation& Stick::getOrientation() const
    {
      updateOrientation() ;
      return Oriented::getOrientation() ;
    }
    
    void Stick::modifyX(const int& i_delta_x)
    {
      m_x += i_delta_x ;
      if (m_x > max)
      {
        m_x = max ;
      }
      if (m_x < -max)
      {
        m_x = -max ;
      }
      m_updated = false ;
    }
    
    void Stick::modifyY(const int& i_delta_y)
    {
      m_y += i_delta_y ;
      if (m_y > max)
      {
        m_y = max ;
      }
      if (m_y < -max)
      {
        m_y = -max ;
      }
      m_updated = false ;
    }

    void Stick::modifyZ(const int& i_delta_z)
    {
      m_z += i_delta_z ;
      if (m_z > max)
      {
        m_z = max ;
      }
      if (m_z < -max)
      {
        m_z = -max ;
      }
      m_updated = false ;
    }

    void Stick::setX(const int& i_x)
    {
      m_x = i_x ;
      if (m_x > max)
      {
        m_x = max ;
      }
      if (m_x < -max)
      {
        m_x = -max ;
      }
      m_updated = false ;
      updateOrientation() ;
      notify() ;
    }
    
    void Stick::setY(const int& i_y)
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
      m_updated = false ;
      updateOrientation() ;
      notify() ;
    }

    void Stick::setZ(const int& i_z)
    {
      m_z = i_z ;
      if (m_z > max)
      {
        m_z = max ;
      }
      if (m_z < -max)
      {
        m_z = -max ;
      }
      m_updated = false ;
      updateOrientation() ;
      notify() ;
    }

    RegisterAxis("set_axis_X",Stick,setX) ;
    RegisterAxis("set_axis_Y",Stick,setY) ;
    RegisterAxis("set_axis_Z",Stick,setZ) ;
  
    void Stick::updateOrientation() const
    {
      if (!m_updated)
      {
        
//        std::cout << "X=" << m_x << ",Y=" << m_y << ",Z=" << m_z << std::endl ;
        /// technique with plannar mapping
        /* 
          map m_x,m_y on a square
        */ 
        Ogre::Vector3 view(-m_x,m_y,max) ;

        view.normalise() ;
        
        Ogre::Vector3 y_rotation = 
          Ogre::Quaternion(Ogre::Degree(-0.45*m_z),Ogre::Vector3::NEGATIVE_UNIT_Z)
          * Ogre::Vector3::UNIT_Y ;
        
        Ogre::Vector3 rigth = -view.crossProduct(y_rotation) ;
        rigth.normalise() ;
        Ogre::Vector3 up = view.crossProduct(rigth) ;
        up.normalise() ;
        
        Ogre::Quaternion orientation(rigth,up,view) ;
        m_orientation = Model::Orientation(orientation) ;
      }
    }

  }
}
