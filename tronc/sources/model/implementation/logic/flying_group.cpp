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
#include <kernel/command_delegator.h>

#include <model/active.h>
#include <model/area.h>
#include <model/autonomous_character.h>
#include <model/custom_mission.h>
#include <model/destroyable.h>
#include <model/flying_group.h>
#include <model/mission.h>
#include <model/observer.h>
#include <model/oriented.h>
#include <model/player.h>
#include <model/positioned.h>
#include <model/sized.h>
#include <model/state.h>
#include <model/head_up_display.h>
#include <model/team.h>
#include <model/transponder.h>
#include <model/with_objectives.h>
#include <model/listener.h>

#include <model/model.h>
#include <model/implementation/with_flying_group.h>
#include <model/implementation/activated_mission.h>
#include <model/implementation/logic/activated_mission.h>
#include <model/implementation/logic/flying_group.h>
#include <model/plays_in.h>
#include <model/plays.h>

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Implementation
    {
      namespace Logic
      {

        RegisterControler(FlyingGroup,
                          Implementation::ActivatedFlyingGroup,
                          LogicSystem) ;

        Position FlyingGroup::getStartingPosition() const
        {
          std::set<Position> enemy_positions ;
          Mission* mission = getObject()->getParent<Mission>() ;
          Team* team = getObject()->getParent<Team>() ;
          Kernel::Object* system = mission->getSystem() ;
          
          if (!system)
            return Position() ;
          
          std::set<WithFlyingGroup*> ships(system->getChildren<WithFlyingGroup>()) ;

          for(std::set<WithFlyingGroup*>::const_iterator ship = ships.begin() ;
              ship != ships.end() ;
              ++ship)
          {
            Kernel::Object* ship_group = (*ship)->getFlyingGroup() ;
            Team* ship_team = ship_group->getParent<Team>() ;
            if (ship_team != team)
              enemy_positions.insert((*ship)->getObject()->getTrait<Positioned>()->getPosition()) ;
          }

          Area enemy_area(enemy_positions) ;

          Distance distance = enemy_area.getRadius() + mission->getStartingDistance() ;
          Position delta(Position::Meter(distance.Meter(),0,0)) ;
          return Position(enemy_area.getCenter()+delta) ;
        }

        void createPlayerPilot(Kernel::Object* ship,Kernel::Object* pilot,Kernel::Object* player)
        {
          pilot->addTrait(new Positioned()) ;
          pilot->addTrait(new Oriented()) ;

          Kernel::Link<Plays>(player,pilot) ;

          pilot->addTrait(new State()) ;
          pilot->getTrait<State>()->addCommandAlias("Menu","push(main_menu_in_game,Displayed)") ;

          // fixme idem : head up displayed is the one of the local player ?
          ship->addTrait(new HeadUpDisplay()) ;
          HeadUpDisplay::connect(ship,ship) ;
        }

        void FlyingGroup::spawn()
        {
          Position starting_position(getStartingPosition()) ;
          Distance radius ;

          // create the ships in the system
          Mission* mission = getObject()->getParent<Mission>() ;
          Team* team = getObject()->getParent<Team>() ;

          Kernel::Object* system = mission->getSystem() ;

          Model::FlyingGroup* group = getTrait<Model::FlyingGroup>() ;

          // sometimes the player plays in the group
          Kernel::Object* player = getObject()->getUniqueLinked<Kernel::Inverse<PlaysIn> >() ;

          for(unsigned int i = 1 ; i <= group->getInitialNumberOfShips() ; ++i)
          {
            Kernel::Object* ship = Model::loadShip(group->getShipName(),system) ;
            ship->addTrait(new WithFlyingGroup(getTrait<Model::FlyingGroup>())) ;
            ship->addTrait(new Transponder(team->getObject())) ;

            ship->setName("ship #" + Kernel::toString(i) + " " + team->getName() + " "  + group->getName()) ;

            // position the ship
            if (i == 1 && ship->getTrait<Sized>())
              radius = 1.5*ship->getTrait<Sized>()->getRadius() ;
            Distance local = ((i-1)/2)*2*radius+radius ;
            Position delta ;
            if (i%2 == 1)
            {
              delta = Position::Meter(0,local.Meter(),0) ;
            }
            else
            {
              delta = Position::Meter(0,-local.Meter(),0) ;
            }

            if (ship->getTrait<Positioned>())
            {
              ship->getTrait<Positioned>()->setPosition(starting_position+delta) ;
            }

            // create the pilot
            Kernel::Object* pilot = ship->createObject() ;

            if (i == 1 && player)
            {
              createPlayerPilot(ship,pilot,player) ;
            }
            else
            {
              pilot->addTrait(new AutonomousCharacter()) ;
              pilot->addTrait(new WithObjectives()) ;
              pilot->getTrait<WithObjectives>()->addObjective(group->getObjective()) ;
            }

            pilot->addTrait(new Kernel::CommandDelegator()) ;
            pilot->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

            group->addShip(ship) ;
          }

          ++m_number_of_spawn ;
        }

        void FlyingGroup::onInit()
        {
          InternalMessage("Mission","FlyingGroup::onInit") ;

          m_number_of_spawn = 0 ;
          spawn() ;
          InternalMessage("Mission","FlyingGroup::onInit") ;
        }

        void FlyingGroup::onUpdate()
        {
          if (getTrait<Model::FlyingGroup>()->getNumberOfShips() == 0)
          {
            if (m_number_of_spawn < getTrait<Model::FlyingGroup>()->getNumberOfSpawn())
            {
              spawn() ;
            }
            else
            {
              Mission* mission = getObject()->getParent<Mission>() ;
                mission->getObject()->getTrait<Implementation::ActivatedMission>()
                                    ->getControler<Logic::ActivatedMission>(getControlerSet())
                                    ->indicateGroupHasNoMoreSpawn(getObject()) ;
            }
          }
        }

        void FlyingGroup::respawnPlayer()
        {
          Model::FlyingGroup* group = getTrait<Model::FlyingGroup>() ;

          Kernel::Object* player = getObject()->getUniqueLinked<Kernel::Inverse<PlaysIn> >() ;

          Kernel::Object* ship = group->getAIShip() ;
          if (ship)
          {
            std::set<AutonomousCharacter*> ais = ship->getChildren<AutonomousCharacter>() ;

            Kernel::Object* pilot = (*ais.begin())->getObject() ;
            pilot->destroyTrait(pilot->getTrait<AutonomousCharacter>()) ;
            createPlayerPilot(ship,pilot,player) ;
          }
        }


      }
    }
  }
}

