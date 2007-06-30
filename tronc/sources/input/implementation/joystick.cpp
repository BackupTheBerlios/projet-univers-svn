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

#include <input/implementation/joystick.h>


namespace ProjetUnivers {
  namespace Input {
    namespace Implementation {

      namespace
      {
        /// local data
        const int max = 100 ;
        const int maximum_X = max ;
        const int maximum_Y = max ;
        const float pi = 3.1415926535 ;
      }

      bool Joystick::buttonPressed(
        const OIS::JoyStickEvent&,
        int)
      {
        return true ;
      }
      
      bool Joystick::buttonReleased(const OIS::JoyStickEvent&,int)
      {
        return true ;
      }
      
      /*!
      @todo 
        configuration depends of joystick
        I do not know how we can determine mapping between axix numbers
        and X/Y/Z ?
        
        
      */ 
      bool Joystick::axisMoved(const OIS::JoyStickEvent& event,int i_axis)
      {
        if (m_controled_object)
        {
          X = 100 * event.state.mAxes[0].abs / OIS::JoyStick::MAX_AXIS ;
          Y = - 100 * event.state.mAxes[1].abs / OIS::JoyStick::MAX_AXIS ;
          Z = 100 * event.state.mAxes[5].abs / OIS::JoyStick::MAX_AXIS ; 
          
          std::cout << "X=" << X << ",Y=" << Y << ",Z=" << Z << std::endl ;

//          std::cout << "0=" << event.state.mAxes[0].abs
//                    << ",1=" << event.state.mAxes[1].abs
//                    << ",2=" << event.state.mAxes[2].abs
//                    << ",3=" << event.state.mAxes[3].abs
//                    << ",4=" << event.state.mAxes[4].abs
//                    << ",5=" << event.state.mAxes[5].abs
//                    << ",6=" << event.state.mAxes[6].abs
//                    << ",7=" << event.state.mAxes[7].abs
//                    << ",8=" << event.state.mAxes[8].abs
//                    << ",9=" << event.state.mAxes[9].abs
//                    << std::endl ;          
//          /// it seem that for my stick POV is handled as buttons
//          std::cout << "POV=" << event.state.mPOV[0].direction << std::endl ;

          /// lookat method...
          Ogre::Vector3 view(-X,Y,max/2.0) ;
          view.normalise() ;
          
          Ogre::Vector3 y_rotation = 
            Ogre::Quaternion(Ogre::Degree(-0.45*Z),Ogre::Vector3::NEGATIVE_UNIT_Z)
            * Ogre::Vector3::UNIT_Y ;
          
          Ogre::Vector3 rigth = -view.crossProduct(y_rotation) ;
          rigth.normalise() ;
          Ogre::Vector3 up = view.crossProduct(rigth) ;
          up.normalise() ;


          std::cout << "X rigth = " << rigth << std::endl ;
          std::cout << "Y up = " << up << std::endl ;
          std::cout << "Z view = " << view << std::endl ;
          
          Ogre::Quaternion orientation(rigth,up,view) ;

          std::cout << "pitch=" << orientation.getPitch().valueRadians()
                    << ",Yaw=" << orientation.getYaw().valueRadians()
                    << ",Roll=" << orientation.getRoll().valueRadians() 
                    << std::endl ;
          
          m_controled_object->setOrientation(
             Model::Orientation(orientation)) ;

//          std::cout << "view = " << view << std::endl ;

//          
//          /// local zAxis of orientation is "good", it is the orientation see from behind
//          std::cout 
//            << m_controled_object->getOrientation().getQuaternion().zAxis() 
//            << std::endl ;
        }
        return true ;
      }
      
      bool Joystick::sliderMoved(const OIS::JoyStickEvent&,int)
      {
        return true ;
      }
      
      bool Joystick::povMoved(const OIS::JoyStickEvent&,int)
      {
        return true ;
      }
      

      Joystick::Joystick(const float& i_sensibility)
      : m_time_delay(0.0),
        m_controled_object(NULL),
        m_sensibility(i_sensibility),
        X(0),
        Y(0),
        Z(0)
      {}
      
      Joystick::~Joystick()
      {}
      
      void Joystick::setTimeDelay(const float& i_seconds)
      {
        m_time_delay = i_seconds ;
      }
      
      void Joystick::setControledObject(Model::Oriented* i_object)
      {
        m_controled_object = i_object ;
      }
    }
  }
}

