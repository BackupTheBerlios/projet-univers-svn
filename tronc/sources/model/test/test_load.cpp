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
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/parameters.h>
#include <kernel/xml_reader.h>

#include <model/model.h>
#include <model/component.h>
#include <model/computer.h>
#include <model/destroyable.h>
#include <model/detector.h>
#include <model/dragger.h>
#include <model/engine.h>
#include <model/engine_controler.h>
#include <model/throttle.h>
#include <model/force_generator.h>
#include <model/listener.h>
#include <model/guidance_controler.h>
#include <model/guidance_system.h>
#include <model/laser.h>
#include <model/menu.h>
#include <model/observer.h>
#include <model/player_configuration.h>
#include <model/positioned.h>
#include <model/oriented.h>
#include <model/mobile.h>
#include <model/massive.h>
#include <model/solid.h>
#include <model/stabilizer.h>
#include <model/stick.h>
#include <model/targeting_system.h>
#include <model/torque_generator.h>
#include <model/universe.h>

#include <model/test/test_load.h>
#include <model/control_connection.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestLoad) ;

namespace ProjetUnivers
{
  namespace Model
  {
    namespace Test
    {

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
                  "<Distance value=\"5\" unit=\"Meter\" name=\"range\"/>\n"
                "</Detector>\n"
              "</object>\n"
              "<object id=\"2\">\n"
                "<Computer/>\n"
              "</object>\n"
              "<Relation name=\"DataConnection\" from=\"1\" to=\"2\"/>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadDetector")) ;
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 2) ;

        bool exist_detector = false ;

        for (std::set<Kernel::Object*>::iterator current = roots.begin() ;
             current != roots.end() ;
             ++current)
        {
          Kernel::Object* object = *current ;
          if (object->getTrait<Detector>())
          {
            exist_detector = true ;
            CPPUNIT_ASSERT(object->getTrait<Detector>()->getRange().Meter() == 5) ;
          }
        }

        CPPUNIT_ASSERT(exist_detector) ;
      }

      void TestLoad::testLoadDragger()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Dragger drag_factor=\"10\"/>\n"
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
                  "<Force x=\"1\" y=\"0\" z=\"0\" unit=\"Newton\"/>\n"
                  "<Distance value=\"5\" unit=\"Meter\"/>\n"
                  "<Position x=\"1\" y=\"2\" z=\"3\" unit=\"Meter\"/>\n"
                "</Engine>\n"
              "</object>\n"
              "<object id=\"2\">\n"
                "<EngineControler>\n"
                  "<ObjectReference id=\"3\" name=\"throttle\"/>\n"
                "</EngineControler>\n"
              "</object>\n"
              "<object id=\"3\">\n"
                "<Throttle y=\"0\"/>\n"
              "</object>\n"
              "<Relation name=\"ControlConnection\" from=\"3\" to=\"2\"/>\n"
              "<Relation name=\"ControlConnection\" from=\"2\" to=\"1\"/>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadEngine")) ;
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)3,roots.size()) ;

        Engine* engine = NULL ;
        EngineControler* engine_controler = NULL ;
        Throttle* throttle = NULL ;

        for (std::set<Kernel::Object*>::iterator current = roots.begin() ;
             current != roots.end() ;
             ++current)
        {
          Kernel::Object* object = *current ;

          if (object->getTrait<Engine>())
          {
            engine = object->getTrait<Engine>() ;
          }

          if (object->getTrait<EngineControler>())
          {
            engine_controler = object->getTrait<EngineControler>() ;
          }
          if (object->getTrait<Throttle>())
            throttle = object->getTrait<Throttle>() ;
        }

        CPPUNIT_ASSERT(engine) ;
        CPPUNIT_ASSERT(engine_controler) ;
        CPPUNIT_ASSERT(throttle) ;

        CPPUNIT_ASSERT(Kernel::Relation::areLinked<ControlConnection>(throttle->getObject(),engine_controler->getObject())) ;
        CPPUNIT_ASSERT(Kernel::Relation::areLinked<ControlConnection>(engine_controler->getObject(),engine->getObject())) ;

        CPPUNIT_ASSERT_EQUAL(Position::Meter(1,2,3),engine->getOutputPosition()) ;
        CPPUNIT_ASSERT_EQUAL(Distance(Distance::_Meter,5),engine->getOutputRadius()) ;
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
                "<GuidanceControler>\n"
                  "<ObjectReference id=\"2\" name=\"stick\"/>\n"
                "</GuidanceControler>\n"
                "<object id=\"2\">\n"
                  "<Stick/>\n"
                "</object>\n"
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
                "<object id=\"2\">\n"
                  "<GuidanceControler>\n"
                    "<ObjectReference id=\"3\" name=\"stick\"/>\n"
                  "</GuidanceControler>\n"
                "</object>\n"
                "<object id=\"3\">\n"
                  "<Stick/>\n"
                "</object>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadGuidanceSystem")) ;
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,roots.size()) ;
        std::set<Kernel::Object*>::iterator current = roots.begin() ;
        Kernel::Object* guidance_system = *current ;
        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()) ;

        CPPUNIT_ASSERT(guidance_system->getTrait<GuidanceSystem>()->m_control) ;

        std::set<GuidanceControler*> guidance_controlers = guidance_system->getDescendants<GuidanceControler>() ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,guidance_controlers.size()) ;
        GuidanceControler* guidance_controler = *guidance_controlers.begin() ;
        CPPUNIT_ASSERT(guidance_controler->m_stick) ;
      }

      void TestLoad::testLoadListener()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Listener hearing_percentage=\"10\"/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadListener")) ;
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Listener>()) ;
        CPPUNIT_ASSERT(root->getTrait<Listener>()->getHearing()==10) ;
      }

      void TestLoad::testLoadLaser()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Laser>\n"
                  "<Position x=\"0\" y=\"0\" z=\"0\" unit=\"Meter\"/>\n"
                  "<Orientation angle_degree=\"45\" axis_x=\"0\" axis_y=\"0\" axis_z=\"0\"/>\n"
                  "<Duration value=\"3\" unit=\"Second\" name=\"beam_lifetime\"/>\n"
                  "<Duration value=\"1\" unit=\"Second\" name=\"shot_delay\"/>\n"
                  "<Distance value=\"10\" unit=\"Meter\" name=\"beam_length\"/>\n"
                  "<Distance value=\"1\" unit=\"Meter\" name=\"beam_radius\"/>\n"
                  "<Speed value=\"8000\" unit=\"MeterPerSecond\" name=\"beamSpeed\"/>\n"
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
        Laser* laser = root->getTrait<Laser>() ;

        CPPUNIT_ASSERT_EQUAL(Position(),laser->getOutPosition()) ;
        CPPUNIT_ASSERT_EQUAL(Duration::Second(3),laser->getLaserBeamLifeDuration()) ;
        CPPUNIT_ASSERT_EQUAL(Duration::Second(1),laser->getTimeBetweenShots()) ;
        CPPUNIT_ASSERT_EQUAL(Distance(Distance::_Meter,10),laser->getBeamLength()) ;
        CPPUNIT_ASSERT_EQUAL(Distance(Distance::_Meter,1),laser->getBeamRadius()) ;
        CPPUNIT_ASSERT_EQUAL(8000.0f,laser->getLaserSpeedMeterPerSecond()) ;
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
                "<Observer>\n"
                  "<Angle value=\"40\" unit=\"Degree\"/>\n"
                "</Observer>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadObserver")) ;
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Observer>()) ;
        Observer* observer = root->getTrait<Observer>() ;
        CPPUNIT_ASSERT_EQUAL(40.0f,observer->getFieldOfView().valueDegrees()) ;
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

      void TestLoad::testLoadPositioned()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Positioned>\n"
                  "<Position x=\"0\" y=\"0\" z=\"0\" unit=\"Meter\"/>\n"
                "</Positioned>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadPositioned")) ;
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<Positioned>()) ;
      }

      void TestLoad::testLoadSolid()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Solid>\n"
                  "<Mesh ogre_ressource=\"test_ship.mesh\"/>\n"
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
        CPPUNIT_ASSERT(root->getTrait<Solid>()->getRadius().Meter()>0) ;
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

      void TestLoad::testLoadPlayerConfiguration()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<PlayerConfiguration>\n"
                  "<Mapping command=\"1\">\n"
                    "<Key number=\"1\"/>\n"
                  "</Mapping>\n"
                  "<Mapping command=\"2\">\n"
                    "<MouseButton number=\"1\"/>\n"
                  "</Mapping>\n"
                  "<Mapping command=\"3\">\n"
                    "<JoystickButton number=\"1\"/>\n"
                  "</Mapping>\n"
                  "<Mapping command=\"4\">\n"
                    "<JoystickX/>\n"
                  "</Mapping>\n"
                  "<Mapping command=\"5\">\n"
                    "<MouseY/>\n"
                  "</Mapping>\n"
                  "<Mapping command=\"6\">\n"
                    "<InvertedMouseWheel/>\n"
                  "</Mapping>\n"
                "</PlayerConfiguration>\n"
              "</object>\n"
            "</model>\n") ;

        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadPlayerConfiguration")) ;
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        PlayerConfiguration* configuration = root->getTrait<PlayerConfiguration>() ;
        CPPUNIT_ASSERT(configuration) ;

        CPPUNIT_ASSERT(configuration->getInputEvent("1")==PlayerConfiguration::InputEvent::key(1)) ;
        CPPUNIT_ASSERT(configuration->getInputEvent("2")==PlayerConfiguration::InputEvent::mouseButton(1)) ;
        CPPUNIT_ASSERT(configuration->getInputEvent("3")==PlayerConfiguration::InputEvent::joystickButton(1)) ;
        CPPUNIT_ASSERT(configuration->getInputAxis("4")==PlayerConfiguration::InputAxis(PlayerConfiguration::InputAxis::JoystickX)) ;
        CPPUNIT_ASSERT(configuration->getInputAxis("5")==PlayerConfiguration::InputAxis(PlayerConfiguration::InputAxis::MouseY)) ;
        CPPUNIT_ASSERT(configuration->getInputAxis("6")==-PlayerConfiguration::InputAxis(PlayerConfiguration::InputAxis::MouseWheel)) ;

      }

      void TestLoad::testTargetingSystem()
      {
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<TargetingSystem/>\n"
              "</object>\n"
            "</model>\n") ;
        std::auto_ptr<Kernel::XMLReader> reader(Kernel::XMLReader::getStringReader(content)) ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadUniverse")) ;
        reader->read(model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;
        CPPUNIT_ASSERT(root->getTrait<TargetingSystem>()) ;
      }

      void TestLoad::loadShip()
      {
        std::auto_ptr<Kernel::Model> model(new Kernel::Model("TestLoad::testLoadUniverse")) ;
        Model::load("default_ship.ship",model.get()) ;

        std::set<Kernel::Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size() == 1) ;
        Kernel::Object* root = *roots.begin() ;

        CPPUNIT_ASSERT(!root->getChildren<TargetingSystem>().empty()) ;
        CPPUNIT_ASSERT(root->getChildren<TargetingSystem>().size()==1) ;
      }

    }
  }
}
