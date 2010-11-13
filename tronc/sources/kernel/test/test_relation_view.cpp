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
#include <kernel/test/reflection/meta.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Test
    {

      CPPUNIT_TEST_SUITE_REGISTRATION(TestRelationView) ;

      namespace Local1
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

      using namespace Local1 ;

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

      namespace Local2
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

      using namespace Local2 ;

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

      namespace Local3
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

      using namespace Local3 ;

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

      namespace Local4
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

      using namespace Local4 ;

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

      namespace Local5
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
            CPPUNIT_ASSERT(getView<DeducedSelectionView>()) ;
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

      using namespace Local5 ;

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

      void TestRelationView::severalInitCloseInTheSameFrame()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        o1->addTrait(new T1()) ;
        o2->addTrait(new T2()) ;
        o1->addTrait(new T3()) ;

        DeducedDeducedView::m_number_of_init = 0 ;
        DeducedDeducedView::m_number_of_close = 0 ;
        DeducedDeducedView::m_number_of_update = 0 ;
        DeducedSelectionView::m_number_of_init = 0 ;

        model->startTransaction() ;

        Link<Selection>(o1,o2) ;
        UnLink<Selection>(o1,o2) ;
        Link<Selection>(o1,o2) ;

        model->endTransaction() ;

      }


      namespace Local6
      {
        class BaseRelation : public Relation
        {};

        class Deduced : public DeducedRelation
        {};

        class A : public Trait
        {};

        DeclareDeducedRelation(Deduced,BaseRelation,IsFrom(HasTrait(A))) ;

        class DeducedControler : public RelationControler<RelationControlerSet>
        {
        protected:

          void onClose()
          {
            CPPUNIT_ASSERT(Relation::areLinked<BaseRelation>(getObjectFrom(),getObjectTo())) ;
            UnLink<BaseRelation>(getObjectFrom(),getObjectTo()) ;
          }
        };

        RegisterRelationControler(DeducedControler,Deduced,RelationControlerSet)
      }

      using namespace Local6 ;

      void TestRelationView::deducedRelationDestroyBaseRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<BaseRelation>(o1,o2) ;
        Trait* a = o1->addTrait(new A()) ;

        Link<Selection>(o1,o1) ;

        o1->destroyTrait(a) ;

        CPPUNIT_ASSERT(!Relation::areLinked<BaseRelation>(o1,o2)) ;
      }

      void TestRelationView::destroyModelShouldCloseRelationViews()
      {
        SelectionView::m_number_of_close = 0 ;
        {
          std::auto_ptr<Model> model(new Model()) ;
          model->init() ;
          Object* o1 = model->createObject() ;
          Object* o2 = model->createObject() ;

          Link<Selection>(o1,o2) ;
        }

        CPPUNIT_ASSERT_EQUAL(1,SelectionView::m_number_of_close) ;
      }

      void TestRelationView::destroyModelShouldCloseRelationControlers()
      {
        SelectionControler::m_number_of_close = 0 ;
        {
          std::auto_ptr<Model> model(new Model()) ;
          model->init() ;
          Object* o1 = model->createObject() ;
          Object* o2 = model->createObject() ;

          Link<Selection>(o1,o2) ;
        }

        CPPUNIT_ASSERT_EQUAL(1,SelectionControler::m_number_of_close) ;
      }

      namespace Local7
      {
        class C7 : public RelationControler<RelationControlerSet>
        {
        protected:

          void onInit()
          {
            CPPUNIT_ASSERT(getRelation()) ;
          }
        };

        RegisterRelationControler(C7,BaseRelation,RelationControlerSet)
      }

      using namespace Local7 ;

      void TestRelationView::getRelation()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<BaseRelation>(o1,o2) ;
      }

      namespace Local8
      {
        class C8 : public RelationControler<RelationControlerSet>
        {
        public:

          void onInit()
          {
            m_inited = true ;
          }

          static bool m_inited ;

        };

        bool C8::m_inited = false ;

        RegisterRelationControler(C8,Relation,RelationControlerSet)
      }

      using namespace Local8 ;

      void TestRelationView::controllerOnGenericRelation()
      {

        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        C8::m_inited = false ;

        Link<Meta::Selection>(o1,o2) ;

        CPPUNIT_ASSERT(C8::m_inited) ;
      }

    }
  }
}

