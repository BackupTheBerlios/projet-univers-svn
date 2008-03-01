/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <math.h>
#include <ode/ode.h>

#include <kernel/parameters.h>
#include <kernel/log.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/model.h>
#include <kernel/controler_set.h>

#include <model/physical_world.h>
#include <model/physical_object.h>
#include <model/model.h>
#include <model/computer.h>
#include <model/massive.h>
#include <model/detector.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/solid.h>
#include <model/laser.h>
#include <model/laser_beam.h>
#include <model/selected.h>
#include <model/detection_data.h>
#include <model/targeting_system.h>
#include <model/ideal_target.h>
#include <model/shooting_helper.h>
#include <model/collision.h>

#include <physic/physic.h>

#include <physic/test/test_shooting_helper.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Physic::Test::TestShootingHelper) ;

namespace ProjetUnivers {
  namespace Physic {
    namespace Test {

      namespace
      {
        /// Acceptable variable for comparison 
        const float delta = 1e-4 ;

        bool equal(float i1,float i2)
        {
          return (fabs(i1 - i2) <= delta) ;
        }
        
      }

      void TestShootingHelper::basicTest()
      {
        InternalMessage("Physic","Physic::Test::TestShootingHelper::basicTest Entering") ;
        /*! 
          we construct a complete system :
          a main ship 
          a ship for detection
          
          we select a target and check the property of the ideal target 
        */
        Model::init() ;

        Kernel::Object* system = Model::createObject("system") ;
        CPPUNIT_ASSERT(system->getTrait<Model::PhysicalWorld>()) ;

        Kernel::Object* ship = Model::createObject("ship",system) ;
        Model::addTrait(ship,new Model::Positionned()) ;
        Model::addTrait(ship,new Model::Oriented()) ;
        Model::addTrait(ship,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship,new Model::Mobile()) ;
        Model::addTrait(ship,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        Model::addTrait(ship,new Model::Computer()) ;
        Model::addTrait(ship,new Model::Laser(Model::Position::Meter(19.2,0,35),Model::Orientation())) ;
        Model::addTrait(ship,new Model::Detector(ship)) ;
        Model::addTrait(ship,new Model::TargetingSystem()) ;
        Model::TargetingSystem::connect(ship,ship) ;
        Model::addTrait(ship,new Model::ShootingHelper()) ;
        Model::ShootingHelper::connect(ship,ship,ship) ;
        
        Kernel::Object* ship2 = Model::createObject("ship2",system) ;
        Model::addTrait(ship2,new Model::Positionned(Model::Position::Meter(0,0,300))) ;
        Model::addTrait(ship2,new Model::Massive(Model::Mass::Kilogram(1000))) ;
        Model::addTrait(ship2,new Model::Oriented()) ;
        Model::addTrait(ship2,new Model::Mobile(Model::Speed::MeterPerSecond(0,10,0))) ;
        Model::addTrait(ship2,new Model::Solid(Model::Mesh("razor.mesh"))) ;
        
        // for detection
        Model::update(Model::Duration::Second(0.1)) ;

        CPPUNIT_ASSERT(ship->getTrait<Model::Computer>()->getMemoryModel()->getRoots().size() == 1) ;
        
        std::set<Kernel::Object*>::const_iterator data_pointer 
          = ship->getTrait<Model::Computer>()->getMemoryModel()->getRoots().begin() ; 
        ship->getTrait<Model::TargetingSystem>()->selectNextTarget() ;

        Kernel::Object* data = *(data_pointer) ;
        CPPUNIT_ASSERT(data->getTrait<Model::Selected>()) ;
        
        // get the ideal target data and check it
        std::set<Model::IdealTarget*> children = data->getDescendants<Model::IdealTarget>() ; 
        
        CPPUNIT_ASSERT(children.size()==1) ;
        Kernel::Object* child = (*(children.begin()))->getObject() ;
        Model::Positionned* positionned = child->getTrait<Model::Positionned>() ;
        CPPUNIT_ASSERT(positionned) ;
        
        /// build a physical viewpoint        
        Physic::init() ;
        Kernel::ControlerSet* physics = Physic::build(ship) ;

        // calculate orientation of laser from positionned and laser out position
        // we should also use laser relative position to the ship if existed
        ::Ogre::Quaternion quaternion(
              ::Ogre::Degree(0),
              (positionned->getPosition() - ship->getTrait<Model::Laser>()->getOutPosition()).Meter()) ;
        
        ship->getTrait<Model::Laser>()->setOrientation(Model::Orientation(quaternion)) ;
        
        ship->getTrait<Model::Laser>()->fire() ;
        
        /// simulation during enought time seconds ...
        const int steps_number = 200 ; 
        for(int i = 1 ; i <= steps_number ; ++i)
        {
          Physic::update(Model::Duration::Second(0.1)) ;
        }
        
        /// check that collision has occured
        std::set<Model::Collision*> collisions = system->getDescendants<Model::Collision>() ;
        CPPUNIT_ASSERT(collisions.size()!=0) ;
        
        Model::Collision* collision = *(collisions.begin()) ;

        /// check that collided objects are ship2 and the laser beam !
        CPPUNIT_ASSERT(collision->getObject1()->getTrait<Model::LaserBeam>() || 
                       collision->getObject2()->getTrait<Model::LaserBeam>()) ;
        CPPUNIT_ASSERT(collision->getObject1() == ship2 || collision->getObject2() == ship2) ;
        
        Physic::close() ;

        InternalMessage("Physic","Physic::Test::TestShootingHelper::basicTest leaving") ;
        
      }

      void TestShootingHelper::setUp() 
      {
        Kernel::Parameters::load("demonstration.config") ;
      }
      
      void TestShootingHelper::tearDown() 
      {
      }

    }
  }
}
