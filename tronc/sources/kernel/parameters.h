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
#ifndef PU_KERNEL_PARAMETERS_H_
#define PU_KERNEL_PARAMETERS_H_

#include <map>
#include <string>
#include <set>
#include <memory>
#include <boost/variant.hpp>

namespace ProjetUnivers {
  namespace Kernel {

    /// Handle parameters loaded from a configuration file.  
    class Parameters 
    {
    public:
      
      /// Empty the parameters. 
      static void reset() ;
      
      /// Load new parameters.
      /*!
        Add parameters to already loaded parameters.
      */
      static void load(const std::string& file_path) ;

      /// Access to a value of type T.
      /*!
        @throw Kernel::ExceptionKernel if not found
      */
      template <typename T>
      static T getValue(const std::string& section,
                        const std::string& name) ;

      /// Access to a value of type T.
      /*!
        @returns default_value if not found
      */
      template <typename T>
      static T getValue(const std::string& section,
                        const std::string& name,
                        T default_value) ;
      
      /// Access to the modules where log is activated.
      /*!
        To activate a log : 
          add log=true in the module section of the parameter file.
      */
      static std::set<std::string> getActivatedLogs() ;

    private:
      
      /// Load the parameters
      void internal_load(const std::string& file_path) ;
      
    /*!
      @name Access methods
      
      Parametesr are organized in sections and have a name.
      Handled basic types are boolean, string and numerics.
      
    */
    // @{
      
      /// Access to a value of type T.
      template <typename T>
      T internalGetValue(const std::string& section,
                         const std::string& name) const ;
      
    // @}
      
      /// section --> name --> value 
      std::map<std::string,
               std::map<std::string,
                        boost::variant<float,std::string,bool> > > m_parameters ;
      
      
      /// Singleton instance.
      static std::auto_ptr<Parameters> m_instance ;
      
    };
  }
}

#include <kernel/implementation/parameters.cxx>

#endif /*PU_KERNEL_PARAMETERS_H_*/
