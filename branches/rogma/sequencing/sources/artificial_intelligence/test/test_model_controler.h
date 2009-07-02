/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2009 Mathieu ROGER                                 *
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
#pragma once


#include <cppunit/extensions/HelperMacros.h>

namespace ProjetUnivers
{
  namespace ArtificialIntelligence
  {
    namespace Test
    {


      ///  Test for AI building.
      class TestModelControler : public CppUnit::TestFixture
      {
      protected:
      /*!
        @name Tests methods
      */
      // @{

        /// Tests basic simulation.
        void simulate() ;

        /// Tests construction with lack of elements.
        void buildWithoutElements() ;

        /// Test a AttackAllEnemy behaviour.
        /*!
          A complete test with own main loop including model, physic and ai.
          A ship pursuit an ennemy.
        */
        void attackAllEnemies() ;

        /// Two agents attacking each other.
        void twoShips() ;

        /// Two teams attacking each other
        /*!
          Foirst team must win because they are twice 2 against 1
        */
        void groupAttack() ;

        /// Test the updating of the positions.
        void testPositionUpdate() ;

        void testMission() ;

        /// Check that correct steering is calculated
        void steering() ;

      // @}


        CPPUNIT_TEST_SUITE(TestModelControler) ;

        CPPUNIT_TEST(buildWithoutElements) ;
        CPPUNIT_TEST(attackAllEnemies) ;
        CPPUNIT_TEST(twoShips) ;
        CPPUNIT_TEST(groupAttack) ;
        CPPUNIT_TEST(testPositionUpdate) ;
        CPPUNIT_TEST(simulate) ;
        CPPUNIT_TEST(steering) ;

        CPPUNIT_TEST_SUITE_END() ;
      };
    }
  }
}



