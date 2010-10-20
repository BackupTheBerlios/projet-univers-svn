/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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
#include <iostream>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/timer.h>
#include <kernel/parameters.h>
#include <kernel/command_delegator.h>

#include <model/model.h>
#include <model/positioned.h>
#include <model/stellar_system.h>
#include <model/oriented.h>
#include <model/observer.h>
#include <model/displayed.h>
#include <model/universe.h>
#include <model/mobile.h>
#include <model/player.h>
#include <model/head_up_display.h>
#include <model/targeting_system.h>
#include <model/computer.h>
#include <model/ideal_target.h>
#include <model/image.h>
#include <model/destroyable.h>
#include <model/solid.h>
#include <model/active.h>
#include <model/detector.h>
#include <model/team.h>
#include <model/transponder.h>
#include <model/custom_mission.h>
#include <model/flying_group.h>
#include <model/state.h>
#include <model/mission.h>
#include <model/played.h>
#include <model/sized.h>
#include <model/selection.h>
#include <model/hit.h>

#include <display/display.h>
#include <display/implementation/target.h>
#include <display/implementation/ogre/ogre.h>
#include <display/implementation/space_dust.h>
#include <display/implementation/positioned.h>
#include <display/implementation/ogre/real_world_view_point.h>
#include <display/implementation/ogre/head_up_display.h>
#include <display/implementation/ogre/positioned.h>
#include <display/test/performance/test_effect.h>
#include <model/laser.h>


namespace ProjetUnivers
{
  namespace Display
  {
    namespace Test
    {
      namespace Performance
      {

        CPPUNIT_TEST_SUITE_REGISTRATION(TestEffect) ;

        Kernel::Object* TestEffect::createUniverseAndSystem(Kernel::Model* model) const
        {
          Kernel::Object* universe = model->createObject() ;
          universe->addTrait(new Model::Universe()) ;
          universe->addTrait(new Model::Positioned()) ;

          Kernel::Object* system = universe->createObject() ;
          system->addTrait(new Model::StellarSystem()) ;
          system->addTrait(new Model::Positioned()) ;

          return system ;
        }

        Kernel::Object* TestEffect::createObserver(Kernel::Object* parent) const
        {
          Kernel::Object* observer = parent->createObject() ;
          observer->addTrait(new Model::Observer()) ;
          observer->getTrait<Model::Observer>()->setFieldOfView(::Ogre::Degree(70)) ;
          observer->addTrait(new Model::Player()) ;
          observer->addTrait(new Model::Active()) ;
          observer->addTrait(new Model::Positioned()) ;
          observer->addTrait(new Model::Oriented()) ;

          return observer ;
        }

        void TestEffect::simulate(Kernel::Model* model,const float& seconds)
        {
          Kernel::Timer timer ;
          Kernel::Timer global_timer ;

          while (global_timer.getSecond() < seconds)
          {
            float seconds = timer.getSecond() ;
            if (seconds != 0)
            {
              timer.reset() ;
            }
            model->update(seconds) ;
          }
        }

        void TestEffect::particle()
        {
          std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
          model->init() ;

          Implementation::Ogre::RealWorldViewPoint* viewpoint =
            model->getViewPoint<Implementation::Ogre::RealWorldViewPoint>() ;

          Kernel::Object* system = createUniverseAndSystem(model.get()) ;
          Kernel::Object* observer = createObserver(system) ;
          Kernel::Object* ship = Model::createShip(system) ;

          Implementation::Ogre::Positioned* positioned = ship->getTrait<Implementation::Positioned>()->getView<Implementation::Ogre::Positioned>(viewpoint) ;
          CPPUNIT_ASSERT(positioned) ;

          const int explosion_number = 100 ;
          float circle_radius = explosion_number * 0.03 ;

          ship->getTrait<Model::Positioned>()->setPosition(Model::Position::Meter(0,0,-explosion_number*40)) ;

          // make a loop,  put nodes on a circle 0.5 radius
          for (int i = 1 ; i <= explosion_number ; ++i)
          {
            Ogre::Quaternion orientation(Ogre::Degree(360/explosion_number)*(i-1),Ogre::Vector3::UNIT_Z) ;
            Ogre::Vector3 position(orientation*Ogre::Vector3::UNIT_X*circle_radius) ;

            ::Ogre::SceneNode* effect = positioned->getNode()->createChildSceneNode(position) ;
            Implementation::Ogre::createAnimatedBillboard(effect,
                                                          "PU/explosion/explosion",
                                                          Model::Duration::Second(2),
                                                          Model::Distance(Model::Distance::_Meter,150)) ;
          }

          Kernel::Timer timer ;
          Kernel::Timer global_timer ;

          for(int i = 1 ; i <= 100 ; ++i)
            simulate(model.get(),0.1) ;

          // @todo check something...
        }

      }
    }
  }
}
