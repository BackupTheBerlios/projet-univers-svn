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
#include <iostream>
#include <kernel/model.h>
#include <kernel/timer.h>
#include <kernel/parameters.h>

#include <model/model.h>
#include <model/menu.h>
#include <model/oriented.h>
#include <model/observer.h>
#include <model/displayed.h>
#include <model/edited.h>
#include <model/player.h>
#include <model/player_configuration.h>
#include <model/positionned.h>
#include <model/displayed.h>

#include <display/implementation/ogre/ogre.h>

#include <input/input_gui.h>
#include <input/implementation/input_internal.h>
#include <gui/test/test_menu.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                GUI::
                                Test::
                                TestMenu) ;

namespace ProjetUnivers {
  namespace GUI {
    namespace Test {
      
      
      void TestMenu::basicTest()
      {
        InternalMessage("GUI","GUI::TestMenu::basicTest entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestMenu::basicTest")) ;
        model->init() ;

        std::string menu_name ;
        
        menu_name = Kernel::Parameters::getValue<std::string>("GUI","Test.BasicTest.Name","main_menu.layout") ; 
        
        Kernel::Object* menu = model->createObject() ;
        menu->addTrait(new Model::Menu(menu_name)) ;
        menu->addTrait(new Model::Displayed()) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        float test_duration = 0 ;
        
        test_duration = Kernel::Parameters::getValue<float>("GUI","Test.BasicTest.Duration",5) ; 
        
        while (global_timer.getSecond() < test_duration)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("GUI","GUI::TestMenu::mouseCursor leaving") ;
      }

      void TestMenu::playerConfiguration()
      {
        InternalMessage("GUI","GUI::TestMenu::playerConfiguration entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestMenu::playerConfiguration")) ;
        model->init() ;
        
        Kernel::Object* option = model->createObject() ;
        Kernel::Object* configuration = Model::createDefaultPlayerConfiguration(option) ;
        configuration->addTrait(new Model::Edited()) ;

//        std::set<std::string> commands(Kernel::Trait::getRegisteredCommands()) ;
//        
//        for(std::set<std::string>::const_iterator command = commands.begin() ;
//            command != commands.end() ;
//            ++command)
//        {
//          std::cout << *command << "=" 
//                    << configuration->getTrait<Model::PlayerConfiguration>()->getInputEvent(*command).toString(Input::getOISKeyboard())
//                    << std::endl ;
//        }
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        float test_duration = 0 ;
        
        try 
        {
          test_duration = Kernel::Parameters::getValue<float>("GUI","Test.PlayerConfiguration.Duration") ; 
        }
        catch(...)
        {
          test_duration = 5 ;
        }
        
        while (global_timer.getSecond() < test_duration)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("GUI","GUI::TestMenu::playerConfiguration leaving") ;
      }
      
      void TestMenu::setUp() 
      {
      }
      
      void TestMenu::tearDown() 
      {
      }

    }
  }
}

