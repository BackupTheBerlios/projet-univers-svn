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
#include <kernel/model.h>
#include <model/model.h>
#include <model/player_configuration.h>
#include <model/test/test_player_configuration.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Model::Test::TestPlayerConfiguration) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {
        
      void TestPlayerConfiguration::testGetInputEvent()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::testGetInputEvent")) ;
        
        Kernel::Object* configuration = model->createObject() ;
        configuration->addTrait(new Model::PlayerConfiguration()) ;
        configuration->getTrait<Model::PlayerConfiguration>()->addMapping(
            Model::PlayerConfiguration::InputEvent::key(OIS::KC_RETURN),"command") ;

        Model::PlayerConfiguration::InputEvent event = configuration->getTrait<Model::PlayerConfiguration>()->getInputEvent("command") ;
        CPPUNIT_ASSERT(event == Model::PlayerConfiguration::InputEvent::key(OIS::KC_RETURN)) ;
      }
      
      void TestPlayerConfiguration::demoTest()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestPlayerConfiguration::demoTest")) ;
        
        Kernel::Object* option = model->createObject() ;
        Kernel::Object* configuration = Model::createDefaultPlayerConfiguration(option) ;
        
        CPPUNIT_ASSERT(configuration->getTrait<Model::PlayerConfiguration>()->getInputEvent("fire") == 
                       Model::PlayerConfiguration::InputEvent::key(OIS::KC_F)) ;
        CPPUNIT_ASSERT(!(configuration->getTrait<Model::PlayerConfiguration>()->getInputEvent("fire") == 
                         Model::PlayerConfiguration::InputEvent::key(OIS::KC_RETURN))) ;
      }

    }
  }
}
