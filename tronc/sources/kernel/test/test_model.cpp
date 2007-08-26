/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER                                 *
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
#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/trait_view.h>
#include <kernel/view_point.h>

#include <kernel/test/test_model.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Kernel::Test::TestModel) ;

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {


      /// local classes
      namespace
      {
        
        class Head : public Trait
        {
        public:
        
          Head()
          : Trait(), value(0)
          {}
        
          void change(const int& i_new_value) 
          {
            value = i_new_value ;
            notify() ;
          }  
          
          int getValue() const
          {
            return value ;
          }
          
        private:
        
          int value ;
          
        };
        
        class Person : public Trait
        {
        public:
        
          Person()
          : Trait(), value(0)
          {}
        
          void changeValue(const int& i_new_value) 
          {
            value = i_new_value ;
            notify() ;
          }  
          
          int getValue() const
          {
            return value ;
          }
          
        private:
        
          int value ;
          
        };

        class Dummy : public Trait
        {
        public:
        
          Dummy()
          : Trait(), value(0)
          {}
        
          void changeValue(const int& i_new_value) 
          {
            value = i_new_value ;
            notify() ;
          }  
          
          int getValue() const
          {
            return value ;
          }
          
        private:
        
          int value ;
          
        };
  
      }
      
      void TestModel::testGetDescendants()
      {
        /// create a model
        std::auto_ptr<Model> model(new Model("TestModel::testGetDescendants")) ;

        //// fill the model
        Object* person = model->createObject("person") ;
        model->addTrait(person,new Person()) ;
        
        // create several heads
        {
          Object* head = model->createObject(person) ;
          model->addTrait(head,new Head()) ;
          
          head = model->createObject(head) ;
          model->addTrait(head,new Head()) ;
          
        }
        
        {
          Object* head = model->createObject(person) ;
          model->addTrait(head,new Head()) ;
        }        

        std::set<Head*> heads = person->getDescendants<Head>() ;
        
        CPPUNIT_ASSERT(heads.size() == 3) ;
        
      }

      void TestModel::setUp()
      {
      }
      
      void TestModel::tearDown()
      {
      }

    }
  }
}
