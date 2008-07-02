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
#include <Ogre.h>
#include <OgreDefaultHardwareBufferManager.h>

#include <kernel/log.h>
#include <kernel/error.h>
#include <kernel/trait.h>
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/command_delegator.h>
#include <kernel/parameters.h>
#include <kernel/xml_reader.h>

#include <model/laser.h>
#include <model/exception.h>
#include <model/destroyable.h>
#include <model/observer.h>
#include <model/massive.h>
#include <model/component.h>
#include <model/mobile.h>
#include <model/physical_object.h>
#include <model/physical_world.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/stellar_system.h>
#include <model/solid.h>
#include <model/stabilizer.h>
#include <model/torque_generator.h>
#include <model/universe.h>
#include <model/guidance_system.h>
#include <model/guidance_controler.h>
#include <model/engine.h>
#include <model/engine_controler.h>
#include <model/stick.h>
#include <model/throttle.h>
#include <model/dragger.h>
#include <model/menu.h>
#include <model/computer.h>
#include <model/detector.h>
#include <model/targeting_system.h>
#include <model/target_displayer.h>
#include <model/shooting_helper.h>
#include <model/transponder.h>
#include <model/with_objectives.h>
#include <model/autonomous_character.h>
#include <model/implementation/logic/logic.h>
#include <model/team.h>
#include <model/player.h>
#include <model/player_configuration.h>
#include <model/game_state.h>

#include <model/model.h>


using namespace Ogre ;

namespace ProjetUnivers {
  namespace Model 
  {

  /*!
    @name Module data.
  */
  // @{

    /// for ogre mesh loading     
    LogManager*                   log_manager = NULL ;
    DefaultHardwareBufferManager* hardware_buffer_manager = NULL ;
    Root*                         root = NULL ;

  // @}
    
