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

#include <model/area.h>
#include <model/autonomous_character.h>
#include <model/custom_mission.h>
#include <model/destroyable.h>
#include <model/flying_group.h>
#include <model/mission.h>
#include <model/observer.h>
#include <model/oriented.h>
#include <model/player.h>
#include <model/positionned.h>
#include <model/sized.h>
#include <model/state.h>
#include <model/target_displayer.h>
#include <model/team.h>
#include <model/transponder.h>
#include <model/with_objectives.h>

#include <model/model.h>
#include <model/implementation/with_flying_group.h>
#include <model/implementation/logic/flying_group.h>

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

        FlyingGroup::FlyingGroup(Implementation::ActivatedFlyingGroup* group,
                                 LogicSystem*                          system)
        : Kernel::Controler<Implementation::ActivatedFlyingGroup,
                            LogicSystem>(group,system),
          m_number_of_spawn(0)
        {}
        
        Position FlyingGroup::getStartingPosition() const
        {
          std::set<Position> enemy_positions ;
          Mission* mission = getObject()->getParent<Mission>() ;
          Team* team = getObject()->getParent<Team>() ;
          Kernel::Object* system = mission->getSystem() ;

          std::set<WithFlyingGroup*> ships(system->getChildren<WithFlyingGroup>()) ;
          
          for(std::set<WithFlyingGroup*>::const_iterator ship = ships.begin() ;
              ship != ships.end() ;
              ++ship)
          {
            Kernel::Object* ship_group = (*ship)->getFlyingGroup() ;
            Team* ship_team = ship_group->getParent<Team>() ;
            if (ship_team != team)
              enemy_positions.insert((*ship)->getObject()->getTrait<Positionned>()->getPosition()) ;
          }

          Area enemy_area(enemy_positions) ;
          
          Distance distance = enemy_area.getRadius() + mission->getStartingDistance() ;
          Position delta(Position::Meter(distance.Meter(),0,0)) ;
          return Position(enemy_area.getCenter()+delta) ;
        }
        
        void FlyingGroup::onInit()
        {
          InternalMessage("Mission","FlyingGroup::onInit") ;
          Position starting_position(getStartingPosition()) ;
          Distance radius ;
          
          // create the ships in the system
          Mission* mission = getObject()->getParent<Mission>() ;
          Team* team = getObject()->getParent<Team>() ;
          
          Kernel::Object* system = mission->getSystem() ;
          
          Model::FlyingGroup* group = getTrait<Model::FlyingGroup>() ;
          
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
            
            if (ship->getTrait<Positionned>())
            {
              ship->getTrait<Positionned>()->setPosition(starting_position+delta) ;
            }
            
            // create the pilot
            Kernel::Object* pilot = ship->createObject() ;
            
            if (i == 1 && group->hasPlayer())
            {
              ship->addTrait(new TargetDisplayer()) ;
              TargetDisplayer::connect(ship,ship) ;
              
              pilot->addTrait(new Positionned()) ;
              pilot->addTrait(new Oriented()) ;
              pilot->addTrait(new Player()) ;
              pilot->addTrait(new Observer()) ;
              
              Player::connect(pilot,mission->getPlayerConfiguration()) ;
              pilot->addTrait(new State()) ;
              pilot->getTrait<State>()->addCommandAlias("Menu","push(main_menu_in_game,Displayed)") ;
              pilot->getTrait<State>()->setCommandOnQuit("change(main_menu,Displayed)") ;
              
            }
            else
            {
              pilot->addTrait(new AutonomousCharacter()) ;
              pilot->addTrait(new WithObjectives()) ;
              pilot->getTrait<WithObjectives>()->addObjective(group->getObjective()) ;
            }

            pilot->addTrait(new Kernel::CommandDelegator()) ;
            pilot->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
            
            group->addShip() ;
          }
          
          ++m_number_of_spawn ;
          InternalMessage("Mission","FlyingGroup::onInit") ;
        }

        void FlyingGroup::onUpdate()
        {
          if (getTrait<Model::FlyingGroup>()->getNumberOfShips() == 0 && 
              m_number_of_spawn < getTrait<Model::FlyingGroup>()->getNumberOfSpawn())
          {
            onInit() ;
          }
        }

      }
    }
  }
}

