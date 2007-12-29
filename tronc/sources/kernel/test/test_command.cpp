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
#include <iostream>

#include <kernel/log.h>
#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/trait.h>
#include <kernel/trait_view.h>
#include <kernel/view_point.h>
#include <kernel/deduced_trait.h>
#include <kernel/command_delegator.h>

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
        
        /// command registration
        RegisterAxis("axis1",Trait1,change) ;

        RegisterFunction("function1",Trait1,getValue) ;

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
        
        /// registration
        RegisterCommand("push",Trait2,push) ;
        RegisterAxis("axis2",Trait2,change) ;

        RegisterFunction("function1",Trait2,getValue) ;
        
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

        RegisterFunction("function1",Trait3,getValue) ;
      }
      
      void TestCommand::basicTest()
      {
        InternalMessage("Kernel","Kernel::Test::TestCommand::basicTest entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;
                                    
        //// fill the model
        Object* object = model->createObject("object") ;
        
        {
          Trait1* trait = new Trait1() ;
          model->addTrait(object,trait) ;
          
          CPPUNIT_ASSERT(object->call("axis1",10)) ;
          CPPUNIT_ASSERT(trait->getValue()==10) ;
          
          std::set<std::string> commands(object->getCommands()) ;
          
          CPPUNIT_ASSERT(commands.size() == 1) ;
        }        
        
        {
          Trait2* trait = new Trait2() ;
          model->addTrait(object,trait) ;
          
          CPPUNIT_ASSERT(! trait->isPushed()) ;
          CPPUNIT_ASSERT(object->call("push")) ;
          CPPUNIT_ASSERT(trait->isPushed()) ;
          
          std::set<std::string> commands(object->getCommands()) ;
          CPPUNIT_ASSERT(commands.size() == 3) ;
          
        
        }        
        
        InternalMessage("Kernel","Kernel::Test::TestCommand::basicTest leaving") ;
      }

      void TestCommand::testCommandDelegator()
      {
        InternalMessage(
          "Kernel",
          "Kernel::Test::TestCommand::testCommandDelegator entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;
                                    
        //// fill the model
        Object* object = model->createObject("object") ;
        Trait1* trait1 = new Trait1() ;
        model->addTrait(object,trait1) ;
        Trait2* trait2 = new Trait2() ;
        model->addTrait(object,trait2) ;
        
        Object* object2 = model->createObject("object2") ;
        CommandDelegator* delegator = new CommandDelegator() ;
        model->addTrait(object2,delegator) ;
        
        delegator->addDelegate(object) ;
        
        CPPUNIT_ASSERT(object2->call("axis1",10)) ;
        CPPUNIT_ASSERT(trait1->getValue()==10) ;
          
        CPPUNIT_ASSERT(! trait2->isPushed()) ;
        CPPUNIT_ASSERT(object2->call("push")) ;
        CPPUNIT_ASSERT(trait2->isPushed()) ;
          
        std::set<std::string> commands(object2->getCommands()) ;
        CPPUNIT_ASSERT(commands.size() == 3) ;
        
        InternalMessage("Kernel","Kernel::Test::TestCommand::testCommandDelegator leaving") ;
      }

      void TestCommand::testFunctionCall()
      {
        InternalMessage(
          "Kernel",
          "Kernel::Test::TestCommand::testFunctionCall entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;
                                    
        //// fill the model
        Object* object = model->createObject("object") ;
        Trait1* trait1 = new Trait1() ;
        model->addTrait(object,trait1) ;
        CPPUNIT_ASSERT(object->callFunction<int>("function1") == 0);        
        
        object->getTrait<Trait1>()->change(10) ;
        CPPUNIT_ASSERT(object->callFunction<int>("function1") == 10);        
        
        model->addTrait(object,new Trait2()) ;
        model->destroyTrait(object,trait1) ;
        
        object->getTrait<Trait2>()->change(50) ;
        CPPUNIT_ASSERT(object->callFunction<int>("function1") == 50);        
        
        InternalMessage(
          "Kernel",
          "Kernel::Test::TestCommand::testFunctionCall leaving") ;
      }

      void TestCommand::testFunctionCallErrorCases()
      {
        InternalMessage(
          "Kernel",
          "Kernel::Test::TestCommand::testFunctionCallErrorCases entering") ;
        /// create a model
        std::auto_ptr<Model> model(new Model()) ;

        //// fill the model
        Object* object = model->createObject("object") ;
        
        /// test unexisting function
        try
        {
          object->callFunction<int>("function1") ;
          CPPUNIT_ASSERT(false) ;
        }
        catch(const std::exception&)
        {
          CPPUNIT_ASSERT(true) ;
        }
        catch(...)
        {
          CPPUNIT_ASSERT(false) ;
        }

        /// test bad cast call
        try
        {
          object->callFunction<std::string>("function1") ;
          CPPUNIT_ASSERT(false) ;
        }
        catch(const boost::bad_any_cast&)
        {
          CPPUNIT_ASSERT(true) ;
        }
        catch(...)
        {
          CPPUNIT_ASSERT(false) ;
        }
        
        InternalMessage(
          "Kernel",
          "Kernel::Test::TestCommand::testFunctionCallErrorCases leaving") ;
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
