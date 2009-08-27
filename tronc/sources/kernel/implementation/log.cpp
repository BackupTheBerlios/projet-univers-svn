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
#include <stdio.h>
#include <memory>
#include <kernel/parameters.h>
#include <kernel/string.h>
#include <kernel/log.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Log
    {
      int indentation = 0 ;

      int getIndentation()
      {
        return indentation*2 ;
      }

      const std::string errorFileName("error.log") ;
      std::auto_ptr<rlog::StdioNode> errorLog ;
      FILE* error ;

      const std::string debugFileName("debug.log") ;
      std::auto_ptr<rlog::StdioNode> debugLog ;
      FILE* debug ;

      void init()
      {
      #ifndef NDEBUG

        // error
        error = fopen(errorFileName.c_str(), "w") ;
        errorLog.reset(new rlog::StdioNode(fileno(error))) ;

        errorLog->subscribeTo( rlog::GetGlobalChannel( "error" ));

        // debug
        debug = fopen(debugFileName.c_str(), "w") ;
        debugLog.reset(new rlog::StdioNode(fileno(debug))) ;
        debugLog->subscribeTo( rlog::GetGlobalChannel( "error" ));

        std::set<std::string> logs(Parameters::getActivatedLogs()) ;

        for(std::set<std::string>::const_iterator log = logs.begin() ;
            log != logs.end() ;
            ++log)
        {
          debugLog->subscribeTo(rlog::GetGlobalChannel(log->c_str()));
        }

      #endif
      }

      void close()
      {
      #ifndef NDEBUG
        fclose(debug) ;
        fclose(error) ;
      #endif
      }

      Block::Block(const std::string& module,const std::string& name)
      : m_module(module),
        m_name(name)
      {
        InternalMessage(m_module.c_str(),std::string("Entering [") + m_module +"] " + m_name) ;
        ++indentation ;
      }

      Block::~Block()
      {
        --indentation ;
        InternalMessage(m_module.c_str(),std::string("Leaving [") + m_module +"] " + m_name) ;
      }

      namespace
      {
        int number = 0 ;
      }

      void logToFile(const std::string& content)
      {
        std::string filename("temp" + Kernel::toString(number++) + ".log") ;
        std::ofstream file(filename.c_str()) ;

        file << content ;

        file.close() ;
      }

    }
  }
}
