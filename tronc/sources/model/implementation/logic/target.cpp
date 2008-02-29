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
            
          delta = 
              (-position.y^2-position.x^2)*speed.z^2
              +(2*position.y*position.z*speed.y+2*position.x*position.z*speed.x)*speed.z
              +(-position.z^2-position.x^2)*speed.y^2
              +2*position.x*position.y*speed.x*speed.y
              +(-position.z^2-position.y^2)*speed.x^2
              +laser_speed^2*position.z^2
              +laser_speed^2*position.y^2
              +laser_speed^2*position.x^2
          
          if delta > 0
          t = (sqrt(delta)
                -position.z*speed.z-position.y*speed.y-position.x*speed.x)
              /(speed.z^2+speed.y^2+speed.x^2-laser_speed^2)
          
          special case for delta=0 when equation becomes linear
        */
        void Target::onUpdate()
        {
          Kernel::Object* laser_object = getViewPoint()->getLaser() ;
          Laser* laser = laser_object ? laser_object->getTrait<Laser>():NULL ; 
          float laser_speed = laser? laser->getLaserSpeedMeterPerSecond():0 ;

          if (laser_speed < 0)
          {
            removeIdealTarget() ;
            return ;
          }
          Ogre::Vector3 position = getObject()->getTrait<Positionned>()->getPosition().Meter() ;
          Ogre::Vector3 speed = getObject()->getTrait<Mobile>()->getSpeed().MeterPerSecond() ;
          
          float time ;
          
          if (speed.length() != 0)
          {
            
            float delta = 
                    (-pow(position.y,2)-pow(position.x,2))*pow(speed.z,2)
                    +(2*position.y*position.z*speed.y+2*position.x*position.z*speed.x)*speed.z
                    +(-pow(position.z,2)-pow(position.x,2))*pow(speed.y,2)
                    +2*position.x*position.y*speed.x*speed.y
                    +(-pow(position.z,2)-pow(position.y,2))*pow(speed.x,2)
                    +pow(laser_speed,2)*pow(position.z,2)
                    +pow(laser_speed,2)*pow(position.y,2)
                    +pow(laser_speed,2)*pow(position.x,2) ;
            
            float divisor = pow(speed.z,2)+pow(speed.y,2)+pow(speed.x,2)-pow(laser_speed,2) ;
            
            if (delta > 0 && divisor != 0)
            {
              time 
              = (sqrt(delta)
                  -position.z*speed.z-position.y*speed.y-position.x*speed.x)
                 /(divisor) ;
            }
            else
            {
              /// no real solution : target is unreachable by laser
              removeIdealTarget() ;
              return ;
            }
          }
          else
          {
            time = position.length()/laser_speed ;
          }
          
          Ogre::Vector3 touch = position + speed*fabs(time) ; 
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
        
        void Target::removeIdealTarget()
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
