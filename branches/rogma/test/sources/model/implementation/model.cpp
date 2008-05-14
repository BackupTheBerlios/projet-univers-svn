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

#include <model/model.h>


using namespace Ogre ;

namespace ProjetUnivers {
  namespace Model 
  {

  /*!
    @name Module data.
  */
  // @{
    
    /// our real world.
    std::auto_ptr<Kernel::Model> model(new Kernel::Model("real world")) ;    
    
    /// for ogre mesh loading     
    LogManager*                   log_manager ;
    DefaultHardwareBufferManager* hardware_buffer_manager ;
    Root*                         root ;

  // @}
    

    Kernel::Object* getObject(const std::string& i_name)
    {
      return model->getObject(i_name) ;
    }
      
    Kernel::Object* createObject(const std::string& i_name)
    {
      return model->createObject(i_name) ;
    }

    Kernel::Object* createObject()
    {
      return model->createObject() ;
    }
    
    Kernel::Object* createObject(const std::string& i_name, 
                                 Kernel::Object* i_parent)
    {
      return model->createObject(i_name,i_parent) ;
    } 

    Kernel::Object* createObject(Kernel::Object* i_parent)
    {
      return model->createObject(i_parent) ;
    } 

    void destroyObject(const std::string& i_name)
    {
      model->destroyObject(i_name) ;
    }
    
    void destroyObject(Kernel::Object* i_object)
    {
      model->destroyObject(i_object) ;
    }

    void changeParent(Kernel::Object* i_object, 
                      Kernel::Object* i_new_parent)
    {
      model->changeParent(i_object,i_new_parent) ;
    }

    void addTrait(Kernel::Object* i_object, 
                  Kernel::Trait* i_new_trait) 
    {
      model->addTrait(i_object,i_new_trait) ;
    }

    void destroyTrait(Kernel::Object* i_object, 
                      Kernel::Trait* i_trait) 
    {
      model->destroyTrait(i_object,i_trait) ;
    }
    
    void init()
    {
      model.reset(new Kernel::Model("real world")) ;
      
      Implementation::Logic::build(model.get()) ;
      Implementation::Logic::init() ;
    }

    void close()
    {
      InternalMessage("Model","Deleting objects") ;
      model.reset() ;    
      Implementation::Logic::close() ;
      InternalMessage("Model","Module Model terminated") ;
      
    }

