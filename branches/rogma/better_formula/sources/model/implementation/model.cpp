/***************************************************************************
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
#include <OgreFileSystem.h>
#include <OgreZip.h>

#include <kernel/log.h>
#include <kernel/error.h>
#include <kernel/trait.h>
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/command_delegator.h>
#include <kernel/parameters.h>
#include <kernel/xml_reader.h>
#include <kernel/xml_writer.h>

#include <model/laser.h>
#include <model/exception.h>
#include <model/end_of_simulation.h>
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
#include <model/head_up_display.h>
#include <model/shooting_helper.h>
#include <model/transponder.h>
#include <model/with_objectives.h>
#include <model/autonomous_character.h>
#include <model/implementation/logic/logic.h>
#include <model/team.h>
#include <model/player.h>
#include <model/player_configuration.h>
#include <model/state.h>
#include <model/image.h>
#include <model/displayed.h>
#include <model/with_lifetime.h>
#include <model/mission.h>
#include <model/custom_mission.h>
#include <model/flying_group.h>

#include <model/implementation/model_internal.h>
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
    Ogre::ResourceGroupManager*   ressource_group_manager = NULL ;
    Ogre::Math*                   math = NULL ;
    Ogre::MeshManager*            mesh_manager = NULL ;
    Ogre::MaterialManager*        material_manager = NULL ;
    Ogre::SkeletonManager*        skeleton_manager = NULL ;
    Ogre::ArchiveManager*         archive_manager = NULL ;
    Ogre::Root*                   root = NULL ;

    bool initialised = false ;

  // @}

    /// Search a filename in the ressources
    std::string findFilePath(const std::string& filename)
    {
      // on demand init
      Model::initRessources() ;

      std::string foundPath = filename;
      Ogre::ResourceGroupManager* groupManager = Ogre::ResourceGroupManager::getSingletonPtr() ;
      Ogre::String group = groupManager->findGroupContainingResource(filename) ;
      Ogre::FileInfoListPtr fileInfos = groupManager->findResourceFileInfo(group,foundPath) ;
      Ogre::FileInfoList::iterator it = fileInfos->begin();
      if(it != fileInfos->end())
      {
        foundPath = it->archive->getName() + "/" + foundPath;
      }
      else
        foundPath = "";

      return foundPath;
    }

    void start()
    {

    }

    void initRessources()
    {
      /// if sufficient ressources have not been initialised...
      InternalMessage("Model","Model::initRessources entering") ;
      if (! MeshManager::getSingletonPtr())
      {
        log_manager = new LogManager() ;
        log_manager->createLog("Ogre.log", false, false) ;
        root = new Root() ;
        hardware_buffer_manager = new DefaultHardwareBufferManager() ;
        MaterialManager::getSingletonPtr()->initialise() ;
        MeshManager::getSingletonPtr()->_initialise() ;
//        skeleton_manager = new SkeletonManager() ;
//        mesh_manager = new MeshManager();

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
        initialised = true ;


      }

      InternalMessage("Model","Model::initRessources leaving") ;

    }

    void closeRessources()
    {
      if (root)
      {
        delete hardware_buffer_manager ;
//        delete skeleton_manager ;
//        delete material_manager ;
//        delete mesh_manager ;
//        delete math ;
//        delete ressource_group_manager ;
        delete root ;

        initialised = false ;
      }
    }

    void loadMission(const std::string& name,
                     Kernel::Object* mission,
                     Kernel::Object* player_configuration,
                     Kernel::Object* main_menu)
    {
      if (name=="basic_mission")
      {

        Kernel::Object* universe = mission->createObject() ;
        universe->addTrait(new Universe()) ;
        universe->addTrait(new Positionned()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new StellarSystem()) ;
        system->addTrait(new Positionned()) ;

        // 2 teams
        Kernel::Object* team1 = mission->createObject() ;
        team1->addTrait(new Team("team1")) ;
        Kernel::Object* team2 = mission->createObject() ;
        team2->addTrait(new Team("team2")) ;

        {
          Kernel::Object* ship = loadShip("default_ship",system) ;
          ship->addTrait(new Transponder(team1)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,0,0)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }
        {
          Kernel::Object* ship = loadShip("default_ship",system) ;
          ship->addTrait(new Transponder(team1)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,500,0)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }

        {
          Kernel::Object* ship = loadShip("default_ship",system) ;
          ship->addTrait(new Transponder(team2)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,0,1100)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }
        {
          Kernel::Object* ship = loadShip("default_ship",system) ;
          ship->addTrait(new Transponder(team2)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,0,3000)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }

        {
          Kernel::Object* ship = loadShip("default_ship",system) ;
          ship->addTrait(new Transponder(team1)) ;
          ship->addTrait(new HeadUpDisplay()) ;
          HeadUpDisplay::connect(ship,ship) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,-500,0)) ;

          Kernel::Object* player = ship->createObject() ;
          player->addTrait(new Positionned()) ;
          player->addTrait(new Oriented()) ;
          player->addTrait(new Player()) ;
          player->addTrait(new Observer()) ;
          player->addTrait(new Kernel::CommandDelegator()) ;
          player->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
          Player::connect(player,player_configuration) ;
          player->addTrait(new State()) ;
          player->getTrait<State>()->addCommandAlias("Menu","push(main_menu_in_game,Displayed)") ;
          player->getTrait<State>()->setCommandOnQuit("change(main_menu,Displayed)") ;
        }
      }
      else
      {
      }
    }

    void load(const std::string& name,Kernel::Model* model)
    {
      if (name == "TestDemonstration")
      {
        /// 1. Construction d'un univers
        InternalMessage("Model","building Universe...") ;
        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Universe()) ;
        universe->addTrait(new Positionned()) ;
        universe->addTrait(new Active()) ;

        /// 1.5 Un système stellaire
        InternalMessage("Model","building stellar system...") ;
        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new StellarSystem()) ;
        system->addTrait(new Positionned()) ;
        InternalMessage("Model","building stellar system done") ;

        // 2 teams
        Kernel::Object* team1 = model->createObject() ;
        Kernel::Object* team2 = model->createObject() ;
        team1->addTrait(new Team("team1")) ;
        team2->addTrait(new Team("team2")) ;


        Kernel::ObjectReference ship1 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(-500,0,-1000)) ;
          ship->getTrait<Model::Oriented>()->setOrientation(Model::Orientation(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y))) ;
          ship->addTrait(new Model::Transponder(team1)) ;
          ship->destroyTrait(ship->getTrait<Model::Destroyable>()) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship1 = ship ;
        }

        Kernel::ObjectReference ship2 ;
        {
          Kernel::Object* ship = Model::createShip(system) ;
          ship->getTrait<Model::Positionned>()->setPosition(Model::Position::Meter(500,0,-1000)) ;
          ship->getTrait<Model::Oriented>()->setOrientation(Model::Orientation(Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y))) ;
          ship->addTrait(new Model::Transponder(team2)) ;
          ship->destroyTrait(ship->getTrait<Model::Destroyable>()) ;
          Kernel::Object* agent = Model::createAI(ship) ;
          agent->getTrait<Model::WithObjectives>()->addObjective(Model::Objective::attackAllEnemies()) ;
          ship2 = ship ;
        }

//        {
//          Kernel::Object* ship = createShip(system) ;
//          ship->addTrait(new Transponder(team1)) ;
//          InternalMessage("Model","changing position") ;
//          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,200,-500)) ;
//          InternalMessage("Model","changing orientation") ;
//          ship->getTrait<Oriented>()->setOrientation(::Ogre::Quaternion(::Ogre::Degree(90),::Ogre::Vector3::UNIT_Y)) ;
//          Kernel::Object* agent = createAI(ship) ;
//          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
//        }
//        {
//          // a sitting duck
//          InternalMessage("Model","building ship...") ;
//          Kernel::Object* ship = system->createObject() ;
//          ship->addTrait(new Positionned(Position::Meter(-200,
//                                                         50,
//                                                         -500))) ;
//          ship->addTrait(new Oriented(::Ogre::Quaternion(::Ogre::Degree(90),::Ogre::Vector3::UNIT_Y))) ;
//          ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;
//          ship->addTrait(new Mobile()) ;
//          ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
//          ship->addTrait(new Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;
//
//          Kernel::Object* st1 = ship->createObject() ;
//          st1->addTrait(new Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;
//
//          Kernel::Object* st2 = ship->createObject() ;
//          st2->addTrait(new Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;
//
//          Kernel::Object* st3 = ship->createObject() ;
//          st3->addTrait(new Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;
//
//          InternalMessage("Model","building ship done") ;
//        }
//
//        {
//          InternalMessage("Model","building ship...") ;
//          Kernel::Object* ship = system->createObject() ;
//          ship->addTrait(new Positionned(Position::Meter(200,
//                                                         50,
//                                                         -1000))) ;
//          ship->addTrait(new Oriented(Orientation(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y)))) ;
//
//          ship->addTrait(new Solid(Mesh("test_ship.mesh"))) ;
//          ship->addTrait(new Mobile(Speed::MeterPerSecond(-50,0,0))) ;
//          ship->addTrait(new Massive(Mass::Kilogram(1000))) ;
//          ship->addTrait(new Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;
//
//          Kernel::Object* st1 = ship->createObject() ;
//          st1->addTrait(new Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;
//
//          Kernel::Object* st2 = ship->createObject() ;
//          st2->addTrait(new Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;
//
//          Kernel::Object* st3 = ship->createObject() ;
//          st3->addTrait(new Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;
//
//
//          Kernel::Object* stick = system->createObject() ;
//          stick->addTrait(new Positionned(Position::Meter(0,
//                                                          0,
//                                                          -50))) ;
//          stick->addTrait(new Stick()) ;
//
//          ship->addTrait(new GuidanceSystem(Kernel::Parameters::getValue<float>("Model","GuidanceForce"))) ;
//          ship->addTrait(new GuidanceControler()) ;
//          // stick,ship
//          connectStickControler(stick,ship) ;
//          connectControlerGuidanceSystem(ship,ship) ;
//
//          /// engine + engine control...
//          Kernel::Object* throttle = ship->createObject() ;
//          throttle->addTrait(new Throttle()) ;
//
//          Kernel::Object* engine = ship->createObject() ;
//          engine->addTrait(new Engine(Force::Newton(0,0,Kernel::Parameters::getValue<float>("Model","EngineMaxForce")))) ;
//
//          Kernel::Object* engine_control = ship->createObject() ;
//          engine_control->addTrait(new EngineControler()) ;
//
//          connectThrottleControler(throttle,engine_control) ;
//          connectControlerEngine(engine_control,engine) ;
//
//          Kernel::Object* laser = ship->createObject() ;
//          laser->addTrait(new Laser(Position::Meter(0,0,-120),
//                                          Orientation(),
//                                          Energy::Joule(10))) ;
//          laser->addTrait(new Component()) ;
//
//          ship->addTrait(new Transponder(team2)) ;
//
//        }
        {
          InternalMessage("Model","building ship done") ;

          /// 4. Ajout d'un observateur
          InternalMessage("Model","building observer...") ;
          Kernel::Object* observer = system->createObject() ;
          observer->addTrait(new Positionned(Position::Meter(0,
                                                             0,
                                                             0))) ;

          // targeting system
          Kernel::Object* computer = observer->createObject() ;
          computer->addTrait(new Computer()) ;
          Kernel::Object* detector = observer->createObject() ;
          detector->addTrait(new Detector(computer,Distance(Distance::_Meter,8000))) ;
          Kernel::Object* target_selector = observer->createObject() ;
          target_selector->addTrait(new TargetingSystem()) ;
          TargetingSystem::connect(target_selector,computer) ;

          Kernel::Object* target_display = observer->createObject() ;
          target_display->addTrait(new HeadUpDisplay()) ;
          HeadUpDisplay::connect(target_display,target_selector) ;

          Kernel::Object* laser_observer = observer->createObject() ;
          laser_observer->addTrait(new Laser(Position(),Orientation(),Energy::Joule(10))) ;

          Kernel::Object* shooting_helper = observer->createObject() ;
          shooting_helper->addTrait(new ShootingHelper()) ;
          ShootingHelper::connect(shooting_helper,computer,laser_observer) ;


          observer->addTrait(new Oriented()) ;
          /// Il a la facult d'observer
          observer->addTrait(new Observer()) ;
          observer->addTrait(new Player()) ;
          observer->addTrait(new Active()) ;
          observer->addTrait(new Kernel::CommandDelegator()) ;
//          observer->getTrait<Kernel::CommandDelegator>()->addDelegate(stick) ;
//          observer->getTrait<Kernel::CommandDelegator>()->addDelegate(throttle) ;
//          observer->getTrait<Kernel::CommandDelegator>()->addDelegate(laser) ;
//          observer->getTrait<Kernel::CommandDelegator>()->addDelegate(target_selector) ;

          observer->addTrait(new Transponder(team1)) ;


        }
        InternalMessage("Model","building observer done") ;
      }
      else if (name == "TestPilot")
      {
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;

        Kernel::Object* welcome = root->createObject() ;
        welcome->addTrait(new Image("intro.png")) ;
        welcome->addTrait(new Displayed()) ;
        welcome->addTrait(new State()) ;
        welcome->addTrait(new WithLifetime(Duration::Second(1))) ;
        welcome->getTrait<State>()->setCommandOnQuit("change(main_menu,Displayed)") ;

        Kernel::Object* quit = root->createObject() ;
        quit->setName("quit") ;
        quit->addTrait(new EndOfSimulation()) ;
        quit->addTrait(new State()) ;

        Kernel::Object* main_menu = root->createObject() ;
        main_menu->setName("main_menu") ;
        main_menu->addTrait(new Menu("main_menu.layout")) ;
        main_menu->addTrait(new State()) ;
        main_menu->getTrait<State>()->addCommandAlias("quit","change(quit,Active)") ;
        main_menu->getTrait<State>()->addCommandAlias("play","change(mission,Edited)") ;
        main_menu->getTrait<State>()->addCommandAlias("configure","push(player_configuration,Edited)") ;

        Kernel::Object* player_configuration = createDefaultPlayerConfiguration(main_menu) ;
        player_configuration->setName("player_configuration") ;
        player_configuration->addTrait(new State()) ;

        Kernel::Object* main_menu_in_game = root->createObject() ;
        main_menu_in_game->setName("main_menu_in_game") ;
        main_menu_in_game->addTrait(new Menu("confirm.layout")) ;
        main_menu_in_game->addTrait(new State()) ;
        main_menu_in_game->getTrait<State>()->addCommandAlias("quit","change(main_menu,Displayed)") ;
        main_menu_in_game->getTrait<State>()->addCommandAlias("cancelQuit","pop()") ;

        Kernel::Object* mission = root->createObject() ;
        mission->setName("mission") ;
        mission->addTrait(new State()) ;
        mission->getTrait<Model::State>()->addCommandAlias("quit","change(main_menu,Displayed)") ;

        CustomMission* custom = new CustomMission("basic_mission",player_configuration,main_menu_in_game) ;
        custom->setStartingDistance(Distance(Distance::_Meter,5000)) ;
        mission->addTrait(custom) ;

        Kernel::Object* team1 = mission->createObject() ;
        team1->addTrait(new Team("ally")) ;

        Kernel::Object* fg1 = team1->createObject() ;
        fg1->addTrait(new FlyingGroup("ally")) ;
        fg1->getTrait<FlyingGroup>()->setInitialNumberOfShips(4) ;
        fg1->getTrait<FlyingGroup>()->setHasPlayer(true) ;
        fg1->getTrait<FlyingGroup>()->setShipName("default_ship") ;

        Kernel::Object* team2 = mission->createObject() ;
        team2->addTrait(new Team("enemy")) ;

        Kernel::Object* fg2 = team2->createObject() ;
        fg2->addTrait(new FlyingGroup("enemy")) ;
        fg2->getTrait<FlyingGroup>()->setInitialNumberOfShips(8) ;
        fg2->getTrait<FlyingGroup>()->setNumberOfSpawn(2) ;
        fg2->getTrait<FlyingGroup>()->setShipName("default_ship") ;
        fg2->getTrait<FlyingGroup>()->setHasPlayer(false) ;
      }
      else if (name == "test")
      {
        // create a scene with ships fighting
        const int number_of_ships = (int)Kernel::Parameters::getValue<float>("Test","numberOfShips",5) ;

        Kernel::Object* universe = model->createObject() ;
        universe->addTrait(new Model::State()) ;
        universe->addTrait(new Model::Active()) ;
        universe->addTrait(new Universe()) ;
        universe->addTrait(new Positionned()) ;
        universe->addTrait(new Model::Oriented()) ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new StellarSystem()) ;
        system->addTrait(new Positionned()) ;

        for(int i = 1 ; i <= number_of_ships ; ++i)
        {
          Kernel::Object* team = universe->createObject() ;
          team->addTrait(new Team("team"+Kernel::toString(i))) ;
          Kernel::Object* ship = loadShip("default_ship",system) ;
          ship->addTrait(new Transponder(team)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;

          // Move ship to other place
          Positionned* positionned = ship->getTrait<Positionned>() ;

          Ogre::Quaternion orientation(Ogre::Degree(360/number_of_ships)*(i-1),Ogre::Vector3::UNIT_Z) ;

          Ogre::Vector3 position(orientation*Ogre::Vector3::UNIT_X*2000) ;

          positionned->setPosition(Position::Meter(position.x,position.y,-position.z)) ;
        }

        Kernel::Object* observer = system->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Positionned(Model::Position::Meter(0,0,2500))) ;
        observer->addTrait(new Model::Oriented()) ;
        observer->addTrait(new Model::State()) ;
        observer->getTrait<Model::State>()->addCommandAlias("quit","change(quit,Active)") ;
      }
      else
      {
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getFileReader(findFilePath(name))) ;
        reader->read(model) ;
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
      ship->addTrait(new Massive(Mass::Kilogram(Kernel::Parameters::getValue<float>("Model","ShipMass",1)))) ;
      ship->addTrait(new Mobile()) ;
      ship->addTrait(new Solid(Mesh("default_ship.mesh"))) ;
      ship->addTrait(new Computer()) ;
      ship->addTrait(new Detector(ship,Distance(Distance::_Meter,8000))) ;
      ship->addTrait(new TargetingSystem()) ;
      ship->addTrait(new GuidanceSystem(Kernel::Parameters::getValue<float>("Model","GuidanceForce",3))) ;
      ship->addTrait(new GuidanceControler()) ;
      ship->addTrait(new ShootingHelper()) ;
      ship->addTrait(new Destroyable(Energy::Joule(10))) ;

      Kernel::Object* laser = ship->createObject() ;
      laser->addTrait(new Laser(Position::Meter(0,0,-120),
                                      Orientation(),
                                      Energy::Joule(10))) ;
      laser->addTrait(new Component()) ;
      laser->getTrait<Laser>()->setShotTimeDelay(Duration::Second(1)) ;
      ShootingHelper::connect(ship,ship,laser) ;
      TargetingSystem::connect(ship,ship) ;

      ship->addTrait(new Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient",0.005))) ;
      Kernel::Object* st1 = ship->createObject() ;
      st1->addTrait(new Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce",5),0)) ;
      st1->addTrait(new Component()) ;
      Kernel::Object* st2 = ship->createObject() ;
      st2->addTrait(new Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce",5),0,0)) ;
      st2->addTrait(new Component()) ;
      Kernel::Object* st3 = ship->createObject() ;
      st3->addTrait(new Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce",5))) ;
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
      engine->addTrait(new Engine(Force::Newton(0,0,-Kernel::Parameters::getValue<float>("Model","EngineMaxForce",650)))) ;
      engine->addTrait(new Component()) ;

      Kernel::Object* engine_control = ship->createObject() ;
      engine_control->addTrait(new EngineControler()) ;
      engine_control->addTrait(new Component()) ;

      connectThrottleControler(throttle,engine_control) ;
      connectControlerEngine(engine_control,engine) ;

      return ship ;
    }

    Kernel::Object* loadShip(const std::string& name,Kernel::Object* parent)
    {
      std::string file_path(findFilePath(name+".ship")) ;

      if (!file_path.empty())
      {
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getFileReader(file_path)) ;
        return reader->read(parent) ;
      }

      ErrorMessage("Cannot locate " + name + ".ship") ;
      return NULL ;
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
      // read from config file
      std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getFileReader(findFilePath("player_configuration.xml"))) ;
      return reader->read(parent) ;
    }

    void savePlayerConfiguration(Kernel::Object* configuration)
    {
      // read from config file
      std::auto_ptr<Kernel::XMLWriter> writer(Kernel::XMLWriter::getFileWriter(findFilePath("player_configuration.xml"))) ;
      writer->writeSingleObject(configuration) ;
    }


  }
}


