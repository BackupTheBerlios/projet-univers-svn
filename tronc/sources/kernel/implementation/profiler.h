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
#include <kernel/timer.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {

      /// Allow profiling of code parts.
      /*!
        The following code will measure time taken between the startBlock and
        endBlock.
        @code
          ...
          Profiler::startBlock("foo") ;

          // some code here
          ...

          Profiler::endBlock() ;
        @endcode

        Profiling is costly so it can be activated or not. By default it is not
        activated.
        # reset() activates it
        # print() print results and desactivates it

      */
      class Profiler
      {
      public:

        /// Start a profiling block.
        static void startBlock(const std::string&) ;

        /// Ends the last profiling block.
        static void endBlock(const std::string& = "") ;

        /// Reset all profiling results and activate the profiling
        static void reset() ;

        /// Prints the profiling results to std::cout and desacttivate profiling
        static void print() ;

      private:

        /// An opened block
        class Block
        {
        public:

          std::string m_name ;
          Timer m_timer ;
        };

        /// Currently opened blocks
        static std::list<Block> m_openned_blocks ;

        /// Statistics of a "method".
        class Statistic
        {
        public:

          std::string m_name ;
          float m_total_elapsed_milliseconds ;
          float m_inner_milliseconds ;
          int m_number_of_calls ;

          /// current number of opened blocks with that name
          int m_number_of_openned ;
        };

        static std::map<std::string,Statistic> m_statistics ;

        static Statistic& getStatistic(const std::string& name) ;

        static unsigned int m_maximum_stack ;

        static bool m_activated ;
      };
    }
  }
}
