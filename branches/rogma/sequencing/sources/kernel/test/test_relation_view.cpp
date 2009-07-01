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

#include <kernel/test/test_relation_view.h>
#include <kernel/view_point.h>

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
        {};

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

        DeducedSelectionView::m_number_of_close = 0 ;
        o2->destroyTrait(o2->getTrait<T2>()) ;
        CPPUNIT_ASSERT_EQUAL(1,DeducedSelectionView::m_number_of_close) ;
      }


    }
  }
}

