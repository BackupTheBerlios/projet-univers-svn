/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2008-2011 Mathieu ROGER                                 *
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

#include <sound/test/sound_test_fixture.h>

namespace ProjetUnivers
{
  namespace Sound
  {
    namespace Test
    {

      /// Test the sound event
      class TestSoundEvent : public SoundTestFixture
      {
      protected:
      /*!
        @name Tests
      */
      // @{

        void collision() ;
        void smallCollision() ;
        void farCollision() ;
        void shot() ;

      // @}
      /*!
        @name Register
      */
      // @{

        CPPUNIT_TEST_SUITE(TestSoundEvent) ;

        CPPUNIT_TEST(collision) ;
        CPPUNIT_TEST(smallCollision) ;
        CPPUNIT_TEST(farCollision) ;
        CPPUNIT_TEST(shot) ;

        CPPUNIT_TEST_SUITE_END() ;

      // @}
      } ;

    }
  }
}
