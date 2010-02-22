/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2010 Mathieu ROGER                                 *
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
#include <model/positioned.h>
#include <model/oriented.h>
#include <model/solid.h>
#include <model/laser.h>
#include <model/has_in_line_of_sight.h>
#include <model/mobile.h>
#include <model/ideal_target.h>
#include <model/physical_world.h>
#include <model/physical_object.h>

#include <model/implementation/logic/target.h>
#include <model/computer.h>
#include <model/data_connection.h>

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Implementation
    {
      namespace Logic
      {

        RegisterRelationControler(Target,
                                  Implementation::Target,
                                  LogicSystem) ;

        void Target::onInit()
        {
          onUpdate() ;
        }

        void Target::onClose()
        {
          if (m_ideal_target)
          {
            m_ideal_target->destroyObject() ;
          }
        }

        void Target::onUpdate()
        {
          InternalMessage("Model","entering Logic::Target::onUpdate") ;

          /// @todo deal with multiple lasers
          /*
            All the calculus works with one laser...
            But how to do it with multiple...

            Maybe we should simply take the front of the ship and the mean speed
            of lasers assuming they all point forward

          */
          Laser* laser = getObjectFrom()->getChild<Laser>() ;
          float laser_speed = laser->getLaserSpeedMeterPerSecond() ;

          if (laser_speed <= 0)
          {
            removeIdealTarget() ;
            InternalMessage("Model","leaving Logic::Target::onUpdate") ;
            return ;
          }

          Kernel::Object* world = getObjectTo()->getParent<PhysicalObject>()->getPhysicalWorld() ;

          // absolute position in physical world
          Ogre::Vector3 target_absolute_position = getObjectTo()->getTrait<Positioned>()->getPosition(world).Meter() ;
          Ogre::Vector3 targeting_absolute_position = getObjectFrom()->getTrait<Positioned>()->getPosition(world).Meter() ;
          Ogre::Vector3 position = target_absolute_position-targeting_absolute_position ;

          // relative to ship's physical world
          Ogre::Vector3 speed = getObjectTo()->getTrait<Mobile>()->getSpeed().MeterPerSecond() ;

          InternalMessage("Model","calculateInterceptionTime(" + Ogre::StringConverter::toString(position)
		                          + "," + Ogre::StringConverter::toString(speed) + "," + Kernel::toString(laser_speed) +")") ;

          std::pair<bool,float> reachable_time =
            Kernel::Algorithm::calculateInterceptionTime(position,speed,laser_speed) ;

          InternalMessage("Model",std::string("calculated interception time=") + (reachable_time.first?"true ":"false")
                                  + "," + Kernel::toString(reachable_time.second)) ;


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

          Kernel::Model* model = getObjectFrom()->getChild<Computer>()->getMemoryModel() ;
          // if no ideal target create
          if (! m_ideal_target)
          {
            m_ideal_target = model->createObject() ;
            m_ideal_target->addTrait(new Positioned()) ;
            m_ideal_target->addTrait(new IdealTarget(getObjectFrom()->getChild<Computer>()->getObject())) ;
          }
          // update ideal target, position is relative to world
          Positioned* positioned = m_ideal_target->getTrait<Positioned>() ;
          positioned->setPosition(touch_position) ;

          // calculate shootable status
          InternalMessage("HasInLineOfSight","calculating shootable status") ;
          bool shootable = true ;

          // range
          float beam_duration_in_seconds = laser->getLaserBeamLifeDuration().Second() ;
          if (time > beam_duration_in_seconds)
            shootable = false ;

          // direction
          if (shootable)
          {
            InternalMessage("HasInLineOfSight","calculating shootable status#0") ;
            PhysicalObject* object = laser->getObject()->getParent<PhysicalObject>() ;
            if (!object)
              return ;

            Orientation orientation_of_laser = getRelativeOrientation(laser->getObject(),world) ;

            // in local space but global orientation
            const Position& position_of_the_beam = laser->getOutPosition()*orientation_of_laser ;

            Orientation orientation_of_the_beam = orientation_of_laser*laser->getOutOrientation() ;

            // the line of the beam
            Ogre::Vector3 out_of_laser = position_of_the_beam.Meter() ;
            // the line of the beam
            // forward of the beam (-z axis of orientation)
            Ogre::Vector3 forward_of_laser = - orientation_of_the_beam.getQuaternion().zAxis() ;

            // calculate nearest point of that line with target position

            // in local position space
            Ogre::Vector3 A = position - out_of_laser ;
            Ogre::Vector3 u = forward_of_laser.normalisedCopy() ;
            Ogre::Vector3 nearest_point = out_of_laser + (A.dotProduct(u)) * u ;

            InternalMessage("HasInLineOfSight","A=" + Ogre::StringConverter::toString(A)) ;
            InternalMessage("HasInLineOfSight","u*10=" + Ogre::StringConverter::toString(u*10)) ;
            InternalMessage("HasInLineOfSight","out_of_laser=" + Ogre::StringConverter::toString(out_of_laser)) ;
            InternalMessage("HasInLineOfSight","forward_of_laser=" + Ogre::StringConverter::toString(forward_of_laser)) ;
            InternalMessage("HasInLineOfSight","nearest_point=" + Ogre::StringConverter::toString(nearest_point)) ;
            InternalMessage("HasInLineOfSight","orientation_of_the_beam=" + Ogre::StringConverter::toString(orientation_of_the_beam.getQuaternion())) ;
            InternalMessage("HasInLineOfSight","position=" + Ogre::StringConverter::toString(position)) ;

            if (nearest_point.dotProduct(u) >= 0)
            {
              float target_size = getObjectTo()->getTrait<Solid>()->getRadius().Meter() ;
              InternalMessage("HasInLineOfSight","target_size=" + Kernel::toString(target_size)) ;
              if (target_size <= (position-nearest_point).length())
              {
                shootable = false ;
              }
            }
            else
            {
              shootable = false ;
            }

            InternalMessage("HasInLineOfSight",shootable?"shootable=true":"shootable=false") ;
            if (shootable)
            {
              Kernel::Link<HasInLineOfSight>(getObjectFrom(),getObjectTo()) ;
            }
            else
            {
              Kernel::UnLink<HasInLineOfSight>(getObjectFrom(),getObjectTo()) ;
            }

          }
          InternalMessage("Model","leaving Logic::Target::onUpdate") ;
        }

        void Target::removeIdealTarget()
        {
          // remove the helper object
          if (m_ideal_target)
          {
            m_ideal_target->destroyObject() ;
          }
        }

      }
    }
  }
}
