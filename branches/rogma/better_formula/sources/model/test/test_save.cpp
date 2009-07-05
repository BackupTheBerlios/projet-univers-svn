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
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/parameters.h>
#include <kernel/xml_writer.h>

#include <model/player_configuration.h>

#include <model/test/test_save.h>

namespace ProjetUnivers 
{
  namespace Model 
  {
    namespace Test 
    {
      CPPUNIT_TEST_SUITE_REGISTRATION(TestSave) ;
      
      void TestSave::saveKeyPlayerConfiguration()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestSave::saveKeyPlayerConfiguration")) ;
        std::auto_ptr<Kernel::XMLWriter> writer(Kernel::XMLWriter::getStringWriter()) ;
        
        Kernel::Object* player_configuration = model->createObject() ;
        player_configuration->addTrait(new Model::PlayerConfiguration()) ;
        player_configuration->getTrait<PlayerConfiguration>()->addMapping(PlayerConfiguration::InputEvent::key(10),"toto") ;
        writer->writeSingleObject(player_configuration) ;

        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model>"
                                           "<object id=\"0\">"
                                             "<PlayerConfiguration>"
                                               "<Mapping command=\"toto\">"
                                                 "<Key number=\"10\"/>"
                                               "</Mapping>"
                                             "</PlayerConfiguration>"
                                           "</object>"
                                         "</model>\n"),
                             writer->getContent()) ;
        
      }

      void TestSave::saveMouseButtonPlayerConfiguration()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestSave::saveMouseButtonPlayerConfiguration")) ;
        std::auto_ptr<Kernel::XMLWriter> writer(Kernel::XMLWriter::getStringWriter()) ;
        
        Kernel::Object* player_configuration = model->createObject() ;
        player_configuration->addTrait(new Model::PlayerConfiguration()) ;
        player_configuration->getTrait<PlayerConfiguration>()->addMapping(PlayerConfiguration::InputEvent::mouseButton(10),"toto") ;
        writer->writeSingleObject(player_configuration) ;

        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model>"
                                           "<object id=\"0\">"
                                             "<PlayerConfiguration>"
                                               "<Mapping command=\"toto\">"
                                                 "<MouseButton number=\"10\"/>"
                                               "</Mapping>"
                                             "</PlayerConfiguration>"
                                           "</object>"
                                         "</model>\n"),
                             writer->getContent()) ;
        
      }

      void TestSave::saveJoystickButtonPlayerConfiguration()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestSave::saveJoystickButtonPlayerConfiguration")) ;
        std::auto_ptr<Kernel::XMLWriter> writer(Kernel::XMLWriter::getStringWriter()) ;
        
        Kernel::Object* player_configuration = model->createObject() ;
        player_configuration->addTrait(new Model::PlayerConfiguration()) ;
        player_configuration->getTrait<PlayerConfiguration>()->addMapping(PlayerConfiguration::InputEvent::joystickButton(10),"toto") ;
        writer->writeSingleObject(player_configuration) ;

        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model>"
                                           "<object id=\"0\">"
                                             "<PlayerConfiguration>"
                                               "<Mapping command=\"toto\">"
                                                 "<JoystickButton number=\"10\"/>"
                                               "</Mapping>"
                                             "</PlayerConfiguration>"
                                           "</object>"
                                         "</model>\n"),
                             writer->getContent()) ;
        
      }
      
      void TestSave::saveJoystickAxes()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestSave::saveJoystickButtonPlayerConfiguration")) ;
        std::auto_ptr<Kernel::XMLWriter> writer(Kernel::XMLWriter::getStringWriter()) ;
        
        Kernel::Object* player_configuration = model->createObject() ;
        player_configuration->addTrait(new Model::PlayerConfiguration()) ;
        player_configuration->getTrait<PlayerConfiguration>()->addMapping(PlayerConfiguration::InputAxis(PlayerConfiguration::InputAxis::JoystickRudder),"rudder") ;
        player_configuration->getTrait<PlayerConfiguration>()->addMapping(PlayerConfiguration::InputAxis(-PlayerConfiguration::InputAxis::JoystickRudder),"inverted_rudder") ;
        player_configuration->getTrait<PlayerConfiguration>()->addMapping(PlayerConfiguration::InputAxis(PlayerConfiguration::InputAxis::MouseX),"mousex") ;
        writer->writeSingleObject(player_configuration) ;

        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model>"
                                           "<object id=\"0\">"
                                             "<PlayerConfiguration>"
                                               "<Mapping command=\"inverted_rudder\">"
                                                 "<InvertedJoystickRudder/>"
                                               "</Mapping>"
                                               "<Mapping command=\"mousex\">"
                                                 "<MouseX/>"
                                               "</Mapping>"
                                               "<Mapping command=\"rudder\">"
                                                 "<JoystickRudder/>"
                                               "</Mapping>"
                                             "</PlayerConfiguration>"
                                           "</object>"
                                         "</model>\n"),
                             writer->getContent()) ;
      }
      
    }
  }
}
