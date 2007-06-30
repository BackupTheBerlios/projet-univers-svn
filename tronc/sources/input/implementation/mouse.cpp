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
#include <kernel/log.h>
#include <kernel/string.h>

#include <input/implementation/mouse.h>


namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      namespace
      {
        /// local data
        
        
      }
      const int max = 100 ;
      const int maximum_X = max ;
      const int maximum_Y = max ;

      bool Mouse::mouseMoved(const OIS::MouseEvent &arg)
      {
        /// test code...

        if (m_controled_object)
        {
        
          X += arg.state.X.rel ;
          if (X > maximum_X)
          {
            X = maximum_X ;
          }
          if (X < -maximum_X)
          {
            X = -maximum_X ;
          }
          
          Y += arg.state.Y.rel ;
          if (Y > maximum_Y)
          {
            Y = maximum_Y ;
          }
          if (Y < -maximum_Y)
          {
            Y = -maximum_Y ;
          }
          std::cout << "X=" << X << ",Y=" << Y
                    << ",deltaX=" << arg.state.X.rel
                    << ",deltaY=" << arg.state.Y.rel
                    << std::endl ;          
          /// lookat method...
          Ogre::Vector3 view(-X,Y,max/2.0) ;
          view.normalise() ;
          Ogre::Vector3 rigth = view.crossProduct(Ogre::Vector3::NEGATIVE_UNIT_Y) ;
          rigth.normalise() ;
          Ogre::Vector3 up = view.crossProduct(rigth) ;
          up.normalise() ;
          
          m_controled_object->setOrientation(
             Model::Orientation(Ogre::Quaternion(rigth,up,view))) ;
          
          /// local zAxis of orientation is "good", it is the orientation see from behind
          std::cout 
            << m_controled_object->getOrientation().getQuaternion().zAxis() 
            << std::endl ;
          
        }
        
        return true ;
        
      }
      
      bool Mouse::mousePressed(const OIS::MouseEvent &arg, 
                               OIS::MouseButtonID id)
      {
        return true ;
      }
      
      bool Mouse::mouseReleased(const OIS::MouseEvent &arg,
                                OIS::MouseButtonID id)
      {
        return true ;
      }

      Mouse::Mouse(const float& i_sensibility)
      : m_time_delay(0.0),
        m_controled_object(NULL),
        m_sensibility(i_sensibility),
        X(0),
        Y(0)
      {}
      
      Mouse::~Mouse()
      {}
      
      void Mouse::setTimeDelay(const float& i_seconds)
      {
        m_time_delay = i_seconds ;
      }
      
      void Mouse::setControledObject(Model::Oriented* i_object)
      {
        m_controled_object = i_object ;
      }
    }
  }
}

