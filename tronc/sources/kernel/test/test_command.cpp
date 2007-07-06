/***************************************************************************
 *   Copyright (C) 2004 by Projet Univers                                  *
 *   rogma.boami@free.fr                                                   *
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

#include <kernel/log.h>
#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/trait_view.h>
#include <kernel/view_point.h>
#include <kernel/deduced_trait.h>

#include <kernel/test/test_command.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
    ProjetUnivers::Kernel::Test::TestCommand) ;

namespace ProjetUnivers {
  namespace Kernel {
    namespace Test {

      /// local classes
      namespace
      {
        class Trait1 : public Trait
        {
        public:
        
          Trait1()
          : Trait(), 
            value(0)
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

        class Trait2 : public Trait
        {
        public:
        
          Trait2()
          : Trait(), 
            value(0),
            m_pushed(false)
          {}
        
          void push()
          {
            m_pushed = true ;
          }
          
          bool isPushed()
          {
            return m_pushed ;
          }
          
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
          bool m_pushed ;
        };
        
        class Trait3 : public Trait
        {
        public:
        
          Trait3()
          : Trait(), 
            value(0)
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

      }
      
      void TestCommand::basicTest()
      {
        InternalMessage("Kernel::Test::TestCommand::basicTest entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;
                                    
        //// fill the model
        Object* object = model->createObject("object") ;
        
        {
          Trait1* trait = new Trait1() ;
          trait->addAxis<Trait1>("axis1",&Trait1::change) ;
          model->addTrait(object,trait) ;
          
          CPPUNIT_ASSERT(object->call("axis1",10)) ;
          CPPUNIT_ASSERT(trait->getValue()==10) ;
          
          std::set<std::string> commands(object->getCommands()) ;
          
          CPPUNIT_ASSERT(commands.size() == 1) ;
        }        
        
        {
          Trait2* trait = new Trait2() ;
          trait->addCommand<Trait2>("push",&Trait2::push) ;
          model->addTrait(object,trait) ;
          
          CPPUNIT_ASSERT(! trait->isPushed()) ;
          CPPUNIT_ASSERT(object->call("push")) ;
          CPPUNIT_ASSERT(trait->isPushed()) ;
          
          std::set<std::string> commands(object->getCommands()) ;
          CPPUNIT_ASSERT(commands.size() == 2) ;

          trait->addAxis<Trait2>("axis2",&Trait2::change) ;
        
          CPPUNIT_ASSERT(object->getCommands().size() == 3) ;
          
        
        }        
        
        InternalMessage("Kernel::Test::TestCommand::basicTest leaving") ;
      }
      
      void TestCommand::setUp()
      {
      }

      void TestCommand::tearDown()
      {
      }

 
       
       
    }
  }
}
