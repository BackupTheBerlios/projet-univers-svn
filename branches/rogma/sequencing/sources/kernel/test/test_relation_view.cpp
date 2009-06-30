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

          SelectionView(RelationViewPoint* viewpoint)
          : RelationView<RelationViewPoint>(viewpoint)
          {}
        };

        RegisterRelationView(SelectionView,Selection,RelationViewPoint) ;
      }

      void TestRelationView::test()
      {
        std::auto_ptr<Model> model(new Model()) ;
        model->init() ;
        Object* o1 = model->createObject() ;
        Object* o2 = model->createObject() ;

        Link<Selection>(o1,o2) ;
        std::set<Object*> related(Relation::getLinked<Selection>(o1)) ;
        CPPUNIT_ASSERT(related.find(o2) != related.end()) ;
        CPPUNIT_ASSERT(related.size() == 1) ;
      }
    }
  }
}

