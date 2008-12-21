/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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

#include <model/state.h>
#include <model/active.h>
#include <model/mission.h>
#include <model/played.h>
#include <model/with_lifetime.h>
#include <model/implementation/activated_mission.h>
#include <model/test/test_mission.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestMission) ;

namespace ProjetUnivers 
{
  namespace Model 
  {
    namespace Test 
    {

      void TestMission::closeMission()
      {
        InternalMessage("Mission","Model::TestMission::closeMission entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        model->init() ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        root->addTrait(new Active()) ;
        
        Kernel::Object* menu = root->createObject() ;
        menu->addTrait(new State()) ;
        menu->setName("menu") ;
        
        Kernel::Object* game = root->createObject() ;
        game->addTrait(new State()) ;
        game->addTrait(new Mission("",NULL,NULL)) ;
        
        Kernel::Object* player = game->createObject() ;
        player->addTrait(new State()) ;
        
        player->getTrait<State>()->setCommandOnQuit("change(menu,Active)") ;
        player->addTrait(new WithLifetime(Duration::Second(0.1))) ;
        
        root->getTrait<State>()->changeState(game,new Played()) ;

        CPPUNIT_ASSERT(!menu->getTrait<Active>()) ;
        CPPUNIT_ASSERT(game->getTrait<Active>()) ;
        CPPUNIT_ASSERT(game->getTrait<Implementation::ActivatedMission>()) ;
        
        model->update(0.5) ;
        model->update(1) ;

        CPPUNIT_ASSERT(menu->getTrait<Active>()) ;
      }
    }
  }
}
