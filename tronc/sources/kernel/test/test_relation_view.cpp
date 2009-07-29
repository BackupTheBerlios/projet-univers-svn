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
#include <kernel/relation_view.h>
#include <kernel/model.h>
#include <kernel/deduced_trait.h>
#include <kernel/log.h>
#include <kernel/view_point.h>
#include <kernel/controler_set.h>
#include <kernel/relation_controler.h>

#include <kernel/test/test_relation_view.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Kernel::Test::TestRelationView) ;

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

        class RelationViewPoint : public ViewPoint
        {
        public:

          RelationViewPoint(Model* model)
          : ViewPoint(model)
          {}
        };

        RegisterViewPoint(RelationViewPoint) ;

        class SelectionView : public RelationView<RelationViewPoint>
        {
        public:

          static int m_number_of_init ;
          static int m_number_of_close ;

          void onInit()
          {
            ++m_number_of_init ;
          }

          void onClose()
          {
            ++m_number_of_close ;
          }
        };

        int SelectionView::m_number_of_init = 0 ;
        int SelectionView::m_number_of_close = 0 ;

        RegisterRelationView(SelectionView,Selection,RelationViewPoint) ;
      }

      void TestRelationView::initView()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        SelectionView::m_number_of_init = 0 ;

        Link<Selection>(o1,o2) ;

        CPPUNIT_ASSERT_EQUAL(1,SelectionView::m_number_of_init) ;
      }

      void TestRelationView::closeView()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        SelectionView::m_number_of_close = 0 ;

        UnLink<Selection>(o1,o2) ;
        CPPUNIT_ASSERT_EQUAL(1,SelectionView::m_number_of_close) ;
      }

      namespace
      {
        class T1 : public Trait
        {
        public:

          void touch()
          {
            notify() ;
          }
        };

        class T2 : public Trait
        {
        public:

          void touch()
          {
            notify() ;
          }
        };

        class DeducedSelection : public DeducedRelation
        {};

        DeclareDeducedRelation(DeducedSelection,
                               Selection,
                               And(IsFrom(HasTrait(T1)),
                                   IsTo(HasTrait(T2)))) ;

        class DeducedSelectionView : public RelationView<RelationViewPoint>
        {
        public:

          static int m_number_of_init ;
          static int m_number_of_close ;
          static int m_number_of_update ;

          void onInit()
          {
            ++m_number_of_init ;
          }

          void onClose()
          {
            ++m_number_of_close ;
          }

          void onUpdate()
          {
            ++m_number_of_update ;
          }
        };

        int DeducedSelectionView::m_number_of_init = 0 ;
        int DeducedSelectionView::m_number_of_close = 0 ;
        int DeducedSelectionView::m_number_of_update = 0 ;

        RegisterRelationView(DeducedSelectionView,DeducedSelection,RelationViewPoint) ;
      }

      void TestRelationView::viewOnDeducedRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        DeducedSelectionView::m_number_of_init = 0 ;
        Link<Selection>(o1,o2) ;
        o1->addTrait(new T1()) ;
        o2->addTrait(new T2()) ;

        CPPUNIT_ASSERT_EQUAL(1,DeducedSelectionView::m_number_of_init) ;

        DeducedSelectionView::m_number_of_update = 0 ;
        o2->getTrait<T2>()->touch() ;
        CPPUNIT_ASSERT_EQUAL(1,DeducedSelectionView::m_number_of_update) ;
        o1->getTrait<T1>()->touch() ;
        CPPUNIT_ASSERT_EQUAL(2,DeducedSelectionView::m_number_of_update) ;

        DeducedSelectionView::m_number_of_close = 0 ;
        o2->destroyTrait(o2->getTrait<T2>()) ;
        CPPUNIT_ASSERT_EQUAL(1,DeducedSelectionView::m_number_of_close) ;
      }

      namespace
      {

        class RelationControlerSet : public ControlerSet
        {
        public:

          RelationControlerSet(Model* model)
          : ControlerSet(model)
          {}
        };

        RegisterControlerSet(RelationControlerSet) ;

        class SelectionControler : public RelationControler<RelationControlerSet>
        {
        public:

          static int m_number_of_init ;
          static int m_number_of_close ;

          void onInit()
          {
            ++m_number_of_init ;
          }

          void onClose()
          {
            ++m_number_of_close ;
          }
        };

        int SelectionControler::m_number_of_init = 0 ;
        int SelectionControler::m_number_of_close = 0 ;

        RegisterRelationControler(SelectionControler,Selection,RelationControlerSet) ;
      }

      void TestRelationView::initControler()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        SelectionControler::m_number_of_init = 0 ;

        Link<Selection>(o1,o2) ;

        CPPUNIT_ASSERT_EQUAL(1,SelectionControler::m_number_of_init) ;
      }

      void TestRelationView::closeControler()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        SelectionControler::m_number_of_close = 0 ;

        UnLink<Selection>(o1,o2) ;
        CPPUNIT_ASSERT_EQUAL(1,SelectionControler::m_number_of_close) ;
      }

      namespace
      {
        class OrSelection : public DeducedRelation
        {};

        DeclareDeducedRelation(OrSelection,
                               Selection,
                               Or(IsFrom(HasTrait(T1)),
                                   IsTo(HasTrait(T2)))) ;

        class OrView : public RelationView<RelationViewPoint>
        {
        public:

          static int m_number_of_init ;
          static int m_number_of_close ;
          static int m_number_of_update ;

          void onInit()
          {
            ++m_number_of_init ;
          }

          void onClose()
          {
            ++m_number_of_close ;
          }

          void onUpdate()
          {
            ++m_number_of_update ;
          }
        };

        int OrView::m_number_of_init = 0 ;
        int OrView::m_number_of_close = 0 ;
        int OrView::m_number_of_update = 0 ;

        RegisterRelationView(OrView,OrSelection,RelationViewPoint) ;
      }

      void TestRelationView::updateOrFormula()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        o1->addTrait(new T1()) ;

        OrView::m_number_of_update = 0 ;

        o1->getTrait<T1>()->touch() ;
        CPPUNIT_ASSERT_EQUAL(1,OrView::m_number_of_update) ;

        o2->addTrait(new T2()) ;

        CPPUNIT_ASSERT_EQUAL(2,OrView::m_number_of_update) ;

        o2->getTrait<T2>()->touch() ;

        CPPUNIT_ASSERT_EQUAL(3,OrView::m_number_of_update) ;
      }

      namespace
      {
        class T3 : public Trait
        {

        };

        class DeducedDeduced : public DeducedRelation
        {};

        DeclareDeducedRelation(DeducedDeduced,
                               DeducedSelection,
                               IsFrom(HasTrait(T3))) ;

        class DeducedDeducedView : public RelationView<RelationViewPoint>
        {
        public:

          static int m_number_of_init ;
          static int m_number_of_close ;
          static int m_number_of_update ;

          void onInit()
          {
            ++m_number_of_init ;
          }

          void onClose()
          {
            ++m_number_of_close ;
          }

          void onUpdate()
          {
            ++m_number_of_update ;
          }
        };

        int DeducedDeducedView::m_number_of_init = 0 ;
        int DeducedDeducedView::m_number_of_close = 0 ;
        int DeducedDeducedView::m_number_of_update = 0 ;

        RegisterRelationView(DeducedDeducedView,DeducedDeduced,RelationViewPoint) ;
      }

      void TestRelationView::deducedRelationOnDeducedRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        o1->addTrait(new T1()) ;
        o2->addTrait(new T2()) ;
        o1->addTrait(new T3()) ;

        DeducedDeducedView::m_number_of_update = 0 ;

        o1->getTrait<T1>()->touch() ;

        CPPUNIT_ASSERT_EQUAL(1,DeducedDeducedView::m_number_of_update) ;

        o2->getTrait<T2>()->touch() ;

        CPPUNIT_ASSERT_EQUAL(2,DeducedDeducedView::m_number_of_update) ;
      }


    }
  }
}

