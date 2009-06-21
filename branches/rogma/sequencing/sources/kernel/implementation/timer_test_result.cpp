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
#include <kernel/timer_test_result.h>

CPPUNIT_NS_BEGIN

void TimerTestResult::startTest(Test* test)
{
  m_timer.reset() ;
}

void TimerTestResult::endTest(Test* test)
{
  m_results[test] = m_timer.getSecond() ;
}

float TimerTestResult::getResult(Test* test) const
{
  std::map<Test*,float>::const_iterator result = m_results.find(test) ;
  if (result != m_results.end())
  {
    return result->second ;
  }
  
  return 0 ;
}

CPPUNIT_NS_END
