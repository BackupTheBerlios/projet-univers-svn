/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/timer.h>
#include <kernel/log.h>

#include <model/model.h>
#include <model/universe.h>
#include <model/positionned.h>
#include <model/stellar_system.h>
#include <model/listener.h>
#include <model/oriented.h>
#include <model/observer.h>
#include <model/active.h>
#include <model/player.h>
#include <model/mobile.h>
#include <model/throttle.h>

#include <sound/test/test_demonstration.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Sound::Test::TestDemonstration);

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Test
    {

      void TestDemonstration::oneShip()
      {
        InternalMessage("Sound","entering TestDemonstration::oneShip") ;
        std::cerr << "TestDemonstration::oneShip" << std::endl ;
        std::cerr.flush() ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        
        Kernel::Object* root = model->createObject() ;
        
        Kernel::Object* universe = root->createObject() ;
        universe->addTrait(new Model::Universe()) ;
        universe->addTrait(new Model::Positionned()) ;
        universe->setName("universe") ;

        Kernel::Object* system = universe->createObject() ;
        system->addTrait(new Model::StellarSystem()) ;
        system->addTrait(new Model::Positionned()) ;
        system->setName("system") ;
        
//        Kernel::Object* ship = Model::loadShip("razor",system) ;
        
        Kernel::Object* pilot = system->createObject() ;
        pilot->addTrait(new Model::Listener()) ;
        pilot->addTrait(new Model::Positionned()) ;
        pilot->addTrait(new Model::Oriented()) ;
        pilot->addTrait(new Model::Player()) ;
        pilot->addTrait(new Model::Observer()) ;
        pilot->addTrait(new Model::Active()) ;

        Kernel::Object* ship2 = Model::loadShip("razor",system) ;
        
        Model::Positionned* ship2_positionned = ship2->getTrait<Model::Positionned>() ; 
        ship2_positionned->setPosition(Model::Position::Meter(0,0,200)) ;
        ship2->getTrait<Model::Mobile>()->setSpeed(Model::Speed::MeterPerSecond(0,0,-50)) ;
        Kernel::Timer global_timer ;
        Kernel::Timer timer ;

        std::set<Model::Throttle*> throttles = ship2->getChildren<Model::Throttle>() ;
        
        (*throttles.begin())->set(100) ;
        
        while (global_timer.getSecond() <= 4)
        {
          float seconds = timer.getSecond() ;
          if (seconds > 0)
          {
            timer.reset() ;
            ship2_positionned->setPosition(ship2_positionned->getPosition()+Model::Position::Meter(0,0,-50*seconds)) ;
            model->update(seconds) ;
          }
        }
        InternalMessage("Sound","leaving TestDemonstration::oneShip") ;
      }

    }
  }
}

