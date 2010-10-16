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
#include <kernel/deduced_trait.h>
#include <kernel/log.h>

#include <kernel/test/test_relation.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestRelation) ;

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

      namespace
      {
        class T1 : public Trait
        {};

        class DT1 : public DeducedTrait
        {};

        DeclareDeducedTrait(DT1,
                            IsRelated(Selection,HasTrait(T1))) ;
      }

      void TestRelation::isRelatedFormulaChangeStateWhenModifyingRelatedObject()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;

        o2->addTrait(new T1()) ;

        CPPUNIT_ASSERT(o1->getTrait<DT1>()) ;

        o2->destroyTrait(o2->getTrait<T1>()) ;

        CPPUNIT_ASSERT(!o1->getTrait<DT1>()) ;
      }

      void TestRelation::isRelatedFormulaChangeStateWhenChangingRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;
        Object* o3 = model->createObject() ;
        o3->addTrait(new T1()) ;
        Link<Selection>(o1,o2) ;

        CPPUNIT_ASSERT(!o1->getTrait<DT1>()) ;

        Link<Selection>(o1,o3) ;

        CPPUNIT_ASSERT(o1->getTrait<DT1>()) ;

        UnLink<Selection>(o1,o3) ;

        CPPUNIT_ASSERT(!o1->getTrait<DT1>()) ;
      }

      void TestRelation::isRelatedFormulaComplexSample()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;
        Object* o3 = model->createObject() ;
        o3->addTrait(new T1()) ;
        Link<Selection>(o1,o2) ;

        CPPUNIT_ASSERT(!o1->getTrait<DT1>()) ;

        Link<Selection>(o1,o3) ;

        CPPUNIT_ASSERT(o1->getTrait<DT1>()) ;

        o2->addTrait(new T1()) ;
        UnLink<Selection>(o1,o3) ;

        // keep it
        CPPUNIT_ASSERT(o1->getTrait<DT1>()) ;
      }

      namespace
      {
        class Ti : public Trait
        {};

        class DTi : public DeducedTrait
        {};

        DeclareDeducedTrait(DTi,
                            IsRelated(Inverse<Selection>,HasTrait(Ti))) ;
      }

      void TestRelation::isRelatedInverse()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;

        o1->addTrait(new Ti()) ;

        CPPUNIT_ASSERT(o2->getTrait<DTi>()) ;

        o1->destroyTrait(o1->getTrait<Ti>()) ;

        CPPUNIT_ASSERT(!o2->getTrait<DTi>()) ;
      }

      namespace
      {
        class T2 : public Trait
        {};

        class DeducedSelection : public DeducedRelation
        {};

        DeclareDeducedRelation(DeducedSelection,
                               Selection,
                               And(IsFrom(HasTrait(T1)),
                                   IsTo(HasTrait(T2)))) ;
      }

      void TestRelation::relationDeducedByAddingALink()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        o1->addTrait(new T1()) ;
        o2->addTrait(new T2()) ;

        CPPUNIT_ASSERT(Relation::getLinked<DeducedSelection>(o1).empty()) ;

        Link<Selection>(o1,o2) ;

        std::set<Object*> related(Relation::getLinked<DeducedSelection>(o1)) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)1,related.size()) ;
        CPPUNIT_ASSERT(related.find(o2) != related.end()) ;
      }

      void TestRelation::relationDeducedByModifyingALinkedObject()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        o1->addTrait(new T1()) ;

        CPPUNIT_ASSERT(Relation::getLinked<DeducedSelection>(o1).empty()) ;

        o2->addTrait(new T2()) ;

        std::set<Object*> related(Relation::getLinked<DeducedSelection>(o1)) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,related.size()) ;
        CPPUNIT_ASSERT(related.find(o2) != related.end()) ;
      }

      void TestRelation::relationUnDeducedByModifyingALinkedObject()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        o1->addTrait(new T1()) ;
        o2->addTrait(new T2()) ;

        std::set<Object*> related(Relation::getLinked<DeducedSelection>(o1)) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,related.size()) ;
        CPPUNIT_ASSERT(related.find(o2) != related.end()) ;

        o1->destroyTrait(o1->getTrait<T1>()) ;

        CPPUNIT_ASSERT(Relation::getLinked<DeducedSelection>(o1).empty()) ;
      }

      void TestRelation::relationUnDeducedByRemovingALink()
      {

        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        o1->addTrait(new T1()) ;
        o2->addTrait(new T2()) ;

        std::set<Object*> related(Relation::getLinked<DeducedSelection>(o1)) ;
        CPPUNIT_ASSERT_EQUAL((unsigned int)1,related.size()) ;
        CPPUNIT_ASSERT(related.find(o2) != related.end()) ;

        UnLink<Selection>(o1,o2) ;

        CPPUNIT_ASSERT(Relation::getLinked<DeducedSelection>(o1).empty()) ;
      }

      namespace
      {
        class OtherSelection : public Relation
        {};
      }

      void TestRelation::primitiveRelationDoesNotTriggerOtherDeduction()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        o1->addTrait(new T1()) ;
        o2->addTrait(new T2()) ;

        CPPUNIT_ASSERT(Relation::getLinked<DeducedSelection>(o1).empty()) ;

        Link<OtherSelection>(o1,o2) ;

        std::set<Object*> related(Relation::getLinked<DeducedSelection>(o1)) ;

        CPPUNIT_ASSERT_EQUAL((unsigned int)0,related.size()) ;
      }

      namespace
      {
        class DontHave : public Relation
        {};

        class ShouldNotDeduce : public DeducedRelation
        {};

        DeclareDeducedRelation(ShouldNotDeduce,DontHave,IsFrom(And(HasTrait(T1),
                                                                   IsRelated(Selection,HasTrait(T2))))) ;

      }

      void TestRelation::havingAllButPrimitiveRelationDoesNotMakeItTrue()
      {
        std::auto_ptr<Model> model(new Model()) ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        o2->addTrait(new T2()) ;

        Link<Selection>(o1,o2) ;

        CPPUNIT_ASSERT(!Relation::areLinked<ShouldNotDeduce>(o1,o2)) ;

        // should not change anything
        o1->addTrait(new T1()) ;

        CPPUNIT_ASSERT(!Relation::areLinked<ShouldNotDeduce>(o1,o2)) ;
      }
    }
  }
}
