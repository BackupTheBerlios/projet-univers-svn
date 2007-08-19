/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2007 Mathieu ROGER rogma.boami@free.fr             *
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
#include <boost/variant.hpp>

namespace ProjetUnivers {
  namespace Kernel {

    /// Handle parameters loaded from a configuration file.  
    class Parameters 
    {
    public:
      
      /// Load new parameters.
      static void load(const std::string& file_path) ;

      /// Access to a value of type T.
      template <typename T>
      static T getValue(const std::string& section,
                        const std::string& name) ;
      

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
