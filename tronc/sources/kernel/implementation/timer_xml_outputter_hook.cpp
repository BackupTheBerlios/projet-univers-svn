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

#include <cppunit/tools/XmlElement.h>
#include <kernel/timer_test_result.h>
#include <kernel/timer_xml_outputter_hook.h>
#include <kernel/string.h>

CPPUNIT_NS_BEGIN

TimerXmlOutputterHook::TimerXmlOutputterHook(TimerTestResult* result)
: m_result(result)
{}
  
void TimerXmlOutputterHook::successfulTestAdded(XmlDocument* document,
                                                XmlElement* testElement,
                                                Test* test)
{
  testElement->addAttribute("duration",ProjetUnivers::Kernel::toString(m_result->getResult(test))) ;
}
  
CPPUNIT_NS_END
