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
#include <kernel/implementation/debugger.h>

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

#ifdef _WIN32
#  include <io.h>
#  define write(fd, buf, n) _write((fd), (buf), static_cast<unsigned>(n))
#else
#  include <unistd.h>

using ProjetUnivers::Kernel::Implementation::Debugger;
#endif

      /// Specialized log node
      class LogNode : public rlog::RLogNode
      {
      public:

        LogNode(int _fdOut = 2)
        : fdOut( _fdOut )
        {}

        void subscribeTo(rlog::RLogNode *node)
        {
          addPublisher(node) ;
          node->isInterested(this, true) ;
        }

      protected:

        /// Prints only channel and message
        virtual void publish(const rlog::RLogData &data)
        {

          std::ostringstream ss ;

          ss << '[' << data.publisher->channel->name() << "] " ;

          ss << data.msg ;

          ss << '\n' ;

          std::string out = ss.str() ;
          write(fdOut, out.c_str(), out.length()) ;
        }

        LogNode(const LogNode &) ;
        LogNode &operator =(const LogNode &) ;

        int fdOut ;

      } ;



      const std::string errorFileName("error.log") ;
      std::auto_ptr<LogNode> errorLog ;
      FILE* error ;

      const std::string debugFileName("debug.log") ;
      std::auto_ptr<LogNode> debugLog ;
      FILE* debug ;

      std::set<std::string> logs ;

      void init()
      {
      #ifndef NDEBUG

        // error
        error = fopen(errorFileName.c_str(), "w") ;
        errorLog.reset(new LogNode(fileno(error))) ;

        errorLog->subscribeTo( rlog::GetGlobalChannel( "error" ));

        // debug
        debug = fopen(debugFileName.c_str(), "w") ;
        debugLog.reset(new LogNode(fileno(debug))) ;
        debugLog->subscribeTo( rlog::GetGlobalChannel( "error" ));

        logs = Parameters::getActivatedLogs() ;
        for(std::set<std::string>::const_iterator log = logs.begin() ;
            log != logs.end() ;
            ++log)
        {
          debugLog->subscribeTo(rlog::GetGlobalChannel(log->c_str()));
        }

        // debugger activation
        if (Parameters::getValue<bool>("Kernel","debug",false))
        {
          Debugger::getDebugger().activate() ;
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
        if (logs.find(m_module) != logs.end())
        {
          std::string message("[" + m_module + "] " + std::string(ProjetUnivers::Kernel::Log::getIndentation(),' ') + "Entering " + m_name + "\n") ;
          write(fileno(debug),message.c_str(),message.length()) ;
          ++indentation ;
        }
      }

      Block::~Block()
      {
        if (logs.find(m_module) != logs.end())
        {
          --indentation ;
          std::string message("[" + m_module + "] " + std::string(ProjetUnivers::Kernel::Log::getIndentation(),' ') + "Leaving " + m_name + "\n") ;
          write(fileno(debug),message.c_str(),message.length()) ;
        }
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
