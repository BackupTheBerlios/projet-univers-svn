/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2009 Mathieu ROGER                                      *
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
#include <memory>
#include <kernel/object.h>
#include <kernel/object_reference.h>
#include <kernel/model.h>
#include <kernel/trait.h>
#include <kernel/xml_writer.h>
#include <kernel/test/test_xml_writer.h>


namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestXMLWriter) ;
      
      // local classes 
      namespace 
      {
        
        // A value class
        class Position
        {
        public:
        
          Position()
          : m_x(0), m_y(0), m_z(0)
          {}

          Position(const Position& position)
          : m_x(position.m_x), m_y(position.m_y), m_z(position.m_z)
          {}

          /// Write a position.          
          void write(Writer* writer)
          {
            writer->startTrait("Position") ;
            writer->addAttribute("x",toString(m_x)) ;
            writer->addAttribute("y",toString(m_y)) ;
            writer->addAttribute("z",toString(m_z)) ;
            writer->endTrait() ;
            
          }   
          
        private:
          
          int m_x ;
          int m_y ;
          int m_z ;
        };
        
        // A trait class
        class Universe : public Trait
        {
        public:

          void write(Writer* writer)
          {
            writer->startTrait("Universe") ;
            writer->endTrait() ;
          }

        };
        
        // A Trait class
        class Positioned : public Trait
        {
        public:
          
          Positioned(const Position& position)
          : m_position(position)
          {}
          
          void write(Writer* writer)
          {
            writer->startTrait("Positioned") ;
            m_position.write(writer) ;
            writer->endTrait() ;
          }
          
          
        private:
          
          Position m_position ;
        };
        
        // A Trait class
        class Truc : public Trait
        {
        public:
          
          Truc(const ObjectReference& reference)
          : m_reference(reference)
          {}
          
          void write(Writer* writer)
          {
            writer->startTrait("Truc") ;
            m_reference.write(writer,"toto") ;
            writer->endTrait() ;
          }
          
          Object* getReference()
          {
            return m_reference ;
          }          
          
        private:
          
          ObjectReference m_reference ;
        };
        
      }

      void TestXMLWriter::object()
      {
        std::auto_ptr<Model> model(new Model("TestXMLWriter::object")) ;
        model->createObject() ;
        
        std::auto_ptr<XMLWriter> writer(XMLWriter::getStringWriter()) ;
        
        writer->write(model.get()) ;
        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model><object id=\"0\"/></model>\n"),
                             writer->getContent()) ;
        
      }

      void TestXMLWriter::trait()
      {
        std::auto_ptr<Model> model(new Model("TestXMLWriter::trait")) ;
        Kernel::Object* object1 = model->createObject() ;
        object1->addTrait(new Universe()) ;
        
        std::auto_ptr<XMLWriter> writer(XMLWriter::getStringWriter()) ;
        
        writer->write(model.get()) ;
        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model><object id=\"0\"><Universe/></object></model>\n"),
                             writer->getContent()) ;
        
      }

      void TestXMLWriter::traitWithContent()
      {
        std::auto_ptr<Model> model(new Model("TestXMLWriter::traitWithContent")) ;
        Kernel::Object* object1 = model->createObject() ;
        object1->addTrait(new Positioned(Position())) ;
        
        std::auto_ptr<XMLWriter> writer(XMLWriter::getStringWriter()) ;
        
        writer->write(model.get()) ;
        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model><object id=\"0\"><Positioned>"
                                         "<Position x=\"0\" y=\"0\" z=\"0\"/>"
                                         "</Positioned></object></model>\n"),
                             writer->getContent()) ;
        
      }

      void TestXMLWriter::traitWithObjectReference()      
      {
        std::auto_ptr<Model> model(new Model("TestXMLWriter::traitWithObjectReference")) ;
        Kernel::Object* object1 = model->createObject() ;
        Kernel::Object* object2 = model->createObject() ;
        object2->addTrait(new Truc(object1)) ;
        
        std::auto_ptr<XMLWriter> writer(XMLWriter::getStringWriter()) ;
        
        writer->write(model.get()) ;
        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model>"
                                           "<object id=\"0\"/>"
                                           "<object id=\"1\">"
                                             "<Truc>"
                                               "<ObjectReference id=\"0\" name=\"toto\"/>"
                                             "</Truc>"
                                           "</object>"
                                         "</model>\n"),
                             writer->getContent()) ;
      }

      void TestXMLWriter::writeSingleObject()
      {
        std::auto_ptr<Model> model(new Model("TestXMLWriter::writeSingleObject")) ;
        Kernel::Object* object1 = model->createObject() ;
        model->createObject() ;
        
        std::auto_ptr<XMLWriter> writer(XMLWriter::getStringWriter()) ;
        
        writer->writeSingleObject(object1) ;
        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model>"
                                           "<object id=\"0\"/>"
                                         "</model>\n"),
                             writer->getContent()) ;
      }
      
      void TestXMLWriter::writeSubObjects()
      {
        std::auto_ptr<Model> model(new Model("TestXMLWriter::writeSingleObject")) ;
        Kernel::Object* object1 = model->createObject() ;
        object1->createObject() ;
        
        std::auto_ptr<XMLWriter> writer(XMLWriter::getStringWriter()) ;
        
        writer->writeSingleObject(object1) ;
        CPPUNIT_ASSERT_EQUAL(std::string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
                                         "<model>"
                                           "<object id=\"0\">"
                                             "<object id=\"1\"/>"
                                           "</object>"
                                         "</model>\n"),
                             writer->getContent()) ;
      }
    
    }
  }
}
