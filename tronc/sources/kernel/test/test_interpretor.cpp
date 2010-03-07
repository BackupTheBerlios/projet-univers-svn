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
#include <kernel/trait.h>
#include <kernel/object.h>
#include <kernel/model.h>
#include <kernel/view_point.h>
#include <kernel/trait_view.h>
#include <kernel/implementation/interpretor.h>
#include <kernel/test/test_interpretor.h>
#include <kernel/deduced_trait.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::Kernel::Test::TestInterpretor) ;

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {

      namespace InterpretorModel
      {
        class T1 : public Trait
        {
        public:

          void touch()
          {
            notify() ;
          }
        };

        class ViewPoint1 : public ViewPoint
        {
        public:
          ViewPoint1(Model* model)
          :ViewPoint(model)
          {}

        };

        class V1 : public TraitView<T1,ViewPoint1>
        {
        public:

          virtual void onUpdate()
          {
            ++number_of_update ;
          }

          static int number_of_update ;
        };

        RegisterView(V1,T1,ViewPoint1) ;

        int V1::number_of_update ;

        class T2 : public DeducedTrait
        {};

        DeclareDeducedTrait(T2,HasTrait(T1)) ;

        class V2 : public TraitView<T1,ViewPoint1>
        {
        public:

          virtual void onUpdate()
          {
            ++number_of_update ;
          }

          static int number_of_update ;
        };

        RegisterView(V2,T2,ViewPoint1) ;

        int V2::number_of_update ;
      }

      void TestInterpretor::addingTraitOnADestroyedObject()
      {
        using namespace InterpretorModel ;

        std::auto_ptr<Model> model(new Model()) ;

        Kernel::Object* object = model->createObject() ;
        Kernel::Object* object2 = object->createObject() ;

        model->startTransaction() ;

        object->destroyObject() ;
        object2->addTrait(new T1()) ;

        // even if the object is to be destroyed we should add it
        CPPUNIT_ASSERT(object2->getTrait<T1>()) ;

        model->endTransaction() ;
      }

      void TestInterpretor::updatingSeveralTimesSameTraitOnlyUpdateOnce()
      {
        using namespace InterpretorModel ;

        std::auto_ptr<Model> model(new Model()) ;
        ViewPoint* viewpoint(model->addViewPoint(new ViewPoint1(model.get()))) ;
        // init the viewpoint
        viewpoint->init() ;

        Kernel::Object* object = model->createObject() ;
        object->addTrait(new T1()) ;

        V1::number_of_update = 0 ;

        model->startTransaction() ;

        object->getTrait<T1>()->touch() ;
        object->getTrait<T1>()->touch() ;

        model->endTransaction() ;

        CPPUNIT_ASSERT_EQUAL(1,V1::number_of_update) ;
      }

      void TestInterpretor::updatingSeveralTimesSameTraitOnlyUpdateOnceDeducedTraitViews()
      {
        using namespace InterpretorModel ;

        std::auto_ptr<Model> model(new Model()) ;
        ViewPoint* viewpoint(model->addViewPoint(new ViewPoint1(model.get()))) ;
        // init the viewpoint
        viewpoint->init() ;

        Kernel::Object* object = model->createObject() ;
        object->addTrait(new T1()) ;

        V2::number_of_update = 0 ;

        model->startTransaction() ;

        object->getTrait<T1>()->touch() ;
        object->getTrait<T1>()->touch() ;

        model->endTransaction() ;

        CPPUNIT_ASSERT_EQUAL(1,V2::number_of_update) ;
      }
      
    }
  }
}

