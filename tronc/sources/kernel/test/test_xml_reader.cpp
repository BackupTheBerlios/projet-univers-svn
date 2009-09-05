/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2007 Mathieu ROGER                                      *
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
#include <kernel/xml_reader.h>
#include <kernel/test/test_xml_reader.h>
#include <kernel/relation.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Test::TestXMLReader) ;

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {

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

          // read position.          
          static Position read(Reader* reader)
          {
            Position result ;
            
            std::map<std::string,std::string>::const_iterator finder ; 

            finder = reader->getAttributes().find("x") ;
            if (finder != reader->getAttributes().end())
            {
              result.m_x = atoi(finder->second.c_str()) ;
            }

            finder = reader->getAttributes().find("y") ;
            if (finder != reader->getAttributes().end())
            {
              result.m_y = atoi(finder->second.c_str()) ;
            }

            finder = reader->getAttributes().find("z") ;
            if (finder != reader->getAttributes().end())
            {
              result.m_z = atoi(finder->second.c_str()) ;
            }
            
            // move out of node
            while (!reader->isEndNode() && reader->processNode())
            {}
            
            reader->processNode() ;
            
            return result ;            
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

          static Trait* read(Reader* reader)
          {
            while (!reader->isEndNode() && reader->processNode())
            {
              if (reader->isTraitNode())
              {
                Trait::read(reader) ;
              }
            }
            reader->processNode() ;
            return new Universe() ;
          }

        };
        
        RegisterTrait(Universe) ;        
        
        // A Trait class
        class Positioned : public Trait
        {
        public:
          
          Positioned(const Position& position)
          : m_position(position)
          {}
          
          static Trait* read(Reader* reader)
          {
            Position position ;
            while (!reader->isEndNode() && reader->processNode())
            {
              if (reader->isTraitNode() && reader->getTraitName() == "position")
              {
                position = Position::read(reader) ;
              }
              else
              {
                Trait::read(reader) ;
              }
            }
            reader->processNode() ;

            return new Positioned(position) ;
          }
          
          
        private:
          
          Position m_position ;
        };
        
        RegisterTrait(Positioned) ;

        // A Trait class
        class Truc : public Trait
        {
        public:
          
          Truc(const ObjectReference& reference)
          : m_reference(reference)
          {}
          
          static Trait* read(Reader* reader)
          {
            ObjectReference reference ;
            while (!reader->isEndNode() && reader->processNode())
            {
              if (reader->isTraitNode() && reader->getTraitName() == "Reference")
              {
                reference = ObjectReference::read(reader) ;
              }
              else
              {
                Trait::read(reader) ;
              }
            }
            reader->processNode() ;

            return new Truc(reference) ;
          }
          
          Object* getReference()
          {
            return m_reference ;
          }          
          
        private:
          
          ObjectReference m_reference ;
        };
        
        RegisterTrait(Truc) ;
        
        class R : public Relation
        {};

        RegisterRelation(R) ;

      }

      void TestXMLReader::basicTest()
      {
        std::auto_ptr<Model> model(new Model("TestXMLReader::basicTest")) ;
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Universe/>\n"
                "<object id=\"2\">\n"
                  "<StellarSystem/>\n"
                  "<Positioned>\n"
                    "<position x=\"0\" y=\"0\" z=\"0\" unit=\"Meter\"/>\n"
                  "</Positioned>\n"
                  "<Oriented>\n"
                    "<orientation w=\"1\" x=\"0\" y=\"0\" z=\"0\"/>\n"
                  "</Oriented>\n"
                  "<Mobile>\n"
                    "<speed x=\"100\" y=\"0\" z=\"0\" unit=\"MeterPerSecond\"/>\n"
                  "</Mobile>\n"
                "</object>\n"
                "<object id=\"6\">\n"
                  "<StellarSystem/>\n"
                "</object>\n"
              "</object>\n"
              "<object id=\"3\">\n"
                "<Truc>\n"
                  "<!-- reference to Oriented trait of object with id 1 -->\n"
                  "<Reference id=\"1\"/>\n"
                "</Truc>\n"
              "</object>\n"
            "</model>\n") ;
        
