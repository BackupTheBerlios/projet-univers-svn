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
#include <cppunit/Test.h>
#include <cppunit/tools/XmlElement.h>
#include <kernel/timer_test_result.h>
#include <kernel/timer_xml_outputter_hook.h>
#include <kernel/string.h>

CPPUNIT_NS_BEGIN



TimerXmlOutputterHook::TimerXmlOutputterHook(TimerTestResult* result)
: m_result(result)
{}
  
void TimerXmlOutputterHook::successfulTestAdded(XmlDocument*,
                                                XmlElement* testElement,
                                                Test* test)
{
  testElement->addAttribute("time",ProjetUnivers::Kernel::toString(m_result->getResult(test))) ;
  
  std::string name(test->getName()) ;
  std::string classname ;
  std::string::size_type previous = 0 ;
  
  for(std::string::size_type position = name.find("::") ; 
      position != std::string::npos ;
      previous=position+2,position = name.find("::",position+2))
  {
    if (!classname.empty())
      classname += "." ;
    
    classname += name.substr(previous,position-previous) ;
  }
  
  testElement->addAttribute("name",name.substr(previous)) ;
  testElement->addAttribute("classname",classname) ;
}
  
CPPUNIT_NS_END