    void load(const std::string& name,Kernel::Object* parent)
    {
     
      if (name == "TestDemonstration")
      {
        /// 1. Construction d'un univers
        InternalMessage("Model","building Universe...") ;
        Kernel::Object* universe = parent->createObject() ;
        
        /// ses facettes
        universe->addTrait(new Universe()) ;
        universe->addTrait(new Positionned()) ;
        
        InternalMessage("Model","construction de Univers terminée") ;

        /// 1.4 Une galaxie
        
        /// 1.5 Un système stellaire
        InternalMessage("Model","building stellar system...") ;
        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new StellarSystem()) ;
        system->addTrait(new Positionned()) ;
        InternalMessage("Model","building stellar system done") ;
        
        
        /// 2. Ajout d'objects planetes
        InternalMessage("Model","building planet...") ;
        Kernel::Object* planet1 = system->createObject() ;
        planet1->addTrait(new Positionned()) ;
        InternalMessage("Model","building planet done") ;

        // 2 teams
        Kernel::Object* team1 = parent->createObject() ;
        team1->addTrait(new Team("team1")) ;
        Kernel::Object* team2 = parent->createObject() ;
        team2->addTrait(new Team("team2")) ;
        
        
        /// 3. Ajout d'un vaisseau
        {
          InternalMessage("Model","building ship...") ;
                    
          Kernel::Object* ship = createShip(system) ;
          ship->addTrait(new Transponder(team1)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,200,-500)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
          
          InternalMessage("Model","building ship done") ;
        }
        {
          InternalMessage("Model","building ship...") ;
          Kernel::Object* ship = system->createObject() ;
          ship->addTrait(new Positionned(Position::Meter(-200,
                                                         50,
                                                         -500))) ;
          ship->addTrait(new Oriented()) ;
          ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
          ship->addTrait(new Mobile()) ;
          ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
          ship->addTrait(new Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;

          Kernel::Object* st1 = ship->createObject() ;
          st1->addTrait(new Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;

          Kernel::Object* st2 = ship->createObject() ;
          st2->addTrait(new Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;

          Kernel::Object* st3 = ship->createObject() ;
          st3->addTrait(new Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;

          InternalMessage("Model","building ship done") ;
        }

        {
          InternalMessage("Model","building ship...") ;
          Kernel::Object* ship = system->createObject() ;
          ship->addTrait(new Positionned(Position::Meter(200,50,-1000))) ;
          ship->addTrait(new Oriented()) ;
          
          ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
          ship->addTrait(new Mobile()) ;
          ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
          ship->addTrait(new Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;

          Kernel::Object* st1 = ship->createObject() ;
          st1->addTrait(new Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;

          Kernel::Object* st2 = ship->createObject() ;
          st2->addTrait(new Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;

          Kernel::Object* st3 = ship->createObject() ;
          st3->addTrait(new Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;


          Kernel::Object* stick = system->createObject() ;
          stick->addTrait(new Positionned(Position::Meter(0,0,-50))) ;
          stick->addTrait(new Stick()) ;
          
          ship->addTrait(new GuidanceSystem(Kernel::Parameters::getValue<float>("Model","GuidanceForce"))) ;
          ship->addTrait(new GuidanceControler()) ;
          // stick,ship
          connectStickControler(stick,ship) ;
          connectControlerGuidanceSystem(ship,ship) ;
          
          /// engine + engine control...
          Kernel::Object* throttle = ship->createObject() ;
          throttle->addTrait(new Throttle()) ;
          
          Kernel::Object* engine = ship->createObject() ;
          engine->addTrait(new Engine(Force::Newton(0,0,Kernel::Parameters::getValue<float>("Model","EngineMaxForce")))) ;
  
          Kernel::Object* engine_control = ship->createObject() ;
          engine_control->addTrait(new EngineControler()) ;

          connectThrottleControler(throttle,engine_control) ;
          connectControlerEngine(engine_control,engine) ;                   
          
          Kernel::Object* laser = ship->createObject() ;
          laser->addTrait(new Laser(Position::Meter(19.2,0,57),
                                    Orientation(),
                                    Energy::Joule(10))) ;
          laser->addTrait(new Component()) ;
          
          ship->addTrait(new Transponder(team2)) ;
          ship->addTrait(new Destroyable(Energy::Joule(10))) ;
          
          
          InternalMessage("Model","building ship done") ;
        }
        {
          /// 4. Ajout d'un observateur
          InternalMessage("Model","building observer...") ;
          
          Kernel::Object* ship = createShip(system) ;
          ship->getTrait<Oriented>()->setOrientation(Orientation(Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y))) ;
                    
          Kernel::Object* observer = ship->createObject() ;
          observer->addTrait(new Positionned()) ;
          observer->addTrait(new Oriented()) ;
          // targeting system
          Kernel::Object* computer = observer->createObject() ;
          computer->addTrait(new Computer()) ;
          
          Kernel::Object* detector = observer->createObject() ;
          detector->addTrait(new Detector(computer,Distance(Distance::_Meter,8000))) ;
          
          Kernel::Object* target_selector = observer->createObject() ;
          target_selector->addTrait(new TargetingSystem()) ;
          TargetingSystem::connect(target_selector,computer) ;
          
          Kernel::Object* target_display = observer->createObject() ;
          target_display->addTrait(new TargetDisplayer()) ;
          TargetDisplayer::connect(target_display,target_selector) ;

          Kernel::Object* laser_observer = observer->createObject() ;
          laser_observer->addTrait(new Laser(Position(),Orientation(),Energy::Joule(10))) ;

          Kernel::Object* shooting_helper = observer->createObject() ;
          shooting_helper->addTrait(new ShootingHelper()) ;
          ShootingHelper::connect(shooting_helper,computer,laser_observer) ;
          
          observer->addTrait(new Observer()) ;
          observer->addTrait(new Player()) ;
          observer->addTrait(new Transponder(team1)) ;
        }
        InternalMessage("Model","building observer done") ;
      }
      else if (name == "TestMenu")
      {
        Kernel::Object* universe = parent->createObject() ;
        
        /// ses facettes
        universe->addTrait(new Menu("ProjetUnivers.layout")) ;
        universe->addTrait(new Universe()) ;
        universe->addTrait(new Positionned()) ;

        Kernel::Object* ship = universe->createObject() ;
        ship->addTrait(new Positionned(Position::Meter(0,0,-500))) ;
        ship->addTrait(new Oriented()) ;
        ship->addTrait(new Solid(Mesh("razor.mesh"))) ;

        /// 4. Ajout d'un observateur
        InternalMessage("Model","building observer...") ;
        Kernel::Object* observer = universe->createObject() ;
        observer->addTrait(new Positionned()) ;
        observer->addTrait(new Oriented()) ;
        observer->addTrait(new Observer()) ;
        observer->addTrait(new Player()) ;
      }
      else if (name == "TestPilot")
      {
        
        Kernel::Object* player_configuration = 
          createDefaultPlayerConfiguration(parent) ;
        
        Kernel::Object* universe = parent->createObject() ;
        universe->addTrait(new Universe()) ;
        universe->addTrait(new Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new StellarSystem()) ;
        system->addTrait(new Positionned()) ;

        // 2 teams
        Kernel::Object* team1 = parent->createObject() ;
        team1->addTrait(new Team("team1")) ;
        Kernel::Object* team2 = parent->createObject() ;
        team2->addTrait(new Team("team2")) ;

        {
          Kernel::Object* ship = createShip(system) ;
          ship->addTrait(new Transponder(team1)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,0,0)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }
        {
          Kernel::Object* ship = createShip(system) ;
          ship->addTrait(new Transponder(team1)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,500,0)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }

        {
          Kernel::Object* ship = createShip(system) ;
          ship->addTrait(new Transponder(team2)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,0,1100)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }
        {
          Kernel::Object* ship = createShip(system) ;
          ship->addTrait(new Transponder(team2)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,0,3000)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }
        
        {
          Kernel::Object* ship = createShip(system) ;
          ship->addTrait(new Transponder(team1)) ;
          ship->addTrait(new TargetDisplayer()) ;
          TargetDisplayer::connect(ship,ship) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,-500,0)) ;
          
          Kernel::Object* player = ship->createObject() ;
          player->addTrait(new Positionned()) ;
          player->addTrait(new Oriented()) ;
          player->addTrait(new Player()) ;
          player->addTrait(new Observer()) ;
          player->addTrait(new Kernel::CommandDelegator()) ;
          player->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
          Player::connect(player,player_configuration) ;
        }
      }
      /// @todo
      
//      else
//      {
//        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getFileReader(name)) ;
//        reader->read(model) ;
//      }            
    }

    void initRessources()
    {
      /// if sufficient ressources have not been initialised...
      InternalMessage("Model","Model::initRessources entering") ;
      if (! MeshManager::getSingletonPtr())
      {
        log_manager = new LogManager() ;
        log_manager->createLog("Ogre.log", false, false); 
        root = new Root() ;
        hardware_buffer_manager = new DefaultHardwareBufferManager() ;
                
        ConfigFile file ;
        file.load("ressources.cfg") ;

        // On parcours ses sections
        ConfigFile::SectionIterator section = file.getSectionIterator();

        String nomSection, nomType, nomArchitecture ;
        while (section.hasMoreElements())
        {
          nomSection = section.peekNextKey();
          ConfigFile::SettingsMultiMap* settings = section.getNext();
          
          ConfigFile::SettingsMultiMap::iterator i;
          for (i = settings->begin(); i != settings->end(); ++i)
          {
              nomType = i->first;
              nomArchitecture = i->second;
              ResourceGroupManager::getSingleton().addResourceLocation(
                  nomArchitecture, nomType, nomSection);
          }
          
        }
        
      }

      InternalMessage("Model","Model::initRessources leaving") ;

    }

    void closeRessources()
    {
      if (root)
      {
        delete root ;
        root = NULL ;
      }
      if (log_manager)
      {
        delete log_manager ;
        log_manager = NULL ;
      }
      if (hardware_buffer_manager)
      {
        delete hardware_buffer_manager ;
        hardware_buffer_manager = NULL ;
      }
    }
    
    Kernel::Object* getControledShip(Kernel::Object* agent)
    {
      Kernel::CommandDelegator* delegator = agent->getTrait<Kernel::CommandDelegator>() ;
      if (! delegator)
        return NULL ;

      const std::set<Kernel::ObjectReference>& delegates = delegator->getDelegates() ;
      /*
        we look up in delegates something that is a physical object...
      */
      for(std::set<Kernel::ObjectReference>::const_iterator delegate = delegates.begin() ; 
          delegate != delegates.end() ;
          ++delegate)
      {
        if (*delegate)
        {
          Kernel::Object* temp = getShip(*delegate) ;
          if (temp)
            return temp ;
        }
      }
      return NULL ;
    }
    
    Kernel::Object* getShip(Kernel::Object* object)
    {
      /// @todo find a proper way
      Model::PhysicalObject* result = object->getParent<PhysicalObject>() ;
      if (result)
        return result->getObject() ;
      
      return NULL ;
    }
    
    Kernel::Object* createShip(Kernel::Object* parent)
    {
      Kernel::Object* ship = parent->createObject() ;
      ship->addTrait(new Positionned()) ;
      ship->addTrait(new Oriented()) ;
      ship->addTrait(new Massive(Mass::Kilogram(Kernel::Parameters::getValue<float>("Model","ShipMass")))) ;
      ship->addTrait(new Mobile()) ;
      ship->addTrait(new Solid(Mesh("razor.mesh"))) ;
      ship->addTrait(new Computer()) ;
      ship->addTrait(new Detector(ship,Distance(Distance::_Meter,8000))) ;
      ship->addTrait(new TargetingSystem()) ;
      ship->addTrait(new GuidanceSystem(Kernel::Parameters::getValue<float>("Model","GuidanceForce"))) ;
      ship->addTrait(new GuidanceControler()) ;
      ship->addTrait(new ShootingHelper()) ;
      ship->addTrait(new Destroyable(Energy::Joule(10))) ;

      Kernel::Object* laser = ship->createObject() ;
      laser->addTrait(new Laser(Position::Meter(19.2,0,57),
                                      Orientation(),
                                      Energy::Joule(10))) ;
      laser->addTrait(new Component()) ;
      laser->getTrait<Laser>()->setShotTimeDelay(Duration::Second(1)) ;
      ShootingHelper::connect(ship,ship,laser) ;
      TargetingSystem::connect(ship,ship) ;
      
      ship->addTrait(new Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;
      Kernel::Object* st1 = ship->createObject() ;
      st1->addTrait(new Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;
      st1->addTrait(new Component()) ;
      Kernel::Object* st2 = ship->createObject() ;
      st2->addTrait(new Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;
      st2->addTrait(new Component()) ;
      Kernel::Object* st3 = ship->createObject() ;
      st3->addTrait(new Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;
      st3->addTrait(new Component()) ;

      Kernel::Object* stick = ship->createObject() ;
      stick->addTrait(new Positionned()) ;
      stick->addTrait(new Stick()) ;
      stick->addTrait(new Component()) ;
      
      // stick,ship
      connectStickControler(stick,ship) ;
      connectControlerGuidanceSystem(ship,ship) ;
      
      /// engine + engine control...
      Kernel::Object* throttle = ship->createObject() ;
      throttle->addTrait(new Throttle()) ;
      throttle->addTrait(new Positionned()) ;
      throttle->addTrait(new Component()) ;
      
      Kernel::Object* engine = ship->createObject() ;
      engine->addTrait(new Engine(Force::Newton(0,0,Kernel::Parameters::getValue<float>("Model","EngineMaxForce")))) ;
      engine->addTrait(new Component()) ;
      
      Kernel::Object* engine_control = ship->createObject() ;
      engine_control->addTrait(new EngineControler()) ;
      engine_control->addTrait(new Component()) ;

      connectThrottleControler(throttle,engine_control) ;
      connectControlerEngine(engine_control,engine) ;                   
      
      return ship ;
    }
    
    Kernel::Object* createAI(Kernel::Object* ship)
    {
      Kernel::Object* agent = ship->createObject() ;
      agent->addTrait(new AutonomousCharacter()) ;
      agent->addTrait(new WithObjectives()) ;
      agent->addTrait(new Kernel::CommandDelegator()) ;
      agent->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

      return agent ;
    }
    
    Kernel::Object* createDefaultPlayerConfiguration(Kernel::Object* parent)
    {
      Kernel::Object* configuration = parent->createObject() ;
      // input player config...
      configuration->addTrait(new PlayerConfiguration()) ;
      configuration->getTrait<PlayerConfiguration>()
                   ->addMapping(PlayerConfiguration::InputEvent::key(OIS::KC_F),"fire") ;
      configuration->getTrait<PlayerConfiguration>()
                   ->addMapping(PlayerConfiguration::InputEvent::key(OIS::KC_S),"Select Next Target") ;
      configuration->getTrait<PlayerConfiguration>()
                   ->addMapping(PlayerConfiguration::InputEvent::key(OIS::KC_P),"Select Previous Target") ;
      configuration->getTrait<PlayerConfiguration>()
                   ->addMapping(PlayerConfiguration::InputEvent::key(OIS::KC_N),"Select Nearest Enemy") ;
      
      // axis
      configuration->getTrait<PlayerConfiguration>()
                   ->addMapping(PlayerConfiguration::InputAxis::joystickAxis(
                       int(Kernel::Parameters::getValue<float>("Input","ThrottelAxis"))),
                       "Throttle") ;
      configuration->getTrait<PlayerConfiguration>()
                   ->addMapping(PlayerConfiguration::InputAxis::joystickAxis(
                       int(Kernel::Parameters::getValue<float>("Input","XAxis"))),
                       "Yaw") ;
      configuration->getTrait<PlayerConfiguration>()
                   ->addMapping(PlayerConfiguration::InputAxis::joystickAxis(
                       int(Kernel::Parameters::getValue<float>("Input","YAxis"))),
                       "Pitch") ;
      configuration->getTrait<PlayerConfiguration>()
                   ->addMapping(PlayerConfiguration::InputAxis::joystickAxis(
                       int(Kernel::Parameters::getValue<float>("Input","ZAxis"))),
                       "Roll") ;
      
      return configuration ;
    }
    
  }
}


