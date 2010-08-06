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
#ifndef PU_MODEL_TEST_WITH_TRANSITIONS_H_
#define PU_MODEL_TEST_WITH_TRANSITIONS_H_

#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers {
  namespace Model {
    namespace Test {


            
      /// Test of State.
      class TestState : public CppUnit::TestFixture {
      protected:
      
      /*!
        @name Test methods
      */
      // @{
        
        /// Transition to other state.
        void basicChangeState() ;

        /// Activate other state.
        void basicPushState() ;

        /// Desactivate other state.
        void basicPopState() ;
        
        /*!
              root
             /    \
         state1   state2
           |
         state3
        
         change state from state3 to state2
        */
        void uncleChangeState() ;
        
        /*!
              root
             /    \
         state1   state2
           |
         state3
        
         push state2 from state3
        */
        void unclePushState() ;
        
        /*!
                     root
                /  |    \     \
               /   |     \     \
              /    |      \     \
             /     |       \     \
         intro    menu    game   exit   
                  /  \     |
                 /    \  player
                /      \     
         input_config credits   
        
          change state from intro to menu
          push/pop state input_config (for editing)
          push/pop state credits
           
          menu push state game (for editing)
          menu change state game (for playing)
          game puch state menu (but in game menu)
          
          menu change state to exit
        */
        void realUsage() ;
        
        /// Declare a transition and triggers it.
        /*!
          @see basicChangeState
        */
        void changeTransitionDeclaration() ;
        
        /// Declare a transition and triggers it.
        /*!
          @see basicPushState
        */
        void pushTransitionDeclaration() ;

        /// Declare a transition and triggers it.
        /*!
          @see basicPopState
        */
        void popTransitionDeclaration() ;

        /// Validate that push twice the same state does not crash.
        void pushStateTwice() ;

        /// Validate that push on a state that have no active substate works.
        void pushOnEmptyState() ;
        
        /// Calling a command not understood by the state continue to other traits.
        void callUnexistingCommand() ;
        
      // @}
      /*!
        @name Test registration
      */
      // @{      
    
        CPPUNIT_TEST_SUITE(TestState) ;
      
        CPPUNIT_TEST(basicChangeState) ;
        CPPUNIT_TEST(basicPushState) ;
        CPPUNIT_TEST(basicPopState) ;
        CPPUNIT_TEST(uncleChangeState) ;
        CPPUNIT_TEST(unclePushState) ;
        CPPUNIT_TEST(realUsage) ;
        CPPUNIT_TEST(changeTransitionDeclaration) ;
        CPPUNIT_TEST(pushTransitionDeclaration) ;
        CPPUNIT_TEST(popTransitionDeclaration) ;
        CPPUNIT_TEST(pushStateTwice) ;
        CPPUNIT_TEST(pushOnEmptyState) ;
        CPPUNIT_TEST(callUnexistingCommand) ;
      
        CPPUNIT_TEST_SUITE_END() ;

      };

    }
  }
}


#endif /*PU_MODEL_TEST_WITH_TRANSITIONS_H_*/
