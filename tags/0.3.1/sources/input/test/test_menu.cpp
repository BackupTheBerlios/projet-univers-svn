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
#include <OIS/OIS.h>

#include <kernel/model.h>
#include <kernel/timer.h>

#include <model/menu.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/observer.h>
#include <model/player.h>

#include <display/implementation/ogre/ogre.h>

#include <input/implementation/input_internal.h>
#include <input/test/test_menu.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Input::
                                Test::
                                TestMenu) ;

namespace ProjetUnivers {
  namespace Input {
    namespace Test {
      
      
      void TestMenu::mouseCursor()
      {
        InternalMessage("Input","Input::TestMenu::mouseCursor entering") ;

        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestMenu::mouseCursor")) ;
        model->init() ;
        
        Kernel::Object* menu = model->createObject() ;
        menu->addTrait(new Model::Menu("Demo7Windows.layout")) ;
        Kernel::Object* observer = model->createObject() ;
        observer->addTrait(new Model::Observer()) ;
        observer->addTrait(new Model::Player()) ;
        observer->addTrait(new Model::Positionned()) ;
        
        Kernel::Timer timer ;
        Kernel::Timer global_timer ;
        
        while (global_timer.getSecond() < 20)
        {
          float seconds = timer.getSecond() ;
          if (seconds != 0)
          {
            timer.reset() ;
          }
          model->update(seconds) ;
        }        
        
        InternalMessage("Input","Input::TestMenu::mouseCursor leaving") ;
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

