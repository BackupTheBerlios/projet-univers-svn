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
#include <kernel/relation.h>
#include <kernel/model.h>

#include <kernel/test/test_relation.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Kernel::Test::TestRelation) ;

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      namespace
      {
        class Selection : public Relation
        {};

      }

      void TestRelation::add()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        std::set<Object*> related(Relation::getLinked<Selection>(o1)) ;
        CPPUNIT_ASSERT(related.find(o2) != related.end()) ;
        CPPUNIT_ASSERT(related.size() == 1) ;
      }

      void TestRelation::severalLinked()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;
        Object* o3 = model->createObject() ;
        Object* o4 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        Link<Selection>(o1,o4) ;
        Link<Selection>(o3,o4) ;

        std::set<Object*> related(Relation::getLinked<Selection>(o1)) ;
        CPPUNIT_ASSERT(related.find(o2) != related.end()) ;
        CPPUNIT_ASSERT(related.find(o4) != related.end()) ;
        CPPUNIT_ASSERT(related.size() == 2) ;
      }

      void TestRelation::remove()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;

        UnLink<Selection>(o1,o2) ;
        std::set<Object*> related(Relation::getLinked<Selection>(o1)) ;
        CPPUNIT_ASSERT(related.size() == 0) ;
      }

      void TestRelation::addTwiceGetOnlyOne()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        Link<Selection>(o1,o2) ;
        std::set<Object*> related(Relation::getLinked<Selection>(o1)) ;
        CPPUNIT_ASSERT(related.find(o2) != related.end()) ;
        CPPUNIT_ASSERT(related.size() == 1) ;
      }

      void TestRelation::removeUnexistingIsCorrect()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        UnLink<Selection>(o1,o2) ;

        std::set<Object*> related(Relation::getLinked<Selection>(o1)) ;
        CPPUNIT_ASSERT(related.size() == 0) ;
      }

      void TestRelation::destroyingCalledObjectRemoveLink()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;

        o2->destroyObject() ;

        std::set<Object*> related(Relation::getLinked<Selection>(o1)) ;
        CPPUNIT_ASSERT(related.size() == 0) ;
      }

      void TestRelation::getInverseRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        std::set<Object*> related(Relation::getLinked<Inverse<Selection> >(o2)) ;
        CPPUNIT_ASSERT(related.find(o1) != related.end()) ;
        CPPUNIT_ASSERT(related.size() == 1) ;
      }

      void TestRelation::addInverseRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Inverse<Selection> >(o1,o2) ;
        std::set<Object*> related(Relation::getLinked<Selection>(o2)) ;
        CPPUNIT_ASSERT(related.find(o1) != related.end()) ;
        CPPUNIT_ASSERT(related.size() == 1) ;

      }


    }
  }
}
