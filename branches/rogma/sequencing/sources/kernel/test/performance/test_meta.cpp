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
#include <iostream>
#include <kernel/exception.h>
#include <kernel/model.h>
#include <kernel/object.h>
#include <kernel/timer.h>

#include <kernel/test/performance/model.h>
#include <kernel/test/performance/test_meta.h>

CPPUNIT_TEST_SUITE_REGISTRATION(
  ProjetUnivers::Kernel::Test::Performance::TestMeta) ;

namespace ProjetUnivers 
{
  namespace Kernel 
  {
    namespace Test 
    {
      namespace Performance
      {
        void TestMeta::comparison()
        {
          const unsigned int number = 1000000 ;
          
          TypeIdentifier a(getClassTypeIdentifier(A)) ;
          TypeIdentifier b(getClassTypeIdentifier(B)) ;
          
          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            b < a ;
          }
        }

        void TestMeta::getClassIdentifier()
        {
          const unsigned int number = 1000000 ;

          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            TypeIdentifier a(getClassTypeIdentifier(A)) ;
          }
        }
        
        void TestMeta::getTypeId()
        {
          const unsigned int number = 1000000 ;

          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            typeid(A) ;
          }
        }
        
        void TestMeta::typeInfoBefore()
        {
          const unsigned int number = 1000000 ;
          const std::type_info& a = typeid(A) ;
          const std::type_info& b = typeid(B) ;
          for(unsigned int i = 1 ; i <= number ; ++i)
          {
            b.before(a) ;
          }
          
        }
        
        
      }
    }
  }
}
