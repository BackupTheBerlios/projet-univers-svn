/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2009 Mathieu ROGER                                 *
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

#include <string>

#define RLOG_COMPONENT "ProjetUnivers"

#include <rlog/rlog.h>
#include <rlog/StdioNode.h>
#include <rlog/RLogChannel.h>


namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Log
    {

    /*!
      @name Start/Close
    */
    // @{

      /// Init logging system.
      void init() ;

      /// Close logging system.
      void close() ;

      /// Current indentation level
      int getIndentation() ;

    // @}
    /*!
      @name Logging

      Log message are sent to modules.
      Logging on a module is activated through parameter file. @see Parameters.
    */
    // @{

      /// Send an error message.
      #define ErrorMessage(message) \
        rError(std::string(message).c_str())

      /// Send an information message from @c module.
      #define InformationMessage(module,message) \
        rLog(RLOG_CHANNEL(module),(std::string(ProjetUnivers::Kernel::Log::getIndentation(),' ') + std::string(message)).c_str())

      /// Send an internal message from @c module.
      #define InternalMessage(module,message) \
        rLog(RLOG_CHANNEL(module),(std::string(ProjetUnivers::Kernel::Log::getIndentation(),' ') + std::string(message)).c_str())

      /// Used as a local objects, produces enter/leave log messages.
      /*!
        @par Usage

        create a temporary variable in a function :
        Kernel::Log::Block temp("Module","function") ;

        will create a enter function/leave function message
      */
      class Block
      {
      public:
        Block(const std::string& module,const std::string& name) ;
        ~Block() ;
      private:

        std::string m_module ;
        std::string m_name ;
      };

      /// Log something to a file whose name is unique
      void logToFile(const std::string& content) ;


    // @}


    }
  }
}
