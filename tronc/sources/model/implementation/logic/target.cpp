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
#include <model/position.h>
#include <model/positionned.h>
#include <model/laser.h>
#include <model/mobile.h>
#include <model/ideal_target.h>
#include <model/implementation/logic/target.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Implementation {
      namespace Logic {

        RegisterView(Target, 
                     Implementation::Target, 
                     ShootingHelperViewPoint) ;
        
        Target::Target(
            Implementation::Target* object,
            ShootingHelperViewPoint* viewpoint)
        : Kernel::TraitView<Implementation::Target,ShootingHelperViewPoint>(object,viewpoint)
        {}
        
        void Target::onInit()
        {
          onUpdate() ;
        }
        
        void Target::onClose()
        {
          if (m_ideal_target)
          {
            getObject()->getModel()->destroyObject(m_ideal_target) ;
          }
        }
        
        
        /*!
          We have to solve the following equation : 
          
          position    is the position of the target
          speed       is the speed vector of the target
          laser_speed is the laser beam speed
          
          distance(position+t*speed) = t*laser_speed
          formal solver gives :
          
          t = (sqrt((-4*position.y^2-4*position.x^2)*speed.z^2+(8*position.y*position.z*speed.y+8*position.x*position.z*speed.x-4*position.z*laser_speed)*speed.z+(-4*position.z^2-4*position.x^2)*speed.y^2+(8*position.x*position.y*speed.x-4*position.y*laser_speed)*speed.y+(-4*position.z^2-4*position.y^2)*speed.x^2-4*position.x*laser_speed*speed.x+laser_speed^2)-2*position.z*speed.z-2*position.y*speed.y-2*position.x*speed.x+laser_speed)
              /(2*speed.z^2+2*speed.y^2+2*speed.x^2)
        */
        void Target::onUpdate()
        {
          Kernel::Object* laser_object = getViewPoint()->getLaser() ;
          Laser* laser = laser_object ? laser_object->getTrait<Laser>():NULL ; 
          float laser_speed = laser? laser->getLaserSpeedMeterPerSecond():0 ;

          if (laser_speed > 0)
          {
            Ogre::Vector3 position = getObject()->getTrait<Positionned>()->getPosition().Meter() ;
            Ogre::Vector3 speed = getObject()->getTrait<Mobile>()->getSpeed().MeterPerSecond() ;
            
            float time ;
            
            if (speed.length() != 0)
            {
              time 
              = (sqrt((-4*pow(position.y,2)-4*pow(position.x,2))*pow(speed.z,2)+(8*position.y*position.z*speed.y+8*position.x*position.z*speed.x-4*position.z*laser_speed)*speed.z+(-4*pow(position.z,2)-4*pow(position.x,2))*pow(speed.y,2)+(8*position.x*position.y*speed.x-4*position.y*laser_speed)*speed.y+(-4*pow(position.z,2)-4*pow(position.y,2))*pow(speed.x,2)-4*position.x*laser_speed*speed.x+pow(laser_speed,2))
                 -2*position.z*speed.z-2*position.y*speed.y-2*position.x*speed.x+laser_speed)
                 /(2*pow(speed.z,2)+2*pow(speed.y,2)+2*pow(speed.x,2)) ;
            }
            else
            {
              time = position.length()/laser_speed ;
            }
            
            Ogre::Vector3 touch = position + speed*time ; 
            Position touch_position(Position::Meter(touch.x,touch.y,touch.z)) ;
            
            // if no ideal target create
            if (! m_ideal_target)
            {
              Kernel::Model* model = getObject()->getModel() ;
              m_ideal_target = model->createObject(getObject()) ;
              model->addTrait(m_ideal_target,new Positionned()) ;
              model->addTrait(m_ideal_target,new IdealTarget()) ;
            }
            
            // update ideal target
            Positionned* positionned = m_ideal_target->getTrait<Positionned>() ;
            positionned->setPosition(touch_position) ;
          }
          else
          {
            // remove the helper object
            if (m_ideal_target)
            {
              getObject()->getModel()->destroyObject(m_ideal_target) ;
            }
          }
        }
      }
    }
  }
}
