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
#include <kernel/exception_kernel.h>
#include <kernel/log.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {

    template <typename T>
    T Parameters::getValue(const std::string& section,
                           const std::string& name) 
    {
      if (! m_instance.get())
      {
        m_instance.reset(new Parameters()) ; 
      }
      
      return m_instance->internalGetValue<T>(section,name) ;

    }

    template <typename T>
    T Parameters::getValue(const std::string& section,
                           const std::string& name,
                           T default_value) 
    {
      try 
      {
        return getValue<T>(section,name) ;
      }
      catch(...)
      {
        return default_value ;
      }
    }
    
    template <typename T>
    T Parameters::internalGetValue(const std::string& section,
                                   const std::string& name) const
    {
      std::map<std::string,std::map<std::string,
        boost::variant<float,std::string,bool> > >::const_iterator 
        section_iterator = m_parameters.find(section) ;
      
      if (section_iterator == m_parameters.end())
      {
        ErrorMessage(std::string("no section named : ") + section) ;
        throw ExceptionKernel(std::string("no section named : ") + section) ;
      }
      
      std::map<std::string,
        boost::variant<float,std::string,bool> >::const_iterator 
        parameter = section_iterator->second.find(name) ;
      
      T result ;
        
      if (parameter != section_iterator->second.end())
      {
        result = boost::get<T>(parameter->second) ;
      }
      else
      {
        ErrorMessage(std::string("no parameter named : ") + name) ;
      	throw ExceptionKernel(std::string("no parameter named : ") + name) ;
      } 
      
      return result ;
    }
  }
}
