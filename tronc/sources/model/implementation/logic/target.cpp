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
#include <kernel/log.h>
#include <kernel/string.h>
#include <kernel/algorithm.h>
#include <model/position.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/solid.h>
#include <model/laser.h>
#include <model/shootable.h>
#include <model/mobile.h>
#include <model/ideal_target.h>
#include <model/physical_world.h>
#include <model/physical_object.h>
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
        
        void Target::onUpdate()
        {
          InternalMessage("Model","entering Logic::Target::onUpdate") ;
          
          Kernel::Object* laser_object = getViewPoint()->getLaser() ;
          Laser* laser = laser_object ? laser_object->getTrait<Laser>():NULL ; 
          float laser_speed = laser? laser->getLaserSpeedMeterPerSecond():0 ;

          if (laser_speed <= 0)
          {
            removeIdealTarget() ;
            InternalMessage("Model","leaving Logic::Target::onUpdate") ;
            return ;
          }
          Ogre::Vector3 position = getObject()->getTrait<Positionned>()->getPosition().Meter() ;
          Ogre::Vector3 speed = getObject()->getTrait<Mobile>()->getSpeed().MeterPerSecond() ;
          
          std::pair<bool,float> reachable_time = 
            Kernel::Algorithm::calculateInterceptionTime(position,speed,laser_speed) ;
          

          if (! reachable_time.first)
          {
            /// no real solution : target is unreachable by laser
            removeIdealTarget() ;
            InternalMessage("Model","leaving Logic::Target::onUpdate") ;
            return ;
          }

          const float time = reachable_time.second ;
          
          Ogre::Vector3 touch = position + speed*fabs(time) ; 
          Position touch_position(Position::Meter(touch.x,touch.y,touch.z)) ;
          
          Kernel::Model* model = getObject()->getModel() ;
          // if no ideal target create
          if (! m_ideal_target)
          {
            m_ideal_target = model->createObject(getObject()) ;
            model->addTrait(m_ideal_target,new Positionned()) ;
            model->addTrait(m_ideal_target,new IdealTarget()) ;
          }
          // update ideal target
          Positionned* positionned = m_ideal_target->getTrait<Positionned>() ;
          positionned->setPosition(touch_position) ;
          
          // calculate shootable status
          InternalMessage("Model","calculating shootable status") ;
          bool shootable = true ;
          
          // range
          float beam_duration_in_seconds = laser->getLaserBeamLifeDuration().Second() ;
          if (time > beam_duration_in_seconds)
            shootable = false ;
          
          // direction
          if (shootable)
          {
            InternalMessage("Model","calculating shootable status#0") ;
            PhysicalObject* object = laser->getObject()->getParent<PhysicalObject>() ;
            if (!object)
              return ;
            Oriented* oriented = laser->getObject()->getParent<Oriented>() ;
            Orientation orientation_of_laser = oriented->getOrientation(object->getObject()) ;

            const Position& position_of_the_beam = 
              laser->getOutPosition()*orientation_of_laser + 
              getRelativePosition(laser->getObject(),object->getObject()) ;

            Orientation orientation_of_the_beam =
              orientation_of_laser*laser->getOutOrientation() ;
            
            // the line of the beam 
            Ogre::Vector3 out_of_laser = position_of_the_beam.Meter() ;
            Ogre::Vector3 forward_of_laser = 
              out_of_laser + orientation_of_the_beam.getQuaternion().zAxis() ;
            
            // calculate nearest point of that line with target position 
            Ogre::Vector3 A = position - out_of_laser ;
            Ogre::Vector3 u = (forward_of_laser-out_of_laser).normalisedCopy() ;
            Ogre::Vector3 nearest_point = out_of_laser + (A.dotProduct(u)) * u ;

            InternalMessage("Model","A=" + Ogre::StringConverter::toString(A)) ;
            InternalMessage("Model","u*10=" + Ogre::StringConverter::toString(u*10)) ;
            InternalMessage("Model","out_of_laser=" + Ogre::StringConverter::toString(out_of_laser)) ;
            InternalMessage("Model","forward_of_laser=" + Ogre::StringConverter::toString(forward_of_laser)) ;
            InternalMessage("Model","nearest_point=" + Ogre::StringConverter::toString(nearest_point)) ;
            InternalMessage("Model","orientation_of_the_beam=" + Ogre::StringConverter::toString(orientation_of_the_beam.getQuaternion())) ;
            InternalMessage("Model","position=" + Ogre::StringConverter::toString(position)) ;
            
            if (nearest_point.dotProduct(u) >= 0)
            {
              float target_size = getObject()->getTrait<Solid>()->getRadius().Meter() ;
              InternalMessage("Model","target_size=" + Kernel::toString(target_size)) ;
              if (target_size <= (position-nearest_point).length())
              {
                shootable = false ;
              }
            }
            else
            {
              shootable = false ;
            }
         
            InternalMessage("Model",shootable?"shootable=true":"shootable=false") ;
            Shootable* shootable_trait = getObject()->getTrait<Shootable>() ;
            if (shootable_trait && !shootable)
            {
              model->destroyTrait(getObject(),shootable_trait) ;
            }
            else if (!shootable_trait && shootable)
            {
              model->addTrait(getObject(),new Shootable()) ;
            }
            
          }
          InternalMessage("Model","leaving Logic::Target::onUpdate") ;
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