    /*!
      @par Status 
        hard coded
    */
    void load(const std::string& name)
    {
     
      if (name == "TestDemonstration")
      {
        /// 1. Construction d'un univers
        InternalMessage("Model","building Universe...") ;
        Kernel::Object* universe = model->createObject("Univers") ;
        
        /// ses facettes
        model->addTrait(universe,new Universe()) ;
        model->addTrait(universe,new Positionned()) ;
        
        InternalMessage("Model","construction de Univers terminée") ;

        /// 1.4 Une galaxie
        
        /// 1.5 Un système stellaire
        InternalMessage("Model","building stellar system...") ;
        Kernel::Object* system = model->createObject("Systeme#1",universe) ;
        model->addTrait(system,new StellarSystem()) ;
        model->addTrait(system,new Positionned()) ;
        InternalMessage("Model","building stellar system done") ;
        
        
        /// 2. Ajout d'objects planetes
        InternalMessage("Model","building planet...") ;
        Kernel::Object* planet1 = model->createObject("Planete#1",system) ;
        model->addTrait(planet1,new Positionned()) ;
        InternalMessage("Model","building planet done") ;

        // 2 teams
        Kernel::Object* team1 = model->createObject() ;
        model->addTrait(team1,new Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        model->addTrait(team2,new Team("team2")) ;
        
        
        /// 3. Ajout d'un vaisseau
        {
          InternalMessage("Model","building ship...") ;
                    
          Kernel::Object* ship = createShip(system) ;
          model->addTrait(ship,new Transponder(team1)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,200,-500)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
          
          InternalMessage("Model","building ship done") ;
        }
        {
          InternalMessage("Model","building ship...") ;
          Kernel::Object* ship = model->createObject(system) ;
          model->addTrait(ship,new Positionned(Position::Meter(-200,
                                                               50,
                                                               -500))) ;
          model->addTrait(ship,new Oriented()) ;
          model->addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
          model->addTrait(ship,new Mobile()) ;
          model->addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
          model->addTrait(ship,new Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;

          Kernel::Object* st1 = model->createObject(ship) ;
          model->addTrait(st1,new Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;

          Kernel::Object* st2 = model->createObject(ship) ;
          model->addTrait(st2,new Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;

          Kernel::Object* st3 = model->createObject(ship) ;
          model->addTrait(st3,new Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;

          InternalMessage("Model","building ship done") ;
        }

        {
          InternalMessage("Model","building ship...") ;
          Kernel::Object* ship = model->createObject("Vaisseau#3",system) ;
          model->addTrait(ship,new Positionned(Position::Meter(200,
                                                               50,
                                                               -1000))) ;
          model->addTrait(ship,new Oriented()) ;
          
          model->addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
          model->addTrait(ship,new Mobile()) ;
          model->addTrait(ship,new Massive(Mass::Kilogram(1000))) ;
          model->addTrait(ship,new Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;

          Kernel::Object* st1 = model->createObject("st1",ship) ;
          model->addTrait(st1,new Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;

          Kernel::Object* st2 = model->createObject("st2",ship) ;
          model->addTrait(st2,new Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;

          Kernel::Object* st3 = model->createObject("st3",ship) ;
          model->addTrait(st3,new Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;


          Kernel::Object* stick = model->createObject("stick",system) ;
          model->addTrait(stick,new Positionned(Position::Meter(0,
                                                                0,
                                                                -50))) ;
          model->addTrait(stick,new Stick()) ;
          
          model->addTrait(ship,new GuidanceSystem(Kernel::Parameters::getValue<float>("Model","GuidanceForce"))) ;
          model->addTrait(ship,new GuidanceControler()) ;
          // stick,ship
          connectStickControler(stick,ship) ;
          connectControlerGuidanceSystem(ship,ship) ;
          
          /// engine + engine control...
          Kernel::Object* throttle = model->createObject("throttle",ship) ;
          model->addTrait(throttle,new Throttle()) ;
          
          Kernel::Object* engine = model->createObject("engine",ship) ;
          model->addTrait(engine,new Engine(Force::Newton(0,0,Kernel::Parameters::getValue<float>("Model","EngineMaxForce")))) ;
  
          Kernel::Object* engine_control = model->createObject("engine_control",ship) ;
          model->addTrait(engine_control,new EngineControler()) ;

          connectThrottleControler(throttle,engine_control) ;
          connectControlerEngine(engine_control,engine) ;                   
          
          Kernel::Object* laser = model->createObject("laser",ship) ;
          model->addTrait(laser,new Laser(Position::Meter(19.2,0,57),
                                          Orientation(),
                                          Energy::Joule(10))) ;
          model->addTrait(laser, new Component()) ;
          
          model->addTrait(ship,new Transponder(team2)) ;
          model->addTrait(ship,new Destroyable(Energy::Joule(10))) ;
          
          
          InternalMessage("Model","building ship done") ;
        }
        {
          /// 4. Ajout d'un observateur
          InternalMessage("Model","building observer...") ;
          
          Kernel::Object* ship = createShip(system) ;
          ship->getTrait<Oriented>()->setOrientation(Orientation(Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y))) ;
                    
          Kernel::Object* observer = model->createObject("Observer",ship) ;
          model->addTrait(observer,new Positionned()) ;
//          model->addTrait(observer,new Oriented(Orientation(Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y)))) ;
          model->addTrait(observer,new Oriented()) ;
          // targeting system
          Kernel::Object* computer = model->createObject("computer",observer) ;
          model->addTrait(computer,new Computer()) ;
          
          Kernel::Object* detector = model->createObject("detector",observer) ;
          model->addTrait(detector,new Detector(computer,Distance(Distance::_Meter,8000))) ;
          
          Kernel::Object* target_selector = model->createObject("target_selector",observer) ;
          model->addTrait(target_selector,new TargetingSystem()) ;
          TargetingSystem::connect(target_selector,computer) ;
          
          Kernel::Object* target_display = model->createObject("target_display",observer) ;
          model->addTrait(target_display,new TargetDisplayer()) ;
          TargetDisplayer::connect(target_display,target_selector) ;

          Kernel::Object* laser_observer = model->createObject(observer) ;
          model->addTrait(laser_observer,new Laser(Position(),Orientation(),Energy::Joule(10))) ;

          Kernel::Object* shooting_helper = model->createObject("shooting_helper",observer) ;
          model->addTrait(shooting_helper,new ShootingHelper()) ;
          ShootingHelper::connect(shooting_helper,computer,laser_observer) ;
          
          /// Il a la faculté d'observer
          model->addTrait(observer,new Observer()) ;
//          model->addTrait(observer,new Kernel::CommandDelegator()) ;
//          observer->getTrait<Kernel::CommandDelegator>()->addDelegate(stick) ;
//          observer->getTrait<Kernel::CommandDelegator>()->addDelegate(throttle) ;
//          observer->getTrait<Kernel::CommandDelegator>()->addDelegate(laser) ;
//          observer->getTrait<Kernel::CommandDelegator>()->addDelegate(target_selector) ;
          
          model->addTrait(observer, new Transponder(team1)) ;
          

        }
        InternalMessage("Model","building observer done") ;
      }
      else if (name == "TestMenu")
      {
        Kernel::Object* universe = model->createObject("Univers") ;
        
        /// ses facettes
        model->addTrait(universe,new Menu("ProjetUnivers.layout")) ;
        model->addTrait(universe,new Universe()) ;
        model->addTrait(universe,new Positionned()) ;

        Kernel::Object* ship = model->createObject("Vaisseau",universe) ;
        model->addTrait(ship,new Positionned(Position::Meter(0,
                                                             0,
                                                             -500))) ;
        model->addTrait(ship,new Oriented()) ;
        model->addTrait(ship,new Solid(Mesh("razor.mesh"))) ;

        /// 4. Ajout d'un observateur
        InternalMessage("Model","building observer...") ;
        Kernel::Object* observer = model->createObject("Observer",universe) ;
        model->addTrait(observer,new Positionned()) ;
        model->addTrait(observer,new Oriented()) ;
        model->addTrait(observer,new Observer()) ;
      }
      else if (name == "TestPilot")
      {
        Kernel::Object* universe = model->createObject() ;
        model->addTrait(universe,new Universe()) ;
        model->addTrait(universe,new Positionned()) ;

        Kernel::Object* system = model->createObject(universe) ;
        model->addTrait(system,new StellarSystem()) ;
        model->addTrait(system,new Positionned()) ;

        // 2 teams
        Kernel::Object* team1 = model->createObject() ;
        model->addTrait(team1,new Team("team1")) ;
        Kernel::Object* team2 = model->createObject() ;
        model->addTrait(team2,new Team("team2")) ;

        {
          Kernel::Object* ship = createShip(system) ;
          model->addTrait(ship,new Transponder(team1)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,0,0)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }
//        {
//          Kernel::Object* ship = createShip(system) ;
//          model->addTrait(ship,new Transponder(team1)) ;
//          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,500,0)) ;
//          Kernel::Object* agent = createAI(ship) ;
//          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
//        }

        {
          Kernel::Object* ship = createShip(system) ;
          model->addTrait(ship,new Transponder(team2)) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,0,1100)) ;
          Kernel::Object* agent = createAI(ship) ;
          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
        }
//        {
//          Kernel::Object* ship = createShip(system) ;
//          model->addTrait(ship,new Transponder(team2)) ;
//          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,0,3000)) ;
//          Kernel::Object* agent = createAI(ship) ;
//          agent->getTrait<WithObjectives>()->addObjective(Objective::attackAllEnemies()) ;
//        }
        
        {
          Kernel::Object* ship = createShip(system) ;
          model->addTrait(ship,new Transponder(team1)) ;
          model->addTrait(ship,new TargetDisplayer()) ;
          TargetDisplayer::connect(ship,ship) ;
          ship->getTrait<Positionned>()->setPosition(Position::Meter(0,-500,0)) ;
//          ship->getTrait<Oriented>()->setOrientation(Orientation(Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y))) ;
          
          Kernel::Object* player = model->createObject("Observer",ship) ;
          model->addTrait(player,new Positionned()) ;
          model->addTrait(player,new Oriented()) ;
          model->addTrait(player,new Observer()) ;
          model->addTrait(player,new Kernel::CommandDelegator()) ;
          player->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;
        }
      }
      else
      {
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getFileReader(name)) ;
        reader->read(model.get()) ;
      }            
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
    }
    
    void update(const Duration& duration)
    {
      Implementation::Logic::update(duration) ;
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
      
      Kernel::Model* model = parent->getModel() ;
      
      Kernel::Object* ship = model->createObject(parent) ;
      model->addTrait(ship,new Positionned()) ;
      model->addTrait(ship,new Oriented()) ;
      model->addTrait(ship,new Massive(Mass::Kilogram(Kernel::Parameters::getValue<float>("Model","ShipMass")))) ;
      model->addTrait(ship,new Mobile()) ;
      model->addTrait(ship,new Solid(Mesh("razor.mesh"))) ;
      model->addTrait(ship,new Computer()) ;
      model->addTrait(ship,new Detector(ship,Distance(Distance::_Meter,8000))) ;
      model->addTrait(ship,new TargetingSystem()) ;
      model->addTrait(ship,new GuidanceSystem(Kernel::Parameters::getValue<float>("Model","GuidanceForce"))) ;
      model->addTrait(ship,new GuidanceControler()) ;
      model->addTrait(ship,new ShootingHelper()) ;
      model->addTrait(ship,new Destroyable(Energy::Joule(10))) ;

      Kernel::Object* laser = model->createObject(ship) ;
      model->addTrait(laser,new Laser(Position::Meter(19.2,0,57),
                                      Orientation(),
                                      Energy::Joule(10))) ;
      model->addTrait(laser, new Component()) ;
      laser->getTrait<Laser>()->setShotTimeDelay(Duration::Second(1)) ;
      ShootingHelper::connect(ship,ship,laser) ;
      TargetingSystem::connect(ship,ship) ;
      
      model->addTrait(ship,new Dragger(Kernel::Parameters::getValue<float>("Model","DraggerCoeeficient"))) ;
      Kernel::Object* st1 = model->createObject(ship) ;
      model->addTrait(st1,new Stabilizer(0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0)) ;
      model->addTrait(st1,new Component()) ;
      Kernel::Object* st2 = model->createObject(ship) ;
      model->addTrait(st2,new Stabilizer(Kernel::Parameters::getValue<float>("Model","StabilizerForce"),0,0)) ;
      model->addTrait(st2,new Component()) ;
      Kernel::Object* st3 = model->createObject(ship) ;
      model->addTrait(st3,new Stabilizer(0,0,Kernel::Parameters::getValue<float>("Model","StabilizerForce"))) ;
      model->addTrait(st3,new Component()) ;

      Kernel::Object* stick = model->createObject(ship) ;
      model->addTrait(stick,new Positionned()) ;
      model->addTrait(stick,new Stick()) ;
      model->addTrait(stick,new Component()) ;
      
      // stick,ship
      connectStickControler(stick,ship) ;
      connectControlerGuidanceSystem(ship,ship) ;
      
      /// engine + engine control...
      Kernel::Object* throttle = model->createObject(ship) ;
      model->addTrait(throttle,new Throttle()) ;
      model->addTrait(throttle,new Positionned()) ;
      model->addTrait(throttle,new Component()) ;
      
      Kernel::Object* engine = model->createObject(ship) ;
      model->addTrait(engine,new Engine(Force::Newton(0,0,Kernel::Parameters::getValue<float>("Model","EngineMaxForce")))) ;
      model->addTrait(engine,new Component()) ;
      
      Kernel::Object* engine_control = model->createObject(ship) ;
      model->addTrait(engine_control,new EngineControler()) ;
      model->addTrait(engine_control,new Component()) ;

      connectThrottleControler(throttle,engine_control) ;
      connectControlerEngine(engine_control,engine) ;                   
      
      return ship ;
    }
    
    Kernel::Object* createAI(Kernel::Object* ship)
    {
      Kernel::Object* agent = model->createObject(ship) ;
      model->addTrait(agent,new AutonomousCharacter()) ;
      model->addTrait(agent,new WithObjectives()) ;
      model->addTrait(agent,new Kernel::CommandDelegator()) ;
      agent->getTrait<Kernel::CommandDelegator>()->addDelegate(ship) ;

      return agent ;
    }
    
  }
}


