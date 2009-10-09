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

#include <kernel/implementation/profiler.h>

namespace ProjetUnivers
{
  namespace Kernel
  {
    namespace Implementation
    {

      std::list<Profiler::Block> Profiler::m_openned_blocks ;
      std::map<std::string,Profiler::Statistic> Profiler::m_statistics ;
      unsigned int Profiler::m_maximum_stack = 0 ;
      bool Profiler::m_activated = false ;
      std::map<std::string,Profiler::NotifyStatistic> Profiler::m_notify_statistics ;
      std::string Profiler::m_current_notify ;

      void Profiler::startBlock(const std::string& name)
      {
        if (!m_activated)
          return ;
        Block block ;
        block.m_name = name ;
        m_openned_blocks.push_back(block) ;

        ++getStatistic(block.m_name).m_number_of_openned ;

        if (m_openned_blocks.size() > m_maximum_stack)
          m_maximum_stack = m_openned_blocks.size() ;
      }

      Profiler::Statistic& Profiler::getStatistic(const std::string& name)
      {
        std::map<std::string,Statistic>::iterator function = m_statistics.find(name) ;

        if (function != m_statistics.end())
          return function->second ;
        else
        {
          Statistic& current = m_statistics[name] ;
          current.m_number_of_calls = 0 ;
          current.m_total_elapsed_milliseconds = 0 ;
          current.m_inner_milliseconds = 0 ;
          current.m_name = name ;
          current.m_number_of_openned = 0 ;

          return current ;
        }

      }

      void Profiler::endBlock(const std::string&)
      {
        if (!m_activated)
          return ;
        Block block = m_openned_blocks.back() ;

        float elapsed = block.m_timer.getMilliSecond() ;

        Statistic& current = getStatistic(block.m_name) ;
        ++current.m_number_of_calls ;
        --current.m_number_of_openned ;

        if (current.m_number_of_openned == 0)
          current.m_total_elapsed_milliseconds += elapsed ;

        current.m_inner_milliseconds += elapsed ;

        m_openned_blocks.pop_back() ;

        if (!m_openned_blocks.empty())
        {
          Statistic& enclosing = getStatistic(m_openned_blocks.back().m_name) ;
          enclosing.m_inner_milliseconds -= elapsed ;
        }
      }

      void Profiler::enterNotify(const std::string& type)
      {
        m_current_notify = type ;
        std::map<std::string,NotifyStatistic>::iterator trait = m_notify_statistics.find(m_current_notify) ;
        if (trait == m_notify_statistics.end())
        {
          m_notify_statistics[m_current_notify].m_number_of_notify = 0 ;
          m_notify_statistics[m_current_notify].m_number_of_updated_observers = 0 ;
          m_notify_statistics[m_current_notify].m_number_of_depending_notify = 0 ;
          m_notify_statistics[m_current_notify].m_number_of_depending_with_observers = 0 ;
        }

        ++m_notify_statistics[m_current_notify].m_number_of_notify ;
      }

      void Profiler::addObserverUpdate()
      {
        ++m_notify_statistics[m_current_notify].m_number_of_updated_observers ;
      }

      void Profiler::addNotifyDependent()
      {
        ++m_notify_statistics[m_current_notify].m_number_of_depending_notify ;
      }

      void Profiler::addNotifyDependentWithObserver()
      {
        ++m_notify_statistics[m_current_notify].m_number_of_depending_with_observers ;
      }

      void Profiler::addDependentNotified(const std::string& name)
      {
        m_notify_statistics[m_current_notify].m_dependents.insert(name) ;
      }

      void Profiler::leaveNotify()
      {
        m_current_notify = "" ;
      }

      void Profiler::reset()
      {
        m_statistics.clear() ;
        m_openned_blocks.clear() ;
        m_maximum_stack = 0 ;
        m_activated = true ;
      }

      void Profiler::print()
      {
        std::cout << "maximum stack size " << m_maximum_stack << std::endl ;
        std::cout << "name\tnumber_of_calls\telapsed(milli seconds)\tinner(milli seconds)" << std::endl ;
        for(std::map<std::string,Profiler::Statistic>::iterator statistic = m_statistics.begin() ; statistic != m_statistics.end() ; ++statistic)
        {
         std::cout << statistic->first << "\t"
                   << statistic->second.m_number_of_calls << "\t"
                   << statistic->second.m_total_elapsed_milliseconds << "\t"
                   << statistic->second.m_inner_milliseconds << std::endl ;
        }

        std::cout << "trait_name\tnumber_of_calls\tnumber_of_view_updated\tnumber_of_depending_notify\tnumber_of_depending_with_observers\tdependent_traits" << std::endl ;
        for(std::map<std::string,NotifyStatistic>::iterator statistic = m_notify_statistics.begin() ; statistic != m_notify_statistics.end() ; ++statistic)
        {
          std::cout << statistic->first << "\t"
                    << statistic->second.m_number_of_notify << "\t"
                    << statistic->second.m_number_of_updated_observers << "\t"
                    << statistic->second.m_number_of_depending_notify << "\t"
                    << statistic->second.m_number_of_depending_with_observers ;

          for(std::set<std::string>::iterator dependent = statistic->second.m_dependents.begin() ; dependent != statistic->second.m_dependents.end() ; ++dependent)

            std::cout << " " << *dependent ;

          std::cout << std::endl ;
        }

        m_activated = false ;
      }



    }
  }
}