//        std::cout << content << std::endl ;

        std::auto_ptr<XMLReader> reader(XMLReader::getStringReader(content)) ;
        reader->read(model.get()) ;
        
        std::set<Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size()==2) ;
        
        std::set<Object*>::const_iterator iterator = roots.begin() ;
        Object* first ;
        Object* second ;
        
        CPPUNIT_ASSERT((*iterator)->getTrait<Universe>()||(*iterator)->getTrait<Truc>()) ;
        
        if ((*iterator)->getTrait<Universe>())
        {
          first = *iterator ;
          ++iterator ;
          second = *iterator ;
        }
        else
        {
          second = *iterator ;
          ++iterator ;
          first = *iterator ;
        }
        
        CPPUNIT_ASSERT(second->getTrait<Truc>()) ;
        CPPUNIT_ASSERT(second->getTrait<Truc>()->getReference()) ;
        CPPUNIT_ASSERT(second->getTrait<Truc>()->getReference() == first) ;
      }

      void TestXMLReader::XMLCharTest()
      {
        const xmlChar* data = (const xmlChar*)"object" ;
        
        CPPUNIT_ASSERT(xmlStrEqual(data,data)==1) ;
        
      }

      void TestXMLReader::readRelation()
      {
        std::auto_ptr<Model> model(new Model("TestXMLReader::basicTest")) ;
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Universe/>\n"
              "</object>\n"
              "<object id=\"2\">\n"
                "<Truc/>\n"
              "</object>\n"
              "<Relation name=\"R\" from=\"1\" to=\"2\"/>\n"
            "</model>\n"
        ) ;

        std::auto_ptr<XMLReader> reader(XMLReader::getStringReader(content)) ;
        reader->read(model.get()) ;

        std::set<Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size()==2) ;

        std::set<Object*>::const_iterator iterator = roots.begin() ;
        Object* first ;
        Object* second ;

        CPPUNIT_ASSERT((*iterator)->getTrait<Universe>()||(*iterator)->getTrait<Truc>()) ;

        if ((*iterator)->getTrait<Universe>())
        {
          first = *iterator ;
          ++iterator ;
          second = *iterator ;
        }
        else
        {
          second = *iterator ;
          ++iterator ;
          first = *iterator ;
        }

        CPPUNIT_ASSERT(Relation::areLinked<R>(first,second)) ;
      }

      void TestXMLReader::readRelationEvenInsideObject()
      {
        std::auto_ptr<Model> model(new Model("TestXMLReader::basicTest")) ;
        std::string content(
          "<?xml version=\"1.0\"?>\n"
            "<model>\n"
              "<object id=\"1\">\n"
                "<Universe/>\n"
                "<Relation name=\"R\" from=\"1\" to=\"2\"/>\n"
              "</object>\n"
              "<object id=\"2\">\n"
                "<Truc/>\n"
              "</object>\n"
            "</model>\n"
        ) ;

        std::auto_ptr<XMLReader> reader(XMLReader::getStringReader(content)) ;
        reader->read(model.get()) ;

        std::set<Object*> roots(model->getRoots()) ;
        CPPUNIT_ASSERT(roots.size()==2) ;

        std::set<Object*>::const_iterator iterator = roots.begin() ;
        Object* first ;
        Object* second ;

        CPPUNIT_ASSERT((*iterator)->getTrait<Universe>()||(*iterator)->getTrait<Truc>()) ;

        if ((*iterator)->getTrait<Universe>())
        {
          first = *iterator ;
          ++iterator ;
          second = *iterator ;
        }
        else
        {
          second = *iterator ;
          ++iterator ;
          first = *iterator ;
        }

        CPPUNIT_ASSERT(Relation::areLinked<R>(first,second)) ;
      }

    }
  }
}
