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
#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <kernel/error.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {
      namespace Performance
      {
        
        /// Test of model/object/trait methods.
        class TestPerformanceModel : public CppUnit::TestFixture 
        {
        protected:
        /*! 
          @name Tests methods
        */
        // @{  
  
          void getUnexistingTraitOnEmptyObject() ;
          /// Test for Object::getTrait
          void getExistingTrait() ;
          void getUnexistingTraitOnFullObject() ;
          void updateFullObject() ;
          void updateDeducedTrait() ;
          void createDestroyObject() ;
          void addRemoveTrait() ;

          void updateSimpleTrait() ;
          /// Best case
          void updateTraitWithNoView() ;

          /// Worst case
          void updateTraitWithView() ;

        // @}
  
  
          CPPUNIT_TEST_SUITE(TestPerformanceModel) ;
  
          CPPUNIT_TEST(getUnexistingTraitOnEmptyObject) ;
          CPPUNIT_TEST(getExistingTrait) ;
          CPPUNIT_TEST(getUnexistingTraitOnFullObject) ;
          CPPUNIT_TEST(updateFullObject) ;
          CPPUNIT_TEST(updateDeducedTrait) ;
          CPPUNIT_TEST(createDestroyObject) ;
          CPPUNIT_TEST(addRemoveTrait) ;
          CPPUNIT_TEST(updateSimpleTrait) ;
          CPPUNIT_TEST(updateTraitWithNoView) ;
          CPPUNIT_TEST(updateTraitWithView) ;

          CPPUNIT_TEST_SUITE_END() ;
  
        };
      }
    }
  }
}
