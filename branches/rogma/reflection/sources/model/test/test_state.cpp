/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2008 Mathieu ROGER                                 *
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
#include <kernel/model.h>
#include <kernel/object.h>

#include <model/state.h>
#include <model/active.h>
#include <model/test/test_state.h>


CPPUNIT_TEST_SUITE_REGISTRATION(ProjetUnivers::
                                Model::
                                Test::
                                TestState) ;

namespace ProjetUnivers {
  namespace Model {
    namespace Test {

      void TestState::basicChangeState()
      {
        InternalMessage("Model","Model::TestState::basicChangeState entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->addTrait(new State()) ;

        root->getTrait<State>()->changeState(state1,new Active()) ;
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;

        InternalMessage("Model","Model::TestState::basicChangeState#1") ;
        // tested method
        state1->getTrait<State>()->changeState(state2,new Active()) ;
        
        CPPUNIT_ASSERT(!state1->getTrait<Active>()) ;
        CPPUNIT_ASSERT(state2->getTrait<Active>()) ;
      }

      void TestState::basicPushState()
      {
        InternalMessage("Model","Model::TestState::basicPushState entering") ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->addTrait(new State()) ;

        root->getTrait<State>()->changeState(state1,new Active()) ;
        
        // tested method
        state1->getTrait<State>()->pushState(state2,new Active()) ;
        
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;
        CPPUNIT_ASSERT(state2->getTrait<Active>()) ;
      }

      void TestState::basicPopState()
      {
        InternalMessage("Model","Model::TestState::basicPopState entering") ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->addTrait(new State()) ;

        root->getTrait<State>()->changeState(state1,new Active()) ;
        state1->getTrait<State>()->pushState(state2,new Active()) ;
        
        // tested method
        root->getTrait<State>()->popState() ;
        
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;
        CPPUNIT_ASSERT(!state2->getTrait<Active>()) ;
      }

      void TestState::uncleChangeState()
      {
        InternalMessage("Model","Model::TestState::basicChangeState entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state3 = state1->createObject() ;
        state3->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->addTrait(new State()) ;

        root->getTrait<State>()->changeState(state1,new Active()) ;
        state1->getTrait<State>()->pushState(state3,new Active()) ;
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;
        CPPUNIT_ASSERT(state3->getTrait<Active>()) ;

        // tested method
        state3->getTrait<State>()->changeState(state2,new Active()) ;
        
        CPPUNIT_ASSERT(!state3->getTrait<Active>()) ;
        CPPUNIT_ASSERT(!state1->getTrait<Active>()) ;
        CPPUNIT_ASSERT(state2->getTrait<Active>()) ;
      }
      
      void TestState::unclePushState()
      {
        InternalMessage("Model","Model::TestState::basicChangeState entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state3 = state1->createObject() ;
        state3->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->addTrait(new State()) ;

        state1->getTrait<State>()->pushState(state3,new Active()) ;
        CPPUNIT_ASSERT(state3->getTrait<Active>()) ;

        // tested method
        state3->getTrait<State>()->pushState(state2,new Active()) ;
        
        CPPUNIT_ASSERT(state3->getTrait<Active>()) ;
        CPPUNIT_ASSERT(state2->getTrait<Active>()) ;
      }
      
      void TestState::realUsage()
      {
        InternalMessage("Model","Model::TestState::basicChangeState entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* intro = root->createObject() ;
        intro->addTrait(new State()) ;
        
        Kernel::Object* menu = root->createObject() ;
        menu->addTrait(new State()) ;

        Kernel::Object* game = root->createObject() ;
        game->addTrait(new State()) ;
        
        Kernel::Object* exit = root->createObject() ;
        exit->addTrait(new State()) ;

        Kernel::Object* input_config = menu->createObject() ;
        input_config->addTrait(new State()) ;
        
        Kernel::Object* credits = menu->createObject() ;
        credits->addTrait(new State()) ;
        
        Kernel::Object* player = game->createObject() ;
        player->addTrait(new State()) ;
        
        // transitions
        root->getTrait<State>()->changeState(intro,new Active()) ;
        CPPUNIT_ASSERT(intro->getTrait<Active>()) ;
        
        intro->getTrait<State>()->changeState(menu,new Active()) ;
        CPPUNIT_ASSERT(!intro->getTrait<Active>()) ;
        CPPUNIT_ASSERT(menu->getTrait<Active>()) ;
        
        menu->getTrait<State>()->pushState(credits,new Active()) ;
        CPPUNIT_ASSERT(menu->getTrait<Active>()) ;
        CPPUNIT_ASSERT(credits->getTrait<Active>()) ;
        
        menu->getTrait<State>()->popState() ;
        CPPUNIT_ASSERT(menu->getTrait<Active>()) ;
        CPPUNIT_ASSERT(!credits->getTrait<Active>()) ;

        menu->getTrait<State>()->pushState(game,new Active()) ;
        CPPUNIT_ASSERT(menu->getTrait<Active>()) ;
        CPPUNIT_ASSERT(game->getTrait<Active>()) ;
        
        game->getTrait<State>()->changeState(game,new Active()) ;
        CPPUNIT_ASSERT(!menu->getTrait<Active>()) ;
        CPPUNIT_ASSERT(game->getTrait<Active>()) ;

        game->getTrait<State>()->pushState(menu,new Active()) ;
        CPPUNIT_ASSERT(menu->getTrait<Active>()) ;
        CPPUNIT_ASSERT(game->getTrait<Active>()) ;
        
        root->getTrait<State>()->popState() ;
        CPPUNIT_ASSERT(!menu->getTrait<Active>()) ;
        CPPUNIT_ASSERT(game->getTrait<Active>()) ;
      }
  
      void TestState::changeTransitionDeclaration()
      {
        InternalMessage("Model","Model::TestState::changeTransitionDeclaration entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->setName("state2") ;
        state2->addTrait(new State()) ;

        root->getTrait<State>()->changeState(state1,new Active()) ;
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;

        // tested method
        state1->call("change(state2,Active)") ;
        
        CPPUNIT_ASSERT(!state1->getTrait<Active>()) ;
        CPPUNIT_ASSERT(state2->getTrait<Active>()) ;
      }
      
      void TestState::pushTransitionDeclaration()
      {
        InternalMessage("Model","Model::TestState::pushTransitionDeclaration entering") ;
        
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->setName("state2") ;
        state2->addTrait(new State()) ;

        root->getTrait<State>()->changeState(state1,new Active()) ;
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;
        
        // tested method
        state1->call("push(state2,Active)") ;
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;
        CPPUNIT_ASSERT(state2->getTrait<Active>()) ;
      }

      void TestState::popTransitionDeclaration()
      {
        InternalMessage("Model","Model::TestState::popTransitionDeclaration entering") ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->addTrait(new State()) ;

        root->getTrait<State>()->changeState(state1,new Active()) ;
        state1->getTrait<State>()->pushState(state2,new Active()) ;
        
        // tested method
        state2->call("pop()") ;
        
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;
        CPPUNIT_ASSERT(!state2->getTrait<Active>()) ;
      }
      
      void TestState::pushStateTwice()
      {
        InternalMessage("Model","Model::TestState::basicPushState entering") ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->addTrait(new State()) ;

        root->getTrait<State>()->changeState(state1,new Active()) ;
        
        // tested method
        state1->getTrait<State>()->pushState(state2,new Active()) ;
        state1->getTrait<State>()->pushState(state2,new Active()) ;
        
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;
        CPPUNIT_ASSERT(state2->getTrait<Active>()) ;
      }

      void TestState::pushOnEmptyState()
      {
        InternalMessage("Model","Model::TestState::basicPushState entering") ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;
        
        Kernel::Object* state1 = root->createObject() ;
        state1->addTrait(new State()) ;
        
        Kernel::Object* state2 = root->createObject() ;
        state2->addTrait(new State()) ;

        // tested method
        root->getTrait<State>()->pushState(state1,new Active()) ;
        CPPUNIT_ASSERT(state1->getTrait<Active>()) ;
      }
      
      namespace 
      {
        class Dummy : public Kernel::Trait
        {
        public:
          
          Dummy()
          : m_executed(false)
          {}
          
          void execute()
          {
            m_executed = true ;
          }
          
          bool m_executed ;
        };
        
        RegisterCommand("execute",Dummy,execute) ;
      }
      
      void TestState::callUnexistingCommand()
      {
        InternalMessage("Model","Model::TestState::callUnexistingCommand entering") ;
        std::auto_ptr<Kernel::Model> model(new Kernel::Model()) ;
        
        Kernel::Object* root = model->createObject() ;
        root->addTrait(new State()) ;

        Kernel::Object* child = root->createObject() ;
        child->addTrait(new Dummy()) ;
        
        root->call("execute") ;
        
        CPPUNIT_ASSERT(child->getTrait<Dummy>()->m_executed) ;
        
      }
    }
  }
}

