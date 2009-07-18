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
#include <fstream>
#include <kernel/parameters.h>

namespace ProjetUnivers 
{
  namespace Kernel 
  {

    std::auto_ptr<Parameters> Parameters::m_instance(NULL) ;

    void Parameters::reset()
    {
      m_instance.reset() ;
    }
    
    void Parameters::load(const std::string& file_path)
    {
      if (! m_instance.get())
      {
        m_instance.reset(new Parameters()) ; 
      }
      
      m_instance->internal_load(file_path) ;
    }

    void Parameters::internal_load(const std::string& file_path)
    {
      // open file and read it
      std::ifstream file(file_path.c_str()) ;
      
      if (file)
      {
        std::string section ;
        
        while (! file.eof())
        {
          char line_buffer[500] ;
          std::string line ;
          file.getline(line_buffer,sizeof(line_buffer)) ;
          line = line_buffer ;
          
          std::string name ;
          std::string value ;
          float numeric_value = 0 ;
          std::string::size_type finder ;
          
          switch (line[0])
          {
          case '[':
            // start section
            finder = line.find(']') ;
            section = line.substr(1,finder-1) ;
            
            break ;
          case '/':
            // comment
            break ;
          default:
            // parameter 
            finder = line.find('=') ;
            name = line.substr(0,finder) ;
            value = line.substr(finder+1,line.size()-finder-1) ;
            
            switch(value[0])
            {
            case '"':
              // a string 
              m_parameters[section][name] = value.substr(1,value.size()-2) ;
              break ;
            case 't':
              // consider it true
              m_parameters[section][name] = true ;
              break ;
            case 'f':
              // consider it true
              m_parameters[section][name] = false ;
              break ;
            default:
              // try numeric
              numeric_value = atof(value.c_str()) ;
              m_parameters[section][name] = numeric_value ;
            }
            
            break ;
          }          
          
        }
      }
      else
      {
        // file does not exists
        ErrorMessage("Kernel::Parameters : file " + file_path + "does not exists") ;
      }
      
    }
    
    std::set<std::string> Parameters::getActivatedLogs()
    {
      std::set<std::string> result ;
      
      if (! m_instance.get())
      {
        return result ;
      }
      
      for(std::map<
            std::string,
            std::map<
              std::string,
              boost::variant<
                float,
                std::string,
                bool> > >::const_iterator parameter = m_instance->m_parameters.begin() ;
          parameter != m_instance->m_parameters.end() ;
          ++parameter)
      {
        std::map<std::string,boost::variant<float,std::string,bool> >::const_iterator 
          finder = parameter->second.find("log") ;
        
        if (finder != parameter->second.end())
        {
          if (boost::get<bool>(finder->second))
          {
            result.insert(parameter->first) ;
          }
        }
      }
      
      return result ;
    }
  }
}
