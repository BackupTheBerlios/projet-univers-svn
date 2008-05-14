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
#include <kernel/xml_reader.h>

#include <model/component.h>
#include <model/computer.h>
#include <model/destroyable.h>
#include <model/detector.h>
#include <model/dragger.h>
#include <model/engine.h>
#include <model/engine_controler.h>
#include <model/throttle.h>
#include <model/force_generator.h>
#include <model/hearing.h>
#include <model/guidance_controler.h>
#include <model/guidance_system.h>
#include <model/laser.h>
#include <model/menu.h>
#include <model/observer.h>
#include <model/positionned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/solid.h>
#include <model/stabilizer.h>
#include <model/stick.h>
#include <model/torque_generator.h>
#include <model/universe.h>

#include <model/test/test_load.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestLoad) ;


namespace ProjetUnivers {
  namespace Model {
    namespace Test {


      void TestLoad::testLoadComponent()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Component/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadComponent")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Component>()) ;
      }
      
      void TestLoad::testLoadComputer()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Computer/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadComputer")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Computer>()) ;
      }
      
      void TestLoad::testLoadDestroyable()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Destroyable>\n"
                  "<Energy value=\"10\" unit=\"Joule\" name=\"max_hit_points\"/>\n"
                  "<Energy value=\"5\" unit=\"Joule\" name=\"current_hit_points\"/>\n"
                "</Destroyable>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadDestroyable")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Destroyable>()) ;
        CPPUNIT_ASSERT(root->getTrait<Destroyable>()->getLife()==0.5) ;
      }
      
      void TestLoad::testLoadDetector()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Detector>\n"
                  "<ObjectReference id=\"2\" name=\"computer\"/>\n"
                  "<Distance value=\"5\" unit=\"Meter\" name=\"range\"/>\n"
                "</Detector>\n"
              "</object>\n"
              "<object id=\"2\">\n"
                "<Computer/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadDetector")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 2) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Detector>()) ;
        CPPUNIT_ASSERT(root->getTrait<Detector>()->getRange().Meter() == 5) ;
        CPPUNIT_ASSERT(root->getTrait<Detector>()->getComputer()) ;
      }

      void TestLoad::testLoadDragger()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Dragger dragg_factor=\"10\"/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadDragger")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Dragger>()) ;
      }
      
      void TestLoad::testLoadEngine()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Engine>\n"
                  "<ObjectReference id=\"2\" name=\"controler\"/>\n"
                  "<Force x=\"1\" y=\"0\" z=\"0\" unit=\"Newton\"/>\n"
                "</Engine>\n"
              "</object>\n"
              "<object id=\"2\">\n"
                "<EngineControler>\n"
                  "<ObjectReference id=\"32\" name=\"throttle\"/>\n"
                "</EngineControler>\n"
              "</object>\n"
              "<object id=\"3\">\n"
                "<Throttle y=\"0\"/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadEngine")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 3) ;
        std::set<Kernel::Object*>::iterator current = roots.begin() ; 
        Kernel::Object* engine = *current ;
        ++current ;
        CPPUNIT_ASSERT(engine->getTrait<Engine>()) ;
        Kernel::Object* engine_controler = *current ;
        ++current ;
        CPPUNIT_ASSERT(engine_controler->getTrait<EngineControler>()) ;
        Kernel::Object* throttle = *current ;
        CPPUNIT_ASSERT(throttle->getTrait<Throttle>()) ;
      }
      
      void TestLoad::testLoadForceGenerator()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<ForceGenerator>\n"
                  "<ObjectReference id=\"2\" name=\"controler\"/>\n"
                  "<Force x=\"1\" y=\"0\" z=\"0\" unit=\"Newton\"/>\n"
                "</ForceGenerator>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadForceGenerator")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        std::set<Kernel::Object*>::iterator current = roots.begin() ; 
        Kernel::Object* engine = *current ;
        CPPUNIT_ASSERT(engine->getTrait<ForceGenerator>()) ;
        CPPUNIT_ASSERT(engine->getTrait<ForceGenerator>()->getAppliedForce().Newton() == Ogre::Vector3(1,0,0)) ;
      }

      void TestLoad::testLoadGuidanceControler()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<GuidanceControler/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadGuidanceControler")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        std::set<Kernel::Object*>::iterator current = roots.begin() ; 
        Kernel::Object* engine = *current ;
        CPPUNIT_ASSERT(engine->getTrait<GuidanceControler>()) ;
      }
      
      void TestLoad::testLoadGuidanceSystem()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<GuidanceSystem force=\"10\">\n"
                  "<ObjectReference id=\"2\" name=\"controler\"/>\n"
                "</GuidanceSystem>\n"
              "</object>\n"
              "<object id=\"2\">\n"
                "<GuidanceControler/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadGuidanceSystem")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 2) ;
        std::set<Kernel::Object*>::iterator current = roots.begin() ; 
        Kernel::Object* guidance_system = *current ;
        ++current ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()) ;
        Kernel::Object* guidance_controler = *current ;
        ++current ;
        CPPUNIT_ASSERT(guidance_controler->getTrait<GuidanceControler>()) ;
      }
      
      void TestLoad::testLoadHearing()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Hearing hearing_percentage=\"10\"/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadHearing")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Hearing>()) ;
        CPPUNIT_ASSERT(root->getTrait<Hearing>()->getHearing()==10) ;
      }

      void TestLoad::testLoadLaser()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Laser>\n"
                  "<Position x=\"0\" y=\"0\" z=\"0\"/>\n"
                  "<Orientation angle_degree=\"45\" axis_x=\"0\" axis_y=\"0\" axis_z=\"0\"/>\n"
                "</Laser>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadLaser")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Laser>()) ;
      }
      
      void TestLoad::testLoadMassive()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Massive>\n"
                  "<Mass value=\"10\" unit=\"Kilogram\"/>\n"
                "</Massive>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadMassive")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Massive>()) ;
      }
      
      void TestLoad::testLoadMenu()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Menu file=\"toto\"/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadMenu")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Menu>()) ;
      }
      
      void TestLoad::testLoadMobile()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Mobile>\n"
                  "<Speed x=\"0\" y=\"0\" z=\"0\" unit=\"MeterPerSecond\"/>\n"
                  "<AngularSpeed x=\"0\" y=\"0\" z=\"0\" unit=\"TurnPerSecond\"/>\n"
                "</Mobile>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadMobile")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Mobile>()) ;
      }
      
      void TestLoad::testLoadObserver()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Observer/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadObserver")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Observer>()) ;
      }

      void TestLoad::testLoadOriented()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Oriented>\n"
                  "<Orientation angle_degree=\"45\" axis_x=\"0\" axis_y=\"0\" axis_z=\"0\"/>\n"
                "</Oriented>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadOriented")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Oriented>()) ;
      }
      
      void TestLoad::testLoadPositionned()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Positionned>\n"
                  "<Position x=\"0\" y=\"0\" z=\"0\"/>\n"
                "</Positionned>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadPositionned")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Positionned>()) ;
      }
      
      void TestLoad::testLoadSolid()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Solid>\n"
                  "<Mesh ogre_ressource=\"toto\"/>\n"
                "</Solid>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadSolid")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Solid>()) ;
      }
      
      void TestLoad::testLoadStabilizer()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Stabilizer axis_x=\"1\" axis_y=\"0\" axis_z=\"0\"/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadStabilizer")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Stabilizer>()) ;
      }
      
      void TestLoad::testLoadStick()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Stick/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadStick")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Stick>()) ;
      }
      
      void TestLoad::testLoadTorqueGenerator()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<TorqueGenerator x=\"0\" y=\"0\" z=\"0\" unit=\"NewtonMeter\"/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadTorqueGenerator")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<TorqueGenerator>()) ;
      }
      
      void TestLoad::testLoadUniverse()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Universe/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadUniverse")) ;          
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Universe>()) ;
      }

      void TestLoad::setUp()
      {
      }

      void TestLoad::tearDown()
      {
      }


    }
  }
}
